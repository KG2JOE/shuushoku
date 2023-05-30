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
		sideTemp->lineAngle = 65 + 90;

		heightTemp->linePos = { -148 - 33.795f,0,-30 };
		heightTemp->lineAngle = -38 - 90;

		break;
	}
	case 4:
	{
		sideTemp->linePos = { 217 - 33.795f,0,-30 };
		sideTemp->lineAngle = -65 - 90;

		heightTemp->linePos = { 217 - 33.795f,0,-30 };
		heightTemp->lineAngle = 38 + 90;

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
		sideTemp->lineAngle = 65 + 90;

		heightTemp->linePos = { 217 - 33.795f,0,-455 };
		heightTemp->lineAngle = -38 - 90;

		break;
	}
	case 10:
	{
		sideTemp->linePos = { -150 - 33.795f,0,-453 };
		sideTemp->lineAngle = -65 - 90;

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

void StagePointer::SetHeightLineCase(char pattern)
{
	int point = setRand->getRandInt(0, 2);

	switch (pattern)
	{
		//前
	case 0:

		if (frontHeight[point]->lineFlag == 0) { frontHeight[point] = SetLinePoint(point, 0)/*SetHeightLinePoint(point)*/; }
		break;
	case 1:
		if (point == 0)
		{
			if (frontHeight[0]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0, 0); frontHeight[1] = SetLinePoint(1, 0); }
			break;
		}
		else if (point == 1)
		{
			if (frontHeight[1]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1, 0); frontHeight[2] = SetLinePoint(2, 0); }
			break;
		}
		else
		{
			if (frontHeight[0]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0, 0); frontHeight[2] = SetLinePoint(2, 0); }
			break;
		}
		break;
	case 2:

		if (point == 0)
		{
			if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(3, 0); }
			break;
		}
		else if (point == 1)
		{
			if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(4, 0); }
			break;
		}
		else
		{
			if (frontHeight[0]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[0] = SetLinePoint(3, 0);  frontHeight[2] = SetLinePoint(4, 0); }
			break;
		}

		break;
	case 3:

		if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(0, 0); }
		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(1, 0); }
		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2, 0); }

		break;

	case 4:

		if (frontHeight[point]->lineFlag == 0) { frontHeight[point] = SetLinePoint(5, 0); }
		break;

	case 5:
		if (point == 0)
		{
			if (frontHeight[0]->lineFlag == 0 && frontHeight[1]->lineFlag == 0) { frontHeight[0] = SetLinePoint(5, 0);  frontHeight[1] = SetLinePoint(5, 0); }
			break;
		}
		else if (point == 1)
		{
			if (frontHeight[1]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[1] = SetLinePoint(5, 0); frontHeight[2] = SetLinePoint(5, 0); }
			break;
		}
		else
		{
			if (frontHeight[0]->lineFlag == 0 && frontHeight[2]->lineFlag == 0) { frontHeight[0] = SetLinePoint(5, 0);  frontHeight[2] = SetLinePoint(5, 0); }
			break;
		}
		break;
	case 6:
		if (frontHeight[0]->lineFlag == 0) { frontHeight[0] = SetLinePoint(5, 0); }
		if (frontHeight[1]->lineFlag == 0) { frontHeight[1] = SetLinePoint(5, 0); }
		if (frontHeight[2]->lineFlag == 0) { frontHeight[2] = SetLinePoint(5, 0); }
		break;

		//後ろ
	case 7:

		if (backHeight[point]->lineFlag == 0) { backHeight[point] = SetLinePoint(point + 6, 0); }
		break;
	case 8:
		if (point == 0)
		{
			if (backHeight[0]->lineFlag == 0 && backHeight[1]->lineFlag == 0) { backHeight[0] = SetLinePoint(6, 0);  backHeight[1] = SetLinePoint(7, 0); }
			break;
		}
		else if (point == 1)
		{
			if (backHeight[1]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[1] = SetLinePoint(7, 0); backHeight[2] = SetLinePoint(8, 0); }
			break;
		}
		else
		{
			if (backHeight[0]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[0] = SetLinePoint(6, 0);  backHeight[2] = SetLinePoint(8, 0); }
			break;
		}
		break;
	case 9:

		if (point == 0)
		{
			if (backHeight[0]->lineFlag == 0) { backHeight[0] = SetLinePoint(9, 0); }
			break;
		}
		else if (point == 1)
		{
			if (backHeight[2]->lineFlag == 0) { backHeight[2] = SetLinePoint(10, 0); }
			break;
		}
		else
		{
			if (backHeight[0]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[0] = SetLinePoint(9, 0);  backHeight[2] = SetLinePoint(10, 0); }
			break;
		}

		break;

	case 10:
		if (backHeight[0]->lineFlag == 0) { backHeight[0] = SetLinePoint(6, 0); }
		if (backHeight[1]->lineFlag == 0) { backHeight[1] = SetLinePoint(7, 0); }
		if (backHeight[2]->lineFlag == 0) { backHeight[2] = SetLinePoint(8, 0); }
		break;
	case 11:

		if (backHeight[point]->lineFlag == 0) { backHeight[point] = SetLinePoint(11, 0); }
		break;

	case 12:
		if (point == 0)
		{
			if (backHeight[0]->lineFlag == 0 && backHeight[1]->lineFlag == 0) { backHeight[0] = SetLinePoint(11, 0);  backHeight[1] = SetLinePoint(11, 0); }
			break;
		}
		else if (point == 1)
		{
			if (backHeight[1]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[1] = SetLinePoint(11, 0); backHeight[2] = SetLinePoint(11, 0); }
			break;
		}
		else
		{
			if (backHeight[0]->lineFlag == 0 && backHeight[2]->lineFlag == 0) { backHeight[0] = SetLinePoint(11, 0);  backHeight[2] = SetLinePoint(11, 0); }
			break;
		}
		break;
	case 13:
		if (backHeight[0]->lineFlag == 0) { backHeight[0] = SetLinePoint(11, 0); }
		if (backHeight[1]->lineFlag == 0) { backHeight[1] = SetLinePoint(11, 0); }
		if (backHeight[2]->lineFlag == 0) { backHeight[2] = SetLinePoint(11, 0); }
		break;

	default:
		break;
	}

}

