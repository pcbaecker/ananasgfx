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

}

#endif

#include "internal/ApplicationStore.hpp"