#pragma once

#include <DirectXMath.h>
#include"RandCreate.h"
#include"Stage.h"

class StagePointer:public Stage
{
private:

	
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;

public:

	/// <summary>
	/// �X�e�[�W���C���̍��W
	/// </summary>
	/// <param name="point"><�p�^�[�����ʃ|�C���g>
	/// <param name="flag"></�c���؂�ւ�>
	/// <returns></returns>
	static Line* SetLinePoint(char point, bool flag);
	
	/// <summary>
	/// �S�p�x�̃X�e�[�W���C���̍��W
	/// </summary>
	/// <param name="point"><10�̔{���w��>
	/// <returns></returns>
	static LineAll* SetLineAllPoint(int point);

	/// <summary>
	/// �O�㍶�E�̃��C���|�C���g
	/// </summary>
	/// <param name="pattern"><�p�^�[������>
	void SetHeightLineCase(char pattern);
	void SetWidthLineCase(char pattern);

};

