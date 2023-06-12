#pragma once
#include <DirectXMath.h>
#include"collision.h"
#include"Stage.h"
#include"StagePointer.h"
class StageLine :public StagePointer
{
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	
public:
	
	//���C���̍U������
	static Line* LineAtk(Line* line, int flag,float endPos);

	//���C���̍X�V
	void LineUpdate(int i);

	//���C���ƘZ�p���̓����蔻��
	static StageParts* LineAtkFlag(Line* line, StageParts* stageParts, Model* model, int flag);

	//���C���̉��Z
	static Line* LineAtkMove(Line* line, int flag, float angle)
	{
		Line* line_ = new Line();
		line_ = line;
		line_->lineAccele += 0.2f;
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

	//�p�x�̂������C���̍X�V
	void LineAllUpdate(int point);
	
	//�p�x�̂������C���̍U������
	static LineAll* LineAllAtk(LineAll* lineAll);

	//�p�x�̂������C���̉��Z
	static LineAll* LineAllMove(LineAll* lineAll)
	{
		LineAll* lineAll_ = new LineAll();
		lineAll_ = lineAll;
		lineAll_->line->lineAccele += 0.2f;
		lineAll_->length += 6.f;

		lineAll_->line->linePos.x = sin((lineAll_->line->lineAngle * DirectX::XM_PI) / 180) * lineAll_->length;
		lineAll_->line->linePos.z = cos((lineAll_->line->lineAngle * DirectX::XM_PI) / 180) * lineAll_->length;
		lineAll_->line->linePos.z -= 242;

		return lineAll_;
	}

	//�p�x�̂������C���̏����l���
	void SetLINEAll(int i) { lineAll[i] = SetLineAllPoint(i); }

	//�p�x�̂������C���̊p�x�擾
	float GetLineAllAngle(int i) { return lineAll[i]->line->lineAngle; }

	//���C���U���̍X�V
	void LineAtkUpdate(int i);


};
