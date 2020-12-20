
#include "sargasso/front_end/modules/events.h"

#include "sargasso/common/log.h"
#include "sargasso/engine.h"

#include <GLFW/glfw3.h>

using SargassoEngine::FrontEnd::Modules::Events;
using namespace SargassoEngine::Common;

Events::Events() { glfwSetErrorCallback(Events::Callbacks::error_callback); }

Events::~Events() {}

void Events::register_window(GLFWwindow* window) {
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetKeyCallback(window, Events::Callbacks::key_action_callback);
}

void Events::deregister_window(GLFWwindow* window) { glfwSetKeyCallback(window, NULL); }

void Events::Callbacks::error_callback(int error, const char* description) {
    logf_error("Error: %", description);
}

void Events::Callbacks::key_action_callback(GLFWwindow* window, int key, int scancode, int action,
                                            int mods) {
    if (window == nullptr) {
        return;
    }

    void* user_pointer = glfwGetWindowUserPointer(window);
    if (user_pointer == nullptr) {
        Common::log("No user pointer registered, nothing to do with keyevent.");
        return;
    }

    Game* game = static_cast<Game*>(glfwGetWindowUserPointer(window));

    if (action == GLFW_PRESS) {
        game->key_pressed(key);
    }

    if (action == GLFW_RELEASE) {
        game->key_released(key);
    }
}