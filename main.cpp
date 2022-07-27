
#include<vector>

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"

#include "Object3d.h"
#include "Model.h"
#include"SpriteCommon.h"
#include"Sprite.h"
#include"FbxLoader.h"
#include"ObjectFBX3d.h"
#include"DebugCamera.h"
#include"PostEffect.h"
#include"GameScene.h"
//#include"fbxsdk.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

#pragma region WindowsAPI初期化
	//FbxManager* fbxManager = FbxManager::Create();

	WinApp* winApp = nullptr;

	winApp = new WinApp();
	winApp->Initialize();

	MSG msg{};  // メッセージ
#pragma endregion WindowsAPI初期化

#pragma region DirectX初期化処理

	DirectXCommon* dxCommon = nullptr;

	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	Input* input = nullptr;
	input = new Input();
	input->Initialize(winApp);
	Audio* audio = Audio::GetInstance();
	audio->Initialize();
	Sprite* sprite = nullptr;
	sprite = new Sprite();

	SpriteCommon* spriteCommon = new SpriteCommon();
	spriteCommon->initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->window_width, winApp->window_height);

	GameScene* game = new GameScene();
	game->Initilize(dxCommon, audio, input, spriteCommon);
	
	DebugCamera* camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	
	Object3d::StaticInitialize(dxCommon->GetDev(), winApp->window_width, winApp->window_height);

	ObjectFBX3d::SetDevice(dxCommon->GetDev());
	ObjectFBX3d::SetCamera(camera);
	ObjectFBX3d::CreateGraphicsPipeline();
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDev());
	FBXModel* fbxModel = nullptr;
	ObjectFBX3d* fbxObj = nullptr;
	fbxModel = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

	fbxObj = new ObjectFBX3d();
	fbxObj->Initialize();
	fbxObj->SetModel(fbxModel);
#pragma endregion DirectX初期化処理

#pragma region 描画初期化処理

	

	spriteCommon->LoadTexture(11, L"Resources/texture.png");
	spriteCommon->LoadTexture(1, L"Resources/white.png");
	spriteCommon->LoadTexture(0, L"Resources/background.png");
	std::vector<Sprite*> sprites;
	sprite = Sprite::Create(spriteCommon,1, { 0,0 }, false, false);
	sprite->SetSize({ 1280,720 });
	PostEffect* postEffect = nullptr;

	postEffect = new PostEffect();
	//postEffect->initialize(spriteCommon,100,{0,0});
	postEffect->Initialize(spriteCommon, 1, { 0,0 }, 0, 0);
	//postEffect->SetSize({ 500,500 });
	
#pragma endregion 描画初期化処理

	int counter = 0; // アニメーションの経過時間カウンター

	fbxObj->PlayAnimation(true);
	//fbxObj->SetRotation({ 0,0.25,0 });
	fbxObj->SetScale({ 2,2,2 });
	fbxObj->SetRotation({ 0,40,0 });
	fbxObj->SetPosition({0,-5,0});
	while (true)  // ゲームループ
	{
#pragma region ウィンドウメッセージ処理
		if (winApp->ProcessMessage()) {
			break;
		}
#pragma endregion ウィンドウメッセージ処理

#pragma region DirectX毎フレーム処理
		// DirectX毎フレーム処理　ここから
		game->Update();

		input->Update();

		const int cycle = 540; // 繰り返しの周期
		counter++;
		counter %= cycle; // 周期を超えたら0に戻る
		float scale = (float)counter / cycle; // [0,1]の数値

		scale *= 360.0f;
		if (input->TriggerKey(DIK_0)) // 数字の0キーが押されていたら
		{
			OutputDebugStringA("Hit 0\n");  // 出力ウィンドウに「Hit 0」と表示
		}

		float clearColor[] = { 0.1f,0.25f, 0.5f,0.0f }; // 青っぽい色

		if (input->PushKey(DIK_SPACE))     // スペースキーが押されていたら
		{
			// 画面クリアカラーの数値を書き換える
			clearColor[1] = 1.0f;
			//break;
		}

		// 座標操作
		/*if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
		{

		}*/


		if (input->PushKey(DIK_D) || input->PushKey(DIK_A))
		{

		}
		fbxObj->Update();
		sprite->Update();

		postEffect->Update();
		/*	objPost->Update();
			objChr->Update();*/
		/*for (auto& sprite : sprites)
		{
			sprite->Update();
		}*/
		
		// DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理

#pragma region グラフィックスコマンド

	//	postEffect->PreDrawScene(dxCommon->GetCmdList());
	//	spriteCommon->PreDraw();

	////	sprite->Draw();
	//	game->Draw();
	//	fbxObj->Draw(dxCommon->GetCmdList());
	//	postEffect->PostDrawScene(dxCommon->GetCmdList());


		dxCommon->PreDraw();
	//	spriteCommon->PreDraw();
		game->Draw();


		//postEffect->Draw();
		//postEffect->Draw();

		// ４．描画コマンドここまで
		dxCommon->PostDraw();


	}

	fbxObj->StopAnimation();
#pragma region WindowsAPI後始末
	winApp->Finalize();
#pragma endregion WindowsAPI後始末
	/*FbxLoader::GetInstance()->Finalize();*/
//	delete fbxModel;
	delete postEffect;
	delete dxCommon;
	delete sprite;

	delete fbxModel;
	//delete modelChr;

	delete input;
	delete winApp;
	delete spriteCommon;
	return 0;
}