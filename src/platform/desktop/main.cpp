#if (defined(__linux__) && !defined(__ANDROID__) && !defined(__UNITTEST__)) || (defined(__APPLE__) && !defined(__UNITTEST__)) || defined(__EMSCRIPTEN__)

#include <ananasgfx/platform/desktop/DesktopWindow.hpp>
#include <ananasgfx/platform/desktop/CommandLineParameters.hpp>
#include <ananasgfx/gfx/Application.hpp>
#include <ananasgfx/gfx/internal/ApplicationManager.hpp>

#include <ee/Log.hpp>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <list>
#include <map>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
static gfx::_internal::ApplicationManager* pCurrentApplicationManager = nullptr;
void mainLoop() {
    pCurrentApplicationManager->tick();
}
#endif

int main(int argc, const char* argv[]) {
    try {
        platform::desktop::CommandLineParameters clp(argc, argv);
        auto logLevel = clp.getString("logging", "info");
        if (logLevel != "none") {
            ee::Log::applyDefaultConfiguration();
            if (logLevel == "trace") {
                ee::Log::registerOutstream(ee::LogLevel::Trace, std::cout);
            }
        }

        // Initialize GLFW
        if (glfwInit() != GLFW_TRUE) {
            std::cerr << __PRETTY_FUNCTION__ << ": Unable to init GLFW" << std::endl;
            return EXIT_FAILURE;
        }

        // Provide GLFW some hints how we want our OpenGL
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//< Required for MacOS
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create the ApplicationManager
        gfx::_internal::ApplicationManager applicationManager(
                clp.getBool("devmode", false),
                {},
                clp.getLong("app-lifetime", 0),
                clp.getString("resource-space", "resource/"),
                clp.getString("user-space", "user/"),
                clp.getBool("fullscreen", false),
                clp.getBool("hide-cursor", true)
                );
#ifdef __EMSCRIPTEN__
        // Define a main loop function, that will be called as fast as possible
    pCurrentApplicationManager = &applicationManager;
    emscripten_set_main_loop(&mainLoop, 0, 1);
#else
        while (!applicationManager.isDone()) {
            applicationManager.tick();
        }
#endif

        return gfx::_internal::ApplicationManager::ReturnCode;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

#endif