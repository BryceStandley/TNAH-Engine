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
	