#include "Player.h"

void Player::Initialize(Input* input_)
{
	assert(input_);
	playerModel = Model::LoadFromOBJ("player");
	bulletModel = Model::LoadFromOBJ("playerBullt");
	this->input = input_;
	playerObj = Object3d::Create();
	playerObj->SetModel(playerModel);
	playerPos = { 0,10,-417 };
	playerObj->SetPosition(playerPos);
	playerObj->SetScale({ 2.0f, 2.0f, 2.0f });
	playerObj->Update();

	for (int i = 0; i < 30; i++)
	{
		bullet[i] = new Bullet();
		bullet[i]->obj = Object3d::Create();
		bullet[i]->obj->SetModel(bulletModel);
		bullet[i]->obj->SetScale({ 3.0,3.0,3.0 });
		bullet[i]->flag = 0;
		bullet[i]->timer = 200;
	}
}

void Player::GameInitialize()
{
	jamp = 7;
	jampFlag = 0;
	damegeFlag = 0;
	stageFlag = 0;
	bulletFlag = 0;
	damegeTimer = 20;
	damegejamp = 13;
	addAngle = 0;
	speed = 1.0f;
	matRot = DirectX::XMMatrixIdentity();
	playerPos = { 0,10,-417 };
	playerObj->SetPosition(playerPos);
	playerObj->SetScale({ 2.0f, 2.0f, 2.0f });
	playerObj->Update();
	life = 20;
	for (int i = 0; i < 30; i++)
	{
		bullet[i]->obj->SetScale({ 3.0,3.0,3.0 });
		bullet[i]->flag = 0;
		bullet[i]->timer = 200;
	}
	Update();
}

void Player::Update()
{

	playerObj->SetPosition(playerPos);
	playerObj->SetRotation(playerRot);
	PlayerDamege();
	BulletUpdate();
	playerObj->Update();
	
}

void Player::PlayerMove()
{
	//プレイヤーの動き
	oldPlayerPos = playerPos;
	if (input->PushKey(DIK_LSHIFT))
	{
		speed = 5.0f;
	}
	if (input->PushKey(DIK_LSHIFT) == 0)
	{
		speed = 1.0f;
	}
	if (input->PushKey(DIK_D))
	{
		XMVECTOR move = { speed, 0, 0, 0 };
		move = XMVector3TransformNormal(move, matRot);

		playerPos.x += move.m128_f32[0];
		playerPos.y += move.m128_f32[1];
		playerPos.z += move.m128_f32[2];

	}
	if (input->PushKey(DIK_A))
	{
		XMVECTOR move = { -speed, 0, 0, 0 };

		move = XMVector3TransformNormal(move, matRot);

		playerPos.x += move.m128_f32[0];
		playerPos.y += move.m128_f32[1];
		playerPos.z += move.m128_f32[2];

	}
	if (input->PushKey(DIK_W))
	{
		XMVECTOR move = { 0, 0, speed, 0 };

		move = XMVector3TransformNormal(move, matRot);

		playerPos.x += move.m128_f32[0];
		playerPos.y += move.m128_f32[1];
		playerPos.z += move.m128_f32[2];

	}
	if (input->PushKey(DIK_S))
	{
		XMVECTOR move = { 0, 0, -speed, 0 };

		move = XMVector3TransformNormal(move, matRot);

		playerPos.x += move.m128_f32[0];
		playerPos.y += move.m128_f32[1];
		playerPos.z += move.m128_f32[2];

	}

	if (input->TriggerKey(DIK_SPACE) && jampFlag == 0 && damegeFlag == 0)
	{
		jampFlag = 1;

	}
	if (jampFlag == 1)
	{
		XMVECTOR move = { 0, jamp, 0, 0 };
		move = XMVector3TransformNormal(move, matRot);
		playerPos.x += move.m128_f32[0];
		playerPos.y += move.m128_f32[1];
		playerPos.z += move.m128_f32[2];
		jamp -= 0.5f;
		if (jamp < -7.0f)
		{
			jampFlag = 0;
			jamp = 7.0f;
		}
	}
	if (input->PushKey(DIK_D) && input->PushKey(DIK_A) == 0 && input->PushKey(DIK_W) == 0 && input->PushKey(DIK_S) == 0)
	{
		addAngle = 89.550f;

	}
	if (input->PushKey(DIK_D) == 0 && input->PushKey(DIK_A) && input->PushKey(DIK_W) == 0 && input->PushKey(DIK_S) == 0)
	{
		addAngle = -89.550f;
	}
	if (input->PushKey(DIK_D) == 0 && input->PushKey(DIK_A) == 0 && input->PushKey(DIK_W) && input->PushKey(DIK_S) == 0)
	{
		addAngle = 0;
	}
	if (input->PushKey(DIK_D) == 0 && input->PushKey(DIK_A) == 0 && input->PushKey(DIK_W) == 0 && input->PushKey(DIK_S))
	{
		addAngle = 89.550f * 2;
	}

	if (input->PushKey(DIK_D) && input->PushKey(DIK_A) == 0 && input->PushKey(DIK_W) == 0 && input->PushKey(DIK_S))
	{
		addAngle = (89.550f * 2) - (89.550f / 2);
	}

	if (input->PushKey(DIK_D) == 0 && input->PushKey(DIK_A) && input->PushKey(DIK_W) == 0 && input->PushKey(DIK_S))
	{
		addAngle = (89.550f * 2) + (89.550f / 2);
	}

	if (input->PushKey(DIK_D) && input->PushKey(DIK_A) == 0 && input->PushKey(DIK_W) && input->PushKey(DIK_S) == 0)
	{
		addAngle = (89.550f / 2);
	}

	if (input->PushKey(DIK_D) == 0 && input->PushKey(DIK_A) && input->PushKey(DIK_W) && input->PushKey(DIK_S) == 0)
	{
		addAngle = -(89.550f / 2);
	}


	//弾の処理
	if (input->TriggerMouseLeft())
	{
		for (int i = 0; i < 30; i++)
		{
			if (i == 0 && bullet[i]->flag == 0)
			{
				bullet[i]->flag = 1;
				bullet[i]->angle = matRot;
				bullet[i]->pos = playerPos;
				bullet[i]->timer = 200;
				break;
			}
			else if (i>=1&&bullet[i - 1]->flag == 1 && bullet[i]->flag == 0)
			{
				bullet[i]->flag = 1;
				bullet[i]->angle = matRot;
				bullet[i]->pos = playerPos;
				bullet[i]->timer = 200;
				break;
			}
		}
	}

}

