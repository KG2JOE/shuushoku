#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include<string>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <vector>

#include"Model.h"
#include"Camera.h"

//#include"PipelineSet.h"

/// 3D�I�u�W�F�N�g
class InstancingObject3d
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	//���f��
	Model* model = nullptr;
	// �J����
	//Camera* camera = nullptr;
	//static Camera* camera;

public: // �T�u�N���X
		// �p�C�v���C���Z�b�g
	struct PipelineSet
	{
		// ���[�g�V�O�l�`��
		ComPtr<ID3D12RootSignature> rootsignature;
		// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
		ComPtr<ID3D12PipelineState> pipelinestate;
	};

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataB0
	{
		//XMMATRIX mat;	// �R�c�ϊ��s��
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
		//XMFLOAT4 color;
	};

	//�C���X�^���V���O�p�ő���������

	/*struct InstanceData {
		XMFLOAT4X4 world;
		XMFLOAT4 color;
	};*/
	//�C���X�^���V���O�p�ő���������


private:
	static const int division = 50;
	static const float radius;
	static const float prizmHeight;
	static const int planeCount = division * 2 + division * 2;
	static const int vertexCount = planeCount * 3;

	
	
public: // �ÓI�����o�֐�
	static void StaticInitialize(ID3D12Device* device, Camera* camera = nullptr);

	/*static void SetCamera(Camera* camera) {
		Object3d::camera = camera;
	}*/

	/// �`��O����
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �J�����̃Z�b�g
	/// </summary>
	/// <param name="camera">�J����</param>
	static void SetCamera(Camera* camera) {
		InstancingObject3d::camera = camera;
	}

	/// �`��㏈��
	static void PostDraw();

	//Object3d* Create(Model* model);

	/// 3D�I�u�W�F�N�g��
	static InstancingObject3d* Create(Model* model = nullptr);

	void SetModel(Model* model) { this->model = model; }
	Model* GetModel() { return model; }
	//static void LoadMaterial(const std::string& directoryPath, const std::string& filename);

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	
	//// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	ComPtr<ID3D12CommandQueue> commandQueue;
	ComPtr<IDXGISwapChain4> swapChain;
	ComPtr<ID3D12DescriptorHeap> descriptorHeap;
	ComPtr<ID3D12CommandAllocator> commandAllocator;

	// �J����
	static Camera* camera;
	// �p�C�v���C��
	static PipelineSet pipelineSet;


private:// �ÓI�����o�֐�
	
	/// �O���t�B�b�N�p�C�v���C������
	static bool InitializeGraphicsPipeline();

	static void CreateModel();

public: // �����o�֐�
	//������
	bool Initialize();
	/// ���t���[������
	void Update();
	/// �`��
	void Draw();

	/// ���W�̎擾
	const XMFLOAT3& GetPosition() { return position; }

	/// ���W�̐ݒ�
	void SetPosition(XMFLOAT3 position) { this->position = position; }

	/// ��]�̎擾
	const XMFLOAT3& GetRotation() { return rotation; }

	/// ��]�̐ݒ�
	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }
	void SetRotationX(float rotation) { this->rotation.x = rotation; }
	void SetRotationY(float rotation) { this->rotation.y = rotation; }
	void SetRotationZ(float rotation) { this->rotation.z = rotation; }

	void SetScale(XMFLOAT3 scale) { this->scale = scale; }


private: // �����o�ϐ�
	ComPtr<ID3D12Resource> constBuffB0; // �萔�o�b�t�@
	// �F
	XMFLOAT4 color = { 1,1,1,1 };
	// ���[�J���X�P�[��
	XMFLOAT3 scale = { 1.0,1.0,1.0 };
	// X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation = { 0,0,0 };
	// ���[�J�����W
	XMFLOAT3 position = { 0,0,1 };
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	// �e�I�u�W�F�N�g
	InstancingObject3d* parent = nullptr;

};