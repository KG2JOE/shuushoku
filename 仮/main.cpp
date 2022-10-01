
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

using namespace DirectX;
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMVECTOR = DirectX::XMVECTOR;
using XMMATRIX = DirectX::XMMATRIX;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

#pragma region WindowsAPI初期化
	WinApp* winApp = nullptr;

	winApp = new WinApp();
	winApp->Initialize();

	MSG msg{};  // メッセージ
#pragma endregion WindowsAPI初期化

#pragma region DirectX初期化処理

	DirectXCommon* dxCommon = nullptr;

	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	Input* input = nullptr;
	input = new Input();
	input->Initialize(winApp);

	Object3d::StaticInitialize(dxCommon->GetDev());
	DebugCamera* camera = nullptr;
	
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);
	Object3d::SetCamera(camera);

	// カメラ注視点をセット
	camera->SetTarget({ 0, 11, -400 });
	camera->SetDistance(3.0f);

#pragma endregion DirectX初期化処理

#pragma region 描画初期化処理

	SpriteCommon* spriteCommon = new SpriteCommon();

	spriteCommon->initialize(dxCommon->GetDev(), dxCommon->GetCmdList(), winApp->window_width, winApp->window_height);
	
	
	spriteCommon->LoadTexture(0, L"Resources/coraRe.png");
	spriteCommon->LoadTexture(1, L"Resources/playerRe.png");
	spriteCommon->LoadTexture(2, L"Resources/reader.png");
	spriteCommon->LoadTexture(3, L"Resources/debugfont.png");

	std::vector<Sprite*> sprites;
	
	Sprite* spriteCoraRe = Sprite::Create(spriteCommon, 0, { 0,0 }, false, false);
	Sprite* spritePlayerRe = Sprite::Create(spriteCommon, 1, { 0,0 }, false, false);
	Sprite* spriteReader = Sprite::Create(spriteCommon, 2, { 0,0 }, false, false);
	XMFLOAT3 coraRe = { 1280 - 128-16,0,0 };

	spriteCoraRe->SetPosition(coraRe);
	spriteCoraRe->Update();
	

	spritePlayerRe->SetPosition({ 1280 - 256 - 120,0,0 });
	spritePlayerRe->Update();
	spriteReader->SetPosition({ 1280 - 256,0,0 });
	spriteReader->Update();
	
	DebugText* debTxt = new DebugText;

	debTxt->Initialize(spriteCommon, 3);
	Model* inCoa = Model::LoadFromOBJ("core_in");
	
	Model* modelGround = Model::LoadFromOBJ("ground");

	Model* modelChr = Model::LoadFromOBJ("chr_sword");
	
	Model* modelBack = Model::LoadFromOBJ("back");
	//Model* modelCloud = Model::LoadFromOBJ("cloud");
	Model* modelTerritory = Model::LoadFromOBJ("territory");

	int ECount = 10;

	const float PI = 3.1415926f;


	Object3d* OBJInCoa = Object3d::Create();
	
	Object3d* OBJBack = Object3d::Create();

	Object3d* objGround = Object3d::Create();
	Object3d* objCloud = Object3d::Create();
	Object3d* objTerritory = Object3d::Create();
	objTerritory->SetModel(modelTerritory);
	objTerritory->SetPosition({ 0,4,50 });
	objTerritory->SetScale({ 98, 1, 98 });
	OBJInCoa->SetModel(inCoa);
	
	OBJBack->SetModel(modelBack);
	objGround->SetModel(modelGround);

	objCloud->SetModel(/*modelCloud*/modelChr);

	//XMFLOAT3 coapos = { 0,4,50 };
	XMFLOAT3 coapos = { 0,14,30 };
	OBJInCoa->SetPosition(coapos);
	

	OBJBack->SetPosition({ 0,10,50 });
	objGround->SetPosition({ 0,0,50 });
	
	float radius = 500.0f;
	float angle[200] = {};

	
	camera->SetEye({ 0, 10, 0 });

	OBJBack->SetScale({ 6.0f,6.0f,6.0f });
