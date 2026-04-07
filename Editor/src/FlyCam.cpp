/*****************************************************************************
 * FlyCam
 * Created by James Mills on 7/04/2026.
 *****************************************************************************/

#include "FlyCam.h"

#include "Vector3.h"

namespace Catalyst::Editor
{
    FlyCam::FlyCam()
        : m_moveSpeed{ 10.f }
    {
        m_view = Matrix4::MakeTransform({ 0.f, 0.f, -10.f }, { 0.f, 0.f, 0.f }, { 1.f });
    }

    void FlyCam::Tick()
    {

    }
}
