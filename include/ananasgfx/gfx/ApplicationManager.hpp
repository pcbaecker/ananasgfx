#ifndef GFX_APPLICATIONMANANGER_H
#define GFX_APPLICATIONMANANGER_H

#include <thread>
#include <functional>
#include <ananasgfx/gfx/Application.hpp>

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
                const std::string& resourceSpace,
                const std::string& userSpace,
                bool fullscreen,
                bool hideCursor) noexcept;

        ~ApplicationManager() noexcept;

        void surfaceAvailable() noexcept;
        void tick() noexcept;
        bool isDone() const noexcept;

    private:
        void setupApplicationTest(const std::string& appname, std::shared_ptr<Application> application) noexcept;

    private:
        bool mDevmode = false;
        long mMaxAppLifetime;
        bool mDone = false;
        std::shared_ptr<Application> pCurrentApplication = nullptr;
        std::map<std::string,ApplicationProxyBase*> mApplications;
        std::map<std::string,ApplicationProxyBase*>::const_iterator mIterator;
        std::unique_ptr<std::thread> mTestThread;
    };

}

#endif