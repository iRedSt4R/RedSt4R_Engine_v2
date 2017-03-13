#pragma once

#include "../RSIncludeOpenGL.h"
#include "../Interfaces/RSRenderer.h"
#include "../../Config/RenderingConfig.h"

namespace RedSt4R
{
	namespace API
	{
		class OpenGLRenderer : public RSRenderer
		{
		public:
			GLFWwindow* m_Window;

		public:
			OpenGLRenderer(GLFWwindow* pWindow);
			~OpenGLRenderer();

			virtual void InitRenderer() override;
			virtual void BeginRenderer() override;
			virtual void Update() override;
			virtual void Render() override;
			virtual void EndRenderer() override;
			virtual void ShutDownRenderer() override;
		};
	}
}
