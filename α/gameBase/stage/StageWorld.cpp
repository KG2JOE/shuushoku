#include "StageWorld.h"


void StageWorld::Initialize(Input* input)
{
	assert(input);
	this->input_ = input;
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			stageParts[i][j] = new StageParts();
			stageParts[i][j]->OBJWorld = Object3d::Create();
			stageParts[i][j]->OBJWorld->SetModel(modelWorld1);
			stageParts[i][j]->OBJWorld->SetScale({ 5,15,5 });
			XMFLOAT3 pos = { -183.795f + (float)(i * 7.51),-145,-450.0f };
			if (i % 2 == 0)
			{
				pos.z += ((float)j * 8.6f);

			}
			else
			{
				pos.z += ((float)j * 8.6f) - 4.35f;

			}
			stageParts[i][j]->OBJWorldPos = pos;
			stageParts[i][j]->oldOBJWorldPos = stageParts[i][j]->OBJWorldPos;
			stageParts[i][j]->worldjamp = 5.0f;
			stageParts[i][j]->OBJWorld->SetPosition(pos);
		}

	}
	for (UINT i = 0; i < 3; i++)
	{

		frontHeight[i] = new Line();
		backHeight[i] = new Line();

		rightSide[i] = new Line();
		leftSide[i] = new Line();

	}

	for (UINT i = 0; i < 4; i++)
	{

		atkOmen[i] = new AtkOmen();
		atkOmen[i]->model = Model::LoadFromOBJ(name[i]);

		atkOmen[i]->OBJ = Object3d::Create();
		atkOmen[i]->OBJ->SetModel(atkOmen[i]->model);


	}


	atkOmen[0]->OBJ->SetPosition({ 0,14,30 });
	atkOmen[1]->OBJ->SetPosition({ 0,0,50 });
	atkOmen[2]->OBJ->SetPosition({ 0,10,50 });
	atkOmen[2]->OBJ->SetScale({ 6.0f,6.0f,6.0f });
	atkOmen[3]->OBJ->SetPosition({ 0,10,50 });

	atkOmen[1]->OBJ->SetPosition(stageParts[25][25]->OBJWorldPos);
	atkOmen[2]->OBJ->SetPosition(stageParts[25][25]->OBJWorldPos);
	atkOmen[3]->OBJ->SetPosition(stageParts[25][25]->OBJWorldPos);
}

void StageWorld::Update()
{

	if (impactFlag == 1)
	{
		WaveATK();
	}
	for (UINT i = 0; i < 3; i++)
	{
		UINT a = rand() % 360 - 148 - 33.795f;
		frontHeightPosRand[i] = a;

		UINT b = rand() % 425 - 455;
		RightSidePosRand[i] = b;

		UINT c = rand() % 360 - 148 - 33.795f;
		backHeightPosRand[i] = c;

		UINT d = rand() % 425 - 455;
		leftSidePosRand[i] = d;
		
		if (frontHeight[i]->lineFlag >= 1)
		{
			FrontHeightLineATK(i);
		}
		if (backHeight[i]->lineFlag >= 1)
		{
			BackHeightLineATK(i);
		}

		if (rightSide[i]->lineFlag >= 1)
		{
			RightSideLineATK(i);
		}

		if (leftSide[i]->lineFlag >= 1)
		{
			leftSideLineATK(i);
		}
	}
	UINT b = rand() % 3;

	setHeightRand = b;
	UINT a = rand() % 3;
	setSideRand = a;
	StageUpdate();

	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			stageParts[i][j]->OBJWorld->Update();
		}

	}
	for (UINT i = 0; i < 4; i++)
	{
		atkOmen[i]->OBJ->Update();
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

				stageParts[i][j]->OBJWorldPos.y += stageParts[i][j]->worldjamp;
				stageParts[i][j]->worldjamp -= 0.5f;
				stageParts[i][j]->OBJWorld->SetPosition(stageParts[i][j]->OBJWorldPos);
				if (stageParts[i][j]->worldjamp < -5.0f)
				{
					stageParts[i][j]->worldjamp = 30.0f;
					if (stageParts[i][j]->flont == false && stageParts[i][j]->back == false && stageParts[i][j]->right == false && stageParts[i][j]->left == false)
					{
						stageParts[i][j]->OBJWorld->SetModel(modelWorld1);
					}
					else
					{
						stageParts[i][j]->OBJWorld->SetModel(modelWorld2);

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
				}
				else
				{
					stageParts[i][j]->OBJWorld->SetModel(modelWorld2);

				}
				stageParts[i][j]->worldjamp = 5.0f;
				stageParts[i][j]->OBJWorldFlag = 0;
				stageParts[i][j]->OBJWorld->SetPosition(stageParts[i][j]->oldOBJWorldPos);

			}
			
		}
	}
}

