#pragma once


#include<vector>

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"

#include "Object3d.h"
#include "Model.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "DebugCamera.h"
#include "Collision.h"
#include"Audio.h"
#include"DebugText.h"

#include"StageWorld.h"
#include"Player.h"
#include"BossEnemy.h"
#include"Hud.h"
#include"Enemys.h"
#include<random>

using namespace DirectX;
class GameScene
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:

	//エンジン初期化
	void EngineIns(WinApp* winApp_, DirectXCommon* dxCommon_, Input* input_);
	//ゲーム初期化
	void Gameins();
	//スタートの初期化
	void StartIns(WinApp* winApp);

	//全体の初期化
	void Initialize(WinApp* winApp_, DirectXCommon* dxCommon_, Input* input_);
	
	//全体更新
	void Update();

	//タイトルの処理
	void TitleScene();

	//ゲーム終了時処理
	void EndScene();

	//操作説明
	void explainScene();

	//ゲーム処理
	void GamePlayScene();

	//それぞれの更新
	void VariableUpdate();

	//全体描画
	void Draw();

	//全体削除
	void Delete();

	//ステージの処理
	void Stage();

	//敵の処理
	void Boss();
	void EnemysUp();

	//当たり判定の処理
	void CollisionUp();
private://エンジン
	//WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	DebugCamera* camera = nullptr;
	SpriteCommon* spriteCommon = new SpriteCommon();
	DebugText* debTxt = new DebugText;
	Audio* audio = Audio::GetInstance();
	RndCreate* rnd = new RndCreate();

	int scene = 0;

private://ゲーム

	Hud* hud = new Hud();
	StageWorld* stageWorld = new StageWorld();
	Player* player = new Player();
	
	BossEnemy* boss = new BossEnemy();
	Enemys* enemys = new Enemys();
	// カメラ関連

	float angleX = 0;
	float angleY = 0;
	float MoveAngleY;
	float scaleX = 1.0f / (float)WinApp::window_width;
	float scaleY = 1.0f / (float)WinApp::window_height;
	float distance = 50.0f;
	XMMATRIX matRot = DirectX::XMMatrixIdentity();

	float addAngle = -89.550f;


	//	ステージ関連
	int stageRand1 = 0;
	int stageRand2 = 0;
	int time = 100;
	int oldtime = 200;
	int time2 = 160;
	int oldtime2 = 200;
	int time3 = 160;
	int oldtime3 = 200;
	

	//	プレイヤー関連
	float setrot = 0;


	//	ボス関連
	bool setflag{};

	//演出関連
	int hudFlag = 0;


	int enemysCount = 0;

};

