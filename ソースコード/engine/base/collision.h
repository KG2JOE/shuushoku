#pragma once

#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

class Collision
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	static bool HitSphere(XMFLOAT3 playerPos,float playerRad,XMFLOAT3 enemyPos, float enemyRad);
	static bool HitCircle(XMFLOAT3 worldPos,float WorldRad,XMFLOAT3 CirciePos, float CircieRad,char setFlag);
	static bool HitLine(XMFLOAT3 linePos,XMFLOAT3 oldLinePos,float lineRad, XMFLOAT3 worldPos, float worldRad,bool flag);

	static bool HitWorld(float pPos,float sDis,bool flag);

	static bool Virtualitys(XMFLOAT3 PlayerRay, XMFLOAT3 skyPos);
	static bool UnVirtualitys(XMFLOAT3 PlayerRay, XMFLOAT3 skyPos);

	static bool territory(XMFLOAT3 Player, XMFLOAT3 Enemy);
	static bool ATKcollision(XMFLOAT3 Player, XMFLOAT3 Enemy);
	static bool CoaHit(XMFLOAT3 Coa, XMFLOAT3 Enemy,float rad);

	static float Distance(XMFLOAT3 playerPos, XMFLOAT3 enemyPos);

};