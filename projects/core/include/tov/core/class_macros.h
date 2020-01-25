#ifndef TOV_CORE_CLASS_MACROS_H
#define TOV_CORE_CLASS_MACROS_H

#include "non_copy_macros.h"
#include "movable_macros.h"

#define TOV_MOVABLE_ONLY(CLASS) \
	TOV_MOVABLE(CLASS) \
	TOV_NON_COPYABLE(CLASS)

#define TOV_MOVABLE_COPYABLE(CLASS) \
	TOV_MOVABLE(CLASS)

#endif