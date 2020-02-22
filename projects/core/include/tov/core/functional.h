#ifndef TOV_CORE_FUNCTIONAL_H
#define TOV_CORE_FUNCTIONAL_H

namespace tov
{
	template<class T>
	struct bitwise_and
	{
		constexpr T operator()(T x, T y) const
		{
			return x & y;
		}
	};

	template<class T>
	struct bitwise_or
	{
		constexpr T operator()(T x, T y) const
		{
			return x | y;
		}
	};
}

#endif