#version 460 core

out vec4 FragColor;

in vec3 PositionView;
in vec3 NormalView;
in vec4 Color;
in vec2 TexCoord;

uniform float colorFactor;
uniform float alphaFactor;
uniform bool useTexture;
uniform sampler2D ourTexture;
uniform mat4 viewMatrix;

uniform struct Material {
    float ambient;
    float diffuse;
    float specular;
    float shininess;
} material;

uniform struct Light {
    vec3 position;
    vec3 color;
} globalLight;

void getGlobalLightFragColor(inout vec3 ambient, inout vec3 diffuse, inout vec3 specular) {
    vec3 n = normalize(NormalView);
    vec3 positionView = vec3(viewMatrix * vec4(globalLight.position, 1.0));
    vec3 s = normalize(positionView - PositionView);
    float sDotN = max(dot(s, n), 0.0);
    vec3 v = normalize(-PositionView);
    vec3 h = normalize(v + s);
    float hDotN = max(dot(h, n), 0.0);
    ambient = globalLight.color * material.ambient;
    diffuse = globalLight.color * material.diffuse * sDotN;
    if (sDotN > 0.0) {
        specular = globalLight.color * material.specular * pow(hDotN, material.shininess);
    } else {
        specular = vec3(0.0);
    }
}

void main() {
    vec3 ambient, diffuse, specular;
    getGlobalLightFragColor(ambient, diffuse, specular);
    if (useTexture) {
        FragColor = texture(ourTexture, TexCoord);
    } else {
        FragColor = Color;
    }
    FragColor *= vec4(diffuse + specular + ambient, 1.0);
    FragColor *= vec4(vec3(colorFactor), alphaFactor);
}
