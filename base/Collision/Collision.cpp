#include "Collision.h"

bool Collision::StageTerritory(XMFLOAT4 stage, XMFLOAT3 player)
{
	float temp = sqrtf(pow(stage.x - player.x, 2) + pow(stage.y - player.y, 2) + pow(stage.z - player.z, 2));
	 
	return stage.w > temp;
	
}

bool Collision::SphereHit(XMFLOAT3 player, XMFLOAT3 pR, XMFLOAT3 enemy, XMFLOAT3 eR)
{
	XMFLOAT3 rad = { pR.x + eR.x,pR.y + eR.y, pR.z + eR.z };
	float radTemp = sqrt(pow(rad.x, 2) + pow(rad.y, 2) + pow(rad.z, 2));
	XMFLOAT3 pos = { enemy.x - player.x,enemy.y - player.y,enemy.z - player.z };
	float posTemp = sqrt(pow(pos.x, 2) + pow(pos.y, 2) + pow(pos.z, 2));
	
	return posTemp <= radTemp;
}
