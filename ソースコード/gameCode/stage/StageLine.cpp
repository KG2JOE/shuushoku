#include "StageLine.h"

StageLine::Line* StageLine::LineAtk(Line* line, int flag, float endPos)
{
	float angle = 0.0f;
	//0or2�̂Ƃ��͉��A1or3�͏c
	if (flag % 2 == 0)
	{
		angle = 90.0f;
	}

	//�����̃��C�����
	Line* line_ = new Line();
	line_ = line;


	
	//���C���̍U������
	if (line_->lineFlag == 1)
	{
		//���C���̏����ʒu���
		line_->oldPos = line_->linePos;

		//���C���̍U���\���Ƀt���O��ύX
		line_->lineFlag = 2;
	}

	//���C���U���̗\��
	if (line_->lineFlag == 2)
	{

		//���C���̈ʒu�X�V
		line_ = LineAtkMove(line_, flag, angle);

		
		switch (flag)
		{

		case 0:
			//�E
			if (line_->linePos.x < endPos)
			{
				//���Z�l��������
				line_->lineAccele = 0.0f;
				//���C���̈ʒu���X�^�[�g�ʒu�ɖ߂�
				line_->linePos = line_->oldPos;
				//���C���̍U���Ƀt���O��ύX
				line_->lineFlag = 3;
			}
			//�ȉ�����
			break;
		case 1:
			//�O
			if (line_->linePos.z < endPos)
			{
				line_->lineAccele = 0.0f;
				line_->linePos = line_->oldPos;
				line_->lineFlag = 3;
			}
			break;
		case 2:
			//��
			if (line_->linePos.x > endPos)
			{
				line_->lineAccele = 0.0f;
				line_->linePos = line_->oldPos;
				line_->lineFlag = 3;
			}
			break;
		case 3:
			//���
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
	//���C���̍U��
	if (line_->lineFlag == 3)
	{

		//���C���̈ʒu�X�V
		line_ = LineAtkMove(line_, flag, angle);

		switch (flag)
		{

		case 0:
			//�E
			if (line_->linePos.x < endPos)
			{
				//���C���̍U���I��
				line_->lineFlag = 0;
			}
			break;
		case 1:
			//�O
			if (line_->linePos.z < endPos)
			{
				line_->lineFlag = 0;
			}
			break;
		case 2:
			//��
			if (line_->linePos.x > endPos)
			{
				line_->lineFlag = 0;
			}
			break;
		case 3:
			//���
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
	//���C���ƘZ�p���̓����蔻��
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

			case RIGHT://�E
				stageParts_->right = 1;
				break;
			case FLONT://�O
				stageParts_->flont = 1;
				break;
			case LEFT://��
				stageParts_->left = 1;
				break;
			case BACK://���
				stageParts_->back = 1;
				break;
			case ALL://�p�x
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

			case RIGHT://�E
				stageParts_->right = 0;
				break;
			case FLONT://�O
				stageParts_->flont = 0;
				break;
			case LEFT://��
				stageParts_->left = 0;
				break;
			case BACK://���
				stageParts_->back = 0;
				break;
			case ALL://�p�x
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
	//���C���̍��W�X�V
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

	//�p�x�̂��郉�C���̍U������
	if (lineAll_->line->lineFlag == 1)
	{
		//�p�x�̂��郉�C���̏����ʒu���
		lineAll_->oldLength = lineAll_->length;

		//�p�x�̂��郉�C���̍U���\���Ƀt���O��ύX
		lineAll_->line->lineFlag = 2;
	}

	//�p�x�̂��郉�C���U���̗\��
	if (lineAll_->line->lineFlag == 2)
	{
		//�p�x�̂��郉�C���̈ʒu�X�V
		lineAll_ = LineAllMove(lineAll_);

		if (lineAll_->length >= 250)
		{
			//�p�x�̂��郉�C���̈ʒu���X�^�[�g�ʒu�ɖ߂�
			lineAll_->length = lineAll_->oldLength;
			//�p�x�̂��郉�C���̍U���Ƀt���O��ύX
			lineAll_->line->lineFlag = 3;
		}

	}

	//�p�x�̂��郉�C���̍U��
	if (lineAll_->line->lineFlag == 3)
	{
		//�p�x�̂��郉�C���̈ʒu�X�V
		lineAll_ = LineAllMove(lineAll_);

		if (lineAll_->length >= 250)
		{
			//�p�x�̂��郉�C���̈ʒu���X�^�[�g�ʒu�ɖ߂�
			lineAll_->length = lineAll_->oldLength;
			
			//�p�x�̂���U���I��
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
	//�p�x�̂��郉�C���̍��W�X�V
	lineAll_->line->linePos.x = sin((lineAll_->line->lineAngle * DirectX::XM_PI) / 180) * lineAll_->length;
	lineAll_->line->linePos.z = cos((lineAll_->line->lineAngle * DirectX::XM_PI) / 180) * lineAll_->length;
	lineAll_->line->linePos.z -= 242;

	return lineAll_;
}

void StageLine::LineAtkUpdate(int i)
{
	//���C���U���̍X�V
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

