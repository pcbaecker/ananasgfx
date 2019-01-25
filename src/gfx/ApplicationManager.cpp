#include <ananasgfx/gfx/ApplicationManager.hpp>
#include <ananasgfx/gfx/Application.hpp>
#include <ee/Log.hpp>
#include <algorithm>

namespace gfx::_internal {

    void ApplicationManager::removeUnlisted(
            std::map<std::string, ApplicationProxyBase *> &mapOfApps,
            std::vector<std::string> &appsToKeep) noexcept {
        // Iterate through all applications
        auto it = mapOfApps.begin();
        while (it != mapOfApps.end()) {
            auto &app = *it;

            // Check if app name is in the list of applications we want to keep
            auto jt = std::find(appsToKeep.begin(), appsToKeep.end(), app.first);
            if (jt != appsToKeep.end()) {
                // We found the app name in the list of applications we want to keep, keep it in map
                // Remove appName from the vector to signal that we found it
                appsToKeep.erase(jt);
                it++;
            } else {
                // We did not find the app name in the list of applications we want to keep
                it = mapOfApps.erase(it);
            }
        }

        // If we did not find some of the apps we want to keep, we show an warning
        if (!appsToKeep.empty()) {
            for (auto &app : appsToKeep) {
                ee::Log::log(ee::LogLevel::Warning, "", __PRETTY_FUNCTION__, "Application not found", {
                        ee::Note("Name", app)
                });
            }
        }
    }

    ApplicationManager::ApplicationManager(
            std::vector<std::string> appNames,
            long appLifetime,
            const std::string &resourceSpace,
            const std::string &userSpace,
            bool fullscreen,
            bool hideCursor
    ) noexcept :
            mMaxAppLifetime(appLifetime),
            mApplications(ApplicationStore::getInstance().getApplications()) {
        // Check if we got appNames, which means we should only execute that apps
        if (!appNames.empty()) {
            removeUnlisted(this->mApplications, appNames);
        }

        // Put the iterator to the first application
        this->mIterator = this->mApplications.cbegin();
    }

    void ApplicationManager::tick() noexcept {
        // If we have a current application running, we update it
        if (this->pCurrentApplication.use_count()) {
            // Tick the current application
            this->pCurrentApplication->tick();

            // Check if the application has finished
            if (this->pCurrentApplication->isDone()) {
                this->pCurrentApplication.reset();
            }
            return;
        }

        // There is currently no application running, check if we have some waiting
        if (this->mIterator != this->mApplications.cend()) {
            // Create a new application instance and increase the iterator
            auto &app = (*this->mIterator++);
            ee::Log::log(ee::LogLevel::Info, "", __PRETTY_FUNCTION__, "Creating application instance", {
                    ee::Note("ApplicationName", app.first)
            });
            this->pCurrentApplication = app.second->createInstance();
            this->pCurrentApplication->setMaxLifetime(this->mMaxAppLifetime);

            // Initialize the application
            ee::Log::log(ee::LogLevel::Trace, "", __PRETTY_FUNCTION__, "Initializing application", {
                    ee::Note("ApplicationName", app.first)
            });
            if (!this->pCurrentApplication->init()) {
                ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Unable to initialize application", {
                        ee::Note("ApplicationName", app.first)
                });
                this->pCurrentApplication.reset();
                return;
            }

            // Initialize the windows
            ee::Log::log(ee::LogLevel::Trace, "", __PRETTY_FUNCTION__, "Initializing windows", {
                    ee::Note("ApplicationName", app.first)
            });
            if (!this->pCurrentApplication->initWindows()) {
                ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Unable to initialize windows", {
                        ee::Note("ApplicationName", app.first)
                });
                this->pCurrentApplication.reset();
                return;
            }

            // To draw the first frame we call tick() again
            ee::Log::log(ee::LogLevel::Trace, "", __PRETTY_FUNCTION__, "Drawing first frame", {
                    ee::Note("ApplicationName", app.first)
            });
            this->tick();
        }
    }

    bool ApplicationManager::isDone() const noexcept {
        // We are done if there is no current application running
        return this->pCurrentApplication.use_count() == 0
               // And the iterator is at the end
               && this->mIterator == this->mApplications.end();
    }

}