#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Input.h"
#include"collision.h"
#include"Player.h"
#include"RandCreate.h"
#include"StagePointer.h"
#include "StageLine.h"

//#include"StageLine.h"
#include"Stage.h"

class StageWorld :public StageLine
{

private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private:

	struct SKY
	{
		Object3d* OBJ{};
		Model* model{};
	};
public:

	//初期化
	void Initialize(Input* input);
	
	//ゲームの初期化
	void GameInitialize();

	//更新
	void Update(XMFLOAT3 pos);

	//ステージの更新
	void StageUpdate();
	void StageUpdate(int i, int j);
	//ステージの更新内容
	void StageUpdateInside(int i, int j);

	//描画処理
	void Draw(int scene);
	
	//削除
	void Delete();

	//波打つ攻撃処理
	void WaveATK();

	//背景の更新
	void SkyUpdate();

	//ステージの座標を正す
	void ResetStageParts();
	void ResetStageParts(int i,int j);

	//プレイヤーに向けての攻撃準備
	void PlayerRockOnSet();
	void HitWave(int i, int j);
	//プレイヤーに向けての攻撃準備内容
	void PlayerRockOnSetInside(int i, int j);

	//プレイヤーに向けての攻撃
	void PlayerRockOnUp();
	//プレイヤーに向けての攻撃内容
	void PlayerRockOnUpInside(int i, int j, bool flag);

	
	//波打つ攻撃の代入
	void SetImpactPos(XMFLOAT3 pos) { this->impactPos = pos; }
	void SetImpactRad(float rad) { this->impactRad = rad; }
	void SetImpactFlag(bool flag) { this->impactFlag = flag; }
	void ALLSetImpact(XMFLOAT3 pos, float rad, bool flag);


	//各柱の座標
	XMFLOAT3 GetPosition(int i, int j) { return stageParts[i][j]->OBJWorldPos; }

	//地面からランダムで攻撃が来るための予測
	void SetStageFlag(int i, int j, char flag)
	{
		this->stageParts[i][j]->OBJWorldFlag = flag;
		stageParts[i][j]->Manifest = 1;
	}
	void SetModel(int i, int j)
	{
		stageParts[i][j]->OBJWorld->SetModel(modelWorld4);
		stageParts[i][j]->Manifest = 1;
	}
	void SetModel2(int i, int j)
	{
		stageParts[i][j]->OBJWorld->SetModel(modelWorld1);
		stageParts[i][j]->Manifest = 0;
	}


	void SetPlayerPos(XMFLOAT3 pos) { this->playerPos = pos; }

	

private:

	Input* input_{};

	const char* name[3] = { "back","back2","back3" };
	XMFLOAT3 rot[3]{};
	SKY* sky[3]{};


	//ステージエフェクト
	//ウェーブ
	XMFLOAT3 impactPos{};
	float impactRad{};
	bool impactFlag = 0;


	


	RndCreate* rnd{};

	XMFLOAT3 playerPos{};
	float radius{};
	char playerRockFlag = 0;
	float playerRockTime = 30;
	float startTime = 50;

	
};

