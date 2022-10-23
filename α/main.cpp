﻿
#include<vector>

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"

#include "Object3d.h"
#include "Model.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "DebugCamera.h"
#include "Collision.h"
#include"Audio.h"
#include"DebugText.h"

#include"StageWorld.h"
#include"Player.h"
using namespace DirectX;
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMVECTOR = DirectX::XMVECTOR;
using XMMATRIX = DirectX::XMMATRIX;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

#pragma region WindowsAPI初期化
	WinApp* winApp = nullptr;

	winApp = new WinApp();
	winApp->Initialize(L"タイトル");

	MSG msg{};  // メッセージ
#pragma endregion WindowsAPI初期化

#pragma region DirectX初期化処理

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

	// カメラ注視点をセット
	camera->SetTarget({ 0, 11, -400 });
	camera->SetDistance(3.0f);

#pragma endregion DirectX初期化処理

#pragma region 描画初期化処理

	SpriteCommon* spriteCommon = new SpriteCommon();

	spriteCommon->initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->window_width, winApp->window_height);
	

	spriteCommon->LoadTexture(0, L"Resources/coraRe.png");
	spriteCommon->LoadTexture(1, L"Resources/playerRe.png");
	spriteCommon->LoadTexture(2, L"Resources/reader.png");
	spriteCommon->LoadTexture(3, L"Resources/debugfont.png");
	spriteCommon->LoadTexture(4, L"Resources/gameover.png");
	spriteCommon->LoadTexture(5, L"Resources/title2.png");
	spriteCommon->LoadTexture(6, L"Resources/hud.png");

	std::vector<Sprite*> sprites;

	/*Sprite* spriteCoraRe = Sprite::Create(spriteCommon, 0, { 0,0 }, false, false);
	Sprite* spritePlayerRe = Sprite::Create(spriteCommon, 1, { 0,0 }, false, false);
	Sprite* spriteReader = Sprite::Create(spriteCommon, 2, { 0,0 }, false, false);
	XMFLOAT3 coraRe = { 1280 - 128 - 16,0,0 };

	spriteCoraRe->SetPosition(coraRe);
	spriteCoraRe->Update();

	spritePlayerRe->SetPosition({ 1280 - 256 - 120,0,0 });
	spritePlayerRe->Update();
	spriteReader->SetPosition({ 1280 - 256,0,0 });
	spriteReader->Update();*/
	Sprite* spriteGameOver = Sprite::Create(spriteCommon, 4, { 0,0 }, false, false);
	spriteGameOver->SetPosition({ 0,0,0 });
	spriteGameOver->Update();
	Sprite* spriteTitle = Sprite::Create(spriteCommon, 5, { 0,0 }, false, false);
	spriteTitle->SetPosition({ 0,0,0 });
	spriteTitle->Update();
	Sprite* spriteHud = Sprite::Create(spriteCommon, 6, { 0,0 }, false, false);
	spriteHud->SetPosition({ 0,0,0 });
	spriteHud->Update();
	DebugText* debTxt = new DebugText;

	debTxt->Initialize(spriteCommon, 3);
	Model* inCoa = Model::LoadFromOBJ("core_in");

	Model* modelGround = Model::LoadFromOBJ("ground");


	Model* modelBack = Model::LoadFromOBJ("back");
	//Model* modelCloud = Model::LoadFromOBJ("cloud");
	Model* modelTerritory = Model::LoadFromOBJ("territory");
	Model* modelWorld1 = Model::LoadFromOBJ("world1");
	Model* modelWorld2 = Model::LoadFromOBJ("world2");
	Model* modelAtkHud = Model::LoadFromOBJ("atkHad");
	Object3d* objAtkHud = Object3d::Create();
	objAtkHud->SetModel(modelAtkHud);
	objAtkHud->SetPosition({ 0,5,-200 });
	int ECount = 10;

	const float PI = 3.1415926f;


	Object3d* OBJInCoa = Object3d::Create();

	Object3d* OBJBack = Object3d::Create();

	Object3d* objGround = Object3d::Create();
	
	OBJInCoa->SetModel(inCoa);

	OBJBack->SetModel(modelBack);
	objGround->SetModel(modelGround);
	
	//XMFLOAT3 coapos = { 0,4,50 };
	XMFLOAT3 coapos = { 0,14,30 };
	OBJInCoa->SetPosition(coapos);


	OBJBack->SetPosition({ 0,10,50 });
	objGround->SetPosition({ 0,0,50 });

	float radius = 500.0f;
	float angle[200] = {};


	camera->SetEye({ 0, 10, 0 });

	OBJBack->SetScale({ 6.0f,6.0f,6.0f });
