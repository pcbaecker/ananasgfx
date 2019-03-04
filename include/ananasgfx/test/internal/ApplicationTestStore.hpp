#ifndef TEST_INTERNAL_APPLICATIONTESTSTORE_H
#define TEST_INTERNAL_APPLICATIONTESTSTORE_H

#include <string>
#include <memory>
#include <list>
#include <map>

namespace gfx {
    class Application;
}

namespace test {

    class ApplicationTest;

    namespace _internal {

        /**
         * @brief The proxy base for the ApplicationTest instances.
         */
        class ApplicationTestProxyBase {
        public:
            /**
             * @brief Constructor.
             *
             * @param appname The name of the app that we want to test.
             */
            explicit ApplicationTestProxyBase(const std::string &appname) noexcept;

            /**
             * @brief Creates a new instance of the ApplicationTest.
             *
             * @param application The application we want to test.
             * @return The created ApplicationTest instance.
             */
            virtual std::shared_ptr<ApplicationTest>
            createInstance(std::shared_ptr<gfx::Application> application) noexcept = 0;
        };

        /**
         * @brief The store where all ApplicationTests are registered.
         */
        class ApplicationTestStore {
        public:
            /**
             * @brief Returns the instance of the ApplicationTestStore.
             *
             * @return The global instance.
             */
            static ApplicationTestStore &getInstance() noexcept;

            /**
             * @brief Registers a new ApplicationTest in the store.
             *
             * @param appname The name of the application we want to test.
             * @param pApplicationTest Pointer to the applicationTestProxyBase.
             */
            void registerApplicationTestProxy(const std::string &appname,
                                              ApplicationTestProxyBase *pApplicationTest) noexcept;

            /**
             * @brief Returns the number of ApplicationTests registered.
             *
             * @return The number of ApplicationTests registered.
             */
            size_t getNumberOfApplicationTests() const noexcept;

            /**
             * @brief Returns the map containing all ApplicationTests.
             *
             * @return The map containing all ApplicationTests.
             */
            const std::map<std::string, std::list<ApplicationTestProxyBase *>> getApplicationTests() const noexcept;

        private:
            /**
             * @brief Hidden constructor.
             */
            ApplicationTestStore() noexcept;

        private:
            /**
             * @brief The map with all ApplicationTests.
             */
            std::map<std::string, std::list<ApplicationTestProxyBase *>> mApplications;
        };

        /**
         * @brief The template ApplicationTest proxy.
         *
         * @tparam T The template parameter that declares the ApplicationTest we want to instanciate.
         */
        template<class T>
        class ApplicationTestProxy : public ApplicationTestProxyBase {
        public:
            /**
             * @brief Constructor.
             *
             * @param appname The name of the application we want to test.
             */
            explicit ApplicationTestProxy(const std::string &appname) noexcept :
            ApplicationTestProxyBase(appname), mAppname(appname) {}

            /**
             * @brief Creates the instance of an ApplicationTest.
             *
             * @param application The application we test.
             *
             * @return The created ApplicationTest instance.
             */
            std::shared_ptr<ApplicationTest>
            createInstance(std::shared_ptr<gfx::Application> application) noexcept override {
                auto test = std::make_shared<T>();
                test->setApplication(this->mAppname, application);
                return test;
            }

        private:
            /**
             * @brief The name of the Application we want to test.
             */
            std::string mAppname;
        };

    }

}

#endif