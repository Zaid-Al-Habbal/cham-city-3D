#ifndef RENDERER_H
#define RENDERER_H

#include "ResourceManager.h"
#include "Scene.h"

#include "Skybox.h"
#include "Light.h"
#include "Controller.h"

#define showMe(x) std::cout << #x << " is " << x  << endl;


class Renderer : public Scene
{
private:
    Skybox skybox;     // skybox.setEnvironment(false); // evening
    Light refLight, mainLight;
    unordered_map<string, TextureManager> textures;
    unordered_map<string, Shader> shaders;
    ISoundEngine* engine;
    ISound* carSound;

    int cntMallDoor, cntEsc, cntGoingUpUsingESC, cntGoingDownUsingESC;
    unsigned int mallCubemapTexture;


    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;


public:
    Renderer();
    void render(Controller& controller);
    void draw(string ObjectName, int numOfVertices, int offset);
    void draw3Dmodel(string name, int startIndex=0, int endIndex=1e9);
    bool nearMallDoor(float x, float y, float z);
    unsigned int loadMallCubemap();
    void eleUp(Camera& camera);
    void eleDown(Camera& camera);
    void closeEleDoor();
    void openEleDoor();
    void turnEscOn();
    void turnEsc2On();
    void escUp(Camera& camera);
    void escDown(Camera& camera);
    void handleElevator(Controller& controller, float camY);
    void moveTheCar(Camera& camera);

};
#endif
