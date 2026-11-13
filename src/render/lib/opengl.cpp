#include <iostream>
#include <lib/calc/Math.h>
#include <render/lib/opengl.h>

void glTranslatef(Vector3 v) {
    glTranslatef(v.x, v.y, v.z);
}

void glRotatef(float degrees, Vector3 pivot) {
    glRotatef(degrees, pivot.x, pivot.y, pivot.z);
}

void glVertex3f(Vector3 v) {
    glVertex3f(v.x, v.y, v.z);
}

void gluLookAt(Vector3 position, Vector3 lookAt, Vector3 upAxis) {
    gluLookAt(position.x, position.y, position.z, lookAt.x, lookAt.y, lookAt.z, upAxis.x, upAxis.y, upAxis.z);
}

void glNormal3f(Vector3 v) {
    glNormal3f(v.x, v.y, v.z);
}

void glScalef(Vector3 v) {
    glScalef(v.x, v.y, v.z);
}

void glDrawCircleYZ(float radius, int edgesCount) {
    glPushMatrix();
    glBegin(GL_LINE_LOOP);
    const float radiansStep = Math::piDouble / (float)edgesCount;
    float angle = 0.0f;
    for (int i = 0; i < edgesCount; i++) {
        glVertex3f(0.0f, radius * Math::cos(angle), radius * Math::sin(angle));
        angle += radiansStep;
    }
    glEnd();
    glPopMatrix();
}

void glDebugOutput(
    GLenum source,
    GLenum type,
    unsigned int id,
    GLenum severity,
    GLsizei,
    const char* message,
    const void*) {
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;
    const char* reset = "\033[0m";
    const char* red = "\033[1;31m";
    std::cerr << red << "OpenGL: " << message << std::endl;
    switch (source) {
        case GL_DEBUG_SOURCE_API:             std::cerr << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cerr << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cerr << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cerr << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cerr << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cerr << "Source: Other"; break;
    }
    std::cerr << ", ";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:               std::cerr << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cerr << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cerr << "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         std::cerr << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cerr << "Type: Performance"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cerr << "Type: Other"; break;
    }
    std::cerr << std::endl << reset;
}

OpenGLException::OpenGLException(const wchar_t* msg) :
    Exception(msg) {
}
