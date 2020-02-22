#ifndef TOV_RENDERING_BUFFERS_BUFFER_ACCESSOR_H
#define TOV_RENDERING_BUFFERS_BUFFER_ACCESSOR_H

#include <tov/rendering/rendering_core.h>

#include <tov/core/functional.h>
#include <tov/rendering/buffers/usage_settings.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(buffers)

	template<class ReaderT, class WriterT, UsageSettings usageSettings>
	class BufferAccessor
	{
	private:
		template<class ReaderT, UsageSettings settings> class Reader {};
		template<class ReaderT>
		class Reader<ReaderT, UsageSettings::READ>
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
		template<class ReaderT>
		class Reader<ReaderT, UsageSettings::NO_READ>
		{
		public:
			template<class... U> Reader(U&&... args) {}
			void read(size_t offset, size_t length, void* pDest) {}
		};

		template<class WriterT, UsageSettings settings> class Writer {};
		template<class WriterT>
		class Writer<WriterT, UsageSettings::WRITE>
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
		template<class WriterT>
		class Writer<WriterT, UsageSettings::NO_WRITE>
		{
		public:
			template<class... U> Writer(U&&... args) {}
			void write(size_t offset, size_t length, void* pSrc) {}
		};

	private:
		static const bitwise_and<UsageSettings> evaluator;
		static constexpr UsageSettings WRITE_ENABLED = evaluator(usageSettings, UsageSettings::WRITE);
		static constexpr UsageSettings READ_ENABLED = evaluator(usageSettings, UsageSettings::READ);

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
		Reader<ReaderT, READ_ENABLED> mReader;
		Writer<WriterT, WRITE_ENABLED> mWriter;
	};

	TOV_NAMESPACE_END // buffers
	TOV_NAMESPACE_END // rendering
}

#endif
