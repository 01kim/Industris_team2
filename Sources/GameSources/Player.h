#pragma once
#include "OBJ3D.h"
#include "Model.h"

class Player
{
public:
	Player() {}
	~Player() {}

	void Init();
	void UnInit();
	void Update();
	void Draw();
	void ImguiDebug();
private:
	// 移動処理
	void Move(float vx, float vz, float speed);

	// プレイヤーが進行方向に向くようにする
	void Turn(float elapsedTime, float vx, float vz, float speed);

	// 水平速力更新処理
	void UpdateHorizontalVelocity(float elapsedTime);
private:
	Model* pModel = nullptr;
	OBJ3D pObj;
	float maxSpeed = 10.0f;
	float friction = 0.5f;            // 摩擦力
	float acceleration = 1.0f;  // 加速力
	float moveSpeedX = 0.0f; // キー入力時のスピード
	float moveSpeedZ = 0.0f; // キー入力時のスピード
};
