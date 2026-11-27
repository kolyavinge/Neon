#version 460 core

out vec4 FragColor;

in vec3 PositionView;
in vec3 NormalView;
in vec4 Color;
in vec2 TexCoord;

uniform float alphaFactor;

uniform bool useTexture;
uniform sampler2D ourTexture;

uniform struct Material {
    float ambient;
    float diffuse;
    float specular;
    float shininess;
} material;

uniform struct {
    vec3 directionView;
    vec3 color;
} globalLight;

const int maxLightsCount = 20; // есть в MeshShaderProgram
uniform struct {
    vec3 positionView;
    vec3 directionView;
    vec3 color;
    float maxDistance;
    bool isSpecularEnabled;
} lights[maxLightsCount];
uniform int lightsCount;

uniform bool isLightEnabled;
uniform bool isSpecularEnabled;

const float maxDepth = 500.0;

// Schlick’s approximation. Работает для x [0;1] и p > 1
float powSchlickApprox(float x, float p) {
    return x / (p - p * x + x);
}

void calculateGlobalLightColor(inout vec3 ambient, inout vec3 diffuse) {
    vec3 s = -globalLight.directionView;
    vec3 n = normalize(NormalView);
    float sDotN = max(dot(s, n), 0.0);
    ambient += globalLight.color * material.ambient;
    diffuse += globalLight.color * material.diffuse * sDotN;
}

void calculateLightColor(int lightIndex, inout vec3 ambient, inout vec3 diffuse, inout vec3 specular) {
    vec3 lightDirection = lights[lightIndex].positionView - PositionView;
    float lightDistance = length(lightDirection);
    if (lightDistance > lights[lightIndex].maxDistance) return;
    vec3 s = normalize(lightDirection);
    vec3 colorIntensity = lights[lightIndex].color / (lightDistance * lightDistance) * max(dot(-s, lights[lightIndex].directionView), 0.0);
    vec3 n = normalize(NormalView);
    float sDotN = max(dot(s, n), 0.0);
    ambient += colorIntensity * material.ambient;
    diffuse += colorIntensity * material.diffuse * sDotN;
    if (isSpecularEnabled &&
        lights[lightIndex].isSpecularEnabled &&
        material.specular > 0.0 &&
        sDotN > 0.0) {
        vec3 v = normalize(-PositionView);
        vec3 h = normalize(v + s);
        float hDotN = max(dot(h, n), 0.0);
        specular += colorIntensity * material.specular * pow(hDotN, material.shininess);
        //specular += colorIntensity * material.specular * powSchlickApprox(hDotN, material.shininess);
    }
}

void main() {
    float depthFactor = 1.0 - clamp(length(PositionView) / maxDepth, 0.0, 1.0);
    if (depthFactor == 0.0) {
        FragColor = vec4(0.0, 0.0, 0.0, alphaFactor);
        return;
    }
    if (useTexture) {
        FragColor = texture(ourTexture, TexCoord);
    } else {
        FragColor = Color;
    }
    FragColor *= depthFactor;
    if (isLightEnabled) {
        vec3 ambient = vec3(0.0), diffuse = vec3(0.0), specular = vec3(0.0);
        calculateGlobalLightColor(ambient, diffuse);
        for (int lightIndex = 0; lightIndex < lightsCount; lightIndex++) {
            calculateLightColor(lightIndex, ambient, diffuse, specular);
        }
        FragColor *= vec4(diffuse + specular + ambient, alphaFactor);
    }
    FragColor *= 1.5; // общая контрастность
}
