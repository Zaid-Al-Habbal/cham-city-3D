#include "App/Renderer.h"
#include "Light.h"

using namespace glm;

Renderer::Renderer()
{
    ResourceManager resourceManager;
    //texture:
    textures = resourceManager.textures;
    //shaders:
    shaders = resourceManager.shaders;

    //MAIN SHADER Light
    mainLight = Light(shaders[MAIN], true, 0, false);
    //REF SHADER Light:
    refLight = Light(shaders[REF], true, 0, false);

}


void Renderer::render(Controller& controller)
{
    Camera camera = controller.getCamera();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
    
    // camera.printPos();

    //Config MAIN shader:
    shaders[REF].use();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
     (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 20000.0f);
    glm::mat4 view = camera.GetViewMatrix();

    //for reflection:
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.currentTexture);

    shaders[REF].setInt("environmentMap", 2);
    shaders[REF].setMat4("projection", projection);
    shaders[REF].setMat4("view", view);
    shaders[REF].setFloat("shininess", 32.0f);
    shaders[REF].setFloat("alpha", 1.0f);
    shaders[REF].setFloat("refVal", 0.0f);
    
    //config refLight:
    refLight.update(camera.Position, camera.Front);

    //---------------------------------------------------------------------------------------
    //OUTSIDE THE MALL:

    //refLight
    refLight.turnOnDir();
    // refLight.turnOnPoint();
    // refLight.turnOnSpot();

    //ROOF BUILDING:
    TextureManager::enable(shaders[REF], textures[GRAY_BRICK], textures[GRAY_BRICK_SPEC], 40);
    draw(ROOF_BUILDING, toruses[ROOF_BUILDING].getIndexCount(), 0);

    //SPECIAL_BUILDINGs:
    draw(SPECIAL_BUILDING, cubes[SPECIAL_BUILDING].getIndexCount(), 0);

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
    TextureManager::enable(shaders[REF], textures[GRAY_TILES], textures[GRAY_TILES_SPEC], 16);
    shaders[REF].setFloat("refVal", 0.07f);
    draw(SIDE_WALK, cubes[SIDE_WALK].getIndexCount(), 0);


    //---------------------------------------------------------------------------------------
    // SKYBOX:
    skybox.setEnvironment(!controller.isNight);
    skybox.draw(shaders[SKYBOX], view, projection);
    
    //************************************************************************************ */
    // ALPHA objects:

    shaders[REF].use();
    shaders[REF].setFloat("refVal", 0.8f);
    //CYL_BUILDING  #ALPHA:
    shaders[REF].setFloat("alpha", 0.75f);
    TextureManager::enable(shaders[REF], textures[BLUE_WINDOW], textures[BLUE_WINDOW_SPEC], 16);
    draw(CYL_BUILDING, cylinders[CYL_BUILDING].getIndexCount(), 30);

    //GLASS_ROOF #ALPHA:
    shaders[REF].setFloat("shininess", 128.0f);
    TextureManager::enable(shaders[REF], textures[WHITE_WINDOW], textures[WHITE_WINDOW_SPEC], 8);
    draw(GLASS_ROOF, cubes[GLASS_ROOF].getIndexCount(), 0);
    shaders[REF].setFloat("shininess", 32.0f);

    //ENTRY_BLOOR: $ALPHA:
    shaders[REF].setFloat("refVal", 0.5f);
    shaders[REF].setFloat("alpha", 0.1f);
    TextureManager::enable(shaders[REF], textures[BLOOR], textures[BLOOR_SPEC], 1);
    draw(ENTRY_BLOOR, cubes[ENTRY_BLOOR].getIndexCount(), 0);


    
}












void Renderer::draw(string objectName, int numOfVertices, int offset)
{
    vaos[objectName].Bind(); ebos[objectName].Bind();
    glDrawElementsInstanced(GL_TRIANGLES, numOfVertices, GL_UNSIGNED_INT, (void*)(offset*sizeof(float)), models[objectName].size());  

}


void Renderer::draw3Dmodel(string name)
{
    shaders[MAIN].setFloat("textureCnt", 1.0f);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, threeDModels[name].textures_loaded[0].id); // note: we also made the textures_loaded vector public (instead of private) from the model class.
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, threeDModels[name].textures_loaded[1].id); // note: we also made the textures_loaded vector public (instead of private) from the model class.
    for (unsigned int i = 0; i < threeDModels[name].meshes.size(); i++)
    {
        glBindVertexArray(threeDModels[name].meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(threeDModels[name].meshes[i].indices.size()), GL_UNSIGNED_INT, 0, models[name].size());
        glBindVertexArray(0);
    }
}

