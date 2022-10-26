#include"Scene.h"

void Scene::Initialize()
{
#pragma region WindowsAPI������
	WinApp* winApp = nullptr;

	winApp = new WinApp();
	winApp->Initialize(L"�Z�p���̋��P");

	MSG msg{};  // ���b�Z�[�W
#pragma endregion WindowsAPI������

#pragma region DirectX����������

	DirectXCommon* dxCommon = nullptr;

	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	Input* input = nullptr;
	input = new Input();
	input->Initialize(winApp);

	Object3d::StaticInitialize(dxCommon->GetDev());
	DebugCamera* camera = nullptr;

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);
	Object3d::SetCamera(camera);

	// �J���������_���Z�b�g
	camera->SetTarget({ 0, 11, -400 });
	camera->SetDistance(3.0f);

#pragma endregion DirectX����������

}