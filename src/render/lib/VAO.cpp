#include <render/lib/VAO.h>

VAO::VAO() {
    _id = 0;
    _format = 0;
    _elementsCount = 0;
}

VAO::~VAO() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteBuffers(_vboIds.getCount(), _vboIds.getItemsPointer());
    glDeleteVertexArrays(1, &_id);
}

void VAO::init(GLuint id, GLenum format, GLsizei elementsCount) {
    _id = id;
    _format = format;
    _elementsCount = elementsCount;
}

GLuint VAO::getId() {
    return _id;
}

void VAO::addVboId(BufferIndices bufferIndex, GLuint vboId) {
    _vboIds[(int)bufferIndex] = vboId;
}

GLenum VAO::getFormat() {
    return _format;
}

GLsizei VAO::getElementsCount() {
    return _elementsCount;
}
