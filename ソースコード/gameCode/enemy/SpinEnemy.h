#pragma once
#include "BaseEnemy.h"
#include"Bullet.h"
#include<list>
class SpinEnemy : public BaseEnemy
{
private:


public:
	~SpinEnemy();//削除
	static std::unique_ptr<SpinEnemy> UniqueCreate();//作成

	void Update();// 更新
	
	void Update(XMFLOAT3 pos) {};

	void Draw();//描画

	void BulletCreate();

	void BulletUpdete();
	std::list<std::unique_ptr<Bullet>>& GetBullets() { return bullets_; }
protected:

	std::list<std::unique_ptr<Bullet>> bullets_{};
	int shotTime = 100;

	bool moveType{};

};

