#include "DebugText.h"

DebugText::DebugText() {

}

DebugText::~DebugText() {
	for (int i = 0; i < _countof(spriteDatas); i++) {
		delete spriteDatas[i];
	}
}

void DebugText::Initialize(SpriteCommon* SCom, UINT texnumber) {

	// nullptr�`�F�b�N
	assert(SCom);

	// �����������o�ϐ��Ɋi�[
	spriteCommon_ = SCom;
	//�S�ẴX�v���C�g�f�[�^�ɂ���
	for (int i = 0; i < _countof(spriteDatas); i++) {
		//�X�v���C�g�𐶐�����
		spriteDatas[i] = Sprite::Create(spriteCommon_, texnumber, { 0, 0 });
	}
}

void DebugText::Print(const std::string& text, float x, float y, float scale) {
	//�S�Ă̕����ɂ���
	for (int i = 0; i < text.size(); i++) {
		//�ő啶��������
		if (spriteIndex >= maxCharCount) {
			break;
		}

		//1�������o��(ASCII�R�[�h�ł������藧���Ȃ�)
		const unsigned char& character = text[i];

		int fontIndex = character - 32;
		if (character >= 0x7f) {
			fontIndex = 0;
		}

		int fontIndexY = fontIndex / fontLineCount;
		int fontIndexX = fontIndex % fontLineCount;

		////���W�v�Z
		//spriteDatas[spriteIndex]->SetPosition({ x + fontWidth * scale * i, y,0 });
		//spriteDatas[spriteIndex]->SetTextureRect({ (float)fontIndexX * fontWidth, (float)fontIndexY * fontHeight }, { (float)fontWidth, (float)fontHeight });
		//spriteDatas[spriteIndex]->SetSize({ fontWidth * scale, fontHeight * scale });

		// ���W�v�Z
		spriteDatas[spriteIndex]->SetPosition({ x + fontWidth * scale * i, y, 0 });
		spriteDatas[spriteIndex]->SetTexLeftTop({ (float)fontIndexX * fontWidth, (float)fontIndexY * fontHeight });
		spriteDatas[spriteIndex]->SetTexSize({ fontWidth, fontHeight });
		spriteDatas[spriteIndex]->SetSize({ fontWidth * scale, fontHeight * scale });
		// ���_�o�b�t�@�]��
		spriteDatas[spriteIndex]->TransferVertexBuffer();
		// �X�V
		spriteDatas[spriteIndex]->Update();
		//������1�i�߂�
		spriteIndex++;
	}
}

void DebugText::DrawAll() {
	//�S�Ă̕����̃X�v���C�g�ɂ���
	for (int i = 0; i < spriteIndex; i++) {
		//�X�v���C�g�`��
		spriteDatas[i]->Draw();
	}

	spriteIndex = 0;
}