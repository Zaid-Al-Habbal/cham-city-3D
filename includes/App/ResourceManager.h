#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <map>

#include "App.h"
#include "shader.h"
#include "TextureManager.h"

using namespace std;

class ResourceManager : public App
{
public:

    map<string, Shader> shaders;
    map<string, TextureManager> textures;

    ResourceManager();
    void setShaders();
    void setTextures();
};

#endif
