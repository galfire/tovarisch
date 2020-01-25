#ifndef TOV_CORE_PLATFORM_H
#define TOV_CORE_PLATFORM_H

#define TOV_PLATFORM_WIN	1
#define TOV_PLATFORM_UNIX	2

#define TOV_ARCHITECTURE_32	1
#define TOV_ARCHITECTURE_64	2

#if defined(_WIN64)
#	define TOV_PLATFORM		TOV_PLATFORM_WIN
#	define TOV_ARCHITECTURE	TOV_ARCHITECTURE_64
#elif defined(_WIN32)
#	define TOV_PLATFORM		TOV_PLATFORM_WIN
#	define TOV_ARCHITECTURE	TOV_ARCHITECTURE_32
#elif defined(unix) || defined(__unix__) || defined(__unix)
#	define TOV_PLATFORM		TOV_PLATFORM_UNIX
#	if __x86_64__ || __ppc64__
#		define TOV_ARCHITECTURE TOV_ARCHITECTURE_64
#	else
#		define TOV_ARCHITECTURE TOV_ARCHITECTURE_32
#	endif
#endif

#endif