#include <render/lib/VAORenderer.h>
#include <render/lib/opengl.h>

void VAORenderer::init() {
    initScreenQuad();
}

void VAORenderer::initScreenQuad() {
    GLuint vaoId;
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);
    Array<GLuint, BufferIndices::_count> vboIds;
    glGenBuffers(1, &vboIds[(int)BufferIndices::vertices]);
    glGenBuffers(1, &vboIds[(int)BufferIndices::faces]);

    Array<GLfloat, 4 * 3> verticesArray;
    GLfloat verticesArrayData[verticesArray.Count] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f
    };
    verticesArray.copyFrom(verticesArrayData, verticesArray.Count);
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[(int)BufferIndices::vertices]);
    glBufferData(GL_ARRAY_BUFFER, verticesArray.getSizeInBytes(), verticesArray.getItemsPointer(), GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)BufferIndices::vertices, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray((GLuint)BufferIndices::vertices);

    Array<GLuint, 2 * 3> facesArray;
    GLuint facesArrayData[facesArray.Count] = {
        0, 1, 2,
        0, 2, 3
    };
    facesArray.copyFrom(facesArrayData, facesArray.Count);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[(int)BufferIndices::faces]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, facesArray.getSizeInBytes(), facesArray.getItemsPointer(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    _screenQuad.init(vaoId, vboIds, GL_TRIANGLES, facesArray.getCount());
}

void VAORenderer::render(VAO& vao) {
    glBindVertexArray(vao.getId());
    glDrawElements(vao.getFormat(), vao.getElementsCount(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void VAORenderer::renderInstances(VAO& vao, int instancesCount) {
    glBindVertexArray(vao.getId());
    glDrawElementsInstanced(vao.getFormat(), vao.getElementsCount(), GL_UNSIGNED_INT, nullptr, instancesCount);
    glBindVertexArray(0);
}

void VAORenderer::renderScreenQuad() {
    render(_screenQuad);
}
