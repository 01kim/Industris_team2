#include <FrameWork.h>

#include "enemy.h"
#include "CameraSystem.h"

Enemy::Enemy()
{
	Init();
}


void Enemy::Update()
{

}


void Enemy::Render()
{
	model->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
	model->Render(GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
		DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), GetColor(), FrameWork::GetInstance().GetElapsedTime());
}


void Enemy::Move()
{

}