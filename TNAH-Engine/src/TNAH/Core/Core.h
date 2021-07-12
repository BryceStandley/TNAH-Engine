#pragma once

#ifdef TNAH_PLATFORM_WINDOWS
	#ifdef TNAH_BUILD_DLL
		#define TNAH_API _declspec(dllexport)
	#else
		#define TNAH_API _declspec(dllimport)
	#endif
#else
	#error TNAH-Engine only supports Windows x64!
#endif
	
#ifdef TNAH_ENABLE_ASSERTS
	#define TNAH_ASSERT(x, ...) { if(!(x)) { TNAH_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define TNAH_CORE_ASSERT(x, ...) { if(!(x)) { TNAH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define TNAH_ASSERT(x, ...)
	#define TNAH_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)