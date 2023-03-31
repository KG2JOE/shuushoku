#pragma once

#include "Sprite.h"
#include <Windows.h>
#include <string>
//#include"SpriteCommon.h"
class DebugText
{
public: //�ÓI�����o�ϐ�
	//�f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
	//�ő啶����
	static const int maxCharCount = 256;
	//�t�H���g�摜��1�������̕�
	//tatic const int fontWidth = 9;//34
	static const int fontWidth = 34;//34
	//�t�H���g�摜��1�������̍���
	//static const int fontHeight = 18;//64
	static const int fontHeight = 64;//64
	//�t�H���g�摜��1�s���̕�����
	//static const int fontLineCount = 14;//10
	static const int fontLineCount = 10;//10
public: //�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	DebugText();
	/// <summary>
    /// �f�X�g���N�^
    /// </summary>
	~DebugText();
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="texnumber">�e�N�X�`���ԍ�</param>
	void Initialize(SpriteCommon* SCom,UINT texnumber);
	/// <summary>
	/// 1������ǉ�
	/// </summary>
	/// <param name="text">�e�L�X�g</param>
	/// <param name="x">������X���W</param>
	/// <param name="y">������Y���W</param>
	/// <param name="size">�����̑傫��</param>
	void Print(const std::string& text, float x, float y, float size);

	void DrawAll();

private: //�����o�ϐ�
	//�X�v���C�g�f�[�^�̔z��
	Sprite* spriteDatas[maxCharCount] = {};

	SpriteCommon* spriteCommon_ = nullptr;

	//�X�v���C�g�f�[�^�z��̓Y�����ԍ�
	int spriteIndex = 0;
};

