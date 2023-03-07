#pragma once
#include <DirectXMath.h>
#include"collision.h"
#include"Object3d.h"
#include"Model.h"
class Stage
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:

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
		char flont{};
		bool back{};
		bool right{};
		bool left{};
		bool Manifest{};
		bool playerRockOnFlag{};
	};

	Line* frontHeight[3]{};
	Line* backHeight[3]{};

	Line* rightSide[3]{};
	Line* leftSide[3]{};

	Model* modelWorld1 = Model::LoadFromOBJ("world1");
	Model* modelWorld2 = Model::LoadFromOBJ("world2");
	Model* modelWorld3 = Model::LoadFromOBJ("world3");
	Model* modelWorld4 = Model::LoadFromOBJ("world4");
	Model* modelWorld5 = Model::LoadFromOBJ("world5");
	Model* modelWorld6 = Model::LoadFromOBJ("world6");
	Model* modelplainWorld = Model::LoadFromOBJ("plainWorld2");
	StageParts* stageParts[50][50]{};
	StageParts* plainWorld[50]{};
	StageParts* StagePartsIns(int i, int j)
	{

		StageParts* sp = new StageParts();
		sp->OBJWorld = Object3d::Create();
		sp->OBJWorld->SetModel(modelWorld1);
		//sp->OBJWorld->SetScale({ 5,15,5 });
		XMFLOAT3 pos = { -183.795f + (float)(i * 7.51),-145,-450.0f };
		float a = 8.75f;
		if (i % 2 == 0)
		{
			pos.z += ((float)j * a);

		}
		else
		{
			pos.z += ((float)j * a) - 4.35f;

		}
		sp->OBJWorldPos = pos;
		sp->oldOBJWorldPos = sp->OBJWorldPos;
		sp->worldjamp = 5.0f;
		sp->OBJWorld->SetPosition(pos);
		return sp;
	}
	Line* LineIns()
	{
		Line* line = new Line();
		return line;
	}
	void StageAllDelete()
	{
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				delete stageParts[i][j]->OBJWorld;

				delete stageParts[i][j];
			}
		}

		for (int i = 0; i < 3; i++)
		{
			delete frontHeight[i];
			delete backHeight[i];

			delete rightSide[i];
			delete leftSide[i];
		}

		delete modelWorld1;
		delete modelWorld2;
		delete modelWorld3;
		delete modelWorld4;
		delete modelWorld5;
		delete modelWorld6;
	}

};
