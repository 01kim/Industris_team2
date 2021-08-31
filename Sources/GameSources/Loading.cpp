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
	// �e�N�X�`���̏�����
	loadingSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/LoadingIcon.png", 1); // ���� : �t�@�C���p�X, �����`�搔
	{
		//loadingSprData.pos = { 1280.0f - loadingSprData.texSize.x, 720.0f -loadingSprData.texSize.y };
		loadingSprData.pos = { 0, 0 };
		loadingSprData.size = { 256.0f, 256.0f };
		loadingSprData.texPos = { 0, 0 };
		loadingSprData.texSize = { 256.0f, 256.0f };
	}

	// ���f���̏�����
	//playerModel = std::make_unique<Model>("Data/Assets/Model/Player/Player.fbx", false);
	//playerModel = std::make_unique<Model>("Data/Assets/Model/Player/Test/Mma_Kick.fbx", false);
	//{
	//	playerModel->StartAnimation(1, true); // ���� : FBX���̃A�j���[�V�����ԍ�, ���[�v�Đ����邩�H
	//	playerModelData.Init();
	//}

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
	//�X���b�h
	std::thread thread(LoadingThred, this);
	//�X���b�h�Ǘ��j��
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
		//Fade::GetInstance()->SetNextScene(new SceneGame()); // TODO : ���̃V�[����ǉ�
		SceneManager::GetInstance()->SetScene(new SceneGame);
		nextScene = nullptr;
	}
	
	time++;
	angle += speed * time;
}

void Loading::Render()
{
	// �e�N�X�`���̕`��
	{
		loadingSpr->Begin();
		loadingSpr->Draw(loadingSprData, 0, { 1, 1, 1, 1 });
		loadingSpr->End();
	}
	// ���f���̕`��
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
	// COM�֘A�̏������ŃX���b�h���ɌĂԕK�v������//�K�v���킩���
	CoInitialize(nullptr);
	// ���̃V�[���̏��������s��
	scene->nextScene->Init();
	// �X���b�h���I���O��COM�֘A�̏I����
	CoUninitialize();
	// ���̃V�[���̏��������ݒ�
	scene->nextScene->SetReady();
}