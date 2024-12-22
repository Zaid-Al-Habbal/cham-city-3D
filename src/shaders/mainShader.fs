#version 330 core

// Inputs from Vertex Shader
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

// Outputs
out vec4 FragColor;

// Uniforms
uniform vec3 viewPos;

// Material Properties
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform float shininess;
uniform float alpha; // Alpha value to control transparency

// Directional Light
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;
uniform bool enableDir;

// Point Light
struct PointLight {
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINT_LIGHTS 6
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform int numOfPoints;

// Spotlight
struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform SpotLight spotLight;
uniform bool enableSpot;

// Function Prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseTex, vec3 specularTex);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseTex, vec3 specularTex);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseTex, vec3 specularTex);

void main()
{
    // Normalize inputs
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Fetch textures once
    vec3 diffuseTex = vec3(texture(texture_diffuse1, TexCoords));
    vec3 specularTex = vec3(texture(texture_specular1, TexCoords));

    //Transparency value:
    float alphaValue = (texture(texture_diffuse1, TexCoords).a + texture(texture_specular1, TexCoords).a) * alpha;

    //Dynamic Alpha based on Distance:
    // float maxDistance = 1000.0f;
    // float distance = length(viewPos - FragPos);
    // float dynAlpha = clamp(1.0 - distance / maxDistance, 0.0, 1.0);

    // //apply changes:
    // alphaValue*=dynAlpha;

    // Skip processing if alpha is low (transparency)
    if (alphaValue < 0.1f) discard;

    // Initialize result color
    vec3 result = vec3(0.0);

    // Directional light
    if (enableDir) result += CalcDirLight(dirLight, norm, viewDir, diffuseTex, specularTex);

    // Point lights
    for (int i = 0; i < numOfPoints; i++) 
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir, diffuseTex, specularTex);

    // Spotlight
    if (enableSpot) result += CalcSpotLight(spotLight, norm, FragPos, viewDir, diffuseTex, specularTex);

    // Output the final color
    FragColor = vec4(result, alphaValue);
}

// Calculate directional light
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseTex, vec3 specularTex)
{
    vec3 lightDir = normalize(-light.direction);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // Combine results
    vec3 ambient = light.ambient * diffuseTex;
    vec3 diffuse = light.diffuse * diff * diffuseTex;
    vec3 specular = light.specular * spec * specularTex;

    return ambient + diffuse + specular;
}

// Calculate point light
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseTex, vec3 specularTex)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Combine results
    vec3 ambient = light.ambient * diffuseTex;
    vec3 diffuse = light.diffuse * diff * diffuseTex;
    vec3 specular = light.specular * spec * specularTex;

    // Apply attenuation
    return (ambient + diffuse + specular) * attenuation;
}

// Calculate spotlight
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseTex, vec3 specularTex)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // Combine results
    vec3 ambient = light.ambient * diffuseTex;
    vec3 diffuse = light.diffuse * diff * diffuseTex;
    vec3 specular = light.specular * spec * specularTex;

    // Apply attenuation and spotlight intensity
    return (ambient + diffuse + specular) * attenuation * intensity;
}
