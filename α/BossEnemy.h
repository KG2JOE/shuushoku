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

	};



public:

	void Initialize();


	void Update();
	void BossEnemyMove();
	void BossEnemyDamege();

	void ATKShotUpdata();
	void ATKShotSet(char flag);
	void SetAtkShot(int a) { this->atkFlag = a; }
	void ATKSShotUpdata();
	void ATKArmUpdata();

	void Delete();
	void Draw();
	float GetAngle() { return moveAngle; }
	char GetFlag() { return moveFlag; }
	float GetTime() { return moveTimer; }
private:
	Model* bossEnemyModel = Model::LoadFromOBJ("spider");
	Model* bossEnemyAtk1 = Model::LoadFromOBJ("enemyAtk");
	Model* bossEnemyAtk2 = Model::LoadFromOBJ("enemyAtk2");
	Model* bossEnemyAtkshot = Model::LoadFromOBJ("enemyAtkShot");
	Object3d* bossEnemyObj = nullptr;

	XMFLOAT3 bossEnemyPos{};
	XMFLOAT3 bossEnemyRotation{};
	float moveLength = -250;
	float oldmoveLength = moveLength;
	float moveAngle = 0;
	float bossEnemyLife = 500.0f;
	char damegeFlag = 0;
	float moveTimer = 2000;
	char moveFlag =1;
	UINT atkFlag = 0;
	ATKShot* shot[5]{};
	ATKShot* sShot{};


	ATKArm* arm[32]{};
};

