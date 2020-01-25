#ifndef TOV_CORE_METHOD_MACROS_H
#define TOV_CORE_METHOD_MACROS_H

#include "compiler/compiler.h"

#if TOV_COMPILER == TOV_COMPILER_MSVC
#	define TOV_ABSTRACT abstract
#else
#	define TOV_ABSTRACT = 0
#endif

#endif