#ifndef TEST_TESTTASKS_H
#define TEST_TESTTASKS_H

#include <functional>

#include <ananasgfx/gfx/Node.hpp>
#include <ananasgfx/gfx/Task.hpp>
#include <ananasgfx/gfx/Application.hpp>

namespace test {

    class IfTask : public gfx::Task {
    public:
        explicit IfTask(
                std::function<bool(gfx::Application *)> condition,
                std::function<void(gfx::Application *)> thenDo,
                std::function<void(gfx::Application *)> elseDo) noexcept;

        bool run(gfx::Application* application) noexcept override;

    private:
        std::function<bool(gfx::Application *)> mCondition;
        std::function<void(gfx::Application *)> mThenDo;
        std::function<void(gfx::Application *)> mElseDo;
    };

    class Compare : public gfx::Task {
    public:
        Compare(const std::string& nodepath, const std::string& filepath) noexcept;

        bool run(gfx::Application* application) noexcept override;

    private:
        bool offerRecreation(gfx::Application* application) noexcept;

    private:
        std::string mNodepath;
        std::string mFilepath;
    };

    class Task : public gfx::Task {
    public:
        Task(std::function<void(gfx::Application *)> task) noexcept;

        bool run(gfx::Application* application) noexcept override;

    private:
        std::function<void(gfx::Application *)> mTask;
    };

    template<class T> class Control : public gfx::Task {
    public:
        Control(std::string nodepath, std::function<void(gfx::Application*, T*)> task) noexcept : mNodepath(std::move(nodepath)), mTask(task) {}

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
        std::string mNodepath;
        std::function<void(gfx::Application*, T*)> mTask;
    };

}

#endif