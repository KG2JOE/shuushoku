#pragma once

#include"Model.h"
#include"Object3d.h"
#include"DirectXMath.h"

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
	};



public:

	void Initialize();


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

	
	void ATKArmUpdata();
	XMFLOAT3 GetArm1(int i) { return arm1[i]->pos; }
	XMFLOAT3 GetArm2(int i) { return arm2[i]->pos; }

	void Delete();
	void Draw();
	float GetAngle() { return moveAngle; }
	char GetFlag() { return moveFlag; }
	float GetTime() { return moveTimer; }

	UINT GetAtkFlag() { return atkFlag; }
private:
	Model* bossEnemyModel = Model::LoadFromOBJ("spider");
	Model* bossEnemyAtk1 = Model::LoadFromOBJ("enemyAtk");
	Model* bossEnemyAtk2 = Model::LoadFromOBJ("enemyAtk2");
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
	float bossEnemyLife = 500.0f;
	char damegeFlag = 0;
	float moveTimer = 2000;
	char moveFlag =1;
	char jampflag = 0;


	UINT atkFlag = 0;
	UINT atkTime = 50;
	ATKShot* shot[5]{};
	ATKShot* sShot{};

	ATKArm* arm1[8]{};

	ATKArm* arm2[32]{};
};

