#pragma once
#include <DirectXMath.h>
#include"collision.h"
#include"Object3d.h"
#include"Model.h"
#include"RandCreate.h"
#include<array>
class Stage
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
protected:

	enum LINEFLAG
	{
		RIGHT = 0,
		FLONT = 1,
		LEFT = 2,
		BACK = 3,
		ALL = 4,
	};

	struct Line
	{
		XMFLOAT3 linePos{};
		XMFLOAT3 oldPos{};
		float lineAccele = 0;
		char lineFlag{};
		float lineAngle{};
	};

	struct LineAll
	{
		Line* line{};
		float length{};
		float oldLength{};
	};

	struct StageParts
	{
		Object3d* OBJWorld{};
		char OBJWorldFlag{};
		XMFLOAT3 OBJWorldPos{};
		XMFLOAT3 oldOBJWorldPos{};
		float worldjamp{};
		char flont{};
		bool back{};
		bool right{};
		bool left{};
		bool all{};
		bool Manifest{};
		bool playerRockOnFlag{};
	};

	Line* frontHeight[3]{};
	Line* backHeight[3]{};

	Line* rightSide[3]{};
	Line* leftSide[3]{};

	LineAll* lineAll[36]{};

	RndCreate* setRand =new RndCreate();

	Model* modelWorld1 = new Model();
	Model* modelWorld2 = new Model();
	Model* modelWorld3 = new Model();
	Model* modelWorld4 = new Model();
	Model* modelWorld5 = new Model();
	Model* modelWorld6 = new Model();

	StageParts* stageParts[50][50]{};

	StageParts* StagePartsIns(int i, int j, bool flag);
	
	//’Êíƒ‰ƒCƒ“‚Ì‰Šú‰»
	Line* LineIns()
	{
		Line* line = new Line();
		return line;
	}

	//‘SŠp“xƒ‰ƒCƒ“UŒ‚‚Ì‰Šú‰»
	LineAll* LineAllIns(int i)
	{

		LineAll* lineAll = new LineAll();
		lineAll->line = LineIns();
		lineAll->line->lineAngle = (float)i * 10.f;

		lineAll->length = -250.f;
		lineAll->oldLength = -250.f;

		lineAll->line->linePos.x = sin((((float)i * 10.f) * DirectX::XM_PI) / 180) * lineAll->length;
		lineAll->line->linePos.z = cos((((float)i * 10.f) * DirectX::XM_PI) / 180) * lineAll->length;
		lineAll->line->linePos.z -= 242;
		
		return lineAll;
	}


	void SetEnemyAngle(float angle) { this->enemyAngle = angle; }


public:
	void StageAllDelete();


protected:

	float enemyAngle{};
	std::array<int, 50> stage_;
	std::array<int, 3> line_;
	std::array<int, 36> lineAll_;
	
	float right_ = -183.795f;
	float flont_ = -455.f;
	float left_ = 185.205f;
	float back_ = 20.f;

};
