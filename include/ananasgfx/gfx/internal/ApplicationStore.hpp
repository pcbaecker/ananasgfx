#ifndef GFX_INTERNAL_APPLICATIONSTORE_H
#define GFX_INTERNAL_APPLICATIONSTORE_H

#include "../Application.hpp"

namespace gfx::_internal {

    /**
     * @brief Base proxy interface.
     */
    class ApplicationProxyBase {
    public:
        explicit ApplicationProxyBase(const std::string& name) noexcept;
        virtual std::shared_ptr<Application> createInstance() noexcept = 0;
    };

    /**
     * @brief The application store, where all applications are registered.
     */
    class ApplicationStore {
    public:
        static ApplicationStore& getInstance() noexcept;

        void registerApplicationProxy(const std::string& name, ApplicationProxyBase *pApplication) noexcept;
        size_t getNumberOfApplications() const noexcept;
        const std::map<std::string,ApplicationProxyBase*> getApplications() const noexcept;

    private:
        ApplicationStore() noexcept;

    private:
        std::map<std::string,ApplicationProxyBase*> mApplications;
    };

    /**
     * @brief Template class to register applications to make instances later.
     *
     * @tparam T
     */
    template <class T> class ApplicationProxy : public ApplicationProxyBase {
    public:
        explicit ApplicationProxy(const std::string& name) noexcept : ApplicationProxyBase(name) {

        }

        std::shared_ptr<Application> createInstance() noexcept override {
            return std::make_shared<T>();
        }

    };

}

#define REGISTER_APPLICATION(appname,appclass) \
gfx::_internal::ApplicationProxy<appclass> app_ ## appclass(appname) // NOLINT

#endif