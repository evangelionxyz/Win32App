#pragma once

#include "vertex_buffer.hpp"
#include "core/types.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void add_vertex_buffer(const VertexBuffer &vertex_buffer);

    void bind();
    static void unbind();
private:
    u32 m_Id;
};