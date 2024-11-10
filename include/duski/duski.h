#pragma once

#include "api/graphics_api.h"

inline const char* vertex_shader_source = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
out vec2 TexCoord;
void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
    TexCoord = aTexCoord;
}
)";

inline const char* fragment_shader_source = R"(
#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D screenTexture;
void main() {
    FragColor = texture(screenTexture, TexCoord);
}
)";

namespace Duski {

	class DuskiWindow {
	public:
		DuskiWindow(int width, int height)
			: m_Window(Window::Window(width, height)) {
		}
	public:
		Window& GetCoreWindow() { return m_Window; }
	private:
		Window m_Window;
	};

	class DuskiAPI {
	public:
		DuskiAPI(API api, DuskiWindow& window)
			: m_API(create_api(api)), m_Window(window) {
			m_API->init_context(m_Window.GetCoreWindow());
			m_API->init_resources(vertex_shader_source, fragment_shader_source);

				m_Framebuffer = new uint32_t[m_Window.GetCoreWindow().GetWidth() * m_Window.GetCoreWindow().GetHeight()];
			std::fill(m_Framebuffer, m_Framebuffer
				+ m_Window.GetCoreWindow().GetWidth() * m_Window.GetCoreWindow().GetHeight(), 0x00000000);
		}

		void render() { m_API->render(m_Window.GetCoreWindow(), m_Framebuffer); }
		void shutdown() { m_API->shutdown(); delete[] m_Framebuffer; }
	public:
		void set_background_color(uint32_t color);

		void fill_rect(
			size_t y_pos, size_t x_pos,
			size_t width, size_t height,
			uint32_t color
		);
		void fill_circle(
			size_t center_x, size_t center_y,
			size_t radius,
			uint32_t color
		);
	private:
		std::unique_ptr<GraphicsAPI> m_API;
		
		DuskiWindow &m_Window;
		uint32_t *m_Framebuffer;
	};

}