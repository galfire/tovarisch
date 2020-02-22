#ifndef TOV_RENDERING_BUFFERS_USAGE_SETTINGS
#define TOV_RENDERING_BUFFERS_USAGE_SETTINGS

#include <tov/rendering/rendering_core.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	enum class UsageSettings : unsigned int
	{
		STATIC = 0,
		DYNAMIC = 1
	};

	constexpr UsageSettings operator & (UsageSettings lhs, UsageSettings rhs)
	{
		return static_cast<UsageSettings>(
			static_cast<std::underlying_type<UsageSettings>::type>(lhs) &
			static_cast<std::underlying_type<UsageSettings>::type>(rhs)
		);
	}

	constexpr UsageSettings& operator &= (UsageSettings& lhs, UsageSettings rhs)
	{
		lhs = static_cast<UsageSettings>(
			static_cast<std::underlying_type<UsageSettings>::type>(lhs) &
			static_cast<std::underlying_type<UsageSettings>::type>(rhs)
		);
		return lhs;
	}

	constexpr UsageSettings operator | (UsageSettings lhs, UsageSettings rhs)
	{
		return static_cast<UsageSettings>(
			static_cast<std::underlying_type<UsageSettings>::type>(lhs) |
			static_cast<std::underlying_type<UsageSettings>::type>(rhs)
		);
	}

	constexpr UsageSettings& operator |= (UsageSettings& lhs, UsageSettings rhs)
	{
		lhs = static_cast<UsageSettings>(
			static_cast<std::underlying_type<UsageSettings>::type>(lhs) |
			static_cast<std::underlying_type<UsageSettings>::type>(rhs)
		);
		return lhs;
	}

	constexpr bool operator == (UsageSettings lhs, std::underlying_type<UsageSettings>::type rhs)
	{
		return static_cast<std::underlying_type<UsageSettings>::type>(lhs) == rhs;
	}

	constexpr bool operator != (UsageSettings lhs, std::underlying_type<UsageSettings>::type rhs)
	{
		return !(lhs == rhs);
	}

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_BUFFERS_USAGE_SETTINGS
