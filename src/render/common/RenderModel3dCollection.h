#pragma once

#include <common/AssetsDirectory.h>
#include <lib/di/Resolver.h>
#include <lib/system.h>
#include <model/vehicle/Wheel.h>
#include <render/lib/Model3d.h>
#include <render/lib/Model3dLoader.h>
#include <render/lib/RenderModel3d.h>
#include <render/lib/RenderModel3dLoader.h>

class RenderModel3dCollection : public Object {

    AssetsDirectory& _assetsDirectory;
    Model3dLoader& _model3dLoader;
    RenderModel3dLoader& _renderModel3dLoader;
    RenderModel3d _vehicleBody;
    Array<RenderModel3d, VehicleConstants::wheelsCount> _vehicleWheels;

public:
    static RenderModel3dCollection* resolve(Resolver& resolver) {
        return new RenderModel3dCollection(
            resolver.resolve<AssetsDirectory>(),
            resolver.resolve<Model3dLoader>(),
            resolver.resolve<RenderModel3dLoader>());
    }

    RenderModel3dCollection(
        AssetsDirectory& assetsDirectory,
        Model3dLoader& model3dLoader,
        RenderModel3dLoader& renderModel3dLoader);

    void loadAllModels();
    RenderModel3d& getVehicleBody();
    RenderModel3d& getVehicleWheel(WheelPosition position);

private:
    float getWheelRadius(Model3d& wheelModel);
};
