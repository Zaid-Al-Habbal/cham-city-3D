#include"VAO.h"

#include <glm/glm.hpp>

// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO Attribute such as a position or color to the VAO
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
}

// Binds the VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::init(VBO& vbo, VBO& instanceVBO)
{
	this->Bind();
	vbo.Bind();
	this->LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    this->LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float)));
    this->LinkAttrib(vbo, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(6*sizeof(float)));
	vbo.Unbind();
	//Instance VBO:
	instanceVBO.Bind();
	std::size_t vec4Size = sizeof(glm::vec4);
	this->LinkAttrib(instanceVBO, 3, 4, GL_FLOAT, 4 * vec4Size, (void*)0);
	this->LinkAttrib(instanceVBO, 4, 4, GL_FLOAT, 4 * vec4Size, (void*)(1 * vec4Size));
	this->LinkAttrib(instanceVBO, 5, 4, GL_FLOAT, 4 * vec4Size, (void*)(2 * vec4Size));
	this->LinkAttrib(instanceVBO, 6, 4, GL_FLOAT, 4 * vec4Size, (void*)(3 * vec4Size));
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	vbo.Unbind();
	this->Unbind();
}
// Deletes the VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}