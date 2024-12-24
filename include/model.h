#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;  // ����λ��
    glm::vec2 TexCoords; // ��������
};

struct Material {
    GLuint textureID;    // ����ID
};

class Model {
public:
    Model(const std::string& objPath, const std::string& mtlPath);
    void Render();

private:
    std::vector<Vertex> vertices_bark;   // ���ɶ�������
    std::vector<Vertex> vertices_leaves; // ��Ҷ��������
    std::vector<Vertex> vertices_stone;

    GLuint VAO_bark, VBO_bark;           // ���� VAO �� VBO
    GLuint VAO_leaves, VBO_leaves;       // ��Ҷ VAO �� VBO
    GLuint VAO_stone, VBO_stone;

    Material barkMaterial;
    Material leafMaterial;
    Material stoneMaterial;

    void loadModelone(const std::string& objPath, const std::string& mtlPath);
    void loadModeltwo(const std::string& objPath, const std::string& mtlPath);
    GLuint loadTexture(const std::string& texturePath);
    void setupMesh();
};

#endif
