#pragma once
#include "BaseEnemy.h"
class SpinEnemy : public BaseEnemy
{
private:





public:
	~SpinEnemy();//�폜
	static std::unique_ptr<SpinEnemy> UniqueCreate();//�쐬

	void Update();// �X�V

	void Draw();//�`��

};

