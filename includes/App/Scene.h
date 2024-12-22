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
    map<string, VAO> vaos;
    map<string, EBO> ebos;
    map<string, Sphere> spheres;
    map<string, Icosphere> icos;
    map<string, Cubesphere> cubes;
    map<string, Cylinder> cylinders;
    map<string, Cone> cones;
    map<string, Torus> toruses;

    map<string, vector<glm::mat4>> models;

    map<string, Model> threeDModels;


    
    Scene();

    void cubeBuffers(string name);
    void threeDmodelBuffers(string name);
    
};

#endif
