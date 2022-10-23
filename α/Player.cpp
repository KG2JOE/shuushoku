#include "Player.h"

void Player::Initialize(Input* input_)
{
	assert(input_);

	this->input = input_;
	playerObj = Object3d::Create();
	playerObj->SetModel(playerModel);
	playerPos = { 0,5,-417 };
	playerObj->SetPosition(playerPos);
	playerObj-> SetScale({ 5.0f, 5.0f, 5.0f });
	playerObj->Update();
}

void Player::Update()
{

	playerObj->SetPosition(playerPos);
	playerObj->SetRotation(playerRot);
	PlayerDamege();

	playerObj->Update();
	//input->Update();

}

void Player::PlayerMove()
{
#pragma region playerMove
	oldPlayerPos = playerPos;
	if (input->PushKey(DIK_D))
	{
		XMVECTOR move = { 1.0f, 0, 0, 0 };
		move = XMVector3TransformNormal(move, matRot);
		
		playerPos.x += move.m128_f32[0];
		playerPos.y += move.m128_f32[1];
		playerPos.z += move.m128_f32[2];
		
	}
	if (input->PushKey(DIK_A))
	{
		XMVECTOR move = { -1.0f, 0, 0, 0 };

		move = XMVector3TransformNormal(move, matRot);
		
		playerPos.x += move.m128_f32[0];
		playerPos.y += move.m128_f32[1];
		playerPos.z += move.m128_f32[2];
	
	}
	if (input->PushKey(DIK_W))
	{
		XMVECTOR move = { 0, 0, 1.0f, 0 };

		move = XMVector3TransformNormal(move, matRot);
		
		playerPos.x += move.m128_f32[0];
		playerPos.y += move.m128_f32[1];
		playerPos.z += move.m128_f32[2];
	
	}
	if (input->PushKey(DIK_S))
	{
		XMVECTOR move = { 0, 0, -1.0f, 0 };

		move = XMVector3TransformNormal(move, matRot);
		
		playerPos.x += move.m128_f32[0];
		playerPos.y += move.m128_f32[1];
		playerPos.z += move.m128_f32[2];
		
	}

	if (input->TriggerKey(DIK_SPACE) && jampFlag == 0&&damegeFlag ==0)
	{
		jampFlag = 1;

		//audio->PlayWave("thunder.wav", false);

	}
	if (jampFlag == 1)
	{
		XMVECTOR move = { 0, jamp, 0, 0 };
		move = XMVector3TransformNormal(move, matRot);
		playerPos.x += move.m128_f32[0];
		playerPos.y += move.m128_f32[1];
		playerPos.z += move.m128_f32[2];
		//camera->SetTarget(playerPos);
		//objCloud->MoveVector(move);
		jamp -= 0.5f;
		if (jamp < -7.0f)
		{
			//audio->Stop("thunder.wav");

			jampFlag = 0;
			jamp =7.0f;
		}
	}
#pragma endregion playerMove
}

void Player::PlayerDamege()
{
	if (damegeFlag == 1)
	{
		XMVECTOR move = { 0, damegejamp, 0, 0 };
		move = XMVector3TransformNormal(move, matRot);
		playerPos.x += move.m128_f32[0];
		playerPos.y += move.m128_f32[1];
		playerPos.z += move.m128_f32[2];
		//camera->SetTarget(playerPos);
		//objCloud->MoveVector(move);
		damegejamp -= 0.5f;
		if (damegejamp < -13.0f)
		{
			//audio->Stop("thunder.wav");

			damegeFlag = 0;
			damegejamp = 13.0f;
		}
	}
}

void Player::Draw()
{
	playerObj->Draw();
}
