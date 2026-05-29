#include <render/common/ShaderProgramCollection.h>

ShaderProgramCollection::ShaderProgramCollection(
    ShaderCollection& shaderCollection) :
    _shaderCollection(shaderCollection) {
}

void ShaderProgramCollection::initAllPrograms() {
    List<Shader*> shaders;

    shaders.add(&_shaderCollection.common);
    shaders.add(&_shaderCollection.shader2);
    shaderProgram1.init(shaders);

    shaders.clear();
    shaders.add(&_shaderCollection.common);
    shaders.add(&_shaderCollection.shader2);
    shaderProgram1.init(shaders);
}
