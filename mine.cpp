#include"mine.h"
#include"DxLib.h"
#include"Transform.h"
#include"enemy.h"

#pragma region �R���g���X�^�E�f�X�g���N�^
//�R���g���X�^
Mine::Mine()
{
		rand = 0;
		damage_flag = false;
		explosion_r = 0;
		mine_flag = false;
		def_explosion_time = 0;
		def_bombs_time = 0;
	for (int i = 0; i < 10; i++)
	{
		transform[i].x = 0;
		transform[i].xr = 0;
		transform[i].y = 0;
		transform[i].yr = 0;
		explosion_time[i] = 0;
		explosion_flag[i] = 0;
		bombs_time[i] = 0;
		exising_flag[i] = 0;
	}

}

//�f�X�g���N�^
Mine::~Mine()
{
}
#pragma endregion

#pragma region ����

//�t���O��true�ɂȂ����烉���_�������(0�`rand_num)
//�����_����rand_div��艺��������
//�󂢂Ă��郉�x����T���č��W�ƃt���O��������

void Mine::form(Transform transForm,int&frame)
{
	if (mine_flag == true)
	{
		if (rand == frame)
		{
			int i = FlagSerch(exising_flag, 10);
			transform[i].x = transForm.x;
			transform[i].y = transForm.y;
			exising_flag[i] = true;
			explosion_time[i] = def_explosion_time;
			bombs_time[i] = def_bombs_time;
			mine_flag = false;
		}
	}
}
#pragma endregion

#pragma region �����蔻��

//�ݒu��Ԃœ��������甚��������
//�������Ă��鎞�ɓ���������̗͂����炷
//�t���O���g��1�_���[�W�����^���Ȃ��悤�ɂ��Ă���

void Mine::HitBox(Transform transform, int& hp)
{
	for (int i = 0; i < 10; i++)
	{
		if (exising_flag[i] == true && explosion_flag[i] == false && explosion_time[i] < def_explosion_time - 30)
		{
			if (this->transform[i].x - this->transform[i].xr < transform.x + transform.xr &&
				this->transform[i].x + this->transform[i].xr > transform.x - transform.xr)
			{
				if (this->transform[i].y - this->transform[i].yr < transform.y + transform.yr &&
					this->transform[i].y + this->transform[i].yr > transform.y - transform.yr)
				{
					explosion_flag[i] = true;
				}

			}

		}

		if (explosion_flag[i] == true)
		{
			if (this->transform[i].x - explosion_r < transform.x + transform.xr &&
				this->transform[i].x + explosion_r > transform.x - transform.xr)
			{
				if (this->transform[i].y - explosion_r < transform.y + transform.yr &&
					this->transform[i].y + explosion_r > transform.y - transform.yr)
				{
					if (damage_flag == false)
					{
						hp--;
					}
					damage_flag = true;
				}
				else
				{
					damage_flag = false;
				}
			}
			else
			{
				damage_flag = false;

			}
		}
	}
}
#pragma endregion

#pragma region ����

//�������Ԃ�0����Ȃ猸�炵0�ɂȂ����甚���t���O��ture�ɂ���
//�����t���O��ture�������甚�����Ԃ����炵��
//�������Ԃ�0�ɂȂ�����e��ϐ���������

void Mine::Move()
{
	for (int i = 0; i < 10; i++)
	{
		if (exising_flag[i] == true && explosion_time[i] > 0)
		{
			explosion_time[i]--;

			if (explosion_time[i] == 0)
			{
				explosion_flag[i] = true;
			}
		}

		if (explosion_flag[i] == true)
		{
			bombs_time[i]--;

			if (bombs_time[i] == 0)
			{
				explosion_flag[i] = false;
				exising_flag[i] = false;
				bombs_time[i] = def_bombs_time;
				explosion_time[i] = def_explosion_time;
			}
		}
	}
}
#pragma endregion

#pragma region �`��

//���݃t���O�Ɣ����t���O�������Ă�����
//���݃t���O�������Ă�����
//�f�o�b�N

void Mine::Draw()
{
	for (int i = 0; i < 10; i++)
	{
		if (exising_flag[i] == true && explosion_flag[i] == true)
		{
			DrawBox((int)transform[i].x - explosion_r, (int)transform[i].y - explosion_r,
				(int)transform[i].x + explosion_r, (int)transform[i].y + explosion_r, GetColor(255, 0, 0), true);
		}
		else if (exising_flag[i] == true)
		{
			DrawBox((int)transform[i].x - transform[i].xr, (int)transform[i].y - transform[i].yr,
				(int)transform[i].x + transform[i].xr, (int)transform[i].y + transform[i].yr, GetColor(255, 255, 255), true);
		}
	}

	DrawFormatString(0, 200, GetColor(255, 255, 255), "mine explosion_time[0]:%d", explosion_time[0]);
	DrawFormatString(0, 220, GetColor(255, 255, 255), "mine bombs_time[0]:%d", bombs_time[0]);
}
#pragma endregion

#pragma region ������

//�\���̂���󂯎���đ��

void Mine::initialize(MimeInitialize& mimeinitialize)
{
	def_explosion_time = mimeinitialize.def_explosion_time;
	def_bombs_time = mimeinitialize.def_bombs_time;
	explosion_r = mimeinitialize.explosion_r;

	for (int i = 0; i < 10; i++)
	{
		transform[i].xr = mimeinitialize.transform_xr;
		transform[i].yr = mimeinitialize.transform_yr;
	}
}
#pragma endregion

#pragma region �Z�b�^�[

void Mine::SetMineFlag(bool flag)
{
	mine_flag = flag;
}

void Mine::SetRand(int end_frame)
{
	rand = GetRand(end_frame);
}
#pragma endregion