#pragma once

#include <lib/system.h>
#include <render/lib/opengl.h>

enum class BufferIndices {
    vertices = 0,
    normals = 1,
    colors = 2,
    texCoords = 3,
    faces = 4,
    _count = 5
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
    void init(GLuint id, Array<GLuint, (int)BufferIndices::_count>& vboIds, GLenum format, GLsizei elementsCount);
    GLuint getId();
    GLenum getFormat();
    GLsizei getElementsCount();
};
