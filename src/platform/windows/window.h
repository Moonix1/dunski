#pragma once

#include <Windows.h>

namespace Duski {

	class Window {
	public:
		Window(int width, int height);
	public:
		HDC &GetHDC() { return m_HDC; };
		HGLRC &GetHGLRC() { return m_HGLRC; };

		int &GetWidth() { return m_Width; };
		int &GetHeight() { return m_Height; };
	private:
		HDC m_HDC;
		HGLRC m_HGLRC;

		int m_Width, m_Height;
	};

}