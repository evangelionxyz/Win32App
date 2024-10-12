#include "renderer/shader.hpp"
#include "core/window.hpp"

#include <glad/glad.h>
#include <memory>

#include <stdio.h>
#include <iostream>

#include "audio/audio_engine.hpp"
#include "audio/sound.hpp"
#include "core/console_manager.hpp"

#include "core/event.hpp"
#include "core/key_event.hpp"
#include "core/app_event.hpp"

#include <thread>

void create_console()
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    freopen("CONIN$", "r", stdin);
}

class Application
{
public:
    Application(HINSTANCE hInstance, int nCmdShow)
    {
        m_Window = CreateScope<Window>(hInstance, nCmdShow, "OpenGL", 800, 600);
        m_Window->set_event_callback(BIND_EVENT_FN(on_event));

        m_Shader = CreateScope<Shader>("data/shaders/default.vert", "data/shaders/default.frag");

        // init audio
        m_AudioEngine = CreateScope<AudioEngine>();
        Sound sound("data/audio/loading_screen.wav");

        m_AudioEngine->add_sound(&sound);
        sound.set_volume(100.0f);
        sound.play();

        float vertices[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.0f, 0.5f
        };
        
        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glCreateBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, static_cast<const void *>(0));
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

    void run()
    {
        std::thread t1([&]()
            {
                while (m_Window->is_looping())
                {
                    for (auto &m : m_Console.get_messages())
                        std::cout << m.get_formatted_message() << '\n';
                    m_Console.clear_messages();
                }
            });
        t1.detach();

        while (m_Window->is_looping())
        {
            if (!m_Window->poll_events())
            {
                m_AudioEngine->update();

                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                m_Shader->use();
                glBindVertexArray(vao);
                glDrawArrays(GL_TRIANGLES, 0, 3);
                glBindVertexArray(0);

                m_Window->swap_buffers();
            }
        }
    }

    bool on_resize(WindowResizeEvent &e)
    {
        glViewport(0, 0, e.get_width(), e.get_height());
        std::cout << e.to_string();

        return false;
    }

    void on_event(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(on_resize));
    }

private:
    Scope<Shader> m_Shader;
    Scope<Window> m_Window;
    Scope<AudioEngine> m_AudioEngine;

    ConsoleManager m_Console;

    u32 vao, vbo;
};


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    create_console();
    Application app(hInstance, nCmdShow);
    app.run();
    FreeConsole();

    return 0;
}