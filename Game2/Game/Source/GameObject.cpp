#include "Framework.h"

#include "GameObject.h"

GameObject::GameObject(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, std::string spriteName, SpriteSheet* spriteSheet)
    : m_pMesh( pMesh )
    , m_pShader( pShader )
    , m_pTexture( pTexture )
    , m_Position( pos )
    , m_Radius( 0.4f ) // TODO: Customize Radius.
    , m_pSpriteSheet(spriteSheet)
    , m_SpriteName(spriteName)
{
    //std::vector<fw::VertexFormat> spriteVerts =
    //{
    //    { vec2( 0.0f,1.0f),  255,255,255,255,  vec2(0.0f,1.0f) * m_pSpriteSheet->GetSpriteInfo("player_06")->UvScale + m_pSpriteSheet->GetSpriteInfo(spriteName)->UvOffset}, // top left
    //    { vec2( 0.0f,0.0f),  255,255,255,255,  vec2(0.0f,0.0f) * m_pSpriteSheet->GetSpriteInfo("player_06")->UvScale + m_pSpriteSheet->GetSpriteInfo(spriteName)->UvOffset}, // bottom left
    //    { vec2( 1.0f,1.0f),  255,255,255,255,  vec2(1.0f,1.0f) * m_pSpriteSheet->GetSpriteInfo("player_06")->UvScale + m_pSpriteSheet->GetSpriteInfo(spriteName)->UvOffset}, // top right
    //    { vec2( 1.0f,0.0f),  255,255,255,255,  vec2(1.0f,0.0f) * m_pSpriteSheet->GetSpriteInfo("player_06")->UvScale + m_pSpriteSheet->GetSpriteInfo(spriteName)->UvOffset}, // bottom right
    //};
    //m_pMesh = new fw::Mesh( GL_TRIANGLE_STRIP, spriteVerts );
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw(vec2 projScale, vec2 camPos)
{
    vec2 m_Scale = vec2( 1, 1 );
    vec2 scale = (m_pSpriteSheet->GetSpriteInfo(m_SpriteName))->UvScale;
    vec2 offset = (m_pSpriteSheet->GetSpriteInfo(m_SpriteName))->UvOffset;
    m_pMesh->Draw( m_pShader, m_pTexture, projScale, camPos, m_Scale, m_Position, 0.0f, scale , offset);
}

bool GameObject::IsCollidingWith(GameObject* pOtherObject)
{
    assert( pOtherObject != nullptr );

    float distance = m_Position.DistanceTo( pOtherObject->m_Position );
    float combinedRadii = m_Radius + pOtherObject->m_Radius;

    if( distance < combinedRadii )
        return true;

    return false;
}
