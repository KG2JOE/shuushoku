#include "collision.h"

bool Collision::HitCircle(XMFLOAT3 worldPos, float WorldRad, XMFLOAT3 CirciePos, float CircieRad, char setFlag)
{
	float temp = sqrtf(pow(worldPos.x - CirciePos.x, 2) + pow(worldPos.z - CirciePos.z, 2));
	if (setFlag == 0)
	{
		return temp <= WorldRad + CircieRad && temp >= WorldRad + CircieRad - 2.0f;
	}
	if (setFlag == 1)
	{
		return temp <= WorldRad + CircieRad;
	}
	if (setFlag == 2)
	{
		float temp2 = sqrtf(pow(worldPos.x - CirciePos.x, 2) + pow(worldPos.y - CirciePos.y, 2) + pow(worldPos.z - CirciePos.z, 2));
		return temp2 < WorldRad + CircieRad;

	}
}

bool Collision::HitWorld(float pPos, float sDis, bool flag)
{
	if (flag == 0)
	{
		return pPos < sDis;
	}
	if (flag == 1)
	{
		return pPos > sDis;
	}
}

bool Collision::Virtualitys(XMFLOAT3 PlayerRay, XMFLOAT3 skyPos)
{
	float temp = sqrtf(pow(skyPos.x - PlayerRay.x, 2) + /*pow(skyPos.y - PlayerRay.y, 2) +*/ pow(skyPos.z - PlayerRay.z, 2));

	return 500 - 17 > temp;
}

bool Collision::UnVirtualitys(XMFLOAT3 PlayerRay, XMFLOAT3 skyPos)
{
	float temp = sqrtf(pow(skyPos.x - PlayerRay.x, 2)/* + pow(skyPos.y - PlayerRay.y, 2)*/ + pow(skyPos.z - PlayerRay.z, 2));

	return 500 - 17 < temp;
}

bool Collision::territory(XMFLOAT3 Player, XMFLOAT3 Enemy)
{
	float temp[4] = {};
	temp[0] = Player.x - Enemy.x;
	temp[1] = Player.y - Enemy.y;
	temp[2] = Player.z - Enemy.z;

	temp[3] = sqrtf((temp[0] * temp[0]) + (temp[1] * temp[1]) + (temp[2] * temp[2]));

	//float sqrtf(temp[3]);

	return temp[3] < sqrtf(10000.0f);
}

bool Collision::ATKcollision(XMFLOAT3 Player, XMFLOAT3 Enemy)
{
	float temp[4];
	temp[0] = Player.x - Enemy.x;
	temp[1] = Player.y - Enemy.y;
	temp[2] = Player.z - Enemy.z;

	temp[3] = sqrtf((temp[0] * temp[0]) + (temp[1] * temp[1]) + (temp[2] * temp[2]));

	return temp[3] <= 10.0f;
}

bool Collision::CoaHit(XMFLOAT3 Coa, XMFLOAT3 Enemy, float rad)
{
	float temp[4] = {};
	temp[0] = Coa.x - Enemy.x;
	temp[1] = Coa.y - Enemy.y;
	temp[2] = Coa.z - Enemy.z;

	temp[3] = sqrtf((temp[0] * temp[0]) + (temp[1] * temp[1]) + (temp[2] * temp[2]));

	return rad * 2 > temp[3];
}
