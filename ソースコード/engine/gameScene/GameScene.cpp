#include "GameScene.h"

void GameScene::EngineIns(WinApp* winApp_, DirectXCommon* dxCommon_, Input* input_)
{
	//winApp = winApp_;
	dxCommon = dxCommon_;
	input = input_;

	Object3d::StaticInitialize(dxCommon->GetDev());

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);
	Object3d::SetCamera(camera);

	// カメラ注視点をセット
	camera->SetTarget({ 0, 11, -400 });
	camera->SetDistance(3.0f);
	camera->SetEye({ 0, 10, 0 });
	spriteCommon->initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), WinApp::window_width, WinApp::window_height);
	spriteCommon->LoadTexture(0, L"Resources/sprite/debugfont.png");
	//spriteCommon->LoadTexture(0, L"Resources/sprite/drawNumber.png");

	audio->Initialize();
	audio->LoadWave("thunder.wav");
	audio->LoadWave("ice1.wav");
	audio->LoadWave("BGM4.wav");
	float s = 0.05f;
	audio->SetVolume("BGM4.wav", s);
	s = 0.1f;
	audio->SetVolume("ice1.wav", s);

	debTxt = new DebugText;
	debTxt->Initialize(spriteCommon, 0);

}

void GameScene::Gameins()
{

	player->GameInitialize();
	stageWorld->GameInitialize();
	boss->GameInitialize();
	player->Update();
	angleX = 0;
	angleY = 0;
	MoveAngleY;

	scaleX = 1.0f / (float)WinApp::window_width;
	scaleY = 1.0f / (float)WinApp::window_height;
	distance = 50.0f;
	matRot = XMMatrixIdentity();
	camera->SetTarget(player->GetPlayerPos());
	camera->SetEye({ player->GetPlayerPos().x,player->GetPlayerPos().y,player->GetPlayerPos().z - distance });
	player->SetLife(player->GetLife());
	hud->SetLife(player->GetLife());
	hud->GameInitialize(50);
	time = 100;
	oldtime = 200;
	time2 = 160;
	oldtime2 = 200;
	time3 = 160;
	oldtime3 = 200;
	enemysCount = 0;
	camera->Update();
	stageWorld->Update(player->GetPlayerPos());
	stageRand1 = rnd->getRandInt(0, 13);
	stageRand2 = rnd->getRandInt(0, 13);
	if (enemys != nullptr)
	{
		enemys->Delete();
	}
	enemys = new Enemys();

}

void GameScene::StartIns(WinApp* winApp)
{
	hud->Initialize(dxCommon, winApp, input, 50);
	stageWorld->Initialize(input);
	player->Initialize(input);
	camera->SetTarget(player->GetPlayerPos());
	camera->SetEye({ player->GetPlayerPos().x,player->GetPlayerPos().y,player->GetPlayerPos().z - distance });
	boss->Initialize();
	enemys = new Enemys();
}

void GameScene::Initialize(WinApp* winApp_, DirectXCommon* dxCommon_, Input* input_)
{

	assert(winApp_);
	assert(dxCommon_);
	assert(input_);
	EngineIns(winApp_, dxCommon_, input_);

	stageRand1 = 0;
	stageRand2 = 0;
	time = 100;
	oldtime = 200;
	time2 = 160;
	oldtime2 = 200;
	time3 = 160;
	oldtime3 = 200;

	StartIns(winApp_);
	Gameins();


}

void GameScene::Update()
{

	TitleScene();

	GamePlayScene();
	explainScene();
	EndScene();
	VariableUpdate();
}

void GameScene::TitleScene()
{
	if (scene == 0)
	{
		if (hudFlag == 0 && input->TriggerMouseLeft())
		{
			
			hud->SetRadius();
			hudFlag = 1;
		}

		if (hudFlag == 2)
		{
			if (hud->GetHudFlag1(26, 14) == 0)
			{
				hudFlag = 0;
				hud->SetChangeCount();

			}
		}
		if (hudFlag == 1)
		{

			if (hud->GetChangeCount() <= 0)
			{
				scene = 4;
				hud->SetRadius();
				hudFlag = 2;
				Gameins();

			}
		}

	}

}

