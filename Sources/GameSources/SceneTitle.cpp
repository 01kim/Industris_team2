#include <FrameWork.h>
#include <string>

#include "SceneTitle.h"
#include "InputDevice.h"
#include "SoundLoader.h"
#include "CameraSystem.h"
#include "SceneGame.h"
#include "Loading.h"
#include "Input.h"

void SceneTitle::Init()
{
	// テクスチャの初期化
	titleSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/Title/TitleLogo.png", 2); // 引数 : ファイルパス, 同時描画数
	{
		titleSprData.pos = { 0, 0 };
		titleSprData.size = { 1280.0f, 720.0f };
		titleSprData.texPos = { 0, 0 };
		titleSprData.texSize = { 1920.0f, 1080.0f };
	}

	// モデルの初期化
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
}

void SceneTitle::Update()
{
	if (Fade::GetInstance()->loading) return;
	Input& input = Input::getInstanse();
	input.Update();
	if (input.GetButtonDown() & input.button.BTN_A)
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->loading = true;
		Fade::GetInstance()->SetNextScene(new Loading(new SceneGame)); // TODO : 次のシーンを追加
	}

}

void SceneTitle::Render()
{
	// テクスチャの描画
	{
		titleSpr->Begin();
		titleSpr->Draw(titleSprData, 0, { 1, 1, 1, 1 });
		titleSpr->Draw(titleSprData, 1.5f, { 1, 1, 1, 1 });
		titleSpr->End();
	}

	// モデルの描画
	{
		//playerModel->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		//playerModel->Render(playerModelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
		//	DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), playerModelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
	}
}

void SceneTitle::ImGui()
{
}

void SceneTitle::UnInit()
{
	playerModelData.UnInit();
}