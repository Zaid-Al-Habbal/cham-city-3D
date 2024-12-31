#include "App/ResourceManager.h"

ResourceManager::ResourceManager()
{
    setShaders();
    setTextures();
    setAudio();
}

void ResourceManager::setAudio()
{
    //ENGINE:
    engine = createIrrKlangDevice();
    engine->setDefault3DSoundMinDistance(115.0f);
    


    ISound* music =engine->play3D("../resources/audio/mall.wav", vec3df(-4500.0f, -492.199f, 4037.31f),
                              true, false, true);
    
    music->setMinDistance(2000.0f);

    music =engine->play3D("../resources/audio/Rival_-Alan-Walker-Dreamer-_Rival-Remix_-_NCS-Release_.ogg", vec3df(907.83f, 249.006f, -3625.85f),
                              true, false, true);
    
    music =engine->play3D("../resources/audio/TOKYO-MACHINE_-NEFFEX-Desperate-_NCS-Release_.ogg", vec3df(1211.15f, 292.262f, 11136.2f),
                              true, false, true);
    
    music =engine->play3D("../resources/audio/Diamond-Eyes-Doxx-My-Heart-_NCS-Release_.ogg", vec3df(-5154.78f, 270.735f, 11111.4f),
                              true, false, true);
        
}

void ResourceManager::setShaders()
{
    //REF:
    shaders[REF] = Shader("../src/shaders/reflectionShader.vs", "../src/shaders/reflectionShader.fs");
    //MAIN:
    shaders[MAIN] = Shader("../src/shaders/mainShader.vs", "../src/shaders/mainShader.fs");
    //SKYBOX:
    shaders[SKYBOX] = Shader("../src/shaders/skybox.vs", "../src/shaders/skybox.fs");

}

void ResourceManager::setTextures()
{   
    stbi_set_flip_vertically_on_load(true);
        
    //BLUE_WINDOW:
    textures[BLUE_WINDOW] = TextureManager("../resources/textures/blue-window.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    
    //Light_METAL:
    textures[LIGHT_METAL] = TextureManager("../resources/textures/Metal009_1K-diff.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[LIGHT_METAL_SPEC] = TextureManager("../resources/textures/Metal009_1K-spec.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    //GRAY_BRICK:
    textures[GRAY_BRICK] = TextureManager("../resources/textures/Bricks065_1K-diff.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[GRAY_BRICK_SPEC] = TextureManager("../resources/textures/Bricks065_1K-spec.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    //WHITE_WINDOW:
    textures[WHITE_WINDOW] = TextureManager("../resources/textures/window3.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[WHITE_WINDOW_SPEC] = TextureManager("../resources/textures/square_glass_spec.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    //BLOOR:
    textures[BLOOR] = TextureManager("../resources/textures/square_glass_diff.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[BLOOR_SPEC] = TextureManager("../resources/textures/square_glass_spec.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    //BLACK_TILE:
    textures[BLACK_TILE] = TextureManager("../resources/textures/Tiles108_1K-diff.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[BLACK_TILE_SPEC] = TextureManager("../resources/textures/Tiles108_1K-spec.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    //BLOOR:
    textures[GRAY_TILES] = TextureManager("../resources/textures/PavingStones127_1K-diff.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[GRAY_TILES_SPEC] = TextureManager("../resources/textures/PavingStones127_1K-spec.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    //WHITE_TILES:
    textures[WHITE_TILES] = TextureManager("../resources/textures/Tiles107_1K-diff.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[WHITE_TILES_SPEC] = TextureManager("../resources/textures/Tiles107_1K-spec.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);

    //WOOD1:
    textures[WOOD1] = TextureManager("../resources/textures/wood_floor_diff.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[WOOD1_SPEC] = TextureManager("../resources/textures/wood_floor_spec.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    
    //WHITE:
    textures[WHITE] = TextureManager("../resources/textures/Metal009_1K-spec.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[SUITE1_TEX] = TextureManager("../resources/textures/suite4.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[SUITE2_TEX] = TextureManager("../resources/textures/suite5.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    
    //BLACK:
    textures[BLACK] = TextureManager("../resources/textures/Black.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    
    //SUITE_REF:
    textures[SUITE_REF] = TextureManager("../resources/textures/suite_shop_ref.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    
    //BLUE_PLASTIC:
    textures[BLUE_PLASTIC] = TextureManager("../resources/textures/Plastic015A_1K-diff.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[BLUE_PLASTIC_SPEC] = TextureManager("../resources/textures/Plastic015A_1K-spec.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    //SHIRT1_TEX:
    textures[SHIRT1_TEX] = TextureManager("../resources/textures/shirt1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[SHIRT2_TEX] = TextureManager("../resources/textures/shirt2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    //SHIRT_REF:
    textures[SHIRT_REF] = TextureManager("../resources/textures/shirt_shop_ref.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    //SPORTY:
    textures[SPORTY] = TextureManager("../resources/textures/Fabric070_1K-diff.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[SPORTY_SPEC] = TextureManager("../resources/textures/Fabric070_1K-spec.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    //SHOE1_TEX:
    textures[SHOE1_TEX] = TextureManager("../resources/textures/boot1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[SHOE2_TEX] = TextureManager("../resources/textures/boot2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[SHOE3_TEX] = TextureManager("../resources/textures/boot3.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

}