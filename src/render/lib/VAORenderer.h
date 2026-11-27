#pragma once

#include <lib/system.h>
#include <render/lib/VAO.h>

class VAORenderer : public Object {

    VAO _screenQuad;

public:
    void init();
    void render(VAO& vao);
    void renderInstances(VAO& vao, int instancesCount);
    void renderScreenQuad();

private:
    void initScreenQuad();
};
