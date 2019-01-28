#ifndef TEST_TEST_H
#define TEST_TEST_H

#include <string>
#include <memory>
#include <list>

namespace test {

    class ApplicationTest {
    public:
        virtual std::string getDescription() noexcept = 0;
    };

    namespace _internal {

        class ApplicationTestProxyBase {
        public:
            ApplicationTestProxyBase() noexcept;
            virtual std::shared_ptr<ApplicationTest> createInstance() noexcept = 0;
        };

        class ApplicationTestStore {
        public:
            static ApplicationTestStore& getInstance() noexcept;

            void registerApplicationTestProxy(ApplicationTestProxyBase *pApplicationTest) noexcept;
            size_t getNumberOfApplicationTests() const noexcept;
            const std::list<ApplicationTestProxyBase*> getApplications() const noexcept;

        private:
            ApplicationTestStore() noexcept;

        private:
            // TODO This must be std::map<std::string,std::list<ApplicationTestProxyBase*>> where the string is the Application name to test
            std::list<ApplicationTestProxyBase*> mApplications;
        };

        template <class T> class ApplicationTestProxy : public ApplicationTestProxyBase {
        public:

            std::shared_ptr<ApplicationTest> createInstance() noexcept override {
                return std::make_shared<T>();
            }

        };

    }

}





#define NN_UNIQUENAME(name,line) name##line
#define APPLICATION_TEST(appname) NN_TESTCLASS(NN_UNIQUENAME(ananasgfx_test,__COUNTER__), description)

#define NN_TESTCLASS(classname, description) \
class classname; \
test::_internal::ApplicationTestProxy<classname> NN_UNIQUENAME(ananasgfx_test_proxy, __COUNTER__); \
class classname : public test::ApplicationTest

#endif