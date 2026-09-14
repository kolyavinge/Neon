#pragma once

#include <engine/world/GameWorldInitializer.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/world/GameWorld.h>
#include <render/common/RenderModel3dCollection.h>
#include <render/common/ShaderCollection.h>
#include <render/common/ShaderProgramCollection.h>
#include <render/common/TextureCollection.h>
#include <render/vehicle/VehicleRenderer.h>
#include <render/world/TrackRenderer.h>
#include <ui/RaceScreen.h>

class GameInitializer : public Object {

    GameWorldInitializer& _gameWorldInitializer;
    RaceScreen& _debugScreen;
    TextureCollection& _textureCollection;
    ShaderCollection& _shaderCollection;
    ShaderProgramCollection& _shaderProgramCollection;
    RenderModel3dCollection& _renderModel3dCollection;
    VehicleRenderer& _vehicleRenderer;
    TrackRenderer& _trackRenderer;

public:
    static GameInitializer* resolve(Resolver& resolver) {
        return new GameInitializer(
            resolver.resolve<GameWorldInitializer>(),
            resolver.resolve<RaceScreen>(),
            resolver.resolve<TextureCollection>(),
            resolver.resolve<ShaderCollection>(),
            resolver.resolve<ShaderProgramCollection>(),
            resolver.resolve<RenderModel3dCollection>(),
            resolver.resolve<VehicleRenderer>(),
            resolver.resolve<TrackRenderer>());
    }

    GameInitializer(
        GameWorldInitializer& gameWorldInitializer,
        RaceScreen& debugScreen,
        TextureCollection& textureCollection,
        ShaderCollection& shaderCollection,
        ShaderProgramCollection& shaderProgramCollection,
        RenderModel3dCollection& renderModel3dCollection,
        VehicleRenderer& vehicleRenderer,
        TrackRenderer& trackRenderer);

    void initGame();
    void initGameWorld(GameWorld& gameWorld);
};
