#include <ananasgfx/test/ApplicationTest.hpp>

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

        ApplicationTestProxyBase::ApplicationTestProxyBase(const std::string& appname) noexcept {
            ApplicationTestStore::getInstance().registerApplicationTestProxy(appname, this);
        }

        void ApplicationTestStore::registerApplicationTestProxy(const std::string& appname, ApplicationTestProxyBase *pApplication) noexcept {
            this->mApplications[appname].push_back(pApplication);
        }

        const std::map<std::string,std::list<ApplicationTestProxyBase*>> ApplicationTestStore::getApplicationTests() const noexcept {
            return this->mApplications;
        }

    }

}