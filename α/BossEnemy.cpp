#include "BossEnemy.h"

void BossEnemy::Initialize()
{
	bossEnemyObj = Object3d::Create();
	bossEnemyObj->SetModel(bossEnemyModel);
	bossEnemyPos.y = 10.0f;
	bossEnemyRotation.y = 180.0f;
	bossEnemyObj->SetPosition(bossEnemyPos);
	bossEnemyObj->SetRotation(bossEnemyRotation);
	bossEnemyObj->SetScale({10.0f,10.0f,10.0f});
	bossEnemyObj->Update();
	bossEnemyLife = 500.0f;
	moveTimer = 200;
}

void BossEnemy::Update()
{
	BossEnemyMove();
	BossEnemyDamege();
	bossEnemyObj->Update();
}

void BossEnemy::BossEnemyMove()
{
	if (moveFlag == 0)
	{

	}
}

void BossEnemy::BossEnemyDamege()
{
	if (damegeFlag == 0)
	{
		bossEnemyLife = bossEnemyLife;
	}
	if (damegeFlag == 1)
	{
		bossEnemyLife --;
	}

}

void BossEnemy::Delete()
{
	delete bossEnemyModel;
	delete bossEnemyObj;
}

void BossEnemy::Draw()
{
	bossEnemyObj->Draw();
}
