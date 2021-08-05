#include <FrameWork.h>
#include <string>

#include "SceneGame.h"
#include "InputDevice.h"
#include "SoundLoader.h"
#include "CameraSystem.h"


void SceneGame::Init()
{
	// �e�N�X�`���̏�����
	//titleSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/Title/TitleLogo.png", 2); // ���� : �t�@�C���p�X, �����`�搔
	//{
	//	titleSprData.pos = { 0, 0 };
	//	titleSprData.size = { 1280.0f, 720.0f };
	//	titleSprData.texPos = { 0, 0 };
	//	titleSprData.texSize = { 1920.0f, 1080.0f };
	//}

	// ���f���̏�����
	playerModel = std::make_unique<Model>("Data/Assets/Model/Player/Test/Mma_Kick.fbx", false);
	{
		playerModel->StartAnimation(1, true); // ���� : FBX���̃A�j���[�V�����ԍ�, ���[�v�Đ����邩�H
		playerModelData.Init();
	}
	stageModel = std::make_unique<Model>("Data/Assets/Model/Plane.fbx", false);
	{
		stageModelData.Init();
	}
	// ���ׂẴT�E���h���~
	{
		AllSoundStop();
		AllBgmSoundStop();
	}

	// �T�E���h�̍Đ�
	{
		//PlaySoundMem(SoundLoader::GetInstance()->bgm.get()); // ���[�v�Đ�
		//PlaySoundMem(SoundLoader::GetInstance()->se.get()); // �P���Đ�
	}
}

void SceneGame::Update()
{
	if (Fade::GetInstance()->loading) return;

	if (xInput[0].bAt || xInput[0].bBt || xInput[0].bXt || xInput[0].bYt)
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->loading = true;
	}
}

void SceneGame::Render()
{
	// �e�N�X�`���̕`��
	{
		//titleSpr->Begin();
		//titleSpr->Draw(titleSprData, 0, { 1, 1, 1, 1 });
		//titleSpr->Draw(titleSprData, 1.5f, { 1, 1, 1, 1 });
		//titleSpr->End();
	}

	// ���f���̕`��
	{
		playerModel->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		playerModel->Render(playerModelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), playerModelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());

		stageModel->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		stageModel->Render(stageModelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), stageModelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
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
}

void SceneGame::UnInit()
{
	playerModelData.UnInit();
	stageModelData.UnInit();
}