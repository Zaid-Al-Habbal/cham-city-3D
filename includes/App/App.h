#ifndef APP_H
#define APP_H

#include <iostream>

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
    SHOE4_TEX = "shoe4Tex",
    SHOE5_TEX = "shoe5Tex",
    SHOE5_TEX_SPEC = "shoe5TexSpec",
    SHOE6_TEX = "shoe6Tex",

 
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

    TABLE4_DIFF = "table4Diff",

    CABINET1_DIFF = "cabinet1Diff",

    COUCH2_DIFF = "couch2Diff",
    COUCH2_SPEC = "couch2Spec",

    SOFA_DIFF = "sofaDiff",
    SOFA_SPEC = "sofaSpec",

    TABLE5_DIFF = "table5Diff",
    TABLE5_SPEC = "table5Spec",

    GREEN_TILES = "greenTiles",
    GREEN_TILES_SPEC = "greenTilesSpec",

    WASHING1_DIFF = "washing1Diff",
    WASHING2_DIFF = "washing2Diff",

    FRIDGE1_DIFF = "fridge1Diff",
    FRIDGE2_DIFF = "fridge2Diff",
    
    GRAY_METAL = "grayMetal",
    GRAY_METAL_SPEC = "grayMetalSpec",

    STOVE_DIFF = "stoveDiff",

    OVEN_DIFF = "ovenDiff",
    
    MICRO_DIFF = "micreDiff",

    TV_DIFF = "tvDiff",

    SYRIA_DIFF = "syriaDiff",

    WHITE2_DIFF = "white2Diff",

    YELLOW = "yelow",
    YELLOW_SPEC = "yelowSpec",
    
    WOOD4 = "wood4",
    WOOD4_SPEC = "wood4SPec",

    SILVER = "silver",
    GOLD = "gold",
    GOLD2 = "gold2",
    GOLD3 = "gold3",
    GOLD4 = "gold4",
    
    SILVER2 = "silver2",
    SILVER3 = "silver3",

    PALM1_DIFF = "palm1Diff",

    PALM2_DIFF = "palm2Diff",

    PALM3_DIFF = "palm3Diff",

    PALM4_DIFF = "palm4Diff",

    MARBLE = "marble",

    SILVER4 = "silver4",
    BUTTOMS_TEX = "buttomsTex",

    GLASS = "glass",
    GLASS_SPEC = "glassSpec",

    SILVER5 = "silver5",
    ESCALATOR_TEX = "escalatorTex",

    CIRCLE_GLASS = "circleGlass",
    CIRCLE_GLASS_SPEC = "circleGlassSpec",

    ROAD_DIFF = "roadDiff",
    ROAD_SPEC = "roadSpec",

    ASPHALT_DIFF = "asphaltDiff",
    ASPHALT_SPEC = "asphaltSpec",

    PAVING_DIFF = "pavingDiff",
    PAVING_SPEC = "pavingSpec",

    STREET_LIGHT_TEX = "streetLightTex",
    MALL_LIGHT_TEX = "mallLightTex",
    
    BUILDING_TEX = "buildingTex",
    SMALL_TREE_TEX = "smallTreeTex",

    AD1_TEX = "ad1Tex",
    AD2_TEX = "ad2Tex",
    AD3_TEX = "ad3Tex",
    AD4_TEX = "ad4Tex",
    AD5_TEX = "ad5Tex",
    AD6_TEX = "ad6Tex",
    AD7_TEX = "ad7Tex",

    CAR1_TEX1 = "car1Tex1",
    CAR2_TEX = "car1Tex2",
    CAR2_SPEC = "car2Spec",
    CAR3_TEX = "car1Tex3",
    CAR3_SPEC = "car3Spec",
    
    LOGO_TEX = "logoTex",

    

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
    MALL_DOOR = "mallDoor",
    

    //Inside the Mall:
    GROUND = "ground",
    //SUITE_SHOP:
    SUITE_SHOP = "suiteShop",
    SUITE_GROUND = "suiteGround",
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
    SHIRT_GROUND = "shirtGround",
    SHIRT1_OBJ = "shirt1",
    SHIRT2_OBJ = "shirt2",
    CLOTHS_PLACE_2 = "clothsPlace2",
    CIRCLE_LIGHT_2 = "circleLight2",
    CASHIER2 = "cashier2",
    SCREEN2 = "screen2", 
    MIRROR2 = "mirror2",
    SHIRT_REF = "shirtRef",

    //SHOES_SHOP:
    SHOES_SHOP = "shoseShop", 
    SHOES_GROUND = "shoesGround",   
    CASHIER3 = "cashier3",
    SMALL_ROOF = "smallRoof",
    SHOE1 = "shoe1",
    SHOE2 = "shoe2",
    SHOE3 = "shoe3",
    SHOE4 = "shoe4",
    SHOE5 = "shoe5",
    SHOE6 = "shoe6",
    SQUARE_LIGHT = "squareLight",

    //Dress_SHOP:
    DRESS_SHOP = "dressShop",
    DRESS_GROUND = "dressGround",
    CASHIER4 = "cashier4",
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
    CIRCLE_LIGHT6 = "circleLight6",

    BED = "bed",
    SOFA = "sofa",
    SOFA1 = "sofa1",
    SOFA2 = "sofa2",
    TABLE2 = "table2",
    TABLE3 = "table3",
    TABLE4 = "table4",
    CABINET1 = "cabinet1",
    COUCH2 = "couch2",
    TABLE5 = "table5",
    FURN_GROUND = "furnGround",

    //TECH:
    TECH_STORE = "techStore",
    TECH_GROUND = "techGROUND",
    CASHIER7 = "cashier7",
    CIRCLE_LIGHT7 = "circleLight7",

    WASHING1 = "washing1",
    WASHING2 = "washing2",
    WASHING_BODY = "washingBody",

    JUST_WHITE = "justWhite",
    JUST_WHITE_SPEC = "justWhiteSpec",

    FRIDGE_BODY = "fridgeBody",
    FRIDGE1 = "fridge1",
    FRIDGE2 = "fridge2",

    STOVE = "stove",

    OVEN = "oven",
    MICRO = "micro",
    TV = "tv",
    SYRIA = "syria",

    INSIDE_ROOF = "insideRoof",
    ROOF_WALL = "roofWall",
    COLUMN = "column",

    //JEWELRY STORE:
    JEWELRY_STORE = "jewelryStore",
    JEWELRY_GROUND = "jewelryGround",
    CIRCLE_LIGHT8 = "cirlceLight8",
    DISPLAY_BASE = "displayBase",
    DISPLAY_VIEW = "displayView",
    CASHIER8 = "cashier8",
    JEW1 = "jew1",
    JEW2 = "jew2",
    JEW3 = "jew3",
    JEW4 = "jew4",
    JEW5 = "jew5",
    JEW6 = "jew6",
    JEW7 = "jew7",
    JEW8 = "jew8",
    JEW9 = "jew9",
    JEW10 = "jew10",
    JEW11 = "jew11",
    JEW12 = "jew12",
    JEW13 = "jew13",
    STONE = "stone",
    STONE2 = "stone2",

    PALM = "palm",
    PALM_LEAVES = "palmLeaves",

    ELEVATOR_BAR = "elevatorBar",
    ELEVATOR_BLOOR = "elevatorBloor",
    ELEVATOR_BODY = "elevatorBody",
    ELEVATOR_INSIDE = "elevatorInside",
    BUTTOMS = "buttoms",
    ELEVATOR_ENTRY = "elevatorEntry",
    ELEVATOR_DOOR = "elevatorDoor",

    ESCALATOR = "escalator",
    ESCALATOR2 = "escalator2",
    ESC_BASE = "escBase",
    ESC_ARM = "escArm",

    ROAD = "road",
    OUTSIDE_GROUND = "outsideGround",
    PAVING = "paving",
    STREET_LIGHT = "streetLight",
    MALL_LIGHT = "mallLight",
    BUILDING = "building",
    SMALL_TREE = "smallTree",
    AD1 = "ad1",
    AD2 = "ad2",
    AD3 = "ad3",
    AD4 = "ad4",
    AD5 = "ad5",
    AD6 = "ad6",
    AD7 = "ad7",

    CAR1 = "car1",
    CAR2 = "car2",
    CAR3 = "car3",
    CAR4 = "car4",
    CAR5 = "car5",
    CAR6 = "car6",
    CAR7 = "car7",

    LOGO = "logo",



    PROJECT_OBJECTS_END = "ProjectEnd";
};

#endif