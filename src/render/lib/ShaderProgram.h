#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <render/lib/Shader.h>
#include <render/lib/opengl.h>

class ShaderProgram : public Object {

    GLuint _id;
    List<GLuint> _shaderIds;

public:
    ShaderProgram();
    ~ShaderProgram();
    void init(Collection<Shader*>& shaders);
    void use();
    void unuse();

protected:
    virtual void initBeforeLink();
    void setInt32(const char* name, GLint value);
    void setFloat32(const char* name, GLfloat value);
    void setBoolean(const char* name, bool value);
    void setVector2(const char* name, GLfloat x, GLfloat y);
    void setVector3(const char* name, Vector3& v);
    void setMatrix3(const char* name, GLfloat* m);
    void setTransformMatrix4(const char* name, TransformMatrix4& m);
    void setOutputNamesForTransformFeedback(GLint count, const char** outputNames);
};
