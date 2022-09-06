#include "ObjManager.h"

ObjManager::ObjManager()
{
}

ObjManager::~ObjManager()
{
	safe_delete(back);
	safe_delete(player);
	for (auto x : dog)
	{
		safe_delete(x);
	}
	for (auto x : dream_dog)
	{
		safe_delete(x);
	}
	safe_delete(river);
	safe_delete(thieves);
}

void ObjManager::Initialize(Input* input)
{
	// ���͏��擾
	this->input = input;
	// �������x
	speed = 6;
	//�����������ǂ���
	hit_Flag = false;
	//���
	limit = 120;
	//���G����
	invincibleCount = limit;
	//�����Ă��邩
	life_Flag = false;
	second_Flag = false;
	startTime = 0;
	//�ŏ��l
	min = 0;
	//�ő�l
	doglimit = 150;
	doglimit1 = 150;
	riverlimit = 150;
	thievelimit = 150;
	// �w�i
	back = new BackGround();
	back->Initialize();
	// �v���C���[
	player = new Player();
	player->Initialize(input);
	river = new River();
	river->Initialize();
	thieves = new Thieves();
	thieves->Initialize();

	for (int i = 0, size = DOG; i < size; i++)
	{
		dog[i] = new Dog();
		dog[i]->Initialize();
		dog[i]->SetPosition({ dog[i]->GetPosition().x - 300,dog[i]->GetPosition().y });
	}

	for (int i = 0, size = D_DOG; i < size; ++i)
	{
		dream_dog[i] = new Dog();
		dream_dog[i]->Initialize();
	}

	goal = 50000;
}

