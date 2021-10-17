#pragma once

#include "Framework.h"

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

    std::map<std::string, fw::Mesh*> m_Meshes;
    fw::ShaderProgram* m_pBasicShader;

    vec2 m_Position;
};
