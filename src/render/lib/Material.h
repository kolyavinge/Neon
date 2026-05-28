#pragma once

#include <lib/system.h>

class Material : public Object {

    float _ambient;
    float _diffuse;
    float _specular;
    float _shininess;

public:
    Material();
    Material(float ambient, float diffuse, float specular, float shininess);
    float getAmbient();
    float getDiffuse();
    float getSpecular();
    float getShininess();
};
