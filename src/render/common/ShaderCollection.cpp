#include <common/resource.h>
#include <render/common/ShaderCollection.h>

ShaderCollection::ShaderCollection(
    ResourceManager& resourceManager,
    ShaderCompiler& shaderCompiler) :
    _resourceManager(resourceManager),
    _shaderCompiler(shaderCompiler) {
}

void ShaderCollection::loadAllShaders() {
    loadShader(IDR_SHADER_COMMON, ShaderType::vertex, output common);
    loadShader(IDR_SHADER_MAIN_SCENE_VERT, ShaderType::vertex, output mainSceneVertex);
    loadShader(IDR_SHADER_MAIN_SCENE_FRAG, ShaderType::fragment, output mainSceneFragment);
}

void ShaderCollection::loadShader(int shaderResourceId, ShaderType shaderType, output Shader& shader) {
    String source = _resourceManager.getTextFileContent(shaderResourceId);
    _shaderCompiler.compile(source, shaderType, output shader);
}
