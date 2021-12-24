#include<DxLib.h>
#include"enemy.h"
#include"subboss.h"
#include"Transform.h"
#include<math.h>



#pragma region ����

//�t�@�C���I�[�v������
//�t�@�C���|�C���^���󂯎���Ċe�ϐ��ɑ������
//EOF�ɂȂ�����c��̕ϐ��͂��ׂ�0����

//���C��
void SubBossForm(const char* file_name, int max, SubBoss& sub_boss)
{
	FILE* fp;
	fopen_s(&fp, file_name, "r");

	if (fp != NULL)
	{
		sub_boss.form(fp);
		fclose(fp);
	}
}

void SubBoss::form(FILE* fp)
{
	if (fscanf_s(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%lf,%lf,%lf,%lf,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%d,%d,%d,%d,%d"
		, &enemy_type, &appear_time, &shot_time, &hp, &transform.xr, &transform.yr, &x_speed, &y_speed, &end_frame, &start_x, &start_y, &end_x, &end_y, &move_time, &move_end_frame,
		&move_end_x[0], &move_end_y[0],
		&move_end_x[1], &move_end_y[1],
		&move_end_x[2], &move_end_y[2],
		&move_end_x[3], &move_end_y[3],
		&move_end_x[4], &move_end_y[4],
		&move_end_x[5], &move_end_y[5],
		&move_end_x[6], &move_end_y[6],
		&mime_initialize.transform_xr, &mime_initialize.transform_yr, &mime_initialize.explosion_r, &mime_initialize.def_explosion_time, &mime_initialize.def_bombs_time)
		!= EOF)
	{
		mine->initialize(mime_initialize);
	}
	else
	{
		enemy_type = 0;
		transform.xr = 0;
		transform.yr = 0;
		hp = 0;
		x_speed = 0;
		y_speed = 0;
		shot_time = 0;
		end_frame = 0;
		start_x = 0;
		end_x = 0;
		end_y = 0;
		appear_time = 0;
		move_time = 0;
		move_end_frame = 0;

		for (int i = 0; i < 7; i++)
		{
			move_end_x[i] = 0;
			move_end_y[i] = 0;
		}

		mime_initialize.transform_yr = 0;
		mime_initialize.transform_xr = 0;
		mime_initialize.def_bombs_time = 0;
		mime_initialize.def_explosion_time = 0;
		mime_initialize.explosion_r = 0;
	}

	move_start_x[0] = end_x;
	move_start_y[0] = end_y;
	transform.x = start_x;
	transform.y = start_y;
	exising_flag = false;
	damage_flag = false;
	fast_move_flag = false;

	move_flag = false;
	frame = 0;
	move_num = 0;
	move_frame = 0;
	for (int i = 1; i < 8; i++)
	{
		move_start_x[i] = move_end_x[i - 1];
		move_start_y[i] = move_end_y[i - 1];
	}

	move_end_x[7] = move_start_x[0];
	move_end_y[7] = move_start_y[0];
	def_move_time = move_time;
	def_shot_time = shot_time;
	hp = 100;
}
#pragma endregion

#pragma region ����

//�o�����Ԏ��Ԃ����炵0�ɂȂ�����ŏ��̈ړ�������
//�e��ł����Ă��ׂď�������Ɉړ�����
//�n���ƒe�̓���������

void SubBoss::Move(Player& player)
{
	//�o�����ԊǗ�
	if (appear_time == 0)
	{
		fast_move_flag = true;
		exising_flag = true;
		appear_time = -1;
	}
	else if (appear_time != 0 && appear_time != -1)
	{
		appear_time--;
	}

	if (enemy_type != 2)
	{
		if (exising_flag == true)
		{
			//�ŏ��̈ړ�
			if (fast_move_flag == true)
			{
				frame++;
				//�C�[�W���O
				transform.x = start_x + (end_x - start_x) * easeInSine((double)frame / (double)end_frame);
				transform.y = start_y + (end_y - start_y) * easeInSine((double)frame / (double)end_frame);

				if (frame == end_frame)
				{
					fast_move_flag = false;
				}
			}

			//�ړ�
			if (fast_move_flag == false)
			{
				if (move_time == 1)
				{//�n���ݒu�t���t�𗧂Ă�
					mine->SetMineFlag(true);
					mine->SetRand(move_end_frame);
				}

				if (move_flag == true)
				{
					if (move_time > 0)
					{
						move_time--;
					}

					if (move_time == 0)
					{
						move_frame++;
						//�C�[�W���O
						transform.x = move_start_x[move_num] + (move_end_x[move_num] - move_start_x[move_num]) * easeInSine((double)move_frame / (double)move_end_frame);
						transform.y = move_start_y[move_num] + (move_end_y[move_num] - move_start_y[move_num]) * easeInSine((double)move_frame / (double)move_end_frame);

						if (move_frame == move_end_frame)
						{
							move_flag = false;
							move_num++;
							move_time = def_move_time;
							move_frame = 0;
							shot_time = def_shot_time;

							if (move_num == 8)
							{
								move_num = 0;
							}
						}
					}
				}
			}

			//���ˎ��ԊǗ�
			if (fast_move_flag == false && shot_time > 0 && move_flag == false)
			{
				shot_time--;
			}

			//���ˉ񐔏�����
			Refresh_ReflectionNum(4);

			//�����蔻��
			if (*bullet->GetBulletFlag() == true)
			{
				for (int i = 0; i < 4; i++)
				{
					HitBox(bullet[i].GetTransform(), bullet[i].GetBulletFlag());
				}
			}

			//�e�̐���
			if (shot_time == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					bullet[i].Form(transform, player, x_speed, y_speed);
					damage_flag = true;
				}

				//�p�x��90�x�����炷
				bullet[1].SetAngle(bullet[0].GetAngle() + (DX_PI_F / 2));
				bullet[2].SetAngle(bullet[1].GetAngle() + (DX_PI_F / 2));
				bullet[3].SetAngle(bullet[2].GetAngle() + (DX_PI_F / 2));

				shot_time = -1;
			}

			if (hp <= 0)
			{
				exising_flag = false;
			}


		}
		//�n���̓���
		mine->form(transform, move_frame);
		mine->HitBox(transform, hp);
		mine->Move();

	}

	for (int i = 0; i < 4; i++)
	{
		//�e�̓���
		bullet[i].Move(enemy_type);
	}
}
#pragma endregion

