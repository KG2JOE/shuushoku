#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Input.h"
#include"collision.h"
class StageWorld
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


	void Initialize(Input* input);

	void Update();

	void Draw();

	void WaveATK();

	void SetImpactPos(XMFLOAT3 pos) { this->impactPos = pos; }
	void SetImpactRad(float rad) { this->impactRad = rad; }
	void SetImpactFlag(bool flag) { this->impactFlag = flag; }
	void ALLSetImpact(XMFLOAT3 pos, float rad, bool flag);
private:
	Input* input_;
	Model* modelWorld1 = Model::LoadFromOBJ("world1");
	Model* modelWorld2 = Model::LoadFromOBJ("world2");
	Object3d* OBJWorld[50][50]{};
	bool OBJWorldFlag[50][50]{};
	XMFLOAT3 OBJWorldPos[50][50]{};
	XMFLOAT3 oldOBJWorldPos[50][50]{};
	float worldjamp[50][50]{};

	//�X�e�[�W�G�t�F�N�g
	XMFLOAT3 impactPos{};
	float impactRad{};
	bool impactFlag = 0;
};