#pragma endregion 描画初期化処理

	int counter = 0; // アニメーションの経過時間カウンター

	//int scene = 0;
	int scene = 0;

	//スカイドーム
	XMFLOAT3 skyPos = OBJBack->GetPosition();

	//コア係
	XMFLOAT3 CoaRotA = {};

	int coaHit = 3000;

	//音
	Audio* audio = Audio::GetInstance();
	audio->Initialize();
	audio->LoadWave("thunder.wav");

	//ステージ
	StageWorld* stageWorld = new StageWorld();
	stageWorld->Initialize(input);
	
#pragma region camera初期化
	// カメラ関係 camera
	
	float angleX = 0;
	float angleY = 0;
	float MoveAngleY;

	float scaleX = 1.0f / (float)WinApp::window_width;
	float scaleY = 1.0f / (float)WinApp::window_height;
	float distance = 50.0f;
	XMMATRIX matRot = DirectX::XMMatrixIdentity();
	
#pragma endregion camera初期化
	Player* player = new Player();
	player->Initialize(input);
	

	/*PlayerPos.x = 0.0f;
	PlayerPos.y = 5.0f;
	PlayerPos.z = -417.0f;*/
	camera->SetTarget(player->GetPlayerPos());
	camera->SetEye({ player->GetPlayerPos().x,player->GetPlayerPos().y,player->GetPlayerPos().z - distance });

	//重力
	const float Grabity = 9.80665f;

	int a = 0;

	int time = 100;
	int oldtime = 100;

	UINT gameFlag = 0;

	float addAngle = -89.550f;
	float setrot = 0;
	while (true)  // ゲームループ
	{
#pragma region ウィンドウメッセージ処理
		if (winApp->ProcessMessage()) {
			break;
		}
#pragma endregion ウィンドウメッセージ処理

#pragma region DirectX毎フレーム処理
		// DirectX毎フレーム処理　ここから

		if (scene == 0)
		{
			
			if (input->PushKey(DIK_SPACE))
			{
				scene = 1;

			}
			if (input->PushKey(DIK_RETURN))
			{
				scene = 1;
				
			}
			if (input->TriggerMouseLeft())
			{
				scene = 1;

			}
			if (input->PushKey(DIK_ESCAPE))
			{
				break;
			}
		}

		if (scene == 1)
		{
			SetCursorPos(860, 440);
			//camera->SetTarget(cloudPos);

			CoaRotA.y += 0.3f;

			OBJInCoa->SetRotation(CoaRotA);

			OBJInCoa->SetModel(inCoa);

			// マウスの入力を取得
			Input::MouseMove mouseMove = input->GetMouseMove();
			float dy = mouseMove.lX * scaleY;
			MoveAngleY = dy * XM_PI;
			float dx = mouseMove.lY * scaleX;


			angleX += dx * XM_PI;
			angleY += dy * XM_PI;
			
			float angley = mouseMove.lX * 0.1f * 5;

			time--;

			if (time < 1)
			{
				time = oldtime;
				//oldtime = time;
				 a = rand() % 14;
				stageWorld->SetHeightLineCase(a);

			}


			// ボタンが押されていたらカメラを並行移動させる
#pragma region playerMove
			player->PlayerMove();

#pragma endregion playerMove


			camera->SetTarget(player->GetPlayerPos());
			if (input->PushKey(DIK_ESCAPE))
			{
				break;
			}

			

			
			if (input->PushMouseLeft())
			{
				//stageWorld->SetHeightLineCase(11);

				//stageWorld->SetHeightLineCase(a);
				//stageWorld->ALLSetImpact(PlayerPos, 1, 1);

			}
			for (int i = 0; i < 50; i++)
			{
				for (int j = 0; j < 50; j++)
				{
					if (player->GetDamegeFlag() == 0)
					{
						XMFLOAT3 temp = stageWorld->GetPosition(i, j);
						temp.y +=140.0f;
						//bool isHit = Collision::HitCircle(stageWorld->GetPosition(i, j), 0, player->GetPlayerPos(), 0, 2);
						bool isHit = Collision::HitCircle(player->GetPlayerPos(), 5, temp, 2, 2);
						if (isHit)
						{

							player->SetDamegeFlag(1);
							gameFlag = gameFlag + 1;
						}
					}

					
				}
			}

			
			XMFLOAT3 cameraEye = camera->GetEye();

			if (angleX < -1.0f)
			{
				angleX = -1.0f;
			}
			if (angleX > 1.0f)
			{
				angleX = 1.0f;
			}

			cameraEye.x = player->GetPlayerPos().x + distance * cos(/*XMConvertToRadians(-angleY - 90)*/-angleY - 89.550f) * cos(/*XMConvertToRadians(-angleX)*/angleX);
			cameraEye.z = player->GetPlayerPos().z + distance * sin(/*XMConvertToRadians(-angleY - 90)*/-angleY - 89.550f) * cos(/*XMConvertToRadians(-angleX)*/angleX);
			cameraEye.y = player->GetPlayerPos().y + 2 + distance * sin(/*XMConvertToRadians(-angleX)*/angleX);

			camera->SetEye(cameraEye);
			
			matRot = player->GetMatRot();
			XMMATRIX matRotNew = XMMatrixIdentity();
			
			matRotNew *= XMMatrixRotationY(MoveAngleY);
			
			matRot = matRotNew * matRot;
		
			player->SetMatRot(matRot);
			
			bool rightHit = Collision::HitWorld(player->GetPlayerPos().x, 219.0f, 1);
			bool leftHit = Collision::HitWorld(player->GetPlayerPos().x, -150.0f, 0);
			bool frontHit = Collision::HitWorld(player->GetPlayerPos().z, -30.0f, 1);
			bool buckHit = Collision::HitWorld(player->GetPlayerPos().z, -453.0f, 0);
			
			if (rightHit || leftHit || frontHit || buckHit)
			{
				
				if (rightHit)
				{
					player->SetPlayerPos({ 219.0f,player->GetPlayerPos().y,player->GetPlayerPos().z });
				}
				if (leftHit)
				{
					player->SetPlayerPos({ -150.0f,player->GetPlayerPos().y,player->GetPlayerPos().z });

				}
				if (frontHit)
				{
					player->SetPlayerPos({ player->GetPlayerPos().x,player->GetPlayerPos().y,-30.0f});

				}
				if (buckHit)
				{
					player->SetPlayerPos({ player->GetPlayerPos().x,player->GetPlayerPos().y,-453.0f });
				}
			}
			////ミニマップの回転を改めて確認すること　　　10月09日記述
			//objPlayer->SetPosition(PlayerPos);
			////cloudRot.y = atan2f(-fTargetEye.x, -fTargetEye.z);
			//playerRot.y = angleY - 90/**= 180 / PI*/;
			////cloudRot.x = atan2f(-fTargetEye.x, -fTargetEye.z);
			//playerRot.x *= 180 / PI;
			//if (input->PushKey(DIK_X))
			//{
			//	objPlayer->SetRotation({ 0.0f, playerRot.y, 0.0f });

			//}

				//ミニマップの回転を改めて確認すること　　　10月09日記述
			
			if (input->PushKey(DIK_0))
			{
				
			}
			setrot = angleY;
			setrot *= 180 / PI;
			player->SetRot({ 0.0f,setrot, 0.0f });
			//cloudRot.y = atan2f(-fTargetEye.x, -fTargetEye.z);
			//playerRot.y = angleY - 90/**= 180 / PI*/;
			////cloudRot.x = atan2f(-fTargetEye.x, -fTargetEye.z);
			//playerRot.x *= 180 / PI;
			//if (input->PushKey(DIK_X))
			//{
			//	objPlayer->SetRotation({ 0.0f, playerRot.y, 0.0f });

			//}

			//ミニマップをいったん切る
			/*if (input->PushKey(DIK_D))
			{
				coraRe.y -= sin(((playerRot.y + 90) * PI) / 180) * (1.0f / 3.90625f);
				coraRe.x -= cos(((playerRot.y + 90) * PI) / 180) * (1.0f / 3.90625f);
			}
			if (input->PushKey(DIK_A))
			{
				coraRe.y += sin(((playerRot.y + 90) * PI) / 180) * (1.0f / 3.90625f);
				coraRe.x += cos(((playerRot.y + 90) * PI) / 180) * (1.0f / 3.90625f);

			}
			if (input->PushKey(DIK_W))
			{
				coraRe.y -= sin((playerRot.y * PI) / 180) * (1.0f / 3.90625f);
				coraRe.x -= cos((playerRot.y * PI) / 180) * (1.0f / 3.90625f);
			}
			if (input->PushKey(DIK_S))
			{
				coraRe.y += sin((playerRot.y * PI) / 180) * (1.0f / 3.90625f);
				coraRe.x += cos((playerRot.y * PI) / 180) * (1.0f / 3.90625f);
			}
			spriteCoraRe->SetPosition(coraRe);
			spritePlayerRe->SetRotation(playerRot.y + 90);
			*/

			

			/*if (gameFlag > 3)
			{
				audio->PlayWave("thunder.wav", 0);
				scene = 2;
			}*/
			char text1[256];
			sprintf_s(text1,"angle%f angleX%f", angleY, angleX);
			debTxt->Print(text1, 0, 0, 1);

			char text2[256];
			sprintf_s(text2, "c.x:%f c.y:%f c.z:%f\np.x:%f p.y:%f p.z:%f", coapos.x, coapos.y, coapos.z,player->GetPlayerPos().x, player->GetPlayerPos().y, player->GetPlayerPos().z);
			debTxt->Print(text2, 0, 16, 1);
		}

		if (scene == 2)
		{


			if (input->PushKey(DIK_ESCAPE))
			{
				break;
			}
			if (input->PushKey(DIK_SPACE))
			{
				break;
			}
			if (input->PushKey(DIK_RETURN))
			{
				break;
			}
			if (input->TriggerMouseLeft())
			{
				break;
			}
		}
		if (scene == 3)
		{
			if (input->PushKey(DIK_ESCAPE))
			{
				break;
			}
		}

		input->Update();

		camera->Update();

		OBJInCoa->Update();

		OBJBack->Update();
		objGround->Update();
		objAtkHud->Update();
		stageWorld->Update();
		player->Update();
		//objPlayer->Update();
		
		//spritePlayerRe->Update();
		//spriteCoraRe->Update();
		spriteGameOver->Update();
		spriteHud->Update();
		spriteTitle->Update();

		// DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理

#pragma region グラフィックスコマンド

		dxCommon->PreDraw();

		Object3d::PreDraw(dxCommon->GetCmdList());
		if (scene == 0)
		{


			objGround->Draw();

			OBJInCoa->Draw();


			
		//	objPlayer->Draw();

		}
		if (scene == 1)
		{
			//	Object3d::PreDraw(dxCommon->GetCmdList());

				//objGround->Draw();
			OBJInCoa->Draw();

			objAtkHud->Draw();
			stageWorld->Draw();
			player->Draw();
			
			//objPlayer->Draw();

		}
		if (scene == 2)
		{



		}
		if (scene == 3)
		{

		}
		Object3d::PostDraw();

		spriteCommon->PreDraw();

		if (scene == 0)
		{
			//spriteReader->Draw();
			//spriteCoraRe->Draw();
			//spritePlayerRe->Draw();
			spriteTitle->Draw();
		}
		if (scene == 1)
		{

			spriteHud->Draw();

			//ミニマップ
			// 10月14日spriteで検索して後日クラスを作り移動せよ
			//spriteReader->Draw();
			//spriteCoraRe->Draw();
			//spritePlayerRe->Draw();

		}
		if (scene == 2)
		{
			spriteGameOver->Draw();

		}
		if (scene == 3)
		{

		}

		debTxt->DrawAll();
		// ４．描画コマンドここまで
		dxCommon->PostDraw();
	}


#pragma region WindowsAPI後始末
	winApp->Finalize();
#pragma endregion WindowsAPI後始末
	delete input;
	delete winApp;
	delete spriteCommon;
	delete inCoa;
	//delete modelChr;
	delete OBJInCoa;
	//delete objPlayer;
	return 0;
}

