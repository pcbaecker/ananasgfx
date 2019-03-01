#ifndef GFX_TASK_H
#define GFX_TASK_H

namespace gfx {

    class Application;

    /**
     * @brief The basic task interface.
     */
    class Task {
    public:
        /**
         * @brief Will be called if the task begins to run.
         *
         * @param application Pointer to the connected application.
         * @return True if the task should be executed again or False if the task is done.
         */
        virtual bool run(Application* application) noexcept = 0;
    };

}

#endif