#include <common/AssetsDirectory.h>
#include <common/InputManager.h>
#include <core/Game.h>
#include <core/GameInitializer.h>
#include <core/MainInjectModule.h>
#include <core/PlayerInputManager.h>
#include <core/ScreenManager.h>
#include <debug/DebugRenderer.h>
#include <engine/CameraUpdater.h>
#include <engine/GameWorldUpdater.h>
#include <engine/collision/VehicleCollisionLogic.h>
#include <engine/vehicle/EngineLogic.h>
#include <engine/vehicle/ForceLogic.h>
#include <engine/vehicle/GearboxLogic.h>
#include <engine/vehicle/PositionLogic.h>
#include <engine/vehicle/SteeringLogic.h>
#include <engine/vehicle/VehicleUpdater.h>
#include <engine/vehicle/WheelLogic.h>
#include <lib/Environment.h>
#include <lib/FileSystem.h>
#include <lib/ResourceManager.h>
#include <render/common/RenderModel3dCollection.h>
#include <render/common/ShaderCollection.h>
#include <render/common/ShaderProgramCollection.h>
#include <render/lib/Model3dLoader.h>
#include <render/lib/Model3dVAOBuilder.h>
#include <render/lib/RenderModel3dLoader.h>
#include <render/lib/ShaderCompiler.h>
#include <render/lib/TextureLoader.h>
#include <render/lib/VAORenderer.h>
#include <render/ui/RaceScreenRenderer.h>
#include <render/vehicle/VehicleRenderer.h>
#include <ui/RaceScreen.h>

void MainInjectModule::init(Binder& binder) {
    binder.bindSingleton<AssetsDirectory>(AssetsDirectory::resolve);
    binder.bindSingleton<InputManager>();
    binder.bindSingleton<Game>(Game::resolve);
    binder.bindSingleton<GameInitializer>(GameInitializer::resolve);
    binder.bindSingleton<PlayerInputManager>(PlayerInputManager::resolve);
    binder.bindSingleton<ScreenManager>(ScreenManager::resolve);
    binder.bindSingleton<DebugRenderer>();
    binder.bindSingleton<CameraUpdater>();
    binder.bindSingleton<GameWorldUpdater>(GameWorldUpdater::resolve);
    binder.bindSingleton<VehicleCollisionLogic>();
    binder.bindSingleton<EngineLogic>();
    binder.bindSingleton<ForceLogic>(ForceLogic::resolve);
    binder.bindSingleton<GearboxLogic>();
    binder.bindSingleton<PositionLogic>(PositionLogic::resolve);
    binder.bindSingleton<SteeringLogic>(SteeringLogic::resolve);
    binder.bindSingleton<VehicleUpdater>(VehicleUpdater::resolve);
    binder.bindSingleton<WheelLogic>();
    binder.bindSingleton<Environment>();
    binder.bindSingleton<FileSystem>();
    binder.bindSingleton<ResourceManager>();
    binder.bindSingleton<RenderModel3dCollection>(RenderModel3dCollection::resolve);
    binder.bindSingleton<ShaderCollection>(ShaderCollection::resolve);
    binder.bindSingleton<ShaderProgramCollection>(ShaderProgramCollection::resolve);
    binder.bindSingleton<Model3dLoader>(Model3dLoader::resolve);
    binder.bindSingleton<Model3dVAOBuilder>();
    binder.bindSingleton<RenderModel3dLoader>(RenderModel3dLoader::resolve);
    binder.bindSingleton<ShaderCompiler>();
    binder.bindSingleton<TextureLoader>(TextureLoader::resolve);
    binder.bindSingleton<VAORenderer>();
    binder.bindSingleton<RaceScreenRenderer>(RaceScreenRenderer::resolve);
    binder.bindSingleton<VehicleRenderer>(VehicleRenderer::resolve);
    binder.bindSingleton<RaceScreen>(RaceScreen::resolve);
}