void GameScene::EndScene()
{
	if (scene == 2)
	{

		if (input->TriggerKey(DIK_E))
		{

			hud->SetRadius();
			hudFlag = 3;
			Gameins();
		}

		if (hudFlag == 3)
		{

			if (hud->GetHudFlag1(26, 14))
			{
				scene = 0;
				hud->SetRadius();
				hudFlag = 2;
			}
		}

		if (hudFlag == 0 && input->TriggerKey(DIK_Q))
		{
			hud->SetRadius();
			hudFlag = 1;

		}
		if (hudFlag == 1)
		{
			Gameins();
			if (hud->GetHudFlag1(26, 14))
			{
				ShowCursor(FALSE);
				scene = 6;
				hudFlag = 2;
				Gameins();

				VariableUpdate();
			}
		}

	}
	if (scene == 3)
	{
		if (input->TriggerKey(DIK_E))
		{

			hud->SetRadius();
			hudFlag = 3;
			Gameins();
		}

		if (hudFlag == 3)
		{

			if (hud->GetHudFlag1(26, 14))
			{
				scene = 0;
				hud->SetRadius();
				hud->SetChangeCount();
				hudFlag = 2;
			}
		}
	}
}

void GameScene::explainScene()
{
	if (scene == 4)
	{
		if (hudFlag == 2)
		{
			if (hud->GetHudFlag1(26, 14) == 0)
			{

				hudFlag = 0;
			}
		}
		if (hudFlag == 1)
		{
			if (hud->GetHudFlag1(24, 12) == 1)
			{
				scene = 5;
				hud->SetRadius();
				hudFlag = 2;

			}
		}
		if (hudFlag == 0 && input->TriggerMouseLeft())
		{
			hud->SetRadius();
			hudFlag = 1;
		}

	}

	if (scene == 5)
	{

		if (hudFlag == 2)
		{
			if (hud->GetHudFlag1(24, 12) == 0)
			{
				hudFlag = 0;
			}
		}



		if (hudFlag)
		{

			if (hud->GetHudFlag1(26, 14))
			{
				ShowCursor(FALSE);
				scene = 6;
				hudFlag = 2;

			}
		}
		if (hudFlag == 0 && input->TriggerMouseLeft())
		{
			hud->SetRadius();
			hudFlag = 1;
		}

	}
	if (scene == 6)
	{
		if (hudFlag == 2)
		{

			if (hud->GetHudFlag1(13, 7) == 0)
			{
				hudFlag = 0;
			}
		}

		if (hudFlag == 0 && input->TriggerMouseLeft())
		{
			scene = 1;
			audio->PlayWave("BGM4.wav", true);


		}

	}
}

