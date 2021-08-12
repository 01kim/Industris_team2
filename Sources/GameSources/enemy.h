#pragma once

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


};
