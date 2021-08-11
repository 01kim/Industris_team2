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
	// �ړ�����
	void Move(float vx, float vz, float speed);

	// �v���C���[���i�s�����Ɍ����悤�ɂ���
	void Turn(float elapsedTime, float vx, float vz, float speed);

	// �������͍X�V����
	void UpdateHorizontalVelocity(float elapsedTime);
private:
	Model* pModel = nullptr;
	OBJ3D pObj;
	float maxSpeed = 10.0f;
	float friction = 0.5f;            // ���C��
	float acceleration = 1.0f;  // ������
	float moveSpeedX = 0.0f; // �L�[���͎��̃X�s�[�h
	float moveSpeedZ = 0.0f; // �L�[���͎��̃X�s�[�h
};
