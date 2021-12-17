#include "Framework.h"

#include "PlayerController.h"

PlayerController::PlayerController()
{
    m_Up = false;
    m_Down = false;
    m_Left = false;
    m_Right = false;
    m_LeftShoot = false;
    m_RightShoot = false;
    m_UpShoot = false;
    m_DownShoot = false;
}

void PlayerController::OnEvent(fw::Event* pEvent)
{
    if( pEvent->GetEventType() == fw::EventType::Input )
    {
        fw::InputEvent* pInputEvent = static_cast<fw::InputEvent*>( pEvent );

        if( pInputEvent->GetDeviceType() == fw::DeviceType::Keyboard )
        {
            if( pInputEvent->GetInputState() == fw::InputState::Pressed )
            {
                if( pInputEvent->GetID() == 'W' || pInputEvent->GetID() == VK_UP )      { m_Up = true; }
                if( pInputEvent->GetID() == 'S' || pInputEvent->GetID() == VK_DOWN )    { m_Down = true; }
                if( pInputEvent->GetID() == 'A' || pInputEvent->GetID() == VK_LEFT )    { m_Left = true; }
                if( pInputEvent->GetID() == 'D' || pInputEvent->GetID() == VK_RIGHT )   { m_Right = true; }
                if (pInputEvent->GetID() == 'J')    { m_LeftShoot = true; }
                if (pInputEvent->GetID() == 'K') { m_DownShoot = true; }
                if (pInputEvent->GetID() == 'L') { m_RightShoot = true; }
                if (pInputEvent->GetID() == 'I') { m_UpShoot = true; }
            }

            if( pInputEvent->GetInputState() == fw::InputState::Released )
            {
                if( pInputEvent->GetID() == 'W' || pInputEvent->GetID() == VK_UP )      { m_Up = false; }
                if( pInputEvent->GetID() == 'S' || pInputEvent->GetID() == VK_DOWN )    { m_Down = false; }
                if( pInputEvent->GetID() == 'A' || pInputEvent->GetID() == VK_LEFT )    { m_Left = false; }
                if( pInputEvent->GetID() == 'D' || pInputEvent->GetID() == VK_RIGHT )   { m_Right = false; }
                if (pInputEvent->GetID() == 'J') { m_LeftShoot = false; }
                if (pInputEvent->GetID() == 'K') { m_DownShoot = false; }
                if (pInputEvent->GetID() == 'L') { m_RightShoot = false; }
                if (pInputEvent->GetID() == 'I') { m_UpShoot = false; }
            }
        }
    }
}

bool PlayerController::IsUpHeld()
{
    return m_Up;
}

bool PlayerController::IsDownHeld()
{
    return m_Down;
}

bool PlayerController::IsLeftHeld()
{
    return m_Left;
}

bool PlayerController::IsRightHeld()
{
    return m_Right;
}

bool PlayerController::IsLeftShooting()
{
    return m_LeftShoot;
}

bool PlayerController::IsRightShooting()
{
    return m_RightShoot;
}

bool PlayerController::IsUpShooting()
{
    return m_UpShoot;
}

bool PlayerController::IsDownShooting()
{
    return m_DownShoot;
}
