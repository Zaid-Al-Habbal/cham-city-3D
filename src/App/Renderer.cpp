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

    //for Escalator:
    cntEsc = 55;

    cntGoingDownUsingESC = cntGoingUpUsingESC = 0;

    //MALL cubemap:
    mallCubemapTexture = loadMallCubemap();

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

    //ROAD:
    TextureManager::enable(shaders[REF], textures[ROAD_DIFF], textures[ROAD_SPEC], 2);
    shaders[REF].setFloat("refVal", 0.007f);
    draw(ROAD, cubes[ROAD].getIndexCount(), 0);

    //OUTSIDE_GROUND:
    TextureManager::enable(shaders[REF], textures[ASPHALT_DIFF], textures[ASPHALT_SPEC], 128);
    draw(OUTSIDE_GROUND, cubes[OUTSIDE_GROUND].getIndexCount(), 0);

    //PAVING:
    TextureManager::enable(shaders[REF], textures[PAVING_DIFF], textures[PAVING_SPEC], 2);
    draw(PAVING, cubes[PAVING].getIndexCount(), 0);

    //STREET_LIGHT:
    TextureManager::enable(shaders[REF], textures[STREET_LIGHT_TEX], textures[STREET_LIGHT_TEX], 1);
    draw3Dmodel(STREET_LIGHT);

    //BUILDING:
    TextureManager::enable(shaders[REF], textures[BUILDING_TEX], textures[BUILDING_TEX], 1);
    draw(BUILDING, cubes[BUILDING].getIndexCount(), 0);

    //SMALL_TREE:
    TextureManager::enable(shaders[REF], textures[SMALL_TREE_TEX], textures[SMALL_TREE_TEX], 1);
    draw3Dmodel(SMALL_TREE);

    //AD1:
    TextureManager::enable(shaders[REF], textures[AD1_TEX], textures[AD1_TEX], 1);
    draw(AD1, cubes[AD1].getIndexCount(), 0);

    //AD2:
    TextureManager::enable(shaders[REF], textures[AD2_TEX], textures[AD2_TEX], 1);
    draw(AD2, cubes[AD2].getIndexCount(), 0);

    //AD3:
    TextureManager::enable(shaders[REF], textures[AD3_TEX], textures[AD3_TEX], 1);
    draw(AD3, cubes[AD3].getIndexCount(), 0);

    //AD4:
    TextureManager::enable(shaders[REF], textures[AD4_TEX], textures[AD4_TEX], 1);
    draw(AD4, cubes[AD4].getIndexCount(), 0);

    //AD5:
    TextureManager::enable(shaders[REF], textures[AD5_TEX], textures[AD5_TEX], 1);
    draw(AD5, cubes[AD5].getIndexCount(), 0);

    //AD6:
    TextureManager::enable(shaders[REF], textures[AD6_TEX], textures[AD6_TEX], 1);
    draw(AD6, cubes[AD6].getIndexCount(), 0);

    //AD7:
    TextureManager::enable(shaders[REF], textures[AD7_TEX], textures[AD7_TEX], 1);
    draw(AD7, cubes[AD7].getIndexCount(), 0);
    


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

    //MALL_LIGHT:
    TextureManager::enable(shaders[MAIN], textures[MALL_LIGHT_TEX], textures[MALL_LIGHT_TEX], 1);
    draw3Dmodel(MALL_LIGHT);


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
    TextureManager::enable(shaders[MAIN], textures[SUITE_REF], textures[BLOOR_SPEC], 1);
    draw(MIRROR, cubes[MIRROR].getIndexCount(), 0);
    
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
    TextureManager::enable(shaders[MAIN], textures[SHIRT_REF], textures[BLOOR_SPEC], 1);
    draw(MIRROR2, cubes[MIRROR2].getIndexCount(), 0);
    
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
    shaders[MAIN].setFloat("alpha", 1.0f);


    //..SHOE1:
    TextureManager::enable(shaders[MAIN], textures[SHOE1_TEX], textures[SHOE1_TEX], 1);
    draw(SHOE1, 6, 0);

    //..SHOE2:
    TextureManager::enable(shaders[MAIN], textures[SHOE2_TEX], textures[SHOE2_TEX], 1);
    draw(SHOE2, 6, 0);

    //..SHOE3:
    TextureManager::enable(shaders[MAIN], textures[SHOE3_TEX], textures[SHOE3_TEX], 1);
    draw(SHOE3, 6, 0);

    //..SHOE4:
    TextureManager::enable(shaders[MAIN], textures[SHOE4_TEX], textures[SHOE4_TEX], 1);
    draw3Dmodel(SHOE4);

    //..SHOE5:
    TextureManager::enable(shaders[MAIN], textures[SHOE5_TEX], textures[SHOE5_TEX_SPEC], 1);
    draw3Dmodel(SHOE5);

    //..SHOE6:
    TextureManager::enable(shaders[MAIN], textures[SHOE6_TEX], textures[SHOE6_TEX], 1);
    draw3Dmodel(SHOE6);

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


    //-------------------------------------------------------------------------------------------

    //INSIDE_ROOF:
    TextureManager::enable(shaders[MAIN], textures[WHITE_TILES], textures[WHITE_TILES_SPEC], 10);
    draw(INSIDE_ROOF, toruses[INSIDE_ROOF].getIndexCount(), 0);

    //ROOF_WALL:
    TextureManager::enable(shaders[MAIN], textures[JUST_WHITE], textures[JUST_WHITE_SPEC], 2);
    draw(ROOF_WALL, cubes[ROOF_WALL].getIndexCount(), 0);

    //COLUMN:
    TextureManager::enable(shaders[MAIN], textures[LIGHT_METAL], textures[LIGHT_METAL_SPEC], 2);
    draw(COLUMN, cylinders[COLUMN].getIndexCount(), 0);

    //------------------------------------------------------------------------------------------------
    mainLight.numOfPoints = 7;
    mainLight.pointLightPosition[4] = vec3(-10647.7f, 240.348f, -2900.12f);
    mainLight.pointLightPosition[5] = vec3(-9168.09f, 240.592f, -2901.13f);
    mainLight.pointLightPosition[6] = vec3(-7686.82f, 240.816f, -2869.64f);

    for(int i=4; i<mainLight.numOfPoints; i++){
        mainLight.pointLightColor[i] = Color::White;
        mainLight.pointLightLinear[i]= 	 	0.0014f;
        mainLight.pointLightQuadratic[i] =  0.000007f;
    }
    mainLight.turnOnPoint();

    //JEWELRY_STORE:
    TextureManager::enable(shaders[MAIN], textures[YELLOW], textures[YELLOW_SPEC], 4);
    draw(JEWELRY_STORE, cubes[JEWELRY_STORE].getIndexCount(), 6);

    //JEWELRY_GROUND:
    TextureManager::enable(shaders[MAIN], textures[WHITE_TILES], textures[WHITE_TILES_SPEC], 4);
    draw(JEWELRY_GROUND, cubes[JEWELRY_GROUND].getIndexCount(), 6);
 
    //..CIRCLE_LIGHT8:
    TextureManager::enable(shaders[MAIN], textures[JUST_WHITE], textures[JUST_WHITE_SPEC], 1);
    draw(CIRCLE_LIGHT8, cylinders[CIRCLE_LIGHT8].getIndexCount(), 0);

    //..DISPLAY_BASE:
    TextureManager::enable(shaders[MAIN], textures[WOOD4], textures[WOOD4_SPEC], 2);
    draw(DISPLAY_BASE, cubes[DISPLAY_BASE].getIndexCount(), 0);

    //CASHIER8:
    TextureManager::enable(shaders[MAIN], textures[WOOD4], textures[WOOD4_SPEC], 1);
    draw(CASHIER8, cubes[CASHIER8].getIndexCount(), 6);

    shaders[MAIN].setFloat("shininess", 128.0f);
    //JEW1:
    TextureManager::enable(shaders[MAIN], textures[GOLD], textures[LIGHT_METAL_SPEC], 1);
    draw(JEW1, toruses[JEW1].getIndexCount(), 0);

    //JEW2:
    TextureManager::enable(shaders[MAIN], textures[SILVER], textures[LIGHT_METAL_SPEC], 1);
    draw(JEW2, toruses[JEW2].getIndexCount(), 0);
    
    //JEW3:
    TextureManager::enable(shaders[MAIN], textures[SILVER], textures[LIGHT_METAL_SPEC], 1);
    draw(JEW3, toruses[JEW3].getIndexCount(), 0);

    //STONE:
    TextureManager::enable(shaders[MAIN], textures[RED_PLASTIC], textures[RED_PLASTIC_SPEC], 1);
    draw(STONE, cylinders[STONE].getIndexCount(), 0);

    //JEW4:
    TextureManager::enable(shaders[MAIN], textures[GOLD], textures[LIGHT_METAL_SPEC], 1);
    draw(JEW4, toruses[JEW4].getIndexCount(), 0);

    //STONE2:
    TextureManager::enable(shaders[MAIN], textures[BLUE_PLASTIC], textures[RED_PLASTIC_SPEC], 1);
    draw(STONE2, cylinders[STONE2].getIndexCount(), 0);

    //JEW5:
    TextureManager::enable(shaders[MAIN], textures[GOLD2], textures[LIGHT_METAL_SPEC], 1);
    draw(JEW5, toruses[JEW5].getIndexCount(), 0);

    //JEW6:
    TextureManager::enable(shaders[MAIN], textures[SILVER2], textures[LIGHT_METAL_SPEC], 1);
    draw(JEW6, toruses[JEW6].getIndexCount(), 0);

    //JEW7:
    TextureManager::enable(shaders[MAIN], textures[PINK], textures[LIGHT_METAL_SPEC], 1);
    draw(JEW7, toruses[JEW7].getIndexCount(), 0);

    //JEW8:
    TextureManager::enable(shaders[MAIN], textures[GOLD3], textures[LIGHT_METAL_SPEC], 1);
    draw(JEW8, toruses[JEW8].getIndexCount(), 0);

    //JEW9:
    TextureManager::enable(shaders[MAIN], textures[GOLD4], textures[LIGHT_METAL_SPEC], 4);
    draw(JEW9, cones[JEW9].getIndexCount(), 0);

    //JEW10:
    TextureManager::enable(shaders[MAIN], textures[GOLD], textures[LIGHT_METAL_SPEC], 1);
    draw(JEW10, cones[JEW10].getIndexCount(), 0);

    //JEW11:
    TextureManager::enable(shaders[MAIN], textures[SILVER2], textures[LIGHT_METAL_SPEC], 1);
    draw(JEW11, cylinders[JEW11].getIndexCount(), 0);

    //JEW12:
    TextureManager::enable(shaders[MAIN], textures[GOLD2], textures[LIGHT_METAL_SPEC], 1);
    draw(JEW12, toruses[JEW12].getIndexCount(), 0);

    //JEW13:
    TextureManager::enable(shaders[MAIN], textures[SILVER2], textures[LIGHT_METAL_SPEC], 1);
    draw(JEW13, toruses[JEW13].getIndexCount(), 0);

    //..DISPLAY_VIEW:
    shaders[MAIN].setFloat("alpha", 0.18f);
    TextureManager::enable(shaders[MAIN], textures[BLOOR], textures[BLOOR_SPEC], 1);
    draw(DISPLAY_VIEW, cubes[DISPLAY_VIEW].getIndexCount(), 0);
    shaders[MAIN].setFloat("alpha", 1.0f);
    
    shaders[MAIN].setFloat("shininess", 32.0f);

    //PALM;
    TextureManager::enable(shaders[MAIN], textures[PALM1_DIFF], textures[PALM1_DIFF], 1);
    draw3Dmodel(PALM, 0, 1);

    TextureManager::enable(shaders[MAIN], textures[PALM3_DIFF], textures[PALM3_DIFF], 1);
    draw3Dmodel(PALM, 2, 3);


    //PALM_LEAVES:
    TextureManager::enable(shaders[MAIN], textures[PALM2_DIFF], textures[PALM2_DIFF], 1);
    draw3Dmodel(PALM_LEAVES, 1, 2);

    TextureManager::enable(shaders[MAIN], textures[PALM4_DIFF], textures[PALM4_DIFF], 1);
    draw3Dmodel(PALM_LEAVES, 3, 4);

    //ELEVATOR START HERE:

    //..ELEVATOR_BARs:
    TextureManager::enable(shaders[MAIN], textures[SILVER3], textures[LIGHT_METAL_SPEC], 1);
    draw(ELEVATOR_BAR, cylinders[ELEVATOR_BAR].getIndexCount(), 0);

    //ESCALATOR START HERE:

    //ESCALATORs:
    cntEsc--; if(cntEsc==-1) cntEsc=54;
    TextureManager::enable(shaders[MAIN], textures[ESCALATOR_TEX], textures[LIGHT_METAL_SPEC], 1);
    turnEscOn();
    
    draw(ESCALATOR, cubes[ESCALATOR].getIndexCount(), 0);
    if(cntGoingDownUsingESC) escDown(controller.camera);
    else if(camY>880.0f && camY<940.0f && camX>380.8f && camX<400.0f && camZ<3096.0f && camZ>2880.0f) cntGoingDownUsingESC=400;
    turnEsc2On();
    draw(ESCALATOR2, cubes[ESCALATOR2].getIndexCount(), 0);
    if(cntGoingUpUsingESC) escUp(controller.camera);
    else if(camY>-420.0f && camY<-360.0f && camX>-1550.0f && camX<-1530.0f && camZ>3866.0f && camZ<4040.0f) cntGoingUpUsingESC=400;
    
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

    //for reflection inside the mall:
    //change refLight:
    refLight.numOfPoints = 4;
    refLight.pointLightPosition[0] = vec3(-12638.7f, 3000.0f, -1872.75f);
    refLight.pointLightPosition[1] = vec3(-11387.6f, 3000.0f, 7564.3f);
    refLight.pointLightPosition[2] = vec3(1734.2f, 3000.0f, 7617.22f);
    refLight.pointLightPosition[3] = vec3(1745.84f, 3000.0f, -2104.92f);
    for(int i=0; i<4; i++){
        refLight.pointLightLinear[i]= 	 	0.12* 0.0014f;
        refLight.pointLightQuadratic[i] = 0.00000005* 0.000007f;
        refLight.pointLightColor[i] = Color::White;
    }
    
    refLight.turnOnPoint();

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mallCubemapTexture);
    shaders[REF].setInt("environmentMap", 2);


    //ELEVATOR_BODY:
    shaders[REF].setFloat("refVal", 0.1f);
    shaders[REF].setFloat("alpha", 1.0f);

    //conf elevator logic:
    if(controller.cntEleDoor<0){
        controller.cntEleDoor++;
        openEleDoor();
    }
    else if(controller.thereIsMovement){
        if(controller.cntEleDoor){
            controller.cntEleDoor--;
            closeEleDoor();
        }
        else if(controller.cnt0to1){            
            controller.cnt0to1--;
            eleUp(controller.camera);
        }
        else if(controller.cnt0to2){
            controller.cnt0to2--;
            eleUp(controller.camera);
        }
        else if(controller.cnt1to0){
            controller.cnt1to0--;
            eleDown(controller.camera);
        }
        else if(controller.cnt1to2){
            controller.cnt1to2--;
            eleUp(controller.camera);
        }
        else if(controller.cnt2to0){
            controller.cnt2to0--;
            eleDown(controller.camera);
        }
        else if(controller.cnt2to1){
            controller.cnt2to1--;
            eleDown(controller.camera);
        }
        if(controller.thereIsMovement==1){
            controller.cntEleDoor = -90;
        }
    }
    else if(controller.groundFloor){
        if(camY>880.0f && camY<940.0f){
            controller.cnt1to0 = 425;
            controller.cntEleDoor = 90;
        } 
        else if(camY>2180.0f && camY<2240.0f){
            controller.cnt2to0 = 850;
            controller.cntEleDoor = 90;
        } 
    }
    else if(controller.firstFloor){
        if(camY>-420.0f && camY<-360.0f){
            controller.cnt0to1 = 425;
            controller.cntEleDoor = 90;
        }
        else if(camY>2180.0f && camY<2240.0f){
            controller.cnt2to1 = 425;
            controller.cntEleDoor = 90;
        } 
    }
    else if(controller.secondFloor){
        if(camY>-420.0f && camY<-360.0f){
            controller.cnt0to2 = 850;
            controller.cntEleDoor = 90;
        }
        else if(camY>880.0f && camY<940.0f){
            controller.cnt1to2 = 425;
            controller.cntEleDoor = 90;
        } 
    }

    TextureManager::enable(shaders[REF], textures[MARBLE], textures[LIGHT_METAL_SPEC], 16);
    draw(ELEVATOR_BODY, cubes[ELEVATOR_BODY].getIndexCount(), 0);

    //ELEVATOR_INSIDE:
    TextureManager::enable(shaders[REF], textures[SILVER4], textures[LIGHT_METAL_SPEC], 1);
    draw(ELEVATOR_INSIDE, cubes[ELEVATOR_INSIDE].getIndexCount(), 0);

    //BUTTOMS:
    TextureManager::enable(shaders[REF], textures[BUTTOMS_TEX], textures[LIGHT_METAL_SPEC], 1);
    draw(BUTTOMS, cubes[BUTTOMS].getIndexCount(), 0);

    //ELEVATOR_ENTRY:
    TextureManager::enable(shaders[REF], textures[SILVER4], textures[LIGHT_METAL_SPEC], 1);
    draw(ELEVATOR_ENTRY, cubes[ELEVATOR_ENTRY].getIndexCount(), 6);

    //ESC_BASE:
    TextureManager::enable(shaders[REF], textures[SILVER4], textures[LIGHT_METAL_SPEC], 1);
    draw(ESC_BASE, cubes[ESC_BASE].getIndexCount(), 6);

    shaders[REF].setFloat("alpha", 0.4f);
    shaders[REF].setFloat("refVal", 0.5f);
    //ESC_ARM:
    TextureManager::enable(shaders[REF], textures[GLASS], textures[GLASS_SPEC], 1);
    draw(ESC_ARM, cubes[ESC_ARM].getIndexCount(), 0);

    shaders[REF].setFloat("alpha", 0.3f);
    shaders[REF].setFloat("refVal", 0.2f);
    //ELEVATOR_DOOR:
    TextureManager::enable(shaders[REF], textures[GLASS], textures[GLASS_SPEC], 1);
    draw(ELEVATOR_DOOR, cubes[ELEVATOR_DOOR].getIndexCount(), 0);


    // SHOP_BLOOR:
    shaders[REF].setFloat("refVal", 0.7f);
    shaders[REF].setFloat("alpha", 0.2f);
    shaders[REF].setFloat("shininess", 128.0f);
    TextureManager::enable(shaders[REF], textures[BLOOR], textures[BLOOR_SPEC], 1);
    draw(SHOP_BLOOR, cubes[SHOP_BLOOR].getIndexCount(), 0);
    shaders[REF].setFloat("shininess", 32.0f);


    //ELEVATOR_BLOOR:
    shaders[REF].setFloat("alpha", 0.2f);
    shaders[REF].setFloat("refVal", 0.3f);
    TextureManager::enable(shaders[REF], textures[BLOOR], textures[BLOOR_SPEC], 1);
    draw(ELEVATOR_BLOOR, cubes[ELEVATOR_BLOOR].getIndexCount(), 6);
    
    shaders[REF].setFloat("alpha", 1.0f);
    shaders[REF].setFloat("refVal", 0.0f);


    refLight.numOfPoints = 0;
    refLight.turnOnPoint();




    //-------------------------------------------------------------------------------------------
    
    
}

