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
#include"BossEnemy.h"
#include"Hud.h"

#include<random>
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
	spriteCommon->LoadTexture(0, L"Resources/debugfont.png");
	DebugText* debTxt = new DebugText;

	debTxt->Initialize(spriteCommon, 0);

	Hud* hud = new Hud();
	hud->Initialize(dxCommon, winApp);



	//Model* inCoa = Model::LoadFromOBJ("core_in");
	//Model* modelGround = Model::LoadFromOBJ("ground");
	//Model* modelBack = Model::LoadFromOBJ("back");
	////Model* modelCloud = Model::LoadFromOBJ("cloud");
	//Model* modelTerritory = Model::LoadFromOBJ("territory");
	//
	//Model* modelAtkHud = Model::LoadFromOBJ("atkHad");


	float radius = 500.0f;
	float angle[200] = {};


	camera->SetEye({ 0, 10, 0 });


#pragma endregion 描画初期化処理



	//int scene = 0;
	int scene = 0;


	//音
	Audio* audio = Audio::GetInstance();
	audio->Initialize();
	audio->LoadWave("thunder.wav");
	audio->LoadWave("BGM4.wav");
	float s = 0.1f;
	audio->SetVolume("BGM4.wav", s);
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
	int b = 0;

	int time = 100;
	int oldtime = 100;
	int time2 = 100;
	int oldtime2 = 100;

	UINT gameFlag = 0;

	float addAngle = -89.550f;
	float setrot = 0;

	bool jampFlag = 0, damegeFlag = 0;
	float jamp = 7.0f, damegejamp = 13.0f;
#pragma region bossEnemy

	BossEnemy* boss = new BossEnemy();
	boss->Initialize();
	bool setflag{};

