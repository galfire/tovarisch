#include <rendering/mesh/mesh.h>

#include <rendering/buffers/index_buffer_object.h>
#include <rendering/buffers/vertex_buffer_object.h>

#include <rendering/mesh/draw_data.h>
#include <rendering/mesh/index_data.h>
#include <rendering/mesh/submesh.h>
#include <rendering/mesh/vertex_data.h>

#include <rendering/pipeline/program.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(mesh)

    Mesh::Mesh(MeshManager& manager) noexcept
        : mManager(manager)
    {}

    Mesh::~Mesh() noexcept
    {}

    auto Mesh::createSubmesh(geometry::Geometry const& geometry, pipeline::Program& program) -> Submesh&
    {
        auto submesh = std::unique_ptr<Submesh>(
            new Submesh(*this, geometry, program)
        );
        mSubmeshes.push_back(std::move(submesh));
        auto ret = mSubmeshes.back().get();
        return *ret;
    }

    auto Mesh::instantiate() const -> MeshInstance
    {
        using DrawDataList = std::vector<DrawData>;
        DrawDataList drawDataList;

        for (auto&& submesh : mSubmeshes)
        {
            auto const& ibo = submesh->getIndexData()->getBufferObject();
            auto const& vbos = submesh->getVertexData()->getBufferObjects();

            for (auto&& vbo : vbos)
            {
                auto& programInstance = submesh->getProgram().instantiate();
                auto drawData = DrawData(ibo, *vbo, programInstance);
                drawDataList.push_back(drawData);
            }
        }
        
        return MeshInstance(std::move(drawDataList));
    }

    TOV_NAMESPACE_END // mesh
    TOV_NAMESPACE_END // rendering
}
