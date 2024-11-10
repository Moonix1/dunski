#include "duski/duski.h"

namespace Duski {

	void DuskiAPI::set_background_color(uint32_t color) {
		std::fill(m_Framebuffer, m_Framebuffer
			+ m_Window.GetCoreWindow().GetWidth() * m_Window.GetCoreWindow().GetHeight(), color);
	}

	void DuskiAPI::fill_rect(
		size_t x_pos, size_t y_pos,
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

	void DuskiAPI::fill_circle(size_t center_x, size_t center_y, size_t radius, uint32_t color) {
		size_t x_inner = center_x - radius;
		size_t y_inner = center_y - radius;
		size_t x_outer = center_x + radius;
		size_t y_outer = center_y + radius;
		for (size_t x = x_inner; x <= x_outer; x++) {
			if (0 <= x && x < m_Window.GetCoreWindow().GetWidth()) {
				for (size_t y = y_inner; y <= y_outer; y++) {
					if (0 <= y && y < m_Window.GetCoreWindow().GetWidth()) {
						size_t dx = x - center_x;
						size_t dy = y - center_y;
						if (dx * dx + dy * dy <= radius * radius) {
							m_Framebuffer[y * m_Window.GetCoreWindow().GetWidth() + x] = color;
						}
					}
				}
			}
		}
	}

}