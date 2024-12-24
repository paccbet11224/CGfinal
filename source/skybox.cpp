#include "skybox.h"
#include "shader_utils.h"
#include <stb_image.h>
#include <iostream>
unsigned int VAO, VBO;
// ��պе������嶥��
float skyboxVertices[] = {
    // ��������� (Back Face)
    -10.0f,  10.0f, -10.0f,  // ���Ͻ�
    -10.0f, -10.0f, -10.0f,  // ���½�
     10.0f, -10.0f, -10.0f,  // ���½�
     10.0f, -10.0f, -10.0f,  // ���½�
     10.0f,  10.0f, -10.0f,  // ���Ͻ�
    -10.0f,  10.0f, -10.0f,  // ���Ͻ�

    // ������ǰ�� (Front Face)
    -10.0f, -10.0f,  10.0f,  // ���½�
    -10.0f,  10.0f,  10.0f,  // ���Ͻ�
     10.0f,  10.0f,  10.0f,  // ���Ͻ�
     10.0f,  10.0f,  10.0f,  // ���Ͻ�
     10.0f, -10.0f,  10.0f,  // ���½�
    -10.0f, -10.0f,  10.0f,  // ���½�

    // ���������� (Left Face)
    -10.0f,  10.0f,  10.0f,  // ���Ͻ�
    -10.0f,  10.0f, -10.0f,  // ���Ͻǣ���
    -10.0f, -10.0f, -10.0f,  // ���½ǣ���
    -10.0f, -10.0f, -10.0f,  // ���½ǣ���
    -10.0f, -10.0f,  10.0f,  // ���½�
    -10.0f,  10.0f,  10.0f,  // ���Ͻ�

    // ���������� (Right Face)
     10.0f,  10.0f,  10.0f,  // ���Ͻ�
     10.0f, -10.0f, -10.0f,  // ���½ǣ���
     10.0f,  10.0f, -10.0f,  // ���Ͻǣ���
     10.0f, -10.0f, -10.0f,  // ���½ǣ���
     10.0f,  10.0f,  10.0f,  // ���Ͻ�
     10.0f, -10.0f,  10.0f,  // ���½�

     // ��������� (Bottom Face)
     -10.0f, -10.0f, -10.0f,  // ���½�
      10.0f, -10.0f, -10.0f,  // ���½�
      10.0f, -10.0f,  10.0f,  // ���½ǣ�ǰ��
      10.0f, -10.0f,  10.0f,  // ���½ǣ�ǰ��
     -10.0f, -10.0f,  10.0f,  // ���½ǣ�ǰ��
     -10.0f, -10.0f, -10.0f,  // ���½�

     // �����嶥�� (Top Face)
     -10.0f,  10.0f, -10.0f,  // ���Ͻǣ���
      10.0f,  10.0f, -10.0f,  // ���Ͻǣ���
      10.0f,  10.0f,  10.0f,  // ���Ͻǣ�ǰ��
      10.0f,  10.0f,  10.0f,  // ���Ͻǣ�ǰ��
     -10.0f,  10.0f,  10.0f,  // ���Ͻǣ�ǰ��
     -10.0f,  10.0f, -10.0f   // ���Ͻǣ���
};

Skybox::Skybox(const std::vector<std::string>& faces) {
    setupSkybox();
    cubemapTexture = loadCubemap(faces);
    shaderProgram = loadShader("Shaders/skybox.vert", "Shaders/skybox.frag");
}

Skybox::~Skybox() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &cubemapTexture);
}

void Skybox::setupSkybox() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
}

unsigned int Skybox::loadCubemap(const std::vector<std::string>& faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        // ����ͼ��
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            // ����ͼ��ͨ����ѡ����ʵĸ�ʽ
            GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

            // ��ӡ������Ϣ
            std::cout << "Loaded texture: " << faces[i]
                << " | Width: " << width << ", Height: " << height
                << ", Channels: " << nrChannels << std::endl;

            // ��������������ͼ����ȷ��
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, format, width, height,
                0, format, GL_UNSIGNED_BYTE, data);

            stbi_image_free(data); // �ͷ�ͼ������
        }
        else {
            std::cerr << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            std::cerr << "STB Error: " << stbi_failure_reason() << std::endl;
            stbi_image_free(data);
            return 0; // ����ʧ��ʱ���� 0������ʹ�ò�����������
        }
    }

    // ������������ͼ���������
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // ��� OpenGL ����
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error during cubemap setup: " << error << std::endl;
    }

    return textureID;
}
void Skybox::render(const glm::mat4& view, const glm::mat4& projection) {
    glDepthFunc(GL_LEQUAL);
    glUseProgram(shaderProgram);

    glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &viewNoTranslation[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);

    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glDepthFunc(GL_LESS);
}
