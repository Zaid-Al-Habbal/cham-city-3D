#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <unordered_map>

#include "App.h"
#include "shader.h"
#include "TextureManager.h"

#if CHAM_ENABLE_AUDIO
#include <irrKlang.h>
using AudioEngine = irrklang::ISoundEngine;
#else
using AudioEngine = void;
#endif

using namespace std;

class ResourceManager : public App
{
public:

    unordered_map<string, Shader> shaders;
    unordered_map<string, TextureManager> textures;
    AudioEngine* engine;

    ResourceManager();
    void setShaders();
    void setTextures();
    void setAudio();
};

#endif
