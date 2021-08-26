#include <FrameWork.h>

#include "Ball.h"
#include "CameraSystem.h"


Ball::Ball()
{
	Init();
	model = std::make_unique<Model>("Data/Assets/Model/Ball.fbx", false);
	SetScale(DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f));


	//DirectX::XMFLOAT3 scale = { collisionScale,collisionScale ,collisionScale };
	DirectX::XMFLOAT3 scale = { 100.0f,100.0f,100.0f };
	collisionModel = std::make_unique<CollisionPrimitive>(1, true, scale);
	collisionModel->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
}


void Ball::Update()
{
	//���������Ă���Ԃ̂�
	if (pull)
	{
		//�{�[���̈ړ��X�V
		Move();
		//�ړI�n�ɒ������Ȃ̔���
		JudgeArrival();
	}
}


void Ball::Render()
{
	model->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
	model->Render(GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
		DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), GetColor(), FrameWork::GetInstance().GetElapsedTime());

	//�����蔻��`��
	if (collisionDraw)
	{
		collisionModel->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
	}
}

void Ball::DebugImgui()
{
	ImGui::Begin("Ball");

	DirectX::XMFLOAT3 pos=GetPos();
	ImGui::DragFloat3("Position", &pos.x);

	if (ImGui::DragFloat3("NextPosition", &nextPos.x))
	{
		pull = false;
		direction = {};
	}
	ImGui::DragFloat3("Direction", &direction.x);

	//�������� �~�߂�
	if (!pull) {
		if (ImGui::Button("Pull"))
		{
			Pull(nextPos);
		}
	}
	if(pull)
	{
		if (ImGui::Button("Stop"))
		{
			pull = false;
			direction = {};
		}

	}

	if (hit) ImGui::Text("HIT");
	if (!pull) ImGui::Text("canPull");

	ImGui::End();
}


void Ball::Move()
{
	//�ʒu�ɉ��Z
	DirectX::XMFLOAT3 pos;
	pos.x = GetPos().x + direction.x;
	pos.y = GetPos().y;
	pos.z = GetPos().z + direction.z;

	//�ړ��X�V
	SetPos(pos);

	//�����蔻��̈ړ��X�V
	collisionModel->SetPos(GetPos());
}

//�@��������
//���x�ƃt���O��ݒ�
void Ball::Pull(DirectX::XMFLOAT3 pos)
{
	//�ړ����I���܂ň�������Ȃ�
	if (pull)return;

	float force = 5.0f;

	float x = (nextPos.x - oldPos.x);
	float z = (nextPos.z - oldPos.z);
	float length = sqrtf(x * x + z * z);

	//���������K�v����
	//�ړ����@�����K�v����
	direction.x = ((nextPos.x - oldPos.x) / length) * force;
	direction.z = ((nextPos.z - oldPos.z) / length) * force;


	pull = true;
}

//�G�Ƃ̏Փ˔���
bool Ball::judgeBallvsEnemy(DirectX::XMFLOAT3 pos,float scale)
{
	//���������Ă��Ȃ��Ȃ�
	if (!pull)return false;

	return hit=Collision::SphereVsSphere(GetPos(), pos, collisionScale, scale);
}

//�@����������
//XZ�̈ʒu���r
//����: ��������t���Ofalse�@���x����
bool Ball::JudgeArrival()
{
	float directionX = nextPos.x - oldPos.x;
	float directionZ = nextPos.z - oldPos.z;

	// X���ʂŖړI�n���߂����ꍇ��
	//�ʒu��ݒ肵�A�t���O�ɑ����B
	if (directionX < 0.0f)
	{
		if(GetPos().x <= nextPos.x )
		{
			SetPosX(nextPos.x);
		}
	}
	else if (directionX > 0.0f)
	{
		if(GetPos().x >= nextPos.x)
		{
			SetPosX(nextPos.x);
		}
	}

	// Z���ʂŖړI�n���߂����ꍇ��
	//�ʒu��ݒ肵�A�t���O�ɑ����B
	if (directionZ < 0.0f)
	{
		if (GetPos().z <= nextPos.z)
		{
			SetPosZ(nextPos.z);
		}
	}
	else if (directionZ > 0.0f)
	{
		if (GetPos().z >= nextPos.z) 
		{
			SetPosZ(nextPos.z);
		}
	}

	// �������Ă���
	//��������t���Ofalse�A���x����
	if (nextPos.x == GetPos().x && nextPos.z == GetPos().z)
	{
		pull = false;
		direction = {};
		return true;
	}

	return false;

}