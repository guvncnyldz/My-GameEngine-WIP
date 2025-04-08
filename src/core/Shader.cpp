#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexSource = loadShaderSource(vertexPath);
    std::string fragmentSource = loadShaderSource(fragmentPath);

    compileAndLinkShaders(vertexSource.c_str(), fragmentSource.c_str());
}

void Shader::use() const {
    glUseProgram(ID); 
}

void Shader::setBool(const char* name, bool value) const {
    int location = getUniformLocation(name);
    use();
    glUniform1i(location, (int)value);
}

void Shader::setInt(const char* name, int value) const {
    int location = getUniformLocation(name);
    use();
    glUniform1i(location, value);
}

void Shader::setFloat(const char* name, float value) const {
    int location = getUniformLocation(name);
    use();
    glUniform1f(location, value);
}

void Shader::setFloat4(const char* name, float v1, float v2, float v3, float v4) const {
    int location = getUniformLocation(name);
    use();
    glUniform4f(location, v1,v2,v3,v4);
}

void Shader::setMat4fv(const char* name, float* value) const
{
    int location = getUniformLocation(name);
    use();
    glUniformMatrix4fv(location, 1, GL_FALSE, value);
}


int Shader::getUniformLocation(const char* name) const
{
    int location = glGetUniformLocation(ID, name);

    if (location == -1)
    {
        LOG_WARNING("Shader name can not find");
    }

    return location;
}


void Shader::compileAndLinkShaders(const char* vertexSource, const char* fragmentSource) {
    unsigned int vertexShader, fragmentShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Compile fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Check fragment shader compilation
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

std::string Shader::loadShaderSource(const char* shaderPath) const {
    std::string shaderCode;
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
    }
    catch (const std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << shaderPath << std::endl;
    }
    return shaderCode;
}
