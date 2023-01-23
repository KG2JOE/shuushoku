#include "BossEnemy.h"

void BossEnemy::Initialize()
{
	rndCreate = new RndCreate();
	rndCreate->Ins();
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
	bossEnemyLife = 50.0f;
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

	for (int i = 0; i < 8; i++)
	{
		arm1[i] = new ATKArm();
		arm1[i]->Obj = Object3d::Create();
		arm1[i]->Obj->SetModel(bossEnemyAtkArm);
		arm1[i]->flag = 0;
		arm1[i]->pos.x = sin(((i * 40 + 40) * DirectX::XM_PI) / 180) * 50;
		arm1[i]->pos.z = cos(((i * 40 + 40) * DirectX::XM_PI) / 180) * 50;
		arm1[i]->pos.z -= 242;
		//arm1[i]->pos.y =7;
		arm1[i]->pos.y = -15;
		arm1[i]->Obj->SetPosition(arm1[i]->pos);
		arm1[i]->Obj->SetRotation({ 0,0,0 });
		arm1[i]->Obj->SetScale({ 10,10,10 });
		arm1[i]->Obj->Update();
	}
	for (int i = 0; i < 32; i++)
	{
		arm2[i] = new ATKArm();
		arm2[i]->Obj = Object3d::Create();
		arm2[i]->Obj->SetModel(bossEnemyAtkArm);
		arm2[i]->flag = 0;
		arm2[i]->pos.y = -15;
		arm2[i]->Obj->SetPosition(arm2[i]->pos);
		arm2[i]->Obj->SetScale({ 10,10,10 });
		arm2[i]->Obj->Update();
	}

	for (int i = 0; i < 5; i++)
	{
		pShot[i] = new ATKShot();
		pShot[i]->Obj = Object3d::Create();
		pShot[i]->Obj->SetModel(bossEnemyAtkshot);
		pShot[i]->Obj->SetScale({ 5.0,5.0,5.0 });
		pShot[i]->flag = 0;
		pShot[i]->Obj->Update();
		matRot[i] = DirectX::XMMatrixIdentity();
	}

}

void BossEnemy::GameInitialize()
{

	moveLength = oldmoveLength;
	oldmoveLength = moveLength;
	
	enemyJamp = 20;
	
	damegeFlag = 0;
	
	
	jampflag = 0;
	moveFlag = 1;
	bossEnemyPos.x = 35.0f;
	bossEnemyPos.y = 10.0f;
	bossEnemyPos.z = -242.0f;
	bossEnemyRotation.y = 180.0f;
	bossEnemyObj->SetPosition(bossEnemyPos);
	bossEnemyObj->SetRotation(bossEnemyRotation);
	
	bossEnemyObj->Update();
	bossEnemyLife = 50.0f;
	moveTimer = 200;
	moveAngle = 180;

	bossEnemyPos.x = sin((moveAngle * DirectX::XM_PI) / 180) * moveLength;
	//vel.y = 0.0f;
	bossEnemyPos.z = cos((moveAngle * DirectX::XM_PI) / 180) * moveLength;
	bossEnemyPos.z -= 242;


	for (int i = 0; i < 5; i++)
	{
		shot[i]->flag = 0;
		shot[i]->Obj->Update();
		pShot[i]->flag = 0;
		pShot[i]->Obj->Update();

	}


	sShot->flag = 0;
	sShot->Obj->Update();

	for (int i = 0; i < 8; i++)
	{
		arm1[i]->flag = 0;
		arm1[i]->pos.x = sin(((i * 40 + 40) * DirectX::XM_PI) / 180) * 50;
		arm1[i]->pos.z = cos(((i * 40 + 40) * DirectX::XM_PI) / 180) * 50;
		arm1[i]->pos.z -= 242;
		//arm1[i]->pos.y =7;
		arm1[i]->pos.y = -15;
		arm1[i]->Obj->SetPosition(arm1[i]->pos);
		arm1[i]->Obj->Update();
	}
	for (int i = 0; i < 32; i++)
	{
		arm2[i]->flag = 0;
		arm2[i]->pos.y = -15;
		arm2[i]->Obj->SetPosition(arm2[i]->pos);
		arm2[i]->Obj->Update();
	}
	atkFlag = 0;
}

