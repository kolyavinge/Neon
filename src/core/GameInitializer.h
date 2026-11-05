#pragma once

#include <engine/world/GameWorldInitializer.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/world/GameWorld.h>
#include <render/common/Model3dCollection.h>
#include <render/common/RenderModel3dCollection.h>
#include <render/common/ShaderCollection.h>
#include <render/common/ShaderProgramCollection.h>
#include <render/common/TextureCollection.h>
#include <render/vehicle/VehicleRenderer.h>
#include <render/world/WorldSegmentRenderer.h>
#include <ui/RaceScreen.h>

class GameInitializer : public Object {

    GameWorldInitializer& _gameWorldInitializer;
    RaceScreen& _debugScreen;
    TextureCollection& _textureCollection;
    ShaderCollection& _shaderCollection;
    ShaderProgramCollection& _shaderProgramCollection;
    Model3dCollection& _model3dCollection;
    RenderModel3dCollection& _renderModel3dCollection;
    VehicleRenderer& _vehicleRenderer;
    WorldSegmentRenderer& _worldSegmentRenderer;

public:
    static GameInitializer* resolve(Resolver& resolver) {
        return new GameInitializer(
            resolver.resolve<GameWorldInitializer>(),
            resolver.resolve<RaceScreen>(),
            resolver.resolve<TextureCollection>(),
            resolver.resolve<ShaderCollection>(),
            resolver.resolve<ShaderProgramCollection>(),
            resolver.resolve<Model3dCollection>(),
            resolver.resolve<RenderModel3dCollection>(),
            resolver.resolve<VehicleRenderer>(),
            resolver.resolve<WorldSegmentRenderer>());
    }

    GameInitializer(
        GameWorldInitializer& gameWorldInitializer,
        RaceScreen& debugScreen,
        TextureCollection& textureCollection,
        ShaderCollection& shaderCollection,
        ShaderProgramCollection& shaderProgramCollection,
        Model3dCollection& model3dCollection,
        RenderModel3dCollection& renderModel3dCollection,
        VehicleRenderer& vehicleRenderer,
        WorldSegmentRenderer& worldSegmentRenderer);

    void initGame();
    void initGameWorld(GameWorld& gameWorld);
};
