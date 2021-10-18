#include "Framework.h"

#include "Game.h"

Game::Game(fw::FWCore& fwCore)
    : m_FWCore( fwCore )
    , m_pImGuiManager( nullptr )
    , m_TimePassed( 0.0f )
    , m_pBasicShader( nullptr )
    , m_Position( 0.0f, 0.0f )
{
    
}

Game::~Game()
{
    delete m_pBasicShader;

    //for( auto& it = m_Meshes.begin(); it != m_Meshes.end(); it++ )
    //{
    //    delete it->second;
    //}

    for( auto& it : m_Meshes )
    {
        delete it.second;
    }

    delete m_pImGuiManager;
}

void Game::Init()
{
    m_pImGuiManager = new fw::ImGuiManager(&m_FWCore);
    m_pImGuiManager->Init();

    glPointSize(10);
    /*Butterfly
    0.0f,0.0f,1.0f, -0.05f, 0.05f,1.0f, 
    -0.05f, 0.05f, 1.0f, -0.075f, -0.075f, 1.0f,
        -0.075f, -0.075f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 0.075f, -0.075f, 1.0f,
        0.075f, -0.075f, 1.0f, 0.05f, 0.05f, 1.0f,
        0.05f, 0.05f, 1.0f, 0.0f, 0.0f, 1.0f*/
    /*Rupee
    0.0f,0.0f,1.0f, 0.1f,-0.1f,1.0f,
    0.1f,-0.1f,1.0f, 0.1f,-0.2f,1.0f,
    0.1f,-0.2f,1.0f, 0.0f,-0.3f,1.0f,
    0.0f,-0.3f,1.0f, -0.1f,-0.2f,1.0f,
    -0.1f,-0.2f,1.0f, -0.1f,-0.1f,1.0f,
    -0.1f,-0.1f,1.0f, 0.0f,0.0f,1.0f
    */

    /*Trapezoid
    0.0f,0.0f,1.0f, 0.05f,0.05f,1.0f,
    0.05f,0.05f,1.0f, 0.1f,0.05f,1.0f,
    0.1f,0.05f,1.0f, 0.15f,0.0f,1.0f,
    0.15f,0.0f,1.0f, 0.0f,0.0f,1.0f,
    */

    // BOX 0.10f,0.10f,1.0f, -0.10f, 0.10f,1.0f,-0.10f, 0.10f,1.0f, -0.10f,-0.1f,1.0f, -0.10f,-0.1f,1.0f, 0.10f,-0.10f,1.0f,0.10f,-0.1f,1.0f, 0.10f,0.10f,1.0f
    //0.0f, 0.0f, 1.0f, 0.05f, 0.05f, 1.0f, -0.05f, 0.05f, 1.0f , 0.0f, 0.0f, 1.0f, 0.075, 0.075, 1.0f, -0.075, 0.075, 1.0f
    // 0.0f, 0.0f, 1.0f ,0.0f ,0.0f, 1.0f, 0.05f, 0.05f, 0.5f, 0.5f,0.5f, 0.5f, -0.05f, 0.05f, 1.0f, 0.0f, 0.0f, 1.0f 
    m_Player = new Player(std::vector<float>{ 
        0.0f,0.0f,1.0f, -0.05f, 0.05f,1.0f, 
        -0.05f, 0.05f, 1.0f, -0.075f,-0.075f,1.0f,
        -0.075f, -0.075f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 0.075f, -0.075f, 1.0f,
        0.075f, -0.075f, 1.0f, 0.05f, 0.05f, 1.0f,
        0.05f, 0.05f, 1.0f, 0.0f, 0.0f, 1.0f}, 12, m_FWCore);

    m_Enemy = new Enemy(std::vector<float>{
        0.0f, 0.0f, 1.0f, 0.05f, 0.05f, 1.0f,
        0.05f, 0.05f, 1.0f, 0.1f, 0.05f, 1.0f,
        0.1f, 0.05f, 1.0f, 0.15f, 0.0f, 1.0f,
        0.15f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, }, 8);

    m_Pickup = new Pickup(std::vector<float>{ 
        0.0f, 0.0f, 1.0f, 0.02f, -0.02f, 1.0f,
        0.02f, -0.02f, 1.0f, 0.02f, -0.04f, 1.0f,
        0.02f, -0.04f, 1.0f, 0.0f, -0.06f, 1.0f,
        0.0f, -0.06f, 1.0f, -0.02f, -0.04f, 1.0f,
        -0.02f, -0.04f, 1.0f, -0.02f, -0.02f, 1.0f,
        -0.02f, -0.02f, 1.0f, 0.0f, 0.0f, 1.0f }, 12);

    m_pBasicShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag");
}

void Game::Update(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );
    ImGui::ShowDemoWindow();
    ImGui::Text("Score: %d", m_Player->GetScore());

    m_TimePassed += deltaTime;

    m_Player->Update(deltaTime);
    if (m_Enemy->GetIsActive()) {
        if (((m_Player->GetPosition()).DistanceTo(m_Enemy->GetPosition())) < 0.05f) {
            m_Enemy->Deactivate();
            m_Player->Respawn();
        }
    }
    
    if (m_Pickup->GetIsActive()) {
        if (((m_Player->GetPosition()).DistanceTo(m_Pickup->GetPosition())) < 0.05f) {
            m_Pickup->Deactivate();
            m_Player->ChangeScore(1);
        }
    }

    float speed = 1.0f;
    vec2 temp = m_Player->GetPosition();
    ImGui::DragFloat( "Position X", &temp.x , 0.02f, -1.0f, 1.0f );
    ImGui::DragFloat("Position Y", &temp.y, 0.02f, -1.0f, 1.0f);
}

void Game::Draw()
{
    glClearColor( 0.0f, 0.0f, 0.2f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    glUseProgram( m_pBasicShader->GetProgram() );

    GLint u_Offset = glGetUniformLocation( m_pBasicShader->GetProgram(), "u_Offset" );
    glUniform2f( u_Offset, m_Position.x, m_Position.y );

    GLint u_Time = glGetUniformLocation( m_pBasicShader->GetProgram(), "u_Time" );
    glUniform1f( u_Time, m_TimePassed );

    m_Player->Draw(m_pBasicShader,m_TimePassed);
    if (m_Enemy->GetIsActive()) {
        m_Enemy->Draw(m_pBasicShader, m_TimePassed);
    }
    if (m_Pickup->GetIsActive()) {
        m_Pickup->Draw(m_pBasicShader, m_TimePassed);
    }
    m_pImGuiManager->EndFrame();
}
