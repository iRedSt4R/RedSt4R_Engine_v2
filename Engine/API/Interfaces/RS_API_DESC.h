#pragma once
#include "../../RSIncludeVulkan.h"

namespace RedSt4R
{
	namespace API
	{
		struct RS_DESC_GRAPHICSPIPELINE
		{
		public:
			VkDevice device;
			VkSurfaceFormatKHR surfaceFormat;
			VkRect2D rect2D;
			VkClearValue clearValue;
			VkViewport viewport;
		};












	}
}