#include "rendering/producers/dependency_graph.h"

#include "rendering/producers/dependency_node.h"

#include <algorithm>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(producers)

    auto resolve(DependencyNode* node, DependencyGraph::DependencyList& resolved) -> void
    {
        auto& dependencies = node->getDependencies();
        for (auto&& dependency : dependencies)
        {
            if (std::find(resolved.begin(), resolved.end(), dependency) == resolved.end())
            {
                resolve(dependency, resolved);
            }
        }
        resolved.push_back(node);
    }

    auto DependencyGraph::resolveDependencies() const -> DependencyGraph::DependencyList
    {
        DependencyGraph::DependencyList resolved = {};
        resolve(mRootNode, resolved);
        return resolved;
    }

    TOV_NAMESPACE_END // producers
    TOV_NAMESPACE_END // producers
}
