#version 330 core
out vec4 FragColor;

in vec2 TexCoords; // �Ӷ�����ɫ����������������

uniform sampler2D grassTexture; // �ݵ�����

void main() {
    // �������в�����ɫ
    FragColor = texture(grassTexture, TexCoords);
}
