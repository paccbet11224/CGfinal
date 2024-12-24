#ifndef ROCK_H
#define ROCK_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include "model.h"  // ���� Model ��һ����װ��ģ�ͼ��غ���Ⱦ����

class Rock {
public:
    // ���캯�������� OBJ ·���Ͳ���·��
    Rock(const std::string& objPath, const std::string& mtlPath);

    // ��Ⱦ������������ͼ����ͶӰ�����ģ�;���
    void render(const glm::mat4& view, const glm::mat4& projection, const glm::mat4& modelMatrix);

private:
    // ���ڼ��غ���Ⱦģ�͵� Model ��ʵ��
    Model* model;

    // ��ɫ������� ID
    GLuint shaderProgram;

    // ���ڴ洢������Ϣ����ɫ����ɫ�������� uniform λ��
    GLuint lightColorLocation;  // ��Դ��ɫ��λ��
    GLuint objectColorLocation; // ������ɫ��λ��

    // ������ɫ���ķ���
    void loadShaders();
};

#endif // ROCK_H
