#include <FrameWork.h>
#include <string>
#include <thread>

#include "Loading.h"
#include "SoundLoader.h"
#include "CameraSystem.h"
#include "SceneGame.h"
#include "Input.h"

void Loading::Init()
{
	// テクスチャの初期化
	loadingSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/LoadingIcon.png", 1); // 引数 : ファイルパス, 同時描画数
	{
		//loadingSprData.pos = { 1280.0f - loadingSprData.texSize.x, 720.0f -loadingSprData.texSize.y };
		loadingSprData.pos = { 0, 0 };
		loadingSprData.size = { 256.0f, 256.0f };
		loadingSprData.texPos = { 0, 0 };
		loadingSprData.texSize = { 256.0f, 256.0f };
	}

	// モデルの初期化
	//playerModel = std::make_unique<Model>("Data/Assets/Model/Player/Player.fbx", false);
	//playerModel = std::make_unique<Model>("Data/Assets/Model/Player/Test/Mma_Kick.fbx", false);
	//{
	//	playerModel->StartAnimation(1, true); // 引数 : FBX内のアニメーション番号, ループ再生するか？
	//	playerModelData.Init();
	//}

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
	//スレッド
	std::thread thread(LoadingThred, this);
	//スレッド管理破棄
	thread.detach();
}

void Loading::Update()
{
	//if (Fade::GetInstance()->loading) return;
	Input input = Input::getInstanse();
	input.Update();
	if (nextScene->IsReady())
	{
		//Fade::GetInstance()->onFadeFlg = true;
		//Fade::GetInstance()->loading = true;
		//Fade::GetInstance()->SetNextScene(new SceneGame()); // TODO : 次のシーンを追加
		SceneManager::GetInstance()->SetScene(new SceneGame);
		nextScene = nullptr;
	}
	
	time++;
	angle += speed * time;
}

void Loading::Render()
{
	// テクスチャの描画
	{
		loadingSpr->Begin();
		loadingSpr->Draw(loadingSprData, 0, { 1, 1, 1, 1 });
		loadingSpr->End();
	}
	// モデルの描画
	{
		//playerModel->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		//playerModel->Render(playerModelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
		//	DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), playerModelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
	}
}

void Loading::ImGui()
{
}

void Loading::UnInit()
{
}

void Loading::LoadingThred(Loading* scene)
{
	// COM関連の初期化でスレッド毎に呼ぶ必要がある//必要かわからん
	CoInitialize(nullptr);
	// 次のシーンの初期化を行う
	scene->nextScene->Init();
	// スレッドが終わる前にCOM関連の終了化
	CoUninitialize();
	// 次のシーンの準備完了設定
	scene->nextScene->SetReady();
}