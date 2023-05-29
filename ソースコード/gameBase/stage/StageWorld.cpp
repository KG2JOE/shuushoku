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

	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			stageParts[i][j] = StagePartsIns(i, j, 1);
		}
	}

	for (int i = 0; i < 36; i++)
	{
		lineAll[i] = LineAllIns(i);
	}

	for (UINT i = 0; i < 3; i++)
	{
		frontHeight[i] = LineIns();
		backHeight[i] = LineIns();
		rightSide[i] = LineIns();
		leftSide[i] = LineIns();

	}
	for (int i = 0; i < 3; i++)
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
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			stageParts[i][j] = StagePartsIns(i, j, 0);
		}

	}
	for (UINT i = 0; i < 3; i++)
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
	for (UINT i = 0; i < 3; i++)
	{
		if (frontHeight[i]->lineFlag >= 1 || backHeight[i]->lineFlag >= 1 ||
			rightSide[i]->lineFlag >= 1 ||leftSide[i]->lineFlag >= 1)
		{

			if (frontHeight[i]->lineFlag >= 1)
			{

				//FrontHeightLineATK(i);
				frontHeight[i] = LineAtk(frontHeight[i], FLONT);
				
			}
			if (backHeight[i]->lineFlag >= 1)
			{
				//BackHeightLineATK(i);
				backHeight[i] = LineAtk(backHeight[i], BACK);
				
			}

			if (rightSide[i]->lineFlag >= 1)
			{
				//RightSideLineATK(i);
				rightSide[i] = LineAtk(rightSide[i], RIGHT);
				
			}

			if (leftSide[i]->lineFlag >= 1)
			{
				//eftSideLineATK(i);
				leftSide[i] = LineAtk(leftSide[i], LEFT);
			
			}
		
			LineUpdate(i);
		}

	}


	//UINT b = rand() % 3;
	UINT b = rnd->getRandInt(0, 2);
	setHeightRand = b;
	UINT a = rnd->getRandInt(0, 2);
	setSideRand = a;

	StageUpdate();

	ResetStageParts();

	rot[0].y += 0.5;
	rot[1].x += 0.5;
	rot[2].z += 0.5;
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			//if (stageParts[i][j]->Manifest == 1 || stageParts[i][j]->playerRockOnFlag == 1)stageParts[i][j]->OBJWorld->Update();
			stageParts[i][j]->OBJWorld->Update();

		}
		//plainWorld[i]->OBJWorld->Update();
	}
	for (int i = 0; i < 3; i++)
	{

		sky[i]->OBJ->SetRotation(rot[i]);
		sky[i]->OBJ->Update();
	}
	startTime--;
	if (startTime <= 0)
	{
		startTime = 30/*(float)RndCreate::sGetRandInt(100, 150)*/;
		//PlayerRockOnSet();

	}
	if (playerRockFlag >= 1)
	{
		PlayerRockOnUp();

	}


}

void StageWorld::StageUpdate()
{

	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
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
					//stageParts[i][j]->OBJWorld->SetModel(modelWorld1);

					stageParts[i][j]->OBJWorldFlag = 0;

				}
			}
			if (impactFlag == 0 && (stageParts[i][j]->worldjamp >= 10.0f))
			{

				//stageParts[i][j]->OBJWorld->SetModel(modelWorld1);
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
	}
}

void StageWorld::Draw(int scene)
{

	if (scene == 1)
	{
		for (int i = 0; i < 50; i++)
		{

			for (int j = 0; j < 50; j++)
			{
				stageParts[i][j]->OBJWorld->Draw();
			}

		}

		for (int i = 0; i < 3; i++)
		{
			sky[i]->OBJ->Draw();
		}
	}

	if (scene == 6)
	{
		for (int i = 0; i < 50; i++)
		{

			for (int j = 0; j < 50; j++)
			{
				stageParts[i][j]->OBJWorld->Draw();
			}

		}

		for (int i = 0; i < 3; i++)
		{
			sky[i]->OBJ->Draw();
		}
	}


	for (int i = 0; i < 3; i++)
	{
		sky[i]->OBJ->Draw();
	}

}

