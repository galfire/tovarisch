#ifndef TOV_RENDERING_MESH_SUBMESH_H
#define TOV_RENDERING_MESH_SUBMESH_H

#include <tov/rendering/rendering_core.h>

#include "index_data.h"
#include "vertex_data.h"
#include "vertex_data_format.h"
#include <tov/rendering/buffers/lock_settings.h>
#include <tov/rendering/buffers/index_type.h>
#include <tov/rendering/buffers/vertex_attribute.h>
#include <tov/rendering/buffers/vertex_buffer_object.h>

#include <tov/rendering/geometry/geometry.h>

namespace tov
{
	TOV_NAMESPACE_BEGIN(rendering)
	TOV_NAMESPACE_BEGIN(mesh)

	template<class DerivedBufferManagerT> class Mesh;

	class SubmeshBase
	{
		TOV_MOVABLE_ONLY(SubmeshBase)

	public:
		SubmeshBase() noexcept = default;
		virtual ~SubmeshBase() noexcept = default;
	};

	template<class DerivedBufferManagerT>
	class Submesh
		: public SubmeshBase
	{
	public:
		Submesh(Mesh<DerivedBufferManagerT>& parentMesh, const tov::rendering::geometry::Geometry& geometry) noexcept
			: SubmeshBase()
			, mParentMesh(parentMesh)
			, mGeometry(geometry)
		{
			this->build();
		}

		~Submesh() noexcept = default;

	private:
		void build()
		{
			this->buildIndexData();
			this->buildVertexData();
		}

		void buildIndexData()
		{
			mIndexData = IndexDataUPtr(
				new IndexData(
					mParentMesh.getManager().getBufferManager(),
					mGeometry.getNumIndices()
				)
			);

			auto ibo = mIndexData->getBufferObject();
			auto numIndices = mGeometry.getNumIndices();
			auto indexType = tov::rendering::buffers::getIndexType(numIndices);

			auto lock = ibo.lock(tov::rendering::buffers::LockSettings::WRITE);

			switch (indexType)
			{
			case tov::rendering::buffers::IndexType::BITS_8:
			{
				for (uint i = 0; i < numIndices; i++)
				{
					auto index = mGeometry.getIndices()[i];
					auto data = (byte)index;
					memcpy(lock, &data, sizeof(byte));
					lock = static_cast<byte*>(lock) + sizeof(byte);
				}
				break;
			}
			case tov::rendering::buffers::IndexType::BITS_16:
			{
				for (uint i = 0; i < numIndices; i++)
				{
					auto index = mGeometry.getIndices()[i];
					auto data = (ushort)index;
					memcpy(lock, &data, sizeof(ushort));
					lock = static_cast<byte*>(lock) + sizeof(ushort);
				}
				break;
			}
			case tov::rendering::buffers::IndexType::BITS_32:
			{
				for (uint i = 0; i < numIndices; i++)
				{
					auto index = mGeometry.getIndices()[i];
					auto data = (uint)index;
					memcpy(lock, &data, sizeof(uint));
					lock = static_cast<byte*>(lock) + sizeof(uint);
				}
				break;
			}
			}
			
			ibo.unlock();
		}

		void buildVertexData()
		{
			auto preferredVertexDataFormat = mParentMesh.getManager().getPreferredVertexDataFormat();
			auto preferredAttributes = preferredVertexDataFormat.getAttributes();

			VertexDataFormat vertexDataFormat;

			for (auto&& attribute : preferredAttributes)
			{
				if (mGeometry.hasAttribute(attribute))
				{
					auto handle = preferredVertexDataFormat.getHandleForAttribute(attribute);
					auto vertexBufferFormat = preferredVertexDataFormat.getVertexBufferFormatForAttribute(attribute);
					vertexDataFormat.mapHandleToFormat(handle, vertexBufferFormat);
				}
			}

			mVertexData = VertexDataUPtr(
				new VertexData(
					mParentMesh.getManager().getBufferManager(),
					vertexDataFormat,
					mGeometry.getNumVertices()
				)
			);

			auto handles = vertexDataFormat.getHandles();
			for (auto&& handle : handles)
			{
				auto vbo = &mVertexData->getBufferObjectForHandle(handle);
				this->writeVertexBuffer(vbo);
			}
		}

		void writeVertexBuffer(tov::rendering::buffers::VertexBufferObject* vbo)
		{
			auto format = vbo->getBufferFormat();
			switch (format.getSequenceType())
			{
			case tov::rendering::buffers::VertexBufferFormat::SequenceType::INTERLEAVED:
				this->writeVertexBufferInterleaved(vbo);
				break;
			case tov::rendering::buffers::VertexBufferFormat::SequenceType::SEQUENTIAL:
				this->writeVertexBufferSequential(vbo);
				break;
			}
		}

		void writeVertexBufferInterleaved(tov::rendering::buffers::VertexBufferObject* vbo)
		{
			auto format = vbo->getBufferFormat();
			auto attributes = format.getVertexFormat().getAttributes();
			auto numVertices = mGeometry.getNumVertices();

			auto lock = vbo->lock(tov::rendering::buffers::LockSettings::WRITE);

			for (uint i = 0; i < numVertices; i++)
			{
				for (auto&& attribute : attributes)
				{
					auto bytes = attribute.getSize();
					switch (attribute.getSemantic())
					{
					case tov::rendering::buffers::VertexAttribute::Semantic::POSITION:
						memcpy(lock, &mGeometry.getPositions()[i], bytes);
						break;
					case tov::rendering::buffers::VertexAttribute::Semantic::NORMAL:
						memcpy(lock, &mGeometry.getNormals()[i], bytes);
						break;
					case tov::rendering::buffers::VertexAttribute::Semantic::TEXTURE_COORDINATE:
						memcpy(lock, &mGeometry.getTextureCoordinates()[i], bytes);
						break;
					}

					// Move the write location forward
					lock = static_cast<byte*>(lock) + bytes;
				}
			}

			vbo->unlock();
		}

		void writeVertexBufferSequential(tov::rendering::buffers::VertexBufferObject* vbo)
		{
			auto format = vbo->getBufferFormat();
			auto attributes = format.getVertexFormat().getAttributes();

			auto lock = vbo->lock(tov::rendering::buffers::LockSettings::WRITE);

			for (auto&& attribute : attributes)
			{
				auto numVertices = mGeometry.getNumVertices();
				auto bytes = attribute.getSize() * numVertices;

				switch (attribute.getSemantic())
				{
				case tov::rendering::buffers::VertexAttribute::Semantic::POSITION:
					memcpy(lock, mGeometry.getPositions(), bytes);
					break;
				case tov::rendering::buffers::VertexAttribute::Semantic::NORMAL:
					memcpy(lock, mGeometry.getNormals(), bytes);
					break;
				case tov::rendering::buffers::VertexAttribute::Semantic::TEXTURE_COORDINATE:
					memcpy(lock, mGeometry.getTextureCoordinates(), bytes);
					break;
				}

				// Move the write location forward
				lock = static_cast<byte*>(lock) + bytes;
			}

			vbo->unlock();
		}

	private:
		Mesh<DerivedBufferManagerT>& mParentMesh;
		const tov::rendering::geometry::Geometry& mGeometry;
		IndexDataUPtr mIndexData;
		VertexDataUPtr mVertexData;
	};

	using SubmeshUPtr = std::unique_ptr<SubmeshBase>;

	TOV_NAMESPACE_END // mesh
	TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_MESH_SUBMESH_H
