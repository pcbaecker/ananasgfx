#include <ananasgfx/test/ApplicationTest.hpp>
#include <ananasgfx/gfx/Application.hpp>

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

    void ApplicationTest::setApplication(std::shared_ptr<gfx::Application> application) noexcept {
        this->mApplication = std::move(application);
    }

    void ApplicationTest::If(std::function<bool(gfx::Application*)> condition,
                             std::function<void(gfx::Application*)> thenDo,
                             std::function<void(gfx::Application*)> elseDo) {
        this->mApplication->addTask(std::make_shared<IfTask>(condition, thenDo, elseDo));
    }

    bool IfTask::run(gfx::Application* application) noexcept {
        // Check if our condition is matched
        if (this->mCondition && this->mCondition(application)) {
            // Make sure we have an thenDo() function
            if (this->mThenDo) {
                // Execute the thenDo()
                this->mThenDo(application);
            }
        } else {
            // Make sure we have an elseDo() function
            if (this->mElseDo) {
                // Execute the elseDo()
                this->mElseDo(application);
            }
        }

        // We never want to retain the task
        return false;
    }

    IfTask::IfTask(std::function<bool(gfx::Application*)> condition,
                   std::function<void(gfx::Application*)> thenDo,
                   std::function<void(gfx::Application*)> elseDo) noexcept :
                   mCondition(std::move(condition)), mThenDo(std::move(thenDo)), mElseDo(std::move(elseDo)) {

    }

}