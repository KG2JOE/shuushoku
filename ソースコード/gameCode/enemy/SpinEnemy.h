#pragma once
#include "BaseEnemy.h"
class SpinEnemy : public BaseEnemy
{
private:





public:
	~SpinEnemy();//削除
	static std::unique_ptr<SpinEnemy> UniqueCreate();//作成

	void Update();// 更新

	void Draw();//描画

};

