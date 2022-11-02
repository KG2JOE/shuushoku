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
			XMFLOAT3 pos = { -150 + (float)(i * 7.51),-145,-450.0f };
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

		height[i] = new Line();
		


	}

	/*atkOmen[0]->model = Model::LoadFromOBJ("core_in");
	atkOmen[1]->model = Model::LoadFromOBJ("ground");
	atkOmen[2]->model = Model::LoadFromOBJ("back");
	atkOmen[3]->model = Model::LoadFromOBJ("territory");
	atkOmen[4]->model = Model::LoadFromOBJ("atkHad");*/
	for (UINT i = 0; i < 4; i++)
	{

		atkOmen[i] = new AtkOmen();
		atkOmen[i]->model = Model::LoadFromOBJ(name[i]);
		
		atkOmen[i]->OBJ = Object3d::Create();
		atkOmen[i]->OBJ->SetModel(atkOmen[i]->model);


	}


	atkOmen[0]->OBJ->SetPosition({ 0,14,30 });
	/*CoaRotA.y += 0.3f;
	OBJInCoa->SetRotation(CoaRotA);*/
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
		UINT a = rand() % 217 - 148;
		posRand[i] = a;

		if (height[i]->lineFlag >= 1)
		{
			HeightLineATK(i);
		}
	}

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
					stageParts[i][j]->OBJWorld->SetModel(modelWorld1);
					stageParts[i][j]->OBJWorldFlag = 0;

				}
			}
			if (impactFlag == 0 && (stageParts[i][j]->worldjamp >= 10.0f))
			{
				stageParts[i][j]->OBJWorld->SetModel(modelWorld1);

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
	delete modelWorld1, modelWorld2, modelAtkHud;

	
	for (int i = 0; i < 4; i++)
	{
		delete atkOmen[i]->model;
		delete atkOmen[i]->OBJ;
		delete atkOmen[i];
	}
}

void StageWorld::WaveATK()
{

	impactRad += 1.0f;
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

void StageWorld::HeightLineATK(UINT point)
{

	if (height[point]->lineFlag == 1)
	{
		height[point]->oldPos = height[point]->linePos;

		height[point]->lineFlag = 2;
		
	}
	if (height[point]->lineFlag == 2)
	{
		height[point]->lineAccele += 0.2f;

		height[point]->linePos.x -= sin((height[point]->lineAngle * DirectX::XM_PI) / 180) * height[point]->lineAccele;
		height[point]->linePos.z -= cos((height[point]->lineAngle * DirectX::XM_PI) / 180) * height[point]->lineAccele;
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				
				bool isHit = Collision::HitCircle(stageParts[i][j]->OBJWorldPos, 5, height[point]->linePos, 5, 1);
				if (isHit)
				{
					stageParts[i][j]->OBJWorld->SetModel(modelWorld2);
				}
			}
		}
		if (height[point]->linePos.z < -550)
		{
			height[point]->lineAccele = 0.0f;
			height[point]->linePos = height[point]->oldPos;
			height[point]->lineFlag = 3;
		}
	}
	if (height[point]->lineFlag == 3)
	{
		height[point]->lineAccele += 0.2f;

		height[point]->linePos.x -= sin((height[point]->lineAngle * DirectX::XM_PI) / 180) * height[point]->lineAccele;
		height[point]->linePos.z -= cos((height[point]->lineAngle * DirectX::XM_PI) / 180) * height[point]->lineAccele;
		if (height[point]->linePos.z < -455)
		{

			height[point]->lineFlag = 0;
		}
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				if (stageParts[i][j]->OBJWorldFlag == 0)
				{
					stageParts[i][j]->OBJWorldFlag = Collision::HitCircle(stageParts[i][j]->OBJWorldPos, 5, height[point]->linePos, 5, 1);


				}
			}
		}
	}

}

void StageWorld::SetHeightLineCase(char pattern)
{
	switch (pattern)
	{
	case 0:
		if (height[0]->lineFlag == 0) { height[0] = SetLinePoint(0); }
		break;
	case 1:
		if (height[1]->lineFlag == 0) { height[1] = SetLinePoint(1); }
		break;
	case 2:
		if (height[2]->lineFlag == 0) { height[2] = SetLinePoint(2); }
		break;
	case 3:
		if (height[0]->lineFlag == 0) { height[0] = SetLinePoint(0); }

		if (height[1]->lineFlag == 0) { height[1] = SetLinePoint(1); }
		break;
	case 4:
		if (height[0]->lineFlag == 0) { height[0] = SetLinePoint(0); }

		if (height[2]->lineFlag == 0) { height[2] = SetLinePoint(2); }
		break;
	case 5:
		if (height[1]->lineFlag == 0) { height[1] = SetLinePoint(1); }

		if (height[2]->lineFlag == 0) { height[2] = SetLinePoint(2); }
		break;
	case 6:
		if (height[0]->lineFlag == 0) { height[0] = SetLinePoint(0); }

		if (height[1]->lineFlag == 0) { height[1] = SetLinePoint(1); }

		if (height[2]->lineFlag == 0) { height[2] = SetLinePoint(2); }
		break;
	case 7:
		if (height[0]->lineFlag == 0) { height[0] = SetLinePoint(3); }

		break;
	case 8:
		if (height[2]->lineFlag == 0) { height[2] = SetLinePoint(4); }

		break;
	case 9:
		if (height[0]->lineFlag == 0) { height[0] = SetLinePoint(3); }
		if (height[2]->lineFlag == 0) { height[2] = SetLinePoint(4); }

		break;
	case 10:
		if (height[0]->lineFlag == 0) { height[0] = SetLinePoint(5); }

		break;
	case 11:
		if (height[0]->lineFlag == 0) { height[0] = SetLinePoint(5); }
		if (height[1]->lineFlag == 0) { height[1] = SetLinePoint(6); }

	case 12:
		if (height[0]->lineFlag == 0) { height[0] = SetLinePoint(5); }
		if (height[1]->lineFlag == 0) { height[1] = SetLinePoint(6); }
		if (height[2]->lineFlag == 0) { height[2] = SetLinePoint(7); }

		break;
	case 13:
		ALLSetImpact({ 35,0,-242 }, 1, 1);
		break;
	case 14:

		break;
	case 15:

		break;
	case 16:

		break;
	case 17:

		break;
	case 18:

		break;
	case 19:
	default:
		break;
	}

}

StageWorld::Line* StageWorld::SetLinePoint(char point)
{
	Line* temp = new Line();

	
	temp->lineAngle = 0;
	temp->lineFlag = 1;

	switch (point)
	{
	case 0:
	{
		temp->linePos = { -148,0,-30 };
		break;
	}
	case 1:
	{
		temp->linePos = { 35,0,-30 };
		break;
	}
	case 2:
	{
		temp->linePos = { 217,0,-30 };
		break;
	}
	case 3:
	{
		temp->linePos = { -148,0,-30 };
		temp->lineAngle = -41;

		break;
	}
	case 4:
	{
		temp->linePos = { 217,0,-30 };
		temp->lineAngle = 41;

		break;
	}
	case 5:
	{
		temp->linePos = { (float)posRand[0],0,-30 };
		//temp->lineAngle = 41;
		break;
	}
	case 6:
	{
		temp->linePos = { (float)posRand[1],0,-30 };
		//temp->lineAngle = 41;
		break;
	}
	case 7:
	{
		temp->linePos = { (float)posRand[2],0,-30 };
		//temp->lineAngle = 41;
		break;
	}
	default:
		break;
	}
	return temp;
}


