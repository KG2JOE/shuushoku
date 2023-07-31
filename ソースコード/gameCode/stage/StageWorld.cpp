#include "StageWorld.h"


void StageWorld::Initialize(Input* input)
{
	//初期化
	assert(input);
	this->input_ = input;
	modelWorld1 = Model::LoadFromOBJ("world1");
	modelWorld2 = Model::LoadFromOBJ("world2");
	modelWorld3 = Model::LoadFromOBJ("world3");
	modelWorld4 = Model::LoadFromOBJ("world4");
	modelWorld5 = Model::LoadFromOBJ("world5");
	modelWorld6 = Model::LoadFromOBJ("world6");

	//柱の初期化
	for (int i = 0; i < stage_.size(); i++)
	{
		for (int j = 0; j < stage_.size(); j++)
		{
			stageParts[i][j] = StagePartsIns(i, j, TRUE);
		}
	}

	//全角度ライン攻撃の初期化
	for (int i = 0; i < lineAll_.size(); i++)
	{
		lineAll[i] = LineAllIns(i);
	}

	//通常ライン攻撃の初期化
	for (UINT i = 0; i <line_.size(); i++)
	{
		frontHeight[i] = LineIns();
		backHeight[i] = LineIns();
		rightSide[i] = LineIns();
		leftSide[i] = LineIns();

	}

	//スカイドームの初期化
	for (int i = 0; i <line_.size(); i++)
	{
		sky[i] = new SKY();
		sky[i]->model = Model::LoadFromOBJ(name[i]);
		sky[i]->OBJ = Object3d::Create();
		sky[i]->OBJ->SetModel(sky[i]->model);
		sky[i]->OBJ->SetPosition(stageParts[25][25]->OBJWorldPos);
		sky[i]->OBJ->SetScale({ 20 - (float)i * 3,20 - (float)i * 3,20 - (float)i * 3 });
		rot[i] = { 0,0,0 };
		sky[i]->OBJ->Update();
	}

	//乱数初期化
	rnd = new RndCreate();

}

void StageWorld::GameInitialize()
{
	//ゲームコンテニュー用の初期化
	for (int i = 0; i < stage_.size(); i++)
	{
		for (int j = 0; j < stage_.size(); j++)
		{
			stageParts[i][j] = StagePartsIns(i, j, FALSE);
		}

	}
	for (UINT i = 0; i <line_.size(); i++)
	{

		frontHeight[i] = LineIns();
		backHeight[i] = LineIns();
		rightSide[i] = LineIns();
		leftSide[i] = LineIns();

	}
	for (int i = 0; i < lineAll_.size(); i++)
	{
		lineAll[i] = LineAllIns(i);
	}
	ALLSetImpact({}, 0, 0);


}

void StageWorld::Update(XMFLOAT3 pos)
{
	//プレイヤーの座標取得
	SetPlayerPos(pos);

	//波打つ攻撃
	if (impactFlag == 1)
	{
		WaveATK();
	}

	//通常ライン攻撃
	for (UINT i = 0; i <line_.size(); i++)
	{
		if (frontHeight[i]->lineFlag >= 1 || backHeight[i]->lineFlag >= 1 ||
			rightSide[i]->lineFlag >= 1 ||leftSide[i]->lineFlag >= 1)
		{

			LineAtkUpdate(i);
		
			LineUpdate(i);
		}

	}

	//全角度ライン攻撃
	for (int i = 0; i < lineAll_.size(); i++)
	{

		if (lineAll[i]->line->lineFlag >= 1)
		{
			lineAll[i] = LineAllAtk(lineAll[i]);
		}

		LineAllUpdate(i);
	}

	
	//柱の座標更新
	for (int i = 0; i < stage_.size(); i++)
	{
		for (int j = 0; j < stage_.size(); j++)
		{

			//柱攻撃の更新
			StageUpdate(i,j);

			//何もしていない柱の修正
			ResetStageParts(i,j);


			stageParts[i][j]->OBJWorld->Update();
		}
	}
	
	//プレイヤーに向けての攻撃
	if (playerRockFlag >= 1)
	{
		PlayerRockOnUp();

	}


}

