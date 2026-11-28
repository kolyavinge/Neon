#pragma once

#include <lib/system.h>
#include <render/lib/ShaderProgram.h>

class MainSceneBackgroundShaderProgram : public ShaderProgram {

    struct {
        GLint resolution;
        GLint backgroundColor;
    } _locations = {};

public:
    void setResolution(int width, int height);
    void setBackgroundColor(Vector3 color);

private:
    void initAfterLink() override;
};
