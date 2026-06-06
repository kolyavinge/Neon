#include <render/common/ShaderProgramCollection.h>

ShaderProgramCollection::ShaderProgramCollection(
    ShaderCollection& shaderCollection) :
    _shaderCollection(shaderCollection) {
}

void ShaderProgramCollection::initAllPrograms() {
    initProgram(mainScene, 1, &_shaderCollection.common);
    initProgram(mesh, 2, &_shaderCollection.meshVertex, &_shaderCollection.meshFragment);
}

void ShaderProgramCollection::initProgram(ShaderProgram& program, int shadersCount, Shader* shaders ...) {
    List<Shader*> shaderList;
    for (int i = 0; i < shadersCount; i++, shaders++) {
        shaderList.add(shaders);
    }
    program.init(shaderList);
}
