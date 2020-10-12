#ifndef TOV_RENDERING_PRODUCERS_RESOURCE_H
#define TOV_RENDERING_PRODUCERS_RESOURCE_H

#include <tov/rendering/rendering_core.h>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(producers)

    class Producer;

    class Resource
    {
    public:
        /*Resource() noexcept = default;
        ~Resource() noexcept = default;*/

        auto setResource(void* resource) { mResource = resource; }
        auto getResource() const { return mResource; }

        auto setProducer(Producer* producer) { mProducer = producer; }
        auto getProducer() -> auto& { return *mProducer; }

    //private:
        void* mResource = nullptr;
        Producer* mProducer = nullptr;
    };

    TOV_NAMESPACE_END // producers
    TOV_NAMESPACE_END // rendering
}

#endif
