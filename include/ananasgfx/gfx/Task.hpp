#ifndef GFX_TASK_H
#define GFX_TASK_H

namespace gfx {

    class Application;

    class Task {
    public:
        virtual bool run(Application* application) noexcept = 0;
    };

}

#endif