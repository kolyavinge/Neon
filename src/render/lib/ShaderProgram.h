#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <render/lib/Shader.h>
#include <render/lib/opengl.h>

class ShaderProgram : public Object {

    GLuint _id;

public:
    ShaderProgram();
    void init(Collection<Shader>& shaders);
    void use();
    void unuse();

protected:
    virtual void initBeforeLink();
    void setInt32(GLchar* name, GLint value);
    void setFloat32(GLchar* name, GLfloat value);
    void setBoolean(GLchar* name, bool value);
    void setVector2(GLchar* name, GLfloat x, GLfloat y);
    void setVector3(GLchar* name, Vector3& v);
    void setMatrix3(GLchar* name, GLfloat* m);
    void setTransformMatrix4(GLchar* name, TransformMatrix4& m);
    void setOutputNamesForTransformFeedback(GLint count, GLchar** outputNames);
};
