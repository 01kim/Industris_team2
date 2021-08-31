#pragma once

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#include <imgui_internal.h>


// SceneƒNƒ‰ƒX
class Scene
{
private:

public:
	virtual void Init() = 0;
	virtual void UnInit() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void ImGui() = 0;

	bool IsReady() const { return ready; }
	void SetReady() { ready = true; }
private:
	bool ready = false;
};