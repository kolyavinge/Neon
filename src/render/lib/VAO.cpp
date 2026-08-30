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

void VAO::init(GLuint id, Array<GLuint, (int)BufferIndices::_count>& vboIds, GLenum format, GLsizei elementsCount) {
    _id = id;
    _vboIds = vboIds;
    _format = format;
    _elementsCount = elementsCount;
}

GLuint VAO::getId() {
    return _id;
}

GLenum VAO::getFormat() {
    return _format;
}

GLsizei VAO::getElementsCount() {
    return _elementsCount;
}
