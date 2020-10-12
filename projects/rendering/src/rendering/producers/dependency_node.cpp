#include "rendering/producers/dependency_node.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(producers)

    DependencyNode::DependencyNode() noexcept
        : mDependencyGraph(this)
    {}

    DependencyNode::~DependencyNode() noexcept
    {}

    void DependencyNode::addDependency(DependencyNode* dependency)
    {
        mDependencyList.push_back(dependency);
        //mDependencyGraph.resolveDependencies();
    }

    auto DependencyNode::getResolvedDependencies() const -> DependencyNode::DependencyList
    {
        return mDependencyGraph.resolveDependencies();
    }

    TOV_NAMESPACE_END // producers
    TOV_NAMESPACE_END // rendering
}
