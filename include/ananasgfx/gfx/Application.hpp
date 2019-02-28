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
        /**
         * @brief Is called to initialize the application.
         *
         * @return True if initialization was successful.
         */
        virtual bool init() noexcept = 0;

        /**
         * @brief Registers the given window in this application.
         *
         * @param window The window to be registered.
         */
        void registerWindow(std::shared_ptr<Window> window) noexcept;

        /**
         * @brief Called every frame.
         */
        void tick() noexcept;

        /**
         * @brief Returns true if this application is done and can be terminated.
         *
         * @return True if application has finished.
         */
        bool isDone() const noexcept;

        /**
         * @brief Signals the application that it should finish gracefully now.
         */
        void close() noexcept;

        /**
         * @brief Sets the max lifetime of this application.
         */
        void setMaxLifetime(long maxlifetime) noexcept;

        /**
         * @brief Returns the max lifetime of this application.
         *
         * @return The max lifetime of this application.
         */
        long getMaxLifetime() const noexcept;

        /**
         * @brief Adds a gfx::Task to this application.
         *
         * @param task The task to be executed.
         */
        void addTask(std::shared_ptr<Task> task) noexcept;

        /**
         * @brief Returns all windows.
         *
         * @return A list containing all windows in this application.
         */
        std::list<std::shared_ptr<Window>>& getWindows() noexcept;

        /**
         * @brief Tries to find a single node matching the nodepath pattern given.
         *
         * @param nodepath The nodepath which specifies the node we want to find.
         * @return An optional that can contain a pointer to the node that matches the given pattern.
         */
        std::optional<gfx::Node*> getNode(const std::string& nodepath) noexcept;

        /**
         * @brief Sets this application to devmode.
         *
         * @param devmode Defines wheather the devmode is enabled or not.
         */
        void setDevmode(bool devmode) noexcept;

        /**
         * @brief Returns true if devmode is enabled for this application.
         *
         * @return True if devmode is enabled.
         */
        bool isDevmode() const noexcept;

        /**
         * @brief Returns a reference to the filemanager.
         *
         * Throws an exception if the filemanager is not set before.
         * @throws ee::Exception
         * @return Reference to the filemanager.
         */
        const FileManager& getFileManager() const;

        /**
         * @brief Sets the filemanager for this application.
         *
         * @param fileManager The filemanager for this application.
         */
        void setFileManager(std::shared_ptr<FileManager> fileManager) noexcept;

    private:
        /**
         * @brief Initializes all registered windows.
         */
        bool initWindows() noexcept;

    private:
        /**
         * @brief Tracks the time of the last update.
         */
        std::chrono::steady_clock::time_point mLastUpdate = std::chrono::steady_clock::now();

        /**
         * @brief Contains all registered windows.
         */
        std::list<std::shared_ptr<Window>> mWindows;

        /**
         * @brief The current lifetime of this application.
         */
        float mLifetime = 0.0f;

        /**
         * @brief The max lifetime of this application (Zero means infinite).
         */
        long mMaxLifetime = 0;

        /**
         * @brief True enables devmode for this application.
         */
        bool mDevmode = false;

        /**
         * @brief Mutex that is used for concurrency with gfx::Tasks.
         */
        std::mutex mTaskMutex;

        /**
         * @brief This list contains all gfx::Tasks (Watch concurrency).
         */
        std::list<std::shared_ptr<gfx::Task>> mTasks;

        /**
         * @brief The file manager for this application.
         */
        std::shared_ptr<FileManager> mFileManager;
    };

}

#endif

#include "internal/ApplicationStore.hpp"