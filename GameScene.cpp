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
	SetBehavior();
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
	obj->SetModel(modelChr2);

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
	modelChr2 = Model::LoadFromOBJ("posuto");

}

void GameScene::SetBehavior()
{
	behavior.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);
	behavior.AddNode("Root", "Attack", 1, BehaviorTree::SELECT_RULE::SEQUENTIAL_LOOPING, AttackJudgment::GetInstance(), NULL);
	behavior.AddNode("Root", "Deffence", 2, BehaviorTree::SELECT_RULE::NON, DeffenceJudgment::GetInstance(), DeffenceAction::GetInstance());
	behavior.AddNode("Attack", "PhysicsAttack", 1, BehaviorTree::SELECT_RULE::NON, NULL, PhysicsAction::GetInstance());
	behavior.AddNode("Attack", "MagicAttack", 2, BehaviorTree::SELECT_RULE::NON, MagicAttackJudgment::GetInstance(), MagicAction::GetInstance());
	behavior.AddNode("Attack", "SkillAttack", 3, BehaviorTree::SELECT_RULE::NON, SkillAttackJudgment::GetInstance(), SkillAction::GetInstance());
	behavior.PrintTree();
	enemyZ = new Enemy (&behavior, 100.0f, 100.0f, 30.0f, 10.0f);
	
}

void GameScene::Behavior()
{
	/*for (int i = 0; i < 100; i++)
	{
		if (enemyZ->IsDie() == false)
		{
			enemyZ->Run();
			enemyZ->ReceiveDamage(2.0f);
		}
	}*/
	if (enemyZ->IsDie() == false)
	{
		enemyZ->Run();
		//enemyZ->ReceiveDamage(1.0f);
	}
}

void GameScene::Update()
{
	input_->Update();

	if (input_->TriggerKey(DIK_P))
	{
		modelChr = Model::LoadFromOBJ("chr_sword");
		obj->SetModel(modelChr);

	}
	if (input_->TriggerKey(DIK_L))
	{
		modelChr = Model::LoadFromOBJ("posuto");
		obj->SetModel(modelChr);
	}
	if (input_->TriggerKey(DIK_SPACE))
	{
		Behavior();
	}
	//Behavior();
	ClassUpdate();
}

void GameScene::ClassUpdate()
{
	
	camera_->Update();
	//input_->Update();
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

