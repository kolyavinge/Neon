#include <render/common/ShaderProgramCollection.h>

ShaderProgramCollection::ShaderProgramCollection(
    ShaderCollection& shaderCollection) :
    _shaderCollection(shaderCollection) {
}

void ShaderProgramCollection::initAllPrograms() {
    //initProgram(output mainScene, 1, &_shaderCollection.common);
    initProgram(output mainScene, 2, &_shaderCollection.mainSceneVertex, &_shaderCollection.mainSceneFragment);
}

void ShaderProgramCollection::initProgram(output ShaderProgram& program, int shadersCount, Shader* shaders ...) {
    List<Shader*> shaderList;
    for (int i = 0; i < shadersCount; i++, shaders++) {
        shaderList.add(shaders);
    }
    program.init(shaderList);
}
