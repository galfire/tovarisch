#ifndef TOV_RENDERING_PRODUCERS_DEPENDENCY_NODE_H
#define TOV_RENDERING_PRODUCERS_DEPENDENCY_NODE_H

#include <tov/rendering/rendering_core.h>

#include "dependency_graph.h"

#include <vector>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(producers)

    class DependencyNode
    {
    public:
        using DependencyList = std::vector<DependencyNode*>;

    public:
        DependencyNode() noexcept;;
        virtual ~DependencyNode() noexcept;

        void addDependency(DependencyNode* dependency);

        auto getDependencies() const -> auto const& { return mDependencyList; }

        void resetDependencies();

        auto getResolvedDependencies() const -> DependencyList;

    private:
        DependencyList mDependencyList;

        DependencyGraph mDependencyGraph;
    };

    TOV_NAMESPACE_END // producers
    TOV_NAMESPACE_END // rendering
}

#endif
