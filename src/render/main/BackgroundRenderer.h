#pragma once

#include <common/EventManager.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <render/common/ShaderProgramCollection.h>
#include <render/lib/VAORenderer.h>
#include <render/shaderprograms/MainSceneBackgroundShaderProgram.h>

class BackgroundRenderer : public Object {

    MainSceneBackgroundShaderProgram& _shader;
    VAORenderer& _vaoRenderer;

public:
    static BackgroundRenderer* resolve(Resolver& resolver) {
        return new BackgroundRenderer(
            resolver.resolve<ShaderProgramCollection>(),
            resolver.resolve<VAORenderer>(),
            resolver.resolve<EventManager>());
    }

    BackgroundRenderer(
        ShaderProgramCollection& shaderProgramCollection,
        VAORenderer& vaoRenderer,
        EventManager& eventManager
    );

    void render();
};
