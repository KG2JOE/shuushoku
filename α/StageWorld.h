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

	struct StageParts
	{
		Object3d* OBJWorld{};
		char OBJWorldFlag{};
		XMFLOAT3 OBJWorldPos{};
		XMFLOAT3 oldOBJWorldPos{};
		float worldjamp{};
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

	void HeightLineATK(UINT point);
	void SetHeightLineCase(char pattern);
	void SetWidthLineCase(char pattern);
	XMFLOAT3 GetPosition(int i, int j) { return stageParts[i][j]->OBJWorldPos; }
	Line* SetLinePoint(char point);
private:
	
	Input* input_;
	Model* modelWorld1 = Model::LoadFromOBJ("world1");
	Model* modelWorld2 = Model::LoadFromOBJ("world2");
	
	StageParts* stageParts[50][50]{};

	const char* name[5] = {"core_in","ground","back","territory","atkHad"};
	AtkOmen* atkOmen[5]{};
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

