#ifndef SHADER_H
#define SHADER_H
#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

//using namespace std;

#define INVALID_UNIFORM_LOCATION -1

class Shader {
public:
    // ��ɫ������ ID
    GLuint ID;

    // ��������������ɫ��
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath);
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath,
        const GLchar* varyings[], int count);
    // ʹ����ɫ��
    void use();
    // ����ͳһ������Uniforms��
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
    // ���ز�������ɫ��
    std::string loadShaderSource(const std::string& path);
    void compileShader(const char* source, GLuint shaderID);
};

#endif
#pragma once
