#pragma once
#include<d3d12.h>
#include<d3dx12.h>
#include<dxgi1_6.h>
#include<wrl.h>
#include"WinApp.h"
#include<chrono>
#include<thread>


class DirectXCommon
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	
	using steady_clock = std::chrono::steady_clock;
	using microseconds = std::chrono::microseconds;
	using time_point = steady_clock::time_point;

public:
	void Initialize(WinApp* win);
	void PreDraw();
	void PostDraw();
private:
	void InitializeDevice();
	void InitializeCommand();
	void InitializeSwapchain();
	void InitializeRenderTargetView();
	void InitializeDepthBuffer();
	
private://インスタンシング用
	

	void InstancingDevice();
	void InstancingCommand();
	void InstancingSwapchain();
	void InstancingRenderTargetView();
	void InstancingDepthBuffer();
private://FPS
	void InitializeFence();
	void InitializeFixFPS();
	void UpdateFixFPS();
public:
	ID3D12Device* GetDev() { return dev.Get(); }
	ID3D12GraphicsCommandList* GetCmdList() { return cmdList.Get(); }
private:
	steady_clock::time_point reference_;
	WinApp* win = nullptr;

	ComPtr<ID3D12Device> dev;
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<IDXGISwapChain4> swapchain;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12CommandQueue> cmdQueue;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	ComPtr<ID3D12Resource> depthBuffer;
	ComPtr<ID3D12Fence> fence;
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	UINT64 fenceVal = 0;
};

