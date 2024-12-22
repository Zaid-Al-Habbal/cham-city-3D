#include "Skybox.h"
#include <stb_image.h>
#include <iostream>

// Skybox vertices
static const float skyboxVertices[] =  {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

static const std::vector<std::string> morningFaces = {
        "../resources/objects/skybox/morning2/right.jpg",
        "../resources/objects/skybox/morning2/left.jpg",
        "../resources/objects/skybox/morning2/top.jpg",
        "../resources/objects/skybox/morning2/bottom.jpg",
        "../resources/objects/skybox/morning2/front.jpg",
        "../resources/objects/skybox/morning2/back.jpg"
};

static const std::vector<std::string> eveningFaces = {
        "../resources/objects/skybox/night/right.jpg",
        "../resources/objects/skybox/night/left.jpg",
        "../resources/objects/skybox/night/top.jpg",
        "../resources/objects/skybox/night/bottom.jpg",
        "../resources/objects/skybox/night/front.jpg",
        "../resources/objects/skybox/night/back.jpg"
};

Skybox::Skybox() {
    // Load textures
    stbi_set_flip_vertically_on_load(false);
    cubemapTextureMorning = loadCubemap(morningFaces);
    cubemapTextureEvening = loadCubemap(eveningFaces);
    currentTexture = cubemapTextureMorning;

    // Setup VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}


Skybox::~Skybox() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &cubemapTextureMorning);
    glDeleteTextures(1, &cubemapTextureEvening);
}

unsigned int Skybox::loadCubemap(const std::vector<std::string>& faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void Skybox::draw(Shader shader, const glm::mat4& view, const glm::mat4& projection) {
    glDepthFunc(GL_LEQUAL);
    shader.use();
    shader.setInt("skybox", 0);
    shader.setMat4("view", glm::mat4(glm::mat3(view))); // Remove translation from view matrix
    shader.setMat4("projection", projection);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, currentTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthFunc(GL_LESS);
}

void Skybox::setEnvironment(bool isMorning) {
    currentTexture = isMorning ? cubemapTextureMorning : cubemapTextureEvening;
}
