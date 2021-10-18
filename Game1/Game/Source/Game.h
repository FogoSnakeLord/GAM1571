#pragma once

#include "Framework.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Pickup.h"
typedef fw::vec2 vec2;

class Game : public fw::GameCore
{
public:
    Game(fw::FWCore& fwCore);
    virtual ~Game() override;

    void Init();
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

protected:
    fw::FWCore& m_FWCore;
    fw::ImGuiManager* m_pImGuiManager;

    float m_TimePassed;
    Player* m_Player;
    Enemy* m_Enemy;
    Pickup* m_Pickup;
    std::map<std::string, fw::Mesh*> m_Meshes;
    fw::ShaderProgram* m_pBasicShader;

    vec2 m_Position;
};
