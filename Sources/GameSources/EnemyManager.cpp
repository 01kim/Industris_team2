
#include "EnemyManager.h"


void EnemyManager::Update()
{
    for (Enemy* enemy : enemies)
    {
        enemy->Update();
    }
}


void EnemyManager::Render()
{
    for (Enemy* enemy : enemies)
    {
        enemy->Render();
    }
}


void EnemyManager::Register(DirectX::XMFLOAT3 pos)
{
    Enemy* enemy = new Enemy();

    enemy->SetPos(pos);

    enemies.emplace_back(enemy);
}