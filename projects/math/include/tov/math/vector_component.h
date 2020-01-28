#ifndef TOV_MATH_VECTOR_COMPONENT_H
#define TOV_MATH_VECTOR_COMPONENT_H

#include <tov/core.h>

#include <array>
#include <immintrin.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(math)

	template<class T, size_t Size, bool SIMD>
	class VectorMemory
	{};

	template<class T, size_t Size>
	class VectorMemory<T, Size, false>
	{
	public:
		inline VectorMemory& operator += (const VectorMemory& vector)
		{
			for (int i = 0; i < Size; i++)
			{
				_memory[i] += vector._memory[i];
			}
			return *this;
		}

		inline VectorMemory& operator -= (const VectorMemory& vector)
		{
			for (int i = 0; i < Size; i++)
			{
				_memory[i] -= vector._memory[i];
			}
			return *this;
		}

	protected:
		std::array<T, Size> _memory;
	};

	template<class T, size_t Size>
	class VectorMemory<T, Size, true>
	{
	public:
		inline VectorMemory& operator += (const VectorMemory& vector)
		{
			_memory = _mm_add_ps(_memory, vector._memory);
			return *this;
		}

		inline VectorMemory& operator -= (const VectorMemory& vector)
		{
			_memory = _mm_sub_ps(_memory, vector._memory);
			return *this;
		}

	protected:
		__m128 _memory;
	};

	template<class T, bool SIMD>
	class VectorMemory3
	{};

	template<class T>
	class VectorMemory3<T, false>
		: public VectorMemory<T, 3, false>
	{
	public:
		inline VectorMemory3 crossProduct(const VectorMemory3& vector) const
		{
			T vx, vy, vz;
			vx = _memory[0];
			vy = _memory[1];
			vz = _memory[2];

			T vx2, vy2, vz2;
			vx2 = vector._memory[0];
			vy2 = vector._memory[1];
			vz2 = vector._memory[2];

			VectorMemory3 v;
			v._memory[0] = vy * vz2 - vz * vy2;
			v._memory[1] = vz * vx2 - vx * vz2;
			v._memory[2] = vx * vy2 - vy * vx2;

			return v;
		}
	};

	template<class T>
	class VectorMemory3<T, true>
		: public VectorMemory<T, 3, true>
	{
	public:
		inline VectorMemory3 crossProduct(const VectorMemory3& vector) const
		{
			__m128 a = _memory;
			__m128 b = vector._memory;

			__m128 _aa = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
			__m128 _ab = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 1, 0, 2));
			__m128 _a_b = _mm_mul_ps(_aa, _ab);

			__m128 _bb = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1));
			__m128 _ba = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 1, 0, 2));
			__m128 _b_a = _mm_mul_ps(_bb, _ba);

			VectorMemory3 v;
			v._memory = _mm_sub_ps(_a_b, _b_a);
			return v;
		}
	};

	template<class T, size_t Size, bool SIMD>
	struct VectorComponent
	{
	public:
		union
		{
			std::array<T, Size> mArr;
			VectorMemory<T, Size, SIMD> mMemory;
		};

		VectorComponent() = default;

		template<class... U>
		VectorComponent(T x, U... args) : mArr{ x, std::forward<U>(args)... } {}
	};

	template<class T, bool SIMD>
	struct VectorComponent<T, 2, SIMD>
	{
	public:
		union
		{
			struct
			{
				T x;
				T y;
			};
			std::array<T, 2> mArr;
			VectorMemory<T, 2, SIMD> mMemory;
		};

		VectorComponent() = default;
		VectorComponent(T x, T y) : x(x), y(y) {}
	};

	template<class T, bool SIMD>
	struct VectorComponent<T, 3, SIMD>
	{
	public:
		union
		{
			struct
			{
				T x;
				T y;
				T z;
			};
			std::array<T, 3> mArr;
			VectorMemory3<T, SIMD> mMemory;
		};

		VectorComponent() = default;
		VectorComponent(T x, T y, T z) : x(x), y(y), z(z) {}
	};

	template<class T, bool SIMD>
	struct VectorComponent<T, 4, SIMD>
	{
	public:
		union
		{
			struct
			{
				T x;
				T y;
				T z;
				T w;
			};
			std::array<T, 4> mArr;
			VectorMemory<T, 4, SIMD> mMemory;
		};

		VectorComponent() = default;
		VectorComponent(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	};

	TOV_NAMESPACE_END // math
}

#endif
