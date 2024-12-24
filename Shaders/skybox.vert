#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main() {
    TexCoords = aPos; // ��������Ķ���λ�ô��ݸ�Ƭ����ɫ��
    gl_Position = projection * view * vec4(aPos, 1.0); // ������ת�����ü��ռ�
}
