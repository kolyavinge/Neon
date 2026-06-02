#include <render/lib/Model3dVAOBuilder.h>

void Model3dVAOBuilder::build(Mesh& mesh, output VAO& vao) {
    GLuint vaoId;
    glGenVertexArrays(1, &vaoId);
    vao.init(vaoId, GL_TRIANGLES, mesh.faces.getCount());
    glBindVertexArray(vao.getId());

    GLuint vboIds[(int)BufferIndices::_count];
    glGenBuffers((int)BufferIndices::_count, vboIds);

    GLuint bufferIndex = (GLuint)BufferIndices::vertices;
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[bufferIndex]);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.getSizeInBytes(), mesh.vertices.getItemsPointer(), GL_STATIC_DRAW);
    glVertexAttribPointer(bufferIndex, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(bufferIndex);

    bufferIndex = (GLuint)BufferIndices::normals;
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[bufferIndex]);
    glBufferData(GL_ARRAY_BUFFER, mesh.normals.getSizeInBytes(), mesh.normals.getItemsPointer(), GL_STATIC_DRAW);
    glVertexAttribPointer(bufferIndex, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(bufferIndex);

    bufferIndex = (GLuint)BufferIndices::texCoords;
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[bufferIndex]);
    glBufferData(GL_ARRAY_BUFFER, mesh.texCoords.getSizeInBytes(), mesh.texCoords.getItemsPointer(), GL_STATIC_DRAW);
    glVertexAttribPointer(bufferIndex, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(bufferIndex);

    bufferIndex = (GLuint)BufferIndices::faces;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[bufferIndex]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.faces.getSizeInBytes(), mesh.faces.getItemsPointer(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
