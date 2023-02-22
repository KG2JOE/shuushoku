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

};
