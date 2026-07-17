#pragma once

#pragma warning(push)
#pragma warning(disable : 5039 4668 5204 4100)
// glew должен подключаться раньше gl
#include <glew/glew.h>

#include <gl/gl.h>
#include <gl/glu.h>
#pragma warning(pop)

#include <lib/exceptions.h>
#include <lib/calc/Vector3.h>

void glTranslatef(Vector3 v);
void glRotatef(float degrees, Vector3 pivot);
void glVertex3f(Vector3 v);
void gluLookAt(Vector3 position, Vector3 lookAt, Vector3 upAxis);
void glNormal3f(Vector3 v);
void glScalef(Vector3 v);
void glDrawCircleYZ(float radius, int edgesCount);

class OpenGLException : public Exception {

public:
    OpenGLException(const wchar_t* msg);
};
