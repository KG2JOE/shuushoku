#include "BossEnemy.h"

void BossEnemy::Initialize()
{
	bossEnemyObj = Object3d::Create();
	bossEnemyObj->SetModel(bossEnemyModel);
	bossEnemyPos.x = 35.0f;
	bossEnemyPos.y = 10.0f;
	bossEnemyPos.z = -242.0f;
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
	bossEnemyObj->SetPosition(bossEnemyPos);
	bossEnemyObj->SetRotation(bossEnemyRotation);

	BossEnemyMove();
	BossEnemyDamege();
	bossEnemyObj->Update();
}

void BossEnemy::BossEnemyMove()
{
	if (moveFlag == 0)
	{

	}

	if (moveFlag == 1)
	{
		moveAngle++;
		if (moveAngle > 359)
		{
			moveAngle = 0;
		}
		//XMFLOAT3 vel = {};
		bossEnemyPos.x = sin((moveAngle * DirectX::XM_PI) / 180) * moveLength;
		//vel.y = 0.0f;
		bossEnemyPos.z = cos((moveAngle * DirectX::XM_PI) / 180) * moveLength;
		bossEnemyPos.z -= 242;
		bossEnemyRotation.y = moveAngle;
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