void Renderer::escUp(Camera& camera){
    camera.Position.x+=5.0f;
    camera.Position.y+=3.25f;
    cntGoingUpUsingESC--;
}

void Renderer::escDown(Camera& camera){
    camera.Position.x-=5.0f;
    camera.Position.y-=3.25f;
    cntGoingDownUsingESC--;
}

void Renderer::turnEscOn(){
    if(cntEsc==0){
        vector<mat4> curPositons;
        for(int i=1; i<36; i++){
            curPositons.push_back(models[ESCALATOR][i]);
        }
        mat4 appModel = mat4(1.0f);
        appModel = translate(appModel, vec3(470.0f, 320.0f, 3000.0f));
        appModel = scale(appModel, vec3(0.1f, 0.1f, 0.6f));
        models[ESCALATOR][35] = appModel;
        for(int i=0; i<35; i++){
            models[ESCALATOR][i] = curPositons[i];
        }
    }
    for(int i=0; i<36; i++){
        models[ESCALATOR][i] = translate(models[ESCALATOR][i], vec3(-10.0f, -6.5f, 0.0f));
    }
    cubeBuffers(ESCALATOR);
}


void Renderer::turnEsc2On(){
    if(cntEsc==0){
        vector<mat4> curPositons;
        for(int i=0; i<35; i++){
            curPositons.push_back(models[ESCALATOR2][i]);
        }
        mat4 appModel = mat4(1.0f);
        appModel = translate(appModel, vec3(-1500.0f, -970.0f, 4000.0f));
        appModel = scale(appModel, vec3(0.1f, 0.1f, 0.6f));
        models[ESCALATOR2][0] = appModel;
        for(int i=0; i<35; i++){
            models[ESCALATOR2][i+1] = curPositons[i];
        }
    }
    for(int i=0; i<36; i++){
        models[ESCALATOR2][i] = translate(models[ESCALATOR2][i], vec3(10.0f, 6.5f, 0.0f));
    }
    cubeBuffers(ESCALATOR2);
}


