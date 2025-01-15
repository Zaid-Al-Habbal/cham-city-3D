#include "App/Scene.h"

#define PB   push_back

using namespace glm;

Scene::Scene()
{
    const glm::mat4 MODEL(1.0f);
    const glm::vec3 X(1.0f, 0.0f, 0.0f), Y(0.0f, 1.0f, 0.0f), Z(0.0f, 0.0f, 1.0f);
    mat4 appModel = MODEL;

    //SPECIAL_BUILDING:
    //..Left:
    cubes[SPECIAL_BUILDING] = Cubesphere(1000.0f, 1,false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4000.0f, 1050.0f, 4100.0f));
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(2.0f, 3.57f, 2*3.5f));
    mat curModel = appModel;
    models[SPECIAL_BUILDING].PB(appModel);
    //..right:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9450.0f, 1050.0f, -2940.0f));
    appModel = rotate(appModel, radians(270.0f), Y);
    appModel = scale(appModel, vec3(1.5*1.0f, 3.57f, 1.2*2*2.0f));
    models[SPECIAL_BUILDING].PB(appModel);
    //..center:
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2050.0f));
    models[SPECIAL_BUILDING].PB(appModel);
    //..back-left:
    appModel = translate(appModel, vec3(8270.0f, 50.0f, 1000.0f));
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(2.0f, 1.16f, 3.1f));
    models[SPECIAL_BUILDING].PB(appModel);
    //..back-right:
    appModel = translate(curModel, vec3(8690.0f, -65.0f, 200.0f));
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.12f, 1.50f));
    models[SPECIAL_BUILDING].PB(appModel);

    cubeBuffers(SPECIAL_BUILDING);

    //SPECIAL_VIEW:
    //..Left:
    cylinders[SPECIAL_VIEW] = Cylinder(2200*1.0f, 2200*1.0f, 1000*1.0f, 3, 10, false, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(5305.0f, 1375.0f, 4110.0f));
    appModel = rotate(appModel, radians(95.0f), Z);
    appModel = scale(appModel, vec3(0.82f, 0.1f, 2*4.05f));
    models[SPECIAL_VIEW].PB(appModel);
    //..center:
    appModel = MODEL;
    appModel = translate(appModel, vec3(400.0f, 1370.0f, -3945.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = rotate(appModel, radians(86.0f), Z);
    appModel = scale(appModel, vec3(0.82f, 0.1f, 1.2*2*2.31f));
    models[SPECIAL_VIEW].PB(appModel);
    //..right:
    appModel = translate(appModel, vec3(0.0f, 0.0f, 1770.0f));
    models[SPECIAL_VIEW].PB(appModel);

    cylinderBuffers(SPECIAL_VIEW);

    //ROOF BUILDING:
    toruses[ROOF_BUILDING] = Torus(1.0f, 0.3f, 4, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4500.0, 3600.0, 3250.0));
    appModel = scale(appModel, vec3(2.2*4250.0f, 2500.0f, 1.65*3800.0f));
    appModel = rotate(appModel, radians(45.0f), Y);
    models[ROOF_BUILDING].PB(appModel);
    torusBuffers(ROOF_BUILDING);

    //CYL_BUILDING:
    cylinders[CYL_BUILDING] = Cylinder(1250*1.0f, 1250*1.0f, 1700*2.0f, 12, 1, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4020.0, 1100.0, -1150.0));
    appModel = rotate(appModel, radians(-220.0f), Y);
    models[CYL_BUILDING].PB(appModel);
    cylinderBuffers(CYL_BUILDING);

    //CYL_ADDITIONAL:
    cylinders[CYL_ADDITIONAL] = Cylinder(1250*1.0f, 1250*1.0f, 150*2.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4020.0, 2965.0, -1150.0));
    appModel = rotate(appModel, radians(-200.0f), Y);
    models[CYL_ADDITIONAL].PB(appModel);

    appModel = translate(appModel, vec3(0.0f, -3720.0f, 0.0f));
    appModel = scale(appModel, vec3(1.0f, 1.2f, 1.0f));
    models[CYL_ADDITIONAL].PB(appModel);

    cylinderBuffers(CYL_ADDITIONAL);

    //GLASS_ROOF:
    cubes[GLASS_ROOF] = Cubesphere(1000.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4530.0f, 3450.0f, 3200.0f));
    appModel = scale(appModel, vec3(8.1f, 0.1f, 5.45f));
    models[GLASS_ROOF].PB(appModel);
    cubeBuffers(GLASS_ROOF);

    //ENTRY:
    toruses[ENTRY] = Torus(1200*1.6f, 1200*0.5f, 4, 7, false, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4550.0f, 100.0f, -2220.0f));
    appModel = rotate(appModel, radians(10.0f), X);
    appModel = scale(appModel, vec3(1.252f, 2.3f, 1.0f));
    appModel = rotate(appModel, radians(45.0f), Z);
    models[ENTRY].PB(appModel);
    torusBuffers(ENTRY);

    //ENTRY_BLOOR:
    cubes[ENTRY_BLOOR] = Cubesphere(1000.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4550.0f, 1350.0f, -2520.0f));
    appModel = rotate(appModel, radians(10.0f), X);
    appModel = scale(appModel, vec3(2.6f, 2.2f, 0.04f));
    models[ENTRY_BLOOR].PB(appModel);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-3600.0f, -380.0f, -2830.0f));
    appModel = scale(appModel, vec3(0.7f, 0.85f, 0.04f));
    models[ENTRY_BLOOR].PB(appModel);
    appModel = translate(appModel, vec3(-2600.0f, 0.0f, 0.0f));
    models[ENTRY_BLOOR].PB(appModel);

    cubeBuffers(ENTRY_BLOOR);

    //MALL_DOOR
    cubes[MALL_DOOR] = Cubesphere(1000.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4220.0f, -380.0f, -2770.0f));
    appModel = scale(appModel, vec3(0.5f, 0.85f, 0.04f));
    models[MALL_DOOR].PB(appModel);
    appModel = translate(appModel, vec3(-1170.0f, 0.0f, 0.0f));
    models[MALL_DOOR].PB(appModel);
    models[MALL_DOOR].resize(2);
    cubeBuffers(MALL_DOOR);

    //SIDE_WALK:
    cubes[SIDE_WALK] = Cubesphere(1000.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4200.0f, -1070.0f, -5020.0f));
    curModel = appModel; 
    appModel = scale(appModel, vec3(23.15f, 0.15f, 3.8f)); 
    models[SIDE_WALK].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -0.0f, 4120.0f));
    models[SIDE_WALK].PB(appModel);
    appModel = translate(appModel, vec3(430.0f, 0.0f, -2056.0f));
    appModel = scale(appModel, vec3(0.25f, 1.0f, 2.57f)); 
    models[SIDE_WALK].PB(appModel);
    appModel = translate(appModel, vec3(-3450.0f, 0.0f, 0.0f));
    models[SIDE_WALK].PB(appModel);

    cubeBuffers(SIDE_WALK); 

    //*********************************************************************************************** */
    //INSIDE THE MALL:::::::

    //GROUND:
    cubes[GROUND] = Cubesphere(5000.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4950.0f, -965.0f, 3860.0f));
    appModel = scale(appModel, vec3(2.7f, 0.01f, 2.3f));
    models[GROUND].PB(appModel);
    cubeBuffers(GROUND); 

    //SUITE_SHOP:
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    //Ground Floor:+++++++++++++++++++++++++++++++++++++++++++++++++
    cubes[SUITE_SHOP] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f, -300.0f, -2850.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 2.1f, 9.2f)); 
    models[SUITE_SHOP].PB(appModel);
    cubeBuffers(SUITE_SHOP);

    //SUITE_GROUND
    cubes[SUITE_GROUND] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f, -900.0f, -2850.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 0.005f, 9.2f)); 
    models[SUITE_GROUND].PB(appModel);
    cubes[SUITE_GROUND].reverseNormals();
    cubeBuffers(SUITE_GROUND);

    //CIRCLE_LIGHT:
    cylinders[CIRCLE_LIGHT] = Cylinder(60.0f, 60.0f, 10.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(0.0f, 280.0f, -2900.0f));
    models[CIRCLE_LIGHT].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT].PB(appModel);
    appModel = translate(appModel, vec3(3000.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT].PB(appModel);
    cylinderBuffers(CIRCLE_LIGHT);

    //CLOTHS_PLACE:
    cylinders[CLOTHS_PLACE] = Cylinder(10.0f, 10.0f, 3600.0f, 36, 1, true, 1);
    appModel = MODEL;
    appModel = translate(appModel, vec3(400.0f, -500.0f, -3555.0f));
    models[CLOTHS_PLACE].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 800.0f));
    models[CLOTHS_PLACE].PB(appModel);
    cylinderBuffers(CLOTHS_PLACE);

    //First Line:
    //SUITE1_OBJ:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1350.0f, -710.0f, -3550.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SUITE1_OBJ].PB(appModel);
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SUITE1_OBJ].PB(appModel);
    }

    //SUITE2_OBJ:
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SUITE2_OBJ].PB(appModel);
    }

    //Second Line:
    //SUITE2_OBJ:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1350.0f, -710.0f, -2750.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SUITE2_OBJ].PB(appModel);

    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SUITE2_OBJ].PB(appModel);
    }

    //SUITE1_OBJ:
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SUITE1_OBJ].PB(appModel);
    }
    squareBuffers(SUITE1_OBJ);
    squareBuffers(SUITE2_OBJ);

    //CASHIER:
    cubes[CASHIER] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f, -710.0f, -3050.0f));
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.4f, 4.0f));
    models[CASHIER].PB(appModel);
    cubeBuffers(CASHIER);

    //SCREEN:
    cubes[SCREEN] =Cubesphere(50.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f, -460.0f, -3050.0f));
    appModel = rotate(appModel, radians(189.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //MIRROR:
    cubes[MIRROR] = Cubesphere(100.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2940.0f, -350.0f, -3050.0f));
    appModel = rotate(appModel, radians(180.0f), Z);
    appModel = scale(appModel, vec3(0.1f, 8.0f, 4.0f));
    models[MIRROR].PB(appModel);
    cubeBuffers(MIRROR);

    //SHOP_BLOOR
    cubes[SHOP_BLOOR] = Cubesphere(100.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(550.0f, -280.0f, -2000.0f));
    appModel = scale(appModel, vec3(41.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2080.0f, 50.0f, -2000.0f));
    appModel = scale(appModel, vec3(4.4f, 4.0f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    cubeBuffers(SHOP_BLOOR);
    
    //Second Floor:+++++++++++++++++++++++++++++++++++++++++++++++++
    cubes[SUITE_SHOP] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f, -300.0f + 1300.0f, -2850.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 2.1f, 9.2f)); 
    models[SUITE_SHOP].PB(appModel);
    cubeBuffers(SUITE_SHOP);

    //SUITE_GROUND
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f, -900.0f + 1300.0f, -2850.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 0.005f, 9.2f)); 
    models[SUITE_GROUND].PB(appModel);
    cubeBuffers(SUITE_GROUND);

    //CIRCLE_LIGHT:
    cylinders[CIRCLE_LIGHT] = Cylinder(60.0f, 60.0f, 10.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(0.0f, 280.0f + 1300.0f, -2900.0f));
    models[CIRCLE_LIGHT].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT].PB(appModel);
    appModel = translate(appModel, vec3(3000.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT].PB(appModel);
    cylinderBuffers(CIRCLE_LIGHT);

    //CLOTHS_PLACE:
    cylinders[CLOTHS_PLACE] = Cylinder(10.0f, 10.0f, 3600.0f, 36, 1, true, 1);
    appModel = MODEL;
    appModel = translate(appModel, vec3(400.0f, -500.0f+ 1300.0f, -3555.0f));
    models[CLOTHS_PLACE].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 800.0f));
    models[CLOTHS_PLACE].PB(appModel);
    cylinderBuffers(CLOTHS_PLACE);

    //First Line:
    //SUITE1_OBJ:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1350.0f, -710.0f+ 1300.0f, -3550.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SUITE1_OBJ].PB(appModel);
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SUITE1_OBJ].PB(appModel);
    }

    //SUITE2_OBJ:
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SUITE2_OBJ].PB(appModel);
    }

    //Second Line:
    //SUITE2_OBJ:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1350.0f, -710.0f+ 1300.0f, -2750.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SUITE2_OBJ].PB(appModel);

    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SUITE2_OBJ].PB(appModel);
    }

    //SUITE1_OBJ:
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SUITE1_OBJ].PB(appModel);
    }
    squareBuffers(SUITE1_OBJ);
    squareBuffers(SUITE2_OBJ);

    //CASHIER:
    cubes[CASHIER] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f, -710.0f+ 1300.0f, -3050.0f));
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.4f, 4.0f));
    models[CASHIER].PB(appModel);
    cubeBuffers(CASHIER);

    //SCREEN:
    cubes[SCREEN] =Cubesphere(50.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f, -460.0f+ 1300.0f, -3050.0f));
    appModel = rotate(appModel, radians(189.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //MIRROR:
    cubes[MIRROR] = Cubesphere(100.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2940.0f, -350.0f+ 1300.0f, -3050.0f));
    appModel = rotate(appModel, radians(180.0f), Z);
    appModel = scale(appModel, vec3(0.1f, 8.0f, 4.0f));
    models[MIRROR].PB(appModel);
    cubeBuffers(MIRROR);

    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(550.0f, -280.0f+ 1300.0f, -2000.0f));
    appModel = scale(appModel, vec3(41.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2080.0f, 50.0f+ 1300.0f, -2000.0f));
    appModel = scale(appModel, vec3(4.4f, 4.0f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    cubeBuffers(SHOP_BLOOR);

    //First Floor:+++++++++++++++++++++++++++++++++++++++++++++++++
    cubes[SUITE_SHOP] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f, -300.0f + 2600.0f, -2850.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 2.1f, 9.2f)); 
    models[SUITE_SHOP].PB(appModel);
    cubeBuffers(SUITE_SHOP);

    //SUITE_GROUND
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f, -900.0f + 2600.0f, -2850.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 0.005f, 9.2f)); 
    models[SUITE_GROUND].PB(appModel);
    cubeBuffers(SUITE_GROUND);

    //CIRCLE_LIGHT:
    cylinders[CIRCLE_LIGHT] = Cylinder(60.0f, 60.0f, 10.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(0.0f, 280.0f + 2600.0f, -2900.0f));
    models[CIRCLE_LIGHT].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT].PB(appModel);
    appModel = translate(appModel, vec3(3000.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT].PB(appModel);
    cylinderBuffers(CIRCLE_LIGHT);

    //CLOTHS_PLACE:
    cylinders[CLOTHS_PLACE] = Cylinder(10.0f, 10.0f, 3600.0f, 36, 1, true, 1);
    appModel = MODEL;
    appModel = translate(appModel, vec3(400.0f, -500.0f+ 2600.0f, -3555.0f));
    models[CLOTHS_PLACE].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 800.0f));
    models[CLOTHS_PLACE].PB(appModel);
    cylinderBuffers(CLOTHS_PLACE);

    //First Line:
    //SUITE1_OBJ:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1350.0f, -710.0f+ 2600.0f, -3550.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SUITE1_OBJ].PB(appModel);
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SUITE1_OBJ].PB(appModel);
    }

    //SUITE2_OBJ:
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SUITE2_OBJ].PB(appModel);
    }

    //Second Line:
    //SUITE2_OBJ:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1350.0f, -710.0f+ 2600.0f, -2750.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SUITE2_OBJ].PB(appModel);

    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SUITE2_OBJ].PB(appModel);
    }

    //SUITE1_OBJ:
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SUITE1_OBJ].PB(appModel);
    }
    squareBuffers(SUITE1_OBJ);
    squareBuffers(SUITE2_OBJ);

    //CASHIER:
    cubes[CASHIER] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f, -710.0f+ 2600.0f, -3050.0f));
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.4f, 4.0f));
    models[CASHIER].PB(appModel);
    cubeBuffers(CASHIER);

    //SCREEN:
    cubes[SCREEN] =Cubesphere(50.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f, -460.0f+ 2600.0f, -3050.0f));
    appModel = rotate(appModel, radians(189.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //MIRROR:
    cubes[MIRROR] = Cubesphere(100.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2940.0f, -350.0f+ 2600.0f, -3050.0f));
    appModel = rotate(appModel, radians(180.0f), Z);
    appModel = scale(appModel, vec3(0.1f, 8.0f, 4.0f));
    models[MIRROR].PB(appModel);
    cubeBuffers(MIRROR);

    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(550.0f, -280.0f+ 2600.0f, -2000.0f));
    appModel = scale(appModel, vec3(41.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2080.0f, 50.0f+ 2600.0f, -2000.0f));
    appModel = scale(appModel, vec3(4.4f, 4.0f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    cubeBuffers(SHOP_BLOOR);


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    
    //SHIRT_SHOP:::::::::::::::::::::::

    //Ground Floor:+++++++++++++++++++++++++++++++++++++++++++++++++
    cubes[SHIRT_SHOP] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f, -300.0f, 10300.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 2.1f, 9.2f)); 
    models[SHIRT_SHOP].PB(appModel);
    cubeBuffers(SHIRT_SHOP);

    //SHIRT_GROUND
    cubes[SHIRT_GROUND] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f, -900.0f, 10300.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 0.005f, 9.2f)); 
    models[SHIRT_GROUND].PB(appModel);
    cubes[SHIRT_GROUND].reverseNormals();
    cubeBuffers(SHIRT_GROUND);

    //CIRCLE_LIGHT_2:
    cylinders[CIRCLE_LIGHT_2] = Cylinder(60.0f, 60.0f, 10.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(0.0f, 280.0f, 10250.0f));
    models[CIRCLE_LIGHT_2].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT_2].PB(appModel);
    appModel = translate(appModel, vec3(3000.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT_2].PB(appModel);
    cylinderBuffers(CIRCLE_LIGHT_2);

    //CLOTHS_PLACE_2:
    cylinders[CLOTHS_PLACE_2] = Cylinder(10.0f, 10.0f, 3600.0f, 36, 1, true, 1);
    appModel = MODEL;
    appModel = translate(appModel, vec3(400.0f, -500.0f, -3555.0f + 13150.0f));
    models[CLOTHS_PLACE_2].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 800.0f));
    models[CLOTHS_PLACE_2].PB(appModel);
    cylinderBuffers(CLOTHS_PLACE_2);

    //First Line:
    //SHIRT1_OBJ:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1350.0f, -710.0f, -3550.0f + 13150.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SHIRT1_OBJ].PB(appModel);
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SHIRT1_OBJ].PB(appModel);
    }

    //SHIRT2_OBJ:
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SHIRT2_OBJ].PB(appModel);
    }

    //Second Line:
    //SHIRT2_OBJ:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1350.0f, -710.0f, -2750.0f + 13150.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SHIRT2_OBJ].PB(appModel);

    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SHIRT2_OBJ].PB(appModel);
    }

    //SHIRT1_OBJ:
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SHIRT1_OBJ].PB(appModel);
    }
    squareBuffers(SHIRT1_OBJ);
    squareBuffers(SHIRT2_OBJ);

    //CASHIER2:
    cubes[CASHIER2] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f, -710.0f, -3050.0f + 13550.0f));
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.4f, 4.0f));
    models[CASHIER2].PB(appModel);
    cubeBuffers(CASHIER2);

    //SCREEN:
    cubes[SCREEN] =Cubesphere(50.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f, -460.0f, -3050.0f + 13550.0f));
    appModel = rotate(appModel, radians(189.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //MIRROR2:
    cubes[MIRROR2] = Cubesphere(100.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2940.0f, -350.0f, -3050.0f + 13150.0f));
    appModel = rotate(appModel, radians(180.0f), Z);
    appModel = scale(appModel, vec3(0.1f, 8.0f, 4.0f));
    models[MIRROR2].PB(appModel);
    cubeBuffers(MIRROR2);

    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(550.0f, -280.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(41.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2080.0f, 50.0f, -2000.0f + 11450.0f));
    appModel = scale(appModel, vec3(4.4f, 4.0f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    cubeBuffers(SHOP_BLOOR);

    //First Floor:+++++++++++++++++++++++++++++++++++++++++++++++++

    cubes[SHIRT_SHOP] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f, -300.0f + 1300.0f, 10300.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 2.1f, 9.2f)); 
    models[SHIRT_SHOP].PB(appModel);
    cubeBuffers(SHIRT_SHOP);

    //SHIRT_GROUND
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f, -900.0f + 1300.0f, 10300.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 0.005f, 9.2f)); 
    models[SHIRT_GROUND].PB(appModel);
    cubeBuffers(SHIRT_GROUND);

    //CIRCLE_LIGHT_2:
    cylinders[CIRCLE_LIGHT_2] = Cylinder(60.0f, 60.0f, 10.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(0.0f, 280.0f + 1300.0f, 10250.0f));
    models[CIRCLE_LIGHT_2].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT_2].PB(appModel);
    appModel = translate(appModel, vec3(3000.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT_2].PB(appModel);
    cylinderBuffers(CIRCLE_LIGHT_2);

    //CLOTHS_PLACE_2:
    cylinders[CLOTHS_PLACE_2] = Cylinder(10.0f, 10.0f, 3600.0f, 36, 1, true, 1);
    appModel = MODEL;
    appModel = translate(appModel, vec3(400.0f, -500.0f+ 1300.0f, -3555.0f + 13150.0f));
    models[CLOTHS_PLACE_2].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 800.0f));
    models[CLOTHS_PLACE_2].PB(appModel);
    cylinderBuffers(CLOTHS_PLACE_2);

    //First Line:
    //SHIRT1_OBJ:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1350.0f, -710.0f+ 1300.0f, -3550.0f + 13150.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SHIRT1_OBJ].PB(appModel);
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SHIRT1_OBJ].PB(appModel);
    }

    //SHIRT2_OBJ:
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SHIRT2_OBJ].PB(appModel);
    }

    //Second Line:
    //SHIRT2_OBJ:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1350.0f, -710.0f+ 1300.0f, -2750.0f + 13150.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SHIRT2_OBJ].PB(appModel);

    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SHIRT2_OBJ].PB(appModel);
    }

    //SHIRT1_OBJ:
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SHIRT1_OBJ].PB(appModel);
    }
    squareBuffers(SHIRT1_OBJ);
    squareBuffers(SHIRT2_OBJ);

    //CASHIER2:
    cubes[CASHIER2] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f, -710.0f+ 1300.0f, -3050.0f + 13550.0f));
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.4f, 4.0f));
    models[CASHIER2].PB(appModel);
    cubeBuffers(CASHIER2);

    //SCREEN:
    cubes[SCREEN] =Cubesphere(50.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f, -460.0f+ 1300.0f, -3050.0f + 13550.0f));
    appModel = rotate(appModel, radians(189.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //MIRROR2:
    cubes[MIRROR2] = Cubesphere(100.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2940.0f, -350.0f+ 1300.0f, -3050.0f + 13150.0f));
    appModel = rotate(appModel, radians(180.0f), Z);
    appModel = scale(appModel, vec3(0.1f, 8.0f, 4.0f));
    models[MIRROR2].PB(appModel);
    cubeBuffers(MIRROR2);

    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(550.0f, -280.0f+ 1300.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(41.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2080.0f, 50.0f+ 1300.0f, -2000.0f + 11450.0f));
    appModel = scale(appModel, vec3(4.4f, 4.0f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    cubeBuffers(SHOP_BLOOR);

    //Second Floor:+++++++++++++++++++++++++++++++++++++++++++++++++

    cubes[SHIRT_SHOP] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f, -300.0f + 2600.0f, 10300.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 2.1f, 9.2f)); 
    models[SHIRT_SHOP].PB(appModel);
    cubeBuffers(SHIRT_SHOP);

    //SHIRT_GROUND
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f, -900.0f + 2600.0f, 10300.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 0.005f, 9.2f)); 
    models[SHIRT_GROUND].PB(appModel);
    cubeBuffers(SHIRT_GROUND);

    //CIRCLE_LIGHT_2:
    cylinders[CIRCLE_LIGHT_2] = Cylinder(60.0f, 60.0f, 10.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(0.0f, 280.0f + 2600.0f, 10250.0f));
    models[CIRCLE_LIGHT_2].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT_2].PB(appModel);
    appModel = translate(appModel, vec3(3000.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT_2].PB(appModel);
    cylinderBuffers(CIRCLE_LIGHT_2);

    //CLOTHS_PLACE_2:
    cylinders[CLOTHS_PLACE_2] = Cylinder(10.0f, 10.0f, 3600.0f, 36, 1, true, 1);
    appModel = MODEL;
    appModel = translate(appModel, vec3(400.0f, -500.0f+ 2600.0f, -3555.0f + 13150.0f));
    models[CLOTHS_PLACE_2].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 800.0f));
    models[CLOTHS_PLACE_2].PB(appModel);
    cylinderBuffers(CLOTHS_PLACE_2);

    //First Line:
    //SHIRT1_OBJ:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1350.0f, -710.0f+ 2600.0f, -3550.0f + 13150.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SHIRT1_OBJ].PB(appModel);
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SHIRT1_OBJ].PB(appModel);
    }

    //SHIRT2_OBJ:
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SHIRT2_OBJ].PB(appModel);
    }

    //Second Line:
    //SHIRT2_OBJ:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1350.0f, -710.0f+ 2600.0f, -2750.0f + 13150.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SHIRT2_OBJ].PB(appModel);

    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SHIRT2_OBJ].PB(appModel);
    }

    //SHIRT1_OBJ:
    for(int i=0; i<70; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[SHIRT1_OBJ].PB(appModel);
    }
    squareBuffers(SHIRT1_OBJ);
    squareBuffers(SHIRT2_OBJ);

    //CASHIER2:
    cubes[CASHIER2] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f, -710.0f+ 2600.0f, -3050.0f + 13550.0f));
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.4f, 4.0f));
    models[CASHIER2].PB(appModel);
    cubeBuffers(CASHIER2);

    //SCREEN:
    cubes[SCREEN] =Cubesphere(50.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f, -460.0f+ 2600.0f, -3050.0f + 13550.0f));
    appModel = rotate(appModel, radians(189.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //MIRROR2:
    cubes[MIRROR2] = Cubesphere(100.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2940.0f, -350.0f+ 2600.0f, -3050.0f + 13150.0f));
    appModel = rotate(appModel, radians(180.0f), Z);
    appModel = scale(appModel, vec3(0.1f, 8.0f, 4.0f));
    models[MIRROR2].PB(appModel);
    cubeBuffers(MIRROR2);

    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(550.0f, -280.0f+ 2600.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(41.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2080.0f, 50.0f+ 2600.0f, -2000.0f + 11450.0f));
    appModel = scale(appModel, vec3(4.4f, 4.0f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    cubeBuffers(SHOP_BLOOR);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //SHOES_SHOP:::::::::::::::::::::::::::::::

    //Ground Floor:+++++++++++++++++++++++++++++++++++++++++++++++++
    cubes[SHOES_SHOP] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f - 5350.0f, -300.0f, 10300.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 2.1f, 9.2f)); 
    models[SHOES_SHOP].PB(appModel);
    cubeBuffers(SHOES_SHOP);

    //SHOES_GROUND
    cubes[SHOES_GROUND] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f- 5350.0f, -900.0f, 10300.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 0.005f, 9.2f)); 
    models[SHOES_GROUND].PB(appModel);
    cubes[SHOES_GROUND].reverseNormals();
    cubeBuffers(SHOES_GROUND);

    //SQUARE_LIGHT:
    cubes[SQUARE_LIGHT] = Cubesphere(200.0f, 1, true);
    cubes[SQUARE_LIGHT].reverseNormals();
    appModel = MODEL;
    appModel = translate(appModel, vec3(0.0f - 5350.0f, 280.0f, 10250.0f));
    appModel = scale(appModel, vec3(1.2f, 0.1f, 1.2f));
    models[SQUARE_LIGHT].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[SQUARE_LIGHT].PB(appModel);
    appModel = translate(appModel, vec3(3000.0f, 0.0f, 0.0f));
    models[SQUARE_LIGHT].PB(appModel);
    cubeBuffers(SQUARE_LIGHT);

    

    //CASHIER3:
    cubes[CASHIER3] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f- 3350.0f, -710.0f, -3050.0f + 13550.0f));
    appModel = rotate(appModel, radians(270.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.4f, 4.0f));
    models[CASHIER3].PB(appModel);
    cubeBuffers(CASHIER3);

    //SCREEN:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f- 3350.0f, -460.0f, -3050.0f + 13550.0f));
    appModel = rotate(appModel, radians(278.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);


    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(100.0f- 3350.0f, -280.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-3450.0f- 3350.0f, -280.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1670.0f- 3350.0f, 150.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.6f, 2.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    
    cubeBuffers(SHOP_BLOOR);


    //SMALL_ROOF:
    cubes[SMALL_ROOF] = Cubesphere(100.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1600.0f- 3350.0f, 20.0f, -300.0f +  11450.0f));
    appModel = scale(appModel, vec3(40.0f, 0.4f, 0.5f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);
    //LEFT SMALL_ROOF:
    appModel = MODEL;
    appModel = translate(appModel, vec3(950.0f- 3350.0f, 20.0f, -1000.0f +  11450.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(10.0f, 0.4f, 0.5f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);

    //RIGHT:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4300.0f- 3350.0f, 20.0f, -1000.0f +  11450.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(10.0f, 0.4f, 0.5f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);
    cubeBuffers(SMALL_ROOF);

    //SHOE1 SHOE2 SHOE3
    appModel = MODEL;
    appModel = translate(appModel, vec3(600.0f- 3350.0f, 130.0f, -300.0f +  11450.0f));
    appModel = scale(appModel, vec3(200.0f, 200.0f, 100.0f));
    models[SHOE1].PB(appModel);
    curModel = translate(appModel, vec3(-2.0f, 0.0f, 0.0f));
    models[SHOE2].PB(curModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE1].PB(appModel);
        curModel = translate(curModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE2].PB(curModel);
    }
    appModel = MODEL;
    appModel = translate(appModel, vec3(600.0f- 3350.0f, -150.0f, -300.0f +  11450.0f));
    appModel = scale(appModel, vec3(200.0f, 200.0f, 100.0f));
    curModel = translate(appModel, vec3(-2.0f, 0.0f, 0.0f));
    models[SHOE2].PB(curModel);
    models[SHOE3].PB(appModel);
    for(int i=0; i<5; i++){
        curModel = translate(curModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE2].PB(curModel);
        appModel = translate(appModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE3].PB(appModel);
    }
    appModel = MODEL;
    appModel = translate(appModel, vec3(600.0f- 3350.0f, -430.0f, -300.0f +  11450.0f));
    appModel = scale(appModel, vec3(200.0f, 200.0f, 100.0f));
    curModel = translate(appModel, vec3(-2.0f, 0.0f, 0.0f));
    models[SHOE1].PB(curModel);
    models[SHOE3].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE3].PB(appModel);
        curModel = translate(curModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE1].PB(curModel);
    }
    //SHOE4:
    threeDModels[SHOE4] = Model("../resources/objects/scanned-adidas-sports-shoe/source/model/Mesh.obj");
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2400.0f, 70.0f, 10000.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(300.0f, 300.0f, 300.0f));
    models[SHOE4].PB(appModel);
    for(float i=200.0f; i<1000.0f; i+=200.0f){
        appModel = MODEL;
        appModel = translate(appModel, vec3(-2400.0f, 70.0f, 10000.0f + i));
        appModel = rotate(appModel, radians(90.0f), Y);
        appModel = scale(appModel, vec3(300.0f, 300.0f, 300.0f));
        models[SHOE4].PB(appModel);
    }
    appModel = MODEL;
    appModel = translate(appModel, vec3(-7600.0f, 70.0f, 10000.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(300.0f, 300.0f, 300.0f));
    models[SHOE4].PB(appModel);
    for(float i=200.0f; i<1000.0f; i+=200.0f){
        appModel = MODEL;
        appModel = translate(appModel, vec3(-7600.0f, 70.0f, 10000.0f + i));
        appModel = rotate(appModel, radians(90.0f), Y);
        appModel = scale(appModel, vec3(300.0f, 300.0f, 300.0f));
        models[SHOE4].PB(appModel);
    }
    threeDmodelBuffers(SHOE4);

    //SHOE5:
    threeDModels[SHOE5] = Model("../resources/objects/shoes-violet/source/end1/Shoes Viola A1.obj");
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2450.0f, -220.0f, 10000.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(25.0f, 25.0f, 25.0f));
    models[SHOE5].PB(appModel);
    for(float i=200.0f; i<1000.0f; i+=200.0f){
        appModel = MODEL;
        appModel = translate(appModel, vec3(-2450.0f, -220.0f, 10000.0f + i));
        appModel = rotate(appModel, radians(90.0f), Y);
        appModel = scale(appModel, vec3(25.0f, 25.0f, 25.0f));
        models[SHOE5].PB(appModel);
    }
    appModel = MODEL;
    appModel = translate(appModel, vec3(-7600.0f, -220.0f, 10000.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(25.0f, 25.0f, 25.0f));
    models[SHOE5].PB(appModel);
    for(float i=200.0f; i<1000.0f; i+=200.0f){
        appModel = MODEL;
        appModel = translate(appModel, vec3(-7600.0f, -220.0f, 10000.0f + i));
        appModel = rotate(appModel, radians(90.0f), Y);
        appModel = scale(appModel, vec3(25.0f, 25.0f, 25.0f));
        models[SHOE5].PB(appModel);
    }
    threeDmodelBuffers(SHOE5);

    //SHOE6:
    threeDModels[SHOE6] = Model("../resources/objects/shoes-violet/source/end1/Shoes Viola A1.obj");
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2450.0f, -500.0f, 10000.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(25.0f, 25.0f, 25.0f));
    models[SHOE6].PB(appModel);
    for(float i=200.0f; i<1000.0f; i+=200.0f){
        appModel = MODEL;
        appModel = translate(appModel, vec3(-2450.0f, -500.0f, 10000.0f + i));
        appModel = rotate(appModel, radians(90.0f), Y);
        appModel = scale(appModel, vec3(25.0f, 25.0f, 25.0f));
        models[SHOE6].PB(appModel);
    }
    appModel = MODEL;
    appModel = translate(appModel, vec3(-7600.0f, -500.0f, 10000.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(25.0f, 25.0f, 25.0f));
    models[SHOE6].PB(appModel);
    for(float i=200.0f; i<1000.0f; i+=200.0f){
        appModel = MODEL;
        appModel = translate(appModel, vec3(-7600.0f, -500.0f, 10000.0f + i));
        appModel = rotate(appModel, radians(90.0f), Y);
        appModel = scale(appModel, vec3(25.0f, 25.0f, 25.0f));
        models[SHOE6].PB(appModel);
    }
    threeDmodelBuffers(SHOE6);
    
    //First Floor:+++++++++++++++++++++++++++++++++++++++++++++++++
    cubes[SHOES_SHOP] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f - 5350.0f, -300.0f + 1300.0f, 10300.0f)); 
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 2.1f, 9.2f)); 
    models[SHOES_SHOP].PB(appModel);
    cubeBuffers(SHOES_SHOP);

    //SHOES_GROUND
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f- 5350.0f, -900.0f+1300.0f, 10300.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 0.005f, 9.2f)); 
    models[SHOES_GROUND].PB(appModel);
    cubeBuffers(SHOES_GROUND);

    //SQUARE_LIGHT:
    cubes[SQUARE_LIGHT] = Cubesphere(200.0f, 1, true);
    cubes[SQUARE_LIGHT].reverseNormals();
    appModel = MODEL;
    appModel = translate(appModel, vec3(0.0f - 5350.0f, 280.0f+ 1300.0f, 10250.0f));
    appModel = scale(appModel, vec3(1.2f, 0.1f, 1.2f));
    models[SQUARE_LIGHT].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[SQUARE_LIGHT].PB(appModel);
    appModel = translate(appModel, vec3(3000.0f, 0.0f, 0.0f));
    models[SQUARE_LIGHT].PB(appModel);
    cubeBuffers(SQUARE_LIGHT);

    

    //CASHIER3:
    cubes[CASHIER3] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f- 3350.0f, -710.0f+ 1300.0f, -3050.0f + 13550.0f));
    appModel = rotate(appModel, radians(270.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.4f, 4.0f));
    models[CASHIER3].PB(appModel);
    cubeBuffers(CASHIER3);

    //SCREEN:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f- 3350.0f, -460.0f+ 1300.0f, -3050.0f + 13550.0f));
    appModel = rotate(appModel, radians(278.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);


    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(100.0f- 3350.0f, -280.0f+ 1300.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-3450.0f- 3350.0f, -280.0f+ 1300.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1670.0f- 3350.0f, 150.0f+ 1300.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.6f, 2.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    
    cubeBuffers(SHOP_BLOOR);


    //SMALL_ROOF:
    cubes[SMALL_ROOF] = Cubesphere(100.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1600.0f- 3350.0f, 20.0f+ 1300.0f, -300.0f +  11450.0f));
    appModel = scale(appModel, vec3(40.0f, 0.4f, 0.5f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);
    cubeBuffers(SMALL_ROOF);
    //LEFT SMALL_ROOF:
    appModel = MODEL;
    appModel = translate(appModel, vec3(950.0f- 3350.0f, 20.0f+1300.0f, -1000.0f +  11450.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(10.0f, 0.4f, 0.5f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);

    //RIGHT:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4300.0f- 3350.0f, 20.0f+1300.0f, -1000.0f +  11450.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(10.0f, 0.4f, 0.5f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);
    cubeBuffers(SMALL_ROOF);

    //SHOE1 SHOE2 SHOE3
    appModel = MODEL;
    appModel = translate(appModel, vec3(600.0f- 3350.0f, 130.0f+ 1300.0f, -300.0f +  11450.0f));
    appModel = scale(appModel, vec3(200.0f, 200.0f, 100.0f));
    models[SHOE1].PB(appModel);
    curModel = translate(appModel, vec3(-2.0f, 0.0f, 0.0f));
    models[SHOE2].PB(curModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE1].PB(appModel);
        curModel = translate(curModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE2].PB(curModel);
    }
    appModel = MODEL;
    appModel = translate(appModel, vec3(600.0f- 3350.0f, -150.0f+ 1300.0f, -300.0f +  11450.0f));
    appModel = scale(appModel, vec3(200.0f, 200.0f, 100.0f));
    curModel = translate(appModel, vec3(-2.0f, 0.0f, 0.0f));
    models[SHOE2].PB(curModel);
    models[SHOE3].PB(appModel);
    for(int i=0; i<5; i++){
        curModel = translate(curModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE2].PB(curModel);
        appModel = translate(appModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE3].PB(appModel);
    }
    appModel = MODEL;
    appModel = translate(appModel, vec3(600.0f- 3350.0f, -430.0f+ 1300.0f, -300.0f +  11450.0f));
    appModel = scale(appModel, vec3(200.0f, 200.0f, 100.0f));
    curModel = translate(appModel, vec3(-2.0f, 0.0f, 0.0f));
    models[SHOE1].PB(curModel);
    models[SHOE3].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE3].PB(appModel);
        curModel = translate(curModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE1].PB(curModel);
    }
    

    //Second Floor:+++++++++++++++++++++++++++++++++++++++++++++++++
    cubes[SHOES_SHOP] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f - 5350.0f, -300.0f + 2600.0f, 10300.0f)); 
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 2.1f, 9.2f)); 
    models[SHOES_SHOP].PB(appModel);
    cubeBuffers(SHOES_SHOP);

    //SHOES_GROUND
    appModel = MODEL;
    appModel = translate(appModel, vec3(320.0f- 5350.0f, -900.0f+2600.0f, 10300.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 0.005f, 9.2f)); 
    models[SHOES_GROUND].PB(appModel);
    cubeBuffers(SHOES_GROUND);

    //SQUARE_LIGHT:
    cubes[SQUARE_LIGHT] = Cubesphere(200.0f, 1, true);
    cubes[SQUARE_LIGHT].reverseNormals();
    appModel = MODEL;
    appModel = translate(appModel, vec3(0.0f - 5350.0f, 280.0f+ 2600.0f, 10250.0f));
    appModel = scale(appModel, vec3(1.2f, 0.1f, 1.2f));
    models[SQUARE_LIGHT].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[SQUARE_LIGHT].PB(appModel);
    appModel = translate(appModel, vec3(3000.0f, 0.0f, 0.0f));
    models[SQUARE_LIGHT].PB(appModel);
    cubeBuffers(SQUARE_LIGHT);

    

    //CASHIER3:
    cubes[CASHIER3] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f- 3350.0f, -710.0f+ 2600.0f, -3050.0f + 13550.0f));
    appModel = rotate(appModel, radians(270.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.4f, 4.0f));
    models[CASHIER3].PB(appModel);
    cubeBuffers(CASHIER3);

    //SCREEN:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f- 3350.0f, -460.0f+ 2600.0f, -3050.0f + 13550.0f));
    appModel = rotate(appModel, radians(278.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);


    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(100.0f- 3350.0f, -280.0f+ 2600.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-3450.0f- 3350.0f, -280.0f+ 2600.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1670.0f- 3350.0f, 150.0f+ 2600.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.6f, 2.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    
    cubeBuffers(SHOP_BLOOR);


    //SMALL_ROOF:
    cubes[SMALL_ROOF] = Cubesphere(100.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1600.0f- 3350.0f, 20.0f+ 2600.0f, -300.0f +  11450.0f));
    appModel = scale(appModel, vec3(40.0f, 0.4f, 0.5f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);
    //LEFT SMALL_ROOF:
    appModel = MODEL;
    appModel = translate(appModel, vec3(950.0f- 3350.0f, 20.0f+2600.0f, -1000.0f +  11450.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(10.0f, 0.4f, 0.5f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);

    //RIGHT:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4300.0f- 3350.0f, 20.0f+2600.0f, -1000.0f +  11450.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(10.0f, 0.4f, 0.5f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -700.0f, 0.0f));
    models[SMALL_ROOF].PB(appModel);
    cubeBuffers(SMALL_ROOF);

    //SHOE1 SHOE2 SHOE3
    appModel = MODEL;
    appModel = translate(appModel, vec3(600.0f- 3350.0f, 130.0f+ 2600.0f, -300.0f +  11450.0f));
    appModel = scale(appModel, vec3(200.0f, 200.0f, 100.0f));
    models[SHOE1].PB(appModel);
    curModel = translate(appModel, vec3(-2.0f, 0.0f, 0.0f));
    models[SHOE2].PB(curModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE1].PB(appModel);
        curModel = translate(curModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE2].PB(curModel);
    }
    appModel = MODEL;
    appModel = translate(appModel, vec3(600.0f- 3350.0f, -150.0f+ 2600.0f, -300.0f +  11450.0f));
    appModel = scale(appModel, vec3(200.0f, 200.0f, 100.0f));
    curModel = translate(appModel, vec3(-2.0f, 0.0f, 0.0f));
    models[SHOE2].PB(curModel);
    models[SHOE3].PB(appModel);
    for(int i=0; i<5; i++){
        curModel = translate(curModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE2].PB(curModel);
        appModel = translate(appModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE3].PB(appModel);
    }
    appModel = MODEL;
    appModel = translate(appModel, vec3(600.0f- 3350.0f, -430.0f+ 2600.0f, -300.0f +  11450.0f));
    appModel = scale(appModel, vec3(200.0f, 200.0f, 100.0f));
    curModel = translate(appModel, vec3(-2.0f, 0.0f, 0.0f));
    models[SHOE1].PB(curModel);
    models[SHOE3].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE3].PB(appModel);
        curModel = translate(curModel, vec3(-4.0f, 0.0f, 0.0f));
        models[SHOE1].PB(curModel);
    }
    

    squareBuffers(SHOE1);
    squareBuffers(SHOE2);
    squareBuffers(SHOE3);

    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //GROUND FLOOR::::::::::::::::::::::::::::::::::
    //DRESS_SHOP:
    cubes[DRESS_SHOP] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-5030-5300.0f, -300.0f, 10300.0f)); 
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 2.1f, 9.0f)); 
    models[DRESS_SHOP].PB(appModel);
    cubeBuffers(DRESS_SHOP);

    //DRESS_GROUND
    cubes[DRESS_GROUND] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-5030-5300.0f, -900.0f, 10300.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 0.005f, 9.0f)); 
    models[DRESS_GROUND].PB(appModel);
    cubes[DRESS_GROUND].reverseNormals();
    cubeBuffers(DRESS_GROUND);
    
    //CIRCLE_LIGHT_4:
    cylinders[CIRCLE_LIGHT_4] = Cylinder(60.0f, 60.0f, 10.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(0.0f -10650.0, 280.0f, 10250.0f));
    models[CIRCLE_LIGHT_4].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT_4].PB(appModel);
    appModel = translate(appModel, vec3(3000.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT_4].PB(appModel);
    cylinderBuffers(CIRCLE_LIGHT_4);

    //CLOTHS_PLACE_4:
    cylinders[CLOTHS_PLACE_4] = Cylinder(10.0f, 10.0f, 800.0f, 36, 1, true, 1);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-830.0f -10700.0, -300.0f, -3155.0f + 13150.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    models[CLOTHS_PLACE_4].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 900.0f));
    models[CLOTHS_PLACE_4].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 900.0f));
    models[CLOTHS_PLACE_4].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 900.0f));
    models[CLOTHS_PLACE_4].PB(appModel);
    cylinderBuffers(CLOTHS_PLACE_4);

    //DRESS:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-830.0f -10700.0, -540.0f, -3405.0f + 13150.0f));
    appModel = scale(appModel, vec3(900.0f, 600.0f, 800.0f));
    models[DRESS1].PB(appModel);
    for(int i=0; i<15; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[DRESS1].PB(appModel);
    }
    squareBuffers(DRESS1);

    appModel = MODEL;
    appModel = translate(appModel, vec3(35.0f -10700.0, -580.0f, -3405.0f + 13150.0f));
    appModel = scale(appModel, vec3(900.0f, 600.0f, 800.0f));
    models[DRESS2].PB(appModel);
    for(int i=0; i<15; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[DRESS2].PB(appModel);
    }
    squareBuffers(DRESS2);

    appModel = MODEL;
    appModel = translate(appModel, vec3(990.0f -10700.0, -480.0f, -3405.0f + 13150.0f));
    appModel = scale(appModel, vec3(900.0f, 600.0f, 800.0f));
    models[DRESS3].PB(appModel);
    for(int i=0; i<15; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[DRESS3].PB(appModel);
    }
    squareBuffers(DRESS3);

    appModel = MODEL;
    appModel = translate(appModel, vec3(1875.0f -10700.0, -480.0f, -3405.0f + 13150.0f));
    appModel = scale(appModel, vec3(900.0f, 600.0f, 800.0f));
    models[DRESS4].PB(appModel);
    for(int i=0; i<15; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[DRESS4].PB(appModel);
    }
    squareBuffers(DRESS4);

    //CASHIER4:
    cubes[CASHIER4] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f- 3350.0f - 5350.0f, -710.0f, -2750.0f + 13550.0f));
    appModel = rotate(appModel, radians(270.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.4f, 4.0f));
    models[CASHIER4].PB(appModel);
    cubeBuffers(CASHIER4);

    //SCREEN:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f- 3350.0f - 5350.0f, -460.0f, -2750.0f + 13550.0f));
    appModel = rotate(appModel, radians(120.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //DRESSING_ROOM:
    cubes[DRESSING_ROOM] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-3860.0f- 3350.0f - 5350.0f, -300.0f, -3580.0f + 13550.0f));
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 5.2f, 1.0f));
    models[DRESSING_ROOM].PB(appModel);
    cubeBuffers(DRESSING_ROOM);

    //MIRROR4:
    cubes[MIRROR4] = Cubesphere(100.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2940.0f - 10700.0f, -350.0f, -2550.0f + 13150.0f));
    appModel = rotate(appModel, radians(180.0f), Z);
    appModel = scale(appModel, vec3(0.1f, 8.0f, 4.0f));
    models[MIRROR4].PB(appModel);
    cubeBuffers(MIRROR4);

    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(100.0f- 3350.0f - 5350.0f, -280.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-3450.0f- 3350.0f - 5350.0f, -280.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1670.0f- 3350.0f - 5350.0f, 150.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.6f, 2.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    cubeBuffers(SHOP_BLOOR);

    //-----------------------------------------------------------------------------------------------------
    //FIRST FLOOR::::::::::::::::::::::::::::::::::
    //DRESS_SHOP:
    cubes[DRESS_SHOP] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-5030-5300.0f, -300.0f + 1300.0f, 10300.0f)); 
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 2.1f, 9.0f)); 
    models[DRESS_SHOP].PB(appModel);
    cubeBuffers(DRESS_SHOP);

    //DRESS_GROUND
    appModel = MODEL;
    appModel = translate(appModel, vec3(-5030-5300.0f, -900.0f + 1300.0f, 10300.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 0.005f, 9.0f)); 
    models[DRESS_GROUND].PB(appModel);
    cubeBuffers(DRESS_GROUND);
    
    //CIRCLE_LIGHT_4:
    cylinders[CIRCLE_LIGHT_4] = Cylinder(60.0f, 60.0f, 10.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(0.0f -10650.0, 280.0f+ 1300.0f, 10250.0f));
    models[CIRCLE_LIGHT_4].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT_4].PB(appModel);
    appModel = translate(appModel, vec3(3000.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT_4].PB(appModel);
    cylinderBuffers(CIRCLE_LIGHT_4);

    //CLOTHS_PLACE_4:
    cylinders[CLOTHS_PLACE_4] = Cylinder(10.0f, 10.0f, 800.0f, 36, 1, true, 1);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-830.0f -10700.0, -300.0f+ 1300.0f, -3155.0f + 13150.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    models[CLOTHS_PLACE_4].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 900.0f));
    models[CLOTHS_PLACE_4].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 900.0f));
    models[CLOTHS_PLACE_4].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 900.0f));
    models[CLOTHS_PLACE_4].PB(appModel);
    cylinderBuffers(CLOTHS_PLACE_4);

    //DRESS:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-830.0f -10700.0, -540.0f+ 1300.0f, -3405.0f + 13150.0f));
    appModel = scale(appModel, vec3(900.0f, 600.0f, 800.0f));
    models[DRESS1].PB(appModel);
    for(int i=0; i<15; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[DRESS1].PB(appModel);
    }
    squareBuffers(DRESS1);

    appModel = MODEL;
    appModel = translate(appModel, vec3(35.0f -10700.0, -580.0f+ 1300.0f, -3405.0f + 13150.0f));
    appModel = scale(appModel, vec3(900.0f, 600.0f, 800.0f));
    models[DRESS2].PB(appModel);
    for(int i=0; i<15; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[DRESS2].PB(appModel);
    }
    squareBuffers(DRESS2);

    appModel = MODEL;
    appModel = translate(appModel, vec3(990.0f -10700.0, -480.0f+ 1300.0f, -3405.0f + 13150.0f));
    appModel = scale(appModel, vec3(900.0f, 600.0f, 800.0f));
    models[DRESS3].PB(appModel);
    for(int i=0; i<15; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[DRESS3].PB(appModel);
    }
    squareBuffers(DRESS3);

    appModel = MODEL;
    appModel = translate(appModel, vec3(1875.0f -10700.0, -480.0f+ 1300.0f, -3405.0f + 13150.0f));
    appModel = scale(appModel, vec3(900.0f, 600.0f, 800.0f));
    models[DRESS4].PB(appModel);
    for(int i=0; i<15; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[DRESS4].PB(appModel);
    }
    squareBuffers(DRESS4);

    //CASHIER4:
    cubes[CASHIER4] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f- 3350.0f - 5350.0f, -710.0f+ 1300.0f, -2750.0f + 13550.0f));
    appModel = rotate(appModel, radians(270.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.4f, 4.0f));
    models[CASHIER4].PB(appModel);
    cubeBuffers(CASHIER4);

    //SCREEN:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f- 3350.0f - 5350.0f, -460.0f+ 1300.0f, -2750.0f + 13550.0f));
    appModel = rotate(appModel, radians(120.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //DRESSING_ROOM:
    cubes[DRESSING_ROOM] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-3860.0f- 3350.0f - 5350.0f, -300.0f+ 1300.0f, -3580.0f + 13550.0f));
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 5.2f, 1.0f));
    models[DRESSING_ROOM].PB(appModel);
    cubeBuffers(DRESSING_ROOM);

    //MIRROR4:
    cubes[MIRROR4] = Cubesphere(100.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2940.0f - 10700.0f, -350.0f+ 1300.0f, -2550.0f + 13150.0f));
    appModel = rotate(appModel, radians(180.0f), Z);
    appModel = scale(appModel, vec3(0.1f, 8.0f, 4.0f));
    models[MIRROR4].PB(appModel);
    cubeBuffers(MIRROR4);

    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(100.0f- 3350.0f - 5350.0f, -280.0f+ 1300.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-3450.0f- 3350.0f - 5350.0f, -280.0f+ 1300.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1670.0f- 3350.0f - 5350.0f, 150.0f+ 1300.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.6f, 2.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    cubeBuffers(SHOP_BLOOR);
    //--------------------------------------------------------------------------------------------------------
    //SECOND FLOOR::::::::::::::::::::::::::::::::::
    //DRESS_SHOP:
    cubes[DRESS_SHOP] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-5030-5300.0f, -300.0f + 2600.0f, 10300.0f)); 
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 2.1f, 9.0f)); 
    models[DRESS_SHOP].PB(appModel);
    cubeBuffers(DRESS_SHOP);

    //DRESS_GROUND
    appModel = MODEL;
    appModel = translate(appModel, vec3(-5030-5300.0f, -900.0f + 2600.0f, 10300.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-270.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 0.005f, 9.0f)); 
    models[DRESS_GROUND].PB(appModel);
    cubeBuffers(DRESS_GROUND);
    
    //CIRCLE_LIGHT_4:
    cylinders[CIRCLE_LIGHT_4] = Cylinder(60.0f, 60.0f, 10.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(0.0f -10650.0, 280.0f+ 2600.0f, 10250.0f));
    models[CIRCLE_LIGHT_4].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT_4].PB(appModel);
    appModel = translate(appModel, vec3(3000.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT_4].PB(appModel);
    cylinderBuffers(CIRCLE_LIGHT_4);

    //CLOTHS_PLACE_4:
    cylinders[CLOTHS_PLACE_4] = Cylinder(10.0f, 10.0f, 800.0f, 36, 1, true, 1);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-830.0f -10700.0, -300.0f+ 2600.0f, -3155.0f + 13150.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    models[CLOTHS_PLACE_4].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 900.0f));
    models[CLOTHS_PLACE_4].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 900.0f));
    models[CLOTHS_PLACE_4].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 900.0f));
    models[CLOTHS_PLACE_4].PB(appModel);
    cylinderBuffers(CLOTHS_PLACE_4);

    //DRESS:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-830.0f -10700.0, -540.0f+ 2600.0f, -3405.0f + 13150.0f));
    appModel = scale(appModel, vec3(900.0f, 600.0f, 800.0f));
    models[DRESS1].PB(appModel);
    for(int i=0; i<15; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[DRESS1].PB(appModel);
    }
    squareBuffers(DRESS1);

    appModel = MODEL;
    appModel = translate(appModel, vec3(35.0f -10700.0, -580.0f+ 2600.0f, -3405.0f + 13150.0f));
    appModel = scale(appModel, vec3(900.0f, 600.0f, 800.0f));
    models[DRESS2].PB(appModel);
    for(int i=0; i<15; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[DRESS2].PB(appModel);
    }
    squareBuffers(DRESS2);

    appModel = MODEL;
    appModel = translate(appModel, vec3(990.0f -10700.0, -480.0f+ 2600.0f, -3405.0f + 13150.0f));
    appModel = scale(appModel, vec3(900.0f, 600.0f, 800.0f));
    models[DRESS3].PB(appModel);
    for(int i=0; i<15; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[DRESS3].PB(appModel);
    }
    squareBuffers(DRESS3);

    appModel = MODEL;
    appModel = translate(appModel, vec3(1875.0f -10700.0, -480.0f+ 2600.0f, -3405.0f + 13150.0f));
    appModel = scale(appModel, vec3(900.0f, 600.0f, 800.0f));
    models[DRESS4].PB(appModel);
    for(int i=0; i<15; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 0.05f));
        models[DRESS4].PB(appModel);
    }
    squareBuffers(DRESS4);

    //CASHIER4:
    cubes[CASHIER4] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f- 3350.0f - 5350.0f, -710.0f+ 2600.0f, -2750.0f + 13550.0f));
    appModel = rotate(appModel, radians(270.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.4f, 4.0f));
    models[CASHIER4].PB(appModel);
    cubeBuffers(CASHIER4);

    //SCREEN:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2050.0f- 3350.0f - 5350.0f, -460.0f+ 2600.0f, -2750.0f + 13550.0f));
    appModel = rotate(appModel, radians(120.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //DRESSING_ROOM:
    cubes[DRESSING_ROOM] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-3860.0f- 3350.0f - 5350.0f, -300.0f+ 2600.0f, -3580.0f + 13550.0f));
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 5.2f, 1.0f));
    models[DRESSING_ROOM].PB(appModel);
    cubeBuffers(DRESSING_ROOM);

    //MIRROR4:
    cubes[MIRROR4] = Cubesphere(100.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2940.0f - 10700.0f, -350.0f+ 2600.0f, -2550.0f + 13150.0f));
    appModel = rotate(appModel, radians(180.0f), Z);
    appModel = scale(appModel, vec3(0.1f, 8.0f, 4.0f));
    models[MIRROR4].PB(appModel);
    cubeBuffers(MIRROR4);

    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(100.0f- 3350.0f - 5350.0f, -280.0f+ 2600.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-3450.0f- 3350.0f - 5350.0f, -280.0f+ 2600.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1670.0f- 3350.0f - 5350.0f, 150.0f+ 2600.0f, -2000.0f +  11450.0f));
    appModel = scale(appModel, vec3(15.6f, 2.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    cubeBuffers(SHOP_BLOOR);

    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //RESTAURANT:
    //GROUND FLOOR:::::::::::::::::::::

    //REST_ROOF:
    cylinders[REST_ROOF] = Cylinder(1200*1.0f, 1200*1.0f, 50.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4000.0, 350.0, -1150.0));
    appModel = rotate(appModel, radians(-220.0f), Y);
    models[REST_ROOF].PB(appModel);
    cylinderBuffers(REST_ROOF);

    //TRIA:
    //..tria bar:
    cylinders[TRIA] = Cylinder(12.0f, 12.0f, 110.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4000.0, 260.0, -1150.0));
    models[TRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0, -70.0, 0.0));
    appModel = scale(appModel, vec3(30.0f, 0.3f, 30.0f));
    models[TRIA].PB(appModel);
    
    cylinderBuffers(TRIA);


    //CYL_LIGHT:
    toruses[CYL_LIGHT] = Torus(3.0*0.76f, 3.0*0.1f, 24, 18, true, 2);
    curModel = appModel;
    appModel = translate(appModel, vec3(-6.0, -250.0, -6.0));
    appModel = scale(appModel, vec3(1.0f, 600.0f, 1.0f));
    models[CYL_LIGHT].PB(appModel);
    appModel = translate(curModel, vec3(-6.0, -250.0, 6.0));
    appModel = scale(appModel, vec3(1.0f, 600.0f, 1.0f));
    models[CYL_LIGHT].PB(appModel);
    appModel = translate(curModel, vec3(6.0, -250.0, 6.0));
    appModel = scale(appModel, vec3(1.0f, 600.0f, 1.0f));
    models[CYL_LIGHT].PB(appModel);
    appModel = translate(curModel, vec3(6.0, -250.0, -6.0));
    appModel = scale(appModel, vec3(1.0f, 600.0f, 1.0f));
    models[CYL_LIGHT].PB(appModel);
    appModel = translate(curModel, vec3(0.0, -250.0, 0.0));
    appModel = scale(appModel, vec3(1.0f, 600.0f, 1.0f));
    models[CYL_LIGHT].PB(appModel);
    torusBuffers(CYL_LIGHT);

    //REST_GROUND:
    cylinders[REST_GROUND] = Cylinder(1200*1.0f, 1200*1.0f, 25.0f, 40, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3900.0, -550.0, -1080.0));
    models[REST_GROUND].PB(appModel);

    //STAIR:
    appModel = translate(appModel, vec3(-1170.0f, -70.0f, 120.0f));
    appModel = rotate(appModel, radians(10.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 4.0f, 0.5f));
    models[REST_GROUND].PB(appModel);
    appModel = translate(appModel, vec3(-700.0f, -20.0f, 0.0f));
    models[REST_GROUND].PB(appModel);
    appModel = translate(appModel, vec3(-700.0f, -20.0f, 0.0f));
    models[REST_GROUND].PB(appModel);
    appModel = translate(appModel, vec3(-700.0f, -20.0f, 0.0f));
    models[REST_GROUND].PB(appModel);

    cylinderBuffers(REST_GROUND);

    //REST_WALLs:
    cubes[REST_WALL] = Cubesphere(1000.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3500.0, -120.0, -180.0));
    appModel = rotate(appModel, radians(-15.0f), Y);
    appModel = scale(appModel, vec3(1.3f, 0.75f, 0.1f));
    models[REST_WALL].PB(appModel);

    appModel = MODEL;
    appModel = translate(appModel, vec3(2950.0, -120.0, -1780.0));
    appModel = rotate(appModel, radians(35.0f), Y);
    appModel = scale(appModel, vec3(0.9f, 0.75f, 0.1f));
    models[REST_WALL].PB(appModel);
    cubeBuffers(REST_WALL);

    //CASHIER5:
    cubes[CASHIER5] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3300.0, -390.0, -580.0));
    appModel = rotate(appModel, radians(260.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.2f, 4.0f));
    models[CASHIER5].PB(appModel);
    cubeBuffers(CASHIER5);

    //SCREEN:
    appModel = MODEL;
    appModel = translate(appModel, vec3(3250.0, -170.0, -580.0));
    appModel = rotate(appModel, radians(100.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //TABLE:
    //table 1:
    cylinders[TABLE] = Cylinder(200.0f, 200.0f, 15.0f, 42, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4800.0, -360.0, -1050.0));
    appModel = rotate(appModel, radians(180.0f), X);
    models[TABLE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4800.0, -450.0, -1050.0));
    appModel = scale(appModel, vec3(0.4f, 12.0f, 0.4f));
    models[TABLE].PB(appModel);
    curModel = appModel;
    //Chair base:
    cylinders[CHAIR_BASE] = Cylinder(200.0f, 200.0f, 15.0f, 42, 1, true, 2);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    appModel = translate(curModel, vec3(0.0f, 0.0f, 600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    //Chair 1:
    toruses[CHAIR] = Torus(200.0f * 1.28f, 200.0f * 1.0f, 15, 14, true, 3);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 10.0f, -1400.0f));
    appModel = scale(appModel, vec3(0.4f, 0.03f, 0.4f));
    models[CHAIR].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 4000.0f));
    models[CHAIR].PB(appModel);

    //table 2:
    cylinders[TABLE] = Cylinder(200.0f, 200.0f, 15.0f, 42, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4500.0, -360.0, -1750.0));
    appModel = rotate(appModel, radians(180.0f), X);
    models[TABLE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4500.0, -450.0, -1750.0));
    appModel = scale(appModel, vec3(0.4f, 12.0f, 0.4f));
    models[TABLE].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, -600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    appModel = translate(curModel, vec3(0.0f, 0.0f, 600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    //Chair 2:
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 10.0f, -1400.0f));
    appModel = scale(appModel, vec3(0.4f, 0.03f, 0.4f));
    models[CHAIR].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 4000.0f));
    models[CHAIR].PB(appModel);

    //table 3:
    cylinders[TABLE] = Cylinder(200.0f, 200.0f, 15.0f, 42, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3700.0, -360.0, -1850.0));
    appModel = rotate(appModel, radians(180.0f), X);
    models[TABLE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3700.0, -450.0, -1850.0));
    appModel = scale(appModel, vec3(0.4f, 12.0f, 0.4f));
    models[TABLE].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, -600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    appModel = translate(curModel, vec3(0.0f, 0.0f, 600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    //Chair 3:
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 10.0f, -1400.0f));
    appModel = scale(appModel, vec3(0.4f, 0.03f, 0.4f));
    models[CHAIR].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 4000.0f));
    models[CHAIR].PB(appModel);

    //table 4:
    cylinders[TABLE] = Cylinder(200.0f, 200.0f, 15.0f, 42, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4000.0, -360.0, -1150.0));
    appModel = rotate(appModel, radians(180.0f), X);
    models[TABLE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4000.0, -450.0, -1150.0));
    appModel = scale(appModel, vec3(0.4f, 12.0f, 0.4f));
    models[TABLE].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, -600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    appModel = translate(curModel, vec3(0.0f, 0.0f, 600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    //Chair 4:
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 10.0f, -1400.0f));
    appModel = scale(appModel, vec3(0.4f, 0.03f, 0.4f));
    models[CHAIR].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 4000.0f));
    models[CHAIR].PB(appModel);
    //---------------------------------------------------------------------------------------------

    //First FLOOR:::::::::::::::::::::

    //REST_ROOF:
    cylinders[REST_ROOF] = Cylinder(1200*1.0f, 1200*1.0f, 50.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4000.0, 350.0 + 1300.0f, -1150.0));
    appModel = rotate(appModel, radians(-220.0f), Y);
    models[REST_ROOF].PB(appModel);
    cylinderBuffers(REST_ROOF);

    //TRIA:
    //..tria bar:
    cylinders[TRIA] = Cylinder(12.0f, 12.0f, 110.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4000.0, 260.0+ 1300.0f, -1150.0));
    models[TRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0, -70.0, 0.0));
    appModel = scale(appModel, vec3(30.0f, 0.3f, 30.0f));
    models[TRIA].PB(appModel);
    
    cylinderBuffers(TRIA);


    //CYL_LIGHT:
    toruses[CYL_LIGHT] = Torus(3.0*0.76f, 3.0*0.1f, 24, 18, true, 2);
    curModel = appModel;
    appModel = translate(appModel, vec3(-6.0, -250.0, -6.0));
    appModel = scale(appModel, vec3(1.0f, 600.0f, 1.0f));
    models[CYL_LIGHT].PB(appModel);
    appModel = translate(curModel, vec3(-6.0, -250.0, 6.0));
    appModel = scale(appModel, vec3(1.0f, 600.0f, 1.0f));
    models[CYL_LIGHT].PB(appModel);
    appModel = translate(curModel, vec3(6.0, -250.0, 6.0));
    appModel = scale(appModel, vec3(1.0f, 600.0f, 1.0f));
    models[CYL_LIGHT].PB(appModel);
    appModel = translate(curModel, vec3(6.0, -250.0, -6.0));
    appModel = scale(appModel, vec3(1.0f, 600.0f, 1.0f));
    models[CYL_LIGHT].PB(appModel);
    appModel = translate(curModel, vec3(0.0, -250.0, 0.0));
    appModel = scale(appModel, vec3(1.0f, 600.0f, 1.0f));
    models[CYL_LIGHT].PB(appModel);
    torusBuffers(CYL_LIGHT);

    //REST_GROUND:
    cylinders[REST_GROUND] = Cylinder(1200*1.0f, 1200*1.0f, 25.0f, 40, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3900.0, -550.0+ 1300.0f, -1080.0));
    models[REST_GROUND].PB(appModel);

    //STAIR:
    appModel = translate(appModel, vec3(-1170.0f, -70.0f, 120.0f));
    appModel = rotate(appModel, radians(10.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 4.0f, 0.5f));
    models[REST_GROUND].PB(appModel);
    appModel = translate(appModel, vec3(-700.0f, -20.0f, 0.0f));
    models[REST_GROUND].PB(appModel);
    appModel = translate(appModel, vec3(-700.0f, -20.0f, 0.0f));
    models[REST_GROUND].PB(appModel);
    appModel = translate(appModel, vec3(-700.0f, -20.0f, 0.0f));
    models[REST_GROUND].PB(appModel);

    cylinderBuffers(REST_GROUND);

    //REST_WALLs:
    cubes[REST_WALL] = Cubesphere(1000.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3500.0, -120.0+ 1300.0f, -180.0));
    appModel = rotate(appModel, radians(-15.0f), Y);
    appModel = scale(appModel, vec3(1.3f, 0.75f, 0.1f));
    models[REST_WALL].PB(appModel);

    appModel = MODEL;
    appModel = translate(appModel, vec3(2950.0, -120.0+ 1300.0f, -1780.0));
    appModel = rotate(appModel, radians(35.0f), Y);
    appModel = scale(appModel, vec3(0.9f, 0.75f, 0.1f));
    models[REST_WALL].PB(appModel);
    cubeBuffers(REST_WALL);

    //CASHIER5:
    cubes[CASHIER5] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3300.0, -390.0+ 1300.0f, -580.0));
    appModel = rotate(appModel, radians(260.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.2f, 4.0f));
    models[CASHIER5].PB(appModel);
    cubeBuffers(CASHIER5);

    //SCREEN:
    appModel = MODEL;
    appModel = translate(appModel, vec3(3250.0, -170.0+ 1300.0f, -580.0));
    appModel = rotate(appModel, radians(100.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //TABLE:
    //table 1:
    cylinders[TABLE] = Cylinder(200.0f, 200.0f, 15.0f, 42, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4800.0, -360.0+ 1300.0f, -1050.0));
    appModel = rotate(appModel, radians(180.0f), X);
    models[TABLE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4800.0, -450.0+ 1300.0f, -1050.0));
    appModel = scale(appModel, vec3(0.4f, 12.0f, 0.4f));
    models[TABLE].PB(appModel);
    curModel = appModel;
    //Chair base:
    cylinders[CHAIR_BASE] = Cylinder(200.0f, 200.0f, 15.0f, 42, 1, true, 2);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    appModel = translate(curModel, vec3(0.0f, 0.0f, 600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    //Chair 1:
    toruses[CHAIR] = Torus(200.0f * 1.28f, 200.0f * 1.0f, 15, 14, true, 3);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 10.0f, -1400.0f));
    appModel = scale(appModel, vec3(0.4f, 0.03f, 0.4f));
    models[CHAIR].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 4000.0f));
    models[CHAIR].PB(appModel);

    //table 2:
    cylinders[TABLE] = Cylinder(200.0f, 200.0f, 15.0f, 42, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4500.0, -360.0+ 1300.0f, -1750.0));
    appModel = rotate(appModel, radians(180.0f), X);
    models[TABLE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4500.0, -450.0+ 1300.0f, -1750.0));
    appModel = scale(appModel, vec3(0.4f, 12.0f, 0.4f));
    models[TABLE].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, -600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    appModel = translate(curModel, vec3(0.0f, 0.0f, 600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    //Chair 2:
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 10.0f, -1400.0f));
    appModel = scale(appModel, vec3(0.4f, 0.03f, 0.4f));
    models[CHAIR].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 4000.0f));
    models[CHAIR].PB(appModel);

    //table 3:
    cylinders[TABLE] = Cylinder(200.0f, 200.0f, 15.0f, 42, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3700.0, -360.0+ 1300.0f, -1850.0));
    appModel = rotate(appModel, radians(180.0f), X);
    models[TABLE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3700.0, -450.0+ 1300.0f, -1850.0));
    appModel = scale(appModel, vec3(0.4f, 12.0f, 0.4f));
    models[TABLE].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, -600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    appModel = translate(curModel, vec3(0.0f, 0.0f, 600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    //Chair 3:
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 10.0f, -1400.0f));
    appModel = scale(appModel, vec3(0.4f, 0.03f, 0.4f));
    models[CHAIR].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 4000.0f));
    models[CHAIR].PB(appModel);

    //table 4:
    cylinders[TABLE] = Cylinder(200.0f, 200.0f, 15.0f, 42, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4000.0, -360.0+ 1300.0f, -1150.0));
    appModel = rotate(appModel, radians(180.0f), X);
    models[TABLE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4000.0, -450.0+ 1300.0f, -1150.0));
    appModel = scale(appModel, vec3(0.4f, 12.0f, 0.4f));
    models[TABLE].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, -600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    appModel = translate(curModel, vec3(0.0f, 0.0f, 600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    //Chair 4:
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 10.0f, -1400.0f));
    appModel = scale(appModel, vec3(0.4f, 0.03f, 0.4f));
    models[CHAIR].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 4000.0f));
    models[CHAIR].PB(appModel);
    //---------------------------------------------------------------------------------------------
    

    //Second FLOOR:::::::::::::::::::::

    //REST_ROOF:
    cylinders[REST_ROOF] = Cylinder(1200*1.0f, 1200*1.0f, 50.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4000.0, 350.0 + 2600.0f, -1150.0));
    appModel = rotate(appModel, radians(-220.0f), Y);
    models[REST_ROOF].PB(appModel);
    cylinderBuffers(REST_ROOF);

    //TRIA:
    //..tria bar:
    cylinders[TRIA] = Cylinder(12.0f, 12.0f, 110.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4000.0, 260.0+ 2600.0f, -1150.0));
    models[TRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0, -70.0, 0.0));
    appModel = scale(appModel, vec3(30.0f, 0.3f, 30.0f));
    models[TRIA].PB(appModel);
    
    cylinderBuffers(TRIA);


    //CYL_LIGHT:
    toruses[CYL_LIGHT] = Torus(3.0*0.76f, 3.0*0.1f, 24, 18, true, 2);
    curModel = appModel;
    appModel = translate(appModel, vec3(-6.0, -250.0, -6.0));
    appModel = scale(appModel, vec3(1.0f, 600.0f, 1.0f));
    models[CYL_LIGHT].PB(appModel);
    appModel = translate(curModel, vec3(-6.0, -250.0, 6.0));
    appModel = scale(appModel, vec3(1.0f, 600.0f, 1.0f));
    models[CYL_LIGHT].PB(appModel);
    appModel = translate(curModel, vec3(6.0, -250.0, 6.0));
    appModel = scale(appModel, vec3(1.0f, 600.0f, 1.0f));
    models[CYL_LIGHT].PB(appModel);
    appModel = translate(curModel, vec3(6.0, -250.0, -6.0));
    appModel = scale(appModel, vec3(1.0f, 600.0f, 1.0f));
    models[CYL_LIGHT].PB(appModel);
    appModel = translate(curModel, vec3(0.0, -250.0, 0.0));
    appModel = scale(appModel, vec3(1.0f, 600.0f, 1.0f));
    models[CYL_LIGHT].PB(appModel);
    torusBuffers(CYL_LIGHT);

    //REST_GROUND:
    cylinders[REST_GROUND] = Cylinder(1200*1.0f, 1200*1.0f, 25.0f, 40, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3900.0, -550.0+ 2600.0f, -1080.0));
    models[REST_GROUND].PB(appModel);

    //STAIR:
    appModel = translate(appModel, vec3(-1170.0f, -70.0f, 120.0f));
    appModel = rotate(appModel, radians(10.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 4.0f, 0.5f));
    models[REST_GROUND].PB(appModel);
    appModel = translate(appModel, vec3(-700.0f, -20.0f, 0.0f));
    models[REST_GROUND].PB(appModel);
    appModel = translate(appModel, vec3(-700.0f, -20.0f, 0.0f));
    models[REST_GROUND].PB(appModel);
    appModel = translate(appModel, vec3(-700.0f, -20.0f, 0.0f));
    models[REST_GROUND].PB(appModel);

    cylinderBuffers(REST_GROUND);

    //REST_WALLs:
    cubes[REST_WALL] = Cubesphere(1000.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3500.0, -120.0+ 2600.0f, -180.0));
    appModel = rotate(appModel, radians(-15.0f), Y);
    appModel = scale(appModel, vec3(1.3f, 0.75f, 0.1f));
    models[REST_WALL].PB(appModel);

    appModel = MODEL;
    appModel = translate(appModel, vec3(2950.0, -120.0+ 2600.0f, -1780.0));
    appModel = rotate(appModel, radians(35.0f), Y);
    appModel = scale(appModel, vec3(0.9f, 0.75f, 0.1f));
    models[REST_WALL].PB(appModel);
    cubeBuffers(REST_WALL);

    //CASHIER5:
    cubes[CASHIER5] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3300.0, -390.0+ 2600.0f, -580.0));
    appModel = rotate(appModel, radians(260.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.2f, 4.0f));
    models[CASHIER5].PB(appModel);
    cubeBuffers(CASHIER5);

    //SCREEN:
    appModel = MODEL;
    appModel = translate(appModel, vec3(3250.0, -170.0+ 2600.0f, -580.0));
    appModel = rotate(appModel, radians(100.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //TABLE:
    //table 1:
    cylinders[TABLE] = Cylinder(200.0f, 200.0f, 15.0f, 42, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4800.0, -360.0+ 2600.0f, -1050.0));
    appModel = rotate(appModel, radians(180.0f), X);
    models[TABLE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4800.0, -450.0+ 2600.0f, -1050.0));
    appModel = scale(appModel, vec3(0.4f, 12.0f, 0.4f));
    models[TABLE].PB(appModel);
    curModel = appModel;
    //Chair base:
    cylinders[CHAIR_BASE] = Cylinder(200.0f, 200.0f, 15.0f, 42, 1, true, 2);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    appModel = translate(curModel, vec3(0.0f, 0.0f, 600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    //Chair 1:
    toruses[CHAIR] = Torus(200.0f * 1.28f, 200.0f * 1.0f, 15, 14, true, 3);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 10.0f, -1400.0f));
    appModel = scale(appModel, vec3(0.4f, 0.03f, 0.4f));
    models[CHAIR].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 4000.0f));
    models[CHAIR].PB(appModel);

    //table 2:
    cylinders[TABLE] = Cylinder(200.0f, 200.0f, 15.0f, 42, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4500.0, -360.0+ 2600.0f, -1750.0));
    appModel = rotate(appModel, radians(180.0f), X);
    models[TABLE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4500.0, -450.0+ 2600.0f, -1750.0));
    appModel = scale(appModel, vec3(0.4f, 12.0f, 0.4f));
    models[TABLE].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, -600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    appModel = translate(curModel, vec3(0.0f, 0.0f, 600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    //Chair 2:
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 10.0f, -1400.0f));
    appModel = scale(appModel, vec3(0.4f, 0.03f, 0.4f));
    models[CHAIR].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 4000.0f));
    models[CHAIR].PB(appModel);

    //table 3:
    cylinders[TABLE] = Cylinder(200.0f, 200.0f, 15.0f, 42, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3700.0, -360.0+ 2600.0f, -1850.0));
    appModel = rotate(appModel, radians(180.0f), X);
    models[TABLE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3700.0, -450.0+ 2600.0f, -1850.0));
    appModel = scale(appModel, vec3(0.4f, 12.0f, 0.4f));
    models[TABLE].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, -600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    appModel = translate(curModel, vec3(0.0f, 0.0f, 600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    //Chair 3:
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 10.0f, -1400.0f));
    appModel = scale(appModel, vec3(0.4f, 0.03f, 0.4f));
    models[CHAIR].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 4000.0f));
    models[CHAIR].PB(appModel);

    //table 4:
    cylinders[TABLE] = Cylinder(200.0f, 200.0f, 15.0f, 42, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4000.0, -360.0+ 2600.0f, -1150.0));
    appModel = rotate(appModel, radians(180.0f), X);
    models[TABLE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4000.0, -450.0+ 2600.0f, -1150.0));
    appModel = scale(appModel, vec3(0.4f, 12.0f, 0.4f));
    models[TABLE].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, -600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    appModel = translate(curModel, vec3(0.0f, 0.0f, 600.0f));
    appModel = scale(appModel, vec3(1.0f, 0.6f, 1.0f));
    models[CHAIR_BASE].PB(appModel);
    //Chair 4:
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 10.0f, -1400.0f));
    appModel = scale(appModel, vec3(0.4f, 0.03f, 0.4f));
    models[CHAIR].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, 4000.0f));
    models[CHAIR].PB(appModel);
    //---------------------------------------------------------------------------------------------

    cylinderBuffers(TABLE);
    cylinderBuffers(CHAIR_BASE);
    torusBuffers(CHAIR);

    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //FURN_STORE:
    //GROUND FLOOR:::::::::::::::::::::::::::::::::::::::
    cubes[FURN_STORE] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3800.0f, -300.0f, 4100.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(4.5f, 2.1f, 13.7f)); 
    models[FURN_STORE].PB(appModel);
    cubes[FURN_STORE].reverseNormals();
    cubeBuffers(FURN_STORE);

    //FURN_GROUND
    cubes[FURN_GROUND] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3800.0f, -900.0f, 4100.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(4.5f, 0.005f, 13.7f)); 
    models[FURN_GROUND].PB(appModel);
    // cubes[FURN_GROUND].reverseNormals();
    cubeBuffers(FURN_GROUND);
    
    //CIRCLE_LIGHT6:
    cylinders[CIRCLE_LIGHT6] = Cylinder(60.0f, 60.0f, 10.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3800.0f, 230.0f, 1700.0f));
    appModel = scale(appModel, vec3(3.0f, 3.0f, 3.0f));
    models[CIRCLE_LIGHT6].PB(appModel);
    for(int i=0; i<3; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 500.0f));
        models[CIRCLE_LIGHT6].PB(appModel);
    }
    cylinderBuffers(CIRCLE_LIGHT6);

    //BED:
    threeDModels[BED] = Model("../resources/objects/GothicBed_01_1k.fbx/GothicBed_01_1k.fbx");
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -900.0f, 700.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[BED].PB(appModel);
    threeDmodelBuffers(BED);

    //SOFA1:
    threeDModels[SOFA1] = Model("../resources/objects/sofa1/scene.gltf");
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -750.0f, 1700.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = scale(appModel, vec3(300.0f, 300.0f, 300.0f));
    models[SOFA1].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -750.0f, 2300.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = scale(appModel, vec3(300.0f, 300.0f, 300.0f));
    models[SOFA1].PB(appModel);
    threeDmodelBuffers(SOFA1);

    //SOFA2:
    threeDModels[SOFA2] = Model("../resources/objects/sofa2/scene.gltf");
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -590.0f, 3100.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SOFA2].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -590.0f, 4100.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SOFA2].PB(appModel);
    threeDmodelBuffers(SOFA2);

    //TABLE2:
    threeDModels[TABLE2] = Model("../resources/objects/table/source/Table.fbx");
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -890.0f, 5200.0f));
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(50.0f, 50.0f, 50.0f));
    models[TABLE2].PB(appModel);
    threeDmodelBuffers(TABLE2);

    //TABLE3:
    threeDModels[TABLE3] = Model("../resources/objects/antique-table/source/model/Antiquetable_Unwrapped.obj");
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -890.0f, 5900.0f));
    appModel = scale(appModel, vec3(15.0f, 15.0f, 15.0f));
    models[TABLE3].PB(appModel);
    threeDmodelBuffers(TABLE3);

    //TABLE4:
    threeDModels[TABLE4] = Model("../resources/objects/ClassicConsole_01_1k.gltf/ClassicConsole_01_1k.gltf");
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -890.0f, 6400.0f));
    appModel = scale(appModel, vec3(300.0f, 300.0f, 300.0f));
    models[TABLE4].PB(appModel);
    threeDmodelBuffers(TABLE4);

    //CABINET1:
    threeDModels[CABINET1] = Model("../resources/objects/Cabinet_Bookcase/20359_Cabinet_Bookcase_v1_Texture.obj");
    appModel = MODEL;
    appModel = translate(appModel, vec3(4200.0f, 200.0f, 7550.0f));
    appModel = rotate(appModel, radians(90.0f), X);
    appModel = scale(appModel, vec3(100.0f, 100.0f, 115.0f));
    models[CABINET1].PB(appModel);
    threeDmodelBuffers(CABINET1);



    //CASHIER6:
    cubes[CASHIER6] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3200.0, -750.0, 7070.0));
    appModel = rotate(appModel, radians(270.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.2f, 4.0f));
    models[CASHIER6].PB(appModel);
    cubeBuffers(CASHIER6);

    //SCREEN:
    appModel = MODEL;
    appModel = translate(appModel, vec3(3250.0, -520.0, 7070.0));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //COUCH2:
    threeDModels[COUCH2] = Model("../resources/objects/couch2/uploads_files_4635285_Couch.fbx");
    appModel = MODEL;
    appModel = translate(appModel, vec3(2800.0f, -800.0f, 1200.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(150.0f, 150.0f, 150.0f));
    models[COUCH2].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2800.0f, -800.0f, 2500.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(150.0f, 150.0f, 150.0f));
    models[COUCH2].PB(appModel);
    threeDmodelBuffers(COUCH2);

    //SOFA:
    threeDModels[SOFA] = Model("../resources/objects/sofa/source/sofa.fbx");
    appModel = MODEL;
    appModel = translate(appModel, vec3(3650.0f, -900.0f, 1600.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(250.0f, 250.0f, 250.0f));
    models[SOFA].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3650.0f, -900.0f, 2500.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(250.0f, 250.0f, 250.0f));
    models[SOFA].PB(appModel);
    threeDmodelBuffers(SOFA);

    //TABLE5:
    threeDModels[TABLE5] = Model("../resources/objects/table2/uploads_files_2693668_Side_Table.fbx");
    appModel = MODEL;
    appModel = translate(appModel, vec3(2800.0f, -900.0f, 6100.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(1000.0f, 1000.0f, 1000.0f));
    models[TABLE5].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2800.0f, -900.0f, 5400.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(1000.0f, 1000.0f, 1000.0f));
    models[TABLE5].PB(appModel);
    threeDmodelBuffers(TABLE5);

    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(2500.0f, -280.0f, 1600.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(25.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2500.0f, 50.0f, 4100.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(18.1f, 4.3f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2500.0f, -280.0f, 6600.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(25.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    
    cubeBuffers(SHOP_BLOOR);
    //-----------------------------------------------------------------------------------------
    //First FLOOR:::::::::::::::::::::::::::::::::::::::
    appModel = MODEL;
    appModel = translate(appModel, vec3(3800.0f, -300.0f + 1300.0f, 4100.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(4.5f, 2.1f, 13.7f)); 
    models[FURN_STORE].PB(appModel);
    cubes[FURN_STORE].reverseNormals();
    cubeBuffers(FURN_STORE);

    //FURN_GROUND
    appModel = MODEL;
    appModel = translate(appModel, vec3(3800.0f, -900.0f+ 1300.0f, 4100.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(4.5f, 0.005f, 13.7f)); 
    models[FURN_GROUND].PB(appModel);
    cubes[FURN_GROUND].reverseNormals();
    cubeBuffers(FURN_GROUND);
    
    //CIRCLE_LIGHT6:
    appModel = MODEL;
    appModel = translate(appModel, vec3(3800.0f, 230.0f+ 1300.0f, 1700.0f));
    appModel = scale(appModel, vec3(3.0f, 3.0f, 3.0f));
    models[CIRCLE_LIGHT6].PB(appModel);
    for(int i=0; i<3; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 500.0f));
        models[CIRCLE_LIGHT6].PB(appModel);
    }
    cylinderBuffers(CIRCLE_LIGHT6);

    //BED:
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -900.0f+ 1300.0f, 700.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[BED].PB(appModel);
    threeDmodelBuffers(BED);

    //SOFA1:
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -750.0f+ 1300.0f, 1700.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = scale(appModel, vec3(300.0f, 300.0f, 300.0f));
    models[SOFA1].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -750.0f+ 1300.0f, 2300.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = scale(appModel, vec3(300.0f, 300.0f, 300.0f));
    models[SOFA1].PB(appModel);
    threeDmodelBuffers(SOFA1);

    //SOFA2:
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -590.0f+ 1300.0f, 3100.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SOFA2].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -590.0f+ 1300.0f, 4100.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SOFA2].PB(appModel);
    threeDmodelBuffers(SOFA2);

    //TABLE2:
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -890.0f+ 1300.0f, 5200.0f));
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(50.0f, 50.0f, 50.0f));
    models[TABLE2].PB(appModel);
    threeDmodelBuffers(TABLE2);

    //TABLE3:
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -890.0f+ 1300.0f, 5900.0f));
    appModel = scale(appModel, vec3(15.0f, 15.0f, 15.0f));
    models[TABLE3].PB(appModel);
    threeDmodelBuffers(TABLE3);

    //TABLE4:
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -890.0f+ 1300.0f, 6400.0f));
    appModel = scale(appModel, vec3(300.0f, 300.0f, 300.0f));
    models[TABLE4].PB(appModel);
    threeDmodelBuffers(TABLE4);

    //CABINET1:
    appModel = MODEL;
    appModel = translate(appModel, vec3(4200.0f, 200.0f+ 1300.0f, 7550.0f));
    appModel = rotate(appModel, radians(90.0f), X);
    appModel = scale(appModel, vec3(100.0f, 100.0f, 115.0f));
    models[CABINET1].PB(appModel);
    threeDmodelBuffers(CABINET1);



    //CASHIER6:
    appModel = MODEL;
    appModel = translate(appModel, vec3(3200.0, -750.0f + 1300.0f, 7070.0));
    appModel = rotate(appModel, radians(270.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.2f, 4.0f));
    models[CASHIER6].PB(appModel);
    cubeBuffers(CASHIER6);

    //SCREEN:
    appModel = MODEL;
    appModel = translate(appModel, vec3(3250.0, -520.0 + 1300.0f, 7070.0));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //COUCH2:
    appModel = MODEL;
    appModel = translate(appModel, vec3(2800.0f, -800.0f + 1300.0f, 1200.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(150.0f, 150.0f, 150.0f));
    models[COUCH2].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2800.0f, -800.0f+ 1300.0f, 2500.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(150.0f, 150.0f, 150.0f));
    models[COUCH2].PB(appModel);
    threeDmodelBuffers(COUCH2);

    //SOFA:
    appModel = MODEL;
    appModel = translate(appModel, vec3(3650.0f, -900.0f+ 1300.0f, 1600.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(250.0f, 250.0f, 250.0f));
    models[SOFA].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3650.0f, -900.0f+ 1300.0f, 2500.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(250.0f, 250.0f, 250.0f));
    models[SOFA].PB(appModel);
    threeDmodelBuffers(SOFA);

    //TABLE5:
    appModel = MODEL;
    appModel = translate(appModel, vec3(2800.0f, -900.0f+ 1300.0f, 6100.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(1000.0f, 1000.0f, 1000.0f));
    models[TABLE5].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2800.0f, -900.0f+ 1300.0f, 5400.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(1000.0f, 1000.0f, 1000.0f));
    models[TABLE5].PB(appModel);
    threeDmodelBuffers(TABLE5);

    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(2500.0f, -280.0f+ 1300.0f, 1600.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(25.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2500.0f, 50.0f+ 1300.0f, 4100.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(18.1f, 4.3f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2500.0f, -280.0f+ 1300.0f, 6600.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(25.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    
    cubeBuffers(SHOP_BLOOR);

    //-----------------------------------------------------------------------------------------
    //First FLOOR:::::::::::::::::::::::::::::::::::::::
    appModel = MODEL;
    appModel = translate(appModel, vec3(3800.0f, -300.0f + 2600.0f, 4100.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(4.5f, 2.1f, 13.7f)); 
    models[FURN_STORE].PB(appModel);
    cubes[FURN_STORE].reverseNormals();
    cubeBuffers(FURN_STORE);

    //FURN_GROUND
    appModel = MODEL;
    appModel = translate(appModel, vec3(3800.0f, -900.0f+ 2600.0f, 4100.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(4.5f, 0.005f, 13.7f)); 
    models[FURN_GROUND].PB(appModel);
    // cubes[FURN_GROUND].reverseNormals();
    cubeBuffers(FURN_GROUND);
    
    //CIRCLE_LIGHT6:
    appModel = MODEL;
    appModel = translate(appModel, vec3(3800.0f, 230.0f+ 2600.0f, 1700.0f));
    appModel = scale(appModel, vec3(3.0f, 3.0f, 3.0f));
    models[CIRCLE_LIGHT6].PB(appModel);
    for(int i=0; i<3; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 500.0f));
        models[CIRCLE_LIGHT6].PB(appModel);
    }
    cylinderBuffers(CIRCLE_LIGHT6);

    //BED:
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -900.0f+ 2600.0f, 700.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[BED].PB(appModel);
    threeDmodelBuffers(BED);

    //SOFA1:
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -750.0f+ 2600.0f, 1700.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = scale(appModel, vec3(300.0f, 300.0f, 300.0f));
    models[SOFA1].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -750.0f+ 2600.0f, 2300.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = scale(appModel, vec3(300.0f, 300.0f, 300.0f));
    models[SOFA1].PB(appModel);
    threeDmodelBuffers(SOFA1);

    //SOFA2:
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -590.0f+ 2600.0f, 3100.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SOFA2].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -590.0f+ 2600.0f, 4100.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SOFA2].PB(appModel);
    threeDmodelBuffers(SOFA2);

    //TABLE2:
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -890.0f+ 2600.0f, 5200.0f));
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(50.0f, 50.0f, 50.0f));
    models[TABLE2].PB(appModel);
    threeDmodelBuffers(TABLE2);

    //TABLE3:
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -890.0f+ 2600.0f, 5900.0f));
    appModel = scale(appModel, vec3(15.0f, 15.0f, 15.0f));
    models[TABLE3].PB(appModel);
    threeDmodelBuffers(TABLE3);

    //TABLE4:
    appModel = MODEL;
    appModel = translate(appModel, vec3(4600.0f, -890.0f+ 2600.0f, 6400.0f));
    appModel = scale(appModel, vec3(300.0f, 300.0f, 300.0f));
    models[TABLE4].PB(appModel);
    threeDmodelBuffers(TABLE4);

    //CABINET1:
    appModel = MODEL;
    appModel = translate(appModel, vec3(4200.0f, 200.0f+ 2600.0f, 7550.0f));
    appModel = rotate(appModel, radians(90.0f), X);
    appModel = scale(appModel, vec3(100.0f, 100.0f, 115.0f));
    models[CABINET1].PB(appModel);
    threeDmodelBuffers(CABINET1);



    //CASHIER6:
    appModel = MODEL;
    appModel = translate(appModel, vec3(3200.0, -750.0f + 2600.0f, 7070.0));
    appModel = rotate(appModel, radians(270.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.2f, 4.0f));
    models[CASHIER6].PB(appModel);
    cubeBuffers(CASHIER6);

    //SCREEN:
    appModel = MODEL;
    appModel = translate(appModel, vec3(3250.0, -520.0 + 2600.0f, 7070.0));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //COUCH2:
    appModel = MODEL;
    appModel = translate(appModel, vec3(2800.0f, -800.0f + 2600.0f, 1200.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(150.0f, 150.0f, 150.0f));
    models[COUCH2].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2800.0f, -800.0f+ 2600.0f, 2500.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(150.0f, 150.0f, 150.0f));
    models[COUCH2].PB(appModel);
    threeDmodelBuffers(COUCH2);

    //SOFA:
    appModel = MODEL;
    appModel = translate(appModel, vec3(3650.0f, -900.0f+ 2600.0f, 1600.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(250.0f, 250.0f, 250.0f));
    models[SOFA].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(3650.0f, -900.0f+ 2600.0f, 2500.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(250.0f, 250.0f, 250.0f));
    models[SOFA].PB(appModel);
    threeDmodelBuffers(SOFA);

    //TABLE5:
    appModel = MODEL;
    appModel = translate(appModel, vec3(2800.0f, -900.0f+ 2600.0f, 6100.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(1000.0f, 1000.0f, 1000.0f));
    models[TABLE5].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2800.0f, -900.0f+ 2600.0f, 5400.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(1000.0f, 1000.0f, 1000.0f));
    models[TABLE5].PB(appModel);
    threeDmodelBuffers(TABLE5);

    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(2500.0f, -280.0f+ 2600.0f, 1600.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(25.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2500.0f, 50.0f+ 2600.0f, 4100.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(18.1f, 4.3f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(2500.0f, -280.0f+ 2600.0f, 6600.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(25.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    
    cubeBuffers(SHOP_BLOOR);

    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //TECH_STORE::::::::::::::::::::::::::::::::
    //GROUND FLOOR:
    cubes[TECH_STORE] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-13460.0f, -300.0f, 2850.0f)); 
    appModel = scale(appModel, vec3(3.5f, 2.1f, 16.9f)); 
    models[TECH_STORE].PB(appModel);
    cubes[TECH_STORE].reverseNormals();
    cubeBuffers(TECH_STORE);

    //TECH_GROUND
    cubes[TECH_GROUND] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-13460.0f, -900.0f, 2850.0f)); 
    appModel = scale(appModel, vec3(3.5f, 0.005f, 16.9f)); 
    models[TECH_GROUND].PB(appModel);
    cubes[TECH_GROUND].reverseNormals();
    cubeBuffers(TECH_GROUND);

    //CIRCLE_LIGHT7:
    cylinders[CIRCLE_LIGHT7] = Cylinder(60.0f, 60.0f, 10.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-13460.0f, 230.0f, 300.0f));
    appModel = scale(appModel, vec3(3.0f, 3.0f, 3.0f));
    models[CIRCLE_LIGHT7].PB(appModel);
    for(int i=0; i<3; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 700.0f));
        models[CIRCLE_LIGHT7].PB(appModel);
    }
    cylinderBuffers(CIRCLE_LIGHT7);

    //WASHINGs:
    cubes[WASHING_BODY] = Cubesphere(350.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f, -700.0f, -800.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 0.9f));
    models[WASHING_BODY].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, 1300.0f));
    models[WASHING_BODY].PB(appModel);
    appModel = translate(appModel, vec3(-1400.0f, 0.0f, 0.0f));
    models[WASHING_BODY].PB(appModel);
    appModel = translate(curModel, vec3(-1400.0f, 0.0f, 0.0f));
    models[WASHING_BODY].PB(appModel);

    //for Oven:
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, 2400.0f));
    models[WASHING_BODY].PB(appModel);

    appModel = translate(appModel, vec3(0.0f, 0.0f, 800.0f));
    models[WASHING_BODY].PB(appModel);

    appModel = translate(appModel, vec3(0.0f, 0.0f, 800.0f));
    models[WASHING_BODY].PB(appModel);

    //for micro:
    appModel = translate(curModel, vec3(0.0f, 290.0f, 2400.0f));
    appModel = scale(appModel, vec3(0.5f, 0.4f, 0.8f));
    models[WASHING_BODY].PB(appModel);

    appModel = translate(appModel, vec3(0.0f, 0.0f, 980.0f));
    models[WASHING_BODY].PB(appModel);

    appModel = translate(appModel, vec3(0.0f, 0.0f, 980.0f));
    models[WASHING_BODY].PB(appModel);

    
    cubeBuffers(WASHING_BODY);    
    cubeBuffers(WASHING_BODY);

    //WASHING1:
    cubes[WASHING1] = Cubesphere(350.0f, 1, true);
    cubes[WASHING2] = Cubesphere(350.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f, -700.0f, -800.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 0.9f));
    models[WASHING1].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, 1300.0f));
    models[WASHING1].PB(appModel);
    appModel = translate(appModel, vec3(-1400.0f, 0.0f, 0.0f));
    models[WASHING2].PB(appModel);
    appModel = translate(curModel, vec3(-1400.0f, 0.0f, 0.0f));
    models[WASHING2].PB(appModel);

    
    cubeBuffers(WASHING1);
    cubeBuffers(WASHING2);

    //OVEN:
    cubes[OVEN] = Cubesphere(350.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -765.0f, 1365.0f));
    appModel = scale(appModel, vec3(1.0f, 1.55f, 2.05f));
    models[OVEN].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -765.0f, 2080.0f));
    appModel = scale(appModel, vec3(1.0f, 1.55f, 2.05f));
    models[OVEN].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -765.0f, 2800.0f));
    appModel = scale(appModel, vec3(1.0f, 1.55f, 2.05f));
    models[OVEN].PB(appModel);
    cubeBuffers(OVEN);

    //MICRO:
    cubes[MICRO] = Cubesphere(350.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1505.0f, -405.0f, 1355.0f));
    appModel = scale(appModel, vec3(1.0f, 0.48f, 0.74f));
    models[MICRO].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1505.0f, -405.0f, 2060.0f));
    appModel = scale(appModel, vec3(1.0f, 0.48f, 0.75f));
    models[MICRO].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1505.0f, -405.0f, 2765.0f));
    appModel = scale(appModel, vec3(1.0f, 0.48f, 0.75f));
    models[MICRO].PB(appModel);
    cubeBuffers(MICRO);

    //FRIDGEs:
    cubes[FRIDGE_BODY] = Cubesphere(400.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f, -430.0f, 5800.0f));
    appModel = scale(appModel, vec3(1.0f, 2.0f, 0.9f));
    models[FRIDGE_BODY].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, 1300.0f));
    models[FRIDGE_BODY].PB(appModel);
    appModel = translate(appModel, vec3(-1400.0f, 0.0f, 0.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 1.7f));
    models[FRIDGE_BODY].PB(appModel);
    appModel = translate(curModel, vec3(-1400.0f, 0.0f, 0.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 1.7f));
    models[FRIDGE_BODY].PB(appModel);
    
    cubeBuffers(FRIDGE_BODY);

    //FRIDGE1:
    cubes[FRIDGE1] = Cubesphere(400.0f, 1, true);
    cubes[FRIDGE2] = Cubesphere(400.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f, -430.0f, 5800.0f));
    appModel = scale(appModel, vec3(1.0f, 2.1f, 2.0f));
    models[FRIDGE2].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, 580.0f));
    models[FRIDGE2].PB(appModel);
    appModel = translate(appModel, vec3(-1400.0f, 0.0f, 0.0f));
    appModel = scale(appModel, vec3(1.0f, 1.04f, 1.03f));
    models[FRIDGE1].PB(appModel);
    appModel = translate(curModel, vec3(-1400.0f, 0.0f, 0.0f));
    appModel = scale(appModel, vec3(1.0f, 1.04f, 1.03f));
    models[FRIDGE1].PB(appModel);

    cubeBuffers(FRIDGE1);
    cubeBuffers(FRIDGE2);

    //STOVE:
    threeDModels[STOVE] = Model("../resources/objects/electric_stove_1k.fbx/electric_stove_1k.fbx");
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -900.0f, 4800.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(600.0f, 450.0f, 400.0f));
    models[STOVE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -900.0f, 4200.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(600.0f, 450.0f, 400.0f));
    models[STOVE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -900.0f, 3600.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(600.0f, 450.0f, 400.0f));
    models[STOVE].PB(appModel);
    threeDmodelBuffers(STOVE);

    cubes[TV] = Cubesphere(700.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-2055.0f, 0.0f, 4800.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    cubeBuffers(TV);

    cubes[SYRIA] = Cubesphere(700.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-2050.0f, 5.0f, 4800.0f));
    appModel = scale(appModel, vec3(1.0f, 0.5f, 0.5f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    cubeBuffers(SYRIA);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-13795.0, -750.0, -1570.0));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.2f, 4.0f));
    models[CASHIER6].PB(appModel);
    cubeBuffers(CASHIER6);

    //SCREEN:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-13795.0, -520.0, -1570.0));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12430.0f, -280.0f, -400.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(28.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12430.0f, 45.0f, 2280.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(18.1f, 4.3f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12430.0f, -280.0f, 5550.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(38.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    
    cubeBuffers(SHOP_BLOOR);
    //--------------------------------------------------------------------------------------------------

    //FIRST FLOOR:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-13460.0f, -300.0f + 1300.0f, 2850.0f)); 
    appModel = scale(appModel, vec3(3.5f, 2.1f, 16.9f)); 
    models[TECH_STORE].PB(appModel);
    cubes[TECH_STORE].reverseNormals();
    cubeBuffers(TECH_STORE);

    //TECH_GROUND
    appModel = MODEL;
    appModel = translate(appModel, vec3(-13460.0f, -900.0f + 1300.0f, 2850.0f)); 
    appModel = scale(appModel, vec3(3.5f, 0.005f, 16.9f)); 
    models[TECH_GROUND].PB(appModel);
    cubes[TECH_GROUND].reverseNormals();
    cubeBuffers(TECH_GROUND);

    //CIRCLE_LIGHT7:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-13460.0f, 230.0f+ 1300.0f, 300.0f));
    appModel = scale(appModel, vec3(3.0f, 3.0f, 3.0f));
    models[CIRCLE_LIGHT7].PB(appModel);
    for(int i=0; i<3; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 700.0f));
        models[CIRCLE_LIGHT7].PB(appModel);
    }
    cylinderBuffers(CIRCLE_LIGHT7);

    //WASHINGs:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f, -700.0f+ 1300.0f, -800.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 0.9f));
    models[WASHING_BODY].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, 1300.0f));
    models[WASHING_BODY].PB(appModel);
    appModel = translate(appModel, vec3(-1400.0f, 0.0f, 0.0f));
    models[WASHING_BODY].PB(appModel);
    appModel = translate(curModel, vec3(-1400.0f, 0.0f, 0.0f));
    models[WASHING_BODY].PB(appModel);

    //for Oven:
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, 2400.0f));
    models[WASHING_BODY].PB(appModel);

    appModel = translate(appModel, vec3(0.0f, 0.0f, 800.0f));
    models[WASHING_BODY].PB(appModel);

    appModel = translate(appModel, vec3(0.0f, 0.0f, 800.0f));
    models[WASHING_BODY].PB(appModel);

    //for micro:
    appModel = translate(curModel, vec3(0.0f, 290.0f, 2400.0f));
    appModel = scale(appModel, vec3(0.5f, 0.4f, 0.8f));
    models[WASHING_BODY].PB(appModel);

    appModel = translate(appModel, vec3(0.0f, 0.0f, 980.0f));
    models[WASHING_BODY].PB(appModel);

    appModel = translate(appModel, vec3(0.0f, 0.0f, 980.0f));
    models[WASHING_BODY].PB(appModel);

    
    cubeBuffers(WASHING_BODY);    
    cubeBuffers(WASHING_BODY);

    //WASHING1:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f, -700.0f+ 1300.0f, -800.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 0.9f));
    models[WASHING1].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, 1300.0f));
    models[WASHING1].PB(appModel);
    appModel = translate(appModel, vec3(-1400.0f, 0.0f, 0.0f));
    models[WASHING2].PB(appModel);
    appModel = translate(curModel, vec3(-1400.0f, 0.0f, 0.0f));
    models[WASHING2].PB(appModel);

    
    cubeBuffers(WASHING1);
    cubeBuffers(WASHING2);

    //OVEN:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -765.0f+ 1300.0f, 1365.0f));
    appModel = scale(appModel, vec3(1.0f, 1.55f, 2.05f));
    models[OVEN].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -765.0f+ 1300.0f, 2080.0f));
    appModel = scale(appModel, vec3(1.0f, 1.55f, 2.05f));
    models[OVEN].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -765.0f+ 1300.0f, 2800.0f));
    appModel = scale(appModel, vec3(1.0f, 1.55f, 2.05f));
    models[OVEN].PB(appModel);
    cubeBuffers(OVEN);

    //MICRO:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1505.0f, -405.0f+ 1300.0f, 1355.0f));
    appModel = scale(appModel, vec3(1.0f, 0.48f, 0.74f));
    models[MICRO].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1505.0f, -405.0f+ 1300.0f, 2060.0f));
    appModel = scale(appModel, vec3(1.0f, 0.48f, 0.75f));
    models[MICRO].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1505.0f, -405.0f+ 1300.0f, 2765.0f));
    appModel = scale(appModel, vec3(1.0f, 0.48f, 0.75f));
    models[MICRO].PB(appModel);
    cubeBuffers(MICRO);

    //FRIDGEs:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f, -430.0f+ 1300.0f, 5800.0f));
    appModel = scale(appModel, vec3(1.0f, 2.0f, 0.9f));
    models[FRIDGE_BODY].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, 1300.0f));
    models[FRIDGE_BODY].PB(appModel);
    appModel = translate(appModel, vec3(-1400.0f, 0.0f, 0.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 1.7f));
    models[FRIDGE_BODY].PB(appModel);
    appModel = translate(curModel, vec3(-1400.0f, 0.0f, 0.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 1.7f));
    models[FRIDGE_BODY].PB(appModel);
    
    cubeBuffers(FRIDGE_BODY);

    //FRIDGE1:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f, -430.0f+ 1300.0f, 5800.0f));
    appModel = scale(appModel, vec3(1.0f, 2.1f, 2.0f));
    models[FRIDGE2].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, 580.0f));
    models[FRIDGE2].PB(appModel);
    appModel = translate(appModel, vec3(-1400.0f, 0.0f, 0.0f));
    appModel = scale(appModel, vec3(1.0f, 1.04f, 1.03f));
    models[FRIDGE1].PB(appModel);
    appModel = translate(curModel, vec3(-1400.0f, 0.0f, 0.0f));
    appModel = scale(appModel, vec3(1.0f, 1.04f, 1.03f));
    models[FRIDGE1].PB(appModel);

    cubeBuffers(FRIDGE1);
    cubeBuffers(FRIDGE2);

    //STOVE:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -900.0f+ 1300.0f, 4800.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(600.0f, 450.0f, 400.0f));
    models[STOVE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -900.0f+ 1300.0f, 4200.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(600.0f, 450.0f, 400.0f));
    models[STOVE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -900.0f+ 1300.0f, 3600.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(600.0f, 450.0f, 400.0f));
    models[STOVE].PB(appModel);
    threeDmodelBuffers(STOVE);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-2055.0f, 0.0f+ 1300.0f, 4800.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    cubeBuffers(TV);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-2050.0f, 5.0f+ 1300.0f, 4800.0f));
    appModel = scale(appModel, vec3(1.0f, 0.5f, 0.5f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    cubeBuffers(SYRIA);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-13795.0, -750.0+ 1300.0f, -1570.0));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.2f, 4.0f));
    models[CASHIER6].PB(appModel);
    cubeBuffers(CASHIER6);

    //SCREEN:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-13795.0, -520.0+ 1300.0f, -1570.0));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12430.0f, -280.0f+ 1300.0f, -400.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(28.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12430.0f, 45.0f+ 1300.0f, 2280.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(18.1f, 4.3f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12430.0f, -280.0f+ 1300.0f, 5550.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(38.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    
    cubeBuffers(SHOP_BLOOR);
    //--------------------------------------------------------------------------------------------------
    
    //FIRST FLOOR:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-13460.0f, -300.0f + 2600.0f, 2850.0f)); 
    appModel = scale(appModel, vec3(3.5f, 2.1f, 16.9f)); 
    models[TECH_STORE].PB(appModel);
    cubes[TECH_STORE].reverseNormals();
    cubeBuffers(TECH_STORE);

    //TECH_GROUND
    appModel = MODEL;
    appModel = translate(appModel, vec3(-13460.0f, -900.0f + 2600.0f, 2850.0f)); 
    appModel = scale(appModel, vec3(3.5f, 0.005f, 16.9f)); 
    models[TECH_GROUND].PB(appModel);
    cubes[TECH_GROUND].reverseNormals();
    cubeBuffers(TECH_GROUND);

    //CIRCLE_LIGHT7:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-13460.0f, 230.0f+ 2600.0f, 300.0f));
    appModel = scale(appModel, vec3(3.0f, 3.0f, 3.0f));
    models[CIRCLE_LIGHT7].PB(appModel);
    for(int i=0; i<3; i++){
        appModel = translate(appModel, vec3(0.0f, 0.0f, 700.0f));
        models[CIRCLE_LIGHT7].PB(appModel);
    }
    cylinderBuffers(CIRCLE_LIGHT7);

    //WASHINGs:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f, -700.0f+ 2600.0f, -800.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 0.9f));
    models[WASHING_BODY].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, 1300.0f));
    models[WASHING_BODY].PB(appModel);
    appModel = translate(appModel, vec3(-1400.0f, 0.0f, 0.0f));
    models[WASHING_BODY].PB(appModel);
    appModel = translate(curModel, vec3(-1400.0f, 0.0f, 0.0f));
    models[WASHING_BODY].PB(appModel);

    //for Oven:
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, 2400.0f));
    models[WASHING_BODY].PB(appModel);

    appModel = translate(appModel, vec3(0.0f, 0.0f, 800.0f));
    models[WASHING_BODY].PB(appModel);

    appModel = translate(appModel, vec3(0.0f, 0.0f, 800.0f));
    models[WASHING_BODY].PB(appModel);

    //for micro:
    appModel = translate(curModel, vec3(0.0f, 290.0f, 2400.0f));
    appModel = scale(appModel, vec3(0.5f, 0.4f, 0.8f));
    models[WASHING_BODY].PB(appModel);

    appModel = translate(appModel, vec3(0.0f, 0.0f, 980.0f));
    models[WASHING_BODY].PB(appModel);

    appModel = translate(appModel, vec3(0.0f, 0.0f, 980.0f));
    models[WASHING_BODY].PB(appModel);

    
    cubeBuffers(WASHING_BODY);    
    cubeBuffers(WASHING_BODY);

    //WASHING1:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f, -700.0f+ 2600.0f, -800.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 0.9f));
    models[WASHING1].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, 1300.0f));
    models[WASHING1].PB(appModel);
    appModel = translate(appModel, vec3(-1400.0f, 0.0f, 0.0f));
    models[WASHING2].PB(appModel);
    appModel = translate(curModel, vec3(-1400.0f, 0.0f, 0.0f));
    models[WASHING2].PB(appModel);

    
    cubeBuffers(WASHING1);
    cubeBuffers(WASHING2);

    //OVEN:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -765.0f+ 2600.0f, 1365.0f));
    appModel = scale(appModel, vec3(1.0f, 1.55f, 2.05f));
    models[OVEN].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -765.0f+ 2600.0f, 2080.0f));
    appModel = scale(appModel, vec3(1.0f, 1.55f, 2.05f));
    models[OVEN].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -765.0f+ 2600.0f, 2800.0f));
    appModel = scale(appModel, vec3(1.0f, 1.55f, 2.05f));
    models[OVEN].PB(appModel);
    cubeBuffers(OVEN);

    //MICRO:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1505.0f, -405.0f+ 2600.0f, 1355.0f));
    appModel = scale(appModel, vec3(1.0f, 0.48f, 0.74f));
    models[MICRO].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1505.0f, -405.0f+ 2600.0f, 2060.0f));
    appModel = scale(appModel, vec3(1.0f, 0.48f, 0.75f));
    models[MICRO].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1505.0f, -405.0f+ 2600.0f, 2765.0f));
    appModel = scale(appModel, vec3(1.0f, 0.48f, 0.75f));
    models[MICRO].PB(appModel);
    cubeBuffers(MICRO);

    //FRIDGEs:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f, -430.0f+ 2600.0f, 5800.0f));
    appModel = scale(appModel, vec3(1.0f, 2.0f, 0.9f));
    models[FRIDGE_BODY].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, 1300.0f));
    models[FRIDGE_BODY].PB(appModel);
    appModel = translate(appModel, vec3(-1400.0f, 0.0f, 0.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 1.7f));
    models[FRIDGE_BODY].PB(appModel);
    appModel = translate(curModel, vec3(-1400.0f, 0.0f, 0.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 1.7f));
    models[FRIDGE_BODY].PB(appModel);
    
    cubeBuffers(FRIDGE_BODY);

    //FRIDGE1:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f, -430.0f+ 2600.0f, 5800.0f));
    appModel = scale(appModel, vec3(1.0f, 2.1f, 2.0f));
    models[FRIDGE2].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(0.0f, 0.0f, 580.0f));
    models[FRIDGE2].PB(appModel);
    appModel = translate(appModel, vec3(-1400.0f, 0.0f, 0.0f));
    appModel = scale(appModel, vec3(1.0f, 1.04f, 1.03f));
    models[FRIDGE1].PB(appModel);
    appModel = translate(curModel, vec3(-1400.0f, 0.0f, 0.0f));
    appModel = scale(appModel, vec3(1.0f, 1.04f, 1.03f));
    models[FRIDGE1].PB(appModel);

    cubeBuffers(FRIDGE1);
    cubeBuffers(FRIDGE2);

    //STOVE:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -900.0f+ 2600.0f, 4800.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(600.0f, 450.0f, 400.0f));
    models[STOVE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -900.0f+ 2600.0f, 4200.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(600.0f, 450.0f, 400.0f));
    models[STOVE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-1400.0f, -900.0f+ 2600.0f, 3600.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = rotate(appModel, radians(-90.0f), Z);
    appModel = scale(appModel, vec3(600.0f, 450.0f, 400.0f));
    models[STOVE].PB(appModel);
    threeDmodelBuffers(STOVE);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-2055.0f, 0.0f+ 2600.0f, 4800.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[TV].PB(appModel);
    cubeBuffers(TV);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-12800.0f-2050.0f, 5.0f+ 2600.0f, 4800.0f));
    appModel = scale(appModel, vec3(1.0f, 0.5f, 0.5f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -2000.0f));
    models[SYRIA].PB(appModel);
    cubeBuffers(SYRIA);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-13795.0, -750.0+ 2600.0f, -1570.0));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(1.0f, 1.2f, 4.0f));
    models[CASHIER6].PB(appModel);
    cubeBuffers(CASHIER6);

    //SCREEN:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-13795.0, -520.0+ 2600.0f, -1570.0));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12430.0f, -280.0f+ 2600.0f, -400.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(28.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12430.0f, 45.0f+ 2600.0f, 2280.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(18.1f, 4.3f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12430.0f, -280.0f+ 2600.0f, 5550.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(38.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    
    cubeBuffers(SHOP_BLOOR);
    //--------------------------------------------------------------------------------------------------
    
    //INSIDE_ROOF:
    toruses[INSIDE_ROOF] = Torus(1.0f, 0.2f, 4, 50, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4750.0, 350.0, 3650.0));
    appModel = scale(appModel, vec3(2.15*4250.0f, 100.0f, 1.8*3800.0f));
    appModel = rotate(appModel, radians(45.0f), Y);
    models[INSIDE_ROOF].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4750.0, 350.0f+1300.0f, 3650.0));
    appModel = scale(appModel, vec3(2.15*4250.0f, 100.0f, 1.8*3800.0f));
    appModel = rotate(appModel, radians(45.0f), Y);
    models[INSIDE_ROOF].PB(appModel);
    torusBuffers(INSIDE_ROOF);

    //first wall:::::::::::::::
    cubes[ROOF_WALL] = Cubesphere(1000.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4750.0f, 550.0f, -250.0f));
    appModel = scale(appModel, vec3(9.2f, 0.33f, 0.1f));
    models[ROOF_WALL].PB(appModel);
    
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4750.0f, 550.0f, 7550.0f));
    appModel = scale(appModel, vec3(9.2f, 0.33f, 0.1f));
    models[ROOF_WALL].PB(appModel);

    appModel = MODEL;
    appModel = translate(appModel, vec3(500.0f, 550.0f, 6000.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(2.6f, 0.33f, 0.1f));
    models[ROOF_WALL].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(500.0f, 550.0f, 1140.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(2.41f, 0.33f, 0.1f));
    models[ROOF_WALL].PB(appModel);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-9950.0f, 550.0f, 6000.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(2.6f, 0.33f, 0.1f));
    models[ROOF_WALL].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9950.0f, 550.0f, 1140.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(2.41f, 0.33f, 0.1f));
    models[ROOF_WALL].PB(appModel);
    cubeBuffers(ROOF_WALL);

    //second wall:::::::::::::::
    cubes[ROOF_WALL] = Cubesphere(1000.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4750.0f, 550.0f + 1300.0f, -250.0f));
    appModel = scale(appModel, vec3(9.2f, 0.33f, 0.1f));
    models[ROOF_WALL].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4750.0f, 550.0f + 1300.0f, 7550.0f));
    appModel = scale(appModel, vec3(9.2f, 0.33f, 0.1f));
    models[ROOF_WALL].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(600.0f, 550.0f + 1300.0f, 3650.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(6.65f, 0.33f, 0.1f));
    models[ROOF_WALL].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9950.0f, 550.0f + 1300.0f, 6000.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(2.6f, 0.33f, 0.1f));
    models[ROOF_WALL].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9950.0f, 550.0f + 1300.0f, 1140.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(2.41f, 0.33f, 0.1f));
    models[ROOF_WALL].PB(appModel);
    cubeBuffers(ROOF_WALL);

    //COLUMN:
    //LEFT:
    cylinders[COLUMN] = Cylinder(250.0f, 250.0f, 3950.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(0.0f, 1050.0f, -300.0f));
    models[COLUMN].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[COLUMN].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[COLUMN].PB(appModel);
    appModel = translate(appModel, vec3(-3300.0f, 0.0f, 0.0f));
    models[COLUMN].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[COLUMN].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[COLUMN].PB(appModel);
    //RIGHT
    appModel = MODEL;
    appModel = translate(appModel, vec3(0.0f, 1050.0f, 7500.0f));
    models[COLUMN].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[COLUMN].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[COLUMN].PB(appModel);
    appModel = translate(appModel, vec3(-3300.0f, 0.0f, 0.0f));
    models[COLUMN].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[COLUMN].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[COLUMN].PB(appModel);
    cylinderBuffers(COLUMN);
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    //JEWELRY STORE:
    //Ground Floor:+++++++++++++++++++++++++++++++++++++++++++++++++

    cubes[JEWELRY_STORE] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -300.0f, -2850.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 2.1f, 9.2f)); 
    models[JEWELRY_STORE].PB(appModel);
    cubeBuffers(JEWELRY_STORE);

    //JEWELRY_GROUND
    cubes[JEWELRY_GROUND] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -900.0f, -2850.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 0.005f, 9.2f)); 
    models[JEWELRY_GROUND].PB(appModel);
    cubes[JEWELRY_GROUND].reverseNormals();
    cubeBuffers(JEWELRY_GROUND);

    //CIRCLE_LIGHT8:
    cylinders[CIRCLE_LIGHT8] = Cylinder(80.0f, 80.0f, 10.0f, 6, 1, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500+320.0f, 280.0f, -2900.0f));
    models[CIRCLE_LIGHT8].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT8].PB(appModel);
    appModel = translate(appModel, vec3(3000.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT8].PB(appModel);
    cylinderBuffers(CIRCLE_LIGHT8);

    //DISPLAY_BASE:
    cubes[DISPLAY_BASE] = Cubesphere(400.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -700.0f, -2300.0f));
    appModel = scale(appModel, vec3(9.5f, 0.8f, 1.0f));
    models[DISPLAY_BASE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -280.0f, -2300.0f));
    appModel = scale(appModel, vec3(9.5f, 0.1f, 1.0f));
    models[DISPLAY_BASE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -700.0f, -3500.0f));
    appModel = scale(appModel, vec3(9.5f, 0.8f, 1.0f));
    models[DISPLAY_BASE].PB(appModel);
    cubeBuffers(DISPLAY_BASE);

    //DISPLAY_VIEW:
    cubes[DISPLAY_VIEW] = Cubesphere(400.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -400.0f, -2300.0f));
    appModel = scale(appModel, vec3(9.5f, 0.4f, 1.0f));
    models[DISPLAY_VIEW].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -100.0f, -2300.0f));
    appModel = scale(appModel, vec3(9.5f, 0.6f, 1.0f));
    models[DISPLAY_VIEW].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -400.0f, -3500.0f));
    appModel = scale(appModel, vec3(9.5f, 0.4f, 1.0f));
    models[DISPLAY_VIEW].PB(appModel);
    cubeBuffers(DISPLAY_VIEW);

    //CASHIER8:
    cubes[CASHIER8] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-7150.0f, -710.0f, -3050.0f));
    appModel = scale(appModel, vec3(1.0f, 1.4f, 3.0f));
    models[CASHIER8].PB(appModel);
    cubeBuffers(CASHIER8);

    //SCREEN:
    cubes[SCREEN] =Cubesphere(50.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-7150.0f, -460.0f, -3050.0f));
    appModel = rotate(appModel, radians(189.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //JEW1:
    toruses[JEW1] = Torus(30.0f*1.0f, 30.0f*0.2f, 36, 4, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12000.0f, -490.0f, -2210.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(700.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    torusBuffers(JEW1);

    //JEW2:
    toruses[JEW2] = Torus(30.0f*1.0f, 30.0f*0.2f, 23, 4, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12000.0f, -490.0f, -2410.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(700.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    torusBuffers(JEW2);

    //JEW3:
    toruses[JEW3] = Torus(10.0f*1.0f, 10.0f*0.2f, 10, 9, true, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -490.0f, -2210.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    torusBuffers(JEW3);

    //STONE:
    cylinders[STONE] = Cylinder(4.3f*1.2f, 4.3f*0.6f, 1.5f, 6, 11, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -477.0f, -2410.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    cylinderBuffers(STONE);

    //JEW4:
    toruses[JEW4] = Torus(10.0f*1.0f, 10.0f*0.2f, 10, 9, false, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -490.0f, -2410.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    torusBuffers(JEW4);

    //STONE2:
    cylinders[STONE2] = Cylinder(4.2f*0.3f, 4.0f*0.55f, 1.7f, 6, 11, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -477.0f, -2210.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    cylinderBuffers(STONE2);

    //JEW5:
    toruses[JEW5] = Torus(5.0*1.0f, 5.0*0.7f, 14, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -477.0f, -2210.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 2.0f));
    models[JEW5].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW5].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW5].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW5].PB(appModel);
    }
    torusBuffers(JEW5);

    //JEW6:
    toruses[JEW6] = Torus(5.0*1.0f, 5.0*0.7f, 14, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -477.0f, -2410.0f));
    models[JEW6].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW6].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW6].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW6].PB(appModel);
    }
    torusBuffers(JEW6);

    //JEW7:
    toruses[JEW7] = Torus(5.0*0.01f, 5.0*0.9f, 3, 3, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9000.0f, -477.0f, -2210.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 2.0f));
    models[JEW7].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW7].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW7].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW7].PB(appModel);
    }
    torusBuffers(JEW7);

    //JEW8:
    toruses[JEW8] = Torus(13.0*0.01f, 13.0*0.3f, 11, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9000.0f, -477.0f, -2410.0f));
    models[JEW8].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW8].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW8].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW8].PB(appModel);
    }
    torusBuffers(JEW8);

    cones[JEW9] = Cone(60.0f*1.5f, 60.0f*1.2f, 4, 1, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8300.0f, -440.0f, -2210.0f));
    models[JEW9].PB(appModel);
    coneBuffers(JEW9);

    cylinders[JEW10] = Cylinder(10.0f*1.0f, 10.0f*1.0f, 10.0f*0.2f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8100.0f, -480.0f, -2210.0f));
    models[JEW10].PB(appModel);
    for(int i=0; i<7; i++){
        appModel = translate(appModel, vec3(50.0f, 0.0f, 0.0f));
        models[JEW10].PB(appModel);
    }
    cylinderBuffers(JEW10);

    cylinders[JEW11] = Cylinder(10.0f*1.0f, 10.0f*1.0f, 10.0f*0.2f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8100.0f, -480.0f, -2410.0f));
    for(int i=0; i<8; i++){
        models[JEW11].PB(appModel);
        appModel = translate(appModel, vec3(50.0f, 0.0f, 0.0f));
    }
    cylinderBuffers(JEW11);

    //second display:
    //JEW1:
    toruses[JEW1] = Torus(30.0f*1.0f, 30.0f*0.2f, 36, 4, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12000.0f, -490.0f, -2210.0f -1200.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(700.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    torusBuffers(JEW1);

    //JEW2:
    toruses[JEW2] = Torus(30.0f*1.0f, 30.0f*0.2f, 23, 4, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12000.0f, -490.0f, -2410.0f-1200.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(700.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    torusBuffers(JEW2);

    //JEW3:
    toruses[JEW3] = Torus(10.0f*1.0f, 10.0f*0.2f, 10, 9, true, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -490.0f, -2210.0f-1200.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    torusBuffers(JEW3);

    //STONE:
    cylinders[STONE] = Cylinder(4.3f*1.2f, 4.3f*0.6f, 1.5f, 6, 11, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -477.0f, -2410.0f-1200.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    cylinderBuffers(STONE);

    //JEW4:
    toruses[JEW4] = Torus(10.0f*1.0f, 10.0f*0.2f, 10, 9, false, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -490.0f, -2410.0f-1200.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    torusBuffers(JEW4);

    //STONE2:
    cylinders[STONE2] = Cylinder(4.2f*0.3f, 4.0f*0.55f, 1.7f, 6, 11, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -477.0f, -2210.0f-1200.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    cylinderBuffers(STONE2);

    //JEW5:
    toruses[JEW5] = Torus(5.0*1.0f, 5.0*0.7f, 14, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -477.0f, -2210.0f-1200.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 2.0f));
    models[JEW5].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW5].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW5].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW5].PB(appModel);
    }
    torusBuffers(JEW5);

    //JEW6:
    toruses[JEW6] = Torus(5.0*1.0f, 5.0*0.7f, 14, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -477.0f, -2410.0f-1200.0f));
    models[JEW6].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW6].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW6].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW6].PB(appModel);
    }
    torusBuffers(JEW6);

    //JEW7:
    toruses[JEW7] = Torus(5.0*0.01f, 5.0*0.9f, 3, 3, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9000.0f, -477.0f, -2210.0f-1200.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 2.0f));
    models[JEW7].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW7].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW7].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW7].PB(appModel);
    }
    torusBuffers(JEW7);

    //JEW8:
    toruses[JEW8] = Torus(13.0*0.01f, 13.0*0.3f, 11, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9000.0f, -477.0f, -2410.0f-1200.0f));
    models[JEW8].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW8].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW8].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW8].PB(appModel);
    }
    torusBuffers(JEW8);

    cones[JEW9] = Cone(60.0f*1.5f, 60.0f*1.2f, 4, 1, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8300.0f, -440.0f, -2210.0f-1200.0f));
    models[JEW9].PB(appModel);
    coneBuffers(JEW9);

    cylinders[JEW10] = Cylinder(10.0f*1.0f, 10.0f*1.0f, 10.0f*0.2f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8100.0f, -480.0f, -2210.0f-1200.0f));
    models[JEW10].PB(appModel);
    for(int i=0; i<7; i++){
        appModel = translate(appModel, vec3(50.0f, 0.0f, 0.0f));
        models[JEW10].PB(appModel);
    }
    cylinderBuffers(JEW10);

    cylinders[JEW11] = Cylinder(10.0f*1.0f, 10.0f*1.0f, 10.0f*0.2f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8100.0f, -480.0f, -2410.0f-1200.0f));
    for(int i=0; i<8; i++){
        models[JEW11].PB(appModel);
        appModel = translate(appModel, vec3(50.0f, 0.0f, 0.0f));
    }
    cylinderBuffers(JEW11);

    //JEW12:
    toruses[JEW12] = Torus(50.0f*1.3f, 50.0f*0.15f, 20, 16, true, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12000.0f, -100.0f, -2210.0f));
    appModel = rotate(appModel, radians(-20.0f), X);
    appModel = scale(appModel, vec3(1.0f, 1.7f, 1.0f));
    models[JEW12].PB(appModel);
    for(float i = 700.0f; i<4000.0f; i+=700.0f){
        appModel = MODEL;
        appModel = translate(appModel, vec3(-12000.0f + i, -100.0f, -2210.0f));
        appModel = rotate(appModel, radians(-20.0f), X);
        appModel = scale(appModel, vec3(1.0f, 1.7f, 1.0f));
        models[JEW12].PB(appModel);
    }
    torusBuffers(JEW12);

    //JEW13:
    toruses[JEW13] = Torus(50.0f*1.3f, 50.0f*0.15f, 20, 16, false, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -100.0f, -2210.0f));
    appModel = rotate(appModel, radians(-20.0f), X);
    appModel = scale(appModel, vec3(1.0f, 1.7f, 1.0f));
    models[JEW13].PB(appModel);
    for(float i = 700.0f; i<4000.0f; i+=700.0f){
        appModel = MODEL;
        appModel = translate(appModel, vec3(-11600.0f + i, -100.0f, -2210.0f));
        appModel = rotate(appModel, radians(-20.0f), X);
        appModel = scale(appModel, vec3(1.0f, 1.7f, 1.0f));
        models[JEW13].PB(appModel);
    }
    torusBuffers(JEW13);

    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9770.0f, -280.0f, -2000.0f));
    appModel = scale(appModel, vec3(41.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-7120.0f, 50.0f, -2000.0f));
    appModel = scale(appModel, vec3(4.4f, 4.0f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    cubeBuffers(SHOP_BLOOR);
    //----------------------------------------------------------------------------------------
    //First Floor:+++++++++++++++++++++++++++++++++++++++++++++++++

    cubes[JEWELRY_STORE] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -300.0f + 1300.0f, -2850.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 2.1f, 9.2f)); 
    models[JEWELRY_STORE].PB(appModel);
    cubeBuffers(JEWELRY_STORE);

    //JEWELRY_GROUND
    cubes[JEWELRY_GROUND] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -900.0f+ 1300.0f, -2850.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 0.005f, 9.2f)); 
    models[JEWELRY_GROUND].PB(appModel);
    cubes[JEWELRY_GROUND].reverseNormals();
    cubeBuffers(JEWELRY_GROUND);

    //CIRCLE_LIGHT8:
    cylinders[CIRCLE_LIGHT8] = Cylinder(80.0f, 80.0f, 10.0f, 6, 1, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500+320.0f, 280.0f+ 1300.0f, -2900.0f));
    models[CIRCLE_LIGHT8].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT8].PB(appModel);
    appModel = translate(appModel, vec3(3000.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT8].PB(appModel);
    cylinderBuffers(CIRCLE_LIGHT8);

    //DISPLAY_BASE:
    cubes[DISPLAY_BASE] = Cubesphere(400.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -700.0f+ 1300.0f, -2300.0f));
    appModel = scale(appModel, vec3(9.5f, 0.8f, 1.0f));
    models[DISPLAY_BASE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -280.0f+ 1300.0f, -2300.0f));
    appModel = scale(appModel, vec3(9.5f, 0.1f, 1.0f));
    models[DISPLAY_BASE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -700.0f+ 1300.0f, -3500.0f));
    appModel = scale(appModel, vec3(9.5f, 0.8f, 1.0f));
    models[DISPLAY_BASE].PB(appModel);
    cubeBuffers(DISPLAY_BASE);

    //DISPLAY_VIEW:
    cubes[DISPLAY_VIEW] = Cubesphere(400.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -400.0f+ 1300.0f, -2300.0f));
    appModel = scale(appModel, vec3(9.5f, 0.4f, 1.0f));
    models[DISPLAY_VIEW].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -100.0f+ 1300.0f, -2300.0f));
    appModel = scale(appModel, vec3(9.5f, 0.6f, 1.0f));
    models[DISPLAY_VIEW].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -400.0f+ 1300.0f, -3500.0f));
    appModel = scale(appModel, vec3(9.5f, 0.4f, 1.0f));
    models[DISPLAY_VIEW].PB(appModel);
    cubeBuffers(DISPLAY_VIEW);

    //CASHIER8:
    cubes[CASHIER8] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-7150.0f, -710.0f+ 1300.0f, -3050.0f));
    appModel = scale(appModel, vec3(1.0f, 1.4f, 3.0f));
    models[CASHIER8].PB(appModel);
    cubeBuffers(CASHIER8);

    //SCREEN:
    cubes[SCREEN] =Cubesphere(50.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-7150.0f, -460.0f+ 1300.0f, -3050.0f));
    appModel = rotate(appModel, radians(189.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //JEW1:
    toruses[JEW1] = Torus(30.0f*1.0f, 30.0f*0.2f, 36, 4, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12000.0f, -490.0f+ 1300.0f, -2210.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(700.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    torusBuffers(JEW1);

    //JEW2:
    toruses[JEW2] = Torus(30.0f*1.0f, 30.0f*0.2f, 23, 4, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12000.0f, -490.0f+ 1300.0f, -2410.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(700.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    torusBuffers(JEW2);

    //JEW3:
    toruses[JEW3] = Torus(10.0f*1.0f, 10.0f*0.2f, 10, 9, true, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -490.0f+ 1300.0f, -2210.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    torusBuffers(JEW3);

    //STONE:
    cylinders[STONE] = Cylinder(4.3f*1.2f, 4.3f*0.6f, 1.5f, 6, 11, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -477.0f+ 1300.0f, -2410.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    cylinderBuffers(STONE);

    //JEW4:
    toruses[JEW4] = Torus(10.0f*1.0f, 10.0f*0.2f, 10, 9, false, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -490.0f+ 1300.0f, -2410.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    torusBuffers(JEW4);

    //STONE2:
    cylinders[STONE2] = Cylinder(4.2f*0.3f, 4.0f*0.55f, 1.7f, 6, 11, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -477.0f+ 1300.0f, -2210.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    cylinderBuffers(STONE2);

    //JEW5:
    toruses[JEW5] = Torus(5.0*1.0f, 5.0*0.7f, 14, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -477.0f+ 1300.0f, -2210.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 2.0f));
    models[JEW5].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW5].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW5].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW5].PB(appModel);
    }
    torusBuffers(JEW5);

    //JEW6:
    toruses[JEW6] = Torus(5.0*1.0f, 5.0*0.7f, 14, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -477.0f+ 1300.0f, -2410.0f));
    models[JEW6].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW6].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW6].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW6].PB(appModel);
    }
    torusBuffers(JEW6);

    //JEW7:
    toruses[JEW7] = Torus(5.0*0.01f, 5.0*0.9f, 3, 3, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9000.0f, -477.0f+ 1300.0f, -2210.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 2.0f));
    models[JEW7].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW7].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW7].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW7].PB(appModel);
    }
    torusBuffers(JEW7);

    //JEW8:
    toruses[JEW8] = Torus(13.0*0.01f, 13.0*0.3f, 11, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9000.0f, -477.0f+ 1300.0f, -2410.0f));
    models[JEW8].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW8].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW8].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW8].PB(appModel);
    }
    torusBuffers(JEW8);

    cones[JEW9] = Cone(60.0f*1.5f, 60.0f*1.2f, 4, 1, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8300.0f, -440.0f+ 1300.0f, -2210.0f));
    models[JEW9].PB(appModel);
    coneBuffers(JEW9);

    cylinders[JEW10] = Cylinder(10.0f*1.0f, 10.0f*1.0f, 10.0f*0.2f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8100.0f, -480.0f+ 1300.0f, -2210.0f));
    models[JEW10].PB(appModel);
    for(int i=0; i<7; i++){
        appModel = translate(appModel, vec3(50.0f, 0.0f, 0.0f));
        models[JEW10].PB(appModel);
    }
    cylinderBuffers(JEW10);

    cylinders[JEW11] = Cylinder(10.0f*1.0f, 10.0f*1.0f, 10.0f*0.2f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8100.0f, -480.0f+ 1300.0f, -2410.0f));
    for(int i=0; i<8; i++){
        models[JEW11].PB(appModel);
        appModel = translate(appModel, vec3(50.0f, 0.0f, 0.0f));
    }
    cylinderBuffers(JEW11);

    //second display:
    //JEW1:
    toruses[JEW1] = Torus(30.0f*1.0f, 30.0f*0.2f, 36, 4, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12000.0f, -490.0f+ 1300.0f, -2210.0f -1200.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(700.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    torusBuffers(JEW1);

    //JEW2:
    toruses[JEW2] = Torus(30.0f*1.0f, 30.0f*0.2f, 23, 4, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12000.0f, -490.0f+ 1300.0f, -2410.0f-1200.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(700.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    torusBuffers(JEW2);

    //JEW3:
    toruses[JEW3] = Torus(10.0f*1.0f, 10.0f*0.2f, 10, 9, true, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -490.0f+ 1300.0f, -2210.0f-1200.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    torusBuffers(JEW3);

    //STONE:
    cylinders[STONE] = Cylinder(4.3f*1.2f, 4.3f*0.6f, 1.5f, 6, 11, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -477.0f+ 1300.0f, -2410.0f-1200.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    cylinderBuffers(STONE);

    //JEW4:
    toruses[JEW4] = Torus(10.0f*1.0f, 10.0f*0.2f, 10, 9, false, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -490.0f+ 1300.0f, -2410.0f-1200.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    torusBuffers(JEW4);

    //STONE2:
    cylinders[STONE2] = Cylinder(4.2f*0.3f, 4.0f*0.55f, 1.7f, 6, 11, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -477.0f+ 1300.0f, -2210.0f-1200.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    cylinderBuffers(STONE2);

    //JEW5:
    toruses[JEW5] = Torus(5.0*1.0f, 5.0*0.7f, 14, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -477.0f+ 1300.0f, -2210.0f-1200.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 2.0f));
    models[JEW5].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW5].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW5].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW5].PB(appModel);
    }
    torusBuffers(JEW5);

    //JEW6:
    toruses[JEW6] = Torus(5.0*1.0f, 5.0*0.7f, 14, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -477.0f+ 1300.0f, -2410.0f-1200.0f));
    models[JEW6].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW6].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW6].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW6].PB(appModel);
    }
    torusBuffers(JEW6);

    //JEW7:
    toruses[JEW7] = Torus(5.0*0.01f, 5.0*0.9f, 3, 3, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9000.0f, -477.0f+ 1300.0f, -2210.0f-1200.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 2.0f));
    models[JEW7].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW7].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW7].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW7].PB(appModel);
    }
    torusBuffers(JEW7);

    //JEW8:
    toruses[JEW8] = Torus(13.0*0.01f, 13.0*0.3f, 11, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9000.0f, -477.0f+ 1300.0f, -2410.0f-1200.0f));
    models[JEW8].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW8].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW8].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW8].PB(appModel);
    }
    torusBuffers(JEW8);

    cones[JEW9] = Cone(60.0f*1.5f, 60.0f*1.2f, 4, 1, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8300.0f, -440.0f+ 1300.0f, -2210.0f-1200.0f));
    models[JEW9].PB(appModel);
    coneBuffers(JEW9);

    cylinders[JEW10] = Cylinder(10.0f*1.0f, 10.0f*1.0f, 10.0f*0.2f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8100.0f, -480.0f+ 1300.0f, -2210.0f-1200.0f));
    models[JEW10].PB(appModel);
    for(int i=0; i<7; i++){
        appModel = translate(appModel, vec3(50.0f, 0.0f, 0.0f));
        models[JEW10].PB(appModel);
    }
    cylinderBuffers(JEW10);

    cylinders[JEW11] = Cylinder(10.0f*1.0f, 10.0f*1.0f, 10.0f*0.2f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8100.0f, -480.0f+ 1300.0f, -2410.0f-1200.0f));
    for(int i=0; i<8; i++){
        models[JEW11].PB(appModel);
        appModel = translate(appModel, vec3(50.0f, 0.0f, 0.0f));
    }
    cylinderBuffers(JEW11);

    //JEW12:
    toruses[JEW12] = Torus(50.0f*1.3f, 50.0f*0.15f, 20, 16, true, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12000.0f, -100.0f+ 1300.0f, -2210.0f));
    appModel = rotate(appModel, radians(-20.0f), X);
    appModel = scale(appModel, vec3(1.0f, 1.7f, 1.0f));
    models[JEW12].PB(appModel);
    for(float i = 700.0f; i<4000.0f; i+=700.0f){
        appModel = MODEL;
        appModel = translate(appModel, vec3(-12000.0f + i, -100.0f+ 1300.0f, -2210.0f));
        appModel = rotate(appModel, radians(-20.0f), X);
        appModel = scale(appModel, vec3(1.0f, 1.7f, 1.0f));
        models[JEW12].PB(appModel);
    }
    torusBuffers(JEW12);

    //JEW13:
    toruses[JEW13] = Torus(50.0f*1.3f, 50.0f*0.15f, 20, 16, false, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -100.0f+ 1300.0f, -2210.0f));
    appModel = rotate(appModel, radians(-20.0f), X);
    appModel = scale(appModel, vec3(1.0f, 1.7f, 1.0f));
    models[JEW13].PB(appModel);
    for(float i = 700.0f; i<4000.0f; i+=700.0f){
        appModel = MODEL;
        appModel = translate(appModel, vec3(-11600.0f + i, -100.0f+ 1300.0f, -2210.0f));
        appModel = rotate(appModel, radians(-20.0f), X);
        appModel = scale(appModel, vec3(1.0f, 1.7f, 1.0f));
        models[JEW13].PB(appModel);
    }
    torusBuffers(JEW13);

    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9780.0f, -280.0f + 1300.0f, -2000.0f));
    appModel = scale(appModel, vec3(41.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-7120.0f, 50.0f + 1300.0f, -2000.0f));
    appModel = scale(appModel, vec3(4.4f, 4.0f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    cubeBuffers(SHOP_BLOOR);
    //--------------------------------------------------------------------------------------------
    //Second Floor:+++++++++++++++++++++++++++++++++++++++++++++++++

    cubes[JEWELRY_STORE] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -300.0f + 2600.0f, -2850.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 2.1f, 9.2f)); 
    models[JEWELRY_STORE].PB(appModel);
    cubeBuffers(JEWELRY_STORE);

    //JEWELRY_GROUND
    cubes[JEWELRY_GROUND] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -900.0f+ 2600.0f, -2850.0f)); //oldZ = -2850 , I added 13150
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(3.0f, 0.005f, 9.2f)); 
    models[JEWELRY_GROUND].PB(appModel);
    cubes[JEWELRY_GROUND].reverseNormals();
    cubeBuffers(JEWELRY_GROUND);

    //CIRCLE_LIGHT8:
    cylinders[CIRCLE_LIGHT8] = Cylinder(80.0f, 80.0f, 10.0f, 6, 1, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500+320.0f, 280.0f+ 2600.0f, -2900.0f));
    models[CIRCLE_LIGHT8].PB(appModel);
    appModel = translate(appModel, vec3(-1500.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT8].PB(appModel);
    appModel = translate(appModel, vec3(3000.0f, 0.0f, 0.0f));
    models[CIRCLE_LIGHT8].PB(appModel);
    cylinderBuffers(CIRCLE_LIGHT8);

    //DISPLAY_BASE:
    cubes[DISPLAY_BASE] = Cubesphere(400.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -700.0f+ 2600.0f, -2300.0f));
    appModel = scale(appModel, vec3(9.5f, 0.8f, 1.0f));
    models[DISPLAY_BASE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -280.0f+ 2600.0f, -2300.0f));
    appModel = scale(appModel, vec3(9.5f, 0.1f, 1.0f));
    models[DISPLAY_BASE].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -700.0f+ 2600.0f, -3500.0f));
    appModel = scale(appModel, vec3(9.5f, 0.8f, 1.0f));
    models[DISPLAY_BASE].PB(appModel);
    cubeBuffers(DISPLAY_BASE);

    //DISPLAY_VIEW:
    cubes[DISPLAY_VIEW] = Cubesphere(400.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -400.0f+ 2600.0f, -2300.0f));
    appModel = scale(appModel, vec3(9.5f, 0.4f, 1.0f));
    models[DISPLAY_VIEW].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -100.0f+ 2600.0f, -2300.0f));
    appModel = scale(appModel, vec3(9.5f, 0.6f, 1.0f));
    models[DISPLAY_VIEW].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9900.0f, -400.0f+ 2600.0f, -3500.0f));
    appModel = scale(appModel, vec3(9.5f, 0.4f, 1.0f));
    models[DISPLAY_VIEW].PB(appModel);
    cubeBuffers(DISPLAY_VIEW);

    //CASHIER8:
    cubes[CASHIER8] = Cubesphere(200.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-7150.0f, -710.0f+ 2600.0f, -3050.0f));
    appModel = scale(appModel, vec3(1.0f, 1.4f, 3.0f));
    models[CASHIER8].PB(appModel);
    cubeBuffers(CASHIER8);

    //SCREEN:
    cubes[SCREEN] =Cubesphere(50.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-7150.0f, -460.0f+ 2600.0f, -3050.0f));
    appModel = rotate(appModel, radians(189.0f), Y);
    appModel = scale(appModel, vec3(0.1f, 1.6f, 2.8f));
    models[SCREEN].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, -35.0f, 0.0f));
    appModel = scale(appModel, vec3(2.0f, 0.6f, 0.2f));
    models[SCREEN].PB(appModel);
    cubeBuffers(SCREEN);

    //JEW1:
    toruses[JEW1] = Torus(30.0f*1.0f, 30.0f*0.2f, 36, 4, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12000.0f, -490.0f+ 2600.0f, -2210.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(700.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    torusBuffers(JEW1);

    //JEW2:
    toruses[JEW2] = Torus(30.0f*1.0f, 30.0f*0.2f, 23, 4, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12000.0f, -490.0f+ 2600.0f, -2410.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(700.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    torusBuffers(JEW2);

    //JEW3:
    toruses[JEW3] = Torus(10.0f*1.0f, 10.0f*0.2f, 10, 9, true, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -490.0f+ 2600.0f, -2210.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    torusBuffers(JEW3);

    //STONE:
    cylinders[STONE] = Cylinder(4.3f*1.2f, 4.3f*0.6f, 1.5f, 6, 11, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -477.0f+ 2600.0f, -2410.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    cylinderBuffers(STONE);

    //JEW4:
    toruses[JEW4] = Torus(10.0f*1.0f, 10.0f*0.2f, 10, 9, false, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -490.0f+ 2600.0f, -2410.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    torusBuffers(JEW4);

    //STONE2:
    cylinders[STONE2] = Cylinder(4.2f*0.3f, 4.0f*0.55f, 1.7f, 6, 11, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -477.0f+ 2600.0f, -2210.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    cylinderBuffers(STONE2);

    //JEW5:
    toruses[JEW5] = Torus(5.0*1.0f, 5.0*0.7f, 14, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -477.0f+ 2600.0f, -2210.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 2.0f));
    models[JEW5].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW5].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW5].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW5].PB(appModel);
    }
    torusBuffers(JEW5);

    //JEW6:
    toruses[JEW6] = Torus(5.0*1.0f, 5.0*0.7f, 14, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -477.0f+ 2600.0f, -2410.0f));
    models[JEW6].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW6].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW6].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW6].PB(appModel);
    }
    torusBuffers(JEW6);

    //JEW7:
    toruses[JEW7] = Torus(5.0*0.01f, 5.0*0.9f, 3, 3, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9000.0f, -477.0f+ 2600.0f, -2210.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 2.0f));
    models[JEW7].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW7].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW7].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW7].PB(appModel);
    }
    torusBuffers(JEW7);

    //JEW8:
    toruses[JEW8] = Torus(13.0*0.01f, 13.0*0.3f, 11, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9000.0f, -477.0f+ 2600.0f, -2410.0f));
    models[JEW8].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW8].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW8].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW8].PB(appModel);
    }
    torusBuffers(JEW8);

    cones[JEW9] = Cone(60.0f*1.5f, 60.0f*1.2f, 4, 1, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8300.0f, -440.0f+ 2600.0f, -2210.0f));
    models[JEW9].PB(appModel);
    coneBuffers(JEW9);

    cylinders[JEW10] = Cylinder(10.0f*1.0f, 10.0f*1.0f, 10.0f*0.2f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8100.0f, -480.0f+ 2600.0f, -2210.0f));
    models[JEW10].PB(appModel);
    for(int i=0; i<7; i++){
        appModel = translate(appModel, vec3(50.0f, 0.0f, 0.0f));
        models[JEW10].PB(appModel);
    }
    cylinderBuffers(JEW10);

    cylinders[JEW11] = Cylinder(10.0f*1.0f, 10.0f*1.0f, 10.0f*0.2f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8100.0f, -480.0f+ 2600.0f, -2410.0f));
    for(int i=0; i<8; i++){
        models[JEW11].PB(appModel);
        appModel = translate(appModel, vec3(50.0f, 0.0f, 0.0f));
    }
    cylinderBuffers(JEW11);

    //second display:
    //JEW1:
    toruses[JEW1] = Torus(30.0f*1.0f, 30.0f*0.2f, 36, 4, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12000.0f, -490.0f+ 2600.0f, -2210.0f -1200.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(700.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW1].PB(appModel);
    torusBuffers(JEW1);

    //JEW2:
    toruses[JEW2] = Torus(30.0f*1.0f, 30.0f*0.2f, 23, 4, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12000.0f, -490.0f+ 2600.0f, -2410.0f-1200.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(700.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW2].PB(appModel);
    torusBuffers(JEW2);

    //JEW3:
    toruses[JEW3] = Torus(10.0f*1.0f, 10.0f*0.2f, 10, 9, true, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -490.0f+ 2600.0f, -2210.0f-1200.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW3].PB(appModel);
    torusBuffers(JEW3);

    //STONE:
    cylinders[STONE] = Cylinder(4.3f*1.2f, 4.3f*0.6f, 1.5f, 6, 11, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -477.0f+ 2600.0f, -2410.0f-1200.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE].PB(appModel);
    cylinderBuffers(STONE);

    //JEW4:
    toruses[JEW4] = Torus(10.0f*1.0f, 10.0f*0.2f, 10, 9, false, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -490.0f+ 2600.0f, -2410.0f-1200.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[JEW4].PB(appModel);
    torusBuffers(JEW4);

    //STONE2:
    cylinders[STONE2] = Cylinder(4.2f*0.3f, 4.0f*0.55f, 1.7f, 6, 11, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -477.0f+ 2600.0f, -2210.0f-1200.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(1000.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    appModel = translate(appModel, vec3(100.0f, 0.0f, 0.0f));
    models[STONE2].PB(appModel);
    cylinderBuffers(STONE2);

    //JEW5:
    toruses[JEW5] = Torus(5.0*1.0f, 5.0*0.7f, 14, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -477.0f+ 2600.0f, -2210.0f-1200.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 2.0f));
    models[JEW5].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW5].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW5].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW5].PB(appModel);
    }
    torusBuffers(JEW5);

    //JEW6:
    toruses[JEW6] = Torus(5.0*1.0f, 5.0*0.7f, 14, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, -477.0f+ 2600.0f, -2410.0f-1200.0f));
    models[JEW6].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW6].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW6].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW6].PB(appModel);
    }
    torusBuffers(JEW6);

    //JEW7:
    toruses[JEW7] = Torus(5.0*0.01f, 5.0*0.9f, 3, 3, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9000.0f, -477.0f+ 2600.0f, -2210.0f-1200.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 2.0f));
    models[JEW7].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW7].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW7].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW7].PB(appModel);
    }
    torusBuffers(JEW7);

    //JEW8:
    toruses[JEW8] = Torus(13.0*0.01f, 13.0*0.3f, 11, 5, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9000.0f, -477.0f+ 2600.0f, -2410.0f-1200.0f));
    models[JEW8].PB(appModel);
    appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
    models[JEW8].PB(appModel);
    for(int i=0; i<5; i++){
        appModel = translate(appModel, vec3(80.0f, 0.0f, 0.0f));
        models[JEW8].PB(appModel);
        appModel = translate(appModel, vec3(20.0f, 0.0f, 0.0f));
        models[JEW8].PB(appModel);
    }
    torusBuffers(JEW8);

    cones[JEW9] = Cone(60.0f*1.5f, 60.0f*1.2f, 4, 1, false, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8300.0f, -440.0f+ 2600.0f, -2210.0f-1200.0f));
    models[JEW9].PB(appModel);
    coneBuffers(JEW9);

    cylinders[JEW10] = Cylinder(10.0f*1.0f, 10.0f*1.0f, 10.0f*0.2f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8100.0f, -480.0f+ 2600.0f, -2210.0f-1200.0f));
    models[JEW10].PB(appModel);
    for(int i=0; i<7; i++){
        appModel = translate(appModel, vec3(50.0f, 0.0f, 0.0f));
        models[JEW10].PB(appModel);
    }
    cylinderBuffers(JEW10);

    cylinders[JEW11] = Cylinder(10.0f*1.0f, 10.0f*1.0f, 10.0f*0.2f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8100.0f, -480.0f+ 2600.0f, -2410.0f-1200.0f));
    for(int i=0; i<8; i++){
        models[JEW11].PB(appModel);
        appModel = translate(appModel, vec3(50.0f, 0.0f, 0.0f));
    }
    cylinderBuffers(JEW11);

    //JEW12:
    toruses[JEW12] = Torus(50.0f*1.3f, 50.0f*0.15f, 20, 16, true, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-12000.0f, -100.0f+ 2600.0f, -2210.0f));
    appModel = rotate(appModel, radians(-20.0f), X);
    appModel = scale(appModel, vec3(1.0f, 1.7f, 1.0f));
    models[JEW12].PB(appModel);
    for(float i = 700.0f; i<4000.0f; i+=700.0f){
        appModel = MODEL;
        appModel = translate(appModel, vec3(-12000.0f + i, -100.0f+ 2600.0f, -2210.0f));
        appModel = rotate(appModel, radians(-20.0f), X);
        appModel = scale(appModel, vec3(1.0f, 1.7f, 1.0f));
        models[JEW12].PB(appModel);
    }
    torusBuffers(JEW12);

    //JEW13:
    toruses[JEW13] = Torus(50.0f*1.3f, 50.0f*0.15f, 20, 16, false, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-11600.0f, -100.0f+ 2600.0f, -2210.0f));
    appModel = rotate(appModel, radians(-20.0f), X);
    appModel = scale(appModel, vec3(1.0f, 1.7f, 1.0f));
    models[JEW13].PB(appModel);
    for(float i = 700.0f; i<4000.0f; i+=700.0f){
        appModel = MODEL;
        appModel = translate(appModel, vec3(-11600.0f + i, -100.0f+ 2600.0f, -2210.0f));
        appModel = rotate(appModel, radians(-20.0f), X);
        appModel = scale(appModel, vec3(1.0f, 1.7f, 1.0f));
        models[JEW13].PB(appModel);
    }
    torusBuffers(JEW13);

    //SHOP_BLOOR
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9780.0f, -280.0f + 2600.0f, -2000.0f));
    appModel = scale(appModel, vec3(41.0f, 9.8f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-7120.0f, 50.0f + 2600.0f, -2000.0f));
    appModel = scale(appModel, vec3(4.4f, 4.0f, 0.05f));
    models[SHOP_BLOOR].PB(appModel);
    cubeBuffers(SHOP_BLOOR);

    //PALM:
    //LEFT SIDE:

    threeDModels[PALM] = Model("../resources/objects/date_palm/scene.gltf");
    appModel = MODEL;
    appModel = translate(appModel, vec3(-3200.0f, -1200.0f, 3500.0f -300.0f));
    appModel = scale(appModel, vec3(5.0f, 4.0f, 5.0f)); 
    models[PALM].PB(appModel);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-3000.0f, -1200.0f, 4000.0f -300.0f));
    appModel = scale(appModel, vec3(5.0f, 5.0f, 5.0f)); 
    models[PALM].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-3400.0f, -1200.0f, 4450.0f -300.0f));
    appModel = scale(appModel, vec3(5.0f, 5.0f, 5.0f)); 
    models[PALM].PB(appModel);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-3200.0f, -1200.0f, 5000.0f-300.0f));
    appModel = scale(appModel, vec3(5.0f, 6.0f, 5.0f)); 
    models[PALM].PB(appModel);

    //RIGHT SIDE:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-6200.0f, -1200.0f, 3500.0f-300.0f));
    appModel = scale(appModel, vec3(5.0f, 4.0f, 5.0f)); 
    models[PALM].PB(appModel);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-6000.0f, -1200.0f, 4000.0f-300.0f));
    appModel = scale(appModel, vec3(5.0f, 5.0f, 5.0f)); 
    models[PALM].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-6400.0f, -1200.0f, 4450.0f-300.0f));
    appModel = scale(appModel, vec3(5.0f, 5.0f, 5.0f)); 
    models[PALM].PB(appModel);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-6200.0f, -1200.0f, 5000.0f-300.0f));
    appModel = scale(appModel, vec3(5.0f, 6.0f, 5.0f)); 
    models[PALM].PB(appModel);

    threeDmodelBuffers(PALM);

    //PALM_LEAVES:
    //LEFT SIDE:

    threeDModels[PALM_LEAVES] = Model("../resources/objects/date_palm/scene.gltf");
    appModel = MODEL;
    appModel = translate(appModel, vec3(-3200.0f, -100.0f, 3500.0f-300.0f));
    appModel = scale(appModel, vec3(2.0f, 2.0f, 2.0f)); 
    models[PALM_LEAVES].PB(appModel);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-3000.0f, 450.0f, 4000.0f-300.0f));
    appModel = scale(appModel, vec3(2.0f, 2.0f, 2.0f)); 
    models[PALM_LEAVES].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-3400.0f, 450.0f, 4450.0f-300.0f));
    appModel = scale(appModel, vec3(2.0f, 2.0f, 2.0f)); 
    models[PALM_LEAVES].PB(appModel);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-3200.0f, 500.0f, 5000.0f-300.0f));
    appModel = scale(appModel, vec3(3.0f, 3.0f, 3.0f)); 
    models[PALM_LEAVES].PB(appModel);

    //RIGHT SIDE:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-6200.0f, -100.0f, 3500.0f-300.0f));
    appModel = scale(appModel, vec3(2.0f, 2.0f, 2.0f)); 
    models[PALM_LEAVES].PB(appModel);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-6000.0f, 450.0f, 4000.0f-300.0f));
    appModel = scale(appModel, vec3(2.0f, 2.0f, 2.0f)); 
    models[PALM_LEAVES].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-6400.0f, 450.0f, 4450.0f-300.0f));
    appModel = scale(appModel, vec3(2.0f, 2.0f, 2.0f)); 
    models[PALM_LEAVES].PB(appModel);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-6200.0f, 500.0f, 5000.0f-300.0f));
    appModel = scale(appModel, vec3(3.0f, 3.0f, 3.0f)); 
    models[PALM_LEAVES].PB(appModel);

    threeDmodelBuffers(PALM_LEAVES);
    //--------------------------------------------------------------------------------

    //ELEVATOR START HERE:

    //..ELEVATOR_BAR:
    cylinders[ELEVATOR_BAR] = Cylinder(70.0f * 1.0f, 70.0f * 1.0f, 4100.0f *1.0f, 36, 1, true, 2);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9000.0f, 1100.0f, 4000.0f));
    models[ELEVATOR_BAR].PB(appModel);
    appModel = translate(appModel, vec3(0.0f, 0.0f, -1000.0f));
    models[ELEVATOR_BAR].PB(appModel);
    cylinderBuffers(ELEVATOR_BAR);

    //..ELEVATOR_BLOOR:
    cubes[ELEVATOR_BLOOR] = Cubesphere(100.0*1.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9500.0f, 500.0f, 3500.0f));
    appModel = rotate(appModel, radians(180.0f), Y);
    appModel = scale(appModel, vec3(7.0f, 47.0f, 10.0f));
    models[ELEVATOR_BLOOR].PB(appModel);
    cubeBuffers(ELEVATOR_BLOOR);

    //ELEVATOR_BODY:
    cubes[ELEVATOR_BODY] = Cubesphere(98.0*1.0, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9530.0f, -900.0f, 3500.0f));
    appModel = scale(appModel, vec3(7.0f, 0.2f, 10.0f));
    models[ELEVATOR_BODY].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9530.0f, 200.0f, 3500.0f));
    appModel = scale(appModel, vec3(7.0f, 3.0f, 10.0f));
    models[ELEVATOR_BODY].PB(appModel);
    models[ELEVATOR_BODY].resize(2);
    cubeBuffers(ELEVATOR_BODY);

    //ELEVATOR_INSIDE:
    cubes[ELEVATOR_INSIDE] = Cubesphere(98.0*1.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9780.0f, -430.0f, 2950.0f));
    appModel = scale(appModel, vec3(2.0f, 8.1f, 0.1f));
    models[ELEVATOR_INSIDE].PB(appModel);
    models[ELEVATOR_INSIDE].resize(1);
    cubeBuffers(ELEVATOR_INSIDE);

    //BUTTOMS:
    cubes[BUTTOMS] = Cubesphere(98.0*1.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9780.0f, -430.0f, 2960.0f));
    appModel = scale(appModel, vec3(1.0f, 1.0f, 0.05f));
    models[BUTTOMS].PB(appModel);
    models[BUTTOMS].resize(1);
    cubeBuffers(BUTTOMS);

    //ELEVATOR_ENTRY: the Diffence between left and right is 1455.0f
    //GROUND FLOOR::::::::::::::::
    //LEFT:
    cubes[ELEVATOR_ENTRY] = Cubesphere(100.0*1.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9940.0f, -300.0f, 2850.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(5.2f, 11.0f, 0.1f));
    models[ELEVATOR_ENTRY].PB(appModel);
    //RIGHT:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9940.0f, -300.0f, 4195.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(5.2f, 11.0f, 0.1f));
    models[ELEVATOR_ENTRY].PB(appModel);
    cubeBuffers(ELEVATOR_ENTRY);

    //ELEVATOR_DOOR: the Diffence between left and right is 1455.0f
    //LEFT:
    cubes[ELEVATOR_DOOR] = Cubesphere(95.0*1.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9940.0f, -300.0f, 2850.0f));
    appModel = scale(appModel, vec3(0.03f, 10.0f, 4.5f));
    models[ELEVATOR_DOOR].PB(appModel);
    //RIGHT:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9940.0f, -300.0f, 4195.0f));
    appModel = scale(appModel, vec3(0.03f, 10.0f, 4.5f));
    models[ELEVATOR_DOOR].PB(appModel);
    cubeBuffers(ELEVATOR_DOOR);

    //FIRST FLOOR::::::::::::::::
    //LEFT:
    cubes[ELEVATOR_ENTRY] = Cubesphere(100.0*1.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9940.0f, -300.0f + 1300.0f, 2850.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(5.2f, 11.0f, 0.1f));
    models[ELEVATOR_ENTRY].PB(appModel);
    //RIGHT:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9940.0f, -300.0f+ 1300.0f, 4195.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(5.2f, 11.0f, 0.1f));
    models[ELEVATOR_ENTRY].PB(appModel);
    cubeBuffers(ELEVATOR_ENTRY);

    //ELEVATOR_DOOR: the Diffence between left and right is 1455.0f
    //LEFT:
    cubes[ELEVATOR_DOOR] = Cubesphere(95.0*1.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9940.0f, -300.0f+ 1300.0f, 2850.0f));
    appModel = scale(appModel, vec3(0.03f, 10.0f, 4.5f));
    models[ELEVATOR_DOOR].PB(appModel);
    //RIGHT:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9940.0f, -300.0f+ 1300.0f, 4195.0f));
    appModel = scale(appModel, vec3(0.03f, 10.0f, 4.5f));
    models[ELEVATOR_DOOR].PB(appModel);
    cubeBuffers(ELEVATOR_DOOR);


    //SECOND FLOOR::::::::::::::::
    //LEFT:
    cubes[ELEVATOR_ENTRY] = Cubesphere(100.0*1.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9940.0f, -300.0f + 2600.0f, 2850.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(5.2f, 11.0f, 0.1f));
    models[ELEVATOR_ENTRY].PB(appModel);
    //RIGHT:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9940.0f, -300.0f+ 2600.0f, 4195.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(5.2f, 11.0f, 0.1f));
    models[ELEVATOR_ENTRY].PB(appModel);
    cubeBuffers(ELEVATOR_ENTRY);

    //ELEVATOR_DOOR: the Diffence between left and right is 1455.0f
    //LEFT:
    cubes[ELEVATOR_DOOR] = Cubesphere(95.0*1.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9940.0f, -300.0f+ 2600.0f, 2850.0f));
    appModel = scale(appModel, vec3(0.03f, 10.0f, 4.5f));
    models[ELEVATOR_DOOR].PB(appModel);
    //RIGHT:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-9940.0f, -300.0f+ 2600.0f, 4195.0f));
    appModel = scale(appModel, vec3(0.03f, 10.0f, 4.5f));
    models[ELEVATOR_DOOR].PB(appModel);
    models[ELEVATOR_DOOR].resize(6);
    cubeBuffers(ELEVATOR_DOOR);

    //ESCALATOR:
    cubes[ESCALATOR] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1500.0f, -950.0f, 3000.0f));
    appModel = scale(appModel, vec3(0.1f, 0.1f, 0.6f));
    models[ESCALATOR].PB(appModel);
    for(int i=0; i<35; i++){
        appModel = translate(appModel, vec3(567.0f, 350.0f, 0.0f));
        models[ESCALATOR].PB(appModel);
    }
    cubeBuffers(ESCALATOR);

    //ESCALATOR2:
    cubes[ESCALATOR2] = Cubesphere(500.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1500.0f, -950.0f, 4000.0f));
    appModel = scale(appModel, vec3(0.1f, 0.1f, 0.6f));
    models[ESCALATOR2].PB(appModel);
    for(int i=0; i<35; i++){
        appModel = translate(appModel, vec3(567.0f, 350.0f, 0.0f));
        models[ESCALATOR2].PB(appModel);
    }
    cubeBuffers(ESCALATOR2);
    models[ESCALATOR].resize(36);
    models[ESCALATOR2].resize(36);

    //ESC_BASE:
    cubes[ESC_BASE] = Cubesphere(500.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-700.0f, -550.0f, 3000.0f));
    appModel = rotate(appModel, radians(120.0f), Z);
    appModel = scale(appModel, vec3(0.3f, 5.0f, 0.65f));
    models[ESC_BASE].PB(appModel);
    //For the second:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-700.0f, -550.0f, 4000.0f));
    appModel = rotate(appModel, radians(120.0f), Z);
    appModel = scale(appModel, vec3(0.3f, 5.0f, 0.65f));
    models[ESC_BASE].PB(appModel);
    cubeBuffers(ESC_BASE);

    //ESC_ARM:
    cubes[ESC_ARM] = Cubesphere(500.0f, 1, true);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-500.0f, -300.0f, 2800.0f));
    appModel = rotate(appModel, radians(120.0f), Z);
    appModel = scale(appModel, vec3(0.5f, 4.1f, 0.07f));
    models[ESC_ARM].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-500.0f, -300.0f, 3200.0f));
    appModel = rotate(appModel, radians(120.0f), Z);
    appModel = scale(appModel, vec3(0.5f, 4.1f, 0.07f));
    models[ESC_ARM].PB(appModel);

    //for the second:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-500.0f, -300.0f, 3800.0f));
    appModel = rotate(appModel, radians(120.0f), Z);
    appModel = scale(appModel, vec3(0.5f, 4.1f, 0.07f));
    models[ESC_ARM].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-500.0f, -300.0f, 4200.0f));
    appModel = rotate(appModel, radians(120.0f), Z);
    appModel = scale(appModel, vec3(0.5f, 4.1f, 0.07f));
    models[ESC_ARM].PB(appModel);
    cubeBuffers(ESC_ARM);

    //ROAD:
    cubes[ROAD] = Cubesphere(2000.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-7000.0f, -1200.0f, -11000.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(3.5f, 0.01f, 14.0f));
    models[ROAD].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(13250.0f, -1200.0f, 3000.0f));
    appModel = scale(appModel, vec3(3.5f, 0.01f, 20.0f));
    models[ROAD].PB(appModel);
    cubeBuffers(ROAD);

    //OUTSIDE_GROUND:
    cubes[OUTSIDE_GROUND] = Cubesphere(2000.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(0.0f, -1250.0f, 0.0f));
    appModel = scale(appModel, vec3(50.0f, 0.01f, 50.0f));
    models[OUTSIDE_GROUND].PB(appModel);
    cubeBuffers(OUTSIDE_GROUND);

    //PAVING:
    cubes[PAVING] = Cubesphere(2000.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-7000.0f, -1150.0f, -11000.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(0.15f, 0.05f, 0.5f));
    models[PAVING].PB(appModel);
    for(int i=1; i<=8; i++){
        appModel = MODEL;
        appModel = translate(appModel, vec3(-7000.0f - ((i*1150.0f)), -1150.0f, -11000.0f));
        appModel = rotate(appModel, radians(90.0f), Y);
        appModel = scale(appModel, vec3(0.15f, 0.05f, 0.5f));
        models[PAVING].PB(appModel);
    }
    for(int i=1; i<=6; i++){
        appModel = MODEL;
        appModel = translate(appModel, vec3(-6000.0f + ((i*1150.0f)), -1150.0f, -11000.0f));
        appModel = rotate(appModel, radians(90.0f), Y);
        appModel = scale(appModel, vec3(0.15f, 0.05f, 0.5f));
        models[PAVING].PB(appModel);
    }
    for(int i=7; i<=11; i++){
        appModel = MODEL;
        appModel = translate(appModel, vec3(-5000.0f + ((i*1150.0f)), -1150.0f, -11000.0f));
        appModel = rotate(appModel, radians(90.0f), Y);
        appModel = scale(appModel, vec3(0.15f, 0.05f, 0.5f));
        models[PAVING].PB(appModel);
    }

    //RIGHT:
    appModel = MODEL;
    appModel = translate(appModel, vec3(-7000.0f, -1150.0f, -15800.0f));
    appModel = rotate(appModel, radians(90.0f), Y);
    appModel = scale(appModel, vec3(0.7f, 0.05f, 0.5f));
    models[PAVING].PB(appModel);
    for(int i=1; i<=8; i++){
        appModel = MODEL;
        appModel = translate(appModel, vec3(-7000.0f - ((i*1150.0f)), -1150.0f, -15800.0f));
        appModel = rotate(appModel, radians(90.0f), Y);
        appModel = scale(appModel, vec3(0.7f, 0.05f, 0.5f));
        models[PAVING].PB(appModel);
    }
    for(int i=1; i<=13; i++){
        appModel = MODEL;
        appModel = translate(appModel, vec3(-7000.0f + ((i*1150.0f)), -1150.0f, -15800.0f));
        appModel = rotate(appModel, radians(90.0f), Y);
        appModel = scale(appModel, vec3(0.7f, 0.05f, 0.5f));
        models[PAVING].PB(appModel);
    }
    cubeBuffers(PAVING);

    //STREET_LIGHT:
    threeDModels[STREET_LIGHT] = Model("../resources/objects/park-light/source/park light/park light.fbx");
    appModel = MODEL;
    appModel = translate(appModel, vec3(-6000.0f, -970.0f, -7000.0f));
    appModel = scale(appModel, vec3(3.0f, 3.0f, 3.0f));
    models[STREET_LIGHT].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-2400.0f, -970.0f, -7000.0f));
    appModel = scale(appModel, vec3(3.0f, 3.0f, 3.0f));
    models[STREET_LIGHT].PB(appModel);
    threeDmodelBuffers(STREET_LIGHT);

    //MALL_LIGHT:
    // 
    threeDModels[MALL_LIGHT] = Model("../resources/objects/hanging_light/scene.gltf");
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1000.0f, 3270.0f, 1000.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = scale(appModel, vec3(600.0f, 600.0f, 300.0f));
    models[MALL_LIGHT].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-1000.0f, 3270.0f, 5500.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = scale(appModel, vec3(600.0f, 600.0f, 300.0f));
    models[MALL_LIGHT].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8500.0f, 3270.0f, 1000.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = scale(appModel, vec3(600.0f, 600.0f, 300.0f));
    models[MALL_LIGHT].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-8500.0f, 3270.0f, 5500.0f));
    appModel = rotate(appModel, radians(-90.0f), X);
    appModel = scale(appModel, vec3(600.0f, 1000.0f, 300.0f));
    models[MALL_LIGHT].PB(appModel);
    threeDmodelBuffers(MALL_LIGHT);

    //BUILDINGs:
    //RIGHT:
    cubes[BUILDING] = Cubesphere(4000.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-7000.0f, 1100.0f, -19000.0f));
    appModel = scale(appModel, vec3(0.7f, 1.0f, 1.0f));
    models[BUILDING].PB(appModel);
    curModel = appModel;
    appModel = translate(appModel, vec3(7000.0f, 0.0f, 0.0f));
    models[BUILDING].PB(appModel);
    appModel = translate(appModel, vec3(7000.0f, 0.0f, 0.0f));
    models[BUILDING].PB(appModel);

    appModel = translate(curModel, vec3(-7000.0f, 0.0f, 0.0f));
    models[BUILDING].PB(appModel);
    appModel = translate(curModel, vec3(-7000.0f, 0.0f, 0.0f));
    models[BUILDING].PB(appModel);

    //LEFT:
    appModel = MODEL;
    appModel = translate(appModel, vec3(18000.0f, 1100.0f, -1000.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(0.7f, 1.0f, 1.0f));
    models[BUILDING].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(18000.0f, 1100.0f, 6000.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(0.7f, 1.0f, 1.0f));
    models[BUILDING].PB(appModel);
    appModel = MODEL;
    appModel = translate(appModel, vec3(18000.0f, 1100.0f, 13000.0f));
    appModel = rotate(appModel, radians(-90.0f), Y);
    appModel = scale(appModel, vec3(0.7f, 1.0f, 1.0f));
    models[BUILDING].PB(appModel);

    
    cubeBuffers(BUILDING);

    //SMALL_TREEs:
    threeDModels[SMALL_TREE] = Model("../resources/objects/othonna_cerarioides_1k.gltf/othonna_cerarioides_1k.gltf");
    appModel = MODEL;
    appModel = translate(appModel, vec3(7000.0f, -1100.0f, -11000.0f));
    appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
    models[SMALL_TREE].PB(appModel);
    for(int i=1; i<=6; i++){
        appModel = MODEL;
        appModel = translate(appModel, vec3(7000.0f - (i*3500.0f), -1100.0f, -11000.0f));
        appModel = scale(appModel, vec3(500.0f, 500.0f, 500.0f));
        models[SMALL_TREE].PB(appModel);
    }

    threeDmodelBuffers(SMALL_TREE);    
}










