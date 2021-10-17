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
    m_pImGuiManager = new fw::ImGuiManager( &m_FWCore );
    m_pImGuiManager->Init();

    glPointSize( 10 );

    std::vector<float> test = { 0.0f,0.0f,0.5f,   0.5f,0.5f,1.0f,   -0.5f,0.5f,0.2f };
    std::vector<float> testTwo = { 0.0f,-0.5f,0.5f,   0.5f,0.0f,1.0f,   -0.5f,0.0f,0.2f };
    std::vector<float> testThree = { 0.0f,-1.0f,0.5f,   0.5f,-0.5f,1.0f,   -0.5f,-0.5f,0.2f };
    m_Meshes["Player"] = new fw::Mesh(3, test);
    m_Meshes["Enemy"] = new fw::Mesh(3, testTwo);
    m_Meshes["Pickup"] = new fw::Mesh(3, testThree);

    m_pBasicShader = new fw::ShaderProgram( "Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag" );
}

void Game::Update(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );
    ImGui::ShowDemoWindow();

    m_TimePassed += deltaTime;

    float speed = 1.0f;

    if( m_FWCore.IsKeyDown('D') )
    {
        m_Position.x += speed * deltaTime;
    }
    if (m_FWCore.IsKeyDown('S'))
    {
        m_Position.y -= speed * deltaTime;
    }
    if (m_FWCore.IsKeyDown('A'))
    {
        m_Position.x -= speed * deltaTime;
    }
    if (m_FWCore.IsKeyDown('W'))
    {
        m_Position.y += speed * deltaTime;
    }
    ImGui::DragFloat( "Position X", &m_Position.x, 0.02f, -1.0f, 1.0f );
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

    m_Meshes["Player"]->Draw( m_pBasicShader );
    m_Meshes["Enemy"]->Draw(m_pBasicShader);
    m_Meshes["Pickup"]->Draw(m_pBasicShader);

    m_pImGuiManager->EndFrame();
}
