#pragma once

#include <vector>
#include <DirectXMath.h>
#include "enemy.h"


class EnemyManager
{
private:
	EnemyManager() {}
	~EnemyManager() {}

public:
	static EnemyManager& Instance()
	{
		static EnemyManager instance;
		return instance;
	}


	void Update();
	void Render();

	void Register(DirectX::XMFLOAT3 pos);

private:
	std::vector<Enemy*> enemies;

};
