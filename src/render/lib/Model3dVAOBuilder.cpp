#include <render/lib/Model3dVAOBuilder.h>

void Model3dVAOBuilder::build(Mesh& mesh, output VAO& vao) {
    GLuint vaoId;
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);
    Array<GLuint, (int)BufferIndices::_count> vboIds;
    buildArrayBuffer(vboIds, BufferIndices::vertices, mesh.vertices.getSizeInBytes(), mesh.vertices.getItemsPointer(), 3, GL_FLOAT);
    buildArrayBuffer(vboIds, BufferIndices::normals, mesh.normals.getSizeInBytes(), mesh.normals.getItemsPointer(), 3, GL_FLOAT);
    buildArrayBuffer(vboIds, BufferIndices::colors, mesh.colors.getSizeInBytes(), mesh.colors.getItemsPointer(), 4, GL_FLOAT);
    buildArrayBuffer(vboIds, BufferIndices::texCoords, mesh.texCoords.getSizeInBytes(), mesh.texCoords.getItemsPointer(), 2, GL_FLOAT);
    buildElementArrayBuffer(vboIds, BufferIndices::faces, mesh.faces.getSizeInBytes(), mesh.faces.getItemsPointer());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    vao.init(vaoId, vboIds, GL_TRIANGLES, mesh.faces.getCount());
}

void Model3dVAOBuilder::buildArrayBuffer(
    Array<GLuint, (int)BufferIndices::_count>& vboIds,
    BufferIndices bufferIndex,
    GLsizeiptr arraySizeInBytes,
    const void* arrayData,
    GLint attribCount,
    GLenum attribType) {
    glGenBuffers(1, &vboIds[(int)bufferIndex]);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[(int)bufferIndex]);
    glBufferData(GL_ARRAY_BUFFER, arraySizeInBytes, arrayData, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)bufferIndex, attribCount, attribType, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray((GLuint)bufferIndex);
}

void Model3dVAOBuilder::buildElementArrayBuffer(
    Array<GLuint, (int)BufferIndices::_count>& vboIds,
    BufferIndices bufferIndex,
    GLsizeiptr arraySizeInBytes,
    const void* arrayData) {
    glGenBuffers(1, &vboIds[(int)bufferIndex]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[(int)bufferIndex]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, arraySizeInBytes, arrayData, GL_STATIC_DRAW);
}
