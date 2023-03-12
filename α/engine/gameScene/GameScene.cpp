#include "GameScene.h"

void GameScene::EngineIns(WinApp* winApp_, DirectXCommon* dxCommon_, Input* input_)
{
	winApp = winApp_;
	dxCommon = dxCommon_;
	input = input_;

	Object3d::StaticInitialize(dxCommon->GetDev());

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);
	Object3d::SetCamera(camera);

	// カメラ注視点をセット
	camera->SetTarget({ 0, 11, -400 });
	camera->SetDistance(3.0f);
	camera->SetEye({ 0, 10, 0 });
	spriteCommon->initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->window_width, winApp->window_height);
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
	matRot = DirectX::XMMatrixIdentity();
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

void GameScene::StartIns()
{
	hud->Initialize(dxCommon, winApp, 50);
	stageWorld->Initialize(input);
	player->Initialize(input);
	camera->SetTarget(player->GetPlayerPos());
	camera->SetEye({ player->GetPlayerPos().x,player->GetPlayerPos().y,player->GetPlayerPos().z - distance });
	boss->Initialize();

}



void GameScene::Initialize(WinApp* winApp_, DirectXCommon* dxCommon_, Input* input_, bool flag)
{
	if (flag ==0)
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

		StartIns();
		Gameins();
	}
	else
	{
		Gameins();
	}
	
}

void GameScene::VariableUpdate(int scene)
{
	switch (scene)
	{
	case 0:

		break;

	case 1:
		camera->Update();
		player->Update();
		hud->Update();
		stageWorld->Update(player->GetPlayerPos());
		boss->Update(player->GetPlayerPos());
		break;
	case 2:

		break;

	case 3:

		break;

	case 4:

		break;

	case 5:

		break;

	case 6:

		if (hudFlag == 0)
		{
			//hud->HudUpdate(5);
			hud->HudUpdate(6);
		}
		break;

	default:
		break;
	}
	input->Update();


}

void GameScene::Draw()
{
	dxCommon->PreDraw();

	Object3d::PreDraw(dxCommon->GetCmdList());
	player->Draw(scene);
	boss->Draw(scene);

	stageWorld->Draw(scene);

	//if (scene == 0)
	//{
	//	//	objPlayer->Draw();
	//}
	//if (scene == 1)
	//{
	//	//	Object3d::PreDraw(dxCommon->GetCmdList());
	//	/*player->Draw();
	//	boss->Draw();
	//	stageWorld->Draw();*/
	//	//objPlayer->Draw();
	//}
	//if (scene == 2){}
	//if (scene == 3){}
	//if (scene == 6)
	//{
	//	/*player->Draw();
	//	boss->Draw();
	//	stageWorld->Draw();*/
	//}
	Object3d::PostDraw();

	spriteCommon->PreDraw();
	debTxt->DrawAll();

	hud->Draw(scene);

	// ４．描画コマンドここまで
	dxCommon->PostDraw();

}

void GameScene::Delete()
{
	player->Delete();
	stageWorld->StageAllDelete();
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

}
