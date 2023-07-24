#pragma once
#include "BaseEnemy.h"
class BattleEnemy : public BaseEnemy
{
public:
	static std::unique_ptr<BattleEnemy> UniqueCreate(XMFLOAT3 pos_);//�쐬

	void Update() {};// �X�V

	void Update(XMFLOAT3 pos);

	void Draw();//�`��



protected:

	

	int atkTime = 200;

	bool atkFlag = 0;

	bool moveFlag = 0;
	
	bool moveType{};


};

