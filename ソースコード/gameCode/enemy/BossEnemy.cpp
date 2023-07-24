#include "BossEnemy.h"

void BossEnemy::Initialize()
{
	bossEnemyModel = Model::LoadFromOBJ("spider");
	/*Model* bossEnemyAtk1 = Model::LoadFromOBJ("enemyAtk");
	Model* bossEnemyAtk2 = Model::LoadFromOBJ("enemyAtk2");*/
	//bossEnemyAtkshot = Model::LoadFromOBJ("enemyAtkShot");
	bossEnemyAtkArm = Model::LoadFromOBJ("enemyArm");
	rndCreate = new RndCreate();
	rndCreate->Ins();
	bossEnemyObj = Object3d::Create();
	bossEnemyObj->SetModel(bossEnemyModel);
	bossEnemyPos.x = 35.0f;
	bossEnemyPos.y = 10.0f;
	bossEnemyPos.z = -242.0f;
	bossEnemyRotation.y = 180.0f;
	
	bossEnemyObj->SetScale({ 10.0f,10.0f,10.0f });
	bossEnemyLife = 50;
	moveTimer = 200;
	moveAngle = 180.0f;

	bossEnemyPos.x = sin((moveAngle * DirectX::XM_PI) / 180) * moveLength;
	//vel.y = 0.0f;
	bossEnemyPos.z = cos((moveAngle * DirectX::XM_PI) / 180) * moveLength;
	bossEnemyPos.z -= 242;

	bossEnemyObj->SetPosition(bossEnemyPos);
	bossEnemyObj->SetRotation(bossEnemyRotation);
	bossEnemyObj->Update();

	titleEnemy = Object3d::Create();
	titleEnemy->SetModel(bossEnemyModel);
	XMFLOAT3 pos = bossEnemyPos;
	titleEnemy->SetPosition({pos.x,pos.y,pos.z-50.f });
	//titleEnemy->SetRotation(bossEnemyRotation);
	titleEnemy->SetScale({ 10.0f,10.0f,10.0f });

	titleEnemy->Update();


	for (int i = 0; i < 17; i++)
	{
		lineAtk[i] = new LineATK();
		lineAtk[i]->pos.x = sin((moveAngle * DirectX::XM_PI) / 180) * moveLength;
		lineAtk[i]->pos.z = cos((moveAngle * DirectX::XM_PI) / 180) * moveLength;
		lineAtk[i]->pos.z -= 242;
		lineAtk[i]->pos.y = {};
		lineAtk[i]->oldPos = lineAtk[i]->pos;
		if (i == 0)
		{
			lineAtk[i]->angle = 0.0f;
		}
		else
		{
			lineAtk[i]->angle = 0.0f;
		}
		lineAtk[i]->angle = (float)i * 15.f + 30.f;

	}
	

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

}

void BossEnemy::GameInitialize()
{

	moveLength = oldmoveLength;
	oldmoveLength = moveLength;

	enemyJump = 20;

	damegeFlag = 0;
	damegeTimer = 10;

	jumpflag = 0;
	moveFlag = 0;
	//moveFlag = 0;
	bossEnemyPos.x = 35.0f;
	bossEnemyPos.y = 10.0f;
	bossEnemyPos.z = -242.0f;
	bossEnemyRotation.y = 180.0f;

	bossEnemyLife = 50;
	moveTimer = 200;
	moveAngle = 180;

	bossEnemyPos.x = sin((moveAngle * DirectX::XM_PI) / 180) * moveLength;
	//vel.y = 0.0f;
	bossEnemyPos.z = cos((moveAngle * DirectX::XM_PI) / 180) * moveLength;
	bossEnemyPos.z -= 242;
	bossEnemyObj->SetPosition(bossEnemyPos);
	bossEnemyObj->SetRotation(bossEnemyRotation);

	bossEnemyObj->Update();

	
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
	XMFLOAT3 pos = bossEnemyPos;
	XMFLOAT3 rot = bossEnemyRotation;
	titleEnemy->SetPosition({ pos.x,pos.y,pos.z-360  });
	titleEnemy->SetRotation({ rot.x,rot.y,rot.z });
	titleEnemy->Update();
}

