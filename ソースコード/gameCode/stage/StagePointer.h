#pragma once

#include <DirectXMath.h>
#include"RandCreate.h"
#include"Stage.h"

class StagePointer:public Stage
{
private:

	
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;

public:

	/// <summary>
	/// ステージラインの座標
	/// </summary>
	/// <param name="point"><パターン識別ポイント>
	/// <param name="flag"></縦横切り替え>
	/// <returns></returns>
	static Line* SetLinePoint(char point, bool flag);
	
	/// <summary>
	/// 全角度のステージラインの座標
	/// </summary>
	/// <param name="point"><10の倍数指定>
	/// <returns></returns>
	static LineAll* SetLineAllPoint(int point);

	/// <summary>
	/// 前後左右のラインポイント
	/// </summary>
	/// <param name="pattern"><パターン入力>
	void SetHeightLineCase(char pattern);
	void SetWidthLineCase(char pattern);

};

