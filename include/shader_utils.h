#pragma once
#ifndef SHADER_UTILS_H
#define SHADER_UTILS_H

#include <GL/glew.h>

// ������ɫ������
unsigned int loadShader(const char* vertexPath, const char* fragmentPath);

// ������ɫ���еľ�����ͶӰ����ͼ��ģ�;���ȣ�
void setUniformMat4(unsigned int shaderProgram, const char* name, const float* value);

// ʹ����ɫ��
void useShader(unsigned int shaderProgram);

#endif // SHADER_UTILS_H
