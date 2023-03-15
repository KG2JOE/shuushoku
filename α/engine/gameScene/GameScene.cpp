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
	//spriteCommon->LoadTexture(0, L"Resources/debugfont.png");
	spriteCommon->LoadTexture(0, L"Resources/sprite/drawNumber.png");

	audio->Initialize();
	audio->LoadWave("thunder.wav");
	audio->LoadWave("ice1.wav");
	audio->LoadWave("BGM4.wav");
	float s = 0.05f;
	audio->SetVolume("BGM4.wav", s);



}

void GameScene::Gameins()
{
	player->GameInitialize();
	stageWorld->GameInitialize();
	boss->GameInitialize();

	angleX = 0;
	angleY = 0;
	MoveAngleY;

	scaleX = 1.0f / (float)WinApp::window_width;
	scaleY = 1.0f / (float)WinApp::window_height;
	distance = 50.0f;
	matRot = XMMatrixIdentity();
	camera->SetTarget(player->GetPlayerPos());
	camera->SetEye({ player->GetPlayerPos().x,player->GetPlayerPos().y,player->GetPlayerPos().z - distance });
	player->SetLife(player->GetLife());//gameFlag = 20;
	hud->SetLife(player->GetLife());
	hud->GameInitialize(50);
	time = 100;
	oldtime = 200;
	time2 = 160;
	oldtime2 = 200;
	time3 = 160;
	oldtime3 = 200;

}

void GameScene::StartIns(WinApp* winApp)
{
	hud->Initialize(dxCommon, winApp, 50);
	stageWorld->Initialize(input);
	player->Initialize(input);
	camera->SetTarget(player->GetPlayerPos());
	camera->SetEye({ player->GetPlayerPos().x,player->GetPlayerPos().y,player->GetPlayerPos().z - distance });
	boss->Initialize();

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
			//scene = 4;
			hud->SetRadius();
			hudFlag = 1;
			//audio->PlayWave("BGM4.wav", true);
			Gameins();
		}
		if (hudFlag == 1)
		{
			
			if (hud->GetHudFlag1(26, 14))
			{
				scene = 4;
				hud->SetRadius();
				hudFlag = 2;
				/*camera->Update();
				player->Update();
				stageWorld->Update(player->GetPlayerPos());
				boss->Update(player->GetPlayerPos());*/
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
			scene = 0;
		}
		if (hudFlag == 0 && input->TriggerKey(DIK_Q))
		{
			hud->SetRadius();
			hudFlag = 1;
		
		}
		if (hudFlag)
		{

			if (hud->GetHudFlag1(26, 14))
			{
				ShowCursor(FALSE);
				scene = 6;
				//hud->SetRadius();
				hudFlag = 2;

			}
		}

	}
	if (scene == 3)
	{
		if (input->TriggerKey(DIK_E))
		{
			scene = 0;
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
				//audio->PlayWave("BGM4.wav", true);
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
				//hud->SetRadius();
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
			stageRand1 = 0;
			stageRand2 = 0;
			time = 100;
			oldtime = 200;
			time2 = 160;
			oldtime2 = 200;
			time3 = 160;
			oldtime3 = 200;
			stageWorld->Initialize(input);
			player->Initialize(input);
			camera->SetTarget(player->GetPlayerPos());
			camera->SetEye({ player->GetPlayerPos().x,player->GetPlayerPos().y,player->GetPlayerPos().z - distance });
			boss->Initialize();

			Gameins();
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

		stageRand1 = rnd->getRandInt(0, 13);
		stageRand2 = rnd->getRandInt(0, 13);
		
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
			time2 -= 3;
			time3 -= 2;
		}

		if (time < 1)
		{
			time = oldtime;

			if (boss->GetBossEnemyLif() < 25)
			{
				oldtime = rnd->getRandInt(30, 95);
			}
			stageWorld->SetHeightLineCase(stageRand1);
			
			//stageWorld->PlayerRockOnSet();

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

#pragma region playerMove
		player->PlayerMove();
		camera->SetTarget(player->GetPlayerPos());
#pragma endregion playerMove

#pragma region テストキー

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
		if (player->GetDamegeFlag() == 0)
		{
			for (int i = 0; i < 5; i++)
			{
				if (boss->GetShotFlag(i) == 1)
				{
					bool isHit = Collision::HitSphere(player->GetPlayerPos(), 4, boss->GetShotPos(i), 3);
					if (isHit)
					{
						player->SetDamegeFlag(2);
						player->SetLife(player->GetLife() - 1);

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
						player->SetDamegeFlag(2);
						player->SetLife(player->GetLife() - 1);
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
						player->SetDamegeFlag(2);
						player->SetLife(player->GetLife() - 1);
						boss->SetPAShotFlag(i, 0);
					}
				}
			}
		}

		if (boss->GetSShotFlag() == 1)
		{
		
			if (player->GetDamegeFlag() == 0)
			{

				XMFLOAT3 pTemp = { player->GetPlayerPos().x,player->GetPlayerPos().y - 2.5f,player->GetPlayerPos().z };

				bool isHit = Collision::HitSphere(pTemp, 4, boss->GetSShotPos(), 3);
				if (isHit)
				{
					player->SetDamegeFlag(2);
					player->SetLife(player->GetLife() - 1);
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


		
		if (input->PushKey(DIK_D) || input->PushKey(DIK_A) || input->PushKey(DIK_W) || input->PushKey(DIK_S))
		{

			setrot = angleY + player->GetAddAngle();
			setrot *= 180 / XM_PI;
			player->SetRot({ 0.0f,setrot, 0.0f });
			hud->PlayerMove(setrot);
		}



		if (player->GetLife() < 1)
		{
			audio->Stop("BGM4.wav");
			audio->PlayWave("thunder.wav", 0);
			scene = 2;
			ShowCursor(TRUE);

		}
		if (boss->GetBossEnemyLif() < 1)
		{
			audio->Stop("BGM4.wav");
			audio->PlayWave("ice1.wav", 0);
			scene = 3;
			ShowCursor(TRUE);

		}
		
		hud->SetLife(player->GetLife());
		hud->SetBossLife(boss->GetBossEnemyLif());
		
	}

}

void GameScene::VariableUpdate()
{
	input->Update();
	switch (scene)
	{
	case 0:
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
		break;

	case 1:
		camera->Update();
		player->Update();
		hud->Update();
		stageWorld->Update(player->GetPlayerPos());
		boss->Update(player->GetPlayerPos());
		break;
	case 2:
		if (hudFlag == 1)
		{
			hud->HudUpdate(2);
		}
		break;

	case 3:

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
			//hud->HudUpdate(5);
			hud->HudUpdate(6);
		}
		break;

	default:
		break;
	}
	


}

void GameScene::Draw(ID3D12GraphicsCommandList* list)
{
	
	Object3d::PreDraw(list);
	player->Draw(scene);
	boss->Draw(scene);

	stageWorld->Draw(scene);

	
	Object3d::PostDraw();

	spriteCommon->PreDraw();
	debTxt->DrawAll();

	hud->Draw(scene);

	// ４．描画コマンドここまで


}

void GameScene::Delete()
{
	player->Delete();
	stageWorld->StageAllDelete();
	boss->Delete();
	hud->Delete();
	audio->Finalize();
	delete debTxt;
	delete camera;
	delete hud;

	delete boss;

	delete player;
	delete stageWorld;

	delete spriteCommon;

}