void GameScene::GamePlayScene()
{
	if (scene == 1)
	{


		SetCursorPos(860, 440);

		// マウスの入力を取得
		Input::MouseMove mouseMove = input->GetMouseMove();
		float dy = mouseMove.lX * scaleY;
		MoveAngleY = dy * XM_PI;
		float dx = mouseMove.lY * scaleX;


		angleX += dx * XM_PI;
		angleY += dy * XM_PI;


		if (boss->GetBossEnemyLif() >= 41&&boss->GetBossEnemyLif() <= 50)
		{
			if (boss->GetMoveFlag() == 1 || boss->GetMoveFlag() == 2)
			{
				for (int i = 0; i < 36; i++)
				{
					if (boss->GetMoveAngle() - 0.5f < stageWorld->GetLineAllAngle(i) && boss->GetMoveAngle() + 0.5f > stageWorld->GetLineAllAngle(i))
					{
						if (rnd->getRandInt(0, 13) % 2 == 1)
						{
							stageWorld->SetLINEAll(i);

						}

					}
				}
			}
		}

		if (boss->GetBossEnemyLif() <= 40)
		{
			Stage();
		}

		if (boss->GetBossEnemyLif() <= 35 && boss->GetBossEnemyLif() > 25)
		{
			//Stage();
		}

		if (boss->GetBossEnemyLif() <= 25)
		{
			Stage();
		}

		if (boss->GetBossEnemyLif() <= 15)
		{

		}

		if (boss->GetBossEnemyLif() < 10)
		{
			Stage();
		}

		//Stage();


#pragma region playerMove
		player->PlayerMove();
		camera->SetTarget(player->GetPlayerPos());
#pragma endregion playerMove


#pragma region テストキー

#ifdef _DEBUG
		if (input->TriggerKey(DIK_3))
		{
			boss->SetBossEnemyLif(15);
		}

		if (input->TriggerKey(DIK_9))
		{
			boss->SetBossEnemyLif(50);
		}

		if (input->TriggerKey(DIK_8))
		{
			boss->SetBossEnemyLif(40);
		}

		if (input->TriggerKey(DIK_7))
		{
			boss->SetBossEnemyLif(30);
		}

		if (input->TriggerKey(DIK_6))
		{
			boss->SetBossEnemyLif(25);
		}
		if (input->TriggerKey(DIK_5))
		{
			boss->SetBossEnemyLif(15);
		}
		if (input->TriggerKey(DIK_4))
		{
			boss->SetBossEnemyLif(10);
		}

		if (input->TriggerKey(DIK_P))
		{
			//boss->SetBossEnemyLif(1);
			enemysCount = 15;
			/*for (int i = 0; i < 36; i++)
			{
				stageWorld->SetLINEAll(i);
			}*/
		}
		if (hudFlag == 0 && input->TriggerKey(DIK_0))
		{
			stageWorld->PlayerRockOnSet();
		}
#endif
		
#pragma region 当たり判定
		CollisionUp();
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

		cameraEye.x = player->GetPlayerPos().x + distance * cos(-angleY - 89.550f) * cos(angleX);
		cameraEye.z = player->GetPlayerPos().z + distance * sin(-angleY - 89.550f) * cos(angleX);
		cameraEye.y = player->GetPlayerPos().y + 2 + distance * sin(angleX);


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
				player->SetPlayerPos({ 219.0f - 33.795f,player->GetPlayerPos().y,player->GetPlayerPos().z });
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


		if (input->PushKey(DIK_D) || input->PushKey(DIK_A) || input->PushKey(DIK_W) || input->PushKey(DIK_S))
		{

			setrot = angleY + player->GetAddAngle();
			setrot *= 180 / XM_PI;
			player->SetRot({ 0.0f,setrot, 0.0f });

		}

#pragma endregion カメラ

		Boss();


		if (player->GetLife() < 1)
		{
			audio->Stop("BGM4.wav");
			audio->PlayWave("thunder.wav", 0);
			scene = 2;
			hud->SetRadius();
			ShowCursor(TRUE);

		}
		if (boss->GetBossEnemyLif() < 1)
		{

			audio->Stop("BGM4.wav");

			hudFlag = 1;

			ShowCursor(TRUE);

		}

		hud->SetLife(player->GetLife());
		hud->SetBossLife(boss->GetBossEnemyLif());

	}

	char text2[256];
	sprintf_s(text2, "angle:%f", boss->GetMoveAngle());
	debTxt->Print(text2, 0, 128, 1);

	char text3[256];
	sprintf_s(text3, "moveTime:%f", boss->GetTime());
	debTxt->Print(text3, 0, 160, 1);

}

