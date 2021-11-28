#include "Framework.h"

#include "Enemy.h"

Enemy::Enemy(fw::Mesh* pMesh, fw::ShaderProgram* pShader, fw::Texture* pTexture, vec2 pos, std::string spriteName, SpriteSheet* spriteSheet)
    : GameObject( pMesh, pShader, pTexture, pos,spriteName,spriteSheet )
{
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
}
