#include "graphics_api.h"

namespace Duski {
    
    std::unique_ptr<GraphicsAPI> create_api(API api) {
        switch (api) {
        case API::OPENGL:
            return std::make_unique<OpenGLAPI>();
        case API::NONE:
        default:
            std::cerr << "No valid graphics API selected." << std::endl;
            return nullptr;
        }
    }

    void CheckOpenGLError(const char* stmt) {
        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            std::cerr << "OpenGL error " << err << " at " << stmt << std::endl;
        }
    }

    GLuint OpenGLAPI::compile_shader(GLenum type, const char* source) {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "Shader Compilation Error:\n" << infoLog << std::endl;
        }
        return shader;
    }

    void OpenGLAPI::init_context(Duski::Window& window) {
        PIXELFORMATDESCRIPTOR pfd = {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA,
            32,
            0, 0, 0, 0, 0, 0,
            0, 0,
            0, 0, 0, 0, 0,
            24,
            8,
            0,
            PFD_MAIN_PLANE,
            0, 0, 0, 0
        };

        int pixelFormat = ChoosePixelFormat(window.GetHDC(), &pfd);
        SetPixelFormat(window.GetHDC(), pixelFormat, &pfd);
        window.GetHGLRC() = wglCreateContext(window.GetHDC());
        wglMakeCurrent(window.GetHDC(), window.GetHGLRC());

        if (!gladLoadGL()) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            exit(-1);
        }
    }

    void OpenGLAPI::init_resources(
        const char* vertex_shader_source,
        const char* fragment_shader_source
    ) {
        GLuint vertexShader = compile_shader(GL_VERTEX_SHADER, vertex_shader_source);
        GLuint fragmentShader = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);

        m_ShaderProgram = glCreateProgram();
        glAttachShader(m_ShaderProgram, vertexShader);
        glAttachShader(m_ShaderProgram, fragmentShader);
        glLinkProgram(m_ShaderProgram);

        int success;
        glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(m_ShaderProgram, 512, nullptr, infoLog);
            std::cerr << "Program Linking Error:\n" << infoLog << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        float vertices[] = {
            -1.0f, -1.0f,  0.0f, 0.0f,
             1.0f, -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f,  1.0f, 1.0f,
            -1.0f,  1.0f,  0.0f, 1.0f
        };
        unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

        GLuint VBO, EBO;
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    void OpenGLAPI::render(Duski::Window& window, uint32_t *framebuffer) {
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, window.GetWidth(), window.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, framebuffer);

        glUseProgram(m_ShaderProgram);
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        SwapBuffers(window.GetHDC());
    }

    void OpenGLAPI::shutdown() {
        if (m_ShaderProgram != 0) {
            glDeleteProgram(m_ShaderProgram);
            m_ShaderProgram = 0;
        }

        if (m_VAO != 0) {
            glDeleteVertexArrays(1, &m_VAO);
            m_VAO = 0;
        }

        if (m_TextureID != 0) {
            glDeleteTextures(1, &m_TextureID);
            m_TextureID = 0;
        }

        GLuint buffers[2] = { m_VBO, m_VAO };
        glDeleteBuffers(2, buffers);
        m_VBO = 0;
        m_VAO = 0;
    }

}