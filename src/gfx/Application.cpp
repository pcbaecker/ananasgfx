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

    bool Application::isDone() const noexcept {
        return this->mWindows.empty();
    }

    void Application::setMaxLifetime(long maxlifetime) noexcept {
        this->mMaxLifetime = maxlifetime;
    }

    void Application::tick() noexcept {
        // Calculate delta time
        float delta = std::chrono::duration<float, std::ratio<1>>(std::chrono::steady_clock::now() - this->mLastUpdate).count();
        this->mLastUpdate = std::chrono::steady_clock::now();

        // Handle lifetime
        this->mLifetime += delta;
        if (this->mMaxLifetime > 0 && this->mLifetime >= this->mMaxLifetime) {
            // We exceeded lifetime
            ee::Log::log(ee::LogLevel::Info, "", __PRETTY_FUNCTION__, "Lifetime exceeded", {
                ee::Note("Lifetime in s", this->mLifetime)
            });
            this->mWindows.clear();
            return;
        }

        // Execute tasks
        {
            // To get and execute tasks we need to lock the mutex
            std::lock_guard<std::mutex> guard(this->mTaskMutex);

            // Make sure there are some tasks to execute
            if (!this->mTasks.empty()) {
                // Iterate through the tasks
                auto it = this->mTasks.begin();
                while (it != this->mTasks.end()) {
                    // Execute the task
                    if ((*it)->run(this)) {
                        // Return true -> we want to retain the task to execute it again next tick
                        it++;
                    } else {
                        // Return false -> we can release the task
                        it = this->mTasks.erase(it);
                    }
                }
            }
        }

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

            window->tick(delta);

            window->swapBuffers();
        }
    }

    void Application::addTask(std::shared_ptr<Task> task) noexcept {
        // To modify the list we need to lock the mutex
        std::lock_guard<std::mutex> guard(this->mTaskMutex);

        // Add task to the list
        this->mTasks.push_back(task);
    }

    std::list<std::shared_ptr<Window>> &Application::getWindows() noexcept {
        return this->mWindows;
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