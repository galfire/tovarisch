#ifndef TOV_RENDERING_BUFFERS_BUFFER_ACCESSOR_H
#define TOV_RENDERING_BUFFERS_BUFFER_ACCESSOR_H

#include <tov/rendering/rendering_core.h>

#include <tov/core/functional.h>
#include <tov/rendering/buffers/access_settings.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	template<class ReaderT, class WriterT, AccessSettings accessSettings>
	class BufferAccessor
	{
	private:
		template<AccessSettings> class Reader {};
		template<>
		class Reader<AccessSettings::READ>
		{
		public:
			template<class... U>
			Reader(U&&... args)
				: mReader(std::forward<U>(args)...)
			{}

			// Read the buffer into pDest
			void read(size_t offset, size_t length, void* pDest)
			{
				mReader.read(offset, length, pDest);
			}

		private:
			ReaderT mReader;
		};
		template<>
		class Reader<AccessSettings::NO_READ>
		{
		public:
			template<class... U> Reader(U&&... args) {}
			void read(size_t offset, size_t length, void* pDest) {}
		};

		template<AccessSettings> class Writer {};
		template<>
		class Writer<AccessSettings::WRITE>
		{
		public:
			template<class... U>
			Writer(U&&... args)
				: mWriter(std::forward<U>(args)...)
			{}

			// Write the buffer with the data from pSrc
			void write(size_t offset, size_t length, void* pSrc)
			{
				mWriter.write(offset, length, pSrc);
			}

		private:
			WriterT mWriter;
		};
		template<>
		class Writer<AccessSettings::NO_WRITE>
		{
		public:
			template<class... U> Writer(U&&... args) {}
			void write(size_t offset, size_t length, void* pSrc) {}
		};

	private:
		static const bitwise_and<AccessSettings> evaluator;
		static constexpr AccessSettings WRITE_ENABLED = evaluator(accessSettings, AccessSettings::WRITE);
		static constexpr AccessSettings READ_ENABLED = evaluator(accessSettings, AccessSettings::READ);

	public:
		template<class... U>
		BufferAccessor(U&&... args)
			: mReader(std::forward<U>(args)...)
			, mWriter(std::forward<U>(args)...)
		{}
		~BufferAccessor() = default;

		void read(size_t offset, size_t length, void* pDest)
		{
			mReader.read(offset, length, pDest);
		}

		void write(size_t offset, size_t length, void* pSrc)
		{
			mWriter.write(offset, length, pSrc);
		}

	private:
		Reader<READ_ENABLED> mReader;
		Writer<WRITE_ENABLED> mWriter;
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}

#endif
