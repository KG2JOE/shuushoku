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
	
	//ラインの攻撃処理
	static Line* LineAtk(Line* line, int flag,float endPos);

	//ラインの更新
	void LineUpdate(int i);

	//ラインと六角柱の当たり判定
	static StageParts* LineAtkFlag(Line* line, StageParts* stageParts, Model* model, int flag);

	//ラインの加算
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

	//角度のついたラインの更新
	void LineAllUpdate(int point);
	
	//角度のついたラインの攻撃処理
	static LineAll* LineAllAtk(LineAll* lineAll);

	//角度のついたラインの加算
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

	//角度のついたラインの初期値代入
	void SetLINEAll(int i) { lineAll[i] = SetLineAllPoint(i); }

	//角度のついたラインの角度取得
	float GetLineAllAngle(int i) { return lineAll[i]->line->lineAngle; }

	//ライン攻撃の更新
	void LineAtkUpdate(int i);


};
