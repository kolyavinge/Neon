#include <render/gl/opengl.h>

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
