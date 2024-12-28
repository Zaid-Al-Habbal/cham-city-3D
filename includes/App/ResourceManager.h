#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <map>

#include "App.h"
#include "shader.h"
#include "TextureManager.h"
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

using namespace irrklang;

using namespace std;

class ResourceManager : public App
{
public:

    map<string, Shader> shaders;
    map<string, TextureManager> textures;
    ISoundEngine* engine;

    ResourceManager();
    void setShaders();
    void setTextures();
    void setAudio();
};

#endif
