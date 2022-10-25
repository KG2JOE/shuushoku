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
		float lineAccele = 0;
		bool lineFlag{};
		float lineAngle{};
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

	void HeightLineATK(UINT point);
	void SetHeightLineCase(char pattern);
	void SetWidthLineCase(char pattern);
	XMFLOAT3 GetPosition(int i, int j) { return OBJWorldPos[i][j]; }
	Line* SetLinePoint(char point);
private:
	const float PI = 3.1415926f;
	Input* input_;
	Model* modelWorld1 = Model::LoadFromOBJ("world1");
	Model* modelWorld2 = Model::LoadFromOBJ("world2");
	Object3d* OBJWorld[50][50]{};
	char OBJWorldFlag[50][50]{};
	XMFLOAT3 OBJWorldPos[50][50]{};
	XMFLOAT3 oldOBJWorldPos[50][50]{};
	float worldjamp[50][50]{};

	XMFLOAT3 Ppos{};
	//ステージエフェクト
	//ウェーブ
	XMFLOAT3 impactPos{};
	float impactRad{};
	bool impactFlag = 0;

	//ライン
	Line* height[3]{};
	Line* width = new Line();
	int posRand[3];
	/*coraRe.y -= sin(((playerRot.y + 90) * PI) / 180) * (1.0f / 3.90625f);
	coraRe.x -= cos(((playerRot.y + 90) * PI) / 180) * (1.0f / 3.90625f);*/

};

