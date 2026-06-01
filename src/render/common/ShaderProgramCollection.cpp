#include <render/common/ShaderProgramCollection.h>

ShaderProgramCollection::ShaderProgramCollection(
    ShaderCollection& shaderCollection) :
    _shaderCollection(shaderCollection) {
}

void ShaderProgramCollection::initAllPrograms() {
    List<Shader*> shaders;

    shaders.add(&_shaderCollection.common);
    //shaders.add(&_shaderCollection.shader2);
    mainScene.init(shaders);

    shaders.clear();
    //shaders.add(&_shaderCollection.common);
    //shaders.add(&_shaderCollection.shader2);
    //main.init(shaders);
}