void Scene::squareBuffers(string name)
{
    GLsizeiptr num = 32 * sizeof(float);
    std::vector<float> vertices = {
        // positions          // normals          // texture coords
        0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f    // top left            
    }; 
    //..vbo:
    VBO vbo(vertices, num);
    //..instanceVBO:
    VBO instanceVBO(models[name], (int)models[name].size());
    //..vao:
    vaos[name] = VAO() ; vaos[name].init(vbo, instanceVBO);
    std::vector<int> indeces = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    //..ebo:
    GLsizeiptr si = 6  * sizeof(float);
    ebos[name] = EBO(indeces, si);
}

void Scene::coneBuffers(string name)
{
    //..vbo:
    VBO vbo(cones[name].getInterleavedVertices(), cones[name].getInterleavedVertexSize());
    //..instanceVBO:
    VBO instanceVBO(models[name], (int)models[name].size());
    //..vao:
    vaos[name] = VAO() ; vaos[name].init(vbo, instanceVBO);
    //..ebo:
    ebos[name] = EBO(cones[name].getIndices(), cones[name].getIndexSize());
}

void Scene::cylinderBuffers(string name)
{
    //..vbo:
    VBO vbo(cylinders[name].getInterleavedVertices(), cylinders[name].getInterleavedVertexSize());
    //..instanceVBO:
    VBO instanceVBO(models[name], (int)models[name].size());
    //..vao:
    vaos[name] = VAO() ; vaos[name].init(vbo, instanceVBO);
    //..ebo:
    ebos[name] = EBO(cylinders[name].getIndices(), cylinders[name].getIndexSize());
}


