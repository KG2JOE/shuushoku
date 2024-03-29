#pragma once
#include "BaseEnemy.h"
#include"Bullet.h"
#include<memory>
#include<array>
#include<list>
class StayEnemy :public BaseEnemy
{
private:


public:
	~StayEnemy();//削除
	static std::unique_ptr<StayEnemy> UniqueCreate();//作成

	void Update();// 更新

	void Update(XMFLOAT3 pos);

	void Draw();//描画

	void BulletCreate();

	void BulletUpdete(XMFLOAT3 targetPos);

	void SetTsrgetPos(XMFLOAT3 pos) { this->targetPos = pos; }

	std::list<std::unique_ptr<Bullet>>& GetBullets() { return bullets_; }
protected:
	XMFLOAT3 targetPos;
	std::list<std::unique_ptr<Bullet>> bullets_{};
	int shotTime = 100;
};

