#include "App/ResourceManager.h"

ResourceManager::ResourceManager()
{
    setShaders();
    setTextures();
}

void ResourceManager::setShaders()
{
    //MAIN:
    shaders[MAIN] = Shader("../src/shaders/mainShader.vs", "../src/shaders/mainShader.fs");
    //SKYBOX:
    shaders[SKYBOX] = Shader("../src/shaders/skybox.vs", "../src/shaders/skybox.fs");

}

void ResourceManager::setTextures()
{   
    stbi_set_flip_vertically_on_load(true);
        
    //CONCRETE:
    textures[CONCRETE] = TextureManager("../resources/textures/concrete_wall_004_diff_1k.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[CONCRETE_SPEC] = TextureManager("../resources/textures/concrete_wall_004_spec_1k.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    
}