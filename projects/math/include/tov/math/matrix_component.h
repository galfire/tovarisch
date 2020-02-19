#ifndef TOV_MATH_MATRIX_COMPONENT_H
#define TOV_MATH_MATRIX_COMPONENT_H

#include "math_core.h"

#include "simd.h"
#include "vector.h"

#include <cstring>
#include <vector>

namespace tov
{
	TOV_NAMESPACE_BEGIN(math)

	template<class T, size_t Rows, size_t Columns, SIMD::Type SIMD_T>
	class MatrixComponent
	{
	public:
		constexpr static size_t ROWS = Rows;
		constexpr static size_t COLUMNS = Columns;
		constexpr static size_t SIZE = ROWS * COLUMNS;

		using Row = VectorTN<T, COLUMNS, SIMD_T>;
		using Column = VectorTN<T, ROWS, SIMD_T>;

	public:
		MatrixComponent()
		{
			std::fill(mArr.begin(), mArr.end(), static_cast<T>(0.0f));
		}

		MatrixComponent(const MatrixComponent& matrix)
		{
			memcpy(mArr.data(), matrix.mArr.data(), SIZE * sizeof(T));
		}

		template<class... U>
		MatrixComponent(T x, U&&... args)
			: mArr { x, std::forward<U>(args)... }
		{}

	protected:
		union
		{
			std::array<T, SIZE> mArr;
			std::array<Row, ROWS> mRows;
		};
	};

	template<size_t Rows, size_t Columns>
	class MatrixComponent<float, Rows, Columns, SIMD::_128F>
	{
	protected:
		using T = float;

	public:
		constexpr static size_t ROWS = Rows;
		constexpr static size_t COLUMNS = Columns;
		constexpr static size_t SIZE = ROWS * COLUMNS;

		using Row = VectorTN<T, COLUMNS, SIMD::_128F>;
		using Column = VectorTN<T, ROWS, SIMD::_128F>;

	public:
		MatrixComponent()
		{
			std::fill(mArr.begin(), mArr.end(), 0.0f);
		}

		MatrixComponent(const MatrixComponent& matrix)
		{
			memcpy(mArr.data(), matrix.mArr.data(), SIZE_ACTUAL * sizeof(T));
		}

		template<class... U>
		MatrixComponent(T x, U&&... args)
			: mArr {}
		{
			std::vector<T> v { x, args... };
			
			T* writePtr = this->mArr.data();
			T* readPtr = v.data();

			for (size_t i = 0; i < ROWS; i++)
			{
				size_t writeRow = i * COLUMNS_ACTUAL;
				size_t readRow = i * COLUMNS;
				memcpy(
					writePtr + writeRow,
					readPtr + readRow,
					COLUMNS * sizeof(T)
				);
			}
		}

	protected:
		constexpr static size_t ROWS_ACTUAL = ROWS;
		constexpr static size_t COLUMNS_ACTUAL = 4u;
		constexpr static size_t SIZE_ACTUAL = ROWS_ACTUAL * COLUMNS_ACTUAL;

		union
		{
			std::array<T, SIZE_ACTUAL> mArr;
			std::array<Row, ROWS_ACTUAL> mRows;
		};
	};

	TOV_NAMESPACE_END // math
}

#endif
