#pragma once

#include"Player.h"
#include"Sprite.h"
#include"SpriteCommon.h"
class MiniMap
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:

	void Initialize(Input* input_);

	void Update();
	void PlayerMove();
	void PlayerDamege();
	void Draw();
private:

};