void Renderer::draw(string objectName, int numOfVertices, int offset)
{
    vaos[objectName].Bind(); ebos[objectName].Bind();
    glDrawElementsInstanced(GL_TRIANGLES, numOfVertices, GL_UNSIGNED_INT, (void*)(offset*sizeof(float)), models[objectName].size());  

}


void Renderer::draw3Dmodel(string name, int startIndex, int endIndex)
{
    if(endIndex==1e9) endIndex = threeDModels[name].meshes.size();
    for (int i = startIndex; i < endIndex; i++)
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

void Renderer::eleUp(Camera& camera){
    //BUTTOMS, ELEVATOR_INSIDE, ELEVATOR_BODY should move up:
    models[BUTTOMS][0] = translate(models[BUTTOMS][0], vec3(0.0f, 3.0f, 0.0f));
    models[ELEVATOR_INSIDE][0] = translate(models[ELEVATOR_INSIDE][0], vec3(0.0f, 3.0f/8.1f, 0.0f));
    models[ELEVATOR_BODY][0] = translate(models[ELEVATOR_BODY][0], vec3(0.0f, 3.0f/0.2f, 0.0f));
    models[ELEVATOR_BODY][1] = translate(models[ELEVATOR_BODY][1], vec3(0.0f, 3.0f/3.0f, 0.0f));
    cubeBuffers(BUTTOMS);
    cubeBuffers(ELEVATOR_BODY);
    cubeBuffers(ELEVATOR_INSIDE);

    //update camera position:
    camera.Position.y+=3.058f;
}

void Renderer::eleDown(Camera& camera){
    models[BUTTOMS][0] = translate(models[BUTTOMS][0], vec3(0.0f, -3.0f, 0.0f));
    models[ELEVATOR_INSIDE][0] = translate(models[ELEVATOR_INSIDE][0], vec3(0.0f, -3.0f/8.1f, 0.0f));
    models[ELEVATOR_BODY][0] = translate(models[ELEVATOR_BODY][0], vec3(0.0f, -3.0f/0.2f, 0.0f));
    models[ELEVATOR_BODY][1] = translate(models[ELEVATOR_BODY][1], vec3(0.0f, -3.0f/3.0f, 0.0f));
    cubeBuffers(BUTTOMS);
    cubeBuffers(ELEVATOR_BODY);
    cubeBuffers(ELEVATOR_INSIDE);

    //update camera position:
    camera.Position.y-=3.058f;
}

void Renderer::closeEleDoor(){
    for(int i=0; i<6; i+=2) 
        models[ELEVATOR_DOOR][i] = translate(models[ELEVATOR_DOOR][i], vec3(0.0f, 0.0f, 1.05f));
    for(int i=1; i<6; i+=2) 
        models[ELEVATOR_DOOR][i] = translate(models[ELEVATOR_DOOR][i], vec3(0.0f, 0.0f, -1.05f)); 
    cubeBuffers(ELEVATOR_DOOR);
}

void Renderer::openEleDoor(){
    for(int i=0; i<6; i+=2) 
        models[ELEVATOR_DOOR][i] = translate(models[ELEVATOR_DOOR][i], vec3(0.0f, 0.0f, -1.05f));
    for(int i=1; i<6; i+=2) 
        models[ELEVATOR_DOOR][i] = translate(models[ELEVATOR_DOOR][i], vec3(0.0f, 0.0f, 1.05f)); 
    cubeBuffers(ELEVATOR_DOOR);

}


unsigned int Renderer::loadMallCubemap() {
    static const std::vector<std::string> faces = {
        "../resources/objects/Mall Cubemap/right.jpg",
        "../resources/objects/Mall Cubemap/left.jpg",
        "../resources/objects/Mall Cubemap/top.jpg",
        "../resources/objects/Mall Cubemap/bottom.jpg",
        "../resources/objects/Mall Cubemap/front.jpg",
        "../resources/objects/Mall Cubemap/back.jpg"
};
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

