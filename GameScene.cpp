#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initilize(DirectXCommon* directXCommon, Audio* audio, Input* input ,SpriteCommon* spriteCommon)
{

	assert(directXCommon);
	assert(spriteCommon);
	assert(input);
	assert(audio);

	this->dxCommon_ = directXCommon;
	this->input_ = input;
	this->audio_ = audio;
	this->spriteCommon_ = spriteCommon;

	device = dxCommon_->GetDev();
	camera_ = new DebugCamera(WinApp::window_width, WinApp::window_height);


	// �J���������_���Z�b�g
	camera_->SetTarget({ 0, 1, 0 });
	camera_->SetDistance(3.0f);
	Object3d::StaticInitialize(dxCommon_->GetDev(), WinApp::window_width, WinApp::window_height);

	LoadTextureSprite();
	LoadTextureFbx();
	LoadTextureObj();

	ObjectSprite();
	ObjectFbx();
	ObjectObj();

}

void GameScene::ObjectSprite()
{
}

void GameScene::ObjectFbx()
{
}

void GameScene::ObjectObj()
{
	obj = Object3d::Create();
	obj->SetModel(modelChr);

}

void GameScene::LoadTextureSprite()
{
}

void GameScene::LoadTextureFbx()
{
}

void GameScene::LoadTextureObj()
{
	modelChr = Model::LoadFromOBJ("chr_sword", device);
}

void GameScene::Update()
{
	

	ClassUpdate();
}

void GameScene::ClassUpdate()
{
	camera_->Update();
	input_->Update();
	obj->Update();
}

void GameScene::Draw()
{
	ID3D12GraphicsCommandList* cmdList = dxCommon_->GetCmdList();

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

	Object3d::PreDraw(cmdList);
	obj->Draw();
	Object3d::PostDraw();
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	spriteCommon_->PreDraw();
	

	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>



#pragma endregion

}

