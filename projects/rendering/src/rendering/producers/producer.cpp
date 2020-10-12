#include "rendering/producers/producer.h"

#include "rendering/producers/resource_bucket.h"
#include "rendering/producers/resource.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(producers)

    Producer::Producer(ResourceBucket& resourceBucket) noexcept
        : mResourceBucket(resourceBucket)
    {}

    void Producer::setOutput(const std::string& name, Resource& resource)
    {
        mResourceBucket.addResource(name, resource);
    }

    void Producer::setInput(const std::string& name)
    {
        auto& resource = mResourceBucket.getResource(name);
        auto& resourceProducer = resource.getProducer();
        this->addDependency(&resourceProducer);
    }

    auto Producer::getResource(const std::string& name) const -> void*
    {
        return mResourceBucket.getResource(name).getResource();
    }

    TOV_NAMESPACE_END // producers
    TOV_NAMESPACE_END // rendering
}