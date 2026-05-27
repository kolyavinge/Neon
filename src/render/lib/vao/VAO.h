#pragma once

#include <lib/system.h>
#include <render/lib/opengl.h>

enum class BufferIndices {
    vertices = 0,
    normals = 1,
    texCoords = 2,
    faces = 3,
    _count = 4
};

// vertex array object
class VAO : public Object {

    GLuint _id;
    Array<GLuint, (int)BufferIndices::_count> _vboIds;
    GLenum _format;
    GLsizei _elementsCount;

public:
    VAO();
    ~VAO();
    void init(GLuint id, GLenum format, GLsizei elementsCount);
    GLuint getId();
    void addVboId(BufferIndices bufferIndex, GLuint vboId);
    GLenum getFormat();
    GLsizei getElementsCount();
};
