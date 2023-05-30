#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Input.h"
#include"collision.h"
#include"Player.h"
#include"RandCreate.h"
#include"StagePointer.h"
//#include"StageLine.h"
#include"Stage.h"

class StageWorld :public StagePointer
{

private:
	//template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
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


	void Initialize(Input* input);
	void GameInitialize();

	void Update(XMFLOAT3 pos);
	void StageUpdate();
	void Draw(int scene);
	void Delete();

	void WaveATK();

	void SkyUpdate();

	void SetLINEAll(int i) { lineAll[i] = SetLineAllPoint(i); }

	void SetImpactPos(XMFLOAT3 pos) { this->impactPos = pos; }
	void SetImpactRad(float rad) { this->impactRad = rad; }
	void SetImpactFlag(bool flag) { this->impactFlag = flag; }
	void ALLSetImpact(XMFLOAT3 pos, float rad, bool flag);

	/*void SetHeightLineCase(char pattern);

	void SetWidthLineCase(char pattern);*/

	void ResetStageParts();

	XMFLOAT3 GetPosition(int i, int j) { return stageParts[i][j]->OBJWorldPos; }
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

	void PlayerRockOnSet();
	void PlayerRockOnUp();

	float GetLineAllAngle(int i) { return lineAll[i]->line->lineAngle; }

	
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


	UINT setHeightRand = 0;
	UINT setSideRand = 0;


	RndCreate* rnd{};

	XMFLOAT3 playerPos{};
	float radius{};
	char playerRockFlag = 0;
	float playerRockTime = 30;
	float startTime = 50;
	
};

