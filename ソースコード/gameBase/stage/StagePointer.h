#pragma once

#include <DirectXMath.h>
#include"RandCreate.h"
#include"StageLine.h"
#include"Stage.h"

class StagePointer:public Stage
{
private:

	
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
private:
	/*struct Line
	{
		XMFLOAT3 linePos{};
		XMFLOAT3 oldPos{};
		float lineAccele = 0;
		char lineFlag{};
		float lineAngle{};
	};*/
public:

	static Line* SetHeightLinePoint(char point);

	static Line* SetSideLinePoint(char point);


	/// <summary>
	/// ステージラインの座標
	/// </summary>
	/// <param name="point"><パターン識別ポイント>
	/// <param name="flag"></縦横切り替え>
	/// <returns></returns>
	static Line* SetLinePoint(char point, bool flag);

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
	//void LineAtkPredict(Line* line, int point, int flag);
	static Line* LineAtk(Line* line,int flag);

	static StageParts* LineAtkFlag(Line* line, StageParts* stageParts, Model* model,int flag);
};

