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

	void Initilize(DirectXCommon* dxComon, Audio* audio,Input* input , SpriteCommon* spriteCommon);
	
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

	SpriteCommon* spriteCommon;
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	//DebugText* debugText;

	DebugCamera* camera = nullptr;
	Sprite* sprite = nullptr;
};