void StageWorld::Draw()
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			stageParts[i][j]->OBJWorld->Draw();

		}
	}
	for (UINT i = 0; i < 4; i++)
	{
		atkOmen[i]->OBJ->Draw();
	}

}

void StageWorld::Delete()
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			delete stageParts[i][j]->OBJWorld;
			delete stageParts[i][j];
		}
	}
	delete modelWorld1, modelWorld2, modelWorld3, modelAtkHud;


	for (int i = 0; i < 4; i++)
	{
		delete atkOmen[i]->model;
		delete atkOmen[i]->OBJ;
		delete atkOmen[i];
	}
}

void StageWorld::WaveATK()
{

	impactRad += 2.0f;
	if (impactRad > 250)
	{
		impactFlag = 0;
	}
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (stageParts[i][j]->OBJWorldFlag == 0)
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

void StageWorld::FrontHeightLineATK(UINT point)
{

	if (frontHeight[point]->lineFlag == 1)
	{
		frontHeight[point]->oldPos = frontHeight[point]->linePos;

		frontHeight[point]->lineFlag = 2;

	}
	if (frontHeight[point]->lineFlag == 2)
	{
		frontHeight[point]->lineAccele += 0.2f;

		frontHeight[point]->linePos.x -= sin((frontHeight[point]->lineAngle * DirectX::XM_PI) / 180) * frontHeight[point]->lineAccele;
		frontHeight[point]->linePos.z -= cos((frontHeight[point]->lineAngle * DirectX::XM_PI) / 180) * frontHeight[point]->lineAccele;
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{

				bool isHit = Collision::HitCircle(stageParts[i][j]->OBJWorldPos, 5, frontHeight[point]->linePos, 5, 1);
				if (isHit)
				{
					stageParts[i][j]->OBJWorld->SetModel(modelWorld2);
					stageParts[i][j]->flont = true;

				}
			}
		}
		if (frontHeight[point]->linePos.z < -455)
		{
			frontHeight[point]->lineAccele = 0.0f;
			frontHeight[point]->linePos = frontHeight[point]->oldPos;
			frontHeight[point]->lineFlag = 3;
		}
	}
	if (frontHeight[point]->lineFlag == 3)
	{
		frontHeight[point]->lineAccele += 0.2f;

		frontHeight[point]->linePos.x -= sin((frontHeight[point]->lineAngle * DirectX::XM_PI) / 180) * frontHeight[point]->lineAccele;
		frontHeight[point]->linePos.z -= cos((frontHeight[point]->lineAngle * DirectX::XM_PI) / 180) * frontHeight[point]->lineAccele;
		if (frontHeight[point]->linePos.z < -455)
		{

			frontHeight[point]->lineFlag = 0;
		}
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				if (stageParts[i][j]->OBJWorldFlag == 0)
				{
					stageParts[i][j]->OBJWorldFlag = Collision::HitCircle(stageParts[i][j]->OBJWorldPos, 5, frontHeight[point]->linePos, 5, 1);

					stageParts[i][j]->flont = false;
				}
			}
		}
	}

}

