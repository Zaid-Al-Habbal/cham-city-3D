#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>
#include <vector>
#include <glm/glm.hpp>

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(const float* vertices, GLsizeiptr size);
	VBO(std::vector<glm::mat4> instanceModels, int vecSize);
	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};

#endif