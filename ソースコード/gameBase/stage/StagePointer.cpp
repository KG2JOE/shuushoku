#include "StagePointer.h"

StagePointer::Line* StagePointer::SetLinePoint(char point, bool flag)
{
	Line* sideTemp = new Line();
	Line* heightTemp = new Line();

	sideTemp->lineAngle = 0;
	sideTemp->lineFlag = 1;

	heightTemp->lineAngle = 0;
	heightTemp->lineFlag = 1;


	switch (point)
	{
		//右または前
	case 0:
	{
		sideTemp->linePos = { 217 - 33.795f,0,-455 };
		heightTemp->linePos = { -148 - 33.795f,0,-30 };
		break;
	}
	case 1:
	{
		sideTemp->linePos = { 217 - 33.795f,0,-212 };
		heightTemp->linePos = { 35 - 33.795f,0,-30 };
		break;
	}
	case 2:
	{
		sideTemp->linePos = { 217 - 33.795f,0,-30 };
		heightTemp->linePos = { 217 - 33.795f,0,-30 };

		break;
	}
	case 3:
	{
		sideTemp->linePos = { 217 - 33.795f,0,-455 };
		sideTemp->lineAngle = 65+90;

		heightTemp->linePos = { -148 - 33.795f,0,-30 };
		heightTemp->lineAngle = -38 - 90;

		break;
	}
	case 4:
	{
		sideTemp->linePos = { 217 - 33.795f,0,-30 };
		sideTemp->lineAngle = -65-90;

		heightTemp->linePos = { 217 - 33.795f,0,-30 };
		heightTemp->lineAngle = 38+90;

		break;
	}
	case 5:
	{
		sideTemp->linePos = { 217 - 33.795f,0,(float)RndCreate::sGetRandInt(-455, -30) };
		heightTemp->linePos = { (float)RndCreate::sGetRandInt(-181,179),0,-30 };

		break;
	}

	//左または後ろ
	case 6:
	{
		sideTemp->linePos = { -150 - 33.795f,0,-453 };
		heightTemp->linePos = { -148 - 33.795f,0,-455 };

		break;
	}
	case 7:
	{
		sideTemp->linePos = { -150 - 33.795f,0,-212 };
		heightTemp->linePos = { 35 - 33.795f,0,-455 };

		break;
	}
	case 8:
	{
		sideTemp->linePos = { -150 - 33.795f,0,-30 };
		heightTemp->linePos = { 217 - 33.795f,0,-455 };

		break;
	}
	case 9:
	{
		sideTemp->linePos = { -150 - 33.795f,0,-30 };
		sideTemp->lineAngle = 65+90;

		heightTemp->linePos = { 217 - 33.795f,0,-455 };
		heightTemp->lineAngle = -38 - 90;

		break;
	}
	case 10:
	{
		sideTemp->linePos = { -150 - 33.795f,0,-453 };
		sideTemp->lineAngle = -65-90;

		heightTemp->linePos = { -148 - 33.795f,0,-455 };
		heightTemp->lineAngle = 38 + 90;

		break;
	}
	case 11:
	{
		sideTemp->linePos = { -150 - 33.795f,0,(float)RndCreate::sGetRandInt(-455, -30) };
		heightTemp->linePos = { (float)RndCreate::sGetRandInt(-181,179),0,-455 };

		break;
	}

	default:
		break;
	}

	if (flag)
	{
		return sideTemp;
	}
	else
	{
		return heightTemp;
	}
}

void StagePointer::LineUpdate(int i)
{
	for (int j = 0; j < 50; j++)
	{
		for (int k = 0; k < 50; k++)
		{
			if (frontHeight[i]->lineFlag >= 1)
			{
				stageParts[j][k] = LineAtkFlag(frontHeight[i], stageParts[j][k], modelWorld2, FLONT);
			}
			if (backHeight[i]->lineFlag >= 1)
			{
				stageParts[j][k] = LineAtkFlag(backHeight[i], stageParts[j][k], modelWorld2, BACK);
			}
			if (rightSide[i]->lineFlag >= 1)
			{
				stageParts[j][k] = LineAtkFlag(rightSide[i], stageParts[j][k], modelWorld2, RIGHT);
			}
			if (leftSide[i]->lineFlag >= 1)
			{
				stageParts[j][k] = LineAtkFlag(leftSide[i], stageParts[j][k], modelWorld2, LEFT);
			}
		}
	}
}

