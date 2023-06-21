#pragma once
#include "BaseEnemy.h"
#include"Bullet.h"
#include<list>
class SpinEnemy : public BaseEnemy
{
private:


public:
	~SpinEnemy();//�폜
	static std::unique_ptr<SpinEnemy> UniqueCreate();//�쐬

	void Update();// �X�V
	
	void Update(XMFLOAT3 pos) {};

	void Draw();//�`��

	void BulletCreate();

	void BulletUpdete();
	std::list<std::unique_ptr<Bullet>>& GetBullets() { return bullets_; }
protected:

	std::list<std::unique_ptr<Bullet>> bullets_{};
	int shotTime = 100;

	bool moveType{};

};

