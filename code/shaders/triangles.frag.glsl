#version 450

layout (location = 0) in vec3 outColor;
layout (location = 0) out vec4 fragColor;

void main()
{
    fragColor = vec4((outColor / 2) + 0.5f, 1.0);
}