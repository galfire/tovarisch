#include <rendering/mesh/submesh.h>

#include <rendering/material.h>

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

#include <rendering/backend.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    void writeVertexBufferInterleaved(buffers::VertexBufferObject& vbo, buffers::VertexBufferFormat const& vbf, geometry::Geometry const& geometry)
    {
        auto attributes = vbf.getVertexFormat().getAttributes();
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

    void writeVertexBufferSequential(buffers::VertexBufferObject& vbo, buffers::VertexBufferFormat const& vbf, geometry::Geometry const& geometry)
    {
        auto attributes = vbf.getVertexFormat().getAttributes();

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

    void writeVertexBuffer(buffers::VertexBufferObject& vbo, buffers::VertexBufferFormat const& vbf, geometry::Geometry const& geometry)
    {
        switch (vbf.getSequenceType())
        {
        case buffers::VertexBufferFormat::SequenceType::INTERLEAVED:
            writeVertexBufferInterleaved(vbo, vbf, geometry);
            break;
        case buffers::VertexBufferFormat::SequenceType::SEQUENTIAL:
            writeVertexBufferSequential(vbo, vbf, geometry);
            break;
        }
    }

    Submesh::Submesh(Mesh& parentMesh, const geometry::Geometry& geometry, VertexDataFormat const& vertexDataFormat) noexcept
        : mParentMesh(parentMesh)
    {
        this->build(geometry, vertexDataFormat);
    }

    Submesh::~Submesh() noexcept
    {}

    auto Submesh::instantiate() -> SubmeshInstance&
    {
        {
            auto const& ibo = mIndexData->getBufferObject();
            auto materialInstance = mMaterial ? &mMaterial->instantiate() : nullptr;
            auto submeshInstance = std::make_unique<SubmeshInstance>(*mDrawDataContext.get(), ibo, materialInstance);
            mSubmeshInstances.push_back(std::move(submeshInstance));
        }

        auto submeshInstance = mSubmeshInstances.back().get();
        return *submeshInstance;
    }

    void Submesh::build(geometry::Geometry const& geometry, VertexDataFormat const& vertexDataFormat)
    {
        this->buildIndexData(geometry);
        this->buildVertexData(geometry, vertexDataFormat);
    }

    void Submesh::buildIndexData(geometry::Geometry const& geometry)
    {
        mIndexData = std::make_unique<IndexData>(
            mParentMesh.getManager().getBufferManager(),
            geometry.getNumIndices()
        );

        auto indices = geometry.getIndices();
        auto numIndices = geometry.getNumIndices();
        auto indexType = buffers::getIndexType(numIndices);

        auto& ibo = mIndexData->getBufferObject();
        auto guard = buffers::Guard(ibo, buffers::LockSettings::WRITE);
        auto lock = guard.getLock();

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

    void Submesh::buildVertexData(geometry::Geometry const& geometry, VertexDataFormat const& vertexDataFormat)
    {
        mVertexData = std::make_unique<VertexData>(
            mParentMesh.getManager().getBufferManager(),
            vertexDataFormat,
            geometry.getNumVertices()
        );

        auto handles = vertexDataFormat.getHandles();
        for (auto&& handle : handles)
        {
            auto& vbo = mVertexData->getBufferObjectForHandle(handle);
            auto vbf = vertexDataFormat.getVertexBufferFormatForHandle(handle);
            writeVertexBuffer(vbo, vbf, geometry);
        }

        mDrawDataContext = std::unique_ptr<DrawDataContext>(
            backend::createDrawDataContext(*mVertexData.get(), vertexDataFormat)
        );
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}
