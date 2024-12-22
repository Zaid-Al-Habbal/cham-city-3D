#ifndef TextureManager_CLASS_H
#define TextureManager_CLASS_H

#include<glad/glad.h>
#include<stb_image.h>

#include"shader.h"

class TextureManager
{
public:
	GLuint ID;
	GLenum type;
    GLenum texSlot;
	TextureManager(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
	TextureManager();
	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();
	//enable material:
	static void enable(Shader mainShader, TextureManager diffuseTex, TextureManager specularTex, float textureCnt);
};
#endif