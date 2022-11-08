#pragma once

#include"Model.h"
#include"Object3d.h"
#include"DirectXMath.h"

class BossEnemy
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:

	void Initialize();


	void Update();
	void BossEnemyMove();
	void BossEnemyDamege();
	void Delete();
	void Draw();
	float GetAngle() { return moveAngle; }
	char GetFlag() { return moveFlag; }
	float GetTime() { return moveTimer; }
private:
	Model* bossEnemyModel = Model::LoadFromOBJ("spider");
	Model* bossEnemyAtk1 = Model::LoadFromOBJ("enemyAtk");
	Model* bossEnemyAtk2 = Model::LoadFromOBJ("enemyAtk2");
	Object3d* bossEnemyObj;

	XMFLOAT3 bossEnemyPos{};
	XMFLOAT3 bossEnemyRotation{};
	float moveLength = -250;
	float oldmoveLength = moveLength;
	float moveAngle;
	float bossEnemyLife = 500.0f;
	char damegeFlag = 0;
	float moveTimer = 2000;
	char moveFlag =0 ;
};

