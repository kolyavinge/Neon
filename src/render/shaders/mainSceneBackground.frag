#version 460 core

out vec4 FragColor;

uniform ivec2 resolution;
uniform vec3 backgroundColor;

void main() {
    float y = gl_FragCoord.y / resolution.y;
    y -= 0.5;
    if (y > 0.0) {
        FragColor = vec4(vec3(backgroundColor), 1.0) * (1.0 - (y / 0.5));
    } else {
        discard;
    }
}