void StageWorld::BackHeightLineATK(UINT point)
{

	if (backHeight[point]->lineFlag == 1)
	{
		backHeight[point]->oldPos = backHeight[point]->linePos;

		backHeight[point]->lineFlag = 2;

	}
	if (backHeight[point]->lineFlag == 2)
	{
		backHeight[point]->lineAccele += 0.2f;

		backHeight[point]->linePos.x += sin((backHeight[point]->lineAngle * DirectX::XM_PI) / 180) * backHeight[point]->lineAccele;
		backHeight[point]->linePos.z += cos((backHeight[point]->lineAngle * DirectX::XM_PI) / 180) * backHeight[point]->lineAccele;
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{

				bool isHit = Collision::HitCircle(stageParts[i][j]->OBJWorldPos, 5, backHeight[point]->linePos, 5, 1);
				if (isHit)
				{
					stageParts[i][j]->OBJWorld->SetModel(modelWorld2);
					stageParts[i][j]->back = true;
				}
			}
		}
		if (backHeight[point]->linePos.z > -30)
		{
			backHeight[point]->lineAccele = 0.0f;
			backHeight[point]->linePos = backHeight[point]->oldPos;
			backHeight[point]->lineFlag = 3;
		}
	}
	if (backHeight[point]->lineFlag == 3)
	{
		backHeight[point]->lineAccele += 0.2f;

		backHeight[point]->linePos.x += sin((backHeight[point]->lineAngle * DirectX::XM_PI) / 180) * backHeight[point]->lineAccele;
		backHeight[point]->linePos.z += cos((backHeight[point]->lineAngle * DirectX::XM_PI) / 180) * backHeight[point]->lineAccele;
		if (backHeight[point]->linePos.z > -30)
		{

			backHeight[point]->lineFlag = 0;
		}
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				if (stageParts[i][j]->OBJWorldFlag == 0)
				{
					stageParts[i][j]->OBJWorldFlag = Collision::HitCircle(stageParts[i][j]->OBJWorldPos, 5, backHeight[point]->linePos, 5, 1);
					stageParts[i][j]->back = false;

				}
			}
		}
	}

}

