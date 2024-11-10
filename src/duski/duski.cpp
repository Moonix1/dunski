#include "duski/duski.h"

namespace Duski {

	void DuskiAPI::set_background_color(uint32_t color) {
		std::fill(m_Framebuffer, m_Framebuffer
			+ m_Window.GetCoreWindow().GetWidth() * m_Window.GetCoreWindow().GetHeight(), color);
	}

	void DuskiAPI::fill_rect(
		size_t y_pos, size_t x_pos,
		size_t width, size_t height,
		uint32_t color
	) {
		for (size_t dx = 0; dx < width; dx++) {
			int x = x_pos + dx;
			if (0 <= x && x < m_Window.GetCoreWindow().GetWidth()) {
			for (size_t dy = 0; dy < height; dy++) {
				int y = y_pos + dy;
				if (0 <= y && y < m_Window.GetCoreWindow().GetHeight()) {
						m_Framebuffer[y * m_Window.GetCoreWindow().GetWidth() + x] = color;
					}
				}
			}
		}
	}

}