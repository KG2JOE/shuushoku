#include "StageWorld.h"


void StageWorld::Initialize(Input* input)
{
	assert(input);
	this->input_ = input;
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			/*stageParts[i][j] = new StageParts();
			stageParts[i][j]->OBJWorld = Object3d::Create();
			stageParts[i][j]->OBJWorld->SetModel(modelWorld1);
			stageParts[i][j]->OBJWorld->SetScale({ 5,15,5 });
			XMFLOAT3 pos = { -183.795f + (float)(i * 7.51),-145,-450.0f };
			if (i % 2 == 0)
			{
				pos.z += ((float)j * 10.0f);

			}
			else
			{
				pos.z += ((float)j * 10.0f) - 4.35f;

			}
			stageParts[i][j]->OBJWorldPos = pos;
			stageParts[i][j]->oldOBJWorldPos = stageParts[i][j]->OBJWorldPos;
			stageParts[i][j]->worldjamp = 5.0f;
			stageParts[i][j]->OBJWorld->SetPosition(pos);*/
			stageParts[i][j] = StagePartsIns(i, j);

		}


	}
	for (int i = 0; i < 50; i++)
	{
		plainWorld[i] = new StageParts();
		plainWorld[i]->OBJWorld = Object3d::Create();
		plainWorld[i]->OBJWorld->SetModel(modelplainWorld);
		plainWorld[i]->OBJWorld->SetScale({ 5,15,5 });
		XMFLOAT3 pos = { -183.795f + (float)(i * 7.51),-145.10f,-275.0f + (8.6f * 3) };
		if (i % 2 == 0)
		{
			pos.z += 8.6f;

		}
		else
		{
			pos.z += 8.6f - 4.35f;

		}
		plainWorld[i]->OBJWorldPos = pos;
		plainWorld[i]->oldOBJWorldPos = plainWorld[i]->OBJWorldPos;
		plainWorld[i]->worldjamp = 5.0f;
		plainWorld[i]->OBJWorld->SetPosition(pos);
	}
	for (UINT i = 0; i < 3; i++)
	{

		/*frontHeight[i] = new Line();
		backHeight[i] = new Line();

		rightSide[i] = new Line();
		leftSide[i] = new Line();*/
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
	ground = new SKY();
	ground->OBJ = Object3d::Create();
	ground->model = Model::LoadFromOBJ("ground");
	ground->OBJ->SetModel(ground->model);
	ground->OBJ->SetPosition({ stageParts[25][25]->OBJWorldPos.x + 5,3, stageParts[25][25]->OBJWorldPos.z - 4.75f });
	ground->OBJ->SetScale({ 14,14,14 });
	ground->OBJ->SetRotation({ 0,0,0 });
	ground->OBJ->Update();
	//	sky[2]->OBJ->SetScale({10,7,10});
	rnd = new RndCreate();

}

