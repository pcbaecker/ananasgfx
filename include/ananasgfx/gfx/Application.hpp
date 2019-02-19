#ifndef GFX_APPLICATION_H
#define GFX_APPLICATION_H

#include <memory>
#include <map>
#include <chrono>
#include <mutex>

#include "Window.hpp"
#include "Task.hpp"
#include "FileManager.hpp"

namespace gfx {

    namespace _internal {
        class ApplicationManager;
    }

    DEFINE_EXCEPTION(ApplicationException);

    /**
     * @brief The base application class every application should derive from.
     */
    class Application {
        friend class ::gfx::_internal::ApplicationManager;
    public:
        virtual bool init() noexcept = 0;

        void registerWindow(std::shared_ptr<Window> window) noexcept;
        void tick() noexcept;
        bool isDone() const noexcept;
        void close() noexcept;

        void setMaxLifetime(long maxlifetime) noexcept;

        void addTask(std::shared_ptr<Task> task) noexcept;

        std::list<std::shared_ptr<Window>>& getWindows() noexcept;

        std::optional<gfx::Node*> getNode(const std::string& nodepath) noexcept;

        void setDevmode(bool devmode) noexcept;
        bool isDevmode() const noexcept;

        /**
         * @brief Returns a reference to the filemanager.
         *
         * Throws an exception if the filemanager is not set before.
         * @throws ee::Exception
         * @return Reference to the filemanager.
         */
        const FileManager& getFileManager() const;
        void setFileManager(std::shared_ptr<FileManager> fileManager) noexcept;

    private:
        bool initWindows() noexcept;

    private:
        std::chrono::steady_clock::time_point mLastUpdate = std::chrono::steady_clock::now();
        std::list<std::shared_ptr<Window>> mWindows;
        float mLifetime = 0.0f;
        long mMaxLifetime = 0;
        bool mDevmode = false;

        std::mutex mTaskMutex;
        std::list<std::shared_ptr<gfx::Task>> mTasks;
        std::shared_ptr<FileManager> mFileManager;
    };

    namespace _internal {

        /**
         * @brief Base proxy interface.
         */
        class ApplicationProxyBase {
        public:
            explicit ApplicationProxyBase(const std::string& name) noexcept;
            virtual std::shared_ptr<Application> createInstance() noexcept = 0;
        };

        /**
         * @brief The application store, where all applications are registered.
         */
        class ApplicationStore {
        public:
            static ApplicationStore& getInstance() noexcept;

            void registerApplicationProxy(const std::string& name, ApplicationProxyBase *pApplication) noexcept;
            size_t getNumberOfApplications() const noexcept;
            const std::map<std::string,ApplicationProxyBase*> getApplications() const noexcept;

        private:
            ApplicationStore() noexcept;

        private:
            std::map<std::string,ApplicationProxyBase*> mApplications;
        };

        /**
         * @brief Template class to register applications to make instances later.
         *
         * @tparam T
         */
        template <class T> class ApplicationProxy : public ApplicationProxyBase {
        public:
            explicit ApplicationProxy(const std::string& name) noexcept : ApplicationProxyBase(name) {

            }

            std::shared_ptr<Application> createInstance() noexcept override {
                return std::make_shared<T>();
            }

        };

    }

}

#define REGISTER_APPLICATION(appname,appclass) \
gfx::_internal::ApplicationProxy<appclass> app_ ## appclass(appname) // NOLINT

#endif