void StagePointer::SetWidthLineCase(char pattern)
{
	int point = setRand->getRandInt(0, 2);
	switch (pattern)
	{
		//右
	case 0:

		if (rightSide[point]->lineFlag == 0) { rightSide[point] = SetLinePoint(point, 1); }
		break;
	case 1:
		if (point == 0)
		{
			if (rightSide[0]->lineFlag == 0 && rightSide[1]->lineFlag == 0) { rightSide[0] = SetLinePoint(0, 1); rightSide[1] = SetLinePoint(1, 1); }
			break;
		}
		else if (point == 1)
		{
			if (rightSide[1]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[1] = SetLinePoint(1, 1); rightSide[2] = SetLinePoint(2, 1); }
			break;
		}
		else
		{
			if (rightSide[0]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[0] = SetLinePoint(0, 1); rightSide[2] = SetLinePoint(2, 1); }
			break;
		}
		break;
	case 2:

		if (point == 0)
		{
			if (rightSide[0]->lineFlag == 0) { rightSide[0] = SetLinePoint(3, 1); }
			break;
		}
		else if (point == 1)
		{
			if (rightSide[2]->lineFlag == 0) { rightSide[2] = SetLinePoint(4, 1); }
			break;
		}
		else
		{
			if (rightSide[0]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[0] = SetLinePoint(3, 1);  rightSide[2] = SetLinePoint(4, 1); }
			break;
		}

		break;
	case 3:

		if (rightSide[0]->lineFlag == 0) { rightSide[0] = SetLinePoint(0, 1); }
		if (rightSide[1]->lineFlag == 0) { rightSide[1] = SetLinePoint(1, 1); }
		if (rightSide[2]->lineFlag == 0) { rightSide[2] = SetLinePoint(2, 1); }

		break;

	case 4:

		if (rightSide[point]->lineFlag == 0) { rightSide[point] = SetLinePoint(5, 1); }
		break;
	case 5:
		if (point == 0)
		{
			if (rightSide[0]->lineFlag == 0 && rightSide[1]->lineFlag == 0) { rightSide[0] = SetLinePoint(5, 1); rightSide[1] = SetLinePoint(5, 1); }
			break;
		}
		else if (point == 1)
		{
			if (rightSide[1]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[1] = SetLinePoint(5, 1); rightSide[2] = SetLinePoint(5, 1); }
			break;
		}
		else
		{
			if (rightSide[0]->lineFlag == 0 && rightSide[2]->lineFlag == 0) { rightSide[0] = SetLinePoint(5, 1); rightSide[2] = SetLinePoint(5, 1); }
			break;
		}
		break;
	case 6:
		if (rightSide[0]->lineFlag == 0) { rightSide[0] = SetLinePoint(5, 1); }
		if (rightSide[1]->lineFlag == 0) { rightSide[1] = SetLinePoint(5, 1); }
		if (rightSide[2]->lineFlag == 0) { rightSide[2] = SetLinePoint(5, 1); }
		break;

		//左
	case 7:

		if (leftSide[point]->lineFlag == 0) { leftSide[point] = SetLinePoint(point + 6, 1); }
		break;
	case 8:
		if (point == 0)
		{
			if (leftSide[0]->lineFlag == 0 && leftSide[1]->lineFlag == 0) { leftSide[0] = SetLinePoint(6, 1); leftSide[1] = SetLinePoint(7, 1); }
			break;
		}
		else if (point == 1)
		{
			if (leftSide[1]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[1] = SetLinePoint(7, 1); leftSide[2] = SetLinePoint(8, 1); }
			break;
		}
		else
		{
			if (leftSide[0]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[0] = SetLinePoint(6, 1); leftSide[2] = SetLinePoint(8, 1); }
			break;
		}
		break;
	case 9:

		if (point == 0)
		{
			if (leftSide[0]->lineFlag == 0) { leftSide[0] = SetLinePoint(9, 1); }
			break;
		}
		else if (point == 1)
		{
			if (leftSide[2]->lineFlag == 0) { leftSide[2] = SetLinePoint(10, 1); }
			break;
		}
		else
		{
			if (leftSide[0]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[0] = SetLinePoint(9, 1);  leftSide[2] = SetLinePoint(10, 1); }
			break;
		}

		break;

	case 10:
		if (leftSide[0]->lineFlag == 0) { leftSide[0] = SetLinePoint(6, 1); }
		if (leftSide[1]->lineFlag == 0) { leftSide[1] = SetLinePoint(7, 1); }
		if (leftSide[2]->lineFlag == 0) { leftSide[2] = SetLinePoint(8, 1); }
		break;
	case 11:

		if (leftSide[point]->lineFlag == 0) { leftSide[point] = SetLinePoint(11, 1); }
		break;

	case 12:
		if (point == 0)
		{
			if (leftSide[0]->lineFlag == 0 && leftSide[1]->lineFlag == 0) { leftSide[0] = SetLinePoint(11, 1); leftSide[1] = SetLinePoint(11, 1); }
			break;
		}
		else if (point == 1)
		{
			if (leftSide[1]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[1] = SetLinePoint(11, 1); leftSide[2] = SetLinePoint(11, 1); }
			break;
		}
		else
		{
			if (leftSide[0]->lineFlag == 0 && leftSide[2]->lineFlag == 0) { leftSide[0] = SetLinePoint(11, 1); leftSide[2] = SetLinePoint(11, 1); }
			//if (frontHeight[2]->lineFlag == 0 && frontHeight[0]->lineFlag == 0) { frontHeight[2] = SetLinePoint(2); }
			break;
		}
		break;
	case 13:
		if (leftSide[0]->lineFlag == 0) { leftSide[0] = SetLinePoint(11, 1); }
		if (leftSide[1]->lineFlag == 0) { leftSide[1] = SetLinePoint(11, 1); }
		if (leftSide[2]->lineFlag == 0) { leftSide[2] = SetLinePoint(11, 1); }
		break;

	default:
		break;
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
		
		line_ = LineAtkCollision(line_, flag, angle);

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
			case 4://角度
				stageParts_->all = 1;

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
			case 4://角度
				stageParts_->all = 0;
				break;
			default:
				break;
			}
		}
	}
	return stageParts_;
}

