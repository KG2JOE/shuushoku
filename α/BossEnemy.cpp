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
	bossEnemyObj->SetScale({ 10.0f,10.0f,10.0f });
	bossEnemyObj->Update();
	bossEnemyLife = 500.0f;
	moveTimer = 200;
	moveAngle = 180;

	bossEnemyPos.x = sin((moveAngle * DirectX::XM_PI) / 180) * moveLength;
	//vel.y = 0.0f;
	bossEnemyPos.z = cos((moveAngle * DirectX::XM_PI) / 180) * moveLength;
	bossEnemyPos.z -= 242;


	for (int i = 0; i < 5; i++)
	{
		shot[i] = new ATKShot();
		shot[i]->Obj = Object3d::Create();
		shot[i]->Obj->SetModel(bossEnemyAtkshot);
		shot[i]->Obj->SetScale({ 5.0,5.0,5.0 });
		shot[i]->flag = 0;
		shot[i]->Obj->Update();
	}

	sShot = new ATKShot();
	sShot->Obj = Object3d::Create();
	sShot->Obj->SetModel(bossEnemyAtkshot);
	sShot->Obj->SetScale({ 3.0,3.0,3.0 });
	sShot->flag = 0;
	sShot->Obj->Update();
	for (int i = 0; i < 32; i++)
	{
		arm[i] = new ATKArm();
		arm[i]->Obj = Object3d::Create();
		arm[i]->flag = 0;
	}


}

void BossEnemy::Update()
{
	moveTimer--;
	if (moveTimer < 0)
	{

		if (moveFlag == 2 || moveFlag == 1)
		{
			moveFlag = rand() % 3 + 1;

		}
		moveTimer = 200;
	}
	int a = rand() % 2;

	atkTime--;
	if (atkTime < 1)
	{
		if (moveFlag == 2 || moveFlag == 1)
		{
			atkFlag = 1;
			atkTime = rand() % 50 + 10;
		}
		
	}
	if (atkFlag == 1)
	{
		ATKShotSet(a);
	}
	
	bossEnemyObj->SetPosition(bossEnemyPos);
	bossEnemyObj->SetRotation(bossEnemyRotation);
	
	ATKShotUpdata();
	for (int i = 0; i < 5; i++)
	{
		if (shot[i]->flag == 1)
		{
			shot[i]->Obj->Update();
		}
	}
	sShot->Obj->Update();
	BossEnemyMove();
	BossEnemyDamege();
	bossEnemyObj->Update();
}

void BossEnemy::BossEnemyMove()
{
	if (moveFlag == 0)
	{

	}

	if (moveFlag == 1 || moveFlag == 2)
	{
		if (moveFlag == 1)
		{
			moveAngle++;
			if (moveAngle > 359)
			{
				moveAngle = 0;
			}
		}
		if (moveFlag == 2)
		{
			moveAngle--;
			if (moveAngle < 1)
			{
				moveAngle = 360;
			}
		}
		//XMFLOAT3 vel = {};
		bossEnemyPos.x = sin((moveAngle * DirectX::XM_PI) / 180) * moveLength;
		//vel.y = 0.0f;
		bossEnemyPos.z = cos((moveAngle * DirectX::XM_PI) / 180) * moveLength;
		bossEnemyPos.z -= 242;
		bossEnemyRotation.y = moveAngle;
	}

	if (moveFlag == 3)
	{
		moveLength = moveLength + 1.0f;
		if (moveLength < 250)
		{
			bossEnemyPos.x = sin((moveAngle * DirectX::XM_PI) / 180) * moveLength;
			//vel.y = 0.0f;
			bossEnemyPos.z = cos((moveAngle * DirectX::XM_PI) / 180) * moveLength;
			bossEnemyPos.z -= 242;
			bossEnemyRotation.y = moveAngle;
		}
		if (moveLength >= 250)
		{
			moveAngle += 180.0f;
			if (moveAngle >= 360)
			{
				moveAngle = moveAngle - 360.0f;
			}
			bossEnemyRotation.y = moveAngle;
			bossEnemyObj->SetRotation(bossEnemyRotation);
			moveLength = oldmoveLength;
			moveFlag = rand() % 2 + 1;
		}

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
		bossEnemyLife--;
		damegeFlag = 0;
	}

}

void BossEnemy::ATKShotUpdata()
{
	
	for (int i = 0; i < 5; i++)
	{
		if (shot[i]->flag == 1)
		{
			shot[i]->Length += 10.0;
			if (shot[i]->Length > 250)
			{
				shot[i]->flag = 0;
			}
			shot[i]->pos.x = sin((shot[i]->angle * DirectX::XM_PI) / 180) * shot[i]->Length;
			//vel.y = 0.0f;
			shot[i]->pos.z = cos((shot[i]->angle * DirectX::XM_PI) / 180) * shot[i]->Length;
			shot[i]->pos.z -= 242;
			shot[i]->Obj->SetPosition(shot[i]->pos);
			shot[i]->Obj->Update();
		}

	}

	if (sShot->flag == 1)
	{
		sShot->angle = moveAngle;
		sShot->Length += 2.0;
		if (sShot->Length > 250)
		{
			sShot->flag = 0;
		}
		sShot->pos.x = sin((sShot->angle * DirectX::XM_PI) / 180) * sShot->Length;
		//vel.y = 0.0f;
		sShot->pos.z = cos((sShot->angle * DirectX::XM_PI) / 180) * sShot->Length;
		sShot->pos.z -= 242;
		sShot->Obj->SetPosition(sShot->pos);
		sShot->Obj->Update();
	}

}

void BossEnemy::ATKShotSet(char flag)
{
	if (flag == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			if (i == 0)
			{
				if (shot[i]->flag == 0)
				{
					shot[i]->flag = 1;
					shot[i]->pos = bossEnemyPos;
					shot[i]->angle = moveAngle;
					shot[i]->Length = moveLength;
					atkFlag = 0;
					break;
				}

			}
			else
			{
				if (shot[i]->flag == 0 && shot[i - 1]->flag == 1)
				{
					shot[i]->flag = 1;
					shot[i]->pos = bossEnemyPos;
					shot[i]->angle = moveAngle;
					shot[i]->Length = moveLength;
					atkFlag = 0;
					break;
				}

			}
		}
	}
	if (flag == 1)
	{
		if (sShot->flag == 0)
		{
			sShot->flag = 1;
			sShot->pos = bossEnemyPos;
			sShot->angle = moveAngle;
			sShot->Length = moveLength;
			atkFlag = 0;
		}
		
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

	for (int i = 0; i < 5; i++)
	{
		if (shot[i]->flag == 1)
		{
			shot[i]->Obj->Draw();
		}
	}
	if (sShot->flag == 1)
	{
		sShot->Obj->Draw();
	}
}
