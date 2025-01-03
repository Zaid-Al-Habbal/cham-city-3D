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

    SHIRT1_TEX = "shirt1Tex",
    SHIRT2_TEX = "shirt2Tex",

    BLUE_PLASTIC = "bluePlastic",
    BLUE_PLASTIC_SPEC = "bluePlasticSpec",

    BLACK = "black",
    BLACK1 = "black1",

    SHOE1_TEX = "shoe1Tex",
    SHOE2_TEX = "shoe2Tex",
    SHOE3_TEX = "shoe3Tex",

    SPORTY = "sporty",
    SPORTY_SPEC = "sportySpec",

    PINK = "pink",
    PINK_SPEC = "pinkSpec",
    DRESS1_TEX = "dress1Tex",
    DRESS2_TEX = "dress2Tex",
    DRESS3_TEX = "dress3Tex",
    DRESS4_TEX = "dress4Tex",

    TRAV = "trav",
    TRAV_SPEC = "travSpec",

    RED_PLASTIC = "redPlastic",
    RED_PLASTIC_SPEC = "redPlasticSpec",

    RED_TILES = "redTiles",
    RED_TILES_SPEC = "redTilesSpec",

    RED_FABRIC1 = "redFabric1",
    RED_FABRIC1_SPEC = "redFabric1Spec",

    RED_FABRIC2 = "redFabric2",
    RED_FABRIC2_SPEC = "redFabric2Spec",
    
    SOFA1_DIFF = "sofa1Diff",
    SOFA2_DIFF = "sofa2Diff",

    BED_DIFF = "bedDiff",
    BED_SPEC = "bedSpec",

    BEIGE = "beige",
    BEIGE_SPEC = "beigeSpec",

    TABLE2_DIFF = "table2Diff",
    TABLE2_SPEC = "table2Spec",
    
    TABLE3_DIFF = "table3Diff",
    TABLE3_SPEC = "table3Spec",


    
    

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

    //SHIRT_SHOP:
    SHIRT_SHOP = "shirtShop",
    SHIRT1_OBJ = "shirt1",
    SHIRT2_OBJ = "shirt2",
    CLOTHS_PLACE_2 = "clothsPlace2",
    CIRCLE_LIGHT_2 = "circleLight2",
    CASHIER2 = "cashier2",
    SCREEN2 = "screen2", 
    MIRROR2 = "mirror2",
    SHOP_BLOOR2 = "shopBloor2",
    SHIRT_REF = "shirtRef",

    //SHOES_SHOP:
    SHOES_SHOP = "shoseShop",    
    CASHIER3 = "cashier3",
    SHOP_BLOOR3 = "shopBloor3",
    SMALL_ROOF = "smallRoof",
    SHOE1 = "shoe1",
    SHOE2 = "shoe2",
    SHOE3 = "shoe3",
    SQUARE_LIGHT = "squareLight",

    //Dress_SHOP:
    DRESS_SHOP = "dressShop",
    CASHIER4 = "cashier4",
    SHOP_BLOOR4 = "shopBloor4",
    DRESS1 = "dress1",
    DRESS2 = "dress2",
    DRESS3 = "dress3",
    DRESS4 = "dress4",
    CIRCLE_LIGHT_4 = "circleLight4",
    MIRROR4 = "mirror4",
    CLOTHS_PLACE_4 = "clothsPlace4",
    SIMPLE_WALL = "simpleWall",
    DRESS_REF = "dressRef",
    DRESSING_ROOM = "dressingRoom",

    //Restaurant:
    REST_GROUND = "restGround",
    TABLE = "table",
    CHAIR = "chair",
    CASHIER5 = "cashire5",
    REST_ROOF = "restRoof",
    TRIA = "tria",
    CYL_LIGHT = "triLight",
    REST_WALL = "restWall",
    CHAIR_BASE = "chairBase",

    //FURN_STORE:
    FURN_STORE = "furnStore",
    CASHIER6 = "cashier6",
    SHOP_BLOOR6 = "shopBloor6",
    CIRCLE_LIGHT6 = "circleLight6",

    BED = "bed",
    SOFA1 = "sofa1",
    SOFA2 = "sofa2",
    TABLE2 = "table2",
    TABLE3 = "table3",
 
    STREND = "strend";
};

#endif