void StageWorld::Delete()
{
	for (int i = 0; i < 3; i++)
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
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (stageParts[i][j]->OBJWorldFlag == 0 && stageParts[i][j]->playerRockOnFlag == 0)
			{
				stageParts[i][j]->OBJWorldFlag = Collision::HitCircle(stageParts[i][j]->OBJWorldPos, 5, impactPos, impactRad, 0);
				stageParts[i][j]->worldjamp = 5.0f;

			}
		}
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
	for (int i = 0; i < 50; i++)
	{

		for (int j = 0; j < 50; j++)
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
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				bool isHit = Collision::HitCircle(stageParts[i][j]->OBJWorldPos, 5, playerPos, 10, 1);
				if (stageParts[i][j]->playerRockOnFlag == 0 && stageParts[i][j]->Manifest == 0 &&
					/*(stageParts[i][j]->OBJWorldPos.x> playerPos.x-10&& stageParts[i][j]->OBJWorldPos.x < playerPos.x + 10 &&
						stageParts[i][j]->OBJWorldPos.z> playerPos.z - 10 && stageParts[i][j]->OBJWorldPos.z < playerPos.z + 10)*/isHit)
				{
					stageParts[i][j]->playerRockOnFlag = /*Collision::HitCircle(stageParts[i][j]->OBJWorldPos, 5, playerPos, 10, 1)*/isHit;
					stageParts[i][j]->OBJWorld->SetModel(modelWorld5);
				}
			}
		}
		playerRockFlag = 1;

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
			for (int i = 0; i < 50; i++)
			{
				for (int j = 0; j < 50; j++)
				{
					if (stageParts[i][j]->playerRockOnFlag == 1)
					{
						stageParts[i][j]->OBJWorld->SetModel(modelWorld6);
						stageParts[i][j]->worldjamp = 5.0f;
					}
				}
			}
		}
	}
	if (playerRockFlag == 2)
	{
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				if (stageParts[i][j]->playerRockOnFlag == 1)
				{
					stageParts[i][j]->OBJWorldPos.y += stageParts[i][j]->worldjamp;
					stageParts[i][j]->worldjamp -= 0.5f;
					stageParts[i][j]->OBJWorld->SetPosition(stageParts[i][j]->OBJWorldPos);
					if (stageParts[i][j]->worldjamp < -5.0f)
					{
						/*stageParts[i][j]->worldjamp = 30.0f;
						if (stageParts[i][j]->flont == 2 && stageParts[i][j]->back == false && stageParts[i][j]->right == false && stageParts[i][j]->left == false)
						{
							stageParts[i][j]->OBJWorld->SetModel(modelWorld1);
							stageParts[i][j]->Manifest = 0;
						}
						else
						{
							stageParts[i][j]->OBJWorld->SetModel(modelWorld2);
							stageParts[i][j]->Manifest = 1;
						}*/
						stageParts[i][j]->OBJWorld->SetPosition(stageParts[i][j]->oldOBJWorldPos);
						stageParts[i][j]->playerRockOnFlag = 0;
						stageParts[i][j]->OBJWorld->SetModel(modelWorld1);
						playerRockFlag = 0;
					}
				}
			}
		}

	}


}
//
//void StageWorld::SetHeightLineCase(char pattern)
//{
//	switch (pattern)
//	{
//		//‘O
//	case 0:
//
//		if (frontHeight[setHeightRand]->lineFlag == 0) { frontHeight[setHeightRand] = SetLinePoint(setHeightRand, 0)/*SetHeightLinePoint(setHeightRand)*/; }
//		break;
//	case 1:
//		if (setHeightRand == 0)
//		{
//			if (frontHeight[0]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0, 0); frontHeight[1] = SetLinePoint(1, 0); }
//			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//			break;
//		}
//		else if (setHeightRand == 1)
//		{
//			if (frontHeight[1]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1, 0); frontHeight[2] = SetLinePoint(2, 0); }
//			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
//			break;
//		}
//		else
//		{
//			if (frontHeight[0]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0, 0); frontHeight[2] = SetLinePoint(2, 0); }
//			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
//			break;
//		}
//		//if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//		break;
//	case 2:
//
//		if (setHeightRand == 0)
//		{
//			if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(3, 0); }
//			break;
//		}
//		else if (setHeightRand == 1)
//		{
//			if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(4, 0); }
//			break;
//		}
//		else
//		{
//			if (frontHeight[0]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[0] = SetLinePoint(3, 0);  frontHeight[2] = SetLinePoint(4, 0); }
//			break;
//		}
//		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }
//		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/
//
//
//		break;
//	case 3:
//
//		if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0, 0); }
//		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1, 0); }
//		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2, 0); }
//
//		break;
//
//	case 4:
//
//		if (frontHeight[setHeightRand]->lineFlag == 0) { frontHeight[setHeightRand] = SetLinePoint(5, 0); }
//		break;
//		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }
//
//		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }*/
//		break;
//	case 5:
//		if (setHeightRand == 0)
//		{
//			if (frontHeight[0]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[0] = SetLinePoint(5, 0);  frontHeight[1] = SetLinePoint(5, 0); }
//			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//			break;
//		}
//		else if (setHeightRand == 1)
//		{
//			if (frontHeight[1]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[1] = SetLinePoint(5, 0); frontHeight[2] = SetLinePoint(5, 0); }
//			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
//			break;
//		}
//		else
//		{
//			if (frontHeight[0]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[0] = SetLinePoint(5, 0);  frontHeight[2] = SetLinePoint(5, 0); }
//			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
//			break;
//		}
//		break;
//	case 6:
//		/*if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//
//		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/
//		if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(5, 0); }
//		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(5, 0); }
//		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(5, 0); }
//		break;
//
//		//Œã‚ë
//	case 7:
//
//		if (backHeight[setHeightRand]->lineFlag == 0) { backHeight[setHeightRand] = SetLinePoint(setHeightRand + 6, 0); }
//		break;
//	case 8:
//		if (setHeightRand == 0)
//		{
//			if (backHeight[0]->lineFlag == 0 && backHeight[1]->lineFlag == 0) { backHeight[0] = SetLinePoint(6, 0);  backHeight[1] = SetLinePoint(7, 0); }
//			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//			break;
//		}
//		else if (setHeightRand == 1)
//		{
//			if (backHeight[1]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[1] = SetLinePoint(7, 0); backHeight[2] = SetLinePoint(8, 0); }
//			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
//			break;
//		}
//		else
//		{
//			if (backHeight[0]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[0] = SetLinePoint(6, 0);  backHeight[2] = SetLinePoint(8, 0); }
//			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
//			break;
//		}
//		//if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//		break;
//	case 9:
//
//		if (setHeightRand == 0)
//		{
//			if (backHeight[0]->lineFlag == 0) { backHeight[0] = SetLinePoint(9, 0); }
//			break;
//		}
//		else if (setHeightRand == 1)
//		{
//			if (backHeight[2]->lineFlag == 0) { backHeight[2] = SetLinePoint(10, 0); }
//			break;
//		}
//		else
//		{
//			if (backHeight[0]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[0] = SetLinePoint(9, 0);  backHeight[2] = SetLinePoint(10, 0); }
//			break;
//		}
//		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }
//		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/
//
//
//		break;
//
//	case 10:
//		if (backHeight[0]->lineFlag == 0) { backHeight[0] = SetLinePoint(6, 0); }
//		if (backHeight[1]->lineFlag == 0) { backHeight[1] = SetLinePoint(7, 0); }
//		if (backHeight[2]->lineFlag == 0) { backHeight[2] = SetLinePoint(8, 0); }
//		break;
//	case 11:
//
//		if (backHeight[setHeightRand]->lineFlag == 0) { backHeight[setHeightRand] = SetLinePoint(11, 0); }
//		break;
//		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }
//
//		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }*/
//		break;
//	case 12:
//		if (setHeightRand == 0)
//		{
//			if (backHeight[0]->lineFlag == 0 && backHeight[1]->lineFlag == 0) { backHeight[0] = SetLinePoint(11, 0);  backHeight[1] = SetLinePoint(11, 0); }
//			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//			break;
//		}
//		else if (setHeightRand == 1)
//		{
//			if (backHeight[1]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[1] = SetLinePoint(11, 0); backHeight[2] = SetLinePoint(11, 0); }
//			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
//			break;
//		}
//		else
//		{
//			if (backHeight[0]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[0] = SetLinePoint(11, 0);  backHeight[2] = SetLinePoint(11, 0); }
//			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
//			break;
//		}
//		break;
//	case 13:
//		/*if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//
//		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/
//		if (backHeight[0]->lineFlag == 0) { backHeight[0] = SetLinePoint(11, 0); }
//		if (backHeight[1]->lineFlag == 0) { backHeight[1] = SetLinePoint(11, 0); }
//		if (backHeight[2]->lineFlag == 0) { backHeight[2] = SetLinePoint(11, 0); }
//		break;
//
//	default:
//		break;
//	}
//
//}
//
//void StageWorld::SetWidthLineCase(char pattern)
//{
//
//	switch (pattern)
//	{
//		//‰E
//	case 0:
//
//		if (rightSide[setSideRand]->lineFlag == 0) { rightSide[setSideRand] = SetLinePoint(setSideRand, 1)/*SetHeightLinePoint(setHeightRand)*/; }
//		break;
//	case 1:
//		if (setSideRand == 0)
//		{
//			if (rightSide[0]->lineFlag == 0 && rightSide[1]->lineFlag == 0) { rightSide[0] = SetLinePoint(0, 1); rightSide[1] = SetLinePoint(1, 1); }
//			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//			break;
//		}
//		else if (setSideRand == 1)
//		{
//			if (rightSide[1]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[1] = SetLinePoint(1, 1); rightSide[2] = SetLinePoint(2, 1); }
//			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
//			break;
//		}
//		else
//		{
//			if (rightSide[0]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[0] = SetLinePoint(0, 1); rightSide[2] = SetLinePoint(2, 1); }
//			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
//			break;
//		}
//		//if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//		break;
//	case 2:
//
//		if (setSideRand == 0)
//		{
//			if (rightSide[0]->lineFlag == 0) { rightSide[0] = SetLinePoint(3, 1); }
//			break;
//		}
//		else if (setSideRand == 1)
//		{
//			if (rightSide[2]->lineFlag == 0) { rightSide[2] = SetLinePoint(4, 1); }
//			break;
//		}
//		else
//		{
//			if (rightSide[0]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[0] = SetLinePoint(3, 1);  rightSide[2] = SetLinePoint(4, 1); }
//			break;
//		}
//		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }
//		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/
//
//
//		break;
//	case 3:
//
//		if (rightSide[0]->lineFlag == 0) { rightSide[0] = SetLinePoint(0, 1); }
//		if (rightSide[1]->lineFlag == 0) { rightSide[1] = SetLinePoint(1, 1); }
//		if (rightSide[2]->lineFlag == 0) { rightSide[2] = SetLinePoint(2, 1); }
//
//		break;
//
//	case 4:
//
//		if (rightSide[setSideRand]->lineFlag == 0) { rightSide[setSideRand] = SetLinePoint(5, 1); }
//		break;
//		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }
//
//		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }*/
//		break;
//	case 5:
//		if (setSideRand == 0)
//		{
//			if (rightSide[0]->lineFlag == 0 && rightSide[1]->lineFlag == 0) { rightSide[0] = SetLinePoint(5, 1); rightSide[1] = SetLinePoint(5, 1); }
//			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//			break;
//		}
//		else if (setSideRand == 1)
//		{
//			if (rightSide[1]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[1] = SetLinePoint(5, 1); rightSide[2] = SetLinePoint(5, 1); }
//			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
//			break;
//		}
//		else
//		{
//			if (rightSide[0]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[0] = SetLinePoint(5, 1); rightSide[2] = SetLinePoint(5, 1); }
//			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
//			break;
//		}
//		break;
//	case 6:
//		/*if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//
//		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/
//		if (rightSide[0]->lineFlag == 0) { rightSide[0] = SetLinePoint(5, 1); }
//		if (rightSide[1]->lineFlag == 0) { rightSide[1] = SetLinePoint(5, 1); }
//		if (rightSide[2]->lineFlag == 0) { rightSide[2] = SetLinePoint(5, 1); }
//		break;
//
//		//¶
//	case 7:
//
//		if (leftSide[setSideRand]->lineFlag == 0) { leftSide[setSideRand] = SetLinePoint(setSideRand + 6, 1); }
//		break;
//	case 8:
//		if (setSideRand == 0)
//		{
//			if (leftSide[0]->lineFlag == 0 && leftSide[1]->lineFlag == 0) { leftSide[0] = SetLinePoint(6, 1); leftSide[1] = SetLinePoint(7, 1); }
//			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//			break;
//		}
//		else if (setSideRand == 1)
//		{
//			if (leftSide[1]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[1] = SetLinePoint(7, 1); leftSide[2] = SetLinePoint(8, 1); }
//			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
//			break;
//		}
//		else
//		{
//			if (leftSide[0]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[0] = SetLinePoint(6, 1); leftSide[2] = SetLinePoint(8, 1); }
//			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
//			break;
//		}
//		//if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//		break;
//	case 9:
//
//		if (setSideRand == 0)
//		{
//			if (leftSide[0]->lineFlag == 0) { leftSide[0] = SetLinePoint(9, 1); }
//			break;
//		}
//		else if (setSideRand == 1)
//		{
//			if (leftSide[2]->lineFlag == 0) { leftSide[2] = SetLinePoint(10, 1); }
//			break;
//		}
//		else
//		{
//			if (leftSide[0]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[0] = SetLinePoint(9, 1);  leftSide[2] = SetLinePoint(10, 1); }
//			break;
//		}
//		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }
//		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/
//
//
//		break;
//
//	case 10:
//		if (leftSide[0]->lineFlag == 0) { leftSide[0] = SetLinePoint(6, 1); }
//		if (leftSide[1]->lineFlag == 0) { leftSide[1] = SetLinePoint(7, 1); }
//		if (leftSide[2]->lineFlag == 0) { leftSide[2] = SetLinePoint(8, 1); }
//		break;
//	case 11:
//
//		if (leftSide[setSideRand]->lineFlag == 0) { leftSide[setSideRand] = SetLinePoint(11, 1); }
//		break;
//		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }
//
//		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }*/
//		break;
//	case 12:
//		if (setSideRand == 0)
//		{
//			if (leftSide[0]->lineFlag == 0 && leftSide[1]->lineFlag == 0) { leftSide[0] = SetLinePoint(11, 1); leftSide[1] = SetLinePoint(11, 1); }
//			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//			break;
//		}
//		else if (setSideRand == 1)
//		{
//			if (leftSide[1]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[1] = SetLinePoint(11, 1); leftSide[2] = SetLinePoint(11, 1); }
//			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
//			break;
//		}
//		else
//		{
//			if (leftSide[0]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[0] = SetLinePoint(11, 1); leftSide[2] = SetLinePoint(11, 1); }
//			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
//			break;
//		}
//		break;
//	case 13:
//		/*if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
//
//		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/
//		if (leftSide[0]->lineFlag == 0) { leftSide[0] = SetLinePoint(11, 1); }
//		if (leftSide[1]->lineFlag == 0) { leftSide[1] = SetLinePoint(11, 1); }
//		if (leftSide[2]->lineFlag == 0) { leftSide[2] = SetLinePoint(11, 1); }
//		break;
//
//	default:
//		break;
//	}
//}