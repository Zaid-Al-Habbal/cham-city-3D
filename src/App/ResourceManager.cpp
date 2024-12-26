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
    
    //BLUE_WINDOW:
    textures[BLUE_WINDOW] = TextureManager("../resources/textures/blue-window.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[BLUE_WINDOW_SPEC] = TextureManager("../resources/textures/blue-window.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    //Light_METAL:
    textures[LIGHT_METAL] = TextureManager("../resources/textures/Metal009_1K-diff.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[LIGHT_METAL_SPEC] = TextureManager("../resources/textures/Metal009_1K-spec.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    //GRAY_BRICK:
    textures[GRAY_BRICK] = TextureManager("../resources/textures/Bricks065_1K-diff.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[GRAY_BRICK_SPEC] = TextureManager("../resources/textures/Bricks065_1K-spec.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    //WHITE_WINDOW:
    textures[WHITE_WINDOW] = TextureManager("../resources/textures/window3.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[WHITE_WINDOW_SPEC] = TextureManager("../resources/textures/square_glass_spec.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    //BLOOR:
    textures[BLOOR] = TextureManager("../resources/textures/square_glass_diff.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[BLOOR_SPEC] = TextureManager("../resources/textures/square_glass_spec.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    //BLACK_TILE:
    textures[BLACK_TILE] = TextureManager("../resources/textures/Tiles108_1K-diff.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[BLACK_TILE_SPEC] = TextureManager("../resources/textures/Tiles108_1K-spec.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
}