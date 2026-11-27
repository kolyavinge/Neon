#include <render/common/ShaderProgramCollection.h>

ShaderProgramCollection::ShaderProgramCollection(
    ShaderCollection& shaderCollection) :
    _shaderCollection(shaderCollection) {
}

void ShaderProgramCollection::initAllPrograms() {
    List<Shader*> shaders;

    //initProgram(output mainScene, 1, &_shaderCollection.common);

    shaders.clear();
    shaders.add(&_shaderCollection.mainSceneVertex);
    shaders.add(&_shaderCollection.mainSceneFragment);
    mainScene.init(shaders);

    shaders.clear();
    shaders.add(&_shaderCollection.simpleVertex);
    shaders.add(&_shaderCollection.mainSceneBackgroundFragment);
    mainSceneBackground.init(shaders);
}
