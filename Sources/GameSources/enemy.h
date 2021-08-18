#pragma once

#include <DirectXMath.h>
#include "OBJ3D.h"
#include "Model.h"



class Enemy : public OBJ3D
{
public:
	Enemy();
	~Enemy() { UnInit(); }

	void Update();
	void Render();

	void Move();

private:
	std::unique_ptr<Model> model;

	DirectX::XMFLOAT3 direction;

public:
	void SetDirection(DirectX::XMFLOAT3 dir) { direction = dir; }
	DirectX::XMFLOAT3 GetDirection() { return direction; }

};
