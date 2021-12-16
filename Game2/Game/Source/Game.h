#pragma once

#include "Framework.h"
#include "DataTypes.h"

class GameObject;
class PlayerController;
class Tilemap;

class Game : public fw::GameCore
{
public:
    Game(fw::FWCore& fwCore);
    virtual ~Game() override;

    void Init();
    virtual void OnEvent(fw::Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    void CheckForCollisions();

    fw::Mesh* GetMesh(std::string name) { return m_Meshes[name]; }
    fw::ShaderProgram* GetShader() { return m_pBasicShader; }
    fw::SpriteSheet* GetSpriteSheet() { return m_pSpriteSheet; }

protected:
    fw::FWCore& m_FWCore;
    fw::ImGuiManager* m_pImGuiManager;

    PlayerController* m_pPlayerController;

    float m_TimePassed;

    std::map<std::string, fw::Mesh*> m_Meshes;
    fw::ShaderProgram* m_pBasicShader;
    fw::Texture* m_pTexture;
    fw::Texture* m_pTexture2;
    fw::SpriteSheet* m_pSpriteSheet;

    Tilemap* m_pTilemap;

    GameObject* m_pPlayer;
    GameObject* m_pEnemy;
};
