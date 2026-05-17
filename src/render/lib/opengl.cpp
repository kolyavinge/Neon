#include <lib/calc/Math.h>
#include <render/lib/opengl.h>

void glTranslatef(Vector3& v) {
    glTranslatef(v.x, v.y, v.z);
}

void glRotatef(float degrees, Vector3& pivot) {
    glRotatef(degrees, pivot.x, pivot.y, pivot.z);
}

void glVertex3f(Vector3& v) {
    glVertex3f(v.x, v.y, v.z);
}

void gluLookAt(Vector3& position, Vector3& lookAt, Vector3& upAxis) {
    gluLookAt(position.x, position.y, position.z, lookAt.x, lookAt.y, lookAt.z, upAxis.x, upAxis.y, upAxis.z);
}

void glNormal3f(Vector3& v) {
    glNormal3f(v.x, v.y, v.z);
}

void glScalef(Vector3& v) {
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

OpenGLException::OpenGLException(const wchar_t* msg) :
    Exception(msg) {
}
