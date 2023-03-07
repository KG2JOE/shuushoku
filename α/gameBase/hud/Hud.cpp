#include "Hud.h"

void Hud::Initialize(DirectXCommon* dxCommon, WinApp* winApp,int bossLi)
{
	assert(dxCommon);
	assert(winApp);
	
	spriteCommon_ = new SpriteCommon();

	spriteCommon_->initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->window_width, winApp->window_height);


	spriteCommon_->LoadTexture(1, L"Resources/sprite/coraRe.png");
	spriteCommon_->LoadTexture(2, L"Resources/sprite/playerRe.png");
	spriteCommon_->LoadTexture(3, L"Resources/sprite/reader.png");
	spriteCommon_->LoadTexture(4, L"Resources/sprite/gameover.png");
	spriteCommon_->LoadTexture(5, L"Resources/sprite/title2.png");
	spriteCommon_->LoadTexture(6, L"Resources/sprite/hud.png");
	//spriteCommon_->LoadTexture(7, L"Resources/sprite/life.png");
	spriteCommon_->LoadTexture(8, L"Resources/sprite/gameClear.png");
	spriteCommon_->LoadTexture(9, L"Resources/sprite/manual.png");
	spriteCommon_->LoadTexture(10, L"Resources/sprite/HP2.png");
	spriteCommon_->LoadTexture(11, L"Resources/sprite/HPBar2.png");
	spriteCommon_->LoadTexture(12, L"Resources/sprite/bossHP.png");
	spriteCommon_->LoadTexture(13, L"Resources/sprite/bossHPBar.png");

	spriteCommon_->LoadTexture(14, L"Resources/sprite/title2-export.png");
	spriteCommon_->LoadTexture(15, L"Resources/sprite/title2-export2.png");
	spriteCommon_->LoadTexture(16, L"Resources/sprite/HudParts64.png");
	spriteCommon_->LoadTexture(17, L"Resources/sprite/HudParts128.png");

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

	title0 = Sprite::Create(spriteCommon_, 5, { 0,0 }, false, false);
	title0->SetPosition({ 0,0,0 });
	title0->Update();

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
	HP->SetPosition({ 0,680-40,0 });
	HP->Update();
	for (int i = 0; i < 20; i++)
	{
		HPBar[i] = Sprite::Create(spriteCommon_, 11, { 0,0 }, false, false);
		HPBar[i]->SetPosition({0 + ((float)i*18),680-40,0});
		HPBar[i]->Update();
	}

	bossHP = Sprite::Create(spriteCommon_, 12, { 0,0 }, false, false);
	bossHP->SetPosition({ 0,10,0 });
	bossHP->Update();
	bossHPBar = Sprite::Create(spriteCommon_, 13, { 0,0 }, false, false);
	bossHPBar->SetPosition({ 0,10,0 });
	bossHPBar->Update();

	bossLife = bossLi;

	title1 = Sprite::Create(spriteCommon_, 14, { 0,0}, false, false);
	title1->SetPosition({ 0,0,0 });
	title1->Update();

	title2 = Sprite::Create(spriteCommon_, 15, { 0,0 }, false, false);
	title2->SetPosition({ 0,0,0 });
	title2->Update();

	for (int i = 0; i < 27; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			hudParts1[i][j] = new HudParts();
			hudParts1[i][j]->sprite = Sprite::Create(spriteCommon_, 16, { 0.5f,0.5f }, false, false);
			XMFLOAT3 pos = { 14 + (float)(i * 48),(float)j * 52,0 };
			//hudParts1[i][j]->sprite->SetPosition({ 14 + (float)(i *48),(float)j * 52,0 });
			
			if (i % 2 == 1)
			{
				float posY = 26;
				pos.y += posY;
				hudParts1[i][j]->sprite->SetPosition(pos);
				hudParts1[i][j]->sprite->Update();
			}
			if (i % 2 == 0)
			{
				hudParts1[i][j]->sprite->SetPosition(pos);
				hudParts1[i][j]->sprite->Update();
			}
			
		}
	}

	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			hudParts2[i][j] = new HudParts();
			hudParts2[i][j]->sprite = Sprite::Create(spriteCommon_, 17, { 0.5,0.5 }, false, false);
			hudParts2[i][j]->sprite->SetPosition({});
			hudParts2[i][j]->sprite->Update();
		}
	}

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
	bossHPBar->SetPosition({ -1280+(25.6f*(float)bossLife),10,0});
	bossHPBar->Update();

}

void Hud::Draw(int scene)
{
	//dxCommon->PreDraw();
	spriteCommon_->PreDraw();
	if (scene == 0)
	{

		//title0->Draw();
		title1->Draw();
		//title2->Draw();
		

		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (hudParts1[i][j]->flag == 1)
				{
					hudParts1[i][j]->sprite->Draw();
				}

			}
		}
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
	delete title0;
	delete core;
	delete player;
	delete reader;
	delete hud;
	delete over;

}

void Hud::HudUpdate(bool flag)
{
	radius+=10;
	if (flag ==0&&radius <= 1430)
	{
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 15; j++)
			{

				if (hudParts1[i][j]->flag == 0)
				{
					bool isHit = Collision::HitCircle({ 0,0,0 }, radius, hudParts1[i][j]->sprite->GetPosition(), 32, 3);
					if (isHit)hudParts1[i][j]->flag = 1;
				}

			}
		}
	}
	
	if (flag == 1 && radius <= 1430)
	{
		for (int i = 0; i < 27; i++)
		{
			for (int j = 0; j < 15; j++)
			{

				if (hudParts1[i][j]->flag == 1)
				{
					bool isHit = Collision::HitCircle({ 0,0,0 }, radius, hudParts1[i][j]->sprite->GetPosition(), 32, 3);
					if (isHit)hudParts1[i][j]->flag = 0;
				}

			}
		}
	}

}

