#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "camera.h"

class Controller {
private:

    // Camera and window management
    Camera camera;
    GLFWwindow* window;

    // Timing
    float deltaTime;
    float lastFrame;


    // Mouse tracking
    float lastX, lastY;
    bool firstMouse;

    // Settings
    const unsigned int SCR_WIDTH;
    const unsigned int SCR_HEIGHT;

    // Private utility functions
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

public:
    //morning/night
    bool isNight;

    // Constructor
    Controller(unsigned int width = 800, unsigned int height = 600);

    // Destructor
    ~Controller();

    // Window initialization
    bool initializeWindow(const std::string& title);

    //Get Camera
    Camera& getCamera() { return camera; }

    // Input handling
    void processInput();

    // Main loop management
    GLFWwindow* getWindow() const { return window; }
    bool shouldClose() const { return glfwWindowShouldClose(window); }

    // Timing utilities
    void updateDeltaTime();
    void initializeOpenGLSettings();
};

#endif
