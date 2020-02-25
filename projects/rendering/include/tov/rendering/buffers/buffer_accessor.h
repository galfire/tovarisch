#ifndef TOV_RENDERING_BUFFERS_BUFFER_ACCESSOR_H
#define TOV_RENDERING_BUFFERS_BUFFER_ACCESSOR_H

#include <tov/rendering/rendering_core.h>

#include <tov/core/functional.h>
#include <tov/rendering/buffers/access_settings.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	namespace {
		template<class ReaderT, AccessSettings> class Reader {};
		template<class ReaderT> class Reader<ReaderT, AccessSettings::READ>
		{
		public:
			template<class... U> Reader(void*& src, void*& dst, U&&... args)
				: mReader(src, dst, std::forward<U>(args)...)
			{}

			// Read the buffer into scratch
			void read(size_t offset, size_t length)
			{
				mReader(offset, length);
			}

		private:
			ReaderT mReader;
		};
		template<class ReaderT> class Reader<ReaderT, AccessSettings::NO_READ>
		{
		public:
			template<class... U> Reader(U&&... args) {}
			void read(size_t offset, size_t length) {}
		};

		template<class WriterT, AccessSettings> class Writer {};
		template<class WriterT> class Writer<WriterT, AccessSettings::WRITE>
		{
		public:
			template<class... U> Writer(void*& src, void*& dst, U&&... args)
				: mWriter(src, dst, std::forward<U>(args)...)
			{}

			// Write scratch into the buffer
			void write(size_t offset, size_t length)
			{
				mWriter(offset, length);
			}

		private:
			WriterT mWriter;
		};

		template<class WriterT> class Writer<WriterT, AccessSettings::NO_WRITE>
		{
		public:
			template<class... U> Writer(U&&... args) {}
			void write(size_t offset, size_t length) {}
		};
	}

	template<class ReaderT, class WriterT, AccessSettings accessSettings>
	class BufferAccessor
	{
	private:
		static const bitwise_and<AccessSettings> evaluator;
		static constexpr AccessSettings WRITE_ENABLED = evaluator(accessSettings, AccessSettings::WRITE);
		static constexpr AccessSettings READ_ENABLED = evaluator(accessSettings, AccessSettings::READ);

	public:
		template<class... U> BufferAccessor(void*& buffer, void*& scratch, U&&... args)
			: mReader(buffer, scratch, std::forward<U>(args)...)
			, mWriter(scratch, buffer, std::forward<U>(args)...)
		{}
		~BufferAccessor() = default;

		void read(size_t offset, size_t length)
		{
			mReader.read(offset, length);
		}

		void write(size_t offset, size_t length)
		{
			mWriter.write(offset, length);
		}

	private:
		Reader<ReaderT, READ_ENABLED> mReader;
		Writer<WriterT, WRITE_ENABLED> mWriter;
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}

#endif
