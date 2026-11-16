#include <render/lib/VAORenderer.h>
#include <render/lib/opengl.h>

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