void StageWorld::StageUpdate()
{

	for (int i = 0; i < stage_.size(); i++)
	{
		for (int j = 0; j < stage_.size(); j++)
		{
			StageUpdateInside(i,j);
		}
	}
}

void StageWorld::StageUpdate(int i, int j)
{
	StageUpdateInside(i, j);

}

void StageWorld::StageUpdateInside(int i, int j)
{
	//ステージの攻撃(上下する動き)
	if (stageParts[i][j]->OBJWorldFlag == 1 && stageParts[i][j]->worldjamp <= 5.0f)
	{
		stageParts[i][j]->OBJWorld->SetModel(modelWorld3);
		stageParts[i][j]->Manifest = 1;


		stageParts[i][j]->OBJWorldPos.y += stageParts[i][j]->worldjamp;
		stageParts[i][j]->worldjamp -= 0.5f;
		stageParts[i][j]->OBJWorld->SetPosition(stageParts[i][j]->OBJWorldPos);
		if (stageParts[i][j]->worldjamp < -5.0f)
		{
			stageParts[i][j]->worldjamp = 30.0f;
			if (stageParts[i][j]->flont == false && stageParts[i][j]->back == false && stageParts[i][j]->right == false && stageParts[i][j]->left == false)
			{
				stageParts[i][j]->OBJWorld->SetModel(modelWorld1);
				stageParts[i][j]->Manifest = 0;
			}
			else
			{
				stageParts[i][j]->OBJWorld->SetModel(modelWorld2);
				stageParts[i][j]->Manifest = 1;


			}
			stageParts[i][j]->OBJWorldFlag = 0;
		}
	}

	//波打つ攻撃(上下する動き)
	if (impactFlag == 0 && (stageParts[i][j]->worldjamp >= 10.0f))
	{

		if (stageParts[i][j]->flont == false && stageParts[i][j]->back == false && stageParts[i][j]->right == false && stageParts[i][j]->left == false)
		{
			stageParts[i][j]->OBJWorld->SetModel(modelWorld1);
			stageParts[i][j]->Manifest = 0;
		}
		else
		{
			stageParts[i][j]->OBJWorld->SetModel(modelWorld2);
			stageParts[i][j]->Manifest = 1;
		}
		stageParts[i][j]->worldjamp = 5.0f;
		stageParts[i][j]->OBJWorldFlag = 0;
		stageParts[i][j]->OBJWorld->SetPosition(stageParts[i][j]->oldOBJWorldPos);

	}
}

void StageWorld::Draw(int scene)
{

	if (scene == 1)
	{
		for (int i = 0; i < stage_.size(); i++)
		{

			for (int j = 0; j < stage_.size(); j++)
			{
				stageParts[i][j]->OBJWorld->Draw();
			}

		}

		for (int i = 0; i <line_.size(); i++)
		{
			sky[i]->OBJ->Draw();
		}
	}

	if (scene == 6)
	{
		for (int i = 0; i < stage_.size(); i++)
		{

			for (int j = 0; j < stage_.size(); j++)
			{
				stageParts[i][j]->OBJWorld->Draw();
			}

		}

		for (int i = 0; i <line_.size(); i++)
		{
			sky[i]->OBJ->Draw();
		}
	}

	SkyUpdate();
	for (int i = 0; i <line_.size(); i++)
	{
		sky[i]->OBJ->Draw();
	}

}

void StageWorld::Delete()
{
	for (int i = 0; i <line_.size(); i++)
	{
		delete	sky[i]->OBJ;
	}

	StageAllDelete();

}

void StageWorld::WaveATK()
{
	//波打つ攻撃の当たり判定
	impactRad += 2.0f;
	if (impactRad > 260)
	{
		impactFlag = 0;
	}
	for (int i = 0; i < stage_.size(); i++)
	{
		for (int j = 0; j < stage_.size(); j++)
		{
			HitWave(i, j);
		}
	}
}

void StageWorld::SkyUpdate()
{
	//スカイドームの更新
	rot[0].y += 0.5f;
	rot[1].x += 0.5f;
	rot[2].z += 0.5f;
	for (int i = 0; i <line_.size(); i++)
	{
		sky[i]->OBJ->SetRotation(rot[i]);
		sky[i]->OBJ->Update();
	}

}

