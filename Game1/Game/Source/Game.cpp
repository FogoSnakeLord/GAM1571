#include "Framework.h"

#include "Game.h"
#include "Random.h"
Game::Game(fw::FWCore& fwCore)
    : m_FWCore( fwCore )
    , m_pImGuiManager( nullptr )
    , m_TimePassed( 0.0f )
    , m_pBasicShader( nullptr )
    , m_Position( 0.0f, 0.0f )
    , m_CollisionDistance(0.1f)
    , m_NumPickupsInactive(0)
    , m_NumEnemiesInactive(0)
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

    Random* r = new Random();
    m_NumPickups = r->RandInt(1, 20);
    m_NumEnemies = r->RandInt(1, 20);
    delete r;

    /*Butterfly Ship
        -0.05f, 0.05f, 1.0f, -0.075f, -0.075f, 1.0f,
        -0.075f, -0.075f, 1.0f, 0.05f, 0.05f, 1.0f,
        0.05f, 0.05f, 1.0f, 0.075f, -0.075f, 1.0f,
        0.075f, -0.075f, 1.0f, -0.05f, 0.05f, 1.0f,
        -0.05f, 0.05f, 1.0f, 0.05f, 0.05f, 1.0f
    */

    /*Not-A-Rupee
    0.0f,0.0f,1.0f, 0.1f,-0.1f,1.0f,
    0.1f,-0.1f,1.0f, 0.1f,-0.2f,1.0f,
    0.1f,-0.2f,1.0f, 0.0f,-0.3f,1.0f,
    0.0f,-0.3f,1.0f, -0.1f,-0.2f,1.0f,
    -0.1f,-0.2f,1.0f, -0.1f,-0.1f,1.0f,
    -0.1f,-0.1f,1.0f, 0.0f,0.0f,1.0f
    */

    /*Trapezoid Enemy
    0.0f,0.0f,1.0f, 0.05f,0.05f,1.0f,
    0.05f,0.05f,1.0f, 0.1f,0.05f,1.0f,
    0.1f,0.05f,1.0f, 0.15f,0.0f,1.0f,
    0.15f,0.0f,1.0f, 0.0f,0.0f,1.0f,
    */

    // BOX 0.10f,0.10f,1.0f, -0.10f, 0.10f,1.0f,-0.10f, 0.10f,1.0f, -0.10f,-0.1f,1.0f, -0.10f,-0.1f,1.0f, 0.10f,-0.10f,1.0f,0.10f,-0.1f,1.0f, 0.10f,0.10f,1.0f

    m_Player = new Player(std::vector<float>{ 
        -0.05f, 0.05f, 1.0f, -0.075f, -0.075f, 1.0f,
            -0.075f, -0.075f, 1.0f, 0.05f, 0.05f, 1.0f,
            0.05f, 0.05f, 1.0f, 0.075f, -0.075f, 1.0f,
            0.075f, -0.075f, 1.0f, -0.05f, 0.05f, 1.0f,
            -0.05f, 0.05f, 1.0f, 0.05f, 0.05f, 1.0f}, 10, m_FWCore);
    for (int i = 0; i < m_NumEnemies; i++) {
        m_Enemies[i] = new Enemy(std::vector<float>{
            0.0f, 0.0f, 1.0f, 0.05f, 0.05f, 1.0f,
                0.05f, 0.05f, 1.0f, 0.1f, 0.05f, 1.0f,
                0.1f, 0.05f, 1.0f, 0.15f, 0.0f, 1.0f,
                0.15f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, }, 8);
    }
    for (int i = 0; i < m_NumPickups; i++) {
        m_Pickups[i] = new Pickup(std::vector<float>{
            0.0f, 0.0f, 1.0f, 0.02f, -0.02f, 1.0f,
                0.02f, -0.02f, 1.0f, 0.02f, -0.04f, 1.0f,
                0.02f, -0.04f, 1.0f, 0.0f, -0.06f, 1.0f,
                0.0f, -0.06f, 1.0f, -0.02f, -0.04f, 1.0f,
                -0.02f, -0.04f, 1.0f, -0.02f, -0.02f, 1.0f,
                -0.02f, -0.02f, 1.0f, 0.0f, 0.0f, 1.0f }, 12);
    }
    m_pBasicShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag");
}

void Game::Update(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );
    ImGui::ShowDemoWindow();
    ImGui::Text("Score: %d", m_Player->GetScore());
    ImGui::Text("Enemies Left: %d", (m_NumEnemies-m_NumEnemiesInactive));
    ImGui::Text("Pickups Left: %d", (m_NumPickups - m_NumPickupsInactive));

    m_TimePassed += deltaTime;

    m_Player->Update(deltaTime);
    for (int i = 0; i < m_NumEnemies; i++) {
        if (m_Enemies[i]->GetIsActive()) {
            if (((m_Player->GetPosition()).DistanceTo(m_Enemies[i]->GetPosition())) < m_CollisionDistance) {
                m_Enemies[i]->Deactivate();
                m_Player->Respawn();
                m_NumEnemiesInactive++;
            }
        }
    }
    for (int i = 0; i < m_NumPickups; i++) {
        if (m_Pickups[i]->GetIsActive()) {
            if (((m_Player->GetPosition()).DistanceTo(m_Pickups[i]->GetPosition())) < m_CollisionDistance) {
                m_Pickups[i]->Deactivate();
                m_Player->ChangeScore(1);
                m_NumPickupsInactive++;
            }
        }
    }
    float speed = 1.0f;
    vec2 temp = m_Player->GetPosition();
    ImGui::DragFloat( "Position X", &temp.x , 0.02f, -1.0f, 1.0f );
    ImGui::DragFloat("Position Y", &temp.y, 0.02f, -1.0f, 1.0f);
}

void Game::Draw()
{
    glClearColor( 0.7f, 0.6f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    glUseProgram( m_pBasicShader->GetProgram() );

    GLint u_Offset = glGetUniformLocation( m_pBasicShader->GetProgram(), "u_Offset" );
    glUniform2f( u_Offset, m_Position.x, m_Position.y );

    GLint u_Time = glGetUniformLocation( m_pBasicShader->GetProgram(), "u_Time" );
    glUniform1f( u_Time, m_TimePassed );

    m_Player->Draw(m_pBasicShader,m_TimePassed);
    for (int i = 0; i < m_NumEnemies; i++) {
        if (m_Enemies[i]->GetIsActive()) {
            m_Enemies[i]->Draw(m_pBasicShader, m_TimePassed);
        }
    }
    for (int i = 0; i < m_NumPickups; i++) {
        if (m_Pickups[i]->GetIsActive()) {
            m_Pickups[i]->Draw(m_pBasicShader, m_TimePassed);
        }
    }
    m_pImGuiManager->EndFrame();
}
