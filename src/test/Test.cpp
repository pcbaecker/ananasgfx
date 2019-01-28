#include <ananasgfx/test/Test.hpp>

namespace test {

    namespace _internal {

        ApplicationTestStore &ApplicationTestStore::getInstance() noexcept {
            static ApplicationTestStore INSTANCE;
            return INSTANCE;
        }

        size_t ApplicationTestStore::getNumberOfApplicationTests() const noexcept {
            return this->mApplications.size();
        }

        ApplicationTestStore::ApplicationTestStore() noexcept {

        }

        ApplicationTestProxyBase::ApplicationTestProxyBase() noexcept {
            ApplicationTestStore::getInstance().registerApplicationTestProxy(this);
        }

        void ApplicationTestStore::registerApplicationTestProxy(ApplicationTestProxyBase *pApplication) noexcept {
            this->mApplications.push_back(pApplication);
        }

        const std::list<ApplicationTestProxyBase *> ApplicationTestStore::getApplications() const noexcept {
            return this->mApplications;
        }

    }

}