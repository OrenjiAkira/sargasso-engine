#include "sargasso/front_end/modules/graphics.h"

#include "sargasso/common/log.h"
#include "sargasso/config.h"
#include "sargasso/front_end/utility/shader_loader.h"

#include <GL/glew.h>

using namespace SargassoEngine::FrontEnd::Modules;
using namespace SargassoEngine::FrontEnd::Utility;
using namespace SargassoEngine::Common;

Graphics::Graphics() : _camera() {
    log("Initializing window...");

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _width = 960;
    _height = 540;
    _camera.make_orthogonal(_width, _height, 0.01f, 1000);
    _camera.look_at(Vec3(0, 0, -10), Vec3(0, 0, 0));
    logf("Camera @ poisition: %", _camera.get_position().to_string());

    _window = glfwCreateWindow(_width, _height, SargassoEngine::ENGINE_NAME, NULL, NULL);
    log("Window created!");

    // Initialize window
    log("Setting GL context..");
    glfwMakeContextCurrent(_window);
    glfwFocusWindow(_window);

    log("Setting swap interval...");
    glfwSwapInterval(1);

    log("Initializing glew...");
    glewInit();

    log("Loading shaders...");
    try {
        _program_id = ShaderLoader::load_default_shaders();
    } catch (const std::string& exception) {
        logf_error("Failed to load shaders:\n\t%", exception);
    }

    logf("window size = (%, %)", _width, _height);

    glGenVertexArrays(1, &_vao_id);
    glBindVertexArray(_vao_id);
}

Graphics::~Graphics() {
    if (_window) {
        glfwDestroyWindow(_window);
    }
}

GLFWwindow* Graphics::get_window() const { return _window; }

int Graphics::get_width() const { return _width; }

int Graphics::get_height() const { return _height; }

bool Graphics::should_window_close() const { return glfwWindowShouldClose(_window); }

void Graphics::render_buffers() {
    // Called before rendering a frame
    glfwGetFramebufferSize(_window, &_width, &_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _set_shader_camera();

    for (const Buffer& buffer : _buffers) {
        buffer.render();
    }

    glfwSwapBuffers(_window);
}

void Graphics::register_buffer(const std::vector<Vec3>& points) {
    _buffers.push_back(Buffer(points));
}

void Graphics::set_camera(const Camera& camera) { _camera = camera; }

Camera Graphics::get_camera() const { return _camera; }

void Graphics::_set_shader_camera() {
    GLint transform_matrix_id = glGetUniformLocation(_program_id, "camera_transform");
    Mat4 transform = _camera.get_transform();
    glUniformMatrix4fv(transform_matrix_id, 1, GL_FALSE, reinterpret_cast<float*>(&transform));
    glUseProgram(_program_id);
}