void GameScene::VariableUpdate()
{
	input->Update();
	switch (scene)
	{
	case 0:

		if (hudFlag == 0 || hudFlag == 1)
		{
			hud->Update();
			
		}
		
		if (hudFlag == 1)
		{
			hud->HudUpdate(0);
			if (hud->GetHudFlag1(26, 14))
			{
				camera->Update();
				player->Update();
				stageWorld->Update(player->GetPlayerPos());
				boss->Update(player->GetPlayerPos());
			}

		}
		if (hudFlag == 2)
		{
			hud->HudUpdate(1);

		}

		break;

	case 1:
		camera->Update();
		player->Update();
		hud->Update();
		stageWorld->Update(player->GetPlayerPos());
		if (enemysCount >= 15)
		{
			boss->Update(player->GetPlayerPos());
			if (boss->GetBossEnemyLif() >= 27)
			{
				enemys->Update(20, player->GetPlayerPos(), boss->GetBossEnemyLif());
			}
			else
			{
				enemys->Update(22, player->GetPlayerPos(), boss->GetBossEnemyLif());
			}
		}
		else if(enemysCount >7&&enemysCount <15)
		{
			enemys->Update(22, player->GetPlayerPos(), boss->GetBossEnemyLif());

		}
		else
		{
			enemys->Update(20, player->GetPlayerPos(), boss->GetBossEnemyLif());

		}
		EnemysUp();
		
		if (hudFlag == 1)
		{
			hud->HudUpdate(20);
			if (hud->GetHudFlag1(26, 14))
			{
				hudFlag = 2;
				hud->SetRadius();
				audio->PlayWave("ice1.wav", 0);

				scene = 3;
			}

		}
		break;
	case 2:
		if (hudFlag == 3)
		{
			hud->HudUpdate(2);
		}
		if (hudFlag == 1)
		{
			hud->HudUpdate(2);
		}
		camera->Update();
		player->Update();
		stageWorld->StageUpdate();
		boss->Update(player->GetPlayerPos());

		break;

	case 3:
		if (hudFlag == 2)
		{
			hud->HudUpdate(21);

		}
		if (hudFlag == 3)
		{
			hud->HudUpdate(2);
		}
		if (hud->GetHudFlag1(26, 14))
		{
			camera->Update();
			player->Update();
			stageWorld->Update(player->GetPlayerPos());
			boss->Update(player->GetPlayerPos());
		}
		stageWorld->StageUpdate();

		break;

	case 4:
		if (hudFlag == 2)
		{
			hud->HudUpdate(1);
		}
		if (hudFlag == 1)
		{
			hud->HudUpdate(3);
		}
		break;

	case 5:
		if (hudFlag == 2)
		{
			hud->HudUpdate(4);
		}

		if (hudFlag == 1)
		{
			hud->HudUpdate(2);
		}
		break;

	case 6:

		if (hudFlag == 2)
		{
			hud->HudUpdate(6);
			hud->Update();
		}

		break;

	default:
		break;
	}



}

void GameScene::Draw()
{

	Object3d::PreDraw(dxCommon->GetCmdList());
	player->Draw(scene);
	
	boss->Draw(scene,enemysCount);
	if (scene == 1)
	{
		enemys->Draw();
	}
	stageWorld->Draw(scene);


	Object3d::PostDraw();

	spriteCommon->PreDraw();

	hud->Draw(scene);

	// ４．描画コマンドここまで


}

void GameScene::Delete()
{
	player->Delete();
	stageWorld->StageAllDelete();
	boss->Delete();

	enemys->Delete();
	hud->Delete();
	audio->Finalize();
	delete debTxt;
	delete camera;
	delete hud;

	delete boss;

	delete player;
	delete stageWorld;
	delete enemys;
	enemys = nullptr;
	delete spriteCommon;

}

void GameScene::Stage()
{
	stageRand1 = rnd->getRandInt(0, 13);
	stageRand2 = rnd->getRandInt(0, 13);

	if (boss->GetMoveFlag() == 1 || boss->GetMoveFlag() == 2)
	{
		for (int i = 0; i < 36; i++)
		{
			if (boss->GetMoveAngle() - 0.5f < stageWorld->GetLineAllAngle(i) && boss->GetMoveAngle() + 0.5f > stageWorld->GetLineAllAngle(i))
			{
				if (rnd->getRandInt(0, 13) % 2 == 1)
				{
					stageWorld->SetLINEAll(i);

				}

			}
		}
	}



	if (boss->GetBossEnemyLif() < 25)
	{
		time -= 4;
	}
	else
	{
		time--;
	}
	if (boss->GetBossEnemyLif() < 17)
	{
		time2 -= rnd->getRandInt(1, 3);
		time3 -= rnd->getRandInt(0, 3);
	}
	else if (boss->GetBossEnemyLif() > 17 && boss->GetBossEnemyLif() < 25)
	{
		time2 -= rnd->getRandInt(0, 1);
		time3 -= rnd->getRandInt(0, 1);

	}

	if (time < 1)
	{
		time = oldtime;

		if (boss->GetBossEnemyLif() < 25)
		{
			oldtime = rnd->getRandInt(30, 95);
		}
		stageWorld->SetHeightLineCase(stageRand1);

	}
	if (time2 < 1)
	{
		time2 = oldtime2;
		if (boss->GetBossEnemyLif() < 17)
		{
			oldtime2 = rnd->getRandInt(30, 95);

		}
		stageWorld->SetWidthLineCase(stageRand2);
	}
	if (time3 < 1)
	{
		time3 = oldtime3;
		oldtime3 = rnd->getRandInt(30, 95);
		stageWorld->PlayerRockOnSet();
	}

	if (boss->GetAtkFlag() == 2 && setflag == 0)
	{
		stageWorld->ALLSetImpact({ 0,0,-242 }, 1, 1);
		setflag = 1;
	}
	if (boss->GetAtkFlag() != 2 && setflag == 1)
	{
		setflag = 0;
	}
}

