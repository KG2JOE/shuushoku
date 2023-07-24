#pragma once
#include"BattleEnemy.h"
#include"StayEnemy.h"
#include"SpinEnemy.h"
#include<DirectXMath.h>
#include<memory>
#include<list>
class Enemys
{

private:

	using XMFLOAT3 = DirectX::XMFLOAT3;
public:
	
	void Delete();

	void EnemysCreate(int scene, XMFLOAT3 pos);

	void Update(int scene, XMFLOAT3 pos,int life);

	void EnemysDead();

	void Draw();

	std::list<std::unique_ptr<BattleEnemy>>& GetBattleEnemys() { return battleEnemys_; }
	std::list<std::unique_ptr<StayEnemy>>& GetStayEnemys() { return stayEnemys_; }
	std::list<std::unique_ptr<SpinEnemy>>& GetSpinEnemys() { return spinEnemys_; }

protected:

	std::list<std::unique_ptr<BattleEnemy>> battleEnemys_{};
	std::list<std::unique_ptr<StayEnemy>> stayEnemys_{};
	std::list<std::unique_ptr<SpinEnemy>> spinEnemys_{};

	int createTime = 50;

	int enemyCount = 0;

};

