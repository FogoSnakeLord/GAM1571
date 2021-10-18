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
    Pickup* m_Pickups[20];
    std::map<std::string, fw::Mesh*> m_Meshes;
    fw::ShaderProgram* m_pBasicShader;
    float m_CollisionDistance;
    int m_NumEnemies;
    Enemy* m_Enemies[20];
    int m_NumPickups;
    int m_NumPickupsInactive;
    int m_NumEnemiesInactive;
    vec2 m_Position;
};