StagePointer::LineAll* StagePointer::SetLineAllPoint(int point)
{
	LineAll* temp = new LineAll();
	temp->line = new Line();
	temp->line->lineAngle = (float)point * 10.f;
	temp->line->lineFlag =1;

	temp->length = -250.f;
	temp->oldLength = -250.f;

	temp->line->linePos.x = sin((((float)point * 10.f) * DirectX::XM_PI) / 180) * temp->length;
	temp->line->linePos.z = cos((((float)point * 10.f) * DirectX::XM_PI) / 180) * temp->length;
	temp->line->linePos.z -= 242;


	return temp;
}

void StagePointer::LineAllUpdate(int point)
{
	for (int j = 0; j < 50; j++)
	{
		for (int k = 0; k < 50; k++)
		{
			if (lineAll[point]->line->lineFlag >= 1)
			{
				stageParts[j][k] = LineAtkFlag(lineAll[point]->line, stageParts[j][k], modelWorld2, ALL);
			}
		}
	}
}

StagePointer::LineAll* StagePointer::LineAllAtk(LineAll* lineAll)
{
	LineAll* lineAll_ = lineAll;

	if (lineAll_->line->lineFlag == 1)
	{
		lineAll_->oldLength = lineAll_->length;
		lineAll_->line->lineFlag = 2;
	}

	if (lineAll_->line->lineFlag == 2)
	{

		//lineAll_->line = LineAtkCollision(lineAll_->line, flag, angle);
		lineAll_ = LineAllCollision(lineAll_);


		if (lineAll_->length >=250)
		{
			lineAll_->length = lineAll_->oldLength;
			lineAll_->line->lineFlag = 3;
		}
		
	}
	if (lineAll_->line->lineFlag == 3)
	{
		//lineAll_->line = LineAtkCollision(lineAll_->line, flag, angle);
		lineAll_ = LineAllCollision(lineAll_);

		if (lineAll_->length >= 250)
		{
			lineAll_->length = lineAll_->oldLength;
			lineAll_->line->lineFlag = 0;

		}
	}


	return lineAll_;
}

