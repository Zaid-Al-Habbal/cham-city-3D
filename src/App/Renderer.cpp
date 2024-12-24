#include "App/Renderer.h"
#include "Light.h"

Renderer::Renderer()
{
    ResourceManager resourceManager;
    //texture:
    textures = resourceManager.textures;
    //shaders:
    shaders = resourceManager.shaders;
    //light
    light = Light(shaders[MAIN], true, 0, false);

}


void Renderer::render(Controller& controller)
{
    Camera camera = controller.getCamera();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
    
    camera.printPos();

    //Config MAIN shader:
    shaders[MAIN].use();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
     (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
    glm::mat4 view = camera.GetViewMatrix();
    shaders[MAIN].setMat4("projection", projection);
    shaders[MAIN].setMat4("view", view);
    shaders[MAIN].setFloat("shininess", 32.0f);
    shaders[MAIN].setFloat("alpha", 1.0f);
    

    //config Light:
    light.update(camera.Position, camera.Front);

    //Light for outside world
    light.turnOnDir();
    // light.turnOnPoint();
    // light.turnOnSpot();


    //STREET_LAND:
    TextureManager::enable(shaders[MAIN], textures[ASPHALT], textures[ASPHALT_SPEC], 100.0f);
    draw(STREET_LAND, toruses[STREET_LAND].getIndexCount());

    
    
    // draw skybox as last
    skybox.setEnvironment(!controller.isNight);
    skybox.draw(shaders[SKYBOX], view, projection);

    
}












void Renderer::draw(string objectName, int numOfVertices)
{
    vaos[objectName].Bind(); ebos[objectName].Bind();
    glDrawElementsInstanced(GL_TRIANGLES, numOfVertices, GL_UNSIGNED_INT, (void*)0, models[objectName].size());  

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

