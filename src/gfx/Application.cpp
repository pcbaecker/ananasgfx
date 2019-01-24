#include <ee/Log.hpp>
#include <ananasgfx/gfx/Application.hpp>

namespace gfx {

    void Application::registerWindow(std::shared_ptr<Window> window) noexcept {
        this->mWindows.push_back(window);
    }

    bool Application::initWindows() noexcept {
        // Go through windows
        for (auto& window : this->mWindows) {
            try {
                // Try to initialize the window
                if (!window->init()) {
                    return false;
                }

                // Provide the renderer to the window
                window->setRenderer(Renderer::create());

                // Initialize the top
                if (!window->mSceneStack.empty()) {
                    window->mSceneStack.top()->init();
                }
            } catch (ee::Exception& e) {
                ee::Log::log(ee::LogLevel::Error, e);
                return false;
            } catch (std::exception& e) {
                ee::Log::log(ee::LogLevel::Error, "", __PRETTY_FUNCTION__, "Received exception", {
                    ee::Note("what()", e.what())
                });
                return false;
            }
        }

        return true;
    }

    void Application::tick() noexcept {
        // TODO event handling here

        // Iterate through all windows
        for (auto it = this->mWindows.begin(); it != this->mWindows.end(); it++) {
            auto& window = (*it);

            // Check if this window should be closed
            if (window->shouldClose()) {
                it = this->mWindows.erase(it);
                continue;
            }

            window->makeContext();

            window->tick();

            window->swapBuffers();
        }
    }

    namespace _internal {

        ApplicationStore &ApplicationStore::getInstance() noexcept {
            static ApplicationStore INSTANCE;
            return INSTANCE;
        }

        size_t ApplicationStore::getNumberOfApplications() const noexcept {
            return this->mApplications.size();
        }

        ApplicationStore::ApplicationStore() noexcept {

        }

        ApplicationProxyBase::ApplicationProxyBase(const std::string& name) noexcept {
            ApplicationStore::getInstance().registerApplicationProxy(name, this);
        }

        void ApplicationStore::registerApplicationProxy(const std::string& name, ApplicationProxyBase *pApplication) noexcept {
            this->mApplications.emplace(name, pApplication);
        }

        const std::map<std::string,ApplicationProxyBase *> ApplicationStore::getApplications() const noexcept {
            return this->mApplications;
        }

    }

}