void GameScene::Boss()
{
	//ボスの
#pragma region ランダムな足攻撃
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
#pragma endregion ランダムな足攻撃
}

void GameScene::EnemysUp()
{
	//雑魚敵とプレイヤーの弾の当たり判定
	for (auto& battleEnemy : enemys->GetBattleEnemys())
	{
		for (int i = 0; i < 30; i++)
		{
			if (player->GetBulletFlag(i) == 1)
			{
				bool isHit = Collision::HitSphere(player->GetBulletPos(i), 4, battleEnemy->GetPos(), 5);
				if (isHit)
				{
					player->SetBulletFlag(i, 0);
					battleEnemy->OnCollisionBullet();
				}
			}
		}
	}

	for (auto& stayEnemy : enemys->GetStayEnemys())
	{
		for (int i = 0; i < 30; i++)
		{
			if (player->GetBulletFlag(i) == 1)
			{
				bool isHit = Collision::HitSphere(player->GetBulletPos(i), 4, stayEnemy->GetPos(), 8);
				if (isHit)
				{
					audio->Stop("ice1.wav");
					audio->PlayWave("ice1.wav", 0);
					enemysCount++;
					player->SetBulletFlag(i, 0);
					stayEnemy->OnCollisionBullet();
				}
			}
		}
	}

	for (auto& spinEnemy : enemys->GetSpinEnemys())
	{
		for (int i = 0; i < 30; i++)
		{
			if (player->GetBulletFlag(i) == 1)
			{
				bool isHit = Collision::HitSphere(player->GetBulletPos(i), 4, spinEnemy->GetPos(), 8);
				if (isHit)
				{
					
					audio->Stop("ice1.wav");
					audio->PlayWave("ice1.wav", 0);
					enemysCount++;
					player->SetBulletFlag(i, 0);
					spinEnemy->OnCollisionBullet();
				}
			}
		}
	}

}

void GameScene::CollisionUp()
{
	//プレイヤーとステージの当たり判定
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

					bool isHit = Collision::HitCircle(pTemp, 5, temp, 2, 2);
					if (isHit)
					{
						player->SetDamegeFlag(1);
						player->SetLife(player->GetLife() - 1);

					}
				}
			}
		}
	}

	//雑魚敵たちとプレイヤーの当たり判定
	for (auto& stayEnemy : enemys->GetStayEnemys())
	{
		for (auto& bullet : stayEnemy->GetBullets())
		{
			bool isHit = Collision::HitSphere(player->GetPlayerPos(), 4, bullet->GetPos(), 3);
			if (isHit)
			{
				player->SetDamegeFlag(2);
				player->SetLife(player->GetLife() - 1);
				bullet->SetHitFlag(true);
			}
		}

	}

	for (auto& spinEnemy : enemys->GetSpinEnemys())
	{
		for (auto& bullet : spinEnemy->GetBullets())
		{
			bool isHit = Collision::HitSphere(player->GetPlayerPos(), 4, bullet->GetPos(), 3);
			if (isHit)
			{
				player->SetDamegeFlag(2);
				player->SetLife(player->GetLife() - 1);
				bullet->SetHitFlag(true);
			}
		}

	}


	//ボスの足の攻撃とプレイヤーとの当たり判定
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
				player->SetLife(player->GetLife() - 1);
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

				player->SetLife(player->GetLife() - 1);
			}
		}
	}

	//プレイヤーの弾とボスの当たり判定
	if (enemysCount >= 15)
	{
		for (int i = 0; i < 30; i++)
		{
			if (player->GetBulletFlag(i) == 1)
			{
				bool isHit = Collision::HitSphere(player->GetBulletPos(i), 4, boss->GetBossPos(), 10);
				if (isHit)
				{
					player->SetBulletFlag(i, 0);
					boss->SetBossEnemyLif(boss->GetBossEnemyLif() - 1);
					boss->SetDamegeFlag(1);
				}
			}
		}
	}
	
}
