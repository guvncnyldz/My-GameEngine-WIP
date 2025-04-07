#ifndef SHADER_H
#define SHADER_H


#include <Logger.h>

#include <pch.h>

class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    
    void use() const;
    
    void setBool(const char* name, bool value) const;
    void setInt(const char* name, int value) const;
    void setFloat(const char* name, float value) const;
    void setFloat4(const char* name, float v1, float v2, float v3, float v4) const;

private:
    int getUniformLocation(const char* name) const;
    void compileAndLinkShaders(const char* vertexSource, const char* fragmentSource);
    std::string loadShaderSource(const char* shaderPath) const;
};

#endif
