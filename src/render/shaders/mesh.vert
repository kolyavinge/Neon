#version 460 core

layout (location = 0) in vec3 in_Position;
layout (location = 2) in vec4 in_Color;
layout (location = 3) in vec2 in_TexCoord;

out vec4 Color;
out vec2 TexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

mat4 modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;

void main() {
    Color = in_Color;
    TexCoord = in_TexCoord;
    gl_Position = modelViewProjectionMatrix * vec4(in_Position, 1.0);
}
