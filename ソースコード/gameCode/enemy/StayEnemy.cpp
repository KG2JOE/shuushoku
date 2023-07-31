#include "StayEnemy.h"
#include"RandCreate.h"

StayEnemy::~StayEnemy()
{
	Delete();
	bullets_.remove_if([](std::unique_ptr<Bullet>& bullet) {return bullet->GetDeadFlag() == false; });

}

std::unique_ptr<StayEnemy> StayEnemy::UniqueCreate()
{

	std::unique_ptr<StayEnemy> enemy = std::make_unique<StayEnemy>();

	RndCreate* randCreate = new RndCreate();
	randCreate->Ins();


	enemy->angle = randCreate->getRandFloat(0, 359);//Šp“x‚Ìƒ‰ƒ“ƒ_ƒ€‘ã“ü
	enemy->moveLength = -250.f;
	enemy->pos.y = 10.0f;
	enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.z = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.z -= 242.f;

	enemy->hitBullet = 0;
	enemy->deadFlag = 0;

	enemy->objects = BaseEnemy::CreateObj("StaySpider");
	enemy->objects->spider->SetScale({ 3.0f,3.0f,3.0f });
	enemy->objects->deadObj->SetScale({ 5.0f,5.0f,5.0f });

	//enemy->objects->spider->SetModel(enemy->model);
	enemy->objects->spider->SetPosition(enemy->pos);
	enemy->objects->spider->SetRotationY(enemy->angle);
	enemy->objects->spider->Update();


	return std::move(enemy);
}

void StayEnemy::Update()
{
	
	
}

void StayEnemy::Update(XMFLOAT3 pos)
{
	shotTime--;

	if (shotTime <= 0)
	{
		shotTime = RndCreate::sGetRandInt(100, 150);
		BulletCreate();
	}

	if (hitBullet == true)
	{
		SetMove(true);
		objects->deadObj->Update();

	}
	BulletUpdete(pos);
	objects->spider->Update();

}

void StayEnemy::Draw()
{
	BaseDraw();
	for (auto& bullet : bullets_)
	{
		bullet->Draw();
	}
}

void StayEnemy::BulletCreate()
{
	bullets_.push_back(Bullet::UniqueCreate(pos, angle, 10));

}

void StayEnemy::BulletUpdete(XMFLOAT3 targetPos)
{
	for (auto& bullet : bullets_)
	{
		bullet->HomingBulletUpdate(targetPos);
	}
	bullets_.remove_if([](std::unique_ptr<Bullet>& bullet) {return bullet->GetDeadFlag() == true; });

}


