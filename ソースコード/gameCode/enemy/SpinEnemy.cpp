#include "SpinEnemy.h"
#include"RandCreate.h"

SpinEnemy::~SpinEnemy()
{
	
	delete objects->spider;
	objects->spider = nullptr;
	delete objects->deadObj;
	objects->deadObj = nullptr;
	delete objects;
	bullets_.remove_if([](std::unique_ptr<Bullet>& bullet) {return bullet->GetDeadFlag() == false; });
	//Delete();
}

std::unique_ptr<SpinEnemy> SpinEnemy::UniqueCreate()
{
	std::unique_ptr<SpinEnemy> enemy = std::make_unique<SpinEnemy>();

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
	
	//enemy->objects = new OBJECTS();
	//Model* model = Model::LoadFromOBJ("spinSpider");
	//enemy->objects->spider = Object3d::Create();
	//enemy->objects->spider->SetModel(model);
	//enemy->objects->spider->SetScale({ 3.0f,3.0f,3.0f });
	//model = Model::LoadFromOBJ("chr_sword");
	//enemy->objects->deadObj = Object3d::Create();
	//enemy->objects->deadObj->SetModel(model);
	//enemy->objects->deadObj->SetScale({ 3.0f,3.0f,3.0f });
	////enemy->objects = BaseEnemy::CreateObj("spider");
	////enemy->objects->spider->SetModel(enemy->model);
	//enemy->objects->spider->SetPosition(enemy->pos);
	//enemy->objects->spider->SetRotationY(enemy->angle);
	//enemy->objects->spider->Update();

	enemy->objects = BaseEnemy::CreateObj("spinSpider");
	enemy->objects->spider->SetScale({ 3.0f,3.0f,3.0f });
	enemy->objects->deadObj->SetScale({ 5.0f,5.0f,5.0f });

	//enemy->objects->spider->SetModel(enemy->model);
	enemy->objects->spider->SetPosition(enemy->pos);
	enemy->objects->spider->SetRotationY(enemy->angle);
	enemy->objects->spider->Update();
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
		angle-=0.5f;
	}
	else
	{
		angle+= 0.5f;
	}
	shotTime--;

	if (shotTime <= 0)
	{
		shotTime = RndCreate::sGetRandInt(100, 150);
		BulletCreate();
	}
	BulletUpdete();

	SetMove(true);
	//spider->Update();
	objects->spider->Update();
	if (hitBullet == true)
	{
		objects->deadObj->Update();
		//deadObj->Update();
	}

}

void SpinEnemy::Draw()
{

	BaseDraw();
	for (auto& bullet : bullets_)
	{
		bullet->Draw();
	}
}

void SpinEnemy::BulletCreate()
{
	bullets_.push_back(Bullet::UniqueCreate(pos, angle, moveLength));

}

void SpinEnemy::BulletUpdete()
{
	for (auto& bullet : bullets_)
	{
		bullet->NormalBulletUpdate();
	}
	bullets_.remove_if([](std::unique_ptr<Bullet>& bullet) {return bullet->GetDeadFlag() == true; });

}
