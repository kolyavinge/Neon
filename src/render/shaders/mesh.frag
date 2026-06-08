#version 460 core

out vec4 FragColor;

in vec4 Color;
in vec2 TexCoord;

uniform float colorFactor;
uniform float alphaFactor;
uniform bool useTexture;
uniform sampler2D ourTexture;

void main() {
    if (useTexture) {
        FragColor = texture(ourTexture, TexCoord);
    } else {
        FragColor = Color;
    }
    FragColor.x *= colorFactor;
    FragColor.y *= colorFactor;
    FragColor.z *= colorFactor;
    FragColor.w *= alphaFactor;
}
