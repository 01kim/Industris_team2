#pragma once
#include <memory>
#include <Camera.h>
#include <Model.h>
#include <Billboard.h>
#include <GeometricPrimitive.h>

#include "Scene.h"
#include "Sprite.h"
#include "Model.h"

//追加
#include "Collision.h"
#include "Ball.h"

class SceneGame : public Scene
{
private:
	// タイトルテクスチャ描画用
	std::unique_ptr<SpriteBatch> titleSpr;
	TexData titleSprData;

	// プレイヤーモデル描画用
	std::unique_ptr<Model> playerModel;
	std::unique_ptr<Model> stageModel;
	OBJ3D playerModelData;
	OBJ3D stageModelData;

	DirectX::XMFLOAT3 stagePos = stageModelData.GetPos();
	DirectX::XMFLOAT3 stageScale = stageModelData.GetScale();
	DirectX::XMFLOAT3 stageAngle = stageModelData.GetAngle();

	//衝突対象
	std::unique_ptr<CollisionPrimitive> collisionModel;
	DirectX::XMFLOAT3 collisionPos = {};
	DirectX::XMFLOAT3 collisionScale = {};


public:
	void Init();
	void UnInit();
	void Update();
	void Render();
	void ImGui();
};