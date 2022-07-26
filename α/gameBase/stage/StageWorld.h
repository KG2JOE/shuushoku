#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Input.h"
#include"collision.h"
#include"Player.h"
class StageWorld
{

private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private:
	struct Line
	{
		XMFLOAT3 linePos{};
		XMFLOAT3 oldPos{};
		float lineAccele = 0;
		char lineFlag{};
		float lineAngle{};
	};

	struct StageParts
	{
		Object3d* OBJWorld{};
		char OBJWorldFlag{};
		XMFLOAT3 OBJWorldPos{};
		XMFLOAT3 oldOBJWorldPos{};
		float worldjamp{};
		bool flont{};
		bool back{};
		bool right{};
		bool left{};
	};

	struct AtkOmen
	{
		Object3d* OBJ{};
		Model* model{};
	};
public:


	void Initialize(Input* input);

	void Update();
	void StageUpdate();
	void Draw();
	void Delete();

	void WaveATK();
	void SetImpactPos(XMFLOAT3 pos) { this->impactPos = pos; }
	void SetImpactRad(float rad) { this->impactRad = rad; }
	void SetImpactFlag(bool flag) { this->impactFlag = flag; }
	void ALLSetImpact(XMFLOAT3 pos, float rad, bool flag);

	void BackHeightLineATK(UINT point);
	void FrontHeightLineATK(UINT point);
	void SetHeightLineCase(char pattern);

	void RightSideLineATK(UINT point);
	void leftSideLineATK(UINT point);
	void SetWidthLineCase(char pattern);


	XMFLOAT3 GetPosition(int i, int j) { return stageParts[i][j]->OBJWorldPos; }
	void SetStageFlag(int i, int j, char flag) { this->stageParts[i][j]->OBJWorldFlag = flag; }

	Line* SetHeightLinePoint(char point);
	Line* SetSideLinePoint(char point);
	
private:
	
	Input* input_{};
	Model* modelWorld1 = Model::LoadFromOBJ("world1");
	Model* modelWorld2 = Model::LoadFromOBJ("world2");
	Model* modelWorld3 = Model::LoadFromOBJ("world3");
	Model* modelAtkHud = Model::LoadFromOBJ("atkHad");
	
	StageParts* stageParts[50][50]{};

	const char* name[4] = {"core_in","ground","back","territory"};
	AtkOmen* atkOmen[4]{};
	//ステージエフェクト
	//ウェーブ
	XMFLOAT3 impactPos{};
	float impactRad{};
	bool impactFlag = 0;

	//ライン
	Line* frontHeight[3]{};
	Line* backHeight[3]{};

	Line* rightSide[3]{};
	Line* leftSide[3]{};

	//Line* width = new Line();
	int frontHeightPosRand[3]{};
	int RightSidePosRand[3]{};
	int backHeightPosRand[3]{};
	int leftSidePosRand[3]{};
	UINT count = 0;
	UINT setHeightRand = 0;
	UINT setSideRand = 0;

	/*coraRe.y -= sin(((playerRot.y + 90) * PI) / 180) * (1.0f / 3.90625f);
	coraRe.x -= cos(((playerRot.y + 90) * PI) / 180) * (1.0f / 3.90625f);*/

};

