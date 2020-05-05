#include "rendering_gl/pipeline/program.h"

#include "rendering_gl/pipeline/program_instance.h"

#include <tov/math/matrix.h>
#include <tov/math/vector.h>

#include <iostream>

namespace tov
{
    TOV_NAMESPACE_BEGIN(rendering)
    TOV_NAMESPACE_BEGIN(gl)
    TOV_NAMESPACE_BEGIN(pipeline)

    Program::Program()
        : rendering::pipeline::Program()
    {}

    Program::~Program()
    {}

    auto Program::instantiateImpl() const -> rendering::pipeline::ProgramInstance*
    {
        return new ProgramInstance(mConstantBufferSize, mConstantBufferOffsetMap);
    }

    TOV_NAMESPACE_END // pipeline
    TOV_NAMESPACE_END // gl
    TOV_NAMESPACE_END // rendering
}
