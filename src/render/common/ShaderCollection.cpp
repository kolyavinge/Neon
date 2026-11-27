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
    loadShader(IDR_SHADER_SIMPLE_VERT, ShaderType::vertex, output simpleVertex);
    loadShader(IDR_SHADER_MAINSCENE_VERT, ShaderType::vertex, output mainSceneVertex);
    loadShader(IDR_SHADER_MAINSCENE_FRAG, ShaderType::fragment, output mainSceneFragment);
    loadShader(IDR_SHADER_MAINSCENEBACKGROUND_FRAG, ShaderType::fragment, output mainSceneBackgroundFragment);
}

void ShaderCollection::loadShader(int shaderResourceId, ShaderType shaderType, output Shader& shader) {
    String source = _resourceManager.getTextFileContent(shaderResourceId);
    _shaderCompiler.compile(source, shaderType, output shader);
}
