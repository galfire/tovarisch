#ifndef TOV_MEMORY_MEMSIZE_H
#define TOV_MEMORY_MEMSIZE_H

struct memsize_t
{
	const inline size_t bytes() const { return b; }
	const inline float kilobytes() const { return bytes() / 1024.f; }
	const inline float megabytes() const { return kilobytes() / 1024.f; }
	const inline float gigabytes() const { return megabytes() / 1024.f; }

	constexpr operator size_t() const { return b; }
	
	size_t b = 0;
};

constexpr memsize_t operator * (unsigned long long v, const memsize_t& sz)
{
	return { static_cast<size_t>(v) * sz.b };
}

constexpr memsize_t operator "" _b(unsigned long long v)
{
	return { static_cast<size_t>(v) };
}

constexpr memsize_t operator "" _kb(unsigned long long v)
{
	return { v * 1024_b };
}

constexpr memsize_t operator "" _mb(unsigned long long v)
{
	return { v * 1024_kb };
}

constexpr memsize_t operator "" _gb(unsigned long long v)
{
	return { v * 1024_mb };
}

#endif