#include <ee/Log.hpp>
#include <ananasgfx/gfx/Application.hpp>

namespace gfx {

    std::vector<std::string> split(const std::string& str, const std::string& delim) {
        std::vector<std::string> tokens;
        size_t prev = 0, pos = 0;
        do {
            pos = str.find(delim, prev);
            if (pos == std::string::npos) pos = str.length();
            std::string token = str.substr(prev, pos-prev);
            if (!token.empty()) tokens.push_back(token);
            prev = pos + delim.length();
        } while (pos < str.length() && prev < str.length());
        return tokens;
    }

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

                // Provide the FileManager to the window
                window->mFileManager = this->mFileManager;

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

    void Application::close() noexcept {
        this->mWindows.clear();
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

            window->handleEvents();

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

    void Application::setDevmode(bool devmode) noexcept {
        this->mDevmode = devmode;
    }

    bool Application::isDevmode() const noexcept {
        return this->mDevmode;
    }

    const FileManager &Application::getFileManager() const {
        // Make sure FileManager is set before
        if (!this->mFileManager) {
            throw ApplicationException(__PRETTY_FUNCTION__, "FileManager must be set before calling this method", {});
        }

        // Return a reference of the FileManager.
        return *this->mFileManager;
    }

    void Application::setFileManager(std::shared_ptr<FileManager> fileManager) noexcept {
        this->mFileManager = fileManager;
    }

    std::optional<gfx::Node *> Application::getNode(const std::string &nodepath) noexcept {
        // Split by dots
        auto steps = split(nodepath, ".");

        if (steps.size() < 2 ) {
            return std::nullopt;
        }
        if (steps[0] != "window" || steps[1] != "scene") {
            return std::nullopt;
        }

        // Get the root scene
        auto window = *this->getWindows().begin();
        auto sceneOpt = window->getScene();
        if (!sceneOpt.has_value()) {
            return std::nullopt;
        }

        // Check if we just want the root scene
        if (steps.size() == 2) {
            return *sceneOpt;
        }

        // Follow the id chain to the end
        int i = 2;
        gfx::Node* node = *sceneOpt;
        while (i < steps.size()) {
            // Try to find the node for this chain element
            auto opt = node->getChildWithId(steps[i++]);
            if (!opt.has_value()) {
                return std::nullopt;
            }

            // We found the node, store it
            node = *opt;
        }

        return node;
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