#pragma once

#include"Model.h"
#include"Object3d.h"
#include"DirectXMath.h"
#include"RandCreate.h"
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
	struct ATKShot
	{
		Object3d* Obj = nullptr;
		XMFLOAT3 pos{};
		float Length{};
		float angle{};
		char flag{};
	};

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



public:

	void Initialize();
	void GameInitialize();


	void Update();
	void BossEnemyMove();
	void BossEnemyDamege();
	XMFLOAT3 GetBossPos() { return bossEnemyPos; }
	void SetMoveFlag(char a) { this->moveFlag = a; }

	void ATKShotUpdata();
	void ATKShotSet(char flag);
	void SetAtkShot(int a) { this->atkFlag = a; }

	XMFLOAT3 GetShotPos(int i) { return shot[i]->pos; }
	char GetShotFlag(int i) { return shot[i]->flag; }
	char GetSShotFlag(){ return sShot->flag; }
	XMFLOAT3 GetSShotPos() { return sShot->pos; }

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
	void Delete();
	void Draw();
	float GetAngle() { return moveAngle; }
	char GetFlag() { return moveFlag; }
	float GetTime() { return moveTimer; }

	UINT GetAtkFlag() { return atkFlag; }

	int GetBossEnemyLif() { return bossEnemyLife; }
	void SetBossEnemyLif(int life) { this->bossEnemyLife = life; }

	char GetArm2Flag(int i) { return arm2[i]->flag; }
	
private:
	Model* bossEnemyModel = Model::LoadFromOBJ("spider");
	/*Model* bossEnemyAtk1 = Model::LoadFromOBJ("enemyAtk");
	Model* bossEnemyAtk2 = Model::LoadFromOBJ("enemyAtk2");*/
	Model* bossEnemyAtkshot = Model::LoadFromOBJ("enemyAtkShot");
	Model* bossEnemyAtkArm = Model::LoadFromOBJ("enemyArm");
	Object3d* bossEnemyObj = nullptr;

	XMFLOAT3 bossEnemyPos{};
	XMFLOAT3 bossEnemyRotation{};
	float moveLength = -250;
	//float moveLength = 0;

	float oldmoveLength = moveLength;
	float moveAngle = 0;
	float enemyJamp = 20;
	int bossEnemyLife = 100;
	char damegeFlag = 0;
	float moveTimer = 2000;
	char moveFlag =1;
	char jampflag = 0;

	UINT atkFlag = 0;
	UINT atkTime = 50;
	ATKShot* shot[5]{};
	ATKShot* sShot{};
	ATKShot* pShot[3]{};

	ATKArm* arm1[8]{};

	ATKArm* arm2[32]{};

	RndCreate* rndCreate;
};

