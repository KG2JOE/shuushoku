#pragma once

#include"Object3d.h"
#include"Input.h"
#include"Model.h"
#include"Sprite.h"
#include"SpriteCommon.h"
#include"DirectXMath.h"
class Player
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::‚ðÈ—ª
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
	XMFLOAT3 GetPlayerPos() { return playerPos; }
	void SetPlayerPos(XMFLOAT3 pos) { this->playerPos = pos; }
	void SetRot(XMFLOAT3 rot) { this->playerRot = rot; }
	void SetDamegeFlag(bool flag) { this->damegeFlag = flag; }
	bool GetDamegeFlag() { return damegeFlag;}
private:
	
	Input* input;
	Model* playerModel = Model::LoadFromOBJ("chr_sword");
	Object3d* playerObj;

	XMFLOAT3 playerPos;
	XMMATRIX matRot = DirectX::XMMatrixIdentity();;
	float jamp = 7;
	bool jampFlag = 0;
	bool damegeFlag = 0;
	float damegejamp = 13;
	XMFLOAT3 playerRot{};
};

