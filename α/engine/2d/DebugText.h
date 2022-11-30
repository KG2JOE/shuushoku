#pragma once

#include "Sprite.h"
#include <Windows.h>
#include <string>
//#include"SpriteCommon.h"
class DebugText
{
public: //静的メンバ変数
	//デバッグテキスト用のテクスチャ番号を指定
	//最大文字数
	static const int maxCharCount = 256;
	//フォント画像内1文字分の幅
	//tatic const int fontWidth = 9;//34
	static const int fontWidth = 34;//34
	//フォント画像内1文字分の高さ
	//static const int fontHeight = 18;//64
	static const int fontHeight = 64;//64
	//フォント画像内1行分の文字数
	//static const int fontLineCount = 14;//10
	static const int fontLineCount = 10;//10
public: //メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	DebugText();
	/// <summary>
    /// デストラクタ
    /// </summary>
	~DebugText();
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="texnumber">テクスチャ番号</param>
	void Initialize(SpriteCommon* SCom,UINT texnumber);
	/// <summary>
	/// 1文字列追加
	/// </summary>
	/// <param name="text">テキスト</param>
	/// <param name="x">文字のX座標</param>
	/// <param name="y">文字のY座標</param>
	/// <param name="size">文字の大きさ</param>
	void Print(const std::string& text, float x, float y, float size);

	void DrawAll();

private: //メンバ変数
	//スプライトデータの配列
	Sprite* spriteDatas[maxCharCount] = {};

	SpriteCommon* spriteCommon_ = nullptr;

	//スプライトデータ配列の添え字番号
	int spriteIndex = 0;
};

