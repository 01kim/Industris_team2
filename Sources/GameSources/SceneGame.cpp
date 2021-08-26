#include <FrameWork.h>
#include <string>

#include "SceneGame.h"
#include "InputDevice.h"
#include "SoundLoader.h"
#include "CameraSystem.h"

#include "EnemyManager.h"

#include "Score.h"

void SceneGame::Init()
{
	// テクスチャの初期化
	//titleSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/Title/TitleLogo.png", 2); // 引数 : ファイルパス, 同時描画数
	//{
	//	titleSprData.pos = { 0, 0 };
	//	titleSprData.size = { 1280.0f, 720.0f };
	//	titleSprData.texPos = { 0, 0 };
	//	titleSprData.texSize = { 1920.0f, 1080.0f };
	//}

	// モデルの初期化
	playerModel = std::make_unique<Model>("Data/Assets/Model/Player/Test/Mma_Kick.fbx", false);
	{
		playerModel->StartAnimation(1, true); // 引数 : FBX内のアニメーション番号, ループ再生するか？
		playerModelData.Init();
	}
	stageModel = std::make_unique<Model>("Data/Assets/Model/Plane.fbx", false);
	{
		stageModelData.Init();
	}

	//エネミーの追加
	{
		EnemyManager::Instance().Register(DirectX::XMFLOAT3{ 1.0f, 0.0f, 0.0f });
	}

	// すべてのサウンドを停止
	{
		AllSoundStop();
		AllBgmSoundStop();
	}

	// サウンドの再生
	{
		//PlaySoundMem(SoundLoader::GetInstance()->bgm.get()); // ループ再生
		//PlaySoundMem(SoundLoader::GetInstance()->se.get()); // 単発再生
	}

	//弾と衝突対象の追加
	{
		//衝突対象
		collisionScale = { 100.0f,100.0f,100.0f };
		collisionModel = std::make_unique<CollisionPrimitive>(1, true, collisionScale);
		collisionModel->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
	}
}

void SceneGame::Update()
{
	if (Fade::GetInstance()->loading) return;

	/*if (xInput[0].bAt || xInput[0].bBt || xInput[0].bXt || xInput[0].bYt)
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->loading = true;
	}*/
	EnemyManager::Instance().Update();

	//玉の更新
	{
		//玉の更新
		Ball::Instance().Update();
		//衝突対象と当たっているか
		Ball::Instance().judgeBallvsEnemy(collisionPos, collisionScale.x);
	}
}

void SceneGame::Render()
{
	// テクスチャの描画
	{
		//titleSpr->Begin();
		//titleSpr->Draw(titleSprData, 0, { 1, 1, 1, 1 });
		//titleSpr->Draw(titleSprData, 1.5f, { 1, 1, 1, 1 });
		//titleSpr->End();
	}

	// モデルの描画
	{
		playerModel->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		playerModel->Render(playerModelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), playerModelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
		stageModel->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		stageModel->Render(stageModelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), stageModelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());

		EnemyManager::Instance().Render();
	}

	//玉の描画
	{
		//玉
		Ball::Instance().Render();
		//衝突対象
		collisionModel->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
	}
}

void SceneGame::ImGui()
{
	//Stage
	ImGui::Begin("Stage");
	ImGui::DragFloat3("Position", &stagePos.x);
	stageModelData.SetPos(stagePos);
	ImGui::DragFloat3("Scale", &stageScale.x);
	stageModelData.SetScale(stageScale);
	ImGui::InputFloat3("Angle", &stageAngle.x);
	stageModelData.SetAngle(stageAngle);
	ImGui::End();

	//玉
	{
		Ball::Instance().DebugImgui();
		//衝突対象
		ImGui::Begin("collision");
		ImGui::DragFloat3("Position", &collisionPos.x);
		collisionModel->SetPos(collisionPos);
		ImGui::DragFloat3("Scale", &collisionScale.x);
		collisionModel->SetScale(collisionScale);
		ImGui::End();
	}

	//スコア
	{
		ImGui::Begin("score");

		int s = ScoreManager::Instance().getScore();
		ImGui::InputInt("score", &s);
		ScoreManager::Instance().setScore(s);
		ImGui::End();
	}
}

void SceneGame::UnInit()
{
	playerModelData.UnInit();
	stageModelData.UnInit();
}