#pragma once

#include"Player.h"
#include"Sprite.h"
#include"SpriteCommon.h"
#include"DirectXCommon.h"
#include"WinApp.h"
class Hud
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private:
	struct Sprites
	{
		Sprite* sprite;
		XMFLOAT3 pos{};
		XMFLOAT3 rotation{};
		XMFLOAT3 angle{};

	};

public:

	void Initialize(DirectXCommon* dxCommon, WinApp* winApp);
	void Update();
	void Draw(int scene);
	void Delete();
	void PlayerMove();

private:
	SpriteCommon* spriteCommon_{};
	Sprites* player = new Sprites;
	//Sprites* enemys{};
	Sprites* bossEnemy = new Sprites;
	Sprites* core = new Sprites;
	Sprites* reader = new Sprites;
	Sprite* title{};
	Sprite* over{};
	Sprite* hud{};
	Sprite* crear{};



};

