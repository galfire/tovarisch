#ifndef TOV_RENDERING_PRODUCERS_PRODUCER_H
#define TOV_RENDERING_PRODUCERS_PRODUCER_H

#include <tov/rendering/rendering_core.h>

#include "dependency_node.h"
#include "resource.h"
#include "resource_bucket.h"

#include <string>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    TOV_NAMESPACE_BEGIN(pipeline)
    class Program;
    class ProgramInstance;
    class Framebuffer;
    TOV_NAMESPACE_END // pipeline

    TOV_NAMESPACE_END // rendering

    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(producers)

    class Producer
        : public DependencyNode
    {
        TOV_MOVABLE_ONLY(Producer)

    public:
        Producer(ResourceBucket& resourceBucket) noexcept;
        virtual ~Producer() noexcept = default;

        virtual void setInputs() TOV_ABSTRACT;
        virtual void setOutputs() TOV_ABSTRACT;
        virtual void render() TOV_ABSTRACT;

    protected:
        void setOutput(const std::string& name, void* resource);
        void setInput(const std::string& name);

        template <class ResourceType>
        auto getResource(const std::string& name) const -> ResourceType*
        {
            auto ptr = mResourceBucket.getResource(name).getResource();
            return reinterpret_cast<ResourceType*>(ptr);
        }

    protected:
        pipeline::Framebuffer* mFramebuffer = nullptr;
        pipeline::Program* mProgram = nullptr;
        pipeline::ProgramInstance* mProgramInstance = nullptr;

    private:
        ResourceBucket& mResourceBucket;
    };

    TOV_NAMESPACE_END // producers
    TOV_NAMESPACE_END // rendering
}

#endif
