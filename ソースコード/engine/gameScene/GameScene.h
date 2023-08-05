#pragma once


#include<vector>

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"

#include "Object3d.h"
#include "Model.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "DebugCamera.h"
#include "Collision.h"
#include"Audio.h"
#include"DebugText.h"

#include"StageWorld.h"
#include"Player.h"
#include"BossEnemy.h"
#include"Hud.h"
#include"Enemys.h"
#include<random>

using namespace DirectX;
class GameScene
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:

	//�G���W��������
	void EngineIns(WinApp* winApp_, DirectXCommon* dxCommon_, Input* input_);
	//�Q�[��������
	void Gameins();
	//�X�^�[�g�̏�����
	void StartIns(WinApp* winApp);

	//�S�̂̏�����
	void Initialize(WinApp* winApp_, DirectXCommon* dxCommon_, Input* input_);
	
	//�S�̍X�V
	void Update();

	//�^�C�g���̏���
	void TitleScene();

	//�Q�[���I��������
	void EndScene();

	//�������
	void explainScene();

	//�Q�[������
	void GamePlayScene();

	//���ꂼ��̍X�V
	void VariableUpdate();

	//�S�̕`��
	void Draw();

	//�S�̍폜
	void Delete();

	//�X�e�[�W�̏���
	void Stage();

	//�G�̏���
	void Boss();
	void EnemysUp();

	//�����蔻��̏���
	void CollisionUp();
private://�G���W��
	//WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	DebugCamera* camera = nullptr;
	SpriteCommon* spriteCommon = new SpriteCommon();
	DebugText* debTxt = new DebugText;
	Audio* audio = Audio::GetInstance();
	RndCreate* rnd = new RndCreate();

	int scene = 0;

private://�Q�[��

	Hud* hud = new Hud();
	StageWorld* stageWorld = new StageWorld();
	Player* player = new Player();
	
	BossEnemy* boss = new BossEnemy();
	Enemys* enemys = new Enemys();
	// �J�����֘A

	float angleX = 0;
	float angleY = 0;
	float MoveAngleY;
	float scaleX = 1.0f / (float)WinApp::window_width;
	float scaleY = 1.0f / (float)WinApp::window_height;
	float distance = 50.0f;
	XMMATRIX matRot = DirectX::XMMatrixIdentity();

	float addAngle = -89.550f;


	//	�X�e�[�W�֘A
	int stageRand1 = 0;
	int stageRand2 = 0;
	int time = 100;
	int oldtime = 200;
	int time2 = 160;
	int oldtime2 = 200;
	int time3 = 160;
	int oldtime3 = 200;
	

	//	�v���C���[�֘A
	float setrot = 0;


	//	�{�X�֘A
	bool setflag{};

	//���o�֘A
	int hudFlag = 0;


	int enemysCount = 0;

};

