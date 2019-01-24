#include <ananasgfx/gfx/ApplicationManager.hpp>
#include <ananasgfx/gfx/Application.hpp>
#include <ee/Log.hpp>

namespace gfx::_internal {

    ApplicationManager::ApplicationManager() noexcept :
    mApplications(ApplicationStore::getInstance().getApplications()) {
        this->mIterator = this->mApplications.cbegin();
    }

    void ApplicationManager::tick() noexcept {
        // If we have a current application running, we update it
        if (this->pCurrentApplication.use_count()) {
            this->pCurrentApplication->tick();
            return;
        }

        // There is currently no application running, check if we have some waiting
        if (this->mIterator != this->mApplications.cend()) {
            // Create a new application instance and increase the iterator
            auto app = (*this->mIterator++);
            ee::Log::log(ee::LogLevel::Info, "", __PRETTY_FUNCTION__, "Creating application instance", {
                    ee::Note("ApplicationName", app.first, __PRETTY_FUNCTION__)
            });
            this->pCurrentApplication = app.second->createInstance();

            // Initialize the application
            ee::Log::log(ee::LogLevel::Trace, "", __PRETTY_FUNCTION__, "Initializing application", {
                ee::Note("ApplicationName", app.first, __PRETTY_FUNCTION__)
            });
            if (!this->pCurrentApplication->init()) {
                ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Unable to initialize application", {
                    ee::Note("ApplicationName", app.first, __PRETTY_FUNCTION__)
                });
                this->pCurrentApplication.reset();
                return;
            }

            // Initialize the windows
            ee::Log::log(ee::LogLevel::Trace, "", __PRETTY_FUNCTION__, "Initializing windows", {
                    ee::Note("ApplicationName", app.first, __PRETTY_FUNCTION__)
            });
            if (!this->pCurrentApplication->initWindows()) {
                ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Unable to initialize windows", {
                        ee::Note("ApplicationName", app.first, __PRETTY_FUNCTION__)
                });
                this->pCurrentApplication.reset();
                return;
            }

            // To draw the first frame we call tick() again
            ee::Log::log(ee::LogLevel::Trace, "", __PRETTY_FUNCTION__, "Drawing first frame", {
                    ee::Note("ApplicationName", app.first, __PRETTY_FUNCTION__)
            });
            this->tick();
        }
    }

    bool ApplicationManager::isDone() const noexcept {
        return false;
    }

}