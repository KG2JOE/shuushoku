#pragma once
#include "BaseEnemy.h"
class BattleEnemy : public BaseEnemy
{
public:
	static std::unique_ptr<BattleEnemy> UniqueCreate(XMFLOAT3 pos_);//ì¬

	void Update() {};// XV

	void Update(XMFLOAT3 pos);

	void Draw();//•`‰æ



protected:

	

	int atkTime = 200;

	bool atkFlag = 0;

	bool moveFlag = 0;
	
	bool moveType{};


};

