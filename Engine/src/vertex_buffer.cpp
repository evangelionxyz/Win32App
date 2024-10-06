#include "vertex_buffer.hpp"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(float *vertices, size_t size)
{
    glCreateBuffers(1, &m_Id);
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float), vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_Id);
}

void VertexBuffer::set_layout()
{

}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Id);
}

void VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
