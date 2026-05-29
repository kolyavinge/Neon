#include <common/resource.h>
#include <render/common/ShaderCollection.h>

ShaderCollection::ShaderCollection(
    ResourceManager& resourceManager,
    ShaderCompiler& shaderCompiler) :
    _resourceManager(resourceManager),
    _shaderCompiler(shaderCompiler) {
}

void ShaderCollection::loadAllShaders() {
    String source = _resourceManager.getTextFileContent(IDR_SHADER_COMMON);
    _shaderCompiler.compile(source, ShaderType::vertex, output common);
}
