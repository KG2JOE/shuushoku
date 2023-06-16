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
	static Line* LineAtkMove(Line* line, int flag, float angle);

	//角度のついたラインの更新
	void LineAllUpdate(int point);
	
	//角度のついたラインの攻撃処理
	static LineAll* LineAllAtk(LineAll* lineAll);

	//角度のついたラインの加算
	static LineAll* LineAllMove(LineAll* lineAll);

	//角度のついたラインの初期値代入
	void SetLINEAll(int i) { lineAll[i] = SetLineAllPoint(i); }

	//角度のついたラインの角度取得
	float GetLineAllAngle(int i) { return lineAll[i]->line->lineAngle; }

	//ライン攻撃の更新
	void LineAtkUpdate(int i);


};
