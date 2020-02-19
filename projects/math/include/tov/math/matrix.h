#ifndef TOV_MATH_MATRIX_H
#define TOV_MATH_MATRIX_H

#include "math_core.h"

#include "matrix_component.h"

#ifdef TOV_DEBUG
#	include <ostream>
#endif

#include <cassert>
#include <cstring>

namespace tov
{
	TOV_NAMESPACE_BEGIN(math)

	template<class T, size_t Rows, size_t Columns, SIMD::Type SIMD_T>
	class MatrixT
		: public MatrixComponent<T, Rows, Columns, SIMD_T>
	{
	public:
		using Base = MatrixComponent<T, Rows, Columns, SIMD_T>;
		using Base::MatrixComponent;
		using Row = typename Base::Row;

		static MatrixT buildIdentity()
		{
			assert(Base::ROWS == Base::COLUMNS);
			MatrixT m(0);
			for (size_t i = 0; i < Base::ROWS; i++)
			{
				m[i][i] = static_cast<T>(1);
			}
			return m;
		}

		explicit MatrixT(T f = (T)0)
		{
			std::fill(this->mArr.begin(), this->mArr.end(), f);
		}

		MatrixT(const MatrixT& matrix)
		{
			memcpy(this->mArr.data(), matrix.mArr.data(), Base::SIZE_ACTUAL * sizeof(T));
		}

		inline MatrixT& operator = (const MatrixT& matrix)
		{
			memcpy(this->mArr.data(), matrix.mArr.data(), Base::SIZE_ACTUAL * sizeof(T));
			return *this;
		}

		inline const Row& operator [] (const size_t i) const
		{
			assert(i < Base::ROWS);
			return this->mRows[i];
		}

		inline Row& operator [] (const size_t i)
		{
			assert(i < Base::ROWS);
			return this->mRows[i];
		}

		inline MatrixT<T, Base::COLUMNS, Base::ROWS, SIMD_T> transpose(void) const
		{
			MatrixT<T, Base::COLUMNS, Base::ROWS, SIMD_T> m;
			for (size_t i = 0; i < Base::ROWS; i++)
			{
				for (size_t j = 0; j < Base::COLUMNS; j++)
				{
					m[j][i] = this->mRows[i][j];
				}
			}
			return m;
		}

		template<class U>
		MatrixT<T, Base::ROWS, U::COLUMNS, SIMD_T> concatenate(const U& matrix) const
		{
			assert(Base::COLUMNS == U::ROWS);
			
			MatrixT<T, Base::ROWS, U::COLUMNS, SIMD_T> result;
			auto transpose = matrix.transpose();
			for (size_t i = 0; i < Base::ROWS; i++)
			{
				auto row = this->mRows[i];
				for (size_t j = 0; j < U::COLUMNS; j++)
				{
					auto column = transpose[j];
					result[i][j] = row.dot(column);
				}
			}
			return result;
		}

		template<class U>
		MatrixT<T, Base::ROWS, U::COLUMNS, SIMD_T> operator * (const U& matrix) const
		{
			return this->concatenate(matrix);
		}

		template<class U>
		MatrixT<T, Base::ROWS, U::COLUMNS, SIMD_T>& operator *= (const U& matrix)
		{
			*this = this->concatenate(matrix);
			return *this;
		}

#ifdef TOV_DEBUG
		inline friend std::ostream& operator <<
			(std::ostream& o, const MatrixT& mat)
		{
			o << "Matrix(";
			for (size_t i = 0; i < Base::ROWS; ++i)
			{
				o << " { ";
				for (size_t j = 0; j < Base::COLUMNS; ++j)
				{
					o << mat[i][j] << " ";
				}
				o << "}";
			}
			o << " )";
			return o;
		}
#endif

	public:
		static const MatrixT ZERO;
		static const MatrixT IDENTITY;
	};

	template<class T, size_t Rows, size_t Columns, SIMD::Type SIMD_T>
	const MatrixT<T, Rows, Columns, SIMD_T> MatrixT<T, Rows, Columns, SIMD_T>::ZERO(0);

	template<class T, size_t Rows, size_t Columns, SIMD::Type SIMD_T>
	const MatrixT<T, Rows, Columns, SIMD_T> MatrixT<T, Rows, Columns, SIMD_T>::IDENTITY = MatrixT<T, Rows, Columns, SIMD_T>::buildIdentity();

	template<size_t Rows, size_t Columns, SIMD::Type SIMD_T = SIMD::_NONE>
	using Matrix = MatrixT<float, Rows, Columns, SIMD_T>;

	using Matrix3 = MatrixT<float, 3, 3, SIMD::_128F>;
	using Matrix4 = MatrixT<float, 4, 4, SIMD::_128F>;

	TOV_NAMESPACE_END // math
}

#endif
