#pragma once
#include "BaseEnemy.h"
#include"Bullet.h"
#include<list>
class SpinEnemy : public BaseEnemy
{
private:


public:
	~SpinEnemy();//íœ
	static std::unique_ptr<SpinEnemy> UniqueCreate();//ì¬

	void Update();// XV
	
	void Update(XMFLOAT3 pos) {};

	void Draw();//•`‰æ

	void BulletCreate();

	void BulletUpdete();
	std::list<std::unique_ptr<Bullet>>& GetBullets() { return bullets_; }
protected:

	std::list<std::unique_ptr<Bullet>> bullets_{};
	int shotTime = 100;

	bool moveType{};

};

