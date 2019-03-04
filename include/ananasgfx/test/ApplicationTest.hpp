#ifndef TEST_APPLICATIONTEST_H
#define TEST_APPLICATIONTEST_H

#include "TestTasks.hpp"
#include "internal/ApplicationTestStore.hpp"

namespace test {

    /**
     * @brief Executes an Application test.
     */
    class ApplicationTest {
    public:
        /**
         * @brief Destructor.
         */
        virtual ~ApplicationTest() noexcept;

        /**
         * @brief The main entry point for the test.
         *
         * Defines what will happen during the test.
         */
        virtual void run() = 0;

        /**
         * @brief Sets the application that will be tested with this class.
         *
         * @param name The name of the application.
         * @param application Pointer to the application.
         */
        void setApplication(std::string name, std::shared_ptr<gfx::Application> application) noexcept;

    protected:
        /**
         * @brief Performs an if.
         *
         * @param condition The condition part.
         * @param thenDo The then do part.
         * @param elseDo The else do part.
         */
        void If(std::function<bool(gfx::Application *)> condition,
                std::function<void(gfx::Application *)> thenDo,
                std::function<void(gfx::Application *)> elseDo = nullptr);

        /**
         * @brief Compares the given nodepath with a previously saved file.
         *
         * @throws ee::Exception
         * @param nodepath The nodepath of the node we want to compare.
         * @param filepath The path of the imagefile we want to compare.
         */
        void Compare(const std::string& nodepath, const std::string& filepath);

        /**
         * @brief Runs The given task in the render thread.
         *
         * @throws ee::Exception
         * @param task The task we want to execute.
         */
        void Run(std::function<void(gfx::Application *)> task);

        /**
         * @brief Executes a control task on a specific node.
         *
         * @tparam T The class of the node.
         * @param nodepath The nodepath.
         * @param task The task we want to execute.
         */
        template<class T> void Control(
                const std::string &nodepath,
                std::function<void(gfx::Application *, T *)> task) noexcept {
            this->mApplication->addTask(std::make_shared<test::Control<T>>(nodepath, task));
        }
    private:
        /**
         * @brief The application name.
         */
        std::string mName;

        /**
         * @brief The number of failures.
         */
        size_t mFailures = 0;

        /**
         * @brief The number number of successes.
         */
        size_t mSuccesses = 0;

        /**
         * @brief The application pointer.
         */
        std::shared_ptr<gfx::Application> mApplication;
    };
}

#define REGISTER_APPLICATIONTEST(appname,appclass) \
test::_internal::ApplicationTestProxy<appclass> app_ ## appclass(appname) // NOLINT

#endif