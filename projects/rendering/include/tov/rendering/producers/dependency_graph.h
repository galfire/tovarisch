#ifndef TOV_RENDERING_PRODUCERS_DEPENDENCY_GRAPH_H
#define TOV_RENDERING_PRODUCERS_DEPENDENCY_GRAPH_H

#include <tov/rendering/rendering_core.h>

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(producers)

    class DependencyNode;

    class DependencyGraph
    {
    public:
        using DependencyList = std::vector<DependencyNode*>;

    public:
        DependencyGraph(DependencyNode* rootNode) noexcept
            : mRootNode(rootNode)
        {}
        ~DependencyGraph() noexcept = default;

        auto resolveDependencies() const -> DependencyList;

    private:
        DependencyNode* mRootNode;
    };

    TOV_NAMESPACE_END // producers
    TOV_NAMESPACE_END // rendering
}

#endif
