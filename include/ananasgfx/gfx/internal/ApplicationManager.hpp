#ifndef GFX_INTERNAL_APPLICATIONMANANGER_H
#define GFX_INTERNAL_APPLICATIONMANANGER_H

#include <thread>
#include <functional>
#include "../Application.hpp"
#include "ApplicationStore.hpp"

namespace gfx::_internal {

    /**
     * @brief Handles the creation of applications.
     */
    class ApplicationManager {
    public:
        /**
         * @brief Stores the global return code.
         *
         * Especially used for ApplicationTests.
         */
        static int ReturnCode;

        /**
         * @brief Removes all applications that are not present in the apps list.
         *
         * @param map The map that should only contain the applications named in the list.
         * @param apps The list that holds the applications that should remain.
         */
        static void removeUnlisted(
                std::map<std::string,ApplicationProxyBase*>& map,
                std::vector<std::string>& apps) noexcept;

        /**
         * @brief Constructor.
         *
         * @param devmode If true the devmode is activated.
         * @param appNames List containing the names of applications that we want to launch (empty means launch all).
         * @param appLifetime The app lifetime (Zero means infinite).
         * @param resourceSpace The resource space path.
         * @param userSpace The user space path.
         * @param fullscreen If true the app should run in fullscreen.
         * @param hideCursor If true the app should hide the cursor.
         */
        ApplicationManager(
                bool devmode,
                std::vector<std::string> appNames,
                long appLifetime,
                std::string resourceSpace,
                std::string userSpace,
                bool fullscreen,
                bool hideCursor) noexcept;

        /**
         * @brief Destructor.
         */
        virtual ~ApplicationManager() noexcept;

        /**
         * @brief Is called every time the current app should do something.
         *
         * Normally called without delay from an outer loop.
         */
        void tick() noexcept;

        /**
         * @brief Signals that all applications finished.
         *
         * @return True if we can terminate the program.
         */
        bool isDone() const noexcept;

        /**
         * @brief Returns a the current application running.
         *
         * @return The current application running.
         */
        const std::shared_ptr<Application>& getCurrentApplication() noexcept;

    private:
        /**
         * @brief Sets up the application test.
         *
         * @param appname The name of the application.
         * @param application The pointer to the application.
         */
        void setupApplicationTest(const std::string& appname, std::shared_ptr<Application> application) noexcept;

    private:
        /**
         * @brief Defines if the program runs in devmode.
         */
        bool mDevmode = false;

        /**
         * @brief Defines the max app lifetime.
         */
        long mMaxAppLifetime;

        /**
         * @brief Defines the resource path.
         */
        std::string mResourcePath;

        /**
         * @brief Defines the user path.
         */
        std::string mUserPath;

        /**
         * @brief Defines if we want to use fullscreen.
         */
        bool mFullscreen = false;

        /**
         * @brief Defines if we want to hide the cursor.
         */
        bool mHideCursor = true;

        /**
         * @brief The current application running.
         */
        std::shared_ptr<Application> pCurrentApplication = nullptr;

        /**
         * @brief The map containing all applications that we want to run.
         */
        std::map<std::string,ApplicationProxyBase*> mApplications;

        /**
         * @brief The iterator that pointer to the next application to launch.
         */
        std::map<std::string,ApplicationProxyBase*>::const_iterator mIterator;

        /**
         * @brief The thread where the ApplicationTest runs inside.
         */
        std::unique_ptr<std::thread> mTestThread;
    };

}

#endif