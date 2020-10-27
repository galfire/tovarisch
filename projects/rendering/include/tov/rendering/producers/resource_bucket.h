#ifndef TOV_RENDERING_PRODUCERS_RESOURCE_BUCKET_H
#define TOV_RENDERING_PRODUCERS_RESOURCE_BUCKET_H

#include <tov/rendering/rendering_core.h>

#include "resource.h"

#include <string>
#include <unordered_map>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(producers)

    class ResourceBucket
    {
    public:
        ResourceBucket() noexcept = default;
        ~ResourceBucket() noexcept = default;

        auto addResource(const std::string& name, Resource resource) -> void
        {
            mResourceMap[name] = resource;
        }

        auto getResource(const std::string& name) -> Resource&
        {
            return mResourceMap.at(name);
        }

        auto reset() -> void
        {
            mResourceMap.clear();
        }

    private:
        using ResourceMap = std::unordered_map<std::string, Resource>;
        ResourceMap mResourceMap;
    };

    TOV_NAMESPACE_END // producers
    TOV_NAMESPACE_END // rendering
}

#endif
