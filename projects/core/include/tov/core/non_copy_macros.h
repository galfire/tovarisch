#ifndef TOV_CORE_NON_COPY_MACROS_H
#define TOV_CORE_NON_COPY_MACROS_H

// TOV_DELETE_COPY_CTOR deletes the copy constructor
#define TOV_DELETE_COPY_CTOR(CLASS) \
	CLASS(const CLASS&) = delete; \

// TOV_DELETE_COPY_ASSIGN deletes the copy assignment
#define TOV_DELETE_COPY_ASSIGN(CLASS) \
	CLASS& operator=(const CLASS&) = delete; \

#define TOV_NON_COPYABLE(CLASS) \
	TOV_DELETE_COPY_CTOR(CLASS) \
	TOV_DELETE_COPY_ASSIGN(CLASS)

#endif