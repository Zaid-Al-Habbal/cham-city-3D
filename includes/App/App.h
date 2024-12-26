#ifndef APP_H
#define APP_H

#include <iostream>
#include <map>

using namespace std;

class App
{
public:
    const string
    
    //Shaders:
    MAIN = "main",
    SKYBOX = "skybox",

    
    //Textures
    CONCRETE = "concrete",
    CONCRETE_SPEC = "concreteSpec",

    BLUE_WINDOW = "blueWindow",
    BLUE_WINDOW_SPEC = "blueWindowSpec",

    LIGHT_METAL = "lightMetal",
    LIGHT_METAL_SPEC = "lightMetalSpec",

    TILE_WINDOW ="tileWindow",
    TILE_WINDOW_SPEC ="tileWindowSpec",

    GRAY_BRICK = "grayBrick",
    GRAY_BRICK_SPEC = "grayBrickSpec",

    WHITE_WINDOW = "whiteWindow",
    WHITE_WINDOW_SPEC = "whiteWindowSpec",

    BLUR_WINDOW = "blurWindow",
    BLUR_WINDOW_SPEC = "blurWindowSpec",

    //Objects:
    SPECIAL_BUILDING = "specialBuilding",
    BACK_WALL = "backWall",
    ROOF_BUILDING = "roofBuilding",
    SPECIAL_VIEW = "specialVIEW",
    CYL_BUILDING = "cylBuilding",
    CYL_ADDITIONAL = "cylAdditional",
    GLASS_ROOF = "glassRoof",


    STREND = "strend";
};

#endif