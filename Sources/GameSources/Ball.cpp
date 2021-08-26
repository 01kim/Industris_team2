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
	//引っ張られている間のみ
	if (pull)
	{
		//ボールの移動更新
		Move();
		//目的地に着いた科の判定
		JudgeArrival();
	}
}


void Ball::Render()
{
	model->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
	model->Render(GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
		DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), GetColor(), FrameWork::GetInstance().GetElapsedTime());

	//当たり判定描画
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

	//引っ張る 止める
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
	//位置に加算
	DirectX::XMFLOAT3 pos;
	pos.x = GetPos().x + direction.x;
	pos.y = GetPos().y;
	pos.z = GetPos().z + direction.z;

	//移動更新
	SetPos(pos);

	//当たり判定の移動更新
	collisionModel->SetPos(GetPos());
}

//　引っ張る
//速度とフラグを設定
void Ball::Pull(DirectX::XMFLOAT3 pos)
{
	//移動し終わるまで引っ張れない
	if (pull)return;

	float force = 5.0f;

	float x = (nextPos.x - oldPos.x);
	float z = (nextPos.z - oldPos.z);
	float length = sqrtf(x * x + z * z);

	//ここ直す必要あり
	//移動方法直す必要あり
	direction.x = ((nextPos.x - oldPos.x) / length) * force;
	direction.z = ((nextPos.z - oldPos.z) / length) * force;


	pull = true;
}

//敵との衝突判定
bool Ball::judgeBallvsEnemy(DirectX::XMFLOAT3 pos,float scale)
{
	//引っ張られていないなら
	if (!pull)return false;

	return hit=Collision::SphereVsSphere(GetPos(), pos, collisionScale, scale);
}

//　到着したか
//XZの位置を比較
//到着: 引っ張りフラグfalse　速度消し
bool Ball::JudgeArrival()
{
	float directionX = nextPos.x - oldPos.x;
	float directionZ = nextPos.z - oldPos.z;

	// X平面で目的地を過ぎた場合は
	//位置を設定し、フラグに足す。
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

	// Z平面で目的地を過ぎた場合は
	//位置を設定し、フラグに足す。
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

	// 到着している
	//引っ張りフラグfalse、速度無し
	if (nextPos.x == GetPos().x && nextPos.z == GetPos().z)
	{
		pull = false;
		direction = {};
		return true;
	}

	return false;

}