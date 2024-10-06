#pragma once
#include "types.h"

struct BufferLayout
{

};

class VertexBuffer
{
public:
    VertexBuffer(float *vertices, size_t size);
    ~VertexBuffer();

    void set_layout();

    void bind() const;
    static void unbind();
private:
    u32 m_Id;
};