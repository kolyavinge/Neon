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
    loadShader(IDR_SHADER_MESH_VERT, ShaderType::vertex, output meshVertex);
    loadShader(IDR_SHADER_MESH_FRAG, ShaderType::fragment, output meshFragment);
}

void ShaderCollection::loadShader(int shaderResourceId, ShaderType shaderType, output Shader& shader) {
    String source = _resourceManager.getTextFileContent(shaderResourceId);
    _shaderCompiler.compile(source, shaderType, output shader);
}
