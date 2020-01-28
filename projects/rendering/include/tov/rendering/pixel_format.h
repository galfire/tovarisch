#ifndef TOV_RENDER_SYSTEM_PIXEL_FORMAT_H
#define TOV_RENDER_SYSTEM_PIXEL_FORMAT_H

#include <tov/core.h>

#include "definitions.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)

	class PixelFormat
	{
	public:
		PixelFormat(ushort red, ushort blue, ushort green, ushort alpha)
			: mRedBits(red)
			, mBlueBits(blue)
			, mGreenBits(green)
			, mAlphaBits(alpha)
		{}
		virtual ~PixelFormat(void) = default;

		ushort getRedBits(void) const { return mRedBits; }
		ushort getBlueBits(void) const { return mBlueBits; }
		ushort getGreenBits(void) const { return mGreenBits; }
		ushort getAlphaBits(void) const { return mAlphaBits; }
		ushort getColourDepth(void) const { return mRedBits + mBlueBits + mGreenBits + mAlphaBits; }

	protected:
		ushort mRedBits;
		ushort mBlueBits;
		ushort mGreenBits;
		ushort mAlphaBits;
	};

	TOV_NAMESPACE_END // rendering
}

#endif