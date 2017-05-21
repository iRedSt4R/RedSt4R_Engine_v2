#pragma once

#include "../../API/RSIncludeOpenGL.h"
#include "../../Config/RenderingConfig.h"

namespace RedSt4R
{
	class Window
	{
	private:
		int m_WindowWidth, m_WindowHeight;
		char* m_WindowName;

		static GLFWwindow* m_Window;


	public:
		Window(float windowWidth, float windowHeight, char* windowName, bool bFullScreen = false);
		~Window();

		bool ShouldClose();
		void Clear();
		void Update();
		void Close();

		__inline static GLFWwindow* GetGLFWWindow() { return m_Window; }

	};
}