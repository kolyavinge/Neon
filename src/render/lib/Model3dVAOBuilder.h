#pragma once

#include <lib/system.h>
#include <render/lib/Model3d.h>
#include <render/lib/VAO.h>

class Model3dVAOBuilder : public Object {

public:
    void build(Mesh& mesh, output VAO& vao);

private:
    void buildArrayBuffer(
        Array<GLuint, (int)BufferIndices::_count>& vboIds,
        BufferIndices bufferIndex,
        GLsizeiptr arraySizeInBytes,
        const void* arrayData,
        GLint attribCount,
        GLenum attribType);

    void buildElementArrayBuffer(
        Array<GLuint, (int)BufferIndices::_count>& vboIds,
        BufferIndices bufferIndex,
        GLsizeiptr arraySizeInBytes,
        const void* arrayData);
};