void StageWorld::GameInitialize()
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			/*stageParts[i][j]->OBJWorld->SetModel(modelWorld1);
			stageParts[i][j]->OBJWorld->SetScale({ 5,15,5 });
			XMFLOAT3 pos = { -183.795f + (float)(i * 7.52),-145,-450.0f - 2.3f };
			if (i % 2 == 0)
			{
				pos.z += ((float)j * 8.65f);

			}
			else
			{
				pos.z += ((float)j * 8.65f) - 4.35f;

			}
			stageParts[i][j]->OBJWorldPos = pos;
			stageParts[i][j]->oldOBJWorldPos = stageParts[i][j]->OBJWorldPos;
			stageParts[i][j]->worldjamp = 5.0f;
			stageParts[i][j]->OBJWorld->SetPosition(pos);
			stageParts[i][j]->Manifest = 0;*/
			stageParts[i][j] = StagePartsIns(i, j);
		}

	}
	for (UINT i = 0; i < 3; i++)
	{

		/*frontHeight[i] = {};
		backHeight[i] = {};
		rightSide[i] = {};
		leftSide[i] = {};
		frontHeight[i] = new Line();
		backHeight[i] = new Line();
		rightSide[i] = new Line();
		leftSide[i] = new Line();*/
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
		if (frontHeight[i]->lineFlag >= 1)
		{
			//FrontHeightLineATK(i);
			frontHeight[i] = StagePointer::LineAtk(frontHeight[i], 1);
			for (int j = 0; j < 50; j++)
			{
				for (int k = 0; k < 50; k++)
				{
					stageParts[j][k] = StagePointer::LineAtkFlag(frontHeight[i], stageParts[j][k], modelWorld2, 1);
				}
			}
		}
		if (backHeight[i]->lineFlag >= 1)
		{
			//BackHeightLineATK(i);
			backHeight[i] = StagePointer::LineAtk(backHeight[i], 3);
			for (int j = 0; j < 50; j++)
			{
				for (int k = 0; k < 50; k++)
				{
					stageParts[j][k] = StagePointer::LineAtkFlag(backHeight[i], stageParts[j][k], modelWorld2, 3);
				}
			}
		}

		if (rightSide[i]->lineFlag >= 1)
		{
			//RightSideLineATK(i);
			rightSide[i] = StagePointer::LineAtk(rightSide[i], 0);
			for (int j = 0; j < 50; j++)
			{
				for (int k = 0; k < 50; k++)
				{
					stageParts[j][k] = StagePointer::LineAtkFlag(rightSide[i], stageParts[j][k], modelWorld2, 0);
				}
			}
		}

		if (leftSide[i]->lineFlag >= 1)
		{
			//eftSideLineATK(i);
			leftSide[i] = StagePointer::LineAtk(leftSide[i], 2);
			for (int j = 0; j < 50; j++)
			{
				for (int k = 0; k < 50; k++)
				{
					stageParts[j][k] = StagePointer::LineAtkFlag(leftSide[i], stageParts[j][k], modelWorld2, 2);
				}
			}
		}
	}
	//UINT b = rand() % 3;
	UINT b = rnd->getRandInt(0, 2);

	setHeightRand = b;
	UINT a = rnd->getRandInt(0, 2);
	setSideRand = a;
	StageUpdate();
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
	ground->OBJ->Update();
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

void StageWorld::Draw()
{
	for (int i = 0; i < 50; i++)
	{

		for (int j = 0; j < 50; j++)
		{
			//if(stageParts[i][j]->back!=0|| stageParts[i][j]->flont != 0 || stageParts[i][j]->left != 0 || stageParts[i][j]->right != 0 || stageParts[i][j]->OBJWorldFlag!=0)
			//if (stageParts[i][j]->Manifest == 1 || stageParts[i][j]->playerRockOnFlag == 1)stageParts[i][j]->OBJWorld->Draw();
			stageParts[i][j]->OBJWorld->Draw();
		}
		//plainWorld[i]->OBJWorld->Draw();

	}
	/*for (int j = 0; j < 50; j++)
	{
		stageParts[25][j]->OBJWorld->Draw();
		stageParts[j][25]->OBJWorld->Draw();
	}*/


	for (int i = 0; i < 3; i++)
	{
		sky[i]->OBJ->Draw();
	}
	//ground->OBJ->Draw();
}

