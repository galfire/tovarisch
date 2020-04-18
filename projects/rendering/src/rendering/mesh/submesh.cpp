#include <rendering/mesh/submesh.h>

#include <rendering/mesh/mesh.h>
#include <rendering/mesh/mesh_manager.h>
#include <rendering/mesh/vertex_data_format.h>

#include <tov/rendering/buffers/lock_settings.h>
#include <tov/rendering/buffers/index_type.h>
#include <tov/rendering/buffers/vertex_attribute.h>
#include <tov/rendering/buffers/vertex_format.h>
#include <tov/rendering/buffers/vertex_buffer_object.h>
#include <tov/rendering/geometry/geometry.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    void writeVertexBufferInterleaved(buffers::VertexBufferObject* vbo, const geometry::Geometry& geometry)
    {
        auto format = vbo->getBufferFormat();
        auto attributes = format.getVertexFormat().getAttributes();
        auto numVertices = geometry.getNumVertices();

        auto lock = vbo->lock(buffers::LockSettings::WRITE);

        for (uint i = 0; i < numVertices; i++)
        {
            for (auto&& attribute : attributes)
            {
                auto bytes = attribute.getSize();

                if (geometry.hasAttribute(attribute))
                {
                    switch (attribute.getSemantic())
                    {
                    case buffers::VertexAttribute::Semantic::POSITION:
                        memcpy(lock, &geometry.getPositions()[i], bytes);
                        break;
                    case buffers::VertexAttribute::Semantic::NORMAL:
                        memcpy(lock, &geometry.getNormals()[i], bytes);
                        break;
                    case buffers::VertexAttribute::Semantic::TEXTURE_COORDINATE:
                        memcpy(lock, &geometry.getTextureCoordinates()[i], bytes);
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    memset(lock, 0, bytes);
                }

                // Move the write location forward
                lock = static_cast<byte*>(lock) + bytes;
            }
        }

        vbo->unlock();
    }

    void writeVertexBufferSequential(buffers::VertexBufferObject* vbo, const geometry::Geometry& geometry)
    {
        auto format = vbo->getBufferFormat();
        auto attributes = format.getVertexFormat().getAttributes();

        auto lock = vbo->lock(buffers::LockSettings::WRITE);

        for (auto&& attribute : attributes)
        {
            auto numVertices = geometry.getNumVertices();
            auto bytes = attribute.getSize() * numVertices;

            if (geometry.hasAttribute(attribute))
            {
                switch (attribute.getSemantic())
                {
                case buffers::VertexAttribute::Semantic::POSITION:
                    memcpy(lock, geometry.getPositions(), bytes);
                    break;
                case buffers::VertexAttribute::Semantic::NORMAL:
                    memcpy(lock, geometry.getNormals(), bytes);
                    break;
                case buffers::VertexAttribute::Semantic::TEXTURE_COORDINATE:
                    memcpy(lock, geometry.getTextureCoordinates(), bytes);
                    break;
                default:
                    break;
                }
            }
            else
            {
                memset(lock, 0, bytes);
            }

            // Move the write location forward
            lock = static_cast<byte*>(lock) + bytes;
        }

        vbo->unlock();
    }

    void writeVertexBuffer(buffers::VertexBufferObject* vbo, const geometry::Geometry& geometry)
    {
        auto format = vbo->getBufferFormat();
        switch (format.getSequenceType())
        {
        case buffers::VertexBufferFormat::SequenceType::INTERLEAVED:
            writeVertexBufferInterleaved(vbo, geometry);
            break;
        case buffers::VertexBufferFormat::SequenceType::SEQUENTIAL:
            writeVertexBufferSequential(vbo, geometry);
            break;
        }
    }

    Submesh::Submesh(Mesh& parentMesh, const geometry::Geometry& geometry) noexcept
        : mParentMesh(parentMesh)
        , mGeometry(geometry)
    {
        this->build();
    }

    void Submesh::build()
    {
        this->buildIndexData();
        this->buildVertexData();

        auto& ibo = *mIndexData->getBufferObject();
        auto& vbos = mVertexData->getBufferObjects();

        for (auto&& vbo : vbos)
        {
            DrawData drawData(ibo, *vbo);
            mDrawDataList.push_back(drawData);
        }
    }

    void Submesh::buildIndexData()
    {
        mIndexData = IndexDataUPtr(
            new IndexData(
                mParentMesh.getManager().getBufferManager(),
                mGeometry.getNumIndices()
            )
        );

        auto indices = mGeometry.getIndices();
        auto numIndices = mGeometry.getNumIndices();
        auto indexType = buffers::getIndexType(numIndices);

        auto ibo = mIndexData->getBufferObject();
        auto lock = ibo->lock(buffers::LockSettings::WRITE);

        switch (indexType)
        {
        case buffers::IndexType::BITS_8:
            for (auto i = 0u; i < numIndices; i++)
            {
                auto index = indices[i];
                auto data = (byte)index;
                memcpy(lock, &data, sizeof(byte));
                lock = static_cast<byte*>(lock) + sizeof(byte);
            }
            break;
        case buffers::IndexType::BITS_16:
            for (auto i = 0u; i < numIndices; i++)
            {
                auto index = indices[i];
                auto data = (ushort)index;
                memcpy(lock, &data, sizeof(ushort));
                lock = static_cast<byte*>(lock) + sizeof(ushort);
            }
            break;
        case buffers::IndexType::BITS_32:
            for (auto i = 0u; i < numIndices; i++)
            {
                auto index = indices[i];
                auto data = (uint)index;
                memcpy(lock, &data, sizeof(uint));
                lock = static_cast<byte*>(lock) + sizeof(uint);
            }
            break;
        }

        ibo->unlock();
    }

    void Submesh::buildVertexData()
    {
        auto preferredVertexDataFormat = mParentMesh.getManager().getPreferredVertexDataFormat();
        auto vertexDataFormat = preferredVertexDataFormat;

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
            auto vbo = mVertexData->getBufferObjectForHandle(handle);
            writeVertexBuffer(vbo, mGeometry);
        }
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}