#pragma endregion 描画初期化処理

	int counter = 0; // アニメーションの経過時間カウンター

	//int scene = 0;
	int scene = 1;
	
	//スカイドーム
	XMFLOAT3 skyPos = OBJBack->GetPosition();

	//コア係
	XMFLOAT3 CoaRotA = {};
	
	int coaHit = 3000;

	//音
	Audio* audio = Audio::GetInstance();
	audio->Initialize();
	audio->LoadWave("thunder.wav");


	// 雲関係
	XMFLOAT3 cloudPos = objCloud->GetPosition();
	
	XMFLOAT3 cloudRot = objCloud->GetRotation();
	XMFLOAT3 playerRe = { 1280 - 128,128,0 };
	XMFLOAT2 raderP = {};
	float rot = 0.0f;
	spritePlayerRe->SetAnchorpoint({ 0.5f,0.5f });
	
	float jamp = 10.0f;
	int jampFlag = 0;
	// カメラ関係 camera
	bool dirty = false;
	float angleX = 0;
	float angleY = 0;
	float scaleX = 1.0f / (float)WinApp::window_width;
	float scaleY = 1.0f / (float)WinApp::window_height;
	bool viewDirty = false;
	float distance = 20.0f;
	XMMATRIX matRot = DirectX::XMMatrixIdentity();
	int ffff = 0;
	float tortalangleX = 0;
	float tortalangleY = 0;
	
	
	// 追加回転分の回転行列を生成
	XMMATRIX matRotNew_ = XMMatrixIdentity();
	//matRotNew *= XMMatrixRotationY(-angleY);
	matRotNew_ *= XMMatrixRotationX(-angleX);

	matRot = matRotNew_ * matRot;

	// 注視点から視点へのベクトルと、上方向ベクトル
	XMVECTOR vTargetEye_ = { 0.0f, 0.0f, -distance, 1.0f };
	XMVECTOR vUp_ = { 0.0f, 1.0f, 0.0f, 0.0f };

	// ベクトルを回転
	vTargetEye_ = XMVector3TransformNormal(vTargetEye_, matRot);
	vUp_ = XMVector3TransformNormal(vUp_, matRot);

	//XMVector3TransformNormal に差し替えることで平行移動以外を反映

	// 長さ
	float length_ = 0.0f;

	XMFLOAT3 target1_ = camera->GetTarget();
	camera->SetEye({ target1_.x + vTargetEye_.m128_f32[0], target1_.y + vTargetEye_.m128_f32[1], target1_.z + vTargetEye_.m128_f32[2] });
	camera->SetUp({ vUp_.m128_f32[0], vUp_.m128_f32[1], vUp_.m128_f32[2] });

	// 注視点からずらした位置に視点座標を決定
	XMFLOAT3 target2_ = camera->GetTarget();
	XMFLOAT3 eye_ = camera->GetEye();

	XMFLOAT3 fTargetEye_ = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 fTargetEye2_ = { 0.0f, 0.0f, 0.0f };

	// 大きさ計算
	length_ = sqrtf(pow(target2_.x - eye_.x, 2) + pow(target2_.y - eye_.y, 2) + pow(target2_.z - eye_.z, 2));
	fTargetEye_.x = eye_.x - target2_.x;
	fTargetEye_.y = eye_.y - target2_.y;
	fTargetEye_.z = eye_.z - target2_.z;

	fTargetEye_.x /= length_;
	fTargetEye_.y /= length_;
	fTargetEye_.z /= length_;

	fTargetEye2_ = fTargetEye_;

	fTargetEye2_.x *= 14;
	fTargetEye2_.y *= 14;
	fTargetEye2_.z *= 14;

	fTargetEye_.x *= 17;
	fTargetEye_.y *= 17;
	fTargetEye_.z *= 17;

	objCloud->SetScale({ 5.0f, 5.0f, 5.0f });

	cloudPos = { target2_.x + fTargetEye_.x, target2_.y + fTargetEye_.y - 1.5f, target2_.z + fTargetEye_.z };

	objCloud->SetPosition(cloudPos);
	camera->SetEye({ cloudPos.x + vTargetEye_.m128_f32[0], cloudPos.y + vTargetEye_.m128_f32[1] + 17, cloudPos.z + vTargetEye_.m128_f32[2] });
	camera->SetTarget(cloudPos);

	while (true)  // ゲームループ
	{
#pragma region ウィンドウメッセージ処理
		if (winApp->ProcessMessage()) {
			break;
		}
#pragma endregion ウィンドウメッセージ処理

#pragma region DirectX毎フレーム処理
		// DirectX毎フレーム処理　ここから

		if (scene == 0)
		{
			if (input->TriggerMouseLeft())
			{
				scene = 1;

			}
			if (input->PushKey(DIK_ESCAPE))
			{
				break;
			}
		}

		if (scene == 1)
		{
			//SetCursorPos(860, 440);

			CoaRotA.y += 0.3f;
			
			OBJInCoa->SetRotation(CoaRotA);
		

			const int cycle = 540; // 繰り返しの周期
			counter++;
			counter %= cycle; // 周期を超えたら0に戻る
			float scale = (float)counter / cycle; // [0,1]の数値

			scale *= 360.0f;
			OBJInCoa->SetModel(inCoa);

			// マウスの入力を取得
			Input::MouseMove mouseMove = input->GetMouseMove();
			float dy = mouseMove.lX * scaleY;
			angleY = -dy * XM_PI;
			tortalangleY += angleY;
			float dx = mouseMove.lY * scaleX;
			angleX = -dx * XM_PI;
			tortalangleX += angleX;

			XMFLOAT3 oldCamera = camera->GetTarget();
			XMFLOAT3 oldCloudPos = cloudPos;
		
			XMFLOAT3 oldCameraEye = camera->GetEye();

			// ボタンが押されていたらカメラを並行移動させる
			if (input->PushKey(DIK_D))
			{
				XMVECTOR move = { 1.0f, 0, 0, 0 };
				move = XMVector3TransformNormal(move, matRot);
				camera->MoveVector(move);
				

			}
			if (input->PushKey(DIK_A))
			{
				XMVECTOR move = { -1.0f, 0, 0, 0 };
				move = XMVector3TransformNormal(move, matRot);
				camera->MoveVector(move);
			
			}
			if (input->PushKey(DIK_W))
			{
				XMVECTOR move = { 0, 0, 1.0f, 0 };
				move = XMVector3TransformNormal(move, matRot);
				camera->MoveVector(move);

				
			}
			if (input->PushKey(DIK_S))
			{
				XMVECTOR move = { 0, 0, -1.0f, 0 };
				move = XMVector3TransformNormal(move, matRot);
				camera->MoveVector(move);
				
			}
			if (input->TriggerKey(DIK_SPACE)&& jampFlag==0)
			{
				jampFlag = 1;
				
				audio->PlayWave("thunder.wav", false);

			}
			if (jampFlag == 1)
			{
				XMVECTOR move = { 0, jamp, 0, 0 };
				move = XMVector3TransformNormal(move, matRot);
				camera->MoveVector(move);
				//objCloud->MoveVector(move);
				jamp -= 0.5f;
				if (jamp < -10.0f)
				{
					audio->Stop("thunder.wav");

					jampFlag = 0;
					jamp = 10.0f;
				}
			}
			spritePlayerRe->SetPosition(playerRe);
		
			if (input->PushKey(DIK_ESCAPE))
			{
				break;
			}
			
				// 追加回転分の回転行列を生成
			XMMATRIX matRotNew = XMMatrixIdentity();
			matRotNew *= XMMatrixRotationY(-angleY);
			matRotNew *= XMMatrixRotationX(-angleX);

			matRot = matRotNew * matRot;
			
			// 注視点から視点へのベクトルと、上方向ベクトル
			XMVECTOR vTargetEye = { 0.0f, 0.0f, -distance, 1.0f };
			XMVECTOR vUp = { 0.0f, 1.0f, 0.0f, 0.0f };

			// ベクトルを回転
			vTargetEye = XMVector3TransformNormal(vTargetEye, matRot);
			vUp = XMVector3TransformNormal(vUp, matRot);

			//XMVector3TransformNormal に差し替えることで平行移動以外を反映

			// 長さ
			float length = 0.0f;
			
			XMFLOAT3 target1 = camera->GetTarget();
			camera->SetEye({ target1.x + vTargetEye.m128_f32[0], target1.y + vTargetEye.m128_f32[1], target1.z + vTargetEye.m128_f32[2] });
			camera->SetUp({ vUp.m128_f32[0], vUp.m128_f32[1], vUp.m128_f32[2] });

			// 注視点からずらした位置に視点座標を決定
			XMFLOAT3 target2 = camera->GetTarget();
			XMFLOAT3 eye = camera->GetEye();

			XMFLOAT3 fTargetEye = { 0.0f, 0.0f, 0.0f };
			

			// 大きさ計算
			length = sqrtf(pow(target2.x - eye.x, 2) + pow(target2.y - eye.y, 2) + pow(target2.z - eye.z, 2));
			fTargetEye.x = eye.x - target2.x;
			fTargetEye.y = eye.y - target2.y;
			fTargetEye.z = eye.z - target2.z;

			fTargetEye.x /= length;
			fTargetEye.y /= length;
			fTargetEye.z /= length;

			fTargetEye.x *= 17;
			fTargetEye.y *= 17;
			fTargetEye.z *= 17;

			objCloud->SetScale({ 5.0f, 5.0f, 5.0f });

			cloudPos = { target2.x + fTargetEye.x, target2.y + fTargetEye.y - 1.5f, target2.z + fTargetEye.z };
			
			bool skyHit = Collision::Virtualitys(camera->GetTarget(), skyPos);
			bool UnSkyHit = Collision::UnVirtualitys(camera->GetTarget(), skyPos);

			if (skyHit)
			{
				//objCloud->SetPosition(cloudPos);
				camera->SetEye({ cloudPos.x + vTargetEye.m128_f32[0], cloudPos.y + vTargetEye.m128_f32[1], cloudPos.z + vTargetEye.m128_f32[2] });

				//camera->SetTarget({ cloudPos.x, cloudPos.y,cloudPos.z-17 });
			}
			if (UnSkyHit)
			{
				camera->SetEye(oldCameraEye);
				camera->SetTarget(oldCamera);
				objCloud->SetPosition(oldCloudPos);

			}

			float dis = sqrtf(pow(target2.x - cloudPos.x, 2) + pow(target2.y - cloudPos.y, 2) + pow(target2.z - cloudPos.z, 2));

			objCloud->SetPosition(cloudPos);
		
			if (input->PushKey(DIK_Z))
			{
				cloudRot.y = atan2f(-fTargetEye.x, -fTargetEye.z);
				cloudRot.y *= 180 / PI;
				cloudRot.x = atan2f(-fTargetEye.x, -fTargetEye.z);
				cloudRot.x *= 180 / PI;
				objCloud->SetRotation({ 0.0f, cloudRot.y, 0.0f });
			}
			
			
			if (skyHit)
			{
				if (input->PushKey(DIK_D))
				{
					coraRe.y -= sin(((cloudRot.y + 90) * PI) / 180) * (1.0f / 3.90625f);
					coraRe.x -= cos(((cloudRot.y + 90) * PI) / 180) * (1.0f / 3.90625f);
				}
				if (input->PushKey(DIK_A))
				{
					coraRe.y += sin(((cloudRot.y + 90) * PI) / 180) * (1.0f / 3.90625f);
					coraRe.x += cos(((cloudRot.y + 90) * PI) / 180) * (1.0f / 3.90625f);

				}
				if (input->PushKey(DIK_W))
				{
					coraRe.y -= sin((cloudRot.y * PI) / 180) * (1.0f / 3.90625f);
					coraRe.x -= cos((cloudRot.y * PI) / 180) * (1.0f / 3.90625f);
				}
				if (input->PushKey(DIK_S))
				{
					coraRe.y += sin((cloudRot.y * PI) / 180) * (1.0f / 3.90625f);
					coraRe.x += cos((cloudRot.y * PI) / 180) * (1.0f / 3.90625f);
				}
			
			}
			spriteCoraRe->SetPosition(coraRe);

		
			/*rot = atan2f(-fTargetEye.x, -fTargetEye.z);
			rot *= 180 / PI;*/
			 spritePlayerRe->SetRotation(cloudRot.y + 90);
		
			 char str[256] = {};

			 sprintf_s(str, "cameraTarget.x:%f cameraTarget.y:%f cameraTarget.z:%f", target1.x, target1.y, target1.z);
			 debTxt->Print(str,0,0,2 );
			 char str2[256] = {};
			
			 sprintf_s(str2, "cameraEye.x:%f cameraEye.y:%f cameraEye.z:%f", camera->GetEye().x, camera->GetEye().y, camera->GetEye().z);
			 debTxt->Print(str2, 0, 32, 2);

			 char str3[256] = {};
			 sprintf_s(str3, "anglex:%f tortalX:%f ", angleX, tortalangleX);
			 debTxt->Print(str3, 0, 64, 2);

			 char str4[256] = {};
			 sprintf_s(str4, "angleY:%f tortalY:%f ", angleY, tortalangleY);
			 debTxt->Print(str4, 0, 96, 2);
			 char str5[256] = {};
			 sprintf_s(str5, "distance:%f ", dis);
			 debTxt->Print(str5, 0, 96+32, 2);

			if (coaHit <= 0)
			{
				scene = 2;
			}

		
		}

		if (scene == 2)
		{


			if (input->PushKey(DIK_ESCAPE))
			{
				break;
			}
			if (input->TriggerMouseLeft())
			{
				break;
			}
		}
		if (scene == 3)
		{
			if (input->PushKey(DIK_ESCAPE))
			{
				break;
			}
		}
		
		input->Update();
	
		camera->Update();
		
		OBJInCoa->Update();
		
		OBJBack->Update();
		objGround->Update();
	
		objCloud->Update();
		objTerritory->Update();
		spritePlayerRe->Update();
		spriteCoraRe->Update();
		

		// DirectX毎フレーム処理　ここまで
#pragma endregion DirectX毎フレーム処理

#pragma region グラフィックスコマンド

		dxCommon->PreDraw();
		
		Object3d::PreDraw(dxCommon->GetCmdList());
		if (scene == 0)
		{
			

			objGround->Draw();

			OBJInCoa->Draw();


			objTerritory->Draw();
			objCloud->Draw();

		}
		if (scene == 1)
		{
		//	Object3d::PreDraw(dxCommon->GetCmdList());
		
			objGround->Draw();
			OBJInCoa->Draw();
		
			
			objTerritory->Draw();
			objCloud->Draw();

		}
		if (scene == 2)
		{
			
			

		}
		if (scene == 3)
		{
		
		}
		Object3d::PostDraw();

		spriteCommon->PreDraw();

		if (scene == 0)
		{
			spriteReader->Draw();
			spriteCoraRe->Draw();
			spritePlayerRe->Draw();
		
		}
		if (scene == 1)
		{


		
			spriteReader->Draw();
			spriteCoraRe->Draw();
			spritePlayerRe->Draw();

		}
		if (scene == 2)
		{
		
		}
		if (scene == 3)
		{

		}

		debTxt->DrawAll();
		// ４．描画コマンドここまで
		dxCommon->PostDraw();
	}
	

#pragma region WindowsAPI後始末
	winApp->Finalize();
#pragma endregion WindowsAPI後始末
	delete input;
	delete winApp;
	delete spriteCommon;
	delete inCoa;
	delete modelChr;
	delete OBJInCoa;
	delete objCloud;
	return 0;
}