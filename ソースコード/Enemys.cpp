#include "Enemys.h"
#include"RandCreate.h"



void Enemys::Delete()
{
	for (std::unique_ptr<BattleEnemy>& battleEnemy : battleEnemys_)
	{
		battleEnemy->SetDeadFlag(true);
	}

	for (std::unique_ptr<StayEnemy>& stayEnemy : stayEnemys_)
	{
		stayEnemy->SetDeadFlag(true);
	}

	for (std::unique_ptr<SpinEnemy>& spinEnemy : spinEnemys_)
	{
		spinEnemy->SetDeadFlag(true);
	}
	EnemysDead();
}

void Enemys::EnemysCreate(int scene, XMFLOAT3 pos)
{
	RndCreate* randCreate = new RndCreate();
	randCreate->Ins();
	if (scene == 20)
	{
		spinEnemys_.push_back(SpinEnemy::UniqueCreate());
		//stayEnemys_.push_back(StayEnemy::UniqueCreate());
		//battleEnemys_.push_back(BattleEnemy::UniqueCreate(pos));

	}
	if (scene == 22)
	{
		if (randCreate->getRandInt(1, 10) % 2 == 0)
		{
			spinEnemys_.push_back(SpinEnemy::UniqueCreate());
		}
		else
		{
			stayEnemys_.push_back(StayEnemy::UniqueCreate());
		}
	}
	if (scene == 24)
	{
		int randC = randCreate->getRandInt(1, 9);
		if (randC == 1|| randC == 4|| randC == 7)
		{
			spinEnemys_.push_back(SpinEnemy::UniqueCreate());
		}
		else if(randC == 2 || randC == 5 || randC == 8)
		{
			stayEnemys_.push_back(StayEnemy::UniqueCreate());
		}
		else
		{
			battleEnemys_.push_back(BattleEnemy::UniqueCreate(pos));
		}
		
	}
	delete randCreate;
}

void Enemys::Update(int scene, XMFLOAT3 pos, int life)
{
	if (enemyCount < 10)
	{
		createTime--;
	}

	if (createTime <= 0)
	{
		
		EnemysCreate(scene, pos);
		if (life <= 10)
		{
			createTime = RndCreate::sGetRandInt(70, 120);

		}
		else
		{
			createTime = RndCreate::sGetRandInt(150, 200);

		}
		enemyCount++;
	}
	for (std::unique_ptr<BattleEnemy>& battleEnemy : battleEnemys_)
	{
		battleEnemy->Update(pos);
	}

	for (std::unique_ptr<StayEnemy>& stayEnemy : stayEnemys_)
	{
		stayEnemy->Update(pos);
	}

	for (std::unique_ptr<SpinEnemy>& spinEnemy : spinEnemys_)
	{
		spinEnemy->Update();
	}
	EnemysDead();
}

void Enemys::EnemysDead()
{
	for (std::unique_ptr<BattleEnemy>& battleEnemy : battleEnemys_)
	{
		if (battleEnemy->GetDeadflag() == true)
		{
			enemyCount--;
		}
		
	}

	for (std::unique_ptr<StayEnemy>& stayEnemy : stayEnemys_)
	{
		if (stayEnemy->GetDeadflag() == true)
		{
			enemyCount--;
		}
	}

	for (std::unique_ptr<SpinEnemy>& spinEnemy : spinEnemys_)
	{
		if (spinEnemy->GetDeadflag() == true)
		{
			enemyCount--;
		}
	}
	battleEnemys_.remove_if([](std::unique_ptr<BattleEnemy>& battleEnemy) {return battleEnemy->GetDeadflag() == true;  });
	stayEnemys_.remove_if([](std::unique_ptr<StayEnemy>& stayEnemy) {return stayEnemy->GetDeadflag() == true;  });
	spinEnemys_.remove_if([](std::unique_ptr<SpinEnemy>& spinEnemy) {return spinEnemy->GetDeadflag() == true;  });

}

void Enemys::Draw()
{
	for (std::unique_ptr<BattleEnemy>& battleEnemy : battleEnemys_)
	{
		battleEnemy->Draw();
	}

	for (std::unique_ptr<StayEnemy>& stayEnemy : stayEnemys_)
	{
		stayEnemy->Draw();
	}

	for (std::unique_ptr<SpinEnemy>& spinEnemy : spinEnemys_)
	{
		spinEnemy->Draw();
	}
}
