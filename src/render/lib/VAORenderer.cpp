#include <render/lib/opengl.h>
#include <render/lib/VAORenderer.h>

void VAORenderer::render(VAO& vao) {
    glBindVertexArray(vao.getId());
    glDrawElements(vao.getFormat(), vao.getElementsCount(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
