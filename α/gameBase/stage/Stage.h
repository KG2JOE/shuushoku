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

	enum LINEFLAG
	{
		RIGHT = 0,
		FLONT = 1,
		LEFT = 2,
		BACK = 3,

	};

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

	Model* modelWorld1 = new Model();
	Model* modelWorld2 = new Model();
	Model* modelWorld3 = new Model();
	Model* modelWorld4 = new Model();
	Model* modelWorld5 = new Model();
	Model* modelWorld6 = new Model();
	
	StageParts* stageParts[50][50]{};

	StageParts* StagePartsIns(int i, int j, bool flag);
	Line* LineIns()
	{
		Line* line = new Line();
		return line;
	}
	void StageAllDelete();

};
