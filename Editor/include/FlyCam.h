/*****************************************************************************
 * FlyCam
 * Created by James Mills on 7/04/2026.
 *****************************************************************************/

#pragma once

#include "Graphics/Camera.h"

namespace Catalyst::Editor
{
    using Graphics::Camera;

    class FlyCam : public Camera
    {
    public:
        FlyCam();

    public:
        virtual void Tick() override;

    protected:
        float m_moveSpeed;

    };
}
