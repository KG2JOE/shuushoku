#include "Hud.h"

void Hud::Initialize(DirectXCommon* dxCommon, WinApp* winApp)
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


}

void Hud::Update()
{
	core->sprite->Update();
	player->sprite->Update();
	reader->sprite->Update();
	over->Update();
	title->Update();
	hud->Update();


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
		reader->sprite->Draw();
		player->sprite->Draw();
		core->sprite->Draw();
		hud->Draw();

	}

	if (scene == 2)
	{
		over->Draw();
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

