#include "rendering/producers/producer.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(producers)

    Producer::Producer(ResourceBucket& resourceBucket) noexcept
        : mResourceBucket(resourceBucket)
    {}

    void Producer::setOutput(const std::string& name, void* resource)
    {
        mResourceBucket.addResource(
            name, 
            { resource, this }
        );
    }

    void Producer::setInput(const std::string& name)
    {
        auto& resource = mResourceBucket.getResource(name);
        auto& resourceProducer = resource.getProducer();
        this->addDependency(&resourceProducer);
    }

    TOV_NAMESPACE_END // producers
    TOV_NAMESPACE_END // rendering
}