#pragma region �`��

//���݃t���O�������Ă�����`�悷��
//�e�ƒn����`�悷��
//�f�o�b�N

void SubBoss::Draw()
{
	if (exising_flag == true)
	{
		DrawBox((int)transform.x - transform.xr, (int)transform.y - transform.yr,
			(int)transform.x + transform.xr, (int)transform.y + transform.yr, GetColor(255, 255, 255), true);
	}

	for (int i = 0; i < 4; i++)
	{
		bullet[i].Draw();
	}

	mine->Draw();

	DrawFormatString(0, 100, GetColor(255, 255, 255), "sub_boss hp:%d", hp);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "sub_boss move_num:%d", move_num);
}
#pragma endregion

#pragma region �����蔻��

//bullet_flag�������Ă����画�������
//�_���[�W�t���O��false�Ȃ�̗͂����炵
//�e��t���O����

void SubBoss::HitBox(Transform transform, bool* bullet_flag)
{
	if (*bullet_flag == true)
	{
		if (this->transform.x - this->transform.xr < transform.x + transform.xr &&
			this->transform.x + this->transform.xr > transform.x - transform.xr)
		{
			if (this->transform.y - this->transform.yr < transform.y + transform.yr &&
				this->transform.y + this->transform.yr > transform.y - transform.yr)
			{
				if (damage_flag == false)
				{
					hp--;
					damage_flag = true;
					*bullet_flag = false;
				}

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
#pragma endregion

#pragma region ���ˉ񐔏�����

//bullet_flag�����ׂ�false��������
//�S�Ă̔��ˉ񐔂�0�ɂ���
//�ړ��t���O�𗧂Ă�

void SubBoss::Refresh_ReflectionNum(int max)
{
	int i = 0;

	for (i = 0; i < max; i++)
	{
		//���ˉ񐔏�����
		if (*bullet[i].GetBulletFlag() == true)
		{
			i -= 1;
			break;

		}
	}
	if (i == max && shot_time == -1)
	{
		for (int j = 0; j < max; j++)
		{
			bullet[j].SetReflectionNum(0);
		}

		move_flag = true;
	}
}
#pragma endregion

#pragma region �R���g���X�^�E�f�X�g���N�^

SubBoss::SubBoss()
{
	enemy_type = 0;//�G�̃^�C�v
	//���W
	transform.x = 0;
	transform.y = 0;
	transform.xr = 0;
	transform.yr = 0;
	hp = 0;//�̗�
	x_speed = 0;//�e��X���W�̃X�s�[�h
	y_speed = 0;//�e��Y���W�̃X�s�[�h
	exising_flag = false;//���݃t���O
	damage_flag = false;
	shot_time = 0;
	//�ŏ��̈ړ��̂��߂̕ϐ�
	frame = 0;
	end_frame = 0;
	start_x = 0;
	start_y = 0;
	end_x = 0;
	end_y = 0;
	fast_move_flag = false;
	appear_time = 0;
	//�ړ��̂��߂̕ϐ�
	move_flag = false;
	move_time = 0;
	move_num = 0;
	move_frame = 0;
	move_end_frame = 0;
	for (int i = 0; i < 8; i++)
	{
		move_start_x[i] = .0;
		move_start_y[i] = 0;
		move_end_x[i] = 0;
		move_end_y[i] = 0;
	}

	//�����l
	def_move_time = move_time;
	def_shot_time = shot_time;

	bullet = new EnemyBullet[4];
	mine = new Mine;

	mime_initialize.transform_yr = 0;
	mime_initialize.transform_xr = 0;
	mime_initialize.def_bombs_time = 0;
	mime_initialize.def_explosion_time = 0;
}

SubBoss::~SubBoss()
{
}
#pragma endregion

