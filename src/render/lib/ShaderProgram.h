#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <render/lib/Shader.h>
#include <render/lib/opengl.h>

class ShaderProgram : public Object {

    List<GLuint> _shaderIds;

public:
    DENY_COPYING(ShaderProgram); // классы использующие ресурсы opengl запрещены к копированию
    ShaderProgram();
    ~ShaderProgram();
    void init(Collection<Shader*>& shaders);
    void use();
    void unuse();

protected:
    GLuint _id;

    virtual void initBeforeLink();
    virtual void initAfterLink();
    void setInt32(GLint location, GLint value);
    void setFloat32(GLint location, GLfloat value);
    void setBoolean(GLint location, bool value);
    void setVector2(GLint location, GLfloat x, GLfloat y);
    void setVector3(GLint location, Vector3 v);
    void setMatrix3(GLint location, GLfloat* m);
    void setTransformMatrix4(GLint location, TransformMatrix4& m);
    void setOutputNamesForTransformFeedback(GLint count, const char** outputNames);
};
