#ifndef TOV_MATH_VECTOR_COMPONENT_H
#define TOV_MATH_VECTOR_COMPONENT_H

#include "math_core.h"

#include <array>
#include <immintrin.h>	

namespace tov
{
	TOV_NAMESPACE_BEGIN(math)

	struct SIMD
	{
		enum Type
		{
			_NONE,
			_128F
		};
	};

	template<class T, size_t Size, SIMD::Type SIMD_T>
	class VectorMemory
	{};

	template<class T, size_t Size>
	class VectorMemory<T, Size, SIMD::_NONE>
	{
	public:
		template<class... U>
		VectorMemory(U&&... args)
			: _memory{ std::forward<U>(args)... }
		{}

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

		inline VectorMemory& operator *= (T scalar)
		{
			for (int i = 0; i < Size; i++)
			{
				_memory[i] *= scalar;
			}
			return *this;
		}

		inline VectorMemory& operator /= (T scalar)
		{
			for (int i = 0; i < Size; i++)
			{
				_memory[i] /= scalar;
			}
			return *this;
		}

		inline bool operator == (const VectorMemory& vector) const
		{
			for (int i = 0; i < Size; i++)
			{
				if (_memory[i] != vector._memory[i])
					return false;
			}
			return true;
		}

		inline bool operator != (const VectorMemory& vector) const
		{
			for (int i = 0; i < Size; i++)
			{
				if (_memory[i] != vector._memory[i])
					return true;
			}
			return false;
		}


		inline T dot(const VectorMemory& vector) const
		{
			T sum = 0;
			for (int i = 0; i < Size; i++)
			{
				sum += _memory[i] * vector._memory[i];
			}
			return sum;
		}

	protected:
		std::array<T, Size> _memory;
	};

	template<size_t Size>
	class VectorMemory<float, Size, SIMD::_128F>
	{
	public:
		VectorMemory(float A = 0.0f, float B = 0.0f, float C = 0.0f, float D = 0.0f)
			: _memory(_mm_set_ps(D, C, B, A))
		{}

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

		inline VectorMemory& operator *= (float scalar)
		{
			__m128 scalars = _mm_set1_ps(scalar);
			_memory = _mm_mul_ps(_memory, scalars);
			return *this;
		}

		inline VectorMemory& operator /= (float scalar)
		{
			__m128 scalars = _mm_set1_ps(scalar);
			_memory = _mm_div_ps(_memory, scalars);
			return *this;
		}

		inline bool operator == (const VectorMemory& vector) const
		{
			__m128 cmp = _mm_cmpeq_ps(_memory, vector._memory);
			uint16_t mask = _mm_movemask_ps(cmp);
			return mask == 0xF;
		}

		inline bool operator != (const VectorMemory& vector) const
		{
			__m128 cmp = _mm_cmpeq_ps(_memory, vector._memory);
			uint16_t mask = _mm_movemask_ps(cmp);
			return mask != 0xF;
		}

		inline float dot(const VectorMemory& vector) const
		{
			__m128 mul = _mm_mul_ps(_memory, vector._memory);
			__m128 hadd = _mm_hadd_ps(mul, mul);
			       hadd = _mm_hadd_ps(hadd, hadd);
			float sum = reinterpret_cast<float*>(&hadd)[0];
			return sum;
		}

	protected:
		__m128 _memory;
	};

	template<class T, SIMD::Type>
	class VectorMemory3
	{};

	template<class T>
	class VectorMemory3<T, SIMD::_NONE>
		: public VectorMemory<T, 3, SIMD::_NONE>
	{
	public:
		using VectorMemory<T, 3, SIMD::_NONE>::VectorMemory;

		inline VectorMemory3& crossAssign(const VectorMemory3& vector)
		{
			T vx = _memory[0];
			T vy = _memory[1];
			T vz = _memory[2];

			T vx2 = vector._memory[0];
			T vy2 = vector._memory[1];
			T vz2 = vector._memory[2];

			_memory[0] = vy * vz2 - vz * vy2;
			_memory[1] = vz * vx2 - vx * vz2;
			_memory[2] = vx * vy2 - vy * vx2;

			return *this;
		}
	};

	template<>
	class VectorMemory3<float, SIMD::_128F>
		: public VectorMemory<float, 3, SIMD::_128F>
	{
	public:
		using VectorMemory<float, 3, SIMD::_128F>::VectorMemory;

		inline VectorMemory3& crossAssign(const VectorMemory3& vector)
		{
			const __m128& a = _memory;
			const __m128& b = vector._memory;

			__m128 _aa = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1));
			__m128 _ab = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 1, 0, 2));
			__m128 _a_b = _mm_mul_ps(_aa, _ab);

			__m128 _bb = _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1));
			__m128 _ba = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 1, 0, 2));
			__m128 _b_a = _mm_mul_ps(_bb, _ba);

			_memory = _mm_sub_ps(_a_b, _b_a);
			
			return *this;
		}
	};

	template<class T, size_t Size, SIMD::Type SIMD_T>
	class VectorComponent
	{
	public:
		VectorComponent() : mMemory() {}

		template<class... U>
		VectorComponent(T x, U&&... args) : mMemory{ x, std::forward<U>(args)... } {}

	public:
		union
		{
			std::array<T, Size> mArr;
			VectorMemory<T, Size, SIMD_T> mMemory;
		};
	};

	template<class T, SIMD::Type SIMD_T>
	class VectorComponent<T, 2, SIMD_T>
	{
	public:
		VectorComponent() : mMemory() {}
		VectorComponent(T x, T y) : mMemory(x, y) {}

	public:
		union
		{
			struct
			{
				T x;
				T y;
			};
			std::array<T, 2> mArr;
			VectorMemory<T, 2, SIMD_T> mMemory;
		};
	};

	template<class T, SIMD::Type SIMD_T>
	class VectorComponent<T, 3, SIMD_T>
	{
	public:
		VectorComponent() : mMemory() {}
		VectorComponent(T x, T y, T z) : mMemory(x, y, z) {}

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
			VectorMemory3<T, SIMD_T> mMemory;
		};
	};

	template<class T, SIMD::Type SIMD_T>
	class VectorComponent<T, 4, SIMD_T>
	{
	public:
		VectorComponent() : mMemory() {}
		VectorComponent(T x, T y, T z, T w) : mMemory(x, y, z, w) {}

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
			VectorMemory<T, 4, SIMD_T> mMemory;
		};
	};

	TOV_NAMESPACE_END // math
}

#endif
