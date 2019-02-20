#include <ananasgfx/gfx/ApplicationManager.hpp>
#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/test/ApplicationTest.hpp>
#include <ee/Log.hpp>
#include <algorithm>

namespace gfx::_internal {

    int ApplicationManager::ReturnCode = EXIT_SUCCESS;

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
            bool devmode,
            std::vector<std::string> appNames,
            long appLifetime,
            const std::string &resourceSpace,
            const std::string &userSpace,
            bool fullscreen,
            bool hideCursor
    ) noexcept :
            mDevmode(devmode),
            mMaxAppLifetime(appLifetime),
            mResourcePath(std::move(resourceSpace)),
            mUserPath(std::move(userSpace)),
            mApplications(ApplicationStore::getInstance().getApplications()) {
        // Check if we got appNames, which means we should only execute that apps
        if (!appNames.empty()) {
            removeUnlisted(this->mApplications, appNames);
        }

        // Put the iterator to the first application
        this->mIterator = this->mApplications.cbegin();
    }

    ApplicationManager::~ApplicationManager() noexcept {
        if (this->mTestThread && this->mTestThread->joinable()) {
            this->mTestThread->join();
        }
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
            this->pCurrentApplication->setDevmode(this->mDevmode);
            this->pCurrentApplication->setFileManager(std::make_shared<FileManager>(this->mResourcePath, this->mUserPath));

            // Setup ApplicationTest for the launched Application (if not test exist, nothing will be done)
            this->setupApplicationTest(app.first, this->pCurrentApplication);

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

    void ApplicationManager::surfaceAvailable() noexcept {

    }

    std::shared_ptr<Application> ApplicationManager::getCurrentApplication() noexcept {
        return this->pCurrentApplication;
    }

    void ApplicationManager::setupApplicationTest(const std::string &appname,
                                                  std::shared_ptr<Application> application) noexcept {
        // Check if we have a sidekick ApplicationTest
        if (test::_internal::ApplicationTestStore::getInstance().getApplicationTests().count(appname)
            && !test::_internal::ApplicationTestStore::getInstance().getApplicationTests().at(appname).empty()) {
            // Get a pointer to the ApplicationTest
            auto test = *test::_internal::ApplicationTestStore::getInstance().getApplicationTests().at(appname).begin();

            // If the thread is already defined we have to reset it
            if (this->mTestThread) {
                if (this->mTestThread->joinable()) {
                    this->mTestThread->join();
                }
                this->mTestThread.release();
            }

            // Start it in another thread
            this->mTestThread = std::make_unique<std::thread>([](
                    std::string appname,
                    std::shared_ptr<Application> appinstance,
                    test::_internal::ApplicationTestProxyBase *pApplicationTestProxyBase) {
                ee::Log::log(ee::LogLevel::Info, "", __PRETTY_FUNCTION__, "Starting ApplicationTest in another thread",
                             {
                                     ee::Note("ApplicationName", appname)
                             });

                // Create the ApplicationTest instance
                auto applicationTest = pApplicationTestProxyBase->createInstance(appinstance);

                // Run the test
                try {
                    applicationTest->run();
                } catch (ee::Exception &e) {
                    ee::Log::log(ee::LogLevel::Error, e);
                } catch (std::exception &e) {
                    ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Caught std::exception", {
                            ee::Note("what()", e.what())
                    });
                } catch (...) {
                    ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Caught unknown exception", {});
                }
            }, appname, application, test);
        }
    }
}