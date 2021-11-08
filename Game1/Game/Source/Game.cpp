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
    , m_BulletDelay(0.0f)
    , m_Round(0)
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
    RoundStart(m_Round);
    m_pBasicShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag");
}

void Game::Update(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );
    ImGui::ShowDemoWindow();
    ImGui::Text("Score: %d", m_Player->GetScore());
    ImGui::Text("Round: %d", m_Round+1);
    ImGui::Text("Enemies Left: %d", (m_NumEnemies - m_NumEnemiesInactive));
    ImGui::Text("Pickups Left: %d", (m_NumPickups - m_NumPickupsInactive));
    if (ImGui::Button("Round 1")) {
        m_Round = 0;
        RoundStart(m_Round);
    }
    if (ImGui::Button("Next Round")&&m_Round!=2) {
        m_Round++;
        RoundStart(m_Round);
    }
    
    float vary = m_Player->GetVary();
    ImGui::SliderFloat("Redness",&vary,0.0f,1.0f);
    m_Player->SetVary(vary);
    m_TimePassed += deltaTime;

    m_Player->Update(deltaTime);
    m_Player->SetVary(m_Player->GetVary() + (0.1 * deltaTime));
    if (m_Player->GetVary() > 1) {
        m_Player->SetVary(0.0f);
    }
    if (m_Player->GetPosition().x > 1.0f) {
        m_Player->SetPosition(vec2(1.0f, m_Player->GetPosition().y));
    }
    else if (m_Player->GetPosition().x < -1.0f) {
        m_Player->SetPosition(vec2(-1.0f, m_Player->GetPosition().y));
    }
    if (m_Player->GetPosition().y > 1.0f) {
        m_Player->SetPosition(vec2(m_Player->GetPosition().x, 1.0f));
    }
    else if (m_Player->GetPosition().y < -1.0f) {
        m_Player->SetPosition(vec2(m_Player->GetPosition().x, -1.0f));
    }

    if (m_BulletDelay <= 0.0f) {
        vec2 dir;
        if (m_FWCore.IsKeyDown('I') && m_FWCore.IsKeyDown('J')) {
            dir.Set(-1.0f, 1.0f);
        }
        else if (m_FWCore.IsKeyDown('I') && m_FWCore.IsKeyDown('L')) {
            dir.Set(1.0f, 1.0f);
        }
        else if (m_FWCore.IsKeyDown('K') && m_FWCore.IsKeyDown('L')) {
            dir.Set(1.0f, -1.0f);
        }
        else if (m_FWCore.IsKeyDown('K') && m_FWCore.IsKeyDown('J')) {
            dir.Set(-1.0f, -1.0f);
        }
        else if (m_FWCore.IsKeyDown('I')) {
            dir.Set(0.0f, 1.0f);
        }
        else if (m_FWCore.IsKeyDown('J')) {
            dir.Set(-1.0f, 0.0f);
        }
        else if (m_FWCore.IsKeyDown('K')) {
            dir.Set(0.0f, -1.0f);
        }
        else if (m_FWCore.IsKeyDown('L')) {
            dir.Set(1.0f, 0.0f);
        }
        if (!(dir.x == 0.0f && dir.y == 0.0f)) {
            m_ActiveGameObjects.push_back(m_BulletPool.GetBullet(dir, m_Player->GetPosition()));
            m_BulletDelay = 0.5f;
        }
    }
    m_BulletDelay -= deltaTime;
    //Cycle through Each active game object and check if they collide with the player if they are an enemy or a pickup
    //If they are a bullet check for collisions with all other gameobjects that aren't bullets or players
    for (int i = m_ActiveGameObjects.size()-1; i >= 0; i--) {
        GameObject* temp = m_ActiveGameObjects[i];
        if (temp->GetPosition().x > 1.0f) {
            temp->SetPosition(vec2(1.0f,temp->GetPosition().y));
            if (Bullet* bullet = dynamic_cast <Bullet*> (temp)) {
                
            }
        }
        else if (temp->GetPosition().x < -1.0f ) {
            temp->SetPosition(vec2(-1.0f, temp->GetPosition().y));
        }
        if (temp->GetPosition().y > 1.0f) {
            temp->SetPosition(vec2(temp->GetPosition().x, 1.0f));
        }
        else if (temp->GetPosition().y < -1.0f) {
            temp->SetPosition(vec2(temp->GetPosition().x, -1.0f));
        }
        if (Enemy* enemy = dynamic_cast <Enemy*> (temp)) {
            enemy->Update(deltaTime);
        }
        if (((m_Player->GetPosition()).DistanceTo(temp->GetPosition())) < m_CollisionDistance) {
            if (Enemy* enemy = dynamic_cast <Enemy*> (temp)) {
                m_EnemyPool.ReturnToPool(enemy);
                m_Player->Respawn();
                m_ActiveGameObjects.erase(m_ActiveGameObjects.begin() + i);
                m_NumEnemiesInactive++;
            }
            else if (Pickup* pickup = dynamic_cast <Pickup*> (temp)) {
                m_Player->ChangeScore(1);
                m_NumPickupsInactive++;
                m_PickupPool.ReturnToPool(pickup);
                m_ActiveGameObjects.erase(m_ActiveGameObjects.begin() + i);
            }
        }
        if (Bullet* bullet = dynamic_cast <Bullet*> (temp)) {
            bullet->Update(deltaTime);
            for (int j = m_ActiveGameObjects.size() - 1; j >= 0; j--) {
                GameObject* temp2 = m_ActiveGameObjects[j];
                if (((bullet->GetPosition()).DistanceTo(temp2->GetPosition())) < m_CollisionDistance) {
                    if (Enemy* enemy = dynamic_cast <Enemy*> (temp2)) {
                        m_EnemyPool.ReturnToPool(enemy);
                        m_BulletPool.ReturnToPool(bullet);
                        m_ActiveGameObjects.erase(m_ActiveGameObjects.begin() + i);
                        m_ActiveGameObjects.erase(m_ActiveGameObjects.begin() + j);
                        i = m_ActiveGameObjects.size() - 1;
                        m_NumEnemiesInactive++;
                    }
                    else if (Pickup* pickup = dynamic_cast <Pickup*> (temp2)) {
                        m_PickupPool.ReturnToPool(pickup);
                        m_BulletPool.ReturnToPool(bullet);
                        m_ActiveGameObjects.erase(m_ActiveGameObjects.begin() + i);
                        m_ActiveGameObjects.erase(m_ActiveGameObjects.begin() + j);
                        i = m_ActiveGameObjects.size() - 1;
                        m_NumPickupsInactive++;
                    }
                }
            }
            if (bullet->GetPosition().x >= 1.0f || bullet->GetPosition().x <= -1.0f || bullet->GetPosition().y >= 1.0f || bullet->GetPosition().y <= -1.0f) {
                m_BulletPool.ReturnToPool(bullet);
                m_ActiveGameObjects.erase(m_ActiveGameObjects.begin() + i);
            }
        }
    }
    if (m_NumEnemies==m_NumEnemiesInactive&&m_NumPickups==m_NumPickupsInactive&&m_Round!=2) {
        m_Round++;
        RoundStart(m_Round);
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

    m_Player->Draw(m_pBasicShader,m_TimePassed);

    for (int i = m_ActiveGameObjects.size() - 1; i >= 0; i--) {
        m_ActiveGameObjects[i]->Draw(m_pBasicShader, m_TimePassed);
    }
    m_pImGuiManager->EndFrame();
}

void Game::RoundStart(int roundNum)
{
    m_ActiveGameObjects.clear();
    Random* r = new Random();
    m_NumPickups = r->RandInt(1, 20);
    m_NumEnemies = r->RandInt(1, 20);
    if (roundNum == 0) {
        for (int i = 0; i < m_NumEnemies; i++) {
            m_ActiveGameObjects.push_back(m_EnemyPool.GetEnemy(0));
        }
    }
    else if (roundNum == 1) {
        for (int i = 0; i < m_NumEnemies; i++) {
            m_ActiveGameObjects.push_back(m_EnemyPool.GetEnemy(1));
        }
    }
    else {
        for (int i = 0; i < m_NumEnemies; i++) {
            m_ActiveGameObjects.push_back(m_EnemyPool.GetEnemy(r->RandInt(0, 1)));
        }
    }
    for (int i = 0; i < m_NumPickups; i++) {
        m_ActiveGameObjects.push_back(m_PickupPool.GetPickup());
    }
    m_NumEnemiesInactive = 0;
    m_NumPickupsInactive = 0;
    delete r;
}