void BossEnemy::Update(XMFLOAT3 pos)
{
	SetPlayerPos(pos);

	if (moveFlag == 0)moveTimer--;

	if (bossEnemyLife <= 50)
	{
		if (moveTimer < 0)
		{


			if (bossEnemyLife < 45 && bossEnemyLife >= 37)
			{
				moveFlag = rndCreate->getRandInt(1, 3);

			}
			if (bossEnemyLife < 37)
			{
				moveFlag = rndCreate->getRandInt(1, 4);

			}
			else
			{
				moveFlag = rndCreate->getRandInt(1, 2);

			}

			if (bossEnemyLife > 40)
			{
				moveAngleFlag = 0;
			}
			if (bossEnemyLife > 30&& bossEnemyLife <= 40)
			{
				moveAngleFlag = rndCreate->getRandInt(0, 1);
			}
			if (bossEnemyLife > 25 && bossEnemyLife <= 30)
			{
				moveAngleFlag = rndCreate->getRandInt(0, 2);
			}


			if (moveAngleFlag > 0)
			{
				oldAngle = moveAngle;
			}

			moveTimer = 200;
		}
		BossEnemyMove();
		bossEnemyObj->SetPosition(bossEnemyPos);
		bossEnemyObj->SetRotation(bossEnemyRotation);
		if (moveAngleFlag == 0)
		{
			if (moveAngle == 0 || moveAngle == 360)moveFlag = 0;
			if (moveAngle == 90)moveFlag = 0;
			if (moveAngle == 180)moveFlag = 0;
			if (moveAngle == 270)moveFlag = 0;
		}
		if (moveAngleFlag == 1)
		{
			if(moveAngle - oldAngle ==180|| moveAngle - oldAngle == -180)moveFlag = 0;
		}
		if (moveAngleFlag == 2)
		{
			if (oldAngle == 0|| oldAngle == 360)
			{
			if (moveFlag == 1)
				{
					
					if (moveAngle == 270)
					{
						moveFlag = 0;
					}
				}
				if (moveFlag == 2)
				{
					
					if (moveAngle == 90)
					{
						moveFlag = 0;
					}
				}
			}

			if (oldAngle == 90)
			{
				if (moveFlag == 1)
				{
					
					if (moveAngle == 0|| moveAngle == 360)
					{
						moveFlag = 0;
					}
				}
				if (moveFlag == 2)
				{
					
					if (moveAngle == 180)
					{
						moveFlag = 0;
					}
				}
			}
			if (oldAngle == 180)
			{
				if (moveFlag == 1)
				{
				
					if (moveAngle == 90)
					{
						moveFlag = 0;
					}
				}
				if (moveFlag == 2)
				{
					
					if (moveAngle == 270)
					{
						moveFlag = 0;
					}
				}
				
			}
			if (oldAngle == 270)
			{
				if (moveFlag == 1)
				{
					if (moveAngle == 180)
					{
						moveFlag = 0;
					}
				}
				if (moveFlag == 2)
				{
					if (moveAngle == 0 || moveAngle == 360)
					{
						moveFlag = 0;
					}
				}
			}
			
		}
	


	}

	if (bossEnemyLife <= 40)
	{
	}

	if (bossEnemyLife <= 35 && bossEnemyLife > 25)
	{
	}

	if (bossEnemyLife <= 25)
	{
	}

	if (bossEnemyLife <= 15)
	{

	}

	if (bossEnemyLife < 10)
	{

		
	}
	if (moveFlag == 3)atkFlag = 3;

	for (int i = 0; i < 8; i++)
	{
		arm1[i]->Obj->Update();
	}
	for (int i = 0; i < 32; i++)
	{
		arm2[i]->Obj->Update();

	}
	ATKArmUpdata();
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
			if (moveAngle > 360)
			{
				moveAngle = 0;
			}
		}
		if (moveFlag == 2)
		{
			moveAngle--;
			if (moveAngle < 0)
			{
				moveAngle = 360;
			}
		}
		
		bossEnemyPos.x = sin((moveAngle * DirectX::XM_PI) / 180) * moveLength;
		
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
			
			moveFlag = rndCreate->getRandInt(1, 2);
			atkFlag = 0;
		}

	}

	if (moveFlag == 4)
	{
		if (jumpflag == 0)
		{
			jumpflag = 1;
			enemyJump = 20;
		}
		if (jumpflag == 1)
		{
			if (enemyJump > -20)
			{
				enemyJump--;
			}
		}
		if (atkFlag == 0)
		{
			moveLength += 6.25f;

		}
	
		if (moveLength < 250)
		{
			bossEnemyPos.x = sin((moveAngle * DirectX::XM_PI) / 180) * moveLength;
			
			bossEnemyPos.z = cos((moveAngle * DirectX::XM_PI) / 180) * moveLength;
			bossEnemyPos.z -= 242;
			if (enemyJump > -20)
			{
				bossEnemyPos.y += enemyJump;
			}
			if (enemyJump <= -20 && jumpflag == 1)
			{
				atkFlag = 2;
				jumpflag = 2;
			}

			bossEnemyRotation.y = moveAngle;
		}
		if (jumpflag == 2)
		{
			
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
				
				moveFlag = rndCreate->getRandInt(1, 2);
				jumpflag = 0;
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
		
		damegeTimer--;
		if (damegeTimer <= 0)
		{
			damegeFlag = 0;
			damegeTimer = 10;
			
			moveTimer = moveTimer/2.f;
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

	//delete bossEnemyAtkshot;
	delete bossEnemyAtkArm;
	

	for (int i = 0; i < 8; i++)
	{
		delete arm1[i]->Obj;
		delete arm1[i];
	}
	for (int i = 0; i < 32; i++)
	{
		delete arm2[i]->Obj;
		delete arm2[i];
	}
	delete bossEnemyModel;
	delete bossEnemyObj;
}

void BossEnemy::Draw(int scene,int count)
{
	if (scene == 0)
	{
		rot++;
		titleEnemy->SetRotationY(rot);
		titleEnemy->Update();
		
		titleEnemy->Draw();
	}

	if (scene == 1)
	{
		if (count >= 15)
		{
			if (damegeTimer % 2 == 0)bossEnemyObj->Draw();

		}
		for (int i = 0; i < 8; i++)
		{
			if (arm1[i]->flag >= 1)
				arm1[i]->Obj->Draw();
		}
		for (int i = 0; i < 32; i++)
		{
			if (arm2[i]->flag == 1)
			{
				arm2[i]->Obj->Draw();
			}
		}
		
	}
	if (scene == 6)
	{
	//	bossEnemyObj->Draw();
	}

}
