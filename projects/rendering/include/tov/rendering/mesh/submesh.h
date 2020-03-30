#ifndef TOV_RENDERING_MESH_SUBMESH_H
#define TOV_RENDERING_MESH_SUBMESH_H

#include <tov/rendering/rendering_core.h>

#include "index_data.h"
#include "vertex_data.h"
#include "vertex_data_format.h"
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
        Submesh(Mesh<DerivedBufferManagerT>& parentMesh, const geometry::Geometry& geometry) noexcept
            : SubmeshBase()
            , mParentMesh(parentMesh)
            , mGeometry(geometry)
        {
            this->build();
        }

        ~Submesh() noexcept = default;

        auto getVertexDataFormat() const { return mVertexData->getFormat(); }

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

            auto indices = mGeometry.getIndices();
            auto numIndices = mGeometry.getNumIndices();
            auto indexType = buffers::getIndexType(numIndices);

            auto ibo = mIndexData->getBufferObject();
            auto lock = ibo.lock(buffers::LockSettings::WRITE);

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
            
            ibo.unlock();
        }

        void buildVertexData()
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
                auto vbo = &mVertexData->getBufferObjectForHandle(handle);
                this->writeVertexBuffer(vbo);
            }
        }

        void writeVertexBuffer(tov::rendering::buffers::VertexBufferObject* vbo)
        {
            auto format = vbo->getBufferFormat();
            switch (format.getSequenceType())
            {
            case buffers::VertexBufferFormat::SequenceType::INTERLEAVED:
                this->writeVertexBufferInterleaved(vbo);
                break;
            case buffers::VertexBufferFormat::SequenceType::SEQUENTIAL:
                this->writeVertexBufferSequential(vbo);
                break;
            }
        }

        void writeVertexBufferInterleaved(tov::rendering::buffers::VertexBufferObject* vbo)
        {
            auto format = vbo->getBufferFormat();
            auto attributes = format.getVertexFormat().getAttributes();
            auto numVertices = mGeometry.getNumVertices();

            auto lock = vbo->lock(buffers::LockSettings::WRITE);

            for (uint i = 0; i < numVertices; i++)
            {
                for (auto&& attribute : attributes)
                {
                    auto bytes = attribute.getSize();

                    if (mGeometry.hasAttribute(attribute))
                    {
                        switch (attribute.getSemantic())
                        {
                        case buffers::VertexAttribute::Semantic::POSITION:
                            memcpy(lock, &mGeometry.getPositions()[i], bytes);
                            break;
                        case buffers::VertexAttribute::Semantic::NORMAL:
                            memcpy(lock, &mGeometry.getNormals()[i], bytes);
                            break;
                        case buffers::VertexAttribute::Semantic::TEXTURE_COORDINATE:
                            memcpy(lock, &mGeometry.getTextureCoordinates()[i], bytes);
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

        void writeVertexBufferSequential(tov::rendering::buffers::VertexBufferObject* vbo)
        {
            auto format = vbo->getBufferFormat();
            auto attributes = format.getVertexFormat().getAttributes();

            auto lock = vbo->lock(buffers::LockSettings::WRITE);

            for (auto&& attribute : attributes)
            {
                auto numVertices = mGeometry.getNumVertices();
                auto bytes = attribute.getSize() * numVertices;

                if (mGeometry.hasAttribute(attribute))
                {
                    switch (attribute.getSemantic())
                    {
                    case buffers::VertexAttribute::Semantic::POSITION:
                        memcpy(lock, mGeometry.getPositions(), bytes);
                        break;
                    case buffers::VertexAttribute::Semantic::NORMAL:
                        memcpy(lock, mGeometry.getNormals(), bytes);
                        break;
                    case buffers::VertexAttribute::Semantic::TEXTURE_COORDINATE:
                        memcpy(lock, mGeometry.getTextureCoordinates(), bytes);
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

    private:
        Mesh<DerivedBufferManagerT>& mParentMesh;
        const geometry::Geometry& mGeometry;
        IndexDataUPtr mIndexData;
        VertexDataUPtr mVertexData;
    };

    using SubmeshUPtr = std::unique_ptr<SubmeshBase>;

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}

#endif // !TOV_RENDERING_MESH_SUBMESH_H
