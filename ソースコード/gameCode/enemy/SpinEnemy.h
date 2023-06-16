#pragma once
#include "BaseEnemy.h"
class SpinEnemy : public BaseEnemy
{
private:





public:
	~SpinEnemy();//íœ
	static std::unique_ptr<SpinEnemy> UniqueCreate();//ì¬

	void Update();// XV

	void Draw();//•`‰æ

};

