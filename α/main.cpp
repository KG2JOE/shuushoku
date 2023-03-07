
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
	//spriteCommon->LoadTexture(0, L"Resources/debugfont.png");
	spriteCommon->LoadTexture(0, L"Resources/sprite/drawNumber.png");
	DebugText* debTxt = new DebugText;

	debTxt->Initialize(spriteCommon, 0);

	Hud* hud = new Hud();
	hud->Initialize(dxCommon, winApp, 50);



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

#pragma region 音
	//音
	Audio* audio = Audio::GetInstance();
	audio->Initialize();
	audio->LoadWave("thunder.wav");
	audio->LoadWave("ice1.wav");
	audio->LoadWave("BGM4.wav");
	float s = 0.05f;
	audio->SetVolume("BGM4.wav", s);

#pragma endregion 音

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
	int oldtime = 200;
	int time2 = 160;
	int oldtime2 = 200;
	int time3 = 160;
	int oldtime3 = 200;

	UINT gameFlag = 20;


	float addAngle = -89.550f;
	float setrot = 0;


	float jamp = 7.0f, damegejamp = 13.0f;
#pragma region bossEnemy

	BossEnemy* boss = new BossEnemy();
	boss->Initialize();
	bool setflag{};

#pragma endregion bossEnemy

#pragma region RndCreate

	RndCreate* rnd = new RndCreate();

