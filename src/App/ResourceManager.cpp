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
    engine->setDefault3DSoundMinDistance(100.0f);
    
    ISound* music =engine->play3D("../resources/audio/mall.wav", vec3df(-4500.0f, -492.199f, 4037.31f),
                              true, false, true);
    
    music->setMinDistance(1500.0f);

    engine->play3D("../resources/audio/Rival_-Alan-Walker-Dreamer-_Rival-Remix_-_NCS-Release_.ogg", vec3df(907.83f, 249.006f, -3625.85f),
                              true, false, true);
    
    engine->play3D("../resources/audio/TOKYO-MACHINE_-NEFFEX-Desperate-_NCS-Release_.ogg", vec3df(1211.15f, 292.262f, 11136.2f),
                              true, false, true);
    
    engine->play3D("../resources/audio/Diamond-Eyes-Doxx-My-Heart-_NCS-Release_.ogg", vec3df(-5154.78f, 270.735f, 11111.4f),
                              true, false, true);

    engine->play3D("../resources/audio/ROSÉ-_-Bruno-Mars-APT.-_ROCK-VERSION_.ogg", vec3df(-10625.5f, 161.943f, 10954.1f),
                              true, false, true);
    
    engine->play3D("../resources/audio/HEAT-WAVES-Glass-Animals-FREE-DOWNLOAD-No-Copyright.ogg", vec3df(4022.05f, -128.344f, -1173.46f),
                              true, false, true);
    engine->play3D("../resources/audio/Diviners_-Tobu-Geometry-_NCS-Release_.ogg", vec3df(4550.74f, 18.6667f, 3748.58f ),
                              true, false, true);
    
    
    engine->play3D("../resources/audio/Linn-Sandin_-Midranger_-Poylow-Revolution-_NCS-Release_.ogg", vec3df(-14159.0f, -0.171659f, 2380.01f),
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
    textures[BLACK1] = TextureManager("../resources/textures/Black.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
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


    //PINK:
    textures[PINK] = TextureManager("../resources/textures/Tiles005_1K-diff.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[PINK_SPEC] = TextureManager("../resources/textures/Tiles005_1K-spec.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    //DRESS:
    textures[DRESS1_TEX] = TextureManager("../resources/textures/dress1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[DRESS2_TEX] = TextureManager("../resources/textures/dress2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[DRESS3_TEX] = TextureManager("../resources/textures/dress3.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[DRESS4_TEX] = TextureManager("../resources/textures/dress4.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    //DRESS_REF:
    textures[DRESS_REF] = TextureManager("../resources/textures/dress_ref.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    //TRAV:
    textures[TRAV] = TextureManager("../resources/textures/Travertine003_1K-diff.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[TRAV_SPEC] = TextureManager("../resources/textures/Travertine003_1K-spec.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    //RED_PLASTIC:
    textures[RED_PLASTIC] = TextureManager("../resources/textures/ChristmasTreeOrnament008_1K-diff.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[RED_PLASTIC_SPEC] = TextureManager("../resources/textures/ChristmasTreeOrnament008_1K-spec.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    //RED_TILES:
    textures[RED_TILES] = TextureManager("../resources/textures/Tiles047_1K-diff.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[RED_TILES_SPEC] = TextureManager("../resources/textures/Tiles047_1K-spec.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    //RED_FABRIC1:
    textures[RED_FABRIC1] = TextureManager("../resources/textures/Fabric055_1K-diff.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[RED_FABRIC1_SPEC] = TextureManager("../resources/textures/Fabric055_1K-spec.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    //RED_FABRIC2:
    textures[RED_FABRIC2] = TextureManager("../resources/textures/Fabric054_1K-diff.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[RED_FABRIC2_SPEC] = TextureManager("../resources/textures/Fabric054_1K-spec.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    //BEIGE:
    textures[BEIGE] = TextureManager("../resources/textures/Travertine003_1K-diff.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[BEIGE_SPEC] = TextureManager("../resources/textures/Travertine003_1K-spec.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);

    //GREEN_TILES:
    textures[GREEN_TILES] = TextureManager("../resources/textures/Tiles003_1K-diff.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[GREEN_TILES_SPEC] = TextureManager("../resources/textures/Tiles003_1K-spec.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    
    //JUST_WHITE:
    textures[JUST_WHITE] = TextureManager("../resources/textures/just_white.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[JUST_WHITE_SPEC] = TextureManager("../resources/textures/just_white.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    //GRAY_METAL:
    textures[GRAY_METAL] = TextureManager("../resources/textures/Metal036_1K-JPG_Color.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[GRAY_METAL_SPEC] = TextureManager("../resources/textures/Metal036_1K-JPG_Metalness.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    //WHITE2:
    textures[WHITE2_DIFF] = TextureManager("../resources/textures/Porcelain001_1K-JPG_Color.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    


    //TEXTURES DO NOT FLIP::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    stbi_set_flip_vertically_on_load(false);

    //SYRIA:
    textures[SYRIA_DIFF] = TextureManager("../resources/textures/syria.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    //TV:
    textures[TV_DIFF] = TextureManager("../resources/textures/screenY.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    //MICRO:
    textures[MICRO_DIFF] = TextureManager("../resources/textures/micro1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    //OVEN:
    textures[OVEN_DIFF] = TextureManager("../resources/textures/oven.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    //WASHINGs:
    textures[WASHING1_DIFF] = TextureManager("../resources/textures/wash2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[WASHING2_DIFF] = TextureManager("../resources/textures/wash1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    
    //FRIDGEs:
    textures[FRIDGE1_DIFF] = TextureManager("../resources/textures/fridge2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    textures[FRIDGE2_DIFF] = TextureManager("../resources/textures/fridge1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    

    //SOFA1:
    textures[SOFA1_DIFF] = TextureManager("../resources/objects/sofa1/textures/diff.jpeg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    
    //BED:
    textures[BED_DIFF] = TextureManager("../resources/objects/GothicBed_01_1k.fbx/textures/GothicBed_01_diff_1k.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[BED_SPEC] = TextureManager("../resources/objects/GothicBed_01_1k.fbx/textures/GothicBed_01_roughness_1k.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    //SOFA2:
    textures[SOFA2_DIFF] = TextureManager("../resources/objects/sofa2/textures/diffuse.jpeg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    
    //TABLE2:
    textures[TABLE2_DIFF] = TextureManager("../resources/objects/table/textures/Table_BC.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[TABLE2_SPEC] = TextureManager("../resources/objects/table/textures/Table_AO.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);
    
    //TABLE3:
    textures[TABLE3_DIFF] = TextureManager("../resources/objects/antique-table/textures/defaultMat_Base_Color.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[TABLE3_SPEC] = TextureManager("../resources/objects/antique-table/textures/defaultMat_Metallic.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);

    //TABLE4
    textures[TABLE4_DIFF] = TextureManager("../resources/objects/ClassicConsole_01_1k.gltf/textures/ClassicConsole_01_diff_1k.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    
    //CABINET1
    textures[CABINET1_DIFF] = TextureManager("../resources/objects/Cabinet_Bookcase/20359_Cabinet_Bookcase.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    
    //COUCH2:
    textures[COUCH2_DIFF] = TextureManager("../resources/objects/couch2/diffuse.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[COUCH2_SPEC] = TextureManager("../resources/objects/couch2/specular.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);

    //SOFA:
    textures[SOFA_DIFF] = TextureManager("../resources/objects/sofa/textures/diffuse.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[SOFA_SPEC] = TextureManager("../resources/objects/sofa/textures/specular.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);

    //TABLE5:
    textures[TABLE5_DIFF] = TextureManager("../resources/objects/table2/Side_Table_COLOR.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    textures[TABLE5_SPEC] = TextureManager("../resources/objects/table2/Side_Table_SPECULAR.jpg", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGB, GL_UNSIGNED_BYTE);

    //STOVE:
    textures[STOVE_DIFF] = TextureManager("../resources/objects/electric_stove_1k.fbx/textures/electric_stove_diff_1k.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);


}