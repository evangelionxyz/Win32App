#pragma once
#include <stdint.h>

#include "types.h"

class Shader
{
public:
    Shader(const char *vertex_filepath, const char *fragment_filepath);
    ~Shader();

    void use();
    static void unuse();
    u32 get_program_id() const { return m_Id; }

private:
    u32 create_shader(const char *filepath, u32 type);
    u32 m_Id;
};