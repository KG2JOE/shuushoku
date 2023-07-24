#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Input.h"
#include"collision.h"
#include"Player.h"
#include"RandCreate.h"
#include"StagePointer.h"
#include "StageLine.h"

//#include"StageLine.h"
#include"Stage.h"

class StageWorld :public StageLine
{

private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private:

	struct SKY
	{
		Object3d* OBJ{};
		Model* model{};
	};
public:

	//������
	void Initialize(Input* input);
	
	//�Q�[���̏�����
	void GameInitialize();

	//�X�V
	void Update(XMFLOAT3 pos);

	//�X�e�[�W�̍X�V
	void StageUpdate();
	void StageUpdate(int i, int j);
	//�X�e�[�W�̍X�V���e
	void StageUpdateInside(int i, int j);

	//�`�揈��
	void Draw(int scene);
	
	//�폜
	void Delete();

	//�g�łU������
	void WaveATK();

	//�w�i�̍X�V
	void SkyUpdate();

	//�X�e�[�W�̍��W�𐳂�
	void ResetStageParts();
	void ResetStageParts(int i,int j);

	//�v���C���[�Ɍ����Ă̍U������
	void PlayerRockOnSet();
	void HitWave(int i, int j);
	//�v���C���[�Ɍ����Ă̍U���������e
	void PlayerRockOnSetInside(int i, int j);

	//�v���C���[�Ɍ����Ă̍U��
	void PlayerRockOnUp();
	//�v���C���[�Ɍ����Ă̍U�����e
	void PlayerRockOnUpInside(int i, int j, bool flag);

	
	//�g�łU���̑��
	void SetImpactPos(XMFLOAT3 pos) { this->impactPos = pos; }
	void SetImpactRad(float rad) { this->impactRad = rad; }
	void SetImpactFlag(bool flag) { this->impactFlag = flag; }
	void ALLSetImpact(XMFLOAT3 pos, float rad, bool flag);


	//�e���̍��W
	XMFLOAT3 GetPosition(int i, int j) { return stageParts[i][j]->OBJWorldPos; }

	//�n�ʂ��烉���_���ōU�������邽�߂̗\��
	void SetStageFlag(int i, int j, char flag)
	{
		this->stageParts[i][j]->OBJWorldFlag = flag;
		stageParts[i][j]->Manifest = 1;
	}
	void SetModel(int i, int j)
	{
		stageParts[i][j]->OBJWorld->SetModel(modelWorld4);
		stageParts[i][j]->Manifest = 1;
	}
	void SetModel2(int i, int j)
	{
		stageParts[i][j]->OBJWorld->SetModel(modelWorld1);
		stageParts[i][j]->Manifest = 0;
	}


	void SetPlayerPos(XMFLOAT3 pos) { this->playerPos = pos; }

	

private:

	Input* input_{};

	const char* name[3] = { "back","back2","back3" };
	XMFLOAT3 rot[3]{};
	SKY* sky[3]{};


	//�X�e�[�W�G�t�F�N�g
	//�E�F�[�u
	XMFLOAT3 impactPos{};
	float impactRad{};
	bool impactFlag = 0;


	


	RndCreate* rnd{};

	XMFLOAT3 playerPos{};
	float radius{};
	char playerRockFlag = 0;
	float playerRockTime = 30;
	float startTime = 50;

	
};

