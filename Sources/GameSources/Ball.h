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

	bool pull = false;	//引かれているかのフラグ
	bool hit = false;	//当たっているか

	DirectX::XMFLOAT3 nextPos;	//目的地
	DirectX::XMFLOAT3 oldPos;	//引かれ始めの場所

	bool  collisionDraw = true;

	//当たり判定(他の物に必要)
	std::unique_ptr<CollisionPrimitive> collisionModel;
	float collisionScale = 100.0f;

public:
	void SetDirection(DirectX::XMFLOAT3 dir) { direction = dir; }
	DirectX::XMFLOAT3 GetDirection() { return direction; }

};
