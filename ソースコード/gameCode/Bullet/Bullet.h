#pragma once
#include"Object3d.h"
#include"Model.h"
#include"collision.h"
#include<DirectXMath.h>
#include<array>

class Bullet
{
protected:
	// DirectX::Çè»ó™
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	~Bullet();

	static std::unique_ptr<Bullet> UniqueCreate(XMFLOAT3 pos, float angle, float moveLength);//çÏê¨

	void DeadJudge();

	void NormalBulletUpdate();
	void HomingBulletUpdate(XMFLOAT3 targetPos);
	
	void Draw();

	XMFLOAT3 GetPos() { return pos; }

	void SetHitFlag(bool flag) { this->hitFlag = flag; }
	void OnCollision() { SetHitFlag(true); }
	bool GetDeadFlag() { return deadFlag; }
protected:
	Object3d* obj;

	XMFLOAT3 pos;

	XMFLOAT3 centerPoint = { 0,0,-242.f };

	XMFLOAT3 size{};
	XMVECTOR homingMove{};

	float angle{};
	float moveLength{};

	bool timeDeadFlag = 0;
	bool hitFlag = 0;
	bool deadFlag = 0;

	bool homingFlag = 0;
	int shotTime = 150;

};