#pragma endregion bossEnemy

	std::random_device rnd;
	std::mt19937_64 mt(rnd());
	std::uniform_int_distribution<> rand100(0, 99);

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

		if (scene == 0)
		{


			if (input->PushKey(DIK_RETURN))
			{
				//scene = 1;
			//	audio->PlayWave("BGM4.wav", true);

			}
			if (input->TriggerMouseLeft())
			{
				scene = 1;
				audio->PlayWave("BGM4.wav", true);


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



			// マウスの入力を取得
			Input::MouseMove mouseMove = input->GetMouseMove();
			float dy = mouseMove.lX * scaleY;
			MoveAngleY = dy * XM_PI;
			float dx = mouseMove.lY * scaleX;


			angleX += dx * XM_PI;
			angleY += dy * XM_PI;

			float angley = mouseMove.lX * 0.1f * 5;

			time--;
			time2--;
			a = rand() % 14;
			b = rand() % 14;
			if (time < 1)
			{
				time = oldtime;
				//oldtime = rand() % 15 + rand() % 50 + 30; - 33.795f
				oldtime = 120;


				stageWorld->SetHeightLineCase(a);

			}
			if (time2 < 1)
			{
				time2 = oldtime2;
				oldtime2 = rand() % 15 + rand() % 50 + 30;
				//oldtime2 = 120;


				stageWorld->SetWidthLineCase(b);

			}

			// ボタンが押されていたらカメラを並行移動させる
#pragma region playerMove
			player->PlayerMove();

#pragma endregion playerMove

#pragma region テストキー

			camera->SetTarget(player->GetPlayerPos());
			if (input->PushKey(DIK_ESCAPE))
			{
				break;
			}

			//if (input->TriggerKey(DIK_1))
			//{
			//	stageWorld->SetWidthLineCase(4);
			//	stageWorld->SetHeightLineCase(4);
			//	stageWorld->SetWidthLineCase(11);
			//	stageWorld->SetHeightLineCase(11);

			//}
			//if (input->PushKey(DIK_2))
			//{
			//	stageWorld->SetWidthLineCase(9);

			//}
			//if (input->TriggerKey(DIK_3))
			//{
			//	//stageWorld->SetWidthLineCase(13);
			//	boss->SetAtkShot(2);
			//}
			if (boss->GetAtkFlag() == 2&& setflag ==0)
			{
				stageWorld->ALLSetImpact({ 0,0,-242 }, 1, 1);
				setflag = 1;
			}
			if (boss->GetAtkFlag() != 2 && setflag == 1)
			{
				setflag = 0;
			}
			if (input->TriggerKey(DIK_4))
			{
				setflag = 0;
				//stageWorld->SetWidthLineCase(13);
				boss->SetMoveFlag(4);
			}
			//if (input->PushMouseLeft())
			//{
			//	//stageWorld->SetHeightLineCase(11);

			//	//stageWorld->SetHeightLineCase(a);
			//	//stageWorld->ALLSetImpact(PlayerPos, 1, 1);

			//}

			
#pragma endregion テストキー

#pragma region 当たり判定
			for (int i = 0; i < 50; i++)
			{
				for (int j = 0; j < 50; j++)
				{
					if (player->GetDamegeFlag() == 0)
					{
						XMFLOAT3 temp = stageWorld->GetPosition(i, j);
						temp.y += 140.0f;
						//bool isHit = Collision::HitCircle(stageWorld->GetPosition(i, j), 0, player->GetPlayerPos(), 0, 2);
						bool isHit = Collision::HitCircle(player->GetPlayerPos(), 5, temp, 2, 2);
						if (isHit)
						{
							player->SetDamegeFlag(1);
							damegeFlag = 1;
							gameFlag = gameFlag + 1;
						}
					}
				}
			}

			for (int i = 0; i < 5; i++)
			{
				if (boss->GetShotFlag(i) == 1)
				{
					bool isHit = Collision::HitSphere(player->GetPlayerPos(), 3, boss->GetShotPos(i), 3);
					if (isHit)
					{
						player->SetDamegeFlag(1);
						damegeFlag = 1;
						gameFlag = gameFlag + 1;
					}
				}
			}

			if (boss->GetSShotFlag() == 1)
			{
				for (int i = 0; i < 50; i++)
				{
					for (int j = 0; j < 50; j++)
					{

						bool stageHit = Collision::HitCircle(stageWorld->GetPosition(i, j), 5, boss->GetSShotPos(), 3, 1);
						if (stageHit)
						{

							stageWorld->SetStageFlag(i, j, 1);
						}
					}
				}

				bool isHit = Collision::HitSphere(player->GetPlayerPos(), 3, boss->GetSShotPos(), 3);
				if (isHit)
				{
					player->SetDamegeFlag(1);
					damegeFlag = 1;
					gameFlag = gameFlag + 1;
				}
			}

			if (boss->GetAtkFlag() == 2)
			{
				for (int i = 0; i < 8; i++)
				{
					XMFLOAT3 pos = { boss->GetArm1(i).x,boss->GetArm1(i).y + 10.0f,boss->GetArm1(i).z };

					bool isHit = Collision::HitSphere(player->GetPlayerPos(), 3, pos, 1);
					if (isHit)
					{
						player->SetDamegeFlag(1);
						damegeFlag = 1;
						gameFlag = gameFlag + 1;
					}
				}
			}

			if (boss->GetAtkFlag() == 3)
			{
				for (int i = 0; i < 32; i++)
				{
					XMFLOAT3 pos = { boss->GetArm2(i).x,boss->GetArm2(i).y + 10.0f,boss->GetArm2(i).z };
					bool isHit = Collision::HitSphere(player->GetPlayerPos(), 3, pos, 1);
					if (isHit)
					{
						player->SetDamegeFlag(1);
						damegeFlag = 1;
						gameFlag = gameFlag + 1;
					}
				}
			}
#pragma endregion 当たり判定


#pragma region カメラ
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


			if (cameraEye.y - player->GetPlayerPos().y < -1.5)
			{
				cameraEye.y = player->GetPlayerPos().y - 1.0f;
				camera->SetEye(cameraEye);
			}
			else
			{
				camera->SetEye(cameraEye);

			}
			if (input->TriggerKey(DIK_SPACE) && jampFlag == 0 && damegeFlag == 0)
			{
				jampFlag = 1;

				//audio->PlayWave("thunder.wav", false);

			}
			if (jampFlag == 1)
			{
				//XMVECTOR move = { 0, jamp, 0, 0 };
				//move = XMVector3TransformNormal(move, matRot);
				//cameraEye.x += move.m128_f32[0];
				//cameraEye.y += move.m128_f32[1];
				//cameraEye.z += move.m128_f32[2];
				////camera->SetTarget(playerPos);
				////objCloud->MoveVector(move);
				//jamp -= 0.5f;
				//if (jamp < -7.0f)
				//{
				//	//audio->Stop("thunder.wav");

				//	jampFlag = 0;
				//	jamp = 7.0f;
				//}
			}
			if (damegeFlag == 1)
			{
				//XMVECTOR move = { 0, damegejamp, 0, 0 };
				//move = XMVector3TransformNormal(move, matRot);
				//cameraEye.x += move.m128_f32[0];
				//cameraEye.y += move.m128_f32[1];
				//cameraEye.z += move.m128_f32[2];
				////camera->SetTarget(playerPos);
				////objCloud->MoveVector(move);
				//damegejamp -= 0.5f;
				//if (damegejamp < -13.0f)
				//{
				//	//audio->Stop("thunder.wav");

				//	damegeFlag = 0;
				//	damegejamp = 13.0f;
				//}
			}
			matRot = player->GetMatRot();
			XMMATRIX matRotNew = XMMatrixIdentity();

			matRotNew *= XMMatrixRotationY(MoveAngleY);

			matRot = matRotNew * matRot;

			player->SetMatRot(matRot);

			bool rightHit = Collision::HitWorld(player->GetPlayerPos().x, 219.0f - 33.795f, 1);
			bool leftHit = Collision::HitWorld(player->GetPlayerPos().x, -150.0f - 33.795f, 0);
			bool frontHit = Collision::HitWorld(player->GetPlayerPos().z, -30.0f, 1);
			bool buckHit = Collision::HitWorld(player->GetPlayerPos().z, -453.0f, 0);
			if (rightHit || leftHit || frontHit || buckHit)
			{

				if (rightHit)
				{
					player->SetPlayerPos({ 219.0f - 33.795,player->GetPlayerPos().y,player->GetPlayerPos().z });
				}
				if (leftHit)
				{
					player->SetPlayerPos({ -150.0f - 33.795f,player->GetPlayerPos().y,player->GetPlayerPos().z });

				}
				if (frontHit)
				{
					player->SetPlayerPos({ player->GetPlayerPos().x,player->GetPlayerPos().y,-30.0f });

				}
				if (buckHit)
				{
					player->SetPlayerPos({ player->GetPlayerPos().x,player->GetPlayerPos().y,-453.0f });
				}
			}

#pragma endregion カメラ


#pragma region 隙間
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

#pragma endregion 隙間


			if (input->PushKey(DIK_0))
			{

			}
			if (input->PushKey(DIK_D) || input->PushKey(DIK_A) || input->PushKey(DIK_W) || input->PushKey(DIK_S))
			{

				setrot = angleY + player->GetAddAngle();
				setrot *= 180 / XM_PI;
				player->SetRot({ 0.0f,setrot, 0.0f });
				hud->PlayerMove(setrot);
			}




#pragma region 隙間

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


#pragma endregion 隙間

			/*if (gameFlag > 3)
			{
				audio->Stop("BGM4.wav");
				audio->PlayWave("thunder.wav", 0);
				scene = 2;
			}*/

			/*float temp = sqrt(pow(player->GetPlayerPos().x - camera->GetEye().x, 2) + pow(player->GetPlayerPos().y - camera->GetEye().y, 2) + pow(player->GetPlayerPos().z - camera->GetEye().z, 2));
			if (temp >= 50)
			{
				distance = 50.0f;
			}*/


			/*char text1[256];
			sprintf_s(text1, "angle%f angle%f distance%f camera:%f playerY:%f", angleY, boss->GetAngle(), temp, camera->GetEye().y, player->GetPlayerPos().y);
			debTxt->Print(text1, 0, 0, 1);*/

			///*	char text2[256];
			//	sprintf_s(text2, "time%f flag%c", boss->GetTime(),boss->GetFlag());
			//	debTxt->Print(text2, 0, 32, 1);*/

			//char text3[256];
			//sprintf_s(text3, "playerX%f playerY%f playerZ%f A(rand)%d", player->GetPlayerPos().x, player->GetPlayerPos().y, player->GetPlayerPos().z, a);
			//debTxt->Print(text3, 0, 64, 1);

			/*char text1[256];
			sprintf_s(text1, "x%f y%f z%f flag %c", boss->GetBossPos().x, boss->GetBossPos().y, boss->GetBossPos().z,boss->GetAtkFlag());
			debTxt->Print(text1, 0, 0, 1);*/
			stageWorld->Update();
			boss->Update();
		}

		if (scene == 2)
		{


			if (input->PushKey(DIK_ESCAPE))
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

		player->Update();



	/*	stageWorld->Update();
		player->Update();*/
		hud->Update();
		//objPlayer->Update();

		//spritePlayerRe->Update();
		//spriteCoraRe->Update();
		/*spriteGameOver->Update();
		spriteHud->Update();
		spriteTitle->Update();*/
		
		//boss->Update();
		// DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理

#pragma region グラフィックスコマンド

		dxCommon->PreDraw();

		Object3d::PreDraw(dxCommon->GetCmdList());
		if (scene == 0)
		{

			//	objPlayer->Draw();

		}
		if (scene == 1)
		{
			//	Object3d::PreDraw(dxCommon->GetCmdList());


			player->Draw();
			boss->Draw();

			stageWorld->Draw();


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
		hud->Draw(scene);

		debTxt->DrawAll();
		// ４．描画コマンドここまで
		dxCommon->PostDraw();
	}
	player->Delete();
	stageWorld->Delete();
	boss->Delete();
	hud->Delete();
#pragma region WindowsAPI後始末
	winApp->Finalize();
#pragma endregion WindowsAPI後始末
	audio->Finalize();
	delete debTxt;
	delete camera;
	delete hud;

	//delete spriteGameOver;
	//delete 	spriteTitle, spriteHud;

	delete boss;
	//delete modelBack, modelAtkHud, modelGround;
	delete player;
	delete stageWorld;
	delete input;
	delete winApp;
	delete spriteCommon;
	//delete inCoa;
	//delete modelChr;
	//delete OBJInCoa;
	//delete objPlayer;
	return 0;
}

