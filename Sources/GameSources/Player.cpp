#include <imgui.h>
#include "Player.h"
#include "CameraSystem.h"
#include <FrameWork.h>

void Player::Init()
{
    pModel = new Model("Data/Assets/Model/Player/Test/Mma_Kick.fbx", false);

    pModel->StartAnimation(1, true); // ���� : FBX���̃A�j���[�V�����ԍ�, ���[�v�Đ����邩�H
    pObj.Init();
}

void Player::UnInit()
{
    if (pModel) {
        delete pModel;
        pModel = nullptr;
    }
}

void Player::Update()
{
    //static float aaa = 0;
    //pObj.SetAngle({aaa, 0, 0});
    //aaa++;
}

void Player::Draw()
{
    pModel->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
    pModel->Render(pObj.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
     	DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), pObj.GetColor(), FrameWork::GetInstance().GetElapsedTime());
}

void Player::ImguiDebug()
{
#ifdef _DEBUG
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
    //ImGui::PushStyleColor(ImGuiCond_FirstUseEver, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));

    if (ImGui::Begin("Player", nullptr, ImGuiWindowFlags_None))
    {
        // �g�����X�t�H�[��
        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
        {
            DirectX::XMFLOAT3 position = pObj.GetPos();
            ImGui::SliderFloat("pos X", &position.x, -200, 200);
            ImGui::SliderFloat("pos Y", &position.y, -200, 200);
            ImGui::SliderFloat("pos Z", &position.z, -200, 200);
            pObj.SetPos(position);

            DirectX::XMFLOAT3 angle = pObj.GetAngle();
            ImGui::SliderFloat("angle X", &angle.x, DirectX::XMConvertToRadians(-180), DirectX::XMConvertToRadians(180));
            ImGui::SliderFloat("angle Y", &angle.y, DirectX::XMConvertToRadians(-180), DirectX::XMConvertToRadians(180));
            ImGui::SliderFloat("angle Z", &angle.z, DirectX::XMConvertToRadians(-180), DirectX::XMConvertToRadians(180));
            pObj.SetAngle(angle);
        }
        ImGui::End();
    }
#endif // !DEBUG_
}

void Player::Move(float vx, float vz, float speed)
{

}

// �v���C���[���i�s�����Ɍ����悤�ɂ���
void Player::Turn(float elapsedTime, float vx, float vz, float speed)
{
    speed *= elapsedTime;

    // �i�s�x�N�g�����[���x�N�g���̏ꍇ�͏�������K�v�Ȃ�
    if (vx == 0.0f && vz == 0.0f) return;

    // �i�s�x�N�g����P�ʃx�N�g����
    float length = sqrtf(vx * vx + vz * vz);
    vx /= length;
    vz /= length;

    DirectX::XMFLOAT3 angle = pObj.GetAngle();

    // ���g�̉�]�l����O���������߂�
    float frontX = sinf(angle.y);
    float frontZ = cosf(angle.y);

    // ��]�p�����߂邽�߁A2�̒P�ʃx�N�g���̓��ς��v�Z����
    float dot = (vx * frontX) + (vz * frontZ);

    // ���ϒl��-1.0~1.0�ŕ\������Ă���A2�̒P�ʃx�N�g���̊p�x��
    // �������ق�1.0�ɋ߂Â��Ƃ��������𗘗p���ĉ�]���x�𒲐�����
    float rot = 1.0f - dot;

    // ���E������s�����߂�2�̒P�ʃx�N�g���̊O�ς��v�Z����
    float cross = (vx * frontZ) - (vz * frontX);

    // 2D�̊O�ϒl�����̏ꍇ�����̏ꍇ�ɂ���č��E���肪�s����
    // ���E������s�����Ƃɂ���č��E�����I������
    if (cross < 0.0f) {
        angle.y -= rot * speed;
        pObj.SetAngle(angle);
    }
    else {
        angle.y += rot * speed;
        pObj.SetAngle(angle);
    }
}

// �������͍X�V����
void Player::UpdateHorizontalVelocity(float elapsedTime)
{
    DirectX::XMFLOAT3 speed = pObj.GetSpeed();

    //// XZ���ʂ̑��͂���������
    float length = sqrtf(speed.x * speed.x + speed.z * speed.z);
    if (length > 0.0f) {
        // ���C��
        float friction = this->friction * elapsedTime;

        // ���C�ɂ�鉡�����̑��x����
        if (length > friction) {
            float vx = speed.x / length;
            float vz = speed.z / length;

            speed.x -= vx * friction;
            speed.z -= vz * friction;
            pObj.SetSpeed(speed);
        }
        // �������̑��͂����C�͈ȉ��ɂȂ����̂ő��͂𖳌���
        else {
            speed = { 0.0f, 0.0f, 0.0f };
            pObj.SetSpeed(speed);
        }
    }

    // XZ���ʂ̑��͂���������
    if (length <= maxSpeed) {
        // �ړ��x�N�g�����[���x�N�g���łȂ��Ȃ��������
        float moveVecLength = sqrtf(moveSpeedX * moveSpeedX + moveSpeedZ * moveSpeedZ);
        if (moveVecLength > 0.0f) {
            // ������
            float acceleration = this->acceleration * elapsedTime;

            // �ړ��x�N�g���ɂ���������
            speed.x += acceleration * moveSpeedX;
            speed.z += acceleration * moveSpeedZ;

            // �ő呬�x����
            float length = sqrtf(speed.x * speed.x + speed.z * speed.z);
            if (length > maxSpeed) {
                float vx = speed.x / length;
                float vz = speed.z / length;

                pObj.SetSpeed(speed);
            }
        }
    }
    //�ړ��x�N�g�������Z�b�g
    moveSpeedX = 0.0f;
    moveSpeedZ = 0.0f;
}