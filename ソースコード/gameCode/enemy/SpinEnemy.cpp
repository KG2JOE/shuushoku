#include "SpinEnemy.h"
#include"RandCreate.h"

SpinEnemy::~SpinEnemy()
{
	delete spider;
	delete deadObj;
	delete model;
}

std::unique_ptr<SpinEnemy> SpinEnemy::UniqueCreate()
{
	std::unique_ptr<SpinEnemy> enemy = std::make_unique<SpinEnemy>();

	RndCreate* randCreate = new RndCreate();
	randCreate->Ins();


	enemy->angle = randCreate->getRandFloat(0, 359);//Šp“x‚Ìƒ‰ƒ“ƒ_ƒ€‘ã“ü
	enemy->moveLength = 250.f;
	enemy->pos.y = 10.0f;
	enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.z = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.z -= 242.f;

	enemy->hitBullet = 0;
	enemy->deadFlag = 0;

	enemy->model = new Model();
	enemy->model = Model::LoadFromOBJ("spider");
	enemy->spider = Object3d::Create();
	enemy->spider->SetModel(enemy->model);
	enemy->spider->SetPosition(enemy->pos);
	enemy->spider->SetRotationY(enemy->angle);

	enemy->deadObj = Object3d::Create();
	enemy->deadObj->SetModel(Model::LoadFromOBJ("spider"));

	if (randCreate->getRandInt(1, 10) % 2 == 0)
	{
		enemy->moveType = true;
	}
	else
	{
		enemy->moveType = false;
	}

	return std::move(enemy);
}

void SpinEnemy::Update()
{
	if (moveType == true)
	{
		angle--;
	}
	else
	{
		angle++;
	}
	
	SetMove();
	
}

void SpinEnemy::Draw()
{
	if (deadTime >= 0)
	{
		spider->Draw();
	}
	if (hitBullet == true)
	{
		deadObj->Draw();
	}
}
