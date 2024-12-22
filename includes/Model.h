#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <mesh.h>
#include <shader.h>

#include <string>
#include <map>
#include <vector>

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model 
{
public:
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

    Model();
    Model(const std::string &path, bool gamma = false);
    void Draw(Shader &shader);

private:
    void loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif
