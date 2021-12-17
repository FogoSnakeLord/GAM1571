#pragma once

#include "Framework.h"

class PlayerController
{
public:
    PlayerController();

    void OnEvent(fw::Event* pEvent);

    bool IsUpHeld();
    bool IsDownHeld();
    bool IsLeftHeld();
    bool IsRightHeld();
    bool IsLeftShooting();
    bool IsRightShooting();
    bool IsUpShooting();
    bool IsDownShooting();
protected:
    bool m_Up;
    bool m_Down;
    bool m_Left;
    bool m_Right;
    bool m_LeftShoot;
    bool m_RightShoot;
    bool m_UpShoot;
    bool m_DownShoot;
};
