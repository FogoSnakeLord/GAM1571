#pragma once

#include "Framework.h"

class PlayerController
{
public:
    PlayerController();

    void OnEvent(fw::Event* pEvent);

    bool IsRightHeld();
    bool IsLeftHeld();
    bool IsUpHeld();
    bool IsDownHeld();
protected:
    bool m_Right;
    bool m_Left;
    bool m_Up;
    bool m_Down;
};