void BossEnemy::Update()
{
	moveTimer--;
	if (moveTimer < 0)
	{

		if (moveFlag == 2 || moveFlag == 1)
		{
			//moveFlag = rand() % 4 + 1;
			if (bossEnemyLife >=45)
			{
				moveFlag = rndCreate->getRandInt(1, 2);

			}
			if (bossEnemyLife < 45&& bossEnemyLife >= 37)
			{
				moveFlag = rndCreate->getRandInt(1, 3);

			}
			if (bossEnemyLife < 37)
			{
				moveFlag = rndCreate->getRandInt(1, 4);

			}
		}
		moveTimer = 200;
	}
	
	//int a = rand() % 2;
	int a = rndCreate->getRandInt(0, 2);

	atkTime--;
	if (atkTime < 1)
	{
		//atkTime = rand() % 50 + 10;
		atkTime = rndCreate->getRandInt(10, 50);

		if (moveFlag == 2 || moveFlag == 1)
		{
			atkFlag = 1;
		}

	}
	if (atkFlag == 1)
	{
		ATKShotSet(a);
	}


	if (moveFlag ==3||moveFlag == 4)
	{
		if (moveFlag == 3)atkFlag = 3;
		if (atkFlag == 2|| atkFlag == 3)
		{
			//ATKArmUpdata();
		}

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
	for (int i = 0; i < 8; i++)
	{
		arm1[i]->Obj->Update();
	}
	for (int i = 0; i < 32; i++)
	{
		arm2[i]->Obj->Update();

	}
	ATKArmUpdata();
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
		moveLength += 3.0f;
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
			//moveFlag = rand() % 2 + 1;
			moveFlag = rndCreate->getRandInt(1, 2);
			atkFlag = 0;
		}

	}

	if (moveFlag == 4)
	{
		if (jampflag == 0)
		{
			jampflag = 1;
			enemyJamp = 20;
		}
		if (jampflag == 1)
		{
			if (enemyJamp > -20)
			{
				enemyJamp--;
			}
		}
		if (atkFlag == 0)
		{
			moveLength += 6.25f;

		}
		//moveLength = 0;
		
		if (moveLength < 250)
		{
			bossEnemyPos.x = sin((moveAngle * DirectX::XM_PI) / 180) * moveLength;
			//vel.y = 0.0f;
			bossEnemyPos.z = cos((moveAngle * DirectX::XM_PI) / 180) * moveLength;
			bossEnemyPos.z -= 242;
			if (enemyJamp > -20)
			{
				bossEnemyPos.y += enemyJamp;
			}
			if (enemyJamp <= -20&&jampflag == 1)
			{
				atkFlag = 2;
				jampflag = 2;
			}
			
			bossEnemyRotation.y = moveAngle;
		}
		if (jampflag == 2)
		{
			//moveLength += 6.25f;
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
					//moveFlag = rand() % 2 + 1;
				moveFlag = rndCreate->getRandInt(1, 2);
				jampflag = 0;
			}
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
				shot[i]->Length = moveLength;

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
			sShot->Length = moveLength;
		}
		sShot->pos.x = sin((sShot->angle * DirectX::XM_PI) / 180) * sShot->Length;
		//vel.y = 0.0f;
		sShot->pos.z = cos((sShot->angle * DirectX::XM_PI) / 180) * sShot->Length;
		sShot->pos.z -= 242;
		sShot->Obj->SetPosition(sShot->pos);
		sShot->Obj->Update();
	}
	for (int i = 0; i < 8; i++)
	{
		arm1[i]->Obj->Update();
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

void BossEnemy::ATKArm1()
{

	if (atkFlag == 2)
	{
		for (int i = 0; i < 8; i++)
		{
			if (arm1[i]->flag == 0)
			{
				arm1[i]->pos.x = sin(((i * 40 + 40) * DirectX::XM_PI) / 180) * 50;
				arm1[i]->pos.z = cos(((i * 40 + 40) * DirectX::XM_PI) / 180) * 50;
				arm1[i]->pos.z -= 242;
				arm1[i]->Obj->SetPosition(arm1[i]->pos);
				arm1[i]->Obj->Update();
				arm1[i]->flag = 1;
			}
			if (arm1[i]->flag == 1)
			{
				arm1[i]->pos.y += arm1[i]->upLength;
				arm1[i]->Obj->SetPosition(arm1[i]->pos);
				arm1[i]->Obj->Update();
				if (arm1[i]->upLength > 0)
				{
					arm1[i]->upLength--;

				}
				if (arm1[i]->upLength <= 0)
				{
					arm1[i]->time -= 5;
					if (arm1[i]->time < 1)
					{
						arm1[i]->upLength--;
					}
				}

				if (arm1[i]->upLength < -6)
				{
					arm1[i]->pos.y = -15;
					arm1[i]->upLength = 6;
					arm1[i]->time = 50;
					arm1[i]->Obj->SetPosition(arm1[i]->pos);
					arm1[i]->Obj->Update();
					arm1[i]->flag = 2;
				}

			}
			if (arm1[i]->flag == 2)
			{
				arm1[i]->pos.x = sin(((i * 40 + 40) * DirectX::XM_PI) / 180) * 100;
				arm1[i]->pos.z = cos(((i * 40 + 40) * DirectX::XM_PI) / 180) * 100;
				arm1[i]->pos.z -= 242;
				arm1[i]->Obj->SetPosition(arm1[i]->pos);
				arm1[i]->Obj->Update();
				arm1[i]->flag = 3;
			}
			if (arm1[i]->flag == 3)
			{
				arm1[i]->pos.y += arm1[i]->upLength;
				arm1[i]->Obj->SetPosition(arm1[i]->pos);
				arm1[i]->Obj->Update();
				if (arm1[i]->upLength > 0)
				{
					arm1[i]->upLength--;

				}
				if (arm1[i]->upLength <= 0)
				{
					arm1[i]->time -= 5;
					if (arm1[i]->time < 1)
					{
						arm1[i]->upLength--;
					}
				}

				if (arm1[i]->upLength < -6)
				{
					arm1[i]->pos.y = -15;
					arm1[i]->upLength = 6;
					arm1[i]->time = 50;
					arm1[i]->Obj->SetPosition(arm1[i]->pos);
					arm1[i]->Obj->Update();
					arm1[i]->flag = 4;
				}

			}
			if (arm1[i]->flag == 4)
			{
				arm1[i]->pos.x = sin(((i * 40 + 40) * DirectX::XM_PI) / 180) * 150;
				arm1[i]->pos.z = cos(((i * 40 + 40) * DirectX::XM_PI) / 180) * 150;
				arm1[i]->pos.z -= 242;
				arm1[i]->Obj->SetPosition(arm1[i]->pos);
				arm1[i]->Obj->Update();
				arm1[i]->flag = 5;
			}
			if (arm1[i]->flag == 5)
			{
				arm1[i]->pos.y += arm1[i]->upLength;
				arm1[i]->Obj->SetPosition(arm1[i]->pos);
				arm1[i]->Obj->Update();
				if (arm1[i]->upLength > 0)
				{
					arm1[i]->upLength--;

				}
				if (arm1[i]->upLength <= 0)
				{
					arm1[i]->time -= 5;
					if (arm1[i]->time < 1)
					{
						arm1[i]->upLength--;
					}
				}
				if (arm1[i]->upLength < -6)
				{
					arm1[i]->pos.y = -15;
					arm1[i]->upLength = 6;
					arm1[i]->time = 50;
					arm1[i]->Obj->SetPosition(arm1[i]->pos);
					arm1[i]->Obj->Update();
					arm1[i]->flag = 6;
				}

			}
			if (arm1[i]->flag == 6)
			{
				arm1[i]->pos.x = sin(((i * 40 + 40) * DirectX::XM_PI) / 180) * 185;
				arm1[i]->pos.z = cos(((i * 40 + 40) * DirectX::XM_PI) / 180) * 185;
				arm1[i]->pos.z -= 242;
				arm1[i]->Obj->SetPosition(arm1[i]->pos);
				arm1[i]->Obj->Update();
				arm1[i]->flag = 7;
			}
			if (arm1[i]->flag == 7)
			{
				arm1[i]->pos.y += arm1[i]->upLength;
				arm1[i]->Obj->SetPosition(arm1[i]->pos);
				arm1[i]->Obj->Update();
				if (arm1[i]->upLength > 0)
				{
					arm1[i]->upLength--;

				}
				if (arm1[i]->upLength <= 0)
				{
					arm1[i]->time -= 5;
					if (arm1[i]->time < 1)
					{
						arm1[i]->upLength--;
					}
				}
				if (arm1[i]->upLength < -6)
				{
					arm1[i]->pos.y = -15;
					arm1[i]->upLength = 6;
					arm1[i]->time = 50;
					arm1[i]->Obj->SetPosition(arm1[i]->pos);
					arm1[i]->Obj->Update();
					arm1[i]->flag = 0;
					atkFlag = 0;
				}

			}
		}
	}

}

void BossEnemy::ATKArm2()
{
	//if (atkFlag == 3)
	//{
	//	for (int i = 0; i < 32; i++)
	//	{
	//		if (arm2[i]->flag == 0)
	//		{

	//			/*float x = rand() % 365 - 181.795f;
	//			float z = rand() % 425 - 455;*/
	//			float x = rndCreate->getRandInt(0, 365) - 181.795f;
	//			float z = rndCreate->getRandInt(0, 425) - 455;
	//			arm2[i]->pos.x = x;
	//			arm2[i]->pos.z = z;
	//			arm2[i]->Obj->SetPosition(arm2[i]->pos);
	//			arm2[i]->flag = 1;
	//			arm2[i]->occurrenceTime = 30;
	//			break;
	//		}

	//	}


	//}

	for (int i = 0; i < 32; i++)
	{
		if (arm2[i]->flag == 1)
		{
			if (arm2[i]->occurrenceTime > 0)
			{
				arm2[i]->occurrenceTime--;
			}
			if (arm2[i]->occurrenceTime <= 0)
			{
				arm2[i]->pos.y += arm2[i]->upLength;
				arm2[i]->Obj->SetPosition(arm2[i]->pos);
				arm2[i]->Obj->Update();
				if (arm2[i]->upLength > 0)
				{
					arm2[i]->upLength--;
				}
				if (arm2[i]->upLength <= 0)
				{
					arm2[i]->time -= 5;
					if (arm2[i]->time < 1)
					{
						arm2[i]->upLength--;
					}
				}
				if (arm2[i]->upLength < -6)
				{
					arm2[i]->pos.y = -15;
					arm2[i]->upLength = 6;
					arm2[i]->time = 50;
					arm2[i]->Obj->SetPosition(arm2[i]->pos);
					arm2[i]->Obj->Update();
					arm2[i]->flag = 2;
				}

			}
			
		}
		arm2[i]->Obj->Update();
	}

}

void BossEnemy::ATKArmUpdata()
{

	ATKArm2();
	ATKArm1();
	
}

void BossEnemy::Delete()
{
	delete bossEnemyModel;
	delete bossEnemyObj;
}

void BossEnemy::Draw()
{
	bossEnemyObj->Draw();
	for (int i = 0; i < 8; i++)
	{
		if(arm1[i]->flag >= 1)
		arm1[i]->Obj->Draw();
	}
	for (int i = 0; i < 32; i++)
	{
		if (arm2[i]->flag == 1)
		{
			arm2[i]->Obj->Draw();
		}
	}
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
