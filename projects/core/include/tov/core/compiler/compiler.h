#ifndef TOV_CORE_COMPILER_H
#define	TOV_CORE_COMPILER_H

// Compiler enumeration
#define TOV_COMPILER_MSVC		1
#define TOV_COMPILER_CLANG		2
#define TOV_COMPILER_GCC		3

#if 0
#
#elif defined(__GNUC__)
#	define TOV_COMPILER			TOV_COMPILER_GCC
#	define TOV_COMPILER_VERSION	__GNUC__
#elif defined(__clang__)
#	define TOV_COMPILER			TOV_COMPILER_CLANG
#	define TOV_COMPILER_VERSION	__clang_major__
#elif defined(_MSC_VER)
#	define TOV_COMPILER			TOV_COMPILER_MSVC
#	define TOV_COMPILER_VERSION _MSC_VER
#endif

#if defined(__EMSCRIPTEN__)
#	define TOV_EMSCRIPTEN
#endif

#endif
