#include <imgui.h>
#include "Player.h"
#include "CameraSystem.h"
#include <FrameWork.h>

void Player::Init()
{
    pModel = new Model("Data/Assets/Model/Player/Test/Mma_Kick.fbx", false);

    pModel->StartAnimation(1, true); // 引数 : FBX内のアニメーション番号, ループ再生するか？
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
        // トランスフォーム
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

// プレイヤーが進行方向に向くようにする
void Player::Turn(float elapsedTime, float vx, float vz, float speed)
{
    speed *= elapsedTime;

    // 進行ベクトルがゼロベクトルの場合は処理する必要なし
    if (vx == 0.0f && vz == 0.0f) return;

    // 進行ベクトルを単位ベクトル化
    float length = sqrtf(vx * vx + vz * vz);
    vx /= length;
    vz /= length;

    DirectX::XMFLOAT3 angle = pObj.GetAngle();

    // 自身の回転値から前方向を求める
    float frontX = sinf(angle.y);
    float frontZ = cosf(angle.y);

    // 回転角を求めるため、2つの単位ベクトルの内積を計算する
    float dot = (vx * frontX) + (vz * frontZ);

    // 内積値は-1.0~1.0で表現されており、2つの単位ベクトルの角度が
    // 小さいほど1.0に近づくという性質を利用して回転速度を調整する
    float rot = 1.0f - dot;

    // 左右判定を行うために2つの単位ベクトルの外積を計算する
    float cross = (vx * frontZ) - (vz * frontX);

    // 2Dの外積値が正の場合か負の場合によって左右判定が行える
    // 左右判定を行うことによって左右判定を選択する
    if (cross < 0.0f) {
        angle.y -= rot * speed;
        pObj.SetAngle(angle);
    }
    else {
        angle.y += rot * speed;
        pObj.SetAngle(angle);
    }
}

// 水平速力更新処理
void Player::UpdateHorizontalVelocity(float elapsedTime)
{
    DirectX::XMFLOAT3 speed = pObj.GetSpeed();

    //// XZ平面の速力を減速する
    float length = sqrtf(speed.x * speed.x + speed.z * speed.z);
    if (length > 0.0f) {
        // 摩擦力
        float friction = this->friction * elapsedTime;

        // 摩擦による横方向の速度処理
        if (length > friction) {
            float vx = speed.x / length;
            float vz = speed.z / length;

            speed.x -= vx * friction;
            speed.z -= vz * friction;
            pObj.SetSpeed(speed);
        }
        // 横方向の速力が摩擦力以下になったので速力を無効化
        else {
            speed = { 0.0f, 0.0f, 0.0f };
            pObj.SetSpeed(speed);
        }
    }

    // XZ平面の速力を加速する
    if (length <= maxSpeed) {
        // 移動ベクトルがゼロベクトルでないなら加速する
        float moveVecLength = sqrtf(moveSpeedX * moveSpeedX + moveSpeedZ * moveSpeedZ);
        if (moveVecLength > 0.0f) {
            // 加速力
            float acceleration = this->acceleration * elapsedTime;

            // 移動ベクトルによる加速処理
            speed.x += acceleration * moveSpeedX;
            speed.z += acceleration * moveSpeedZ;

            // 最大速度制限
            float length = sqrtf(speed.x * speed.x + speed.z * speed.z);
            if (length > maxSpeed) {
                float vx = speed.x / length;
                float vz = speed.z / length;

                pObj.SetSpeed(speed);
            }
        }
    }
    //移動ベクトルをリセット
    moveSpeedX = 0.0f;
    moveSpeedZ = 0.0f;
}