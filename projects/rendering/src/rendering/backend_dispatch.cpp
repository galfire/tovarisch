#include "rendering/backend_dispatch.h"

#include "rendering/backend.h"

#include "rendering/commands/commands.h"

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)

    void BackendDispatch::ApplyViewport(const void* data)
    {
        auto command = reinterpret_cast<const commands::ApplyViewport*>(data);
        backend::ApplyViewport();
    }

    TOV_NAMESPACE_END // rendering
}
