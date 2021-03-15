#include "Shader.h"

Shader::~Shader()
{
    if (program != GL_NONE)
    {
        glDeleteProgram(program);
    }
}

bool Shader::Works()
{
    return !error;
}

void Shader::Start()
{
    glUseProgram(program);
}

int Shader::LoadCompileShader(const char* path, int type)
{

    std::ifstream file(path);
    if (!file.good())
    {
        std::cout << "Couldn't open shader file for loading: " << path << std::endl;
        return GL_NONE;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileContentsStr = buffer.str();
    const char* fileContents = fileContentsStr.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &fileContents, nullptr);
    glCompileShader(shader);

    return shader;
}

bool Shader::Compild(int shader)
{
    GLint compileSucceeded = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSucceeded);

    if (compileSucceeded == GL_FALSE)
    {
        GLint errorLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLength);

        GLchar* errorLog = new GLchar[errorLength];
        glGetShaderInfoLog(shader, errorLength, &errorLength, errorLog);

        std::cout << "Error compiling shader: " << errorLog << std::endl;
        delete[] errorLog;
        return false;
    }

    return true;
}

bool Shader::ProgramLinked(int shader)
{
    GLint linkSucceeded = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linkSucceeded);

    if (linkSucceeded == GL_FALSE)
    {
        GLint errorLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &errorLength);

        GLchar* errorLog = new GLchar[errorLength];
        glGetProgramInfoLog(program, errorLength, &errorLength, errorLog);

        std::cout << "Error linking shader program: " << errorLog << std::endl;
        delete[] errorLog;
        return false;
    }

    return true;
}