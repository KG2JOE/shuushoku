#include"Stage.h"

Stage::StageParts* Stage::StagePartsIns(int i, int j, bool flag)
{
	StageParts* sp;
	//パーツを0から作るか否か
	if (flag)
	{

		sp = new StageParts();
		sp->OBJWorld = Object3d::Create();
	}
	else
	{
		sp = stageParts[i][j];
	}

	//初期モデルのセット
	sp->OBJWorld->SetModel(modelWorld1);
	//sp->OBJWorld->SetScale({ 5,15,5 });

	//初期座標入力
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

	//座標の代入
	sp->OBJWorldPos = pos;
	sp->oldOBJWorldPos = pos;
	sp->worldjamp = 5.0f;
	sp->OBJWorld->SetPosition(pos);

	//フラグの初期化
	sp->flont = 0;
	sp->back = 0;
	sp->right = 0;
	sp->left = 0;
	sp->Manifest = 0;
	sp->playerRockOnFlag = 0;
	return sp;
	delete sp->OBJWorld;
	delete sp;
}

void Stage::StageAllDelete()
{
	//削除
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

