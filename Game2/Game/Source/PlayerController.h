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

protected:
    bool m_Up;
    bool m_Down;
    bool m_Left;
    bool m_Right;
};