#pragma endregion RndCreate

	bool hudFlag = 0;


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
		if (scene == 4)
		{
			if (input->TriggerMouseRight())
			{
				scene = 1;
				audio->PlayWave("BGM4.wav", true);


			}
		}
		if (scene == 0)
		{
			if (input->TriggerKey(DIK_SPACE))
			{
				hud->SetRadius();
				hudFlag = 1;
			}

			if (input->TriggerKey(DIK_P))
			{
				hudFlag = 0;
				hud->SetRadius();
			}

			if (hudFlag)
			{
				hud->HudUpdate(0);
			}
			if (hudFlag ==0)
			{
				hud->HudUpdate(1);
			}
			if (input->PushKey(DIK_RETURN))
			{
				//scene = 1;
			//	audio->PlayWave("BGM4.wav", true);

			}
			if (input->TriggerMouseRight())
			{
				scene = 4;
				//audio->PlayWave("BGM4.wav", true);
				player->GameInitialize();
				stageWorld->GameInitialize();
				boss->GameInitialize();

				angleX = 0;
				angleY = 0;
				MoveAngleY;

				scaleX = 1.0f / (float)WinApp::window_width;
				scaleY = 1.0f / (float)WinApp::window_height;
				distance = 50.0f;
				matRot = DirectX::XMMatrixIdentity();
				camera->SetTarget(player->GetPlayerPos());
				camera->SetEye({ player->GetPlayerPos().x,player->GetPlayerPos().y,player->GetPlayerPos().z - distance });
				gameFlag = 20;
				hud->SetLife(gameFlag);
				hud->GameInitialize(50);
				time = 100;
				oldtime = 200;
				time2 = 160;
				oldtime2 = 200;
				time3 = 160;
				oldtime3 = 200;
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


			/*a = rand() % 14;
			b = rand() % 14;*/
			a = rnd->getRandInt(0, 13);
			b = rnd->getRandInt(0, 13);
			time--;
			if (boss->GetBossEnemyLif() < 25)
			{
				time -= 4;
			}
			if (boss->GetBossEnemyLif() < 17)
			{
				time2 -= 3;
				time3 -= 2;
			}

			if (time < 1)
			{
				time = oldtime;
				//oldtime = rand() % 15 + rand() % 50 + 30; - 33.795f
				if (boss->GetBossEnemyLif() < 25)
				{
					oldtime = rnd->getRandInt(30, 95);

				}


				stageWorld->SetHeightLineCase(a);
				stageWorld->SetWidthLineCase(b);
				//stageWorld->PlayerRockOnSet();

			}
			if (time2 < 1)
			{
				time2 = oldtime2;
				//oldtime2 = rand() % 15 + rand() % 50 + 30;
				//oldtime2 = 120;
				if (boss->GetBossEnemyLif() < 17)
				{
					oldtime2 = rnd->getRandInt(30, 95);

				}

				//stageWorld->SetWidthLineCase(b);

			}
			if (time3 < 1)
			{
				time3 = oldtime3;
				//oldtime2 = rand() % 15 + rand() % 50 + 30;
				//oldtime2 = 120;
				oldtime3 = rnd->getRandInt(30, 95);


				stageWorld->PlayerRockOnSet();

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

			//if (input->TriggerKey(DIK_3))
			//{
			//	setflag = 0;
			//	//stageWorld->SetWidthLineCase(13);
			//	boss->SetMoveFlag(4);
			//}
			//if (input->PushMouseLeft())
			//{
			//	//stageWorld->SetHeightLineCase(11);

			//	//stageWorld->SetHeightLineCase(a);
			//	//stageWorld->ALLSetImpact(PlayerPos, 1, 1);

			//}

			if (input->TriggerKey(DIK_3))
			{

				stageWorld->PlayerRockOnSet();
				//boss->SetAtkShot(3);
			//	stageWorld->SetHeightLineCase(a);
			//	stageWorld->SetWidthLineCase(b);
				//stageWorld->SetWidthLineCase(9);
			}
#pragma endregion テストキー

			if (boss->GetAtkFlag() == 2 && setflag == 0)
			{
				stageWorld->ALLSetImpact({ 0,0,-242 }, 1, 1);
				setflag = 1;
			}
			if (boss->GetAtkFlag() != 2 && setflag == 1)
			{
				setflag = 0;
			}
#pragma region 当たり判定
			if (player->GetDamegeFlag() == 0)
			{


				for (int i = 0; i < 50; i++)
				{
					for (int j = 0; j < 50; j++)
					{
						if (player->GetDamegeFlag() == 0)
						{
							XMFLOAT3 temp = stageWorld->GetPosition(i, j);
							temp.y += 140.0f;
							XMFLOAT3 pTemp = { player->GetPlayerPos().x,player->GetPlayerPos().y - 2.5f,player->GetPlayerPos().z };
							//bool isHit = Collision::HitCircle(stageWorld->GetPosition(i, j), 0, player->GetPlayerPos(), 0, 2);
							bool isHit = Collision::HitCircle(pTemp, 5, temp, 2, 2);
							if (isHit)
							{
								player->SetDamegeFlag(1);

								gameFlag = gameFlag - 1;
							}
						}
					}
				}
			}
			if (player->GetDamegeFlag() == 0)
			{
				for (int i = 0; i < 5; i++)
				{
					if (boss->GetShotFlag(i) == 1)
					{
						bool isHit = Collision::HitSphere(player->GetPlayerPos(), 4, boss->GetShotPos(i), 3);
						if (isHit)
						{
							player->SetDamegeFlag(1);

							gameFlag = gameFlag - 1;
							boss->SetShotFlag(i, 0);
						}
					}
				}
			}

			if (player->GetDamegeFlag() == 0)
			{
				for (int i = 0; i < 5; i++)
				{
					if (boss->GetPShotFlag(i) >= 1)
					{
						bool isHit = Collision::HitSphere(player->GetPlayerPos(), 4, boss->GetPshotPos(i), 3);
						if (isHit)
						{
							player->SetDamegeFlag(1);

							gameFlag = gameFlag - 1;
							boss->SetPShotFlag(i, 0);
						}
					}
				}
			}

			if (player->GetDamegeFlag() == 0)
			{
				for (int i = 0; i < 5; i++)
				{
					if (boss->GetPAshotFlag(i) >= 1)
					{
						bool isHit = Collision::HitSphere(player->GetPlayerPos(), 4, boss->GetPAshotPos(i), 3);
						if (isHit)
						{
							player->SetDamegeFlag(1);

							gameFlag = gameFlag - 1;
							boss->SetPAShotFlag(i, 0);
						}
					}
				}
			}

			if (boss->GetSShotFlag() == 1)
			{
				/*for (int i = 0; i < 50; i++)
				{
					for (int j = 0; j < 50; j++)
					{

						bool stageHit = Collision::HitCircle(stageWorld->GetPosition(i, j), 5, boss->GetSShotPos(), 3, 1);
						if (stageHit)
						{

							stageWorld->SetStageFlag(i, j, 1);
						}
					}
				}*/
				if (player->GetDamegeFlag() == 0)
				{

					XMFLOAT3 pTemp = { player->GetPlayerPos().x,player->GetPlayerPos().y - 2.5f,player->GetPlayerPos().z };

					bool isHit = Collision::HitSphere(pTemp, 4, boss->GetSShotPos(), 3);
					if (isHit)
					{
						player->SetDamegeFlag(1);

						gameFlag = gameFlag - 1;
					}
				}
			}

			if (boss->GetAtkFlag() == 2 && player->GetDamegeFlag() == 0)
			{
				for (int i = 0; i < 8; i++)
				{
					XMFLOAT3 pos = { boss->GetArm1(i).x,boss->GetArm1(i).y + 10.0f,boss->GetArm1(i).z };
					XMFLOAT3 pTemp = { player->GetPlayerPos().x,player->GetPlayerPos().y - 2.5f,player->GetPlayerPos().z };

					bool isHit = Collision::HitSphere(pTemp, 4, pos, 1);
					if (isHit)
					{
						player->SetDamegeFlag(1);

						gameFlag = gameFlag - 1;
					}
				}
			}

			if (boss->GetAtkFlag() == 3 && player->GetDamegeFlag() == 0)
			{
				for (int i = 0; i < 32; i++)
				{
					XMFLOAT3 pos = { boss->GetArm2(i).x,boss->GetArm2(i).y + 10.0f,boss->GetArm2(i).z };
					XMFLOAT3 pTemp = { player->GetPlayerPos().x,player->GetPlayerPos().y - 2.5f,player->GetPlayerPos().z };

					bool isHit = Collision::HitSphere(pTemp, 4, pos, 1);
					if (isHit)
					{
						player->SetDamegeFlag(1);

						gameFlag = gameFlag - 1;
					}
				}
			}
			for (int i = 0; i < 30; i++)
			{
				if (player->GetBulletFlag(i) == 1)
				{
					bool isHit = Collision::HitSphere(player->GetBulletPos(i), 4, boss->GetBossPos(), 10);
					if (isHit)
					{
						player->SetBulletFlag(i, 0);
						boss->SetBossEnemyLif(boss->GetBossEnemyLif() - 1);
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

			matRot = player->GetMatRot();
			XMMATRIX matRotNew = XMMatrixIdentity();

			matRotNew *= XMMatrixRotationY(MoveAngleY);
			if (input->TriggerMouseLeft())
			{
				player->SetBulletAngole(MoveAngleY);

			}
			matRot = matRotNew * matRot;

			player->SetMatRot(matRot);

			bool rightHit = Collision::HitWorld(player->GetPlayerPos().x, 219.0f - 33.795f, 1);
			bool leftHit = Collision::HitWorld(player->GetPlayerPos().x, -150.0f - 33.795f, 0);
			bool frontHit = Collision::HitWorld(player->GetPlayerPos().z, -22.0f, 1);
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
					player->SetPlayerPos({ player->GetPlayerPos().x,player->GetPlayerPos().y,-22.0f });

				}
				if (buckHit)
				{
					player->SetPlayerPos({ player->GetPlayerPos().x,player->GetPlayerPos().y,-453.0f });
				}
			}

#pragma endregion カメラ


#pragma region 隙間
			for (int i = 0; i < 32; i++)
			{
				int x = rnd->getRandInt(0, 49);
				int z = rnd->getRandInt(0, 49);
				if (boss->GetArm2Flag(i) == 0 && boss->GetAtkFlag() == 3)
				{

					float posX = stageWorld->GetPosition(x, z).x;
					float posZ = stageWorld->GetPosition(x, z).z;
					stageWorld->SetModel(x, z);
					boss->SetArm2(i, { posX,-14 ,posZ });
					boss->SetArm2Flag(i, 1);
					boss->SetArm2OccurrenceTime(i);
					break;
				}

				if (boss->GetArm2OccurrenceTime(i) == 30, boss->GetArm2posY(i) == -15 && boss->GetArm2Flag(i) == 2)
				{
					XMFLOAT2 pos = { boss->GetArm2(i).x ,boss->GetArm2(i).z };
					for (int j = 0; j < 50; j++)
					{
						for (int w = 0; w < 50; w++)
						{
							XMFLOAT2 pos2 = { stageWorld->GetPosition(j, w).x,stageWorld->GetPosition(j, w).z };

							if (pos.x == pos2.x && pos.y == pos2.y)
							{
								stageWorld->SetModel2(j, w);
								boss->SetArm2Flag(i, 0);
							}
						}
					}

				}

			}
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



			if (gameFlag < 1)
			{
				audio->Stop("BGM4.wav");
				audio->PlayWave("thunder.wav", 0);
				scene = 2;
			}
			if (boss->GetBossEnemyLif() < 1)
			{
				audio->Stop("BGM4.wav");
				audio->PlayWave("ice1.wav", 0);
				scene = 3;
			}

			hud->SetLife(gameFlag);
			hud->SetBossLife(boss->GetBossEnemyLif());
			hud->Update();

			stageWorld->Update(player->GetPlayerPos());
			//boss->Update(player->GetPlayerPos());
		}

		if (scene == 2)
		{



			if (input->TriggerMouseRight())
			{
				scene = 0;
			}
		}
		if (scene == 3)
		{
			if (input->TriggerMouseRight())
			{
				scene = 0;

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
		debTxt->DrawAll();

		hud->Draw(scene);

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

