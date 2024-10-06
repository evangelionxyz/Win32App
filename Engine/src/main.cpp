#include "shader.hpp"
#include "window.hpp"

#include <glad/glad.h>
#include <memory>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Window window(hInstance, nCmdShow, "OpenGL", 800, 600);
    Scope<Shader> shader = CreateScope<Shader>("data/shaders/default.vert", "data/shaders/default.frag");

    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.0f,  0.5f
    };

    u32 vao, vbo;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, static_cast<const void *>(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    while (window.is_looping())
    {
        if (!window.poll_events())
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader->use();
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);

            window.swap_buffers();
        }
    }

    return 0;
}