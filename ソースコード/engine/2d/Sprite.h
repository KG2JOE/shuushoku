#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include"SpriteCommon.h"

class Sprite
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT2 uv;  // uv座標
	};

	struct ConstBufferData {
		XMFLOAT4 color; // 色 (RGBA)
		XMMATRIX mat;   // ３Ｄ変換行列
	};

protected:
	//頂点バッファ;
	ComPtr<ID3D12Resource> vertBuff_;
	//頂点バッファビュー;
	D3D12_VERTEX_BUFFER_VIEW vbView_{};
	//定数バッファ;
	ComPtr<ID3D12Resource> constBuff_;
	// Z軸回りの回転角
	float rotation_ = 0.0f;
	// 座標
	XMFLOAT3 position_ = { 0,0,0 };
	// ワールド行列
	XMMATRIX matWorld_;
	// 色(RGBA)
	XMFLOAT4 color_ = { 1, 1, 1, 1 };
	// テクスチャ番号
	UINT texNumber_ = 0;
	// 大きさ
	XMFLOAT2 size_ = { 100, 100 };
	// アンカーポイント
	XMFLOAT2 anchorpoint_ = { 0.5f, 0.5f };
	// 左右反転
	bool isFlipX_ = false;
	// 上下反転
	bool isFlipY_ = false;
	// テクスチャ左上座標
	XMFLOAT2 texLeftTop_ = { 0, 0 };
	// テクスチャ切り出しサイズ
	XMFLOAT2 texSize_ = { 100, 100 };
	// 非表示
	bool isInvisible_ = false;

	SpriteCommon* SspriteCommon = nullptr;

public:
	Sprite(/*UINT texNumber, XMFLOAT3 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY*/);

	static Sprite* Create(SpriteCommon* spriteCommon, UINT texNumber, XMFLOAT2 anchorpoint = { 0.5f,0.5f }, bool isFlipX = false, bool isFlipY = false);

	void initialize(SpriteCommon* spriteCommon, UINT texNumber, XMFLOAT2 anchorpoint = { 0.5f,0.5f }, bool isFlipX = false, bool isFlipY = false);

	D3D12_RESOURCE_DESC SetSprite(SpriteCommon* spriteCommon, UINT texNumber){ return spriteCommon->GetTexBuff(texNumber)->GetDesc(); }

	void TransferVertexBuffer();

	void SetTextureRect(XMFLOAT2 texLeftTop, XMFLOAT2 texSize);

	void Update();

	void SetPosition(const XMFLOAT3 position) { position_ = position; }

	XMFLOAT3 GetPosition() { return position_; }

	void SetRotation(float rotation) { rotation_ = rotation; }

	void SetSize(XMFLOAT2 size) { size_ = size; }

	void SetTexLeftTop(XMFLOAT2 texLeftTop) { texLeftTop_ = texLeftTop; }

	void SetTexSize(XMFLOAT2 texSize) { texSize_ = texSize; }

	void SetAnchorpoint(XMFLOAT2 anchorpoint) { anchorpoint_ = anchorpoint; }

	void Draw();

};