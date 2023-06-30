#include "BaseEnemy.h"

void BaseEnemy::SetMove(bool flag)
{
	if (hitBullet == true)
	{
		BulletHit();
	}
	
	if (flag == true)
	{
		pos.x = sin((angle * DirectX::XM_PI) / 180) * moveLength;
		pos.z = cos((angle * DirectX::XM_PI) / 180) * moveLength;
		pos.z += centerPoint.z;
	}
	objects->spider->SetPosition(pos);
	objects->spider->SetRotationY(angle);
	if (hitBullet == true)
	{
		objects->deadObj->SetPosition(pos);
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
	/*delete spider;
	delete deadObj;*/
	delete objects->spider;
	delete objects->deadObj;
	//delete model;
}

BaseEnemy::OBJECTS* BaseEnemy::CreateObj(const std::string& modelname)
{
	OBJECTS* objects = new OBJECTS();
	
	Model* model = Model::LoadFromOBJ(modelname);
	objects->spider = Object3d::Create();
	objects->spider->SetModel(model);
	
	model = Model::LoadFromOBJ("iceHorn");
	objects->deadObj = Object3d::Create();
	objects->deadObj->SetModel(model);


	return objects;
}

void BaseEnemy::BaseDraw()
{
	if (deadTime >= 0)
	{
		objects->spider->Draw();
	}
	if (hitBullet == true)
	{
		objects->deadObj->Draw();
	}
}
