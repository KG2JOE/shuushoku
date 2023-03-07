#pragma once

#include"Player.h"
#include"Sprite.h"
#include"SpriteCommon.h"
#include"DirectXCommon.h"
#include"WinApp.h"
#include"collision.h"
class Hud
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::‚ðÈ—ª
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private:
	struct Sprites
	{
		Sprite* sprite{};
		XMFLOAT3 pos{};
		XMFLOAT3 rotation{};
		XMFLOAT3 angle{};

	};

	struct HudParts
	{
		Sprite* sprite{};
		bool flag{};
	};


public:

	void Initialize(DirectXCommon* dxCommon, WinApp* winApp, int bossLi);
	void GameInitialize(int bossLi);
	void Update();
	void Draw(int scene);
	void Delete();
	void PlayerMove(float rot) { player->sprite->SetRotation(rot); }
	void SetLife(int i) { this->life = i; }

	void SetBossLife(int i) { this->bossLife = i; }

	void HudUpdate(bool flag);

	void SetRadius() { radius = 0; };
private:
	SpriteCommon* spriteCommon_{};
	Sprites* player = new Sprites;
	//Sprites* enemys{};
	Sprites* bossEnemy = new Sprites;
	Sprites* core = new Sprites;
	Sprites* reader = new Sprites;
	
	Sprite* title0{};
	Sprite* over{};
	Sprite* hud{};
	Sprite* crear{};
	
	Sprite* manual{};

	Sprite* HP{};
	Sprite* HPBar[20]{};

	int life{};
	
	Sprite* bossHP{};
	Sprite* bossHPBar{};

	Sprite* title1{};
	Sprite* title2{};
	HudParts* hudParts1[27][15]{};
	HudParts* hudParts2[14][8]{};

	float radius = 0;

	int bossLife = 50;


};