void Player::PlayerDamege()
{
	//プレイヤーのダメージ処理
	if (damegeFlag == 1)
	{
		stageFlag = true;
	}
	if (stageFlag == true)
	{
		XMVECTOR move = { 0, damegejamp, 0, 0 };
		move = XMVector3TransformNormal(move, matRot);
		playerPos.x += move.m128_f32[0];
		playerPos.y += move.m128_f32[1];
		playerPos.z += move.m128_f32[2];

		damegejamp -= 0.5f;
		if (damegejamp < -13.0f)
		{
			if (damegeFlag == 1)
			{
				damegeFlag = 0;

			}
			stageFlag = false;
			damegejamp = 13.0f;
		}
	}
	if (damegeFlag == 2)
	{
		bulletFlag = true;
		
	}
	if (bulletFlag == true)
	{
		
		damegeTimer--;
		if (damegeTimer <= 0)
		{
			if (damegeFlag == 2)
			{
				damegeFlag = 0;

			}
			bulletFlag = 0;
			damegeTimer = 20;
		}
	}
}

void Player::BulletUpdate()
{
	//弾の更新
	for (int i = 0; i < 30; i++)
	{
		if (bullet[i]->flag == 1)
		{
			bullet[i]->timer--;
			if (bullet[i]->timer < 1)
			{
				bullet[i]->flag = 0;
			}
			XMVECTOR move = { 0, 0, 30, 0 };
			move = XMVector3TransformNormal(move, bullet[i]->angle);
			
			bullet[i]->pos.x += move.m128_f32[0];
			bullet[i]->pos.y += move.m128_f32[1];
			bullet[i]->pos.z += move.m128_f32[2];
			bullet[i]->obj->SetPosition(bullet[i]->pos);
		}
		bullet[i]->obj->Update();
	}

}

void Player::Delete()
{
	
	delete playerModel;
	delete bulletModel;
	delete playerObj;
	for (int i = 0; i < 30; i++)
	{
		delete bullet[i]->obj;
	}
}

void Player::Draw(int scene)
{

	if (scene == 1)
	{
		if(damegeTimer%2== 0)playerObj->Draw();
		for (int i = 0; i < 30; i++)
		{
			if (bullet[i]->flag == 1)
			{
				bullet[i]->obj->Draw();
			}

		}
	}
	if (scene == 6)
	{
		playerObj->Draw();
	}

	
}
