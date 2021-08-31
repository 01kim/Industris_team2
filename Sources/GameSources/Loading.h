#pragma once
#include <memory>
#include <Camera.h>
#include <Model.h>
#include <Billboard.h>
#include <GeometricPrimitive.h>

#include "Scene.h"
#include "Sprite.h"
#include "Model.h"
class Loading : public Scene
{
public:
	Loading(Scene* nextScene) :nextScene(nextScene) {}
	void Init()override;
	void UnInit()override;
	void Update()override;
	void Render()override;
	void ImGui()override;
private:
	static void LoadingThred(Loading* scene);
private:
	std::unique_ptr<SpriteBatch> loadingSpr;
	TexData loadingSprData;
	static constexpr float speed = 180;
	float angle = 0.0f;
	int time = 0;
	Scene* nextScene = nullptr;
};