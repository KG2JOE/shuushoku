#pragma once

#include"Object3d.h"
#include"Input.h"
#include"Model.h"

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

private:
	struct Bullet
	{
		Object3d* obj{};
		XMFLOAT3 pos{};
		bool flag{};
		XMMATRIX angle{};
		float timer = 200;
	};
public:
	
	void Initialize(Input* input_);
	void GameInitialize();


	void Update();
	void PlayerMove();
	void PlayerDamege();

	void BulletUpdate();

	void Delete();
	void Draw(int scene);
	XMFLOAT3 GetPlayerPos() { return playerPos; }
	void SetPlayerPos(XMFLOAT3 pos) { this->playerPos = pos; }

	XMFLOAT3 GetOldPlayerPos() { return oldPlayerPos; }
	void SetOldPlayerPos(XMFLOAT3 pos) { this->oldPlayerPos = pos; }

	XMFLOAT3 GetBulletPos(int i) { return bullet[i]->pos; }
	bool GetBulletFlag(int i) { return bullet[i]->flag; }
	void SetBulletFlag(int i, bool flag) { this->bullet[i]->flag = flag; }

	void SetRot(XMFLOAT3 rot) { this->playerRot = rot; }

	void SetMatRot(XMMATRIX rot) { this->matRot = rot; }
	XMMATRIX GetMatRot() { return matRot; }
	
	void SetDamegeFlag(char flag) { this->damegeFlag = flag; }
	bool GetDamegeFlag() { return damegeFlag;}

	float GetAddAngle() { return addAngle; }

	void SetBulletAngole( float angle) { this->angle = angle; }

	int GetLife() { return life;}
	void SetLife(int life_) { this->life = life_; }
private:
	Input* input{};
	Model* playerModel = new Model();
	Model* bulletModel = new Model();
	Bullet* bullet[30]{};
	Object3d* playerObj{};
	
	
	XMFLOAT3 playerPos{};
	XMFLOAT3 oldPlayerPos{};
	XMMATRIX matRot = DirectX::XMMatrixIdentity();

	//
	float jamp = 7;
	bool jampFlag = 0;
	char damegeFlag = 0;
	bool stageFlag = 0;
	bool bulletFlag = 0;
	int damegeTimer = 20;
	float damegejamp = 13;
	float addAngle = 0;
	float speed = 1.0f;
	XMFLOAT3 playerRot{};
	float angle{};

	int life = 20;
};

