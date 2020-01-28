#ifndef TOV_MATH_VECTOR_H
#define TOV_MATH_VECTOR_H

#include <tov/core.h>

#include <ostream>
#include <cstring>
#include <iostream>

#include "vector_component.h"

namespace tov
{
	TOV_NAMESPACE_BEGIN(math)

	template<class T, size_t Size, bool SIMD>
	class VectorT
		: public VectorComponent<T, Size, SIMD>
	{
	public:
		using VectorComponent<T, Size, SIMD>::VectorComponent;

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
	};

	template<class T, bool SIMD>
	class Vector2T
		: public VectorT<T, 2, SIMD>
	{
	public:
		Vector2T(T x, T y)
			: VectorT<T, 2, SIMD>(x, y) {}

		Vector2T(const VectorT<T, 2, SIMD>& v)
			: VectorT<T, 2, SIMD>(v) {}
	};

	using Vector2 = Vector2T<float, false>;

	template<class T, bool SIMD>
	class Vector3T
		: public VectorT<T, 3, SIMD>
	{
	public:
		Vector3T(T x, T y, T z)
			: VectorT<T, 3, SIMD>(x, y, z) {}

		Vector3T(const VectorT<T, 3, SIMD>& v)
			: VectorT<T, 3, SIMD>(v) {}

		inline Vector3T crossProduct(const Vector3T& vector) const
		{
			Vector3T v = *this;
			v.mMemory = v.mMemory.crossProduct(vector.mMemory);
			return v;
		}

		inline Vector3T operator * (const Vector3T& vector) const
		{
			return crossProduct(vector);
		}
	};

	using Vector3 = Vector3T<float, true>;

	template<class T, bool SIMD>
	class Vector4T
		: public VectorT<T, 4, SIMD>
	{
	public:
		Vector4T(T x, T y, T z, T w)
			: VectorT<T, 4, SIMD>(x, y, z, w) {}

		Vector4T(const VectorT<T, 4, SIMD> v)
			: VectorT<T, 4, SIMD>(v) {}
	};

	using Vector4 = Vector4T<float, true>;

	template<class T, size_t Size, bool SIMD>
	class VectorNT
		: public VectorT<T, Size, SIMD>
	{
	public:
		template <class... U>
		VectorNT(T x, U... args)
			: VectorT<T, Size, SIMD>(x, std::forward<U>(args)...) {}

		VectorNT(const VectorT<T, Size, SIMD> v)
			: VectorT<T, Size, SIMD>(v) {}
	};

	template<size_t Size>
	using Vector = VectorNT<float, Size, false>;

	TOV_NAMESPACE_END // math
}

#endif
