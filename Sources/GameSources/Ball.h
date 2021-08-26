#pragma once

#include <DirectXMath.h>
#include "OBJ3D.h"
#include "Model.h"

#include "Collision.h"

class Ball : public OBJ3D
{
public:
	Ball();
	~Ball() { UnInit(); }

	static Ball& Instance()
	{
		static Ball instance;
		return instance;
	}

	void Update();
	void Render();
	void DebugImgui();

	void Move();

	void Pull(DirectX::XMFLOAT3 pos);
	bool judgeBallvsEnemy(DirectX::XMFLOAT3 pos,float scale);
	bool JudgeArrival();

	bool isPull(){ return pull; }

private:
	std::unique_ptr<Model> model;

	DirectX::XMFLOAT3 direction;

	bool pull = false;	//������Ă��邩�̃t���O
	bool hit = false;	//�������Ă��邩

	DirectX::XMFLOAT3 nextPos;	//�ړI�n
	DirectX::XMFLOAT3 oldPos;	//������n�߂̏ꏊ

	bool  collisionDraw = true;

	//�����蔻��(���̕��ɕK�v)
	std::unique_ptr<CollisionPrimitive> collisionModel;
	float collisionScale = 100.0f;

public:
	void SetDirection(DirectX::XMFLOAT3 dir) { direction = dir; }
	DirectX::XMFLOAT3 GetDirection() { return direction; }

};
