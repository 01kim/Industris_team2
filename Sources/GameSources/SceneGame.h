#pragma once
#include <memory>
#include <Camera.h>
#include <Model.h>
#include <Billboard.h>
#include <GeometricPrimitive.h>

#include "Scene.h"
#include "Sprite.h"
#include "Model.h"


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

#if DEBUG_MODE
	DirectX::XMFLOAT3 stagePos = stageModelData.GetPos();
	DirectX::XMFLOAT3 stageScale = stageModelData.GetScale();
	DirectX::XMFLOAT3 stageAngle = stageModelData.GetAngle();
#endif //DEBUG_MODE
public:
	void Init();
	void UnInit();
	void Update();
	void Render();
	void ImGui();
};