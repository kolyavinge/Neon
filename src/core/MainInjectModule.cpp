#include <common/AssetsDirectory.h>
#include <common/InputManager.h>
#include <core/Game.h>
#include <core/GameInitializer.h>
#include <core/MainInjectModule.h>
#include <core/PlayerInputManager.h>
#include <core/ScreenManager.h>
#include <debug/DebugRenderer.h>
#include <engine/common/CameraUpdater.h>
#include <engine/vehicle/EngineLogic.h>
#include <engine/vehicle/ForceLogic.h>
#include <engine/vehicle/GearboxLogic.h>
#include <engine/vehicle/PositionLogic.h>
#include <engine/vehicle/SteeringLogic.h>
#include <engine/vehicle/VehicleUpdater.h>
#include <engine/vehicle/WheelLogic.h>
#include <engine/world/GameWorldInitializer.h>
#include <engine/world/GameWorldUpdater.h>
#include <engine/world/TrackCollection.h>
#include <engine/world/VehicleCollisionLogic.h>
#include <engine/world/WorldSegmentDataFinder.h>
#include <engine/world/WorldSegmentTreeBuilder.h>
#include <engine/world/WorldSegmentVisibilityUpdater.h>
#include <lib/Environment.h>
#include <lib/FileSystem.h>
#include <lib/ResourceManager.h>
#include <render/common/Model3dConverter.h>
#include <render/common/RenderModel3dCollection.h>
#include <render/common/ShaderCollection.h>
#include <render/common/ShaderProgramCollection.h>
#include <render/common/TextureCollection.h>
#include <render/lib/Model3dLoader.h>
#include <render/lib/Model3dVAOBuilder.h>
#include <render/lib/RenderModel3dLoader.h>
#include <render/lib/ShaderCompiler.h>
#include <render/lib/TextureLoader.h>
#include <render/lib/VAORenderer.h>
#include <render/ui/RaceScreenRenderer.h>
#include <render/vehicle/VehicleRenderer.h>
#include <render/world/TrackRenderer.h>
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
    binder.bindSingleton<EngineLogic>(EngineLogic::resolve);
    binder.bindSingleton<ForceLogic>(ForceLogic::resolve);
    binder.bindSingleton<GearboxLogic>();
    binder.bindSingleton<PositionLogic>(PositionLogic::resolve);
    binder.bindSingleton<SteeringLogic>(SteeringLogic::resolve);
    binder.bindSingleton<VehicleUpdater>(VehicleUpdater::resolve);
    binder.bindSingleton<WheelLogic>();
    binder.bindSingleton<GameWorldInitializer>(GameWorldInitializer::resolve);
    binder.bindSingleton<GameWorldUpdater>(GameWorldUpdater::resolve);
    binder.bindSingleton<TrackCollection>();
    binder.bindSingleton<VehicleCollisionLogic>(VehicleCollisionLogic::resolve);
    binder.bindSingleton<WorldSegmentDataFinder>();
    binder.bindSingleton<WorldSegmentTreeBuilder>();
    binder.bindSingleton<WorldSegmentVisibilityUpdater>();
    binder.bindSingleton<Environment>();
    binder.bindSingleton<FileSystem>();
    binder.bindSingleton<ResourceManager>();
    binder.bindSingleton<Model3dConverter>(Model3dConverter::resolve);
    binder.bindSingleton<RenderModel3dCollection>(RenderModel3dCollection::resolve);
    binder.bindSingleton<ShaderCollection>(ShaderCollection::resolve);
    binder.bindSingleton<ShaderProgramCollection>(ShaderProgramCollection::resolve);
    binder.bindSingleton<TextureCollection>(TextureCollection::resolve);
    binder.bindSingleton<Model3dLoader>(Model3dLoader::resolve);
    binder.bindSingleton<Model3dVAOBuilder>();
    binder.bindSingleton<RenderModel3dLoader>(RenderModel3dLoader::resolve);
    binder.bindSingleton<ShaderCompiler>();
    binder.bindSingleton<TextureLoader>(TextureLoader::resolve);
    binder.bindSingleton<VAORenderer>();
    binder.bindSingleton<RaceScreenRenderer>(RaceScreenRenderer::resolve);
    binder.bindSingleton<VehicleRenderer>(VehicleRenderer::resolve);
    binder.bindSingleton<TrackRenderer>(TrackRenderer::resolve);
    binder.bindSingleton<RaceScreen>(RaceScreen::resolve);
}
