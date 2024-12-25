#include "Light.h"

Light::Light(){}

Light::Light(Shader shader, bool enableDir, int numOfPoints, bool enableSpot)
{
    this->myShader = shader;
    this->enableDir = enableDir;
    this->numOfPoints = numOfPoints;
    this->enableSpot = enableSpot;
    //DirLight:
    dirLightColor = glm::vec3(1.0f, 0.95f, 0.9f);
    dirLightDirection = glm::vec3(-470.0f, -1205.6f, 12181.2f);
    dirLightSpecular = glm::vec3(0.7f, 0.7f, 0.7f);
    //PointLight:
    for(int i=0; i<numOfPoints; i++){
        pointLightColor[i]= glm::vec3(1.0f);
        pointLightSpecular[i]=glm::vec3(1.0f);
        pointLightConstant[i] =1.0f;
        pointLightLinear[i]=0.0014f;
        pointLightQuadratic[i] = 0.000007f;
        pointLightPosition[i] = glm::vec3( 0.7f,  0.2f,  2.0f); 
        
    }
    //SpotLight:
    this->spotLightColor = glm::vec3(1.0f);
    
    spotLightSpecular = glm::vec3(1.0f);
    spotLightConstant = 1.0f;
    spotLightLinear = 0.09f;
    spotLightQuadratic = 0.032f;
    spotLightCutOff = 12.5f;
    spotLightOuterCutOff = 17.5f;
    
    myShader.use();
    //Dir light
    myShader.setBool("enableDir", enableDir);
    if(enableDir) turnOnDir();
    // point light 
    myShader.setInt("numOfPoints", numOfPoints);
    turnOnPoint();
    // spotLight
    myShader.setBool("enableSpot", enableSpot);
    if(enableSpot) turnOnSpot();
    
}
void Light::update(glm::vec3 cameraPos, glm::vec3 cameraFront)
{
    spotLightPosition = cameraPos;
    spotLightDirection = cameraFront;
    //viewPos:
    viewPos = cameraPos;
    myShader.setVec3("viewPos", viewPos);

}
void Light::turnOnDir()
{
    myShader.use();
    this->dirLightDiffuse = this->dirLightColor * glm::vec3(0.8f);
    this->dirLightAmbient = this->dirLightColor * glm::vec3(0.8f);
    myShader.setVec3("dirLight.direction", dirLightDirection);
    myShader.setVec3("dirLight.specular", dirLightSpecular);
    myShader.setVec3("dirLight.ambient", dirLightAmbient);
    myShader.setVec3("dirLight.diffuse", dirLightDiffuse);
    
}
void Light::turnOnPoint()
{
    myShader.use();
    for(int i=0; i<numOfPoints; i++){
        this->pointLightDiffuse[i] = this->pointLightColor[i] * glm::vec3(0.8f);
        this->pointLightAmbient[i] = this->pointLightDiffuse[i] * glm::vec3(0.2f);
    }
    for(char x = '0'; x-'0'<numOfPoints; x++){
        std::string ch; ch += x;
        myShader.setVec3("pointLights["+ch+"].position", pointLightPosition[x-'0']);
        myShader.setVec3("pointLights["+ch+"].ambient", pointLightAmbient[x-'0']);
        myShader.setVec3("pointLights["+ch+"].diffuse", pointLightDiffuse[x-'0']);
        myShader.setVec3("pointLights["+ch+"].specular", pointLightSpecular[x-'0']);
        myShader.setFloat("pointLights["+ch+"].constant", pointLightConstant[x-'0']);
        myShader.setFloat("pointLights["+ch+"].linear", pointLightLinear[x-'0']);
        myShader.setFloat("pointLights["+ch+"].quadratic", pointLightQuadratic[x-'0']);
    }
}
void Light::turnOnSpot()
{
    myShader.use();
    this->spotLightDiffuse = this->spotLightColor * glm::vec3(0.8f);
    this->spotLightAmbient = this->spotLightDiffuse * glm::vec3(0.2f);
    myShader.setVec3("spotLight.position", spotLightPosition);
    myShader.setVec3("spotLight.direction", spotLightDirection);
    myShader.setVec3("spotLight.ambient", spotLightAmbient);
    myShader.setVec3("spotLight.diffuse", spotLightDiffuse);
    myShader.setVec3("spotLight.specular", spotLightSpecular);
    myShader.setFloat("spotLight.constant", spotLightConstant);
    myShader.setFloat("spotLight.linear", spotLightLinear);
    myShader.setFloat("spotLight.quadratic", spotLightQuadratic);
    myShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(spotLightCutOff)));
    myShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(spotLightOuterCutOff)));
}
