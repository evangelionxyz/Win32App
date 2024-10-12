#include "shader.hpp"

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Shader::Shader(const char *vertex_filepath, const char *fragment_filepath)
{
    u32 vertex_shader = create_shader(vertex_filepath, GL_VERTEX_SHADER);
    u32 fragment_shader = create_shader(fragment_filepath, GL_FRAGMENT_SHADER);

    m_Id = glCreateProgram();
    glAttachShader(m_Id, vertex_shader);
    glAttachShader(m_Id, fragment_shader);
    glLinkProgram(m_Id);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

Shader::~Shader()
{
    glDeleteProgram(m_Id);
}

void Shader::use()
{
    glUseProgram(m_Id);
}

void Shader::unuse()
{
    glUseProgram(0);
}

u32 Shader::create_shader(const char *filepath, u32 type)
{
    std::ifstream file(filepath);
    std::stringstream buffer;

    buffer << file.rdbuf();
    std::string source_str = buffer.str();
    const char *source = source_str.c_str();

    u32 shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infolog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infolog);
        std::cerr << "Error: Shader Compilation Failed\n" << infolog << std::endl;
    }

    return shader;
}

