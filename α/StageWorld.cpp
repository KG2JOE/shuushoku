#include "StageWorld.h"


void StageWorld::Initialize(Input* input)
{
	assert(input);
	this->input_ = input;
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			OBJWorld[i][j] = Object3d::Create();
			OBJWorld[i][j]->SetModel(modelWorld1);
			OBJWorld[i][j]->SetScale({ 5,15,5 });
			XMFLOAT3 pos = { -150 + (float)(i * 7.51),-145,-450.0f };
			if (i % 2 == 0)
			{
				pos.z += ((float)j * 8.6f);
				//OBJWorld[i][j]->SetPosition({ -300 + (float)(i * 7.5),-140,00.0f + ((float)j * 8.50f) });

			}
			else
			{
				pos.z += ((float)j * 8.6f) - 4.35f;
				//OBJWorld[i][j]->SetPosition({ -300 + (float)(i * 7.5),-140,00.0f + ((float)j * 8.50f)-4.5f});

			}
			OBJWorldPos[i][j] = pos;
			oldOBJWorldPos[i][j] = OBJWorldPos[i][j];
			worldjamp[i][j] = 5.0f;
			OBJWorld[i][j]->SetPosition(pos);
		}

	}
	for (UINT i = 0; i < 3; i++)
	{
		height[i] = new Line();
	}

}

void StageWorld::Update()
{
	/*if (input_->TriggerMouseLeft() && impactFlag == 0)
	{
		WaveATK();
	}*/
	if (impactFlag == 1)
	{
		WaveATK();
	}
	for (UINT i = 0; i < 3; i++)
	{
		UINT a = rand() % 217 - 148;
		posRand[i] = a;

		if (height[i]->lineFlag == 1)
		{
			HeightLineATK(i);
		}
	}

	StageUpdate();
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			OBJWorld[i][j]->Update();

		}

	}

}

void StageWorld::StageUpdate()
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (OBJWorldFlag[i][j] == 1 && worldjamp[i][j] <= 5.0f)
			{
				OBJWorld[i][j]->SetModel(modelWorld2);

				OBJWorldPos[i][j].y += worldjamp[i][j];
				worldjamp[i][j] -= 0.5f;
				OBJWorld[i][j]->SetPosition(OBJWorldPos[i][j]);
				if (worldjamp[i][j] < -5.0f)
				{
					worldjamp[i][j] = 30.0f;
					OBJWorld[i][j]->SetModel(modelWorld1);
					OBJWorldFlag[i][j] = 0;

				}
			}
			if (impactFlag == 0 && (worldjamp[i][j] >= 10.0f))
			{
				worldjamp[i][j] = 5.0f;
				OBJWorldFlag[i][j] = 0;
				OBJWorld[i][j]->SetPosition(oldOBJWorldPos[i][j]);

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
			OBJWorld[i][j]->Draw();

		}
	}
}

void StageWorld::Delete()
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			delete OBJWorld[i][j];
		}
	}
	delete modelWorld1, modelWorld2;
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
			if (OBJWorldFlag[i][j] == 0)
			{
				OBJWorldFlag[i][j] = Collision::HitCircle(OBJWorldPos[i][j], 5, impactPos, impactRad, 0);
				worldjamp[i][j] = 5.0f;

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

	/*coraRe.y -= sin(((playerRot.y + 90) * PI) / 180) * (1.0f / 3.90625f);
	coraRe.x -= cos(((playerRot.y + 90) * PI) / 180) * (1.0f / 3.90625f);*/
	if (height[point]->lineFlag == 1)
	{
		height[point]->lineAccele += 0.45f;
		/*height[point]->linePos.x -= height[point]->lineAccele;
		height[point]->linePos.z -= height[point]->lineAccele;*/
		height[point]->linePos.x -= sin((height[point]->lineAngle * PI) / 180) * height[point]->lineAccele;
		height[point]->linePos.z -= cos((height[point]->lineAngle * PI) / 180) * height[point]->lineAccele;
		if (height[point]->linePos.z < -455)
		{
			//impactFlag = 0;
			height[point]->lineFlag = 0;
		}
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				if (OBJWorldFlag[i][j] == 0)
				{
					OBJWorldFlag[i][j] = Collision::HitCircle(OBJWorldPos[i][j], 5, height[point]->linePos, 5, 1);
					//worldjamp[i][j] = 5.0f;

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