void Scene::torusBuffers(string name)
{
    //..vbo:
    VBO vbo(toruses[name].getInterleavedVertices(), toruses[name].getInterleavedVertexSize());
    //..instanceVBO:
    VBO instanceVBO(models[name], (int)models[name].size());
    //..vao:
    vaos[name] = VAO() ; vaos[name].init(vbo, instanceVBO);
    //..ebo:
    ebos[name] = EBO(toruses[name].getIndices(), toruses[name].getIndexSize());
}

void Scene::cubeBuffers(string name)
{
    //..vbo:
    VBO vbo(cubes[name].getInterleavedVertices(), cubes[name].getInterleavedVertexSize());
    //..instanceVBO:
    VBO instanceVBO(models[name], (int)models[name].size());
    //..vao:
    vaos[name] = VAO() ; vaos[name].init(vbo, instanceVBO);
    //..ebo:
    ebos[name] = EBO(cubes[name].getIndices(), cubes[name].getIndexSize());
} 

void Scene::threeDmodelBuffers(string name)
{
    //..instanceVBO:
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, models[name].size() * sizeof(glm::mat4), models[name].data(), GL_STATIC_DRAW);
    for (unsigned int i = 0; i < threeDModels[name].meshes.size(); i++)
    {
        unsigned int VAO = threeDModels[name].meshes[i].VAO;
        glBindVertexArray(VAO);
        // set attribute pointers for matrix (4 times vec4)
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
    }
} 