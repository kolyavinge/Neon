#version 460 core

out vec4 FragColor;

in vec3 PositionView;
in vec3 NormalView;
in vec4 Color;
in vec2 TexCoord;

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

const int maxLightsCount = 20; // есть в MeshShaderProgram
uniform struct {
    vec3 position;
    vec3 direction;
    vec3 color;
} lights[maxLightsCount];
uniform int lightsCount;

uniform bool enableLight;
uniform bool enableSpecular;

const float maxDepth = 500.0;

void calculateGlobalLightColor(inout vec3 ambient, inout vec3 diffuse) {
    vec3 n = normalize(NormalView);
    // TODO передавать сюда направление к свету сразу умноженное на viewMatrix
    // не считать lightPositionView - PositionView
    vec3 lightPositionView = vec3(viewMatrix * vec4(globalLight.position, 1.0));
    vec3 s = normalize(lightPositionView - PositionView);
    float sDotN = max(dot(s, n), 0.0);
    vec3 v = normalize(-PositionView);
    ambient += globalLight.color * material.ambient;
    diffuse += globalLight.color * material.diffuse * sDotN;
}

void calculateLightColor(int lightIndex, inout vec3 ambient, inout vec3 diffuse, inout vec3 specular) {
    vec3 lightPositionView = vec3(viewMatrix * vec4(lights[lightIndex].position, 1.0));
    vec3 lightDirection = lightPositionView - PositionView;
    float lightDistance = length(lightDirection);
    vec3 lightDirectionView = vec3(viewMatrix * vec4(lights[lightIndex].direction, 0.0));
    vec3 s = normalize(lightDirection);
    vec3 colorIntensity = lights[lightIndex].color / lightDistance * clamp(dot(-s, lightDirectionView), 0.0, 1.0);
    if (length(colorIntensity) < 0.1) return; // 0.1 есть в VehicleData
    vec3 n = normalize(NormalView);
    float sDotN = max(dot(s, n), 0.0);
    vec3 v = normalize(-PositionView);
    ambient += colorIntensity * material.ambient;
    diffuse += colorIntensity * material.diffuse * sDotN;
    if (enableSpecular && sDotN > 0.0) {
        vec3 h = normalize(v + s);
        float hDotN = max(dot(h, n), 0.0);
        specular += colorIntensity * material.specular * pow(hDotN, material.shininess);
    }
}

void main() {
    float depthFactor = 1.0 - clamp(length(PositionView) / maxDepth, 0.0, 1.0);
    if (depthFactor == 0.0) {
        FragColor = vec4(0.0);
        return;
    }
    if (useTexture) {
        FragColor = texture(ourTexture, TexCoord);
    } else {
        FragColor = Color;
    }
    FragColor *= depthFactor;
    if (enableLight) {
        vec3 ambient = vec3(0.0), diffuse = vec3(0.0), specular = vec3(0.0);
        calculateGlobalLightColor(ambient, diffuse);
        for (int lightIndex = 0; lightIndex < lightsCount; lightIndex++) {
            calculateLightColor(lightIndex, ambient, diffuse, specular);
        }
        FragColor *= vec4(diffuse + specular + ambient, alphaFactor);
    }
}
