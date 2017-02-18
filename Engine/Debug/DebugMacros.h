#pragma once

#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <vulkan\vulkan.h>

#ifdef  _DEBUG 
#define RS_ERROR(x) { HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hOut, 1|5|FOREGROUND_INTENSITY); std::cout<<"|LINE: "<<__LINE__<<"| "; SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_INTENSITY); std::cout<<x<<std::endl; }
#define RS_WARNING(x) { HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hOut, 1|5|FOREGROUND_INTENSITY); std::cout<<"|LINE: "<<__LINE__<<"| "; SetConsoleTextAttribute(hOut, 14|FOREGROUND_INTENSITY); std::cout<<x<<std::endl; }
#define RS_LOG(x) { HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hOut, 1|5|FOREGROUND_INTENSITY); std::cout<<"|LINE: "<<__LINE__<<"| "; SetConsoleTextAttribute(hOut, 1|7|FOREGROUND_INTENSITY); std::cout<<x<<std::endl; }
#else
#define RS_ERROR(x) ;
#define RS_WARNING(x) ;
#define RS_LOG(x)  ;
#endif

#if defined(_MSC_VER) 
	#define FORCE_INLINE __forceinline	
#else
	#if defined (__GNUC__)
		#define FORCE_INLINE __attribute__((always_inline))
	#else
		#define FORCE_INLINE  
	#endif
#endif

#define RS_API __declspec(dllexport)

/*
void CheckVk(VkResult a_Result, char* a_FailedMessage)
{
	if (a_Result != VK_SUCCESS)
	{
		RS_ERROR(a_FailedMessage)
	}
}

void CheckVk(VkResult a_Result, char* a_FailedMessage, char* a_SuccessMessage)
{
	if (a_Result != VK_SUCCESS)
	{
		RS_ERROR(a_FailedMessage)
	}
	else
	{
		RS_LOG(a_SuccessMessage)
	}
}
*/