#ifndef Light_CLASS_H
#define Light_CLASS_H

#include<glad/glad.h>
#include<iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"shader.h"
#include"TextureManager.h"
#include "camera.h"

#include <vector>



class Light
{
public:
    // directional light:
    glm::vec3 dirLightColor, dirLightDirection, dirLightAmbient, dirLightDiffuse, dirLightSpecular;
    // Point light:
    glm::vec3 pointLightColor[8], pointLightAmbient[8], pointLightDiffuse[8], pointLightSpecular[8], pointLightPosition[8];
    float pointLightConstant[8], pointLightLinear[8], pointLightQuadratic[8];
    // Spot light:
    glm::vec3 spotLightColor, spotLightPosition, spotLightDirection, spotLightAmbient, spotLightDiffuse, spotLightSpecular;
    float spotLightConstant, spotLightLinear, spotLightQuadratic, spotLightCutOff,spotLightOuterCutOff;
    
    //for turning Lights on and off
    bool enableDir, enableSpot;
    int numOfPoints;
    //shader
    Shader myShader;
    //comera position:
    glm::vec3 viewPos;
    //Material:
    
    Light(Shader shader, bool enableDir, int numOfPoints, bool enableSpot);
    Light();

    void turnOnDir();
    void turnOnPoint();
    void turnOnSpot();
    void update(glm::vec3 cameraPos, glm::vec3 cameraFront);
	
};
#endif