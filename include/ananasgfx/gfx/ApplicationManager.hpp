#ifndef GFX_APPLICATIONMANANGER_H
#define GFX_APPLICATIONMANANGER_H

#include <ananasgfx/gfx/Application.hpp>

namespace gfx::_internal {

    class ApplicationManager {
    public:
        static void removeUnlisted(
                std::map<std::string,ApplicationProxyBase*>& map,
                std::vector<std::string>& apps) noexcept;

        ApplicationManager(
                std::vector<std::string> appNames,
                long appLifetime,
                const std::string& resourceSpace,
                const std::string& userSpace,
                bool fullscreen,
                bool hideCursor) noexcept;

        void surfaceAvailable() noexcept;
        void tick() noexcept;
        bool isDone() const noexcept;
    private:
        long mMaxAppLifetime;
        bool mDone = false;
        std::shared_ptr<Application> pCurrentApplication = nullptr;
        std::map<std::string,ApplicationProxyBase*> mApplications;
        std::map<std::string,ApplicationProxyBase*>::const_iterator mIterator;
    };

}

#endif