void StageWorld::SetHeightLineCase(char pattern)
{
	switch (pattern)
	{
		//前
	case 0:

		if (frontHeight[setHeightRand]->lineFlag == 0) { frontHeight[setHeightRand] = SetHeightLinePoint(setHeightRand); }
		break;
	case 1:
		if (setHeightRand == 0)
		{
			if (frontHeight[0]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[0] = SetHeightLinePoint(0);  frontHeight[1] = SetHeightLinePoint(1); }
			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
			break;
		}
		else if (setHeightRand == 1)
		{
			if (frontHeight[1]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[1] = SetHeightLinePoint(1); frontHeight[2] = SetHeightLinePoint(2); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		else
		{
			if (frontHeight[0]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[0] = SetHeightLinePoint(0);  frontHeight[2] = SetHeightLinePoint(2); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		//if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
		break;
	case 2:

		if (setHeightRand == 0)
		{
			if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetHeightLinePoint(3); }
			break;
		}
		else if (setHeightRand == 1)
		{
			if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetHeightLinePoint(4); }
			break;
		}
		else
		{
			if (frontHeight[0]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[0] = SetHeightLinePoint(3);  frontHeight[2] = SetHeightLinePoint(4); }
			break;
		}
		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }
		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/


		break;
	case 3:

		if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetHeightLinePoint(0); }
		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetHeightLinePoint(1); }
		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetHeightLinePoint(2); }

		break;

	case 4:

		if (frontHeight[setHeightRand]->lineFlag == 0) { frontHeight[setHeightRand] = SetHeightLinePoint(setHeightRand + 5); }
		break;
		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }

		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }*/
		break;
	case 5:
		if (setHeightRand == 0)
		{
			if (frontHeight[0]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[0] = SetHeightLinePoint(5);  frontHeight[1] = SetHeightLinePoint(6); }
			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
			break;
		}
		else if (setHeightRand == 1)
		{
			if (frontHeight[1]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[1] = SetHeightLinePoint(6); frontHeight[2] = SetHeightLinePoint(7); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		else
		{
			if (frontHeight[0]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[0] = SetHeightLinePoint(5);  frontHeight[2] = SetHeightLinePoint(7); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		break;
	case 6:
		/*if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }

		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/
		if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetHeightLinePoint(5); }
		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetHeightLinePoint(6); }
		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetHeightLinePoint(7); }
		break;

		//後ろ
	case 7:

		if (backHeight[setHeightRand]->lineFlag == 0) { backHeight[setHeightRand] = SetHeightLinePoint(setHeightRand + 8); }
		break;
	case 8:
		if (setHeightRand == 0)
		{
			if (backHeight[0]->lineFlag == 0 && backHeight[1]->lineFlag == 0) { backHeight[0] = SetHeightLinePoint(8);  backHeight[1] = SetHeightLinePoint(9); }
			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
			break;
		}
		else if (setHeightRand == 1)
		{
			if (backHeight[1]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[1] = SetHeightLinePoint(9); backHeight[2] = SetHeightLinePoint(10); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		else
		{
			if (backHeight[0]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[0] = SetHeightLinePoint(8);  backHeight[2] = SetHeightLinePoint(10); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		//if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
		break;
	case 9:

		if (setHeightRand == 0)
		{
			if (backHeight[0]->lineFlag == 0) { backHeight[0] = SetHeightLinePoint(11); }
			break;
		}
		else if (setHeightRand == 1)
		{
			if (backHeight[2]->lineFlag == 0) { backHeight[2] = SetHeightLinePoint(12); }
			break;
		}
		else
		{
			if (backHeight[0]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[0] = SetHeightLinePoint(11);  backHeight[2] = SetHeightLinePoint(12); }
			break;
		}
		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }
		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/


		break;

	case 10:
		if (backHeight[0]->lineFlag == 0) { backHeight[0] = SetHeightLinePoint(8); }
		if (backHeight[1]->lineFlag == 0) { backHeight[1] = SetHeightLinePoint(9); }
		if (backHeight[2]->lineFlag == 0) { backHeight[2] = SetHeightLinePoint(10); }
		break;
	case 11:

		if (backHeight[setHeightRand]->lineFlag == 0) { backHeight[setHeightRand] = SetHeightLinePoint(setHeightRand + 13); }
		break;
		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }

		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }*/
		break;
	case 12:
		if (setHeightRand == 0)
		{
			if (backHeight[0]->lineFlag == 0 && backHeight[1]->lineFlag == 0) { backHeight[0] = SetHeightLinePoint(13);  backHeight[1] = SetHeightLinePoint(14); }
			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
			break;
		}
		else if (setHeightRand == 1)
		{
			if (backHeight[1]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[1] = SetHeightLinePoint(14); backHeight[2] = SetHeightLinePoint(15); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		else
		{
			if (backHeight[0]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[0] = SetHeightLinePoint(13);  backHeight[2] = SetHeightLinePoint(15); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		break;
	case 13:
		/*if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }

		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/
		if (backHeight[0]->lineFlag == 0) { backHeight[0] = SetHeightLinePoint(13); }
		if (backHeight[1]->lineFlag == 0) { backHeight[1] = SetHeightLinePoint(14); }
		if (backHeight[2]->lineFlag == 0) { backHeight[2] = SetHeightLinePoint(15); }
		break;
	
	default:
		break;
	}

}

void StageWorld::RightSideLineATK(UINT point)
{
	if (rightSide[point]->lineFlag == 1)
	{
		rightSide[point]->oldPos = rightSide[point]->linePos;

		rightSide[point]->lineFlag = 2;

	}
	if (rightSide[point]->lineFlag == 2)
	{
		rightSide[point]->lineAccele += 0.2f;

		rightSide[point]->linePos.x -= sin(((rightSide[point]->lineAngle + 90) * DirectX::XM_PI) / 180) * rightSide[point]->lineAccele;
		rightSide[point]->linePos.z -= cos(((rightSide[point]->lineAngle + 90) * DirectX::XM_PI) / 180) * rightSide[point]->lineAccele;
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{

				bool isHit = Collision::HitCircle(stageParts[i][j]->OBJWorldPos, 5, rightSide[point]->linePos, 5, 1);
				if (isHit)
				{
					stageParts[i][j]->OBJWorld->SetModel(modelWorld2);
					stageParts[i][j]->right = true;

				}
			}
		}
		if (rightSide[point]->linePos.x < -183.795f)
		{
			rightSide[point]->lineAccele = 0.0f;
			rightSide[point]->linePos = rightSide[point]->oldPos;
			rightSide[point]->lineFlag = 3;
		}
	}
	if (rightSide[point]->lineFlag == 3)
	{
		rightSide[point]->lineAccele += 0.2f;

		rightSide[point]->linePos.x -= sin(((rightSide[point]->lineAngle + 90) * DirectX::XM_PI) / 180) * rightSide[point]->lineAccele;
		rightSide[point]->linePos.z -= cos(((rightSide[point]->lineAngle + 90) * DirectX::XM_PI) / 180) * rightSide[point]->lineAccele;
		if (rightSide[point]->linePos.x < -183.795f)
		{

			rightSide[point]->lineFlag = 0;
		}
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				if (stageParts[i][j]->OBJWorldFlag == 0)
				{
					stageParts[i][j]->OBJWorldFlag = Collision::HitCircle(stageParts[i][j]->OBJWorldPos, 5, rightSide[point]->linePos, 5, 1);
					stageParts[i][j]->right = false;

				}
			}
		}
	}
}

void StageWorld::leftSideLineATK(UINT point)
{
	if (leftSide[point]->lineFlag == 1)
	{
		leftSide[point]->oldPos = leftSide[point]->linePos;

		leftSide[point]->lineFlag = 2;

	}
	if (leftSide[point]->lineFlag == 2)
	{
		leftSide[point]->lineAccele += 0.2f;

		leftSide[point]->linePos.x += sin(((leftSide[point]->lineAngle + 90) * DirectX::XM_PI) / 180) * leftSide[point]->lineAccele;
		leftSide[point]->linePos.z += cos(((leftSide[point]->lineAngle + 90) * DirectX::XM_PI) / 180) * leftSide[point]->lineAccele;
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{

				bool isHit = Collision::HitCircle(stageParts[i][j]->OBJWorldPos, 5, leftSide[point]->linePos, 5, 1);
				if (isHit)
				{
					stageParts[i][j]->OBJWorld->SetModel(modelWorld2);
					stageParts[i][j]->left = true;
				}
			}
		}
		if (leftSide[point]->linePos.x > 185.205f)
		{
			leftSide[point]->lineAccele = 0.0f;
			//leftSide[point]->linePos = leftSide[point]->oldPos;
			leftSide[point]->lineFlag = 3;
		}
	}
	if (leftSide[point]->lineFlag == 3)
	{
		leftSide[point]->lineAccele += 0.2f;

		leftSide[point]->oldPos.x += sin(((leftSide[point]->lineAngle + 90) * DirectX::XM_PI) / 180) * leftSide[point]->lineAccele;
		leftSide[point]->oldPos.z += cos(((leftSide[point]->lineAngle + 90) * DirectX::XM_PI) / 180) * leftSide[point]->lineAccele;
		if (leftSide[point]->oldPos.x > 185.205f)
		{

			leftSide[point]->lineFlag = 0;
		}
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{


				if (stageParts[i][j]->OBJWorldFlag == 0)
				{
					stageParts[i][j]->OBJWorldFlag = Collision::HitCircle(stageParts[i][j]->OBJWorldPos, 5, leftSide[point]->oldPos, 5, 1);
					stageParts[i][j]->left = false;

				}
			}
		}
	}
}

void StageWorld::SetWidthLineCase(char pattern)
{
	switch (pattern)
	{
		//右
	case 0:

		if (rightSide[setSideRand]->lineFlag == 0) { rightSide[setSideRand] = SetSideLinePoint(setSideRand); }
		break;
	case 1:
		if (setSideRand == 0)
		{
			if (rightSide[0]->lineFlag == 0 && rightSide[1]->lineFlag == 0) { rightSide[0] = SetSideLinePoint(0);  rightSide[1] = SetSideLinePoint(1); }

			break;
		}
		else if (setSideRand == 1)
		{
			if (rightSide[1]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[1] = SetSideLinePoint(1); rightSide[2] = SetSideLinePoint(2); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		else
		{
			if (rightSide[0]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[0] = SetSideLinePoint(0);  rightSide[2] = SetSideLinePoint(2); }

			break;
		}

		break;
	case 2:

		if (setSideRand == 0)
		{
			if (rightSide[0]->lineFlag == 0) { rightSide[0] = SetSideLinePoint(3); }
			break;
		}
		else if (setSideRand == 1)
		{
			if (rightSide[2]->lineFlag == 0) { rightSide[2] = SetSideLinePoint(4); }
			break;
		}
		else
		{
			if (rightSide[0]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[0] = SetSideLinePoint(3);  rightSide[2] = SetSideLinePoint(4); }
			break;
		}
		break;
	case 3:

		if (rightSide[0]->lineFlag == 0) { rightSide[0] = SetSideLinePoint(0); }
		if (rightSide[1]->lineFlag == 0) { rightSide[1] = SetSideLinePoint(1); }
		if (rightSide[2]->lineFlag == 0) { rightSide[2] = SetSideLinePoint(2); }

		break;

	case 4:

		if (rightSide[setSideRand]->lineFlag == 0) { rightSide[setSideRand] = SetSideLinePoint(setSideRand + 5); }
		break;
	case 5:
		if (setSideRand == 0)
		{
			if (rightSide[0]->lineFlag == 0 && rightSide[1]->lineFlag == 0) { rightSide[0] = SetSideLinePoint(5);  rightSide[1] = SetSideLinePoint(6); }
			break;
		}
		else if (setSideRand == 1)
		{
			if (rightSide[1]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[1] = SetSideLinePoint(6); rightSide[2] = SetSideLinePoint(7); }
			break;
		}
		else
		{
			if (rightSide[0]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[0] = SetSideLinePoint(5);  rightSide[2] = SetSideLinePoint(7); }
			break;
		}
		break;
	case 6:
		if (rightSide[0]->lineFlag == 0) { rightSide[0] = SetSideLinePoint(5); }
		if (rightSide[1]->lineFlag == 0) { rightSide[1] = SetSideLinePoint(6); }
		if (rightSide[2]->lineFlag == 0) { rightSide[2] = SetSideLinePoint(7); }
		break;

		//左
	case 7:
		if (leftSide[setSideRand]->lineFlag == 0) { leftSide[setSideRand] = SetSideLinePoint(setSideRand + 8); }

		break;
	case 8:
		if (setSideRand == 0)
		{
			if (leftSide[0]->lineFlag == 0 && leftSide[1]->lineFlag == 0) { leftSide[0] = SetSideLinePoint(8);  leftSide[1] = SetSideLinePoint(9); }

			break;
		}
		else if (setSideRand == 1)
		{
			if (leftSide[1]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[1] = SetSideLinePoint(9); leftSide[2] = SetSideLinePoint(10); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		else
		{
			if (leftSide[0]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[0] = SetSideLinePoint(8);  leftSide[2] = SetSideLinePoint(10); }

			break;
		}
		//if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
		break;
	case 9:

		if (setSideRand == 0)
		{
			if (leftSide[0]->lineFlag == 0) { leftSide[0] = SetSideLinePoint(11); }
			break;
		}
		else if (setSideRand == 1)
		{
			if (leftSide[2]->lineFlag == 0) { leftSide[2] = SetSideLinePoint(12); }
			break;
		}
		else
		{
			if (leftSide[0]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[0] = SetSideLinePoint(11);  leftSide[2] = SetSideLinePoint(12); }
			break;
		}
		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }
		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/
		break;
	case 10:

		if (leftSide[0]->lineFlag == 0) { leftSide[0] = SetSideLinePoint(8); }
		if (leftSide[1]->lineFlag == 0) { leftSide[1] = SetSideLinePoint(9); }
		if (leftSide[2]->lineFlag == 0) { leftSide[2] = SetSideLinePoint(10); }

		break;
	case 11:
		if (leftSide[setSideRand]->lineFlag == 0) { leftSide[setSideRand] = SetSideLinePoint(setSideRand + 13); }
		break;
		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }
		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }*/
		break;
	case 12:
		if (setSideRand == 0)
		{
			if (leftSide[0]->lineFlag == 0 && leftSide[1]->lineFlag == 0) { leftSide[0] = SetSideLinePoint(13);  leftSide[1] = SetSideLinePoint(14); }
			break;
		}
		else if (setSideRand == 1)
		{
			if (leftSide[1]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[1] = SetSideLinePoint(14); leftSide[2] = SetSideLinePoint(15); }
			break;
		}
		else
		{
			if (leftSide[0]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[0] = SetSideLinePoint(13);  leftSide[2] = SetSideLinePoint(15); }
			break;
		}
		break;
	case 13:
		/*if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/
		if (leftSide[0]->lineFlag == 0) { leftSide[0] = SetSideLinePoint(13); }
		if (leftSide[1]->lineFlag == 0) { leftSide[1] = SetSideLinePoint(14); }
		if (leftSide[2]->lineFlag == 0) { leftSide[2] = SetSideLinePoint(15); }
		break;
	
	default:
		break;
	}


}

StageWorld::Line* StageWorld::SetHeightLinePoint(char point)
{
	Line* temp = new Line();


	temp->lineAngle = 0;
	temp->lineFlag = 1;

	switch (point)
	{
		//前
	case 0:
	{
		temp->linePos = { -148 - 33.795f,0,-30 };
		break;
	}
	case 1:
	{
		temp->linePos = { 35 - 33.795f,0,-30 };
		break;
	}
	case 2:
	{
		temp->linePos = { 217 - 33.795f,0,-30 };
		break;
	}
	case 3:
	{
		temp->linePos = { -148 - 33.795f,0,-30 };
		temp->lineAngle = -41;

		break;
	}
	case 4:
	{
		temp->linePos = { 217 - 33.795f,0,-30 };
		temp->lineAngle = 41;

		break;
	}
	case 5:
	{
		temp->linePos = { (float)frontHeightPosRand[0],0,-30 };
		//temp->lineAngle = 41;
		break;
	}
	case 6:
	{
		temp->linePos = { (float)frontHeightPosRand[1],0,-30 };
		//temp->lineAngle = 41;
		break;
	}
	case 7:
	{
		temp->linePos = { (float)frontHeightPosRand[2],0,-30 };
		//temp->lineAngle = 41;
		break;
	}
	//後ろ
	case 8:
	{
		temp->linePos = { -148 - 33.795f,0,-455 };
		break;
	}
	case 9:
	{
		temp->linePos = { 35 - 33.795f,0,-455 };
		break;
	}
	case 10:
	{
		temp->linePos = { 217 - 33.795f,0,-455 };
		break;
	}
	case 11:
	{
		temp->linePos = { 217 - 33.795f,0,-455 };
		temp->lineAngle = -41;

		break;
	}
	case 12:
	{
		temp->linePos = { -148 - 33.795f,0,-455 };
		temp->lineAngle = 41;

		break;
	}
	case 13:
	{
		temp->linePos = { (float)backHeightPosRand[0],0,-455 };
		//temp->lineAngle = 41;
		break;
	}
	case 14:
	{
		temp->linePos = { (float)backHeightPosRand[1],0,-455 };
		//temp->lineAngle = 41;
		break;
	}
	case 15:
	{
		temp->linePos = { (float)backHeightPosRand[2],0,-455 };
		//temp->lineAngle = 41;
		break;
	}
	default:
		break;
	}
	return temp;
}

StageWorld::Line* StageWorld::SetSideLinePoint(char point)
{
	Line* temp = new Line();


	temp->lineAngle = 0;
	temp->lineFlag = 1;

	switch (point)
	{
		//右
	case 0:
	{
		temp->linePos = { 217 - 33.795f,0,-455 };
		break;
	}
	case 1:
	{
		temp->linePos = { 217 - 33.795f,0,-212 };
		break;
	}
	case 2:
	{
		temp->linePos = { 217 - 33.795f,0,-30 };
		break;
	}
	case 3:
	{
		temp->linePos = { 217 - 33.795f,0,-455 };
		temp->lineAngle = 49;

		break;
	}
	case 4:
	{
		temp->linePos = { 217 - 33.795f,0,-30 };
		temp->lineAngle = -49;

		break;
	}
	case 5:
	{
		temp->linePos = { 217 - 33.795f,0,(float)RightSidePosRand[0] };
		//temp->lineAngle = 41;
		break;
	}
	case 6:
	{
		temp->linePos = { 217 - 33.795f,0,(float)RightSidePosRand[1] };
		//temp->lineAngle = 41;
		break;
	}
	case 7:
	{
		temp->linePos = { 217 - 33.795f,0,(float)RightSidePosRand[2] };
		//temp->lineAngle = 41;
		break;
	}
	//左
	case 8:
	{
		temp->linePos = { -150 - 33.795f,0,-453 };
		break;
	}
	case 9:
	{
		temp->linePos = { -150 - 33.795f,0,-212 };
		break;
	}
	case 10:
	{
		temp->linePos = { -150 - 33.795f,0,-30 };
		break;
	}
	case 11:
	{
		temp->linePos = { -150 - 33.795f,0,-30 };
		temp->lineAngle = 49;

		break;
	}
	case 12:
	{
		temp->linePos = { -150 - 33.795f,0,-453 };
		temp->lineAngle = -49;

		break;
	}
	case 13:
	{
		temp->linePos = { -150 - 33.795f,0,(float)leftSidePosRand[0] };
		//temp->lineAngle = 41;
		break;
	}
	case 14:
	{
		temp->linePos = { -150 - 33.795f,0,(float)leftSidePosRand[1] };
		//temp->lineAngle = 41;
		break;
	}
	case 15:
	{
		temp->linePos = { -150 - 33.795f,0,(float)leftSidePosRand[2] };
		//temp->lineAngle = 41;
		break;
	}
	default:
		break;
	}
	return temp;
}


