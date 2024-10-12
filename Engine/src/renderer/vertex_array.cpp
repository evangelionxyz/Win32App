#include "vertex_array.hpp"
#include <glad/glad.h>

VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &m_Id);
    glBindVertexArray(m_Id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_Id);
}

void VertexArray::add_vertex_buffer(const VertexBuffer &vertex_buffer)
{
    vertex_buffer.bind();
}

void VertexArray::bind()
{
    glBindVertexArray(m_Id);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}
