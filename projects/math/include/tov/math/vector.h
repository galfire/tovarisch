#ifndef TOV_MATH_VECTOR_H
#define TOV_MATH_VECTOR_H

#include "math_core.h"

#if TOV_DEBUG
#	include <ostream>
#endif

#include <cstring>

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

		explicit VectorT(T f = (T)0)
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
			return *(&this->mArr[0] + i);
		}

		inline T& operator [] (const size_t i)
		{
			assert(i < Size);
			return *(&this->mArr[0] + i);
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
			this->mMemory += vector.mMemory;
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
			this->mMemory -= vector.mMemory;
			return *this;
		}

		inline VectorT operator * (const VectorT& vector)
		{
			VectorT v = *this;
			v.mMemory *= vector.mMemory;
			return v;
		}

		inline VectorT& operator *= (const VectorT& vector)
		{
			this->mMemory *= vector.mMemory;
			return *this;
		}
		inline VectorT operator / (const VectorT& vector)
		{
			VectorT v = *this;
			v.mMemory /= vector.mMemory;
			return v;
		}

		inline VectorT& operator /= (const VectorT& vector)
		{
			this->mMemory /= vector.mMemory;
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
			this->mMemory *= scalar;
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
			this->mMemory /= scalar;
			return *this;
		}

		inline bool operator == (const VectorT& vector) const
		{
			return this->mMemory == vector.mMemory;
		}

		inline bool operator != (const VectorT& vector) const
		{
			return this->mMemory != vector.mMemory;
		}

		inline T dot(const VectorT& vector) const
		{
			T dot = this->mMemory.dot(vector.mMemory);
			return dot;
		}

		inline T squaredLength() const
		{
			return this->mMemory.squaredLength();
		}

		inline T length() const
		{
			return static_cast<T>(std::sqrt(this->squaredLength()));
		}

		inline VectorT reciprocal() const
		{
			VectorT v = *this;
			v.mMemory.reciprocalAssign();
			return v;
		}

		inline VectorT& normalize()
		{
			T length = this->length();
			if (length > 1e-08)
			{
				VectorT r(length);
				*this *= r.reciprocal();
			}
			return *this;
		}

		inline VectorT normalizedCopy() const
		{
			VectorT v = *this;
			v.normalize();
			return v;
		}

		auto data() const
		{
			return this->mArr.data();
		}

#if TOV_DEBUG
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

	public:
		static const VectorT ZERO;
		static const VectorT UNIT_SCALE;
	};

	template<class T, size_t Size, SIMD::Type SIMD_T> const VectorT<T, Size, SIMD_T> VectorT<T, Size, SIMD_T>::ZERO(0);
	template<class T, size_t Size, SIMD::Type SIMD_T> const VectorT<T, Size, SIMD_T> VectorT<T, Size, SIMD_T>::UNIT_SCALE(1);

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
			this->mMemory.crossAssign(vector.mMemory);
			return *this;
		}

	public:
		static const VectorT3 UNIT_X;
		static const VectorT3 UNIT_Y;
		static const VectorT3 UNIT_Z;
	};

	template<class T, SIMD::Type SIMD_T> const VectorT3<T, SIMD_T> VectorT3<T, SIMD_T>::UNIT_X = VectorT3(1, 0, 0);
	template<class T, SIMD::Type SIMD_T> const VectorT3<T, SIMD_T> VectorT3<T, SIMD_T>::UNIT_Y = VectorT3(0, 1, 0);
	template<class T, SIMD::Type SIMD_T> const VectorT3<T, SIMD_T> VectorT3<T, SIMD_T>::UNIT_Z = VectorT3(0, 0, 1);

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
