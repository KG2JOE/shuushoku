#include "StageLine.h"

StageLine::Line* StageLine::LineAtk(Line* line, int flag, float endPos)
{
	float angle = 0.0f;
	//0or2のときは横、1or3は縦
	if (flag % 2 == 0)
	{
		angle = 90.0f;
	}

	//引数のライン代入
	Line* line_ = new Line();
	line_ = line;


	
	//ラインの攻撃準備
	if (line_->lineFlag == 1)
	{
		//ラインの初期位置代入
		line_->oldPos = line_->linePos;

		//ラインの攻撃予測にフラグを変更
		line_->lineFlag = 2;
	}

	//ライン攻撃の予測
	if (line_->lineFlag == 2)
	{

		//ラインの位置更新
		line_ = LineAtkMove(line_, flag, angle);

		
		switch (flag)
		{

		case 0:
			//右
			if (line_->linePos.x < endPos)
			{
				//加算値を初期化
				line_->lineAccele = 0.0f;
				//ラインの位置をスタート位置に戻す
				line_->linePos = line_->oldPos;
				//ラインの攻撃にフラグを変更
				line_->lineFlag = 3;
			}
			//以下同文
			break;
		case 1:
			//前
			if (line_->linePos.z < endPos)
			{
				line_->lineAccele = 0.0f;
				line_->linePos = line_->oldPos;
				line_->lineFlag = 3;
			}
			break;
		case 2:
			//左
			if (line_->linePos.x > endPos)
			{
				line_->lineAccele = 0.0f;
				line_->linePos = line_->oldPos;
				line_->lineFlag = 3;
			}
			break;
		case 3:
			//後ろ
			if (line_->linePos.z > endPos)
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
	//ラインの攻撃
	if (line_->lineFlag == 3)
	{

		//ラインの位置更新
		line_ = LineAtkMove(line_, flag, angle);

		switch (flag)
		{

		case 0:
			//右
			if (line_->linePos.x < endPos)
			{
				//ラインの攻撃終了
				line_->lineFlag = 0;
			}
			break;
		case 1:
			//前
			if (line_->linePos.z < endPos)
			{
				line_->lineFlag = 0;
			}
			break;
		case 2:
			//左
			if (line_->linePos.x > endPos)
			{
				line_->lineFlag = 0;
			}
			break;
		case 3:
			//後ろ
			if (line_->linePos.z > endPos)
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

void StageLine::LineUpdate(int i)
{
	//ラインと六角柱の当たり判定
	for (int j = 0; j < stage_.size(); j++)
	{
		for (int k = 0; k < stage_.size(); k++)
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

StageLine::StageParts* StageLine::LineAtkFlag(Line* line, StageParts* stageParts, Model* model, int flag)
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

			case RIGHT://右
				stageParts_->right = 1;
				break;
			case FLONT://前
				stageParts_->flont = 1;
				break;
			case LEFT://左
				stageParts_->left = 1;
				break;
			case BACK://後ろ
				stageParts_->back = 1;
				break;
			case ALL://角度
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

			case RIGHT://右
				stageParts_->right = 0;
				break;
			case FLONT://前
				stageParts_->flont = 0;
				break;
			case LEFT://左
				stageParts_->left = 0;
				break;
			case BACK://後ろ
				stageParts_->back = 0;
				break;
			case ALL://角度
				stageParts_->all = 0;
				break;
			default:
				break;
			}
		}
	}
	return stageParts_;
}

Stage::Line* StageLine::LineAtkMove(Line* line, int flag, float angle)
{

	Line* line_ = new Line();
	line_ = line;
	line_->lineAccele += 0.2f;
	//ラインの座標更新
	if (flag <= 1)
	{
		line_->linePos.x -= sin((line_->lineAngle + angle * DirectX::XM_PI) / 180) * line_->lineAccele;
		line_->linePos.z -= cos((line_->lineAngle + angle * DirectX::XM_PI) / 180) * line_->lineAccele;
	}
	else
	{
		line_->linePos.x += sin((line_->lineAngle + angle * DirectX::XM_PI) / 180) * line_->lineAccele;
		line_->linePos.z += cos((line_->lineAngle + angle * DirectX::XM_PI) / 180) * line_->lineAccele;
	}
	return line_;
}

void StageLine::LineAllUpdate(int point)
{
	for (int j = 0; j < stage_.size(); j++)
	{
		for (int k = 0; k < stage_.size(); k++)
		{
			if (lineAll[point]->line->lineFlag >= 1)
			{
				stageParts[j][k] = LineAtkFlag(lineAll[point]->line, stageParts[j][k], modelWorld2, ALL);
			}
		}
	}
}

StageLine::LineAll* StageLine::LineAllAtk(LineAll* lineAll)
{
	LineAll* lineAll_ = lineAll;

	//角度のあるラインの攻撃準備
	if (lineAll_->line->lineFlag == 1)
	{
		//角度のあるラインの初期位置代入
		lineAll_->oldLength = lineAll_->length;

		//角度のあるラインの攻撃予測にフラグを変更
		lineAll_->line->lineFlag = 2;
	}

	//角度のあるライン攻撃の予測
	if (lineAll_->line->lineFlag == 2)
	{
		//角度のあるラインの位置更新
		lineAll_ = LineAllMove(lineAll_);

		if (lineAll_->length >= 250)
		{
			//角度のあるラインの位置をスタート位置に戻す
			lineAll_->length = lineAll_->oldLength;
			//角度のあるラインの攻撃にフラグを変更
			lineAll_->line->lineFlag = 3;
		}

	}

	//角度のあるラインの攻撃
	if (lineAll_->line->lineFlag == 3)
	{
		//角度のあるラインの位置更新
		lineAll_ = LineAllMove(lineAll_);

		if (lineAll_->length >= 250)
		{
			//角度のあるラインの位置をスタート位置に戻す
			lineAll_->length = lineAll_->oldLength;
			
			//角度のある攻撃終了
			lineAll_->line->lineFlag = 0;

		}
	}
	return lineAll_;
}

Stage::LineAll* StageLine::LineAllMove(LineAll* lineAll)
{
	LineAll* lineAll_ = new LineAll();
	lineAll_ = lineAll;
	lineAll_->line->lineAccele += 0.2f;
	lineAll_->length += 6.f;
	//角度のあるラインの座標更新
	lineAll_->line->linePos.x = sin((lineAll_->line->lineAngle * DirectX::XM_PI) / 180) * lineAll_->length;
	lineAll_->line->linePos.z = cos((lineAll_->line->lineAngle * DirectX::XM_PI) / 180) * lineAll_->length;
	lineAll_->line->linePos.z -= 242;

	return lineAll_;
}

void StageLine::LineAtkUpdate(int i)
{
	//ライン攻撃の更新
	if (frontHeight[i]->lineFlag >= 1)
	{
		frontHeight[i] = LineAtk(frontHeight[i], FLONT, flont_);
	}

	if (backHeight[i]->lineFlag >= 1)
	{
		backHeight[i] = LineAtk(backHeight[i], BACK, back_);
	}

	if (rightSide[i]->lineFlag >= 1)
	{
		rightSide[i] = LineAtk(rightSide[i], RIGHT, right_);
	}

	if (leftSide[i]->lineFlag >= 1)
	{
		leftSide[i] = LineAtk(leftSide[i], LEFT, left_);
	}
}

