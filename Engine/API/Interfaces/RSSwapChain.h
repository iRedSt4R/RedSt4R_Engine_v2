#pragma once
#include "../../RSIncludeVulkan.h"
#include "../../Core/Window/Window.h"
#include "RSDevice.h"

enum class EBufferingType
{
	Double, Triple
};

namespace RedSt4R
{
	namespace API
	{
		class RSSwapChain
		{
		public:
			static RSSwapChain* CreateSwapChain(RSDevice* pDevice, EBufferingType bufferingType, Window* pWindow);
		};
	}
}