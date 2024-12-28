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
    appModel = translate(curModel, vec3(8700.0f, 50.0f, 20.0f));
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
    appModel = translate(appModel, vec3(-4500.0, 3600.0, 2650.0));
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
    appModel = rotate(appModel, radians(-240.0f), Y);
    models[CYL_ADDITIONAL].PB(appModel);

    appModel = translate(appModel, vec3(0.0f, -3750.0f, 0.0f));
    models[CYL_ADDITIONAL].PB(appModel);

    cylinderBuffers(CYL_ADDITIONAL);

    //GLASS_ROOF:
    cubes[GLASS_ROOF] = Cubesphere(1000.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4530.0f, 3450.0f, 2600.0f));
    appModel = scale(appModel, vec3(8.1f, 0.1f, 5.45f));
    models[GLASS_ROOF].PB(appModel);
    cubeBuffers(GLASS_ROOF);

    //ENTRY:
    toruses[ENTRY] = Torus(1200*1.6f, 1200*0.5f, 4, 7, false, 3);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4550.0f, 100.0f, -2420.0f));
    appModel = rotate(appModel, radians(10.0f), X);
    appModel = scale(appModel, vec3(1.252f, 2.3f, 1.0f));
    appModel = rotate(appModel, radians(45.0f), Z);
    models[ENTRY].PB(appModel);
    torusBuffers(ENTRY);

    //ENTRY_BLOOR:
    cubes[ENTRY_BLOOR] = Cubesphere(1000.0f, 1, false);
    appModel = MODEL;
    appModel = translate(appModel, vec3(-4650.0f, 1150.0f, -2520.0f));
    appModel = rotate(appModel, radians(20.0f), X);
    appModel = scale(appModel, vec3(2.3f, 2.0f, 0.04f));
    models[ENTRY_BLOOR].PB(appModel);

    appModel = MODEL;
    appModel = translate(appModel, vec3(-3550.0f, -415.0f, -2830.0f));
    appModel = scale(appModel, vec3(0.40f, 1.0f, 0.04f));
    models[ENTRY_BLOOR].PB(appModel);
    appModel = translate(appModel, vec3(-5050.0f, 0.0f, 0.0f));
    models[ENTRY_BLOOR].PB(appModel);

    cubeBuffers(ENTRY_BLOOR);

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
    appModel = translate(appModel, vec3(-4800.0f, -965.0f, 2560.0f));
    appModel = scale(appModel, vec3(2.73f, 0.01f, 2.0f));
    models[GROUND].PB(appModel);
    cubeBuffers(GROUND); 


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