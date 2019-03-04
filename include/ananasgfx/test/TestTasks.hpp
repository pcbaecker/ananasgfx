#ifndef TEST_TESTTASKS_H
#define TEST_TESTTASKS_H

#include <functional>
#include <future>

#include <ananasgfx/gfx/Node.hpp>
#include <ananasgfx/gfx/Task.hpp>
#include <ananasgfx/gfx/Application.hpp>

namespace test {

    /**
     * @brief Runs an conditional task that will execute a different callback depending on the condition.
     */
    class IfTask : public gfx::Task {
    public:
        /**
         * @brief Constructor.
         *
         * @param condition The condition.
         * @param thenDo The then do.
         * @param elseDo The else do.
         * @param promise The result promise.
         */
        explicit IfTask(
                std::function<bool(gfx::Application *)> condition,
                std::function<void(gfx::Application *)> thenDo,
                std::function<void(gfx::Application *)> elseDo,
                std::promise<bool> promise) noexcept;

        /**
         * @brief Executes the task.
         *
         * @param application Pointer to the application that will execute this task.
         * @return True if we want to retain the task.
         */
        bool run(gfx::Application* application) noexcept override;

    private:
        /**
         * @brief The condition.
         */
        std::function<bool(gfx::Application *)> mCondition;

        /**
         * @brief The then to.
         */
        std::function<void(gfx::Application *)> mThenDo;

        /**
         * @brief The else do.
         */
        std::function<void(gfx::Application *)> mElseDo;

        /**
         * @brief The promise.
         */
        std::promise<bool> mPromise;
    };

    /**
     * @brief Compares a node with an imagefile.
     */
    class Compare : public gfx::Task {
    public:
        /**
         * @brief Constructor.
         *
         * @param nodepath The path of the node we want to compare.
         * @param filepath The path of the file we want to compare.
         * @param promise The promise that will get the result of this execution.
         */
        Compare(const std::string& nodepath, const std::string& filepath, std::promise<bool> promise) noexcept;

        /**
         * @brief Executes this task.
         *
         * @param application The application that executes this task.
         */
        bool run(gfx::Application* application) noexcept override;

    private:
        /**
         * @brief Offer the user a creation / recreation of the imagefile.
         *
         * @param application The application that executes this task.
         * @return True on success.
         */
        bool offerRecreation(gfx::Application* application) noexcept;

    private:
        /**
         * @brief The node path.
         */
        std::string mNodepath;

        /**
         * @brief The file path.
         */
        std::string mFilepath;

        /**
         * @brief The promise.
         */
        std::promise<bool> mPromise;
    };

    /**
     * @brief A basic test task.
     */
    class Task : public gfx::Task {
    public:
        /**
         * @brief Constructor.
         *
         * @param task The function we want to execute.
         */
        Task(std::function<void(gfx::Application *)> task) noexcept;

        /**
         * @brief Executes this task.
         *
         * @param application The application that executes this test.
         * @return True if we want to retain this task.
         */
        bool run(gfx::Application* application) noexcept override;

    private:
        /**
         * @brief The task we want to execute.
         */
        std::function<void(gfx::Application *)> mTask;
    };

    /**
     * @brief Controls a node.
     *
     * @tparam T The class of the node we want to control.
     */
    template<class T> class Control : public gfx::Task {
    public:
        /**
         * @brief Constructor.
         *
         * @param nodepath The path of the node we want to control.
         * @param task The task we want to execute on the node.
         */
        Control(std::string nodepath, std::function<void(gfx::Application*, T*)> task) noexcept : mNodepath(std::move(nodepath)), mTask(task) {}

        /**
         * @brief Executes this task.
         *
         * @param application The application that executes this task.
         * @return True if we want to retain this task.
         */
        bool run(gfx::Application* application) noexcept override {
            // Try to get the node
            auto nodeOptional = application->getNode(this->mNodepath);
            if (!nodeOptional.has_value()) {
                std::cerr << "NODE = " << this->mNodepath << " NOT FOUND" << std::endl;
                return false;
            }

            // Try to convert the node to the requested type
            auto node = dynamic_cast<T*>(*nodeOptional);
            if (node == nullptr) {
                std::cerr << "NODE = " << this->mNodepath << " INVALID TYPE" << std::endl;
                return false;
            }

            // Execute the task
            if (this->mTask) {
                this->mTask(application, node);
            }

            // We never want to retain this task
            return false;
        }

    private:
        /**
         * @brief The node path.
         */
        std::string mNodepath;

        /**
         * @brief The task.
         */
        std::function<void(gfx::Application*, T*)> mTask;
    };
}

#endif