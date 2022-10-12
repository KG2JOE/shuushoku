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
}

void StageWorld::Update()
{
	/*if (input_->TriggerMouseLeft() && impactFlag == 0)
	{
		WaveATK();
	}*/
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			OBJWorld[i][j]->Update();

		}

	}
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

				}
			}
			if (impactFlag == 0 && (worldjamp[i][j] == 30.0f))
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

void StageWorld::WaveATK(XMFLOAT3 pos)
{
	impactPos = pos;
	if (impactFlag == 1)
	{
		impactRad += 1.0f;
		if (impactRad > 200)
		{
			impactFlag = 0;
		}
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{

				OBJWorldFlag[i][j] = Collision::HitCircle(OBJWorldPos[i][j], 5, impactPos, impactRad);

			}
		}

	}
}
