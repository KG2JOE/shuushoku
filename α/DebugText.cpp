#include "DebugText.h"

DebugText::DebugText() {

}

DebugText::~DebugText() {
	for (int i = 0; i < _countof(spriteDatas); i++) {
		delete spriteDatas[i];
	}
}

void DebugText::Initialize(SpriteCommon* SCom,UINT texnumber) {
	
	// nullptrチェック
	assert(SCom);

	// 引数をメンバ変数に格納
	spriteCommon_ = SCom;
	//全てのスプライトデータについて
	for (int i = 0; i < _countof(spriteDatas); i++) {
		//スプライトを生成する
		spriteDatas[i] = Sprite::Create(spriteCommon_,texnumber, { 0, 0 });
	}
}

void DebugText::Print(const std::string& text, float x, float y, float scale) {
	//全ての文字について
	for (int i = 0; i < text.size(); i++) {
		//最大文字数超過
		if (spriteIndex >= maxCharCount) {
			break;
		}

		//1文字取り出す(ASCIIコードでしか成り立たない)
		const unsigned char& character = text[i];

		int fontIndex = character - 32;
		if (character >= 0x7f) {
			fontIndex = 0;
		}

		int fontIndexY = fontIndex / fontLineCount;
		int fontIndexX = fontIndex % fontLineCount;

		////座標計算
		//spriteDatas[spriteIndex]->SetPosition({ x + fontWidth * scale * i, y,0 });
		//spriteDatas[spriteIndex]->SetTextureRect({ (float)fontIndexX * fontWidth, (float)fontIndexY * fontHeight }, { (float)fontWidth, (float)fontHeight });
		//spriteDatas[spriteIndex]->SetSize({ fontWidth * scale, fontHeight * scale });

		// 座標計算
		spriteDatas[spriteIndex]->SetPosition({ x + fontWidth * scale * i, y, 0 });
		spriteDatas[spriteIndex]->SetTexLeftTop({ (float)fontIndexX * fontWidth, (float)fontIndexY * fontHeight });
		spriteDatas[spriteIndex]->SetTexSize({ fontWidth, fontHeight });
		spriteDatas[spriteIndex]->SetSize({ fontWidth * scale, fontHeight * scale });
		// 頂点バッファ転送
		spriteDatas[spriteIndex]->TransferVertexBuffer();
		// 更新
		spriteDatas[spriteIndex]->Update();
		//文字を1つ進める
		spriteIndex++;
	}
}

void DebugText::DrawAll() {
	//全ての文字のスプライトについて
	for (int i = 0; i < spriteIndex; i++) {
		//スプライト描画
		spriteDatas[i]->Draw();
	}

	spriteIndex = 0;
}