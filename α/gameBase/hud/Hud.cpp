#include "Hud.h"

void Hud::Initialize(DirectXCommon* dxCommon, WinApp* winApp,int bossLi)
{
	assert(dxCommon);
	assert(winApp);
	
	spriteCommon_ = new SpriteCommon();

	spriteCommon_->initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->window_width, winApp->window_height);


	spriteCommon_->LoadTexture(1, L"Resources/coraRe.png");
	spriteCommon_->LoadTexture(2, L"Resources/playerRe.png");
	spriteCommon_->LoadTexture(3, L"Resources/reader.png");
	spriteCommon_->LoadTexture(4, L"Resources/gameover.png");
	spriteCommon_->LoadTexture(5, L"Resources/title2.png");
	spriteCommon_->LoadTexture(6, L"Resources/hud.png");
	//spriteCommon_->LoadTexture(7, L"Resources/life.png");
	spriteCommon_->LoadTexture(8, L"Resources/gameClear.png");
	spriteCommon_->LoadTexture(9, L"Resources/manual.png");
	spriteCommon_->LoadTexture(10, L"Resources/HP2.png");
	spriteCommon_->LoadTexture(11, L"Resources/HPBar2.png");
	spriteCommon_->LoadTexture(12, L"Resources/bossHP.png");
	spriteCommon_->LoadTexture(13, L"Resources/bossHPBar.png");

	core->sprite = Sprite::Create(spriteCommon_, 1, { 0,0 }, false, false);
	core->pos = { 1280 - 128 - 16,0,0 };
	core->sprite->SetPosition(core->pos);
	core->sprite->Update();

	player->sprite = Sprite::Create(spriteCommon_, 2, { 0.5,0.5 }, false, false);
	player->sprite->SetPosition({ 1280 - 128,128,0 });
	player->sprite->Update();

	reader->sprite = Sprite::Create(spriteCommon_, 3, { 0,0 }, false, false);
	reader->sprite->SetPosition({ 1280 - 256,0,0 });
	reader->sprite->Update();

	over = Sprite::Create(spriteCommon_, 4, { 0,0 }, false, false);
	over->SetPosition({ 0,0,0 });
	over->Update();

	title = Sprite::Create(spriteCommon_, 5, { 0,0 }, false, false);
	title->SetPosition({ 0,0,0 });
	title->Update();

	hud = Sprite::Create(spriteCommon_,6 , { 0,0 }, false, false);
	hud->SetPosition({ 0,0,0 });
	hud->Update();
	
	crear = Sprite::Create(spriteCommon_, 8, { 0,0 }, false, false);
	crear->SetPosition({ 0,0,0 });
	crear->Update();
	
	manual = Sprite::Create(spriteCommon_, 9, { 0,0 }, false, false);
	manual->SetPosition({ 0,0,0 });
	manual->Update();
	
	HP = Sprite::Create(spriteCommon_, 10, { 0,0 }, false, false);
	HP->SetPosition({ 0,680,0 });
	HP->Update();
	for (int i = 0; i < 20; i++)
	{
		HPBar[i] = Sprite::Create(spriteCommon_, 11, { 0,0 }, false, false);
		HPBar[i]->SetPosition({0 + ((float)i*9),680,0});
		HPBar[i]->Update();
	}

	bossHP = Sprite::Create(spriteCommon_, 12, { 0,0 }, false, false);
	bossHP->SetPosition({ 0,0,0 });
	bossHP->Update();
	bossHPBar = Sprite::Create(spriteCommon_, 13, { 0,0 }, false, false);
	bossHPBar->SetPosition({ 0,0,0 });
	bossHPBar->Update();

	bossLife = bossLi;

}

void Hud::GameInitialize(int bossLi)
{
	bossLife = bossLi;

}

void Hud::Update()
{
	/*core->sprite->Update();
	player->sprite->Update();
	reader->sprite->Update();*/
	/*over->Update();
	title->Update();
	hud->Update();
	life->Update();*/
	bossHPBar->SetPosition({ -1280+(25.6f*(float)bossLife),0,0});
	bossHPBar->Update();

}

void Hud::Draw(int scene)
{
	//dxCommon->PreDraw();
	spriteCommon_->PreDraw();
	if (scene == 0)
	{

		title->Draw();
		

	}

	if (scene == 1)
	{
	//	reader->sprite->Draw();
	//	player->sprite->Draw();
	//	core->sprite->Draw();
		//hud->Draw();
		//
		bossHPBar->Draw();
		bossHP->Draw();
		for (int i = 0; i < life; i++)
		{
			HPBar[i]->Draw();
		}
		HP->Draw();
	}

	if (scene == 2)
	{
		over->Draw();
	}
	if (scene == 3)
	{
		crear->Draw();
	}
	if (scene == 4)
	{
		manual->Draw();
	}

}

void Hud::Delete()
{
	delete spriteCommon_;
	delete title;
	delete core;
	delete player;
	delete reader;
	delete hud;
	delete over;

}

