#include <rendering/mesh/submesh.h>

#include <rendering/buffers/guard.h>
#include <rendering/buffers/index_buffer_object.h>
#include <rendering/buffers/index_type.h>
#include <rendering/buffers/lock_settings.h>
#include <rendering/buffers/vertex_attribute.h>
#include <rendering/buffers/vertex_buffer_object.h>
#include <rendering/buffers/vertex_format.h>

#include <rendering/geometry/geometry.h>

#include <rendering/mesh/index_data.h>
#include <rendering/mesh/mesh.h>
#include <rendering/mesh/mesh_manager.h>
#include <rendering/mesh/vertex_data.h>
#include <rendering/mesh/vertex_data_format.h>

#include <rendering/pipeline/program.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    void writeVertexBufferInterleaved(buffers::VertexBufferObject& vbo, const geometry::Geometry& geometry)
    {
        auto const& format = vbo.getBufferFormat();
        auto attributes = format.getVertexFormat().getAttributes();
        auto numVertices = geometry.getNumVertices();

        auto guard = buffers::Guard(vbo, buffers::LockSettings::WRITE);
        auto lock = guard.getLock();

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
    }

    void writeVertexBufferSequential(buffers::VertexBufferObject& vbo, const geometry::Geometry& geometry)
    {
        auto const& format = vbo.getBufferFormat();
        auto attributes = format.getVertexFormat().getAttributes();

        auto guard = buffers::Guard(vbo, buffers::LockSettings::WRITE);
        auto lock = guard.getLock();

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
    }

    void writeVertexBuffer(buffers::VertexBufferObject& vbo, const geometry::Geometry& geometry)
    {
        auto format = vbo.getBufferFormat();
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

    Submesh::Submesh(Mesh& parentMesh, const geometry::Geometry& geometry, pipeline::Program& program) noexcept
        : mParentMesh(parentMesh)
        , mGeometry(geometry)
        , mProgram(program)
    {
        this->build();
    }

    Submesh::~Submesh() noexcept
    {}

    void Submesh::build()
    {
        this->buildIndexData();
        this->buildVertexData();
    }

    void Submesh::buildIndexData()
    {
        mIndexData = std::unique_ptr<IndexData>(
            new IndexData(
                mParentMesh.getManager().getBufferManager(),
                mGeometry.getNumIndices()
            )
        );

        auto indices = mGeometry.getIndices();
        auto numIndices = mGeometry.getNumIndices();
        auto indexType = buffers::getIndexType(numIndices);

        auto& ibo = mIndexData->getBufferObject();
        auto guard = buffers::Guard(ibo, buffers::LockSettings::WRITE);
        auto lock = guard.getLock();;

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
    }

    void Submesh::buildVertexData()
    {
        auto preferredVertexDataFormat = mParentMesh.getManager().getPreferredVertexDataFormat();
        auto vertexDataFormat = preferredVertexDataFormat;

        mVertexData = std::unique_ptr<VertexData>(
            new VertexData(
                mParentMesh.getManager().getBufferManager(),
                vertexDataFormat,
                mGeometry.getNumVertices()
            )
        );

        auto handles = vertexDataFormat.getHandles();
        for (auto&& handle : handles)
        {
            auto& vbo = mVertexData->getBufferObjectForHandle(handle);
            writeVertexBuffer(vbo, mGeometry);
        }
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}