void StageWorld::ALLSetImpact(XMFLOAT3 pos, float rad, bool flag)
{
	//波打つ攻撃の代入
	SetImpactPos(pos);
	SetImpactRad(rad);
	SetImpactFlag(flag);
}

void StageWorld::ResetStageParts()
{
	
	for (int i = 0; i < stage_.size(); i++)
	{
		for (int j = 0; j < stage_.size(); j++)
		{
			if (stageParts[i][j]->OBJWorld->GetModel() == modelWorld1)
			{
				stageParts[i][j]->OBJWorld->SetPosition(stageParts[i][j]->oldOBJWorldPos);
				stageParts[i][j]->worldjamp = 5.0f;
			}
		}
	}
}

void StageWorld::ResetStageParts(int i, int j)
{
	//柱を元に戻す
	if (stageParts[i][j]->OBJWorld->GetModel() == modelWorld1)
	{
		stageParts[i][j]->OBJWorld->SetPosition(stageParts[i][j]->oldOBJWorldPos);
		stageParts[i][j]->worldjamp = 5.0f;
	}
}

void StageWorld::PlayerRockOnSet()
{
	if (playerRockFlag == 0)
	{
		for (int i = 0; i < stage_.size(); i++)
		{
			for (int j = 0; j < stage_.size(); j++)
			{
				PlayerRockOnSetInside(i, j);
			}
		}
		playerRockFlag = 1;

	}
}

void StageWorld::PlayerRockOnSetInside(int i, int j)
{
	bool isHit = Collision::HitCircle(stageParts[i][j]->OBJWorldPos, 5, playerPos, 10, 1);
	if (stageParts[i][j]->playerRockOnFlag == 0 && stageParts[i][j]->Manifest == 0 && isHit)
	{
		stageParts[i][j]->playerRockOnFlag = isHit;
		stageParts[i][j]->OBJWorld->SetModel(modelWorld5);
	}
}

void StageWorld::PlayerRockOnUp()
{
	if (playerRockFlag == 1)
	{
		playerRockTime--;
		if (playerRockTime <= 0)
		{
			playerRockFlag = 2;
			playerRockTime = 20;
			for (int i = 0; i < stage_.size(); i++)
			{
				for (int j = 0; j < stage_.size(); j++)
				{
					PlayerRockOnUpInside(i, j, FALSE);
				}
			}
		}
	}

	if (playerRockFlag == 2)
	{
		for (int i = 0; i < stage_.size(); i++)
		{
			for (int j = 0; j < stage_.size(); j++)
			{
				PlayerRockOnUpInside(i, j, TRUE);
			}
		}

	}


}

void StageWorld::PlayerRockOnUpInside(int i, int j, bool flag)
{
	if (flag == TRUE)
	{
		if (stageParts[i][j]->playerRockOnFlag == 1)
		{
			stageParts[i][j]->OBJWorldPos.y += stageParts[i][j]->worldjamp;
			stageParts[i][j]->worldjamp -= 0.5f;
			stageParts[i][j]->OBJWorld->SetPosition(stageParts[i][j]->OBJWorldPos);
			if (stageParts[i][j]->worldjamp < -5.0f)
			{
				stageParts[i][j]->OBJWorld->SetPosition(stageParts[i][j]->oldOBJWorldPos);
				stageParts[i][j]->playerRockOnFlag = 0;
				stageParts[i][j]->OBJWorld->SetModel(modelWorld1);
				playerRockFlag = 0;
			}
		}
	}
	else
	{
		if (stageParts[i][j]->playerRockOnFlag == 1)
		{
			stageParts[i][j]->OBJWorld->SetModel(modelWorld6);
			stageParts[i][j]->worldjamp = 5.0f;
		}
	}
	
}

void StageWorld::HitWave(int i, int j)
{
	//波打つ攻撃の当たり判定
	if (stageParts[i][j]->OBJWorldFlag == 0 && stageParts[i][j]->playerRockOnFlag == 0)
	{
		stageParts[i][j]->OBJWorldFlag = Collision::HitCircle(stageParts[i][j]->OBJWorldPos, 5, impactPos, impactRad, 0);
		stageParts[i][j]->worldjamp = 5.0f;
	}
}
