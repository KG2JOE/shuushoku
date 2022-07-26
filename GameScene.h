#pragma once
#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include"Audio.h"
#include "Object3d.h"
#include "Model.h"
#include"SpriteCommon.h"
#include"Sprite.h"
#include"FbxLoader.h"
#include"ObjectFBX3d.h"
#include"DebugCamera.h"
#include"PostEffect.h"
#include<vector>
class GameScene
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	GameScene();

	~GameScene();

	void Initilize(DirectXCommon* directXCommon, Audio* audio,Input* input , SpriteCommon* spriteCommon);
	
	void ObjectSprite();

	void ObjectFbx();

	void ObjectObj();

	
	void LoadTextureSprite();
	void LoadTextureFbx();
	void LoadTextureObj();

	void Update();
	void ClassUpdate();

	void Draw();

private: // ÉÅÉìÉoïœêî
	ID3D12Device* device;
	SpriteCommon* spriteCommon_;
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	//DebugText* debugText;

	DebugCamera* camera_ = nullptr;
	Sprite* sprite_ = nullptr;

	Object3d* obj = nullptr;
	Model* modelChr = nullptr;

};

