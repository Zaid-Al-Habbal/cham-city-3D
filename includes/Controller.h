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
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

public:
    Camera camera;
    //morning/night
    bool isNight, groundFloor, firstFloor, secondFloor;
    int cnt0to1, cnt0to2, cnt1to0, cnt1to2, cnt2to1, cnt2to0, cntEleDoor, thereIsMovement;

    static bool isGoingUpStairsToRest(float x, float y, float z);
    static bool isGoingDownStairsFromRest(float x, float y, float z);
    static bool inElevator(float x, float z);

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
