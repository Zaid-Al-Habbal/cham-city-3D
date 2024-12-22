#include"TextureManager.h"

TextureManager::TextureManager(){}

TextureManager::TextureManager(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	// Assigns the type of the texture ot the texture object
        type = texType;
        texSlot = slot;

        // Stores the width, height, and the number of color channels of the image
        int widthImg, heightImg, numColCh;
        // Flips the image so it appears right side up

        // Reads the image from a file and stores it in bytes
        unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

        // Generates an OpenGL texture object
        glGenTextures(1, &ID);
        // Assigns the texture to a TextureManager Unit
        glActiveTexture(slot);
        glBindTexture(texType, ID);

        // Configures the way the texture repeats (if it does at all)
        glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Configures the type of algorithm that is used to make the image smaller or bigger
        glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


        // Extra lines in case you choose to use GL_CLAMP_TO_BORDER
        // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
        // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

        // Assigns the image to the OpenGL Texture object
        if(bytes){
            glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
            // Generates MipMaps
            glGenerateMipmap(texType);
        }
        else std::cout << "Failed to load texture " << image << std::endl;

        // Deletes the image data as it is already in the OpenGL Texture object
        stbi_image_free(bytes);

        // Unbinds the OpenGL Texture object so that it can't accidentally be modified
        glBindTexture(texType, 0);
}
void TextureManager::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.use();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void TextureManager::Bind()
{
	glActiveTexture(texSlot);
    glBindTexture(type, ID);
}

void TextureManager::Unbind()
{
	glBindTexture(type, 0);
}

void TextureManager::Delete()
{
	glDeleteTextures(1, &ID);
}

void TextureManager::enable(Shader mainShader, TextureManager diffuseTex, TextureManager specularTex, float textureCnt)
{
    diffuseTex.Bind();
    specularTex.Bind();
    diffuseTex.texUnit(mainShader, "texture.diffuse1", 0);
    specularTex.texUnit(mainShader, "texture.specular1", 1);
    mainShader.setFloat("textureCnt", textureCnt);

}