void ObjManager::Update()
{
	//�v���C���[�|�W�V����
	XMFLOAT2 P_pos = player->GetPosition();
	XMFLOAT2 riverPos = { river->GetPosition().x + 310, river->GetPosition().y + 400 };

	// ����
	speed += 0.01f;
	min += 0.01f;

	doglimit -= 1;
	doglimit1 -= 1;
	riverlimit -= 1;
	thievelimit -= 1;

	// �v���C���[���Q���爫�����[�h��
	if (player->GetSleep())
	{
		back->SetSleep();

		// ���Ŋo��
		if (input->TriggerKey(DIK_LEFT) && player->GetSleep())
		{
			int muteki = 3;
			player->Awake();
			back->SetAwake();
			doglimit = muteki;
			doglimit1 = muteki;
			riverlimit = muteki;
			thievelimit = muteki;
			for (int i = 0; i < DOG; ++i)
			{
				dog[i]->ReStart();
				life_Flag = false;
			}
			thieves->Spawn();
			river->ReStart();
		}
	}

	//�v���C���[�̈ړ�����
	if (P_pos.y >= 620)
	{
		P_pos.y = 620;
		player->SetPosition(P_pos);
	}
	else if (P_pos.y <= 305)
	{
		P_pos.y = 305;
		player->SetPosition(P_pos);
	}

	//����������J�E���g������
	if (hit_Flag)
	{
		invincibleCount--;
		hit_Flag = InvincibleTime(hit_Flag);
		damage = true;
	}

	// ���ꂼ��̃I�u�W�F�N�g�̃X�s�[�h��ύX
	{
		back->SetSpeed(speed);
		river->SetSpeed(speed);
		for (int i = 0, size = DOG; i < size; ++i)
		{
			dog[i]->SetSpeed(speed);
		}
		if (player->GetSleep())
		{
			for (int i = 0, size = D_DOG; i < size; ++i)
			{
				dream_dog[i]->SetSpeed(speed);
			}
		}
	}

	//�����蔻��
	{
		//�v���C���[�|�W�V����
		XMFLOAT2 P_pos = player->GetPosition();
		//��
		for (int i = 0, size = DOG; i < size; ++i)
		{
			bool CheckPlayer2Dog = Collision::CheckBox2D(P_pos, dog[i]->GetPosition(),
				{ 50,50 }, { 50,50 }, 1.0f, 1.0f);

			if (CheckPlayer2Dog && !hit_Flag)
			{
				SpeedDown();
				hit_Flag = InvincibleTime(hit_Flag);
			}

			min = MinElement(dog[i], DOG);

			if (dog[1]->GetPosition().x >= 2660)
			{
				doglimit = RandomStart(doglimit);
				dog[i]->ReStart();
			}
			
			if (player->GetSleep())
			{
				dog[i]->ReStart();
			}
		}

		//��(����)
		for (int i = 0, size = D_DOG; i < size; ++i)
		{
			bool CheckPlayer2DDog = Collision::CheckBox2D(P_pos, dream_dog[i]->GetPosition(),
				{ 50,50 }, { 50,50 }, 1.0f, 1.0f);

			if (CheckPlayer2DDog && !hit_Flag)
			{
				SpeedDown();
				hit_Flag = InvincibleTime(hit_Flag);
			}

			min = MinElement(dream_dog[i], D_DOG);

			if (min >= 1280)
			{
				for (int i = 0, size = D_DOG; i < size; ++i)
				{
					doglimit1 = RandomStart(doglimit1);
					dream_dog[i]->ReStart();
				}
			}

			if (!player->GetSleep())
			{
				dream_dog[i]->ReStart();
			}
		}

		//��
		XMFLOAT2 riverPos = { river->GetPosition().x + 310, river->GetPosition().y + 400 };
		bool CheckPlayer2River = Collision::CheckBox2D(P_pos, riverPos, { 100,100 }, { 200,420 }, 1.0f, 1.0f);
		bool Updown = river->GetUpdown();

		if (CheckPlayer2River && Updown)
		{
			P_pos.y -= speed / 1.5f;
			player->SetPosition(P_pos);
		}
		else if (CheckPlayer2River && !Updown)
		{
			P_pos.y += speed / 1.5f;
			player->SetPosition(P_pos);
		}

		if (player->GetSleep())
		{
			if (riverPos.x >= 1480)
			{
				riverlimit = RandomStart(riverlimit);
				river->ReStart();
			}
		}
		else
		{
			if (riverPos.x >= 1480)
			{
				riverlimit = RandomStart(riverlimit);
				river->ReStart();
			}
		}

		//����(�ʏ�)
		for (auto& x : thieves->GetPosition())
		{
			bool CheckPlayer2thieves = Collision::CheckBox2D(P_pos, { x.x - 80,x.y }, { 80,80 }, { 0.5f,1.0f }, 1.0f, 1.0f);

			if (CheckPlayer2thieves && !hit_Flag)
			{
				SpeedDown();
				hit_Flag = InvincibleTime(hit_Flag);
			}

			if (!player->GetSleep())
			{
				if (x.x >= 1550.0f)
				{
					thievelimit = RandomStart(thievelimit);
					thieves->Spawn();
				}
			}
			else
			{
				if (x.x >= 1550.0f)
				{
					thievelimit = RandomStart(thievelimit);
					thieves->Spawn();
				}
			}
		}

		static std::vector<XMFLOAT2> signPos;
		signPos = back->GetSignPos();
		for (int i = 0; i < 5; i++)
		{
			if (Collision::CheckBox2D(player->GetPosition(), signPos[i], { 100, 100 }, { 250, 250 }))
			{
				sign[i] = true;
			}
		}
	}
	if (sign[0] && sign[1] && sign[2] && sign[3] && sign[4])
	{
		signClear = true;
	}

	// �S�[��
	goal -= speed;
	if (goal <= 0)
	{
		clear = true;
	}
	// �Q�[���I�[�o�[
	over = back->GetOver();

	// �X�V
	back->Update();
	player->Update();

	//��
	if (riverlimit <= 0)
	{
		river->Update();
	}

	//����(�ʏ�)
	if (thievelimit <= 0)
	{
		thieves->Update(speed);
	}

	//��
	if (!player->GetSleep() && doglimit <= 0)
	{
		for (int i = 0, size = DOG; i < size; ++i)
		{
			dog[i]->Update();
		}

		if (!life_Flag)
		{
			for (int i = 0, size = D_DOG; i < size; ++i)
			{
				dream_dog[i]->ReStart();
				life_Flag = true;
			}
		}
	}

	if (player->GetSleep() && doglimit1 <= 0)
	{
		for (int i = 0, size = D_DOG; i < size; ++i)
		{
			dream_dog[i]->Update();
		}

		if (!life_Flag)
		{
			for (int i = 0, size = DOG; i < size; ++i)
			{
				dog[i]->ReStart();
				life_Flag = true;
			}
		}
	}
}

void ObjManager::SpeedDown()
{
	//���x��1/2�ɂ���
	speed /= 2;
}

bool ObjManager::InvincibleTime(bool hit_Flag)
{
	hit_Flag = true;

	if (invincibleCount <= 0)
	{
		invincibleCount = limit;
		hit_Flag = false;
	}

	return hit_Flag;
}

int ObjManager::RandomStart(int count)
{
	int num = rand() % 60;

	count = num;

	return count;
}

float ObjManager::MinElement(Dog* array, float size)
{
	float min = dream_dog[0]->GetPosition().x;

	for (int i = 1; i < size; ++i)
	{
		float num = dream_dog[i]->GetPosition().x;

		if (min > num)
		{
			min = num;
		}
	}

	return min;
}

void ObjManager::Draw()
{
	// �`��
	back->Draw();
	river->Draw();
	thieves->Draw(player->GetSleep());
	for (int i = 0, size = DOG; i < size; ++i)
	{
		dog[i]->Draw(player->GetSleep());
	}

	for (int i = 0, size = D_DOG; i < size; ++i)
	{
		dream_dog[i]->Draw(player->GetSleep());
	}

	if (hit_Flag)
	{
		if (invincibleCount % 30 >= 15)
		{
			player->Draw();
		}
	}
	else
	{
		player->Draw();
	}
}
