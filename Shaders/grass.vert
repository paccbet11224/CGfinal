#version 330 core
layout(location = 0) in vec3 aPos;       // ����λ��
layout(location = 1) in vec2 aTexCoords; // ��������

out vec2 TexCoords; // ���ݸ�Ƭ����ɫ������������

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// ���Ƶ��θ߶ȵ������Ƶ��
uniform float amplitude; // �߶����
uniform float frequency; // Ƶ�ʲ���

// ƽ����������ֵ�������
float smoothRandom(vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // �ĸ��ǵ����ֵ
    float a = fract(sin(dot(i + vec2(0.0, 0.0), vec2(12.9898, 78.233))) * 43758.5453);
    float b = fract(sin(dot(i + vec2(1.0, 0.0), vec2(12.9898, 78.233))) * 43758.5453);
    float c = fract(sin(dot(i + vec2(0.0, 1.0), vec2(12.9898, 78.233))) * 43758.5453);
    float d = fract(sin(dot(i + vec2(1.0, 1.0), vec2(12.9898, 78.233))) * 43758.5453);

    // ƽ����ֵ
    vec2 u = f * f * (3.0 - 2.0 * f);
    return mix(mix(a, b, u.x), mix(c, d, u.x), u.y);
}

// ���ƽ��������fBM��
float fbm(vec2 st) {
    float total = 0.0;
    float persistence = 0.5; // ÿ������˥������
    float freq = frequency;
    float amp = 1.0;

    for (int i = 0; i < 4; ++i) { // ���� 4 ��ƽ������
        total += smoothRandom(st * freq) * amp;
        freq *= 2.0;    // Ƶ�ʱ���
        amp *= persistence; // ���˥��
    }
    return total;
}

void main() {
    // ������������߶�
    float height = amplitude * fbm(aPos.xz);

    // ���һ����΢���Ŷ�
    height += amplitude * 0.1 * smoothRandom(aPos.xz * 10.0);

    // ����ǵ������棬����ԭʼ�߶�
    float newY = (aPos.y < 0.0) ? aPos.y : height;

    // �������λ��
    vec3 newPos = vec3(aPos.x, newY, aPos.z);

    // ������������
    TexCoords = aTexCoords;

    // Ӧ�� MVP �任
    gl_Position = projection * view * model * vec4(newPos, 1.0);
}
