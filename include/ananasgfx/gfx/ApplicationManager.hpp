#ifndef GFX_APPLICATIONMANANGER_H
#define GFX_APPLICATIONMANANGER_H

#include <ananasgfx/gfx/Application.hpp>

namespace gfx::_internal {

    class ApplicationManager {
    public:
        ApplicationManager() noexcept;

        void surfaceAvailable() noexcept;
        void tick() noexcept;
        bool isDone() const noexcept;
    private:
        bool mDone = false;
        std::shared_ptr<Application> pCurrentApplication = nullptr;
        std::map<std::string,ApplicationProxyBase*> mApplications;
        std::map<std::string,ApplicationProxyBase*>::const_iterator mIterator;
    };

}

#endif