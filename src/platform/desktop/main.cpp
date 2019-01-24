#if (defined(__linux__) && !defined(__ANDROID__) && !defined(__UNITTEST__)) || (defined(__APPLE__) && !defined(__UNITTEST__)) || defined(__EMSCRIPTEN__)

#include "ananasgfx/platform/desktop/DesktopWindow.hpp"
#include "../../../include/ananasgfx/gfx/Application.hpp"
#include "../../../include/ananasgfx/gfx/ApplicationManager.hpp"

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

int main(int argc, char* argv[]) {
    try {
        // Get program arguments
        std::list<std::string> args;
        for (int i = 0; i < argc; i++) {
            args.emplace_back(argv[i]);
        }

        // Check for fullscreen
        bool fullscreen = std::find(args.begin(), args.end(), "--fullscreen") != args.end();

        // Check for hiding mouse cursor
        bool hideMouseCursor = std::find(args.begin(), args.end(), "--no-cursor") != args.end();

        // Check for user-space and resource-space
        std::string userSpace;
        const std::string userSpaceCmd = "--user-space=";
        std::string resourceSpace;
        const std::string resourceSpaceCmd = "--resource-space=";
        for (auto& arg : args) {
            // User space
            if (arg.find(userSpaceCmd) == 0) {
                userSpace = arg.substr(userSpaceCmd.length(), arg.length() - userSpaceCmd.length());
            }

            // Resource space
            if (arg.find(resourceSpaceCmd) == 0) {
                resourceSpace = arg.substr(resourceSpaceCmd.length(), arg.length() - resourceSpaceCmd.length());
            }
        }

        if (glfwInit() != GLFW_TRUE) {
            std::cerr << __PRETTY_FUNCTION__ << ": Unable to init GLFW" << std::endl;
            return EXIT_FAILURE;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//< Required for MacOS
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        gfx::_internal::ApplicationManager applicationManager;
#ifdef __EMSCRIPTEN__
        // Define a main loop function, that will be called as fast as possible
    pCurrentApplicationManager = &applicationManager;
    emscripten_set_main_loop(&mainLoop, 0, 1);
#else
        while (!applicationManager.isDone()) {
            applicationManager.tick();
        }
#endif

        return EXIT_SUCCESS;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

#endif