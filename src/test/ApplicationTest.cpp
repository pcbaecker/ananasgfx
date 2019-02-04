#include <ananasgfx/test/ApplicationTest.hpp>
#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/test/PHash.hpp>

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

    void ApplicationTest::Compare(const std::string &nodepath, const std::string &filepath) {
        this->mApplication->addTask(std::make_shared<test::Compare>(nodepath, filepath));
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

    Compare::Compare(const std::string &nodepath, const std::string &filepath) noexcept : mNodepath(nodepath), mFilepath(filepath) {

    }

    bool Compare::run(gfx::Application* application) noexcept {
        // Load the template file
        auto templateFile = gfx::Bitmap::read(this->mFilepath);
        if (!templateFile.has_value()) {
            std::cerr << "Templatefile not found" << std::endl;
            return false;
        }

        // Load the scene
        auto window = *application->getWindows().begin();
        std::cout << window->getWidth() << "x" << window->getHeight() << std::endl;
        auto scene = window->getScene();
        if (!scene.has_value()) {
            std::cerr << "Scene not found" << std::endl;
            return false;
        }

        // Load the bitmap
        auto rt = (*scene)->asRenderTexture();
        auto bitmap = rt->toBitmap();
        if (!bitmap.has_value()) {
            std::cerr << "Rendertexture to bitmap failed" << std::endl;
            return false;
        }

        (*bitmap)->saveAsFile("file.png");
        (*templateFile)->saveAsFile("file2.png");

        auto tf = test::PHash::hash(*templateFile->get());
        auto node = test::PHash::hash(*bitmap->get());
        std::cout << "Distance = " << (int)test::PHash::distance(tf, node) << std::endl;

        return false;
    }
}