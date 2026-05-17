#pragma once

#include <lib/calc/TransformMatrix4.h>
#include <lib/calc/Vector3.h>
#include <lib/system.h>
#include <render/lib/Shader.h>

class ShaderProgram : public Object {

    GLuint _id;

public:
    ShaderProgram();
    void init(Collection<Shader>& shaders);
    void use();
    void unuse();

protected:
    virtual void initBeforeLink();
    void setInt32(char* name, int value);
    void setFloat32(char* name, float value);
    void setBoolean(char* name, bool value);
    void setVector2(char* name, float x, float y);
    void setVector3(char* name, Vector3& v);
    void setMatrix3(char* name, float* m);
    void setTransformMatrix4(char* name, TransformMatrix4& m);
    void setOutputNamesForTransformFeedback(int count, char** outputNames);
};
