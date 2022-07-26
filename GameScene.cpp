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


	// カメラ注視点をセット
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
	sprite_ = new Sprite();
	sprite_ = Sprite::Create(spriteCommon_, 0, { 0,0 }, false, false);

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
	spriteCommon_->LoadTexture(11, L"Resources/texture.png");
	spriteCommon_->LoadTexture(1, L"Resources/white.png");
	spriteCommon_->LoadTexture(0, L"Resources/background.png");
}

void GameScene::LoadTextureFbx()
{
}

void GameScene::LoadTextureObj()
{
	modelChr = Model::LoadFromOBJ("chr_sword");
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
	sprite_->Update();
}

void GameScene::Draw()
{
	ID3D12GraphicsCommandList* cmdList = dxCommon_->GetCmdList();

#pragma region 背景スプライト描画
	
	
	// 背景スプライト描画前処理
	
	// 背景スプライト描画
	spriteCommon_->PreDraw();

	sprite_->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	
	// 深度バッファクリア
	
#pragma endregion

#pragma region 3D描画

	Object3d::PreDraw(cmdList);
	obj->Draw();
	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	spriteCommon_->PreDraw();
	

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>



#pragma endregion

}

