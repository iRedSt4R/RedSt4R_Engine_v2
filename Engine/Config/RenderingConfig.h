#pragma once

#define USE_OPENGL 0
#define USE_D3D11 0
#define USE_VULKAN 1
#define USE_D3D12 0

namespace RedSt4R
{
	class EngineConfig
	{
	public:
		static int s_Window_Width;
		static int s_Window_Height;

		static int s_SwapChainImages;

	public:
		__inline static void SetWindowSize(int width, int height) {s_Window_Height = height; s_Window_Width = width;}
		__inline static void SetWindowWidth(int width) { s_Window_Width = width;}
		__inline static void SetWindowHeight(int height) { s_Window_Height = height; }
		__inline static void SetSwapChainImageCout(int numberOfImages) { s_SwapChainImages = numberOfImages; }

		__inline static int GetWindowWidth() { return s_Window_Width; }
		__inline static int GetWindowHeight() { return s_Window_Height; }
		__inline static int GetSwapChainImageCout() { return s_SwapChainImages; }
	};
}