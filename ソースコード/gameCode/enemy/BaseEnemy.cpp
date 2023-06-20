#include "BaseEnemy.h"

void BaseEnemy::SetMove()
{
	if (hitBullet == true)
	{
		BulletHit();
	}
	pos.x = sin((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.z = cos((angle * DirectX::XM_PI) / 180) * moveLength;
	pos.z += centerPoint.z;
	spider->SetPosition(pos);
	spider->SetRotationY(angle);
	if (hitBullet == true)
	{
		deadObj->SetPosition(pos);
	}
}

void BaseEnemy::BulletHit()
{
	moveLength+=1.f;
	pos.y += (float)jump;
	if (jump > -5)
	{
		jump--;
	}
	else if (jump <= -5)
	{
		deadFlag = true;
	}

}

void BaseEnemy::Delete()
{
	delete spider;
	delete deadObj;
	delete objects->spider;
	delete objects->deadObj;
	delete model;
}

BaseEnemy::OBJECTS* BaseEnemy::CreateObj(const std::string& modelname)
{
	OBJECTS* objects = new OBJECTS();
	
	objects->spider = Object3d::Create();
	objects->spider->SetModel(Model::LoadFromOBJ(modelname));
	
	objects->deadObj = Object3d::Create();
	objects->deadObj->SetModel(Model::LoadFromOBJ("chr_sword"));


	return objects;
}

void BaseEnemy::BaseDraw()
{
	if (deadTime >= 0)
	{
		spider->Draw();
	}
	if (hitBullet == true)
	{
		deadObj->Draw();
	}
}
