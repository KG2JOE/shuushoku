#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initilize(DirectXCommon* dxComon, Audio* audio, Input* input ,SpriteCommon* spriteCommon)
{

	assert(dxCommon);
	assert(spriteCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;
	this->spriteCommon = spriteCommon;


	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);

	LoadTextureSprite();
	LoadTextureFbx();
	LoadTextureObj();

	ObjectSprite();
	ObjectFbx();
	ObjectObj();
	// �J���������_���Z�b�g
	camera->SetTarget({ 0, 1, 0 });
	camera->SetDistance(3.0f);


}

void GameScene::ObjectSprite()
{
}

void GameScene::ObjectFbx()
{
}

void GameScene::ObjectObj()
{
}

void GameScene::LoadTextureSprite()
{
}

void GameScene::LoadTextureFbx()
{
}

void GameScene::LoadTextureObj()
{
}

void GameScene::Update()
{
	

	ClassUpdate();
}

void GameScene::ClassUpdate()
{
	camera->Update();
	input->Update();
}

void GameScene::Draw()
{
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCmdList();

#pragma region �w�i�X�v���C�g�`��
	
	
	// �w�i�X�v���C�g�`��O����
	
	// �w�i�X�v���C�g�`��
	

	/// <summary>
	/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>

	// �X�v���C�g�`��㏈��
	
	// �[�x�o�b�t�@�N���A
	
#pragma endregion

#pragma region 3D�`��

#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	spriteCommon->PreDraw();
	

	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>



#pragma endregion

}

