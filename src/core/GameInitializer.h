#pragma once

#include <engine/GameState.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <render/common/RenderModel3dCollection.h>
#include <render/common/ShaderCollection.h>
#include <render/common/ShaderProgramCollection.h>
#include <render/vehicle/VehicleRenderer.h>
#include <ui/RaceScreen.h>

class GameInitializer : public Object {

    GameUpdater& _gameUpdater;
    RaceScreen& _debugScreen;
    ShaderCollection& _shaderCollection;
    ShaderProgramCollection& _shaderProgramCollection;
    RenderModel3dCollection& _renderModel3dCollection;
    VehicleRenderer& _vehicleRenderer;

public:
    static GameInitializer* resolve(Resolver& resolver) {
        return new GameInitializer(
            resolver.resolve<GameUpdater>(),
            resolver.resolve<RaceScreen>(),
            resolver.resolve<ShaderCollection>(),
            resolver.resolve<ShaderProgramCollection>(),
            resolver.resolve<RenderModel3dCollection>(),
            resolver.resolve<VehicleRenderer>());
    }

    GameInitializer(
        GameUpdater& gameUpdater,
        RaceScreen& debugScreen,
        ShaderCollection& shaderCollection,
        ShaderProgramCollection& shaderProgramCollection,
        RenderModel3dCollection& renderModel3dCollection,
        VehicleRenderer& vehicleRenderer);

    void initGame(GameState& gameState);
};
