#include "collision.h"

bool Collision::HitSphere(XMFLOAT3 playerPos, float playerRad, XMFLOAT3 enemyPos, float enemyRad)
{
	float temp[4]{};
	temp[0] = powf(enemyPos.x - playerPos.x, 2);
	temp[1] = powf(enemyPos.y - playerPos.y, 2);
	temp[2] = powf(enemyPos.z - playerPos.z, 2);
	temp[3] = sqrtf(temp[0] + temp[1] + temp[2]);

	return temp[3] <=playerRad + enemyRad;
}

bool Collision::HitCircle(XMFLOAT3 worldPos, float WorldRad, XMFLOAT3 CirciePos, float CircieRad, char setFlag)
{
	float temp = sqrtf(powf(worldPos.x - CirciePos.x, 2) + powf(worldPos.z - CirciePos.z, 2));
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
		float temp2 = sqrtf(powf(worldPos.x - CirciePos.x, 2) + powf(worldPos.y - CirciePos.y, 2) + powf(worldPos.z - CirciePos.z, 2));
		return temp2 < WorldRad + CircieRad;

	}
	if (setFlag == 3)
	{
		temp = sqrtf(powf(worldPos.x - CirciePos.x, 2) + powf(worldPos.y - CirciePos.y, 2));
		return temp <= WorldRad + CircieRad;
	}
	if (setFlag == 4)
	{
		temp = sqrtf(powf(worldPos.x - CirciePos.x, 2) + powf(worldPos.y - CirciePos.y, 2));
		return temp <= WorldRad + CircieRad && temp >= WorldRad + CircieRad - 20.0f;

	}

}

bool Collision::HitLine(XMFLOAT3 linePos, XMFLOAT3 oldLinePos, float lineRad, XMFLOAT3 worldPos, float worldRad,bool flag)
{
//ècÉâÉCÉì
	XMFLOAT2 temp;
	float distance;
	if (flag)
	{
		if (worldPos.z <= linePos.z)
		{
			temp = { linePos.x,linePos.z };
		}
		else if (worldPos.z >= oldLinePos.z)
		{
			temp = { oldLinePos.x,oldLinePos.z };
		}
		else
		{
			temp = { linePos.x ,worldPos.z };
		}
		distance = sqrtf(powf(worldPos.x - temp.x, 2) + powf(worldPos.z - temp.y, 2));

	}

//â°ÉâÉCÉì
	else
	{
		if (worldPos.x <= linePos.x)
		{
			temp = { linePos.x,linePos.z };
		}
		else if (worldPos.x >= oldLinePos.x)
		{
			temp = { oldLinePos.x,oldLinePos.z };
		}
		else
		{
			temp = { worldPos.x ,linePos.z };
		}
		distance = sqrtf(powf(worldPos.x - temp.x, 2) + powf(worldPos.z - temp.y, 2));

	}

	return distance <= lineRad + worldRad;
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
	float temp = sqrtf(powf(skyPos.x - PlayerRay.x, 2) + /*powf(skyPos.y - PlayerRay.y, 2) +*/ powf(skyPos.z - PlayerRay.z, 2));

	return 500 - 17 > temp;
}

bool Collision::UnVirtualitys(XMFLOAT3 PlayerRay, XMFLOAT3 skyPos)
{
	float temp = sqrtf(powf(skyPos.x - PlayerRay.x, 2)/* + powf(skyPos.y - PlayerRay.y, 2)*/ + powf(skyPos.z - PlayerRay.z, 2));

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

float Collision::Distance(XMFLOAT3 playerPos, XMFLOAT3 enemyPos)
{
	float temp;
	temp = sqrtf(powf(playerPos.x-enemyPos.x, 2) + powf(playerPos.y - enemyPos.y, 2) + powf(playerPos.z - enemyPos.z, 2));
	return temp;
}
