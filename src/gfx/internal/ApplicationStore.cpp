#include <ananasgfx/gfx/internal/ApplicationStore.hpp>

namespace gfx::_internal {

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