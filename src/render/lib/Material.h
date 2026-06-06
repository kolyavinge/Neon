#pragma once

#include <lib/system.h>

class Material : public Object {

    float _ambient;
    float _diffuse;
    float _specular;
    float _shininess;

public:
    static Material standard;

    Material();
    Material(float ambient, float diffuse, float specular, float shininess);
    Material& operator=(const Material& other);
    float getAmbient();
    float getDiffuse();
    float getSpecular();
    float getShininess();
};
