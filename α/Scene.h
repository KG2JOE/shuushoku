#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Object3d.h"
#include "DebugCamera.h"

class Scene
{
private:


public:
	void Initialize();

	void Update();
	
	void Delete();

private:

	int scene = 0;
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	DebugCamera* camera = nullptr;


};