void StageWorld::Delete()
{
	/*for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			delete stageParts[i][j]->OBJWorld;
			delete stageParts[i][j];
		}
	}*/
	//delete modelWorld1, modelWorld2, modelWorld3;

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
					stageParts[i][j]->flont = 1;
					stageParts[i][j]->Manifest = 1;


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

					stageParts[i][j]->flont = 0;
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
					stageParts[i][j]->Manifest = 1;

					stageParts[i][j]->back = true;
				}
			}
		}
		if (backHeight[point]->linePos.z > -20)
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
		//�O
	case 0:

		if (frontHeight[setHeightRand]->lineFlag == 0) { frontHeight[setHeightRand] = StagePointer::SetLinePoint(setHeightRand, 0)/*SetHeightLinePoint(setHeightRand)*/; }
		break;
	case 1:
		if (setHeightRand == 0)
		{
			if (frontHeight[0]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[0] = StagePointer::SetLinePoint(0, 0); frontHeight[1] = StagePointer::SetLinePoint(1, 0); }
			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
			break;
		}
		else if (setHeightRand == 1)
		{
			if (frontHeight[1]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[1] = StagePointer::SetLinePoint(1, 0); frontHeight[2] = StagePointer::SetLinePoint(2, 0); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		else
		{
			if (frontHeight[0]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[0] = StagePointer::SetLinePoint(0, 0); frontHeight[2] = StagePointer::SetLinePoint(2, 0); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		//if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
		break;
	case 2:

		if (setHeightRand == 0)
		{
			if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = StagePointer::SetLinePoint(3,0); }
			break;
		}
		else if (setHeightRand == 1)
		{
			if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = StagePointer::SetLinePoint(4,0); }
			break;
		}
		else
		{
			if (frontHeight[0]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[0] = StagePointer::SetLinePoint(3,0);  frontHeight[2] = StagePointer::SetLinePoint(4,0); }
			break;
		}
		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }
		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/


		break;
	case 3:

		if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = StagePointer::SetLinePoint(0,0); }
		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = StagePointer::SetLinePoint(1,0); }
		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = StagePointer::SetLinePoint(2,0); }

		break;

	case 4:

		if (frontHeight[setHeightRand]->lineFlag == 0) { frontHeight[setHeightRand] = StagePointer::SetLinePoint(5,0); }
		break;
		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }

		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }*/
		break;
	case 5:
		if (setHeightRand == 0)
		{
			if (frontHeight[0]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[0] = StagePointer::SetLinePoint(5,0);  frontHeight[1] = StagePointer::SetLinePoint(5,0); }
			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
			break;
		}
		else if (setHeightRand == 1)
		{
			if (frontHeight[1]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[1] = StagePointer::SetLinePoint(5,0); frontHeight[2] = StagePointer::SetLinePoint(5,0); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		else
		{
			if (frontHeight[0]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[0] = StagePointer::SetLinePoint(5,0);  frontHeight[2] = StagePointer::SetLinePoint(5,0); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		break;
	case 6:
		/*if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }

		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/
		if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = StagePointer::SetLinePoint(5,0); }
		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = StagePointer::SetLinePoint(5,0); }
		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = StagePointer::SetLinePoint(5,0); }
		break;

		//���
	case 7:

		if (backHeight[setHeightRand]->lineFlag == 0) { backHeight[setHeightRand] = StagePointer::SetLinePoint(setHeightRand + 6,0); }
		break;
	case 8:
		if (setHeightRand == 0)
		{
			if (backHeight[0]->lineFlag == 0 && backHeight[1]->lineFlag == 0) { backHeight[0] = StagePointer::SetLinePoint(6,0);  backHeight[1] = StagePointer::SetLinePoint(7,0); }
			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
			break;
		}
		else if (setHeightRand == 1)
		{
			if (backHeight[1]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[1] = StagePointer::SetLinePoint(7,0); backHeight[2] = StagePointer::SetLinePoint(8,0); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		else
		{
			if (backHeight[0]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[0] = StagePointer::SetLinePoint(6,0);  backHeight[2] = StagePointer::SetLinePoint(8,0); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		//if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
		break;
	case 9:

		if (setHeightRand == 0)
		{
			if (backHeight[0]->lineFlag == 0) { backHeight[0] = StagePointer::SetLinePoint(9,0); }
			break;
		}
		else if (setHeightRand == 1)
		{
			if (backHeight[2]->lineFlag == 0) { backHeight[2] = StagePointer::SetLinePoint(10,0); }
			break;
		}
		else
		{
			if (backHeight[0]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[0] = StagePointer::SetLinePoint(9,0);  backHeight[2] = StagePointer::SetLinePoint(10,0); }
			break;
		}
		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }
		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/


		break;

	case 10:
		if (backHeight[0]->lineFlag == 0) { backHeight[0] = StagePointer::SetLinePoint(6,0); }
		if (backHeight[1]->lineFlag == 0) { backHeight[1] = StagePointer::SetLinePoint(7,0); }
		if (backHeight[2]->lineFlag == 0) { backHeight[2] = StagePointer::SetLinePoint(8,0); }
		break;
	case 11:

		if (backHeight[setHeightRand]->lineFlag == 0) { backHeight[setHeightRand] = StagePointer::SetLinePoint(11,0); }
		break;
		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }

		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }*/
		break;
	case 12:
		if (setHeightRand == 0)
		{
			if (backHeight[0]->lineFlag == 0 && backHeight[1]->lineFlag == 0) { backHeight[0] = StagePointer::SetLinePoint(11,0);  backHeight[1] = StagePointer::SetLinePoint(11,0); }
			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
			break;
		}
		else if (setHeightRand == 1)
		{
			if (backHeight[1]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[1] = StagePointer::SetLinePoint(11,0); backHeight[2] = StagePointer::SetLinePoint(11,0); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		else
		{
			if (backHeight[0]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[0] = StagePointer::SetLinePoint(11,0);  backHeight[2] = StagePointer::SetLinePoint(11,0); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		break;
	case 13:
		/*if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }

		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/
		if (backHeight[0]->lineFlag == 0) { backHeight[0] = StagePointer::SetLinePoint(11,0); }
		if (backHeight[1]->lineFlag == 0) { backHeight[1] = StagePointer::SetLinePoint(11,0); }
		if (backHeight[2]->lineFlag == 0) { backHeight[2] = StagePointer::SetLinePoint(11,0); }
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
					stageParts[i][j]->Manifest = 1;


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
					stageParts[i][j]->Manifest = 1;

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
		//�E
	case 0:

		if (rightSide[setSideRand]->lineFlag == 0) { rightSide[setSideRand] = StagePointer::SetLinePoint(setSideRand, 1)/*SetHeightLinePoint(setHeightRand)*/; }
		break;
	case 1:
		if (setSideRand == 0)
		{
			if (rightSide[0]->lineFlag == 0 && rightSide[1]->lineFlag == 0) { rightSide[0] = StagePointer::SetLinePoint(0, 1); rightSide[1] = StagePointer::SetLinePoint(1, 1); }
			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
			break;
		}
		else if (setSideRand == 1)
		{
			if (rightSide[1]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[1] = StagePointer::SetLinePoint(1, 1); rightSide[2] = StagePointer::SetLinePoint(2, 1); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		else
		{
			if (rightSide[0]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[0] = StagePointer::SetLinePoint(0, 1); rightSide[2] = StagePointer::SetLinePoint(2, 1); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		//if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
		break;
	case 2:

		if (setSideRand == 0)
		{
			if (rightSide[0]->lineFlag == 0) { rightSide[0] = StagePointer::SetLinePoint(3, 1); }
			break;
		}
		else if (setSideRand == 1)
		{
			if (rightSide[2]->lineFlag == 0) { rightSide[2] = StagePointer::SetLinePoint(4, 1); }
			break;
		}
		else
		{
			if (rightSide[0]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[0] = StagePointer::SetLinePoint(3, 1);  rightSide[2] = StagePointer::SetLinePoint(4, 1); }
			break;
		}
		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }
		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/


		break;
	case 3:

		if (rightSide[0]->lineFlag == 0) { rightSide[0] = StagePointer::SetLinePoint(0, 1); }
		if (rightSide[1]->lineFlag == 0) { rightSide[1] = StagePointer::SetLinePoint(1, 1); }
		if (rightSide[2]->lineFlag == 0) { rightSide[2] = StagePointer::SetLinePoint(2, 1); }

		break;

	case 4:

		if (rightSide[setSideRand]->lineFlag == 0) { rightSide[setSideRand] = StagePointer::SetLinePoint(5, 1); }
		break;
		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }

		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }*/
		break;
	case 5:
		if (setSideRand == 0)
		{
			if (rightSide[0]->lineFlag == 0 && rightSide[1]->lineFlag == 0) { rightSide[0] = StagePointer::SetLinePoint(5, 1); rightSide[1] = StagePointer::SetLinePoint(5, 1); }
			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
			break;
		}
		else if (setSideRand == 1)
		{
			if (rightSide[1]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[1] = StagePointer::SetLinePoint(5, 1); rightSide[2] = StagePointer::SetLinePoint(5, 1); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		else
		{
			if (rightSide[0]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[0] = StagePointer::SetLinePoint(5, 1); rightSide[2] = StagePointer::SetLinePoint(5, 1); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		break;
	case 6:
		/*if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }

		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/
		if (rightSide[0]->lineFlag == 0) { rightSide[0] = StagePointer::SetLinePoint(5, 1); }
		if (rightSide[1]->lineFlag == 0) { rightSide[1] = StagePointer::SetLinePoint(5, 1); }
		if (rightSide[2]->lineFlag == 0) { rightSide[2] = StagePointer::SetLinePoint(5, 1); }
		break;

		//��
	case 7:

		if (leftSide[setSideRand]->lineFlag == 0) { leftSide[setSideRand] = StagePointer::SetLinePoint(setSideRand + 6, 1); }
		break;
	case 8:
		if (setSideRand == 0)
		{
			if (leftSide[0]->lineFlag == 0 && leftSide[1]->lineFlag == 0) { leftSide[0] = StagePointer::SetLinePoint(6, 1); leftSide[1] = StagePointer::SetLinePoint(7, 1); }
			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
			break;
		}
		else if (setSideRand == 1)
		{
			if (leftSide[1]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[1] = StagePointer::SetLinePoint(7, 1); leftSide[2] = StagePointer::SetLinePoint(8, 1); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		else
		{
			if (leftSide[0]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[0] = StagePointer::SetLinePoint(6, 1); leftSide[2] = StagePointer::SetLinePoint(8, 1); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		//if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
		break;
	case 9:

		if (setSideRand == 0)
		{
			if (leftSide[0]->lineFlag == 0) { leftSide[0] = StagePointer::SetLinePoint(9, 1); }
			break;
		}
		else if (setSideRand == 1)
		{
			if (leftSide[2]->lineFlag == 0) { leftSide[2] = StagePointer::SetLinePoint(10, 1); }
			break;
		}
		else
		{
			if (leftSide[0]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[0] = StagePointer::SetLinePoint(9, 1);  leftSide[2] = StagePointer::SetLinePoint(10, 1); }
			break;
		}
		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }
		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/


		break;

	case 10:
		if (leftSide[0]->lineFlag == 0) { leftSide[0] = StagePointer::SetLinePoint(6, 1); }
		if (leftSide[1]->lineFlag == 0) { leftSide[1] = StagePointer::SetLinePoint(7, 1); }
		if (leftSide[2]->lineFlag == 0) { leftSide[2] = StagePointer::SetLinePoint(8, 1); }
		break;
	case 11:

		if (leftSide[setSideRand]->lineFlag == 0) { leftSide[setSideRand] = StagePointer::SetLinePoint(11, 1); }
		break;
		/*if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0); }

		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }*/
		break;
	case 12:
		if (setSideRand == 0)
		{
			if (leftSide[0]->lineFlag == 0 && leftSide[1]->lineFlag == 0) { leftSide[0] = StagePointer::SetLinePoint(11, 1); leftSide[1] = StagePointer::SetLinePoint(11, 1); }
			//if (frontHeight[1]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }
			break;
		}
		else if (setSideRand == 1)
		{
			if (leftSide[1]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[1] = StagePointer::SetLinePoint(11, 1); leftSide[2] = StagePointer::SetLinePoint(11, 1); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		else
		{
			if (leftSide[0]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[0] = StagePointer::SetLinePoint(11, 1); leftSide[2] = StagePointer::SetLinePoint(11, 1); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		break;
	case 13:
		/*if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1); }

		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }*/
		if (leftSide[0]->lineFlag == 0) { leftSide[0] = StagePointer::SetLinePoint(11, 1); }
		if (leftSide[1]->lineFlag == 0) { leftSide[1] = StagePointer::SetLinePoint(11, 1); }
		if (leftSide[2]->lineFlag == 0) { leftSide[2] = StagePointer::SetLinePoint(11, 1); }
		break;

	default:
		break;
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
				if (stageParts[i][j]->playerRockOnFlag == 0 && stageParts[i][j]->Manifest==0&&
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
						playerRockFlag = 0;
					}
				}
			}
		}

	}

}


