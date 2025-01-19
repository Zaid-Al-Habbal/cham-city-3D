#include "Controller.h"
#include <stb_image.h>

bool IS_NIGHT = false, GROUND_FLOOR=false, FIRST_FLOOR=false, SECOND_FLOOR=false, camFly=false;
float prevX = 0.0f;

bool Controller::isGoingDownStairsFromRest(float x, float y, float z){
    return x < prevX && y>=-372.0f && z>=-1344.0f && z<=-772.0f;
}
bool Controller::isGoingUpStairsToRest(float x, float y, float z){
    return x > prevX && y<-130.0f &&  z>=-1344.0f && z<=-772.0f;
}


Controller::Controller(unsigned int width, unsigned int height):
    camera(glm::vec3(10186.6f, -371.344f, -12936.1f)),
    window(nullptr),
    deltaTime(0.0f),
    lastFrame(0.0f),
    lastX(width / 2.0f),
    lastY(height / 2.0f),
    firstMouse(true),
    SCR_WIDTH(width),
    SCR_HEIGHT(height),
    isNight(false),
    cnt0to1(0),
    cnt0to2(0),
    cnt2to1(0),
    cnt1to2(0),
    cnt1to0(0),
    cnt2to0(0),
    cntEleDoor(0),
    groundFloor(false),
    firstFloor(false),
    secondFloor(false),
    moved(false),
    cntMoved(0)
    
{}

Controller::~Controller() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void Controller::initializeOpenGLSettings(){
    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    // MSAA (Multiple sub-sample anti-analysing)
    glEnable(GL_MULTISAMPLE); // enabled by default on some drivers, but not all so always enable to make sure

    // enable blending:
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
    // Set the mouse button callback
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, keyCallback);


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(window, this);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    glEnable(GL_MULTISAMPLE); // Enable MSAA

    return true;
}

// Mouse button callback function
void Controller::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            IS_NIGHT^=1;
        }
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            camFly^=1;  
        }
    }

}

// Track key states
std::unordered_map<int, bool> keyState;
std::unordered_map<int, bool> keyProcessed;

// Key callback function
void Controller::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        keyState[key] = true;
    } else if (action == GLFW_RELEASE) {
        keyState[key] = false;
        keyProcessed[key] = false; // Reset the processed state on release
    }
}

void Controller::processInput() {

    moved = false;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        moved=true;
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        moved=true;
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        moved=true;
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        moved=true;
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if(moved){
        cntMoved++; if(cntMoved==31)cntMoved=0;
    }
    
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS && inElevator(camera.Position.x, camera.Position.z))
        GROUND_FLOOR = true;
    
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && inElevator(camera.Position.x, camera.Position.z))
        FIRST_FLOOR = true;

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && inElevator(camera.Position.x, camera.Position.z))
        SECOND_FLOOR = true;

    //CAR:
    if(keyState[GLFW_KEY_ENTER] && !keyProcessed[GLFW_KEY_ENTER]){
        camera.inDrivingMode^=1;
        keyProcessed[GLFW_KEY_ENTER] = true; // Mark the key as processed
    }


    if(camera.Position.x>2200 && camera.Position.x< 2700){
        if(isGoingDownStairsFromRest(camera.Position.x, camera.Position.y, camera.Position.z)){
            camera.Position.y-=20.0f;
        }
        else if(isGoingUpStairsToRest(camera.Position.x, camera.Position.y, camera.Position.z)){
            camera.Position.y+=20.0f;
        }
    }
    
    prevX = camera.Position.x;
    isNight = IS_NIGHT;
    groundFloor = GROUND_FLOOR;
    firstFloor = FIRST_FLOOR;
    secondFloor = SECOND_FLOOR;
    GROUND_FLOOR=FIRST_FLOOR=SECOND_FLOOR=false;
    thereIsMovement = cnt0to1 + cnt0to2 + cnt1to0 + cnt1to2 + cnt2to0 + cnt2to1;
    camera.fly = camFly;
}

bool Controller::inElevator(float x, float z){
    return x>=-9750.0f && x<-9402.0f && z>=3120.0f && z<=3860.0f;
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
