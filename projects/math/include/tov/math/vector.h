#ifndef TOV_MATH_VECTOR_H
#define TOV_MATH_VECTOR_H

#include "math_core.h"

#ifdef TOV_DEBUG
#	include <ostream>
#endif

#include <cstring>
#include <iostream>

#include "vector_component.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(math)

	template<class T, size_t Size, SIMD::Type SIMD_T>
	class VectorT
		: public VectorComponent<T, Size, SIMD_T>
	{
	public:
		using VectorComponent<T, Size, SIMD_T>::VectorComponent;

		VectorT(T f = (T)0)
		{
			std::fill(this->mArr.begin(), this->mArr.end(), f);
		}

		VectorT(const VectorT& vector)
		{
			memcpy(this->mArr.data(), vector.mArr.data(), Size * sizeof(T));
		}

		VectorT(const std::array<T, Size>& data)
		{
			this->mArr = data;
		}

		inline VectorT& operator = (const VectorT& vector)
		{
			memcpy(this->mArr.data(), vector.mArr.data(), Size * sizeof(T));
			return *this;
		}

		inline T operator [] (const size_t i) const
		{
			assert(i < Size);
			return *(&mArr[0] + i);
		}

		inline T& operator [] (const size_t i)
		{
			assert(i < Size);
			return *(&mArr[0] + i);
		}

		inline VectorT operator + () const
		{
			return *this;
		}

		inline VectorT operator - () const
		{
			VectorT v = *this;
			v.mMemory *= -1.0f;
			return v;
		}

		inline VectorT operator + (const VectorT& vector) const
		{
			VectorT v = *this;
			v.mMemory += vector.mMemory;
			return v;
		}

		inline VectorT& operator += (const VectorT& vector)
		{
			mMemory += vector.mMemory;
			return *this;
		}

		inline VectorT operator - (const VectorT& vector) const
		{
			VectorT v = *this;
			v.mMemory -= vector.mMemory;
			return v;
		}

		inline VectorT& operator -= (const VectorT& vector)
		{
			mMemory -= vector.mMemory;
			return *this;
		}

		inline VectorT operator * (T scalar) const
		{
			VectorT v = *this;
			v.mMemory *= scalar;
			return v;
		}

		inline VectorT& operator *= (T scalar)
		{
			mMemory *= scalar;
			return *this;
		}

		inline VectorT operator / (T scalar) const
		{
			VectorT v = *this;
			v.mMemory /= scalar;
			return v;
		}

		inline VectorT& operator /= (T scalar)
		{
			mMemory /= scalar;
			return *this;
		}

		inline bool operator == (const VectorT& vector) const
		{
			return mMemory == vector.mMemory;
		}

		inline bool operator != (const VectorT& vector) const
		{
			return mMemory != vector.mMemory;
		}

		inline T dot(const VectorT& vector) const
		{
			T dot = mMemory.dot(vector.mMemory);
			return dot;
		}

#ifdef TOV_DEBUG
		inline friend std::ostream& operator <<
			(std::ostream& o, const VectorT& vec)
		{
			o << "Vector" << Size << "( ";
			for (size_t i = 0; i < Size; ++i)
			{
				o << vec[i] << " ";
			}
			o << ")";
			return o;
		}
#endif
	};

	template<class T, size_t Size, SIMD::Type SIMD_T>
	class VectorTN
		: public VectorT<T, Size, SIMD_T>
	{
	public:
		template <class... U>
		VectorTN(T x, U&&... args)
			: VectorT<T, Size, SIMD_T>(x, std::forward<U>(args)...) {}

		VectorTN(const VectorT<T, Size, SIMD_T> v)
			: VectorT<T, Size, SIMD_T>(v) {}
	};

	template<size_t Size, SIMD::Type SIMD_T = SIMD::_NONE>
	using Vector = VectorTN<float, Size, SIMD_T>;

	template<class T, SIMD::Type SIMD_T>
	class VectorT2
		: public VectorTN<T, 2, SIMD_T>
	{
	public:
		VectorT2(T x, T y)
			: VectorTN<T, 2, SIMD_T>(x, y) {}

		VectorT2(const VectorT<T, 2, SIMD_T>& v)
			: VectorTN<T, 2, SIMD_T>(v) {}
	};

	using Vector2 = VectorT2<float, SIMD::_NONE>;

	template<class T, SIMD::Type SIMD_T>
	class VectorT3
		: public VectorTN<T, 3, SIMD_T>
	{
	public:
		VectorT3(T x, T y, T z)
			: VectorTN<T, 3, SIMD_T>(x, y, z) {}

		VectorT3(const VectorT<T, 3, SIMD_T>& v)
			: VectorTN<T, 3, SIMD_T>(v) {}

		inline VectorT3 cross(const VectorT3& vector) const
		{
			VectorT3 v = *this;
			v.mMemory.crossAssign(vector.mMemory);
			return v;
		}

		inline VectorT3& crossAssign(const VectorT3& vector)
		{
			mMemory.crossAssign(vector.mMemory);
			return *this;
		}
	};

	using Vector3 = VectorT3<float, SIMD::_128F>;

	template<class T, SIMD::Type SIMD_T>
	class VectorT4
		: public VectorTN<T, 4, SIMD_T>
	{
	public:
		VectorT4(T x, T y, T z, T w)
			: VectorTN<T, 4, SIMD_T>(x, y, z, w) {}

		VectorT4(const VectorT<T, 4, SIMD_T> v)
			: VectorTN<T, 4, SIMD_T>(v) {}
	};

	using Vector4 = VectorT4<float, SIMD::_128F>;

	TOV_NAMESPACE_END // math
}

#endif
