#include "App/Renderer.h"
#include "Light.h"

using namespace glm;

Renderer::Renderer()
{
    ResourceManager resourceManager;
    
    engine = resourceManager.engine;
    //texture:
    textures = resourceManager.textures;
    //shaders:
    shaders = resourceManager.shaders;

    //MAIN SHADER Light
    mainLight = Light(shaders[MAIN], false, 1, false);
    //REF SHADER Light:
    refLight = Light(shaders[REF], true, 0, false);

    //for Mall Door:
    cntMallDoor=90;

}


void Renderer::render(Controller& controller)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
    
    //camera
    Camera camera = controller.getCamera();
    vec3 camFro = camera.Front;
    vec3 camPos = camera.Position;
    vec3 camUp = camera.WorldUp;
    float camX=camPos.x, camY=camPos.y, camZ=camPos.z;
    engine->setListenerPosition(vec3df(camPos.x, camPos.y, camPos.z),
     vec3df(camFro.x, camFro.y, camFro.z), vec3df(0,0,0),
      vec3df(camUp.x, camUp.y, camUp.z));       
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
     (float)SCR_WIDTH / (float)SCR_HEIGHT, 2.0f, 30000.0f);
    glm::mat4 view = camera.GetViewMatrix();
    

    //REEEEEEEEEEEEEEEEEEEEEEF:---------------------------------------------
    //---------------------------------------------------------------------------------------
    //Config REF shader:
    shaders[REF].use();

    //for reflection:
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.currentTexture);
    shaders[REF].setInt("environmentMap", 2);
    shaders[REF].setFloat("refVal", 0.0f);


    shaders[REF].setMat4("projection", projection);
    shaders[REF].setMat4("view", view);
    shaders[REF].setFloat("shininess", 32.0f);
    shaders[REF].setFloat("alpha", 1.0f);
    
    //config refLight:
    refLight.update(camPos, camFro);

    //OUTSIDE THE MALL:---------------------------------------------------------------------

    //refLight
    if(controller.isNight){
        refLight.numOfPoints = 3;
        refLight.pointLightSpecular[0] = refLight.pointLightSpecular[1] =
        refLight.pointLightSpecular[2] = vec3(0.05f);
        refLight.pointLightPosition[0] = vec3(1433.98f, 1437.68f, -7595.11f);
        refLight.pointLightPosition[1] = vec3(8055.57f, 1024.51f, 4461.24f);
        refLight.pointLightPosition[2] = vec3(-10006.6f, 1314.37f, -5178.68f);
        
        refLight.pointLightColor[0] = refLight.pointLightColor[1] =
        refLight.pointLightColor[2] = Color::Blue;

        refLight.turnOnPoint(); 
        refLight.dirLightColor = vec3(0.5f); 
        refLight.turnOnDir();

    }
    else{
        refLight.dirLightColor = vec3(0.8f); 
        refLight.turnOnDir();
        shaders[REF].setInt("numOfPoints", 0);
    }
    // refLight.turnOnSpot();

    //ROOF BUILDING:
    TextureManager::enable(shaders[REF], textures[GRAY_BRICK], textures[GRAY_BRICK_SPEC], 40);
    draw(ROOF_BUILDING, toruses[ROOF_BUILDING].getIndexCount(), 0);

    //SPECIAL_BUILDINGs:
    draw(SPECIAL_BUILDING, cubes[SPECIAL_BUILDING].getIndexCount(), 6);

    //SPECIAL_VIEWs:
    draw(SPECIAL_VIEW, cylinders[SPECIAL_VIEW].getIndexCount(), 0);

    //CYL_ADDITIONAL:
    TextureManager::enable(shaders[REF], textures[LIGHT_METAL], textures[LIGHT_METAL_SPEC], 10);
    draw(CYL_ADDITIONAL, cylinders[CYL_ADDITIONAL].getIndexCount(), 30);

    //ENTRY:
    TextureManager::enable(shaders[REF], textures[BLACK_TILE], textures[BLACK_TILE_SPEC], 4);
    shaders[REF].setFloat("refVal", 0.1f);
    draw(ENTRY, toruses[ENTRY].getIndexCount(), 0);

    //SIDE_WALK:
    TextureManager::enable(shaders[REF], textures[GRAY_TILES], textures[GRAY_TILES_SPEC], 8);
    shaders[REF].setFloat("refVal", 0.07f);
    draw(SIDE_WALK, cubes[SIDE_WALK].getIndexCount(), 0);

    /*********************************************************************************************** */

    //MAIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIN:

    //INSIDE THE MALL:--------------------------------------------------------------------------------------

    //Config MAIN shader:
    shaders[MAIN].use();

    shaders[MAIN].setInt("environmentMap", 2);
    shaders[MAIN].setMat4("projection", projection);
    shaders[MAIN].setMat4("view", view);
    shaders[MAIN].setFloat("shininess", 32.0f);
    shaders[MAIN].setFloat("alpha", 1.0f);

    //config mainLight:
    mainLight.update(camera.Position, camera.Front);

    //change mainLight:
    mainLight.numOfPoints = 4;
    mainLight.pointLightPosition[0] = vec3(-12638.7f, 3000.0f, -1872.75f);
    mainLight.pointLightPosition[1] = vec3(-11387.6f, 3000.0f, 7564.3f);
    mainLight.pointLightPosition[2] = vec3(1734.2f, 3000.0f, 7617.22f);
    mainLight.pointLightPosition[3] = vec3(1745.84f, 3000.0f, -2104.92f);
    for(int i=0; i<4; i++){
        mainLight.pointLightLinear[i]= 	 	0.12* 0.0014f;
        mainLight.pointLightQuadratic[i] = 0.00000005* 0.000007f;
    }
    
    mainLight.turnOnPoint();
    mainLight.turnOnDir();


    //GROUND:
    TextureManager::enable(shaders[MAIN], textures[WHITE_TILES], textures[WHITE_TILES_SPEC], 4);
    draw(GROUND, cubes[GROUND].getIndexCount(), 0);
    

    //SUITE_SHOP::::::::::::
    //update mainLight:
    //Add 3 point light to the SUITE_STORE:
    mainLight.numOfPoints = 7;
    mainLight.pointLightPosition[4] = vec3(9.46201f, 235.168f, -2896.55f);
    mainLight.pointLightPosition[5] = vec3(-1498.04f, 235.644f, -2903.98f);
    mainLight.pointLightPosition[6] = vec3(1469.42f, 235.57f, -2904.44f);
    for(int i=4; i<7; i++){
        mainLight.pointLightColor[i] = Color::White;
        mainLight.pointLightLinear[i]= 	 	0.0014f;
        mainLight.pointLightQuadratic[i] =  0.00000007f;
    }
    
    mainLight.turnOnPoint();
    
    //SUITE_SHOP:
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^   
    TextureManager::enable(shaders[MAIN], textures[WOOD1], textures[WOOD1_SPEC], 2);
    draw(SUITE_SHOP, cubes[SUITE_SHOP].getIndexCount(), 6);

    TextureManager::enable(shaders[MAIN], textures[WHITE_TILES], textures[WHITE_TILES_SPEC], 1);
    draw(SUITE_GROUND, cubes[SUITE_GROUND].getIndexCount(), 0);


    //..CIRCLE_LIGHT:
    TextureManager::enable(shaders[MAIN], textures[WHITE], textures[WHITE], 1);
    draw(CIRCLE_LIGHT, cylinders[CIRCLE_LIGHT].getIndexCount(), 0);

    //..CLOTHS_PLACE:
    TextureManager::enable(shaders[MAIN], textures[LIGHT_METAL], textures[LIGHT_METAL_SPEC], 1);
    draw(CLOTHS_PLACE, cylinders[CLOTHS_PLACE].getIndexCount(), 0);

    //..SUITE1_OBJ:
    TextureManager::enable(shaders[MAIN], textures[SUITE1_TEX], textures[SUITE1_TEX], 1);
    draw(SUITE1_OBJ, 6, 0);

    //..SUITE5_OBJ:
    TextureManager::enable(shaders[MAIN], textures[SUITE2_TEX], textures[SUITE2_TEX], 1);
    draw(SUITE2_OBJ, 6, 0);

    //..CASHIER:
    TextureManager::enable(shaders[MAIN], textures[WHITE], textures[WHITE], 1);
    draw(CASHIER, cubes[CASHIER].getIndexCount(), 6);

    //..SCREEN:
    TextureManager::enable(shaders[MAIN], textures[BLACK], textures[BLACK], 1);
    draw(SCREEN, cubes[SCREEN].getIndexCount(), 0);

    //..MIRROR:
    // shaders[MAIN].setFloat("alpha", 0.4f);
    TextureManager::enable(shaders[MAIN], textures[SUITE_REF], textures[BLOOR_SPEC], 1);
    draw(MIRROR, cubes[MIRROR].getIndexCount(), 0);
    
    // SHOP_BLOOR:
    shaders[MAIN].setFloat("alpha", 0.2f);
    TextureManager::enable(shaders[MAIN], textures[BLOOR], textures[BLOOR_SPEC], 1);
    draw(SHOP_BLOOR, cubes[SHOP_BLOOR].getIndexCount(), 0);
    shaders[MAIN].setFloat("alpha", 1.0f);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^   

    //SHIRT_SHOP Lights:

    mainLight.pointLightPosition[4] = vec3(9.46201f, 245.168f, 10253.45f);
    mainLight.pointLightPosition[5] = vec3(-1498.04f, 249.644f, 10246.02f);
    mainLight.pointLightPosition[6] = vec3(1469.42f, 256.57f, 10245.56f);
    mainLight.turnOnPoint();

    //SHIRT_SHOP:
    TextureManager::enable(shaders[MAIN], textures[BLUE_PLASTIC], textures[BLUE_PLASTIC_SPEC], 2);
    draw(SHIRT_SHOP, cubes[SHIRT_SHOP].getIndexCount(), 6);

    TextureManager::enable(shaders[MAIN], textures[WHITE_TILES], textures[WHITE_TILES_SPEC], 1);
    draw(SHIRT_GROUND, cubes[SHIRT_GROUND].getIndexCount(), 0);

    //update point lights:

    //..CIRCLE_LIGHT_2:
    TextureManager::enable(shaders[MAIN], textures[WHITE], textures[WHITE], 4);
    draw(CIRCLE_LIGHT_2, cylinders[CIRCLE_LIGHT_2].getIndexCount(), 0);

    //..CLOTHS_PLACE:
    TextureManager::enable(shaders[MAIN], textures[LIGHT_METAL], textures[LIGHT_METAL_SPEC], 1);
    draw(CLOTHS_PLACE_2, cylinders[CLOTHS_PLACE_2].getIndexCount(), 0);

    //..SHIRT1_OBJ:
    TextureManager::enable(shaders[MAIN], textures[SHIRT1_TEX], textures[SHIRT1_TEX], 1);
    draw(SHIRT1_OBJ, 6, 0);

    //..SHIRT2_OBJ:
    TextureManager::enable(shaders[MAIN], textures[SHIRT2_TEX], textures[SHIRT2_TEX], 1);
    draw(SHIRT2_OBJ, 6, 0);

    //..CASHIER2:
    TextureManager::enable(shaders[MAIN], textures[WOOD1], textures[WOOD1_SPEC], 1);
    draw(CASHIER2, cubes[CASHIER2].getIndexCount(), 6);

    //..SCREEN2:
    TextureManager::enable(shaders[MAIN], textures[BLACK], textures[BLACK], 1);
    draw(SCREEN2, cubes[SCREEN2].getIndexCount(), 0);

    //..MIRROR2:
    // shaders[MAIN].setFloat("alpha", 0.4f);
    TextureManager::enable(shaders[MAIN], textures[SHIRT_REF], textures[BLOOR_SPEC], 1);
    draw(MIRROR2, cubes[MIRROR2].getIndexCount(), 0);
    
    // SHOP_BLOOR2:
    shaders[MAIN].setFloat("alpha", 0.2f);
    TextureManager::enable(shaders[MAIN], textures[BLOOR], textures[BLOOR_SPEC], 1);
    draw(SHOP_BLOOR2, cubes[SHOP_BLOOR2].getIndexCount(), 0);
    shaders[MAIN].setFloat("alpha", 1.0f);
    //------------------------------------------------------------------------------------
    //SHOES_SHOP Lights:

    mainLight.pointLightPosition[4] = vec3(9.46201f- 5350.0f, 245.168f, 10253.45f);
    mainLight.pointLightPosition[5] = vec3(-1798.04f- 5350.0f, 249.644f, 10246.02f);
    mainLight.pointLightPosition[6] = vec3(-3532.13f, 243.98f, 10278.2f);
    for(int i=4; i<7; i++){
        mainLight.pointLightLinear[i]= 	 	0.00014f;
        mainLight.pointLightQuadratic[i] =  0.00000007f;
    }
    mainLight.turnOnPoint();

    //SHOES_SHOP:
    TextureManager::enable(shaders[MAIN], textures[SPORTY], textures[SPORTY_SPEC], 3);
    draw(SHOES_SHOP, cubes[SHOES_SHOP].getIndexCount(), 6);

    TextureManager::enable(shaders[MAIN], textures[WHITE_TILES], textures[WHITE_TILES_SPEC], 1);
    draw(SHOES_GROUND, cubes[SHOES_GROUND].getIndexCount(), 0);
    
    //..SQUARE_LIGHT:
    TextureManager::enable(shaders[MAIN], textures[WHITE], textures[WOOD1_SPEC], 4);
    draw(SQUARE_LIGHT, cubes[SQUARE_LIGHT].getIndexCount(), 0);

    //..CASHIER3:
    TextureManager::enable(shaders[MAIN], textures[BLOOR], textures[BLOOR_SPEC], 1);
    draw(CASHIER3, cubes[CASHIER3].getIndexCount(), 6);


    //SMALL_ROOF:
    shaders[MAIN].setFloat("alpha", 0.3f);
    TextureManager::enable(shaders[MAIN], textures[BLOOR], textures[BLOOR_SPEC], 1);
    draw(SMALL_ROOF, cubes[SMALL_ROOF].getIndexCount(), 0);
    

    //..SHOE1:
    TextureManager::enable(shaders[MAIN], textures[SHOE1_TEX], textures[SHOE1_TEX], 1);
    draw(SHOE1, 6, 0);

    //..SHOE2:
    TextureManager::enable(shaders[MAIN], textures[SHOE2_TEX], textures[SHOE2_TEX], 1);
    draw(SHOE2, 6, 0);

    //..SHOE3:
    TextureManager::enable(shaders[MAIN], textures[SHOE3_TEX], textures[SHOE3_TEX], 1);
    draw(SHOE3, 6, 0);

    // SHOP_BLOOR3:
    shaders[MAIN].setFloat("alpha", 0.2f);
    TextureManager::enable(shaders[MAIN], textures[BLOOR], textures[BLOOR_SPEC], 1);
    draw(SHOP_BLOOR3, cubes[SHOP_BLOOR3].getIndexCount(), 0);
    shaders[MAIN].setFloat("alpha", 1.0f);
    //-----------------------------------------------------------------------------------
    //DRESS_SHOP Lights:

    mainLight.pointLightPosition[4] = vec3(-9153.74f, 261.258f, 10244.0f);
    mainLight.pointLightPosition[5] = vec3(-12147.3f, 249.924f, 10244.0f);
    mainLight.pointLightPosition[6] = vec3(-10642.2f, 229.65f, 10221.4f);
    for(int i=4; i<7; i++){
        mainLight.pointLightLinear[i]= 	 	0.00014f;
        mainLight.pointLightQuadratic[i] =  0.000001f;
        mainLight.pointLightColor[i] = Color::Pink;
    }
    mainLight.turnOnPoint();

    //DRESS_SHOP:
    TextureManager::enable(shaders[MAIN], textures[PINK], textures[PINK_SPEC], 1);
    draw(DRESS_SHOP, cubes[DRESS_SHOP].getIndexCount(), 6);

    TextureManager::enable(shaders[MAIN], textures[WHITE_TILES], textures[WHITE_TILES_SPEC], 1);
    draw(DRESS_GROUND, cubes[DRESS_GROUND].getIndexCount(), 0);

    //..CIRCLE_LIGHT_4:
    TextureManager::enable(shaders[MAIN], textures[BLOOR], textures[BLOOR_SPEC], 1);
    draw(CIRCLE_LIGHT_4, cylinders[CIRCLE_LIGHT_4].getIndexCount(), 0);

    //..CLOTHS_PLACE_4:
    TextureManager::enable(shaders[MAIN], textures[LIGHT_METAL], textures[LIGHT_METAL_SPEC], 1);
    draw(CLOTHS_PLACE_4, cylinders[CLOTHS_PLACE_4].getIndexCount(), 0);

    //DRESS1:
    TextureManager::enable(shaders[MAIN], textures[DRESS1_TEX], textures[DRESS1_TEX], 1);
    draw(DRESS1, 6, 0);

    //DRESS2:
    TextureManager::enable(shaders[MAIN], textures[DRESS2_TEX], textures[DRESS2_TEX], 1);
    draw(DRESS2, 6, 0);

    //DRESS3:
    TextureManager::enable(shaders[MAIN], textures[DRESS3_TEX], textures[DRESS3_TEX], 1);
    draw(DRESS3, 6, 0);

    //DRESS4:
    TextureManager::enable(shaders[MAIN], textures[DRESS4_TEX], textures[DRESS4_TEX], 1);
    draw(DRESS4, 6, 0);

    //..CASHIER4:
    TextureManager::enable(shaders[MAIN], textures[WHITE], textures[WOOD1_SPEC], 1);
    draw(CASHIER4, cubes[CASHIER4].getIndexCount(), 6);

    //..DRESSING_ROOM:
    TextureManager::enable(shaders[MAIN], textures[PINK], textures[PINK_SPEC], 1);
    draw(DRESSING_ROOM, cubes[DRESSING_ROOM].getIndexCount(), 6);

    //..MIRROR4:
    TextureManager::enable(shaders[MAIN], textures[DRESS_REF], textures[BLOOR_SPEC], 1);
    draw(MIRROR4, cubes[MIRROR4].getIndexCount(), 0);

    // SHOP_BLOOR4:
    shaders[MAIN].setFloat("alpha", 0.2f);
    TextureManager::enable(shaders[MAIN], textures[BLOOR], textures[BLOOR_SPEC], 1);
    draw(SHOP_BLOOR4, cubes[SHOP_BLOOR4].getIndexCount(), 0);
    shaders[MAIN].setFloat("alpha", 1.0f);

    //----------------------------------------------------------------------------------------

    //RESTAURANT:

    mainLight.numOfPoints = 8;
    mainLight.pointLightPosition[4] = vec3(3795.58f, 153.309f, -946.823f);
    mainLight.pointLightPosition[5] = vec3(3820.7f, 165.071f, -1341.6f);
    mainLight.pointLightPosition[6] = vec3(4145.5f, 86.7375f, -1355.64f);
    mainLight.pointLightPosition[7] = vec3(4169.58f, 95.2565f, -982.829f);

    for(int i=4; i<8; i++){
        mainLight.pointLightColor[i] = Color::DarkRed;
        mainLight.pointLightLinear[i]= 	 	0.00014f;
        mainLight.pointLightQuadratic[i] =  0.000001f;
    }
    mainLight.turnOnPoint();
    

    //REST_ROOF:
    TextureManager::enable(shaders[MAIN], textures[TRAV], textures[TRAV_SPEC],4);
    draw(REST_ROOF, cylinders[REST_ROOF].getIndexCount(), 0);

    //TRIA:
    TextureManager::enable(shaders[MAIN], textures[RED_PLASTIC], textures[RED_PLASTIC_SPEC],1);
    draw(TRIA, cylinders[TRIA].getIndexCount(), 0);

    //CYL_LIGHT:
    TextureManager::enable(shaders[MAIN], textures[BLOOR], textures[BLOOR_SPEC],1);
    draw(CYL_LIGHT, toruses[CYL_LIGHT].getIndexCount(), 0);

    //REST_GROUND:
    TextureManager::enable(shaders[MAIN], textures[RED_TILES], textures[RED_TILES_SPEC], 6);
    draw(REST_GROUND, cylinders[REST_GROUND].getIndexCount(), 0);

    //REST_WALL:
    draw(REST_WALL, cubes[REST_WALL].getIndexCount(), 0);

    //..CASHIER5:
    TextureManager::enable(shaders[MAIN], textures[RED_PLASTIC], textures[RED_PLASTIC_SPEC], 1);
    draw(CASHIER5, cubes[CASHIER5].getIndexCount(), 6);

    //..TABLE:
    TextureManager::enable(shaders[MAIN], textures[RED_FABRIC1], textures[RED_FABRIC1_SPEC], 1);
    draw(TABLE, cylinders[TABLE].getIndexCount(), 0);

    //..CHAIR_BASE:
    TextureManager::enable(shaders[MAIN], textures[RED_FABRIC2], textures[RED_FABRIC2_SPEC], 1);
    draw(CHAIR_BASE, cylinders[CHAIR_BASE].getIndexCount(), 0);


    //..CHAIR:
    draw(CHAIR, toruses[CHAIR].getIndexCount(), 0);
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    //conf Lights for Furniture store:
    mainLight.numOfPoints = 8;
    mainLight.pointLightPosition[4] = vec3(3970.11f, -303.889f, 1729.78f);
    mainLight.pointLightPosition[5] = vec3(3736.78f, -303.889f, 3153.78f);
    mainLight.pointLightPosition[6] = vec3(3495.82f, -303.889f, 4608.87f);
    mainLight.pointLightPosition[7] = vec3(3612.33f, -303.388f, 6169.94f);

    for(int i=4; i<mainLight.numOfPoints; i++){
        mainLight.pointLightColor[i] = Color::SandyBrown;
        mainLight.pointLightLinear[i]= 	 	0.000001 * 0.0014f;
        mainLight.pointLightQuadratic[i] =  0.0000007f;
    }
    mainLight.turnOnPoint();

    //FURN_STORE::::::::::::::::::::::::::::
    TextureManager::enable(shaders[MAIN], textures[BEIGE], textures[BEIGE_SPEC], 4);
    draw(FURN_STORE, cubes[FURN_STORE].getIndexCount(), 6);

    //FURN_GROUND:
    TextureManager::enable(shaders[MAIN], textures[WHITE_TILES], textures[WHITE_TILES_SPEC], 1);
    draw(FURN_GROUND, cubes[FURN_GROUND].getIndexCount(), 0);

    //..CIRCLE_LIGHT6:
    TextureManager::enable(shaders[MAIN], textures[BLOOR], textures[BLOOR_SPEC], 1);
    draw(CIRCLE_LIGHT6, cylinders[CIRCLE_LIGHT6].getIndexCount(), 0);

    //..BED:
    TextureManager::enable(shaders[MAIN], textures[BED_DIFF], textures[BED_SPEC], 1);
    draw3Dmodel(BED, 0, threeDModels[BED].meshes.size());

    //..SOFA1:
    TextureManager::enable(shaders[MAIN], textures[SOFA1_DIFF], textures[BLACK1], 1);
    draw3Dmodel(SOFA1, 0, threeDModels[SOFA1].meshes.size());

    //..SOFA2:
    TextureManager::enable(shaders[MAIN], textures[SOFA2_DIFF], textures[BLACK1], 1);
    draw3Dmodel(SOFA2, 0, threeDModels[SOFA2].meshes.size());

    //..TABLE2:
    TextureManager::enable(shaders[MAIN], textures[TABLE2_DIFF], textures[TABLE2_SPEC], 1);
    draw3Dmodel(TABLE2, 0, threeDModels[TABLE2].meshes.size());

    //..TABLE3:
    TextureManager::enable(shaders[MAIN], textures[TABLE3_DIFF], textures[TABLE3_SPEC], 1);
    draw3Dmodel(TABLE3);

    //..TABLE4:
    TextureManager::enable(shaders[MAIN], textures[TABLE4_DIFF], textures[BLACK1], 1);
    draw3Dmodel(TABLE4);

    //..CABINET1:
    TextureManager::enable(shaders[MAIN], textures[CABINET1_DIFF], textures[BLACK1], 1);
    draw3Dmodel(CABINET1);
    
    //..COUCH2:
    TextureManager::enable(shaders[MAIN], textures[COUCH2_DIFF], textures[COUCH2_SPEC], 1);
    draw3Dmodel(COUCH2);
    

    //..CASHIER6:
    shaders[MAIN].setFloat("alpha", 0.8f);
    TextureManager::enable(shaders[MAIN], textures[BLOOR], textures[BLOOR_SPEC], 1);
    draw(CASHIER6, cubes[CASHIER6].getIndexCount(), 6);
    shaders[MAIN].setFloat("alpha", 1.0f);

    //..SOFA:
    TextureManager::enable(shaders[MAIN], textures[SOFA_DIFF], textures[SOFA_SPEC], 1);
    draw3Dmodel(SOFA);

    //..TABLE5:
    TextureManager::enable(shaders[MAIN], textures[TABLE5_DIFF], textures[TABLE5_SPEC], 1);
    draw3Dmodel(TABLE5);

    
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    
    mainLight.numOfPoints = 8;
    mainLight.pointLightPosition[4] = vec3(-13362.7f, 150.694f, 6568.96f);
    mainLight.pointLightPosition[5] = vec3(-13340.6f, 150.694f, 4554.39f);
    mainLight.pointLightPosition[6] = vec3(-13319.4f, 150.694f, 2560.75f );
    mainLight.pointLightPosition[7] = vec3(-13374.3f, 150.694f, 355.059f );

    for(int i=4; i<mainLight.numOfPoints; i++){
        mainLight.pointLightColor[i] = Color::Blue;
        mainLight.pointLightLinear[i]= 	 	0.0014f;
        mainLight.pointLightQuadratic[i] =  0.000007f;
    }
    mainLight.turnOnPoint();
    // TECH_STORE:::::::::::::::::::::
    TextureManager::enable(shaders[MAIN], textures[GREEN_TILES], textures[GREEN_TILES_SPEC], 6);
    draw(TECH_STORE, cubes[TECH_STORE].getIndexCount(), 6);

    //TECH_GROUND:
    TextureManager::enable(shaders[MAIN], textures[WHITE_TILES], textures[WHITE_TILES_SPEC], 2);
    draw(TECH_GROUND, cubes[TECH_GROUND].getIndexCount(), 0);

    //..CIRCLE_LIGHT7:
    TextureManager::enable(shaders[MAIN], textures[JUST_WHITE], textures[JUST_WHITE_SPEC], 1);
    draw(CIRCLE_LIGHT7, cylinders[CIRCLE_LIGHT7].getIndexCount(), 0);

    //..WASHING_BODY:
    TextureManager::enable(shaders[MAIN], textures[JUST_WHITE], textures[JUST_WHITE_SPEC], 1);
    draw(WASHING_BODY, cubes[WASHING_BODY].getIndexCount(), 6);

    //..WASHING1:
    TextureManager::enable(shaders[MAIN], textures[WASHING1_DIFF], textures[WASHING1_DIFF], 1);
    draw(WASHING1, 6, 0);

    //..WASHING2:
    TextureManager::enable(shaders[MAIN], textures[WASHING2_DIFF], textures[WASHING2_DIFF], 1);
    draw(WASHING2, 6, 0);

    //..FRIDGE_BODY:
    TextureManager::enable(shaders[MAIN], textures[GRAY_METAL], textures[GRAY_METAL_SPEC], 1);
    draw(FRIDGE_BODY, cubes[FRIDGE_BODY].getIndexCount(), 6);

    //..FRIDGE1:
    TextureManager::enable(shaders[MAIN], textures[FRIDGE1_DIFF], textures[FRIDGE1_DIFF], 1);
    draw(FRIDGE1, 6, 0);

    //..FRIDGE2:
    TextureManager::enable(shaders[MAIN], textures[FRIDGE2_DIFF], textures[FRIDGE2_DIFF], 1);
    draw(FRIDGE2, 6, 0);

    //..STOVE:
    TextureManager::enable(shaders[MAIN], textures[STOVE_DIFF], textures[STOVE_DIFF], 1);
    draw3Dmodel(STOVE);

    //..OVEN:
    TextureManager::enable(shaders[MAIN], textures[OVEN_DIFF], textures[OVEN_DIFF], 1);
    draw(OVEN, 6, 0);

    //..MICRO:
    TextureManager::enable(shaders[MAIN], textures[MICRO_DIFF], textures[MICRO_DIFF], 1);
    draw(MICRO, 6, 0);

    //..TV:
    TextureManager::enable(shaders[MAIN], textures[TV_DIFF], textures[JUST_WHITE_SPEC], 1);
    draw(TV, 6, 0);

    //..SYRIA:
    shaders[MAIN].setFloat("alpha", cos((float)glfwGetTime()));
    TextureManager::enable(shaders[MAIN], textures[SYRIA_DIFF], textures[JUST_WHITE_SPEC], 1);
    draw(SYRIA, 6, 0);
    shaders[MAIN].setFloat("alpha", 1.0f);

    // SHOP_BLOOR6:
    shaders[MAIN].setFloat("alpha", 0.2f);
    TextureManager::enable(shaders[MAIN], textures[BLOOR], textures[BLOOR_SPEC], 1);
    draw(SHOP_BLOOR6, cubes[SHOP_BLOOR6].getIndexCount(), 0);
    shaders[MAIN].setFloat("alpha", 1.0f);
    
    //---------------------------------------------------------------------------------------
    camera.printPos();
    // SKYBOX:
    skybox.setEnvironment(!controller.isNight);
    skybox.draw(shaders[SKYBOX], view, projection);
    
    //************************************************************************************ */
    // ALPHA objects:

    shaders[REF].use();
    shaders[REF].setFloat("refVal", 0.8f);
    //CYL_BUILDING  #ALPHA:
    shaders[REF].setFloat("alpha", 0.75f);
    TextureManager::enable(shaders[REF], textures[BLUE_WINDOW], textures[BLUE_WINDOW], 16);
    draw(CYL_BUILDING, cylinders[CYL_BUILDING].getIndexCount(), 30);

    //GLASS_ROOF #ALPHA:
    shaders[REF].setFloat("shininess", 128.0f);
    TextureManager::enable(shaders[REF], textures[WHITE_WINDOW], textures[WHITE_WINDOW_SPEC], 8);
    draw(GLASS_ROOF, cubes[GLASS_ROOF].getIndexCount(), 0);


    //MALL_DOOR: $ALPHA:
    if(nearMallDoor(camX, camY, camZ) && cntMallDoor){
        if(cntMallDoor==89) engine->play3D("../resources/audio/automaticdoor.wav", vec3df(-4501.33f, -320.344f, -2852.66f));
        if(cntMallDoor==30)  engine->play3D("../resources/audio/store-door-chime.wav", vec3df(-4501.33f, -320.344f, -2652.66f));
        cntMallDoor--;
        models[MALL_DOOR][0] = translate(models[MALL_DOOR][0], vec3(10.0f, 0.0f, 0.0f));
        models[MALL_DOOR][1] = translate(models[MALL_DOOR][1], vec3(-10.0f, 0.0f, 0.0f));
        cubeBuffers(MALL_DOOR);
    }
    else if(!nearMallDoor(camX, camY, camZ) && cntMallDoor<90){
        cntMallDoor++;
        models[MALL_DOOR][0] = translate(models[MALL_DOOR][0], vec3(-10.0f, 0.0f, 0.0f));
        models[MALL_DOOR][1] = translate(models[MALL_DOOR][1], vec3(10.0f, 0.0f, 0.0f));
        cubeBuffers(MALL_DOOR);
    }
    shaders[REF].setFloat("refVal", 0.8f);
    shaders[REF].setFloat("alpha", 0.4f);
    TextureManager::enable(shaders[REF], textures[BLOOR], textures[BLOOR_SPEC], 1);
    draw(MALL_DOOR, cubes[MALL_DOOR].getIndexCount(), 0);
    shaders[REF].setFloat("shininess", 32.0f);

    //ENTRY_BLOOR: $ALPHA:
    shaders[REF].setFloat("refVal", 0.8f);
    shaders[REF].setFloat("alpha", 0.2f);
    TextureManager::enable(shaders[REF], textures[BLOOR], textures[BLOOR_SPEC], 1);
    draw(ENTRY_BLOOR, cubes[ENTRY_BLOOR].getIndexCount(), 0);
    shaders[REF].setFloat("shininess", 32.0f);

    //-------------------------------------------------------------------------------------------
    
    
}












void Renderer::draw(string objectName, int numOfVertices, int offset)
{
    vaos[objectName].Bind(); ebos[objectName].Bind();
    glDrawElementsInstanced(GL_TRIANGLES, numOfVertices, GL_UNSIGNED_INT, (void*)(offset*sizeof(float)), models[objectName].size());  

}


void Renderer::draw3Dmodel(string name, int startIndex, int endIndex)
{
    if(endIndex==1e9) endIndex = threeDModels[name].meshes.size();
    for (unsigned int i = startIndex; i < endIndex; i++)
    {
        glBindVertexArray(threeDModels[name].meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(threeDModels[name].meshes[i].indices.size()), GL_UNSIGNED_INT, 0, models[name].size());
        glBindVertexArray(0);
    }
    // cout << (int)threeDModels[name].meshes.size() << endl;
}

bool Renderer::nearMallDoor(float x, float y, float z){
    return z>=-3440.0f && z<-2260.0f && x>=-5060.0f && x<-3960.0f && y>=-391.5f && y<-370.0f;
}