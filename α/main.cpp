

#include"GameScene.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

#pragma region WindowsAPI初期化
	WinApp* winApp = nullptr;

	winApp = new WinApp();
	winApp->Initialize(L"六角柱の狂襲");

	MSG msg{};  // メッセージ
#pragma endregion WindowsAPI初期化

#pragma region DirectX初期化処理

	DirectXCommon* dxCommon = nullptr;

	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	Input* input = nullptr;
	input = new Input();
	input->Initialize(winApp);

	GameScene* game = new GameScene();

	game->Initialize(winApp, dxCommon, input);


	//GetWindowInfo();
	while (true)  // ゲームループ
	{
#pragma region ウィンドウメッセージ処理
		if (winApp->ProcessMessage()) {
			break;
		}
#pragma endregion ウィンドウメッセージ処理

#pragma region DirectX毎フレーム処理
		// DirectX毎フレーム処理　ここから
		if (input->PushKey(DIK_ESCAPE))
		{
			break;
		}
		game->Update();
	
#pragma endregion DirectX毎フレーム処理

#pragma region グラフィックスコマンド

		dxCommon->PreDraw();

		game->Draw(dxCommon->GetCmdList());
		
		// ４．描画コマンドここまで
		dxCommon->PostDraw();
	}
	
	game->Delete();
#pragma region WindowsAPI後始末
	winApp->Finalize();
#pragma endregion WindowsAPI後始末
	
	delete input;
	delete winApp;
	
	return 0;
}


