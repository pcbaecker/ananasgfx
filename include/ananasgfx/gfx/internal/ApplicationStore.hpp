#ifndef GFX_INTERNAL_APPLICATIONSTORE_H
#define GFX_INTERNAL_APPLICATIONSTORE_H

#include "../Application.hpp"

namespace gfx::_internal {

    /**
     * @brief Base proxy interface.
     */
    class ApplicationProxyBase {
    public:
        /**
         * @brief Constructor.
         *
         * @param name The name of the application.
         */
        explicit ApplicationProxyBase(const std::string& name) noexcept;

        /**
         * @brief Creates a new intance of the application.
         *
         * @return New instance of the application.
         */
        virtual std::shared_ptr<Application> createInstance() noexcept = 0;
    };

    /**
     * @brief The application store, where all applications are registered.
     */
    class ApplicationStore {
    public:
        /**
         * @brief Returns the instance of the ApplicationStore.
         *
         * Singleton.
         * @return Reference to the one and only instance of the ApplicationStore.
         */
        static ApplicationStore& getInstance() noexcept;

        /**
         * @brief Registers an application proxy in the store.
         *
         * @param name The name of the application.
         * @param pApplication Pointer to the application proxy base.
         */
        void registerApplicationProxy(const std::string& name, ApplicationProxyBase *pApplication) noexcept;

        /**
         * @brief Returns the number of applications registered in the store.
         *
         * @return The number of applications registered.
         */
        size_t getNumberOfApplications() const noexcept;

        /**
         * @brief Returns the application-name map.
         *
         * @return Reference to map containing the application-names.
         */
        const std::map<std::string,ApplicationProxyBase*> getApplications() const noexcept;

    private:
        /**
         * @brief Hidden constructor.
         */
        ApplicationStore() noexcept;

    private:
        /**
         * @brief The map containing the applications connected with the names.
         */
        std::map<std::string,ApplicationProxyBase*> mApplications;
    };

    /**
     * @brief Template class to register applications to make instances later.
     *
     * @tparam T
     */
    template <class T> class ApplicationProxy : public ApplicationProxyBase {
    public:
        /**
         * @brief Constructor.
         *
         * @param name The application name.
         */
        explicit ApplicationProxy(const std::string& name) noexcept : ApplicationProxyBase(name) {}

        /**
         * @brief Creates an instance of the proxied application.
         *
         * @return New application instance.
         */
        std::shared_ptr<Application> createInstance() noexcept override {
            return std::make_shared<T>();
        }
    };
}

#define REGISTER_APPLICATION(appname,appclass) \
gfx::_internal::ApplicationProxy<appclass> app_ ## appclass(appname) // NOLINT

#endif