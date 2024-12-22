#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 aInstanceModel;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 view;
uniform mat4 projection;

uniform float textureCnt;

void main(){
    gl_Position = projection * view * aInstanceModel * vec4(aPos, 1.0);
    Normal = mat3(transpose(inverse(aInstanceModel))) * aNormal; 
    FragPos = vec3(aInstanceModel * vec4(aPos, 1.0));
    TexCoords = aTexCoords*textureCnt;
}