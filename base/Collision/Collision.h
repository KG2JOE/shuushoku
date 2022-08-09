#pragma once

#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

class Collision
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//ステージ内にいるための当たり判定
	bool StageTerritory(XMFLOAT4 stage,XMFLOAT3 player);
	//球(楕円状?でも可)の当たり判定
	bool SphereHit(XMFLOAT3 player, XMFLOAT3 pR,XMFLOAT3 enemy, XMFLOAT3 eR);

};