StagePointer::Line* StagePointer::LineAtk(Line* line, int flag)
{
	float angle = 0.0f;
	//0or2のときは横、1or3は縦
	if (flag % 2 == 0)
	{
		angle = 90.0f;

	}
	Line* line_ = new Line();
	line_ = line;
	if (line_->lineFlag == 1)
	{
		line_->oldPos = line_->linePos;

		line_->lineFlag = 2;

	}

	
	if (line_->lineFlag == 2)
	{
		/*line_->lineAccele += 0.2f;
		if (flag <= 1)
		{
			line_->linePos.x -= sin((line_->lineAngle + angle * DirectX::XM_PI) / 180) * line_->lineAccele;
			line_->linePos.z -= cos((line_->lineAngle + angle * DirectX::XM_PI) / 180) * line_->lineAccele;
		}
		else
		{
			line_->linePos.x += sin((line_->lineAngle + angle * DirectX::XM_PI) / 180) * line_->lineAccele;
			line_->linePos.z += cos((line_->lineAngle + angle * DirectX::XM_PI) / 180) * line_->lineAccele;
		}*/

		line_ = LineAtkCollision(line_,flag,angle);
		
		switch (flag)
		{

		case 0:
			//右
			if (line_->linePos.x < -183.795f)
			{
				line_->lineAccele = 0.0f;
				line_->linePos = line_->oldPos;
				line_->lineFlag = 3;
			}
			break;
		case 1:
			//前
			if (line_->linePos.z < -455)
			{
				line_->lineAccele = 0.0f;
				line_->linePos = line_->oldPos;
				line_->lineFlag = 3;
			}
			break;
		case 2:
			//左
			if (line_->linePos.x > 185.205f)
			{
				line_->lineAccele = 0.0f;
				line_->linePos = line_->oldPos;
				line_->lineFlag = 3;
			}
			break;
		case 3:
			//後ろ
			if (line_->linePos.z > -20)
			{
				line_->lineAccele = 0.0f;
				line_->linePos = line_->oldPos;
				line_->lineFlag = 3;
			}
			break;

		default:
			break;
		}
		
	}
	if (line_->lineFlag == 3)
	{
		/*	line_->lineAccele += 0.2f;

			if (flag <= 1)
			{
				line_->linePos.x -= sin((line_->lineAngle + angle * DirectX::XM_PI) / 180) * line_->lineAccele;
				line_->linePos.z -= cos((line_->lineAngle + angle * DirectX::XM_PI) / 180) * line_->lineAccele;
			}
			else
			{
				line_->linePos.x += sin((frontHeight[point]->lineAngle + angle * DirectX::XM_PI) / 180) * line_->lineAccele;
				line_->linePos.z += cos((frontHeight[point]->lineAngle + angle * DirectX::XM_PI) / 180) * line_->lineAccele;
			}*/

		line_ = LineAtkCollision(line_, flag, angle);

		switch (flag)
		{

		case 0:
			//右
			if (line_->linePos.x < -183.795f)
			{
				line_->lineFlag = 0;
			}
			break;
		case 1:
			//前
			if (line_->linePos.z < -455)
			{
				line_->lineFlag = 0;
			}
			break;
		case 2:
			//左
			if (line_->linePos.x > 185.205f)
			{
				line_->lineFlag = 0;
			}
			break;
		case 3:
			//後ろ
			if (line_->linePos.z > -20)
			{
				line_->lineFlag = 0;
			}
			break;

		default:
			break;
		}

	}
	
	return line_;
}

StagePointer::StageParts* StagePointer::LineAtkFlag(Line* line, StageParts* stageParts, Model* model, int flag)
{
	StageParts* stageParts_ = new StageParts();
	stageParts_ = stageParts;

	if (line->lineFlag == 2)
	{
		bool isHit = Collision::HitCircle(stageParts_->OBJWorldPos, 5, line->linePos, 5, 1);
		if (isHit)
		{
			stageParts_->OBJWorld->SetModel(model);
			stageParts_->Manifest = 1;
			switch (flag)
			{

			case 0://右
				stageParts_->right = 1;
				break;
			case 1://前
				stageParts_->flont = 1;
				break;
			case 2://左
				stageParts_->left = 1;
				break;
			case 3://後ろ
				stageParts_->back = 1;
				break;

			default:
				break;
			}
		}
	}
	
	if (line->lineFlag == 3)
	{
		bool isHit = Collision::HitCircle(stageParts_->OBJWorldPos, 5, line->linePos, 5, 1);
		if (isHit)
		{
			stageParts_->OBJWorldFlag = isHit;

			switch (flag)
			{

			case 0://右
				stageParts_->right = 0;
				break;
			case 1://前
				stageParts_->flont = 0;
				break;
			case 2://左
				stageParts_->left = 0;
				break;
			case 3://後ろ
				stageParts_->back = 0;
				break;

			default:
				break;
			}
		}
	}
	return stageParts_;
}
