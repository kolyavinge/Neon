#include <render/lib/Material.h>

Material::Material() {
    _ambient = 0.0f;
    _diffuse = 0.0f;
    _specular = 0.0f;
    _shininess = 0.0f;
}

Material::Material(float ambient, float diffuse, float specular, float shininess) {
    _ambient = ambient;
    _diffuse = diffuse;
    _specular = specular;
    _shininess = shininess;
}

Material& Material::operator=(const Material& other) {
    _ambient = other._ambient;
    _diffuse = other._diffuse;
    _specular = other._specular;
    _shininess = other._shininess;

    return *this;
}

float Material::getAmbient() {
    return _ambient;
}

float Material::getDiffuse() {
    return _diffuse;
}

float Material::getSpecular() {
    return _specular;
}

float Material::getShininess() {
    return _shininess;
}
