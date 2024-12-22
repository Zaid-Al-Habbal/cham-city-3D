#ifndef RENDERER_H
#define RENDERER_H

#include "ResourceManager.h"
#include "Scene.h"

#include "Skybox.h"
#include "Light.h"
#include "Controller.h"

class Renderer : public Scene
{
private:
    Skybox skybox;     // skybox.setEnvironment(false); // evening
    Light light;
    map<string, TextureManager> textures;
    map<string, Shader> shaders;

    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;


public:
    Renderer();
    void render(Controller& controller);
    void draw(string ObjectName, int numOfVertices);
    void draw3Dmodel(string modelName);

};
#endif
