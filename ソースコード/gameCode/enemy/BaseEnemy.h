#pragma once
#include<DirectXMath.h>
#include<array>
#include"Object3d.h"
#include"Model.h"
class BaseEnemy
{
protected:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	virtual ~BaseEnemy() {};//デリート

	void SetPos(XMFLOAT3 pos) { this->pos = pos; }
	XMFLOAT3 GetPos() { return pos; }

	void SetSize(XMFLOAT3 size) { this->size = size; }
	XMFLOAT3 GetSize() { return size; }

	void SetAngle(float angle) { this->angle = angle; }
	float GetAngle() { return angle; }

	void SetMoveLength(float moveLength_) { this->moveLength = moveLength_; }//距離代入
	float GetMoveLength() { return moveLength; }//距離取得

	void SetHitBullet(bool hitBullet) { this->hitBullet = hitBullet; }
	bool GetHitBullet() { return hitBullet; }

	void SetDeadFlag(bool deadFlag) { this->deadFlag = deadFlag; }
	bool GetDeadflag() { return deadFlag; }

	void OnCollisionBullet() { hitBullet = true; }
	void OnCollisiondead() { deadFlag = true; }

	void SetMove();
	void BulletHit();

	virtual	void Update() = 0;//更新

	virtual void Draw() = 0;//描画

protected:

	XMFLOAT3 pos{};
	XMFLOAT3 size{};
	float angle{};
	float moveLength{};

	float jump = 5.f;

	bool hitBullet{};
	bool deadFlag{};

	int deadTime = 29;

	Object3d* spider{};
	Object3d* deadObj{};
	Model* model{};
};

