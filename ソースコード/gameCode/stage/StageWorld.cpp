#include "StageWorld.h"


void StageWorld::Initialize(Input* input)
{
	assert(input);
	this->input_ = input;
	modelWorld1 = Model::LoadFromOBJ("world1");
	modelWorld2 = Model::LoadFromOBJ("world2");
	modelWorld3 = Model::LoadFromOBJ("world3");
	modelWorld4 = Model::LoadFromOBJ("world4");
	modelWorld5 = Model::LoadFromOBJ("world5");
	modelWorld6 = Model::LoadFromOBJ("world6");

	for (int i = 0; i < stage_.size(); i++)
	{
		for (int j = 0; j < stage_.size(); j++)
		{
			stageParts[i][j] = StagePartsIns(i, j, TRUE);
		}
	}

	for (int i = 0; i < lineAll_.size(); i++)
	{
		lineAll[i] = LineAllIns(i);
	}

	for (UINT i = 0; i <line_.size(); i++)
	{
		frontHeight[i] = LineIns();
		backHeight[i] = LineIns();
		rightSide[i] = LineIns();
		leftSide[i] = LineIns();

	}
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


	rnd = new RndCreate();

}

void StageWorld::GameInitialize()
{
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
	ALLSetImpact({}, 0, 0);


}

void StageWorld::Update(XMFLOAT3 pos)
{
	SetPlayerPos(pos);

	if (impactFlag == 1)
	{
		WaveATK();
	}
	for (UINT i = 0; i <line_.size(); i++)
	{
		if (frontHeight[i]->lineFlag >= 1 || backHeight[i]->lineFlag >= 1 ||
			rightSide[i]->lineFlag >= 1 ||leftSide[i]->lineFlag >= 1)
		{

			LineAtkUpdate(i);
		
			LineUpdate(i);
		}

	}
	for (int i = 0; i < lineAll_.size(); i++)
	{

		if (lineAll[i]->line->lineFlag >= 1)
		{
			lineAll[i] = LineAllAtk(lineAll[i]);
		}

		LineAllUpdate(i);
	}

	UINT b = rnd->getRandInt(0, 2);
	setHeightRand = b;
	UINT a = rnd->getRandInt(0, 2);
	setSideRand = a;

	StageUpdate();

	ResetStageParts();

	
	for (int i = 0; i < stage_.size(); i++)
	{
		for (int j = 0; j < stage_.size(); j++)
		{
			stageParts[i][j]->OBJWorld->Update();
		}
	}
	
	startTime--;
	if (startTime <= 0)
	{
		startTime = 30;
		

	}
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

void StageWorld::StageUpdateInside(int i, int j)
{
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
			}
		}
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
	if (stageParts[i][j]->OBJWorldFlag == 0 && stageParts[i][j]->playerRockOnFlag == 0)
	{
		stageParts[i][j]->OBJWorldFlag = Collision::HitCircle(stageParts[i][j]->OBJWorldPos, 5, impactPos, impactRad, 0);
		stageParts[i][j]->worldjamp = 5.0f;
	}
}
