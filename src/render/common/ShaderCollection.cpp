#include <render/common/ShaderCollection.h>

ShaderCollection::ShaderCollection(
    ProjectDirectories& projectDirectories,
    ShaderCompiler& shaderCompiler) :
    _projectDirectories(projectDirectories),
    _shaderCompiler(shaderCompiler) {
}

void ShaderCollection::init() {
    String shaderFileFullPath(_projectDirectories.getShaders());
    shaderFileFullPath.append(L"shader1.vert");
    shader1 = _shaderCompiler.compile(shaderFileFullPath, ShaderType::vertex);

    shaderFileFullPath = _projectDirectories.getShaders();
    shaderFileFullPath.append(L"shader2.vert");
    shader2 = _shaderCompiler.compile(shaderFileFullPath, ShaderType::vertex);
}
