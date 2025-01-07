#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "App.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "color.hpp"
#include "Sphere.h"
#include "Icosphere.h"
#include "Cubesphere.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Torus.h"

#include "Model.h"


using namespace std;

class Scene : public App
{
public:
    unordered_map<string, VAO> vaos;
    unordered_map<string, EBO> ebos;
    unordered_map<string, Sphere> spheres;
    unordered_map<string, Icosphere> icos;
    unordered_map<string, Cubesphere> cubes;
    unordered_map<string, Cylinder> cylinders;
    unordered_map<string, Cone> cones;
    unordered_map<string, Torus> toruses;

    unordered_map<string, vector<glm::mat4>> models;

    unordered_map<string, Model> threeDModels;

    
    Scene();

    void cubeBuffers(string name);
    void squareBuffers(string name);
    void torusBuffers(string name);
    void cylinderBuffers(string name);
    void coneBuffers(string name);
    void threeDmodelBuffers(string name);
    
};

#endif
