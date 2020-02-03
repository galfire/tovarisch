#ifndef TOV_RENDERING_GLES_GL_IMPL_H
#define TOV_RENDERING_GLES_GL_IMPL_H

#include <tov/core/platform/platform.h>

#if TOV_PLATFORM == TOV_PLATFORM_WIN
#	include <Windows.h>
#endif

#ifdef TOV_GLES
#	include <GLES3/gl31.h>
#	include <GLES2/gl2ext.h>
#else ifdef TOV_GL
#	include <gl/GL.h>
#	include <gl/GLU.h>
#endif


//#include <GLES3/gl31.h>
//#include <GLES2/gl2ext.h>

#endif
