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

uniform struct {
    vec3 position;
    vec3 color;
} globalLight;

const int maxLightsCount = 20;
uniform struct {
    vec3 position;
    vec3 direction;
    vec3 color;
} lights[maxLightsCount];
uniform int lightsCount;

void calculateGlobalLightColor(inout vec3 ambient, inout vec3 diffuse, inout vec3 specular) {
    vec3 n = normalize(NormalView);
    vec3 lightPositionView = vec3(viewMatrix * vec4(globalLight.position, 1.0));
    vec3 s = normalize(lightPositionView - PositionView);
    float sDotN = max(dot(s, n), 0.0);
    vec3 v = normalize(-PositionView);
    vec3 h = normalize(v + s);
    float hDotN = max(dot(h, n), 0.0);
    ambient += globalLight.color * material.ambient;
    diffuse += globalLight.color * material.diffuse * sDotN;
    if (sDotN > 0.0) {
        specular += globalLight.color * material.specular * pow(hDotN, material.shininess);
    }
}

void calculateLightColor(int lightIndex, inout vec3 ambient, inout vec3 diffuse, inout vec3 specular) {
    vec3 lightDirectionView = vec3(viewMatrix * vec4(lights[lightIndex].direction, 0.0));
    vec3 n = normalize(NormalView);
    vec3 lightPositionView = vec3(viewMatrix * vec4(lights[lightIndex].position, 1.0));
    vec3 s = normalize(lightPositionView - PositionView);
    float sDotN = max(dot(s, n), 0.0);
    vec3 v = normalize(-PositionView);
    vec3 h = normalize(v + s);
    float hDotN = max(dot(h, n), 0.0);
    float l = length(lightPositionView - PositionView);
    float intensity = (1.0 / l) * clamp(dot(-s, lightDirectionView), 0.0, 1.0);
    ambient += lights[lightIndex].color * material.ambient * intensity;
    diffuse += lights[lightIndex].color * material.diffuse * sDotN * intensity;
    if (sDotN > 0.0) {
        specular += lights[lightIndex].color * material.specular * pow(hDotN, material.shininess) * intensity;
    }
}

void main() {
    if (useTexture) {
        FragColor = texture(ourTexture, TexCoord);
    } else {
        FragColor = Color;
    }
    vec3 ambient = vec3(0.0), diffuse = vec3(0.0), specular = vec3(0.0);
    calculateGlobalLightColor(ambient, diffuse, specular);
    for (int lightIndex = 0; lightIndex < lightsCount; lightIndex++) {
        calculateLightColor(lightIndex, ambient, diffuse, specular);
    }
    FragColor *= vec4(diffuse + specular + ambient, 1.0);
    FragColor *= vec4(vec3(colorFactor), alphaFactor);
}
