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
    REF = "reflection",
    MAIN = "main",
    SKYBOX = "skybox",

    
    //Textures
    CONCRETE = "concrete",
    CONCRETE_SPEC = "concreteSpec",

    BLUE_WINDOW = "blueWindow",
    BLUE_WINDOW_SPEC = "blueWindowSpec",

    LIGHT_METAL = "lightMetal",
    LIGHT_METAL_SPEC = "lightMetalSpec",

    GRAY_BRICK = "grayBrick",
    GRAY_BRICK_SPEC = "grayBrickSpec",

    WHITE_WINDOW = "whiteWindow",
    WHITE_WINDOW_SPEC = "whiteWindowSpec",

    BLOOR = "bloor",
    BLOOR_SPEC = "bloorSpec",

    BLACK_TILE = "blackTile",
    BLACK_TILE_SPEC = "blackTileSpec",

    GRAY_TILES = "grayTiles",     
    GRAY_TILES_SPEC = "grayTilesSpec",
    
    WHITE_TILES = "whiteTiles",     
    WHITE_TILES_SPEC = "whiteTilesSpec",
    

    //Objects:

    //..Outside The mall:

    SPECIAL_BUILDING = "specialBuilding",
    BACK_WALL = "backWall",
    ROOF_BUILDING = "roofBuilding",
    SPECIAL_VIEW = "specialVIEW",
    CYL_BUILDING = "cylBuilding",
    CYL_ADDITIONAL = "cylAdditional",
    GLASS_ROOF = "glassRoof",
    ENTRY = "entry",
    ENTRY_BLOOR = "entryBloor",
    SIDE_WALK = "sideWalk",
    GROUND = "ground",


    STREND = "strend";
};

#endif