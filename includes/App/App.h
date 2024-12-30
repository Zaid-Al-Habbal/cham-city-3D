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
    BLUE_WINDOW = "blueWindow",

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

    BLACK_PAINT = "blackPaint",
    BLACK_PAINT_SPEC = "blackPaintSpec",

    WOOD1 = "wood1",
    WOOD1_SPEC = "wood1Spec",

    WHITE = "white",

    SUITE1_TEX = "suit1Tex",
    SUITE2_TEX = "suit2Tex",

    BLACK = "black",
    

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
    

    //Inside the Mall:
    GROUND = "ground",
    //SUITE_SHOP:
    SUITE_SHOP = "suiteShop",
    SUITE1_OBJ = "suite1Obj",
    SUITE2_OBJ = "suite2Obj",
    CIRCLE_LIGHT = "circleLight",
    CLOTHS_PLACE = "clothsPlace",
    CASHIER = "cashier",
    SCREEN = "screen", 
    MIRROR = "mirror",
    SUITE_REF = "suiteRef",
    SHOP_BLOOR = "shopBloor",


    STREND = "strend";
};

#endif