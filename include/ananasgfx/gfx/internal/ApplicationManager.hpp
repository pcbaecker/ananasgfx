#ifndef GFX_INTERNAL_APPLICATIONMANANGER_H
#define GFX_INTERNAL_APPLICATIONMANANGER_H

#include <thread>
#include <functional>
#include "../Application.hpp"
#include "ApplicationStore.hpp"

namespace gfx::_internal {

    class ApplicationManager {
    public:
        static int ReturnCode;

        static void removeUnlisted(
                std::map<std::string,ApplicationProxyBase*>& map,
                std::vector<std::string>& apps) noexcept;

        ApplicationManager(
                bool devmode,
                std::vector<std::string> appNames,
                long appLifetime,
                std::string resourceSpace,
                std::string userSpace,
                bool fullscreen,
                bool hideCursor) noexcept;

        ~ApplicationManager() noexcept;

        void surfaceAvailable() noexcept;
        void tick() noexcept;
        bool isDone() const noexcept;

        std::shared_ptr<Application> getCurrentApplication() noexcept;

    private:
        void setupApplicationTest(const std::string& appname, std::shared_ptr<Application> application) noexcept;

    private:
        bool mDevmode = false;
        long mMaxAppLifetime;
        std::string mResourcePath;
        std::string mUserPath;
        bool mDone = false;
        bool mFullscreen = false;
        bool mHideCursor = true;
        std::shared_ptr<Application> pCurrentApplication = nullptr;
        std::map<std::string,ApplicationProxyBase*> mApplications;
        std::map<std::string,ApplicationProxyBase*>::const_iterator mIterator;
        std::unique_ptr<std::thread> mTestThread;
    };

}

#endif