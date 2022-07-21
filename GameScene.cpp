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
	// カメラ注視点をセット
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

#pragma region 背景スプライト描画
	
	
	// 背景スプライト描画前処理
	
	// 背景スプライト描画
	

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	
	// 深度バッファクリア
	
#pragma endregion

#pragma region 3D描画

#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	spriteCommon->PreDraw();
	

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>



#pragma endregion

}

