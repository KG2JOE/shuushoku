#pragma once

#include <DirectXMath.h>
#include"RandCreate.h"
#include"StageLine.h"
#include"Stage.h"

class StagePointer:public Stage
{
private:

	
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;

public://Line

	/// <summary>
	/// �X�e�[�W���C���̍��W
	/// </summary>
	/// <param name="point"><�p�^�[�����ʃ|�C���g>
	/// <param name="flag"></�c���؂�ւ�>
	/// <returns></returns>
	static Line* SetLinePoint(char point, bool flag);

	void SetHeightLineCase(char pattern);
	void SetWidthLineCase(char pattern);

	void LineUpdate(int i);

	static Line* LineAtkCollision(Line* line, int flag,float angle)
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

	static Line* LineAtk(Line* line,int flag);

	static StageParts* LineAtkFlag(Line* line, StageParts* stageParts, Model* model,int flag);

public://LineAll

	static LineAll* SetLineAllPoint(int point);

	void LineAllUpdate(int point);

	static LineAll* LineAllAtk(LineAll* lineAll);

	static LineAll* LineAllCollision(LineAll* lineAll)
	{
		LineAll* lineAll_ = new LineAll();
		lineAll_ = lineAll;
		lineAll_->line->lineAccele += 0.2f;
		lineAll_->length += 6.f;
		/*lineAll_->line->linePos.x -= sin((lineAll_->line->lineAngle * DirectX::XM_PI) / 180) * lineAll_->line->lineAccele;
		lineAll_->line->linePos.z -= cos((lineAll_->line->lineAngle * DirectX::XM_PI) / 180) * lineAll_->line->lineAccele;*/
		/*lineAll_->line->linePos.x += sin((lineAll_->line->lineAngle * DirectX::XM_PI) / 180) * lineAll_->line->lineAccele;
		lineAll_->line->linePos.z += cos((lineAll_->line->lineAngle * DirectX::XM_PI) / 180) * lineAll_->line->lineAccele;*/
		lineAll_->line->linePos.x = sin((lineAll_->line->lineAngle * DirectX::XM_PI) / 180) * lineAll_->length;
		lineAll_->line->linePos.z = cos((lineAll_->line->lineAngle * DirectX::XM_PI) / 180) * lineAll_->length;
		lineAll_->line->linePos.z -= 242;

		return lineAll_;
	}
};

