#include "BattleEnemy.h"
#include"RandCreate.h"

std::unique_ptr<BattleEnemy> BattleEnemy::UniqueCreate(XMFLOAT3 pos)
{
	std::unique_ptr<BattleEnemy> enemy = std::make_unique<BattleEnemy>();

	RndCreate* randCreate = new RndCreate();
	randCreate->Ins();


	enemy->angle = randCreate->getRandFloat(0, 359);//Šp“x‚Ìƒ‰ƒ“ƒ_ƒ€‘ã“ü
	enemy->moveLength = -250.f;
	enemy->pos.y = 10.0f;
	enemy->pos.x = sin((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.z = cos((enemy->angle * DirectX::XM_PI) / 180) * enemy->moveLength;
	enemy->pos.z += pos.z;

	enemy->hitBullet = 0;
	enemy->deadFlag = 0;

	enemy->objects = BaseEnemy::CreateObj("spider");
	enemy->objects->spider->SetScale({ 3.0f,3.0f,3.0f });
	enemy->objects->deadObj->SetScale({ 3.0f,3.0f,3.0f });
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

void BattleEnemy::Update(XMFLOAT3 pos_)
{

	if (moveType == true)
	{
		angle--;
	}
	else
	{
		angle++;
	}
	if (moveLength <= -70)moveLength++;

	pos.x = sin((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.z = cos((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.x += pos_.x;
	pos.z += pos_.z;
	SetMove(false);
	if (hitBullet == true)
	{
		//SetMove(false);
		objects->deadObj->Update();
	}
	objects->spider->Update();

}

void BattleEnemy::Draw()
{
	BaseDraw();
}
