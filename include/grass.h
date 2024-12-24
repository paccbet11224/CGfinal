#ifndef GRASS_H
#define GRASS_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Grass {
public:
    Grass(const std::string& texturePath);
    ~Grass();

    void setAmplitude(float amp);    // ���õ��θ߶����
    void setFrequency(float freq);   // ���õ������Ƶ��
    void setThickness(float thick);  // ���õ��εĺ��

    void render(const glm::mat4& view, const glm::mat4& projection);

private:
    unsigned int VAO, VBO, EBO;
    unsigned int textureID;
    unsigned int shaderProgram;

    float amplitude;  // ���θ߶����
    float frequency;  // �������Ƶ��
    float thickness;  // ���κ��

    void setupPlane();
    void loadTexture(const std::string& texturePath);
};

#endif // GRASS_H
