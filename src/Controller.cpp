#include "Controller.h"
#include <stb_image.h>

Controller::Controller(unsigned int width, unsigned int height):
    camera(glm::vec3(0.0f, 0.0f, 3.0f)),
    window(nullptr),
    deltaTime(0.0f),
    lastFrame(0.0f),
    lastX(width / 2.0f),
    lastY(height / 2.0f),
    firstMouse(true),
    SCR_WIDTH(width),
    SCR_HEIGHT(height),
    isNight(false)
{}

Controller::~Controller() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void Controller::initializeOpenGLSettings(){
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    // stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    // MSAA (Multiple sub-sample anti-analysing)
    glEnable(GL_MULTISAMPLE); // enabled by default on some drivers, but not all so always enable to make sure


    // enable blending:
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //enable face culling:
    glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT); 

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

bool Controller::initializeWindow(const std::string& title) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    glfwWindowHint(GLFW_SAMPLES, 4);  // Request 4x MSAA

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(window, this);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    return true;
}

void Controller::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        isNight = !isNight;
}

void Controller::updateDeltaTime() {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Controller::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Controller::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Controller* controller = static_cast<Controller*>(glfwGetWindowUserPointer(window));
    if (!controller) return;

    if (controller->firstMouse) {
        controller->lastX = static_cast<float>(xpos);
        controller->lastY = static_cast<float>(ypos);
        controller->firstMouse = false;
    }

    float xoffset = static_cast<float>(xpos) - controller->lastX;
    float yoffset = controller->lastY - static_cast<float>(ypos); // Reversed since y-coordinates go from bottom to top

    controller->lastX = static_cast<float>(xpos);
    controller->lastY = static_cast<float>(ypos);

    controller->camera.ProcessMouseMovement(xoffset, yoffset);
}

void Controller::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Controller* controller = static_cast<Controller*>(glfwGetWindowUserPointer(window));
    if (!controller) return;

    controller->camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
