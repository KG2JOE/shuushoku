#include "Bullet.h"

Bullet::~Bullet()
{
	delete obj;
}

std::unique_ptr<Bullet> Bullet::UniqueCreate(XMFLOAT3 pos, float angle, float moveLength)
{
	std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>();
	bullet->pos = pos;
	bullet->angle = angle;
	bullet->moveLength = moveLength;
	bullet->homingFlag = true;
	bullet->obj = Object3d::Create();
	bullet->obj->SetModel(Model::LoadFromOBJ("enemyAtkShot"));

	bullet->obj->SetPosition(bullet->pos);
	bullet->obj->SetScale({ 3.0,3.0,3.0 });
	bullet->obj->Update();
	return bullet;
}

void Bullet::DeadJudge()
{
	if (timeDeadFlag == true || hitFlag == true)
	{
		deadFlag = true;
	}
}

void Bullet::NormalBulletUpdate()
{

	moveLength += 10.f;
	if (moveLength > 250.f)
	{
		timeDeadFlag = true;
	}

	pos.x = sin((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.z = cos((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.z -= 242.f;
	DeadJudge();
	obj->SetPosition(pos);
	obj->SetScale({ 5.0,5.0,5.0 });
	obj->Update();
}

void Bullet::HomingBulletUpdate(XMFLOAT3 targetPos)
{
	if (homingFlag == true)
	{
		float distance = 0;
		distance = Collision::Distance(targetPos, pos);

		if (distance > 80)
		{
			XMVECTOR vec;
			vec.m128_f32[0] = (targetPos.x - pos.x);
			vec.m128_f32[1] = (targetPos.y - pos.y);
			vec.m128_f32[2] = (targetPos.z - pos.z);
			vec = DirectX::XMVector3Normalize(vec);
			
			homingMove.m128_f32[0] = vec.m128_f32[0] * moveLength;
			homingMove.m128_f32[1] = vec.m128_f32[1] * moveLength;
			homingMove.m128_f32[2] = vec.m128_f32[2] * moveLength;
		}
		else
		{
			homingFlag = false;
		}

		pos.x += homingMove.m128_f32[0];
		pos.y += homingMove.m128_f32[1];
		pos.z += homingMove.m128_f32[2];

		if (shotTime <= 0)
		{
			shotTime = 150;
			timeDeadFlag = true;
		}
	
	}

	if (homingFlag == false)
	{
		shotTime--;
		pos.x += homingMove.m128_f32[0];
		pos.y += homingMove.m128_f32[1];
		pos.z += homingMove.m128_f32[2];

		if (shotTime <= 0)
		{
			shotTime = 150;
			timeDeadFlag = true;
		}
		
	}
	DeadJudge();
	obj->SetPosition(pos);
	obj->Update();
}

void Bullet::Draw()
{
	if (timeDeadFlag == false && hitFlag == false)
	{
		obj->Draw();
	}

}


