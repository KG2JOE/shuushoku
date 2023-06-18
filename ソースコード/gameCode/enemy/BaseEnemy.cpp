#include "BaseEnemy.h"

void BaseEnemy::SetMove()
{
	if (hitBullet == true)
	{
		BulletHit();
	}
	spider->SetPosition(pos);
	spider->SetRotationY(angle);
	if (hitBullet == true)
	{
		deadObj->SetPosition(pos);
	}
}

void BaseEnemy::BulletHit()
{
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
