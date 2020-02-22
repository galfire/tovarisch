#ifndef TOV_RENDERING_BUFFERS_LOCK_SETTINGS
#define TOV_RENDERING_BUFFERS_LOCK_SETTINGS

#include <tov/rendering/rendering_core.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	// Lock settings
	enum class LockSettings
	{
		// Populate the buffer with the committed data from the external location
		READ = 1 << 0,
		NO_READ = 0 << 0,

		// Return a blank buffer for writing that will be committed to the external location
		WRITE = 1 << 1,
		NO_WRITE = 0 << 1,

		// All data committed to the external location will be discarded on lock
		DISCARD = 1 << 2,
	};

	constexpr LockSettings operator & (LockSettings lhs, LockSettings rhs)
	{
		return static_cast<LockSettings>(
			static_cast<std::underlying_type<LockSettings>::type>(lhs )&
			static_cast<std::underlying_type<LockSettings>::type>(rhs)
		);
	}

	constexpr LockSettings& operator &= (LockSettings& lhs, LockSettings rhs)
	{
		lhs = static_cast<LockSettings>(
			static_cast<std::underlying_type<LockSettings>::type>(lhs) &
			static_cast<std::underlying_type<LockSettings>::type>(rhs)
		);
		return lhs;
	}

	constexpr LockSettings operator | (LockSettings lhs, LockSettings rhs)
	{
		return static_cast<LockSettings>(
			static_cast<std::underlying_type<LockSettings>::type>(lhs) |
			static_cast<std::underlying_type<LockSettings>::type>(rhs)
		);
	}

	constexpr LockSettings& operator |= (LockSettings& lhs, LockSettings rhs)
	{
		lhs = static_cast<LockSettings>(
			static_cast<std::underlying_type<LockSettings>::type>(lhs) |
			static_cast<std::underlying_type<LockSettings>::type>(rhs)
		);
		return lhs;
	}

	constexpr bool operator == (LockSettings lhs, std::underlying_type<LockSettings>::type rhs)
	{
		return static_cast<std::underlying_type<LockSettings>::type>(lhs) == rhs;
	}

	constexpr bool operator != (LockSettings lhs, std::underlying_type<LockSettings>::type rhs)
	{
		return !(lhs == rhs);
	}

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_BUFFERS_LOCK_SETTINGS
