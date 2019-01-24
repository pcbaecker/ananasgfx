#include <iostream>

#include <ananasgfx/gfx/ApplicationManager.hpp>
#include <ananasgfx/gfx/Application.hpp>

namespace gfx::_internal {

    ApplicationManager::ApplicationManager() noexcept :
    mApplications(ApplicationStore::getInstance().getApplications()) {
        this->mIterator = this->mApplications.cbegin();
    }

    void ApplicationManager::tick() noexcept {
        // If we have a current application running, we update it
        if (this->pCurrentApplication.use_count()) {
            this->pCurrentApplication->tick();
            return;
        }

        // There is currently no application running, check if we have some waiting
        if (this->mIterator != this->mApplications.cend()) {
            // Create a new application instance and increase the iterator
            auto app = (*this->mIterator++);
            std::cout << "Launching application: " << app.first << std::endl;
            this->pCurrentApplication = app.second->createInstance();

            // Initialize the application
            if (!this->pCurrentApplication->init()) {
                std::cerr << __PRETTY_FUNCTION__ << ": Unable to initialize application" << std::endl;
                this->pCurrentApplication.reset();
                return;
            }

            // Initialize the windows
            if (!this->pCurrentApplication->initWindows()) {
                std::cerr << __PRETTY_FUNCTION__ << ": Unable to initialize windows" << std::endl;
                this->pCurrentApplication.reset();
                return;
            }

            // To draw the first frame we call tick() again
            this->tick();
        }
    }

    bool ApplicationManager::isDone() const noexcept {
        return false;
    }

}