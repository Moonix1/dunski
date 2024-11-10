#pragma once

#if defined(_WIN64) || defined(_WIN32)
#include "../platform/windows/window.h"
#else
#error "Duski currently only supports Windows!"
#endif

#include <stdint.h>
#include <memory>
#include <iostream>
#include <glad/glad.h>

namespace Duski {

    const int WINDOW_WIDTH = 0;
    const int WINDOW_HEIGHT = 0;

    class GraphicsAPI;

    enum class API {
        OPENGL,
        NONE
    };

    class GraphicsAPI {
    public:
        GraphicsAPI(API api) : m_API(api) {}

        virtual ~GraphicsAPI() = default;

        virtual void init_context(Duski::Window& window) = 0;
        virtual void init_resources(const char* vertex_shader_source, const char* fragment_shader_source) = 0;
        virtual void render(Duski::Window& window, uint32_t* framebuffer) = 0;
        virtual void shutdown() = 0;

    protected:
        API m_API;
    };

    class OpenGLAPI : public GraphicsAPI {
    public:
        OpenGLAPI() : GraphicsAPI(API::OPENGL) {}

        GLuint compile_shader(GLenum type, const char* source);

        void init_context(Duski::Window& window) override;
        void init_resources(const char* vertex_shader_source, const char* fragment_shader_source) override;
        void render(Duski::Window& window, uint32_t* framebuffer) override;
        void shutdown() override;

    private:
        GLuint m_TextureID, m_ShaderProgram;
        GLuint m_VAO, m_VBO;
    };
    
    std::unique_ptr<GraphicsAPI> create_api(API api);
}
