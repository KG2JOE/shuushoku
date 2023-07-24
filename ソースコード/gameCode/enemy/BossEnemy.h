#pragma once

#include"Model.h"
#include"Object3d.h"
#include"DirectXMath.h"
#include"RandCreate.h"
#include"collision.h"
class BossEnemy
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::‚ðÈ—ª
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private:
	


	struct ATKArm
	{
		Object3d* Obj = nullptr;
		XMFLOAT3 pos{};
		float Length{};
		float angle{};
		char flag{};
		float upLength = 6;
		float time = 50;
		float occurrenceTime = 50;
	};

	struct LineATK
	{
		XMFLOAT3 pos{};
		XMFLOAT3 oldPos{};
		float angle{};
		float moveLength = -250;
	};

public:



	void Initialize();
	void GameInitialize();
	void Update(XMFLOAT3 pos);
	void Delete();
	void Draw(int scene,int count);
	void BossEnemyMove();
	void BossEnemyDamege();
	XMFLOAT3 GetBossPos() { return bossEnemyPos; }
	void SetMoveFlag(char a) { this->moveFlag = a; }

	float GetMoveAngle() { return moveAngle; }
	char GetMoveFlag() { return moveFlag; }
	float GetTime() { return moveTimer; }

	UINT GetAtkFlag() { return atkFlag; }

	void SetBossEnemyLif(int life) { this->bossEnemyLife = life; }
	int GetBossEnemyLif() { return bossEnemyLife; }





	

	void ATKArm1();
	void ATKArm2();
	void ATKArmUpdata();
	XMFLOAT3 GetArm1(int i) { return arm1[i]->pos; }
	XMFLOAT3 GetArm2(int i) { return arm2[i]->pos; }
	void SetArm2(int i, XMFLOAT3 a)
	{
		this->arm2[i]->pos = a;
		arm2[i]->Obj->SetPosition(arm2[i]->pos);
	};
	void SetArm2Flag(int i, char b) { arm2[i]->flag = b; }
	void SetArm2OccurrenceTime(int i) { arm2[i]->occurrenceTime = 30; }
	float GetArm2OccurrenceTime(int i) { return  arm2[i]->occurrenceTime; }
	float GetArm2posY(int i) { return  arm2[i]->pos.y; }
	char GetArm2Flag(int i) { return arm2[i]->flag; }
	void SetDamegeFlag(char flag) { this->damegeFlag = flag; }
	void SetPlayerPos(XMFLOAT3 pos) { this->playerPos = pos; }

private:
	Model* bossEnemyModel = new Model();
	//Model* bossEnemyAtkshot = new Model();
	Model* bossEnemyAtkArm = new Model();
	Object3d* bossEnemyObj = nullptr;

	XMFLOAT3 bossEnemyPos{};
	XMFLOAT3 bossEnemyRotation{};
	float moveLength = -250;
	
	float oldmoveLength = moveLength;
	float moveAngle = 0;
	float enemyJump = 20;
	int bossEnemyLife = 100;
	char damegeFlag = 0;
	int damegeTimer = 10;
	float moveTimer = 2000;
	char moveFlag = 1;
	char moveAngleFlag = 1;
	float oldAngle{};
	char jumpflag = 0;

	UINT atkFlag = 0;
	UINT atkTime = 50;
	


	LineATK* lineAtk[17];

	ATKArm* arm1[8]{};

	ATKArm* arm2[32]{};

	RndCreate* rndCreate;

	XMFLOAT3 playerPos{};


	Object3d* titleEnemy = nullptr;
	float titleEnemyAngle{};
	float rot{};

};

