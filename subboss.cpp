#include<DxLib.h>
#include"enemy.h"
#include"subboss.h"
#include"Transform.h"
#include"map.h"
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
	if (fscanf_s(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%lf,%lf,%lf,%lf,%d,%d,%d,%d,%d,%d,%d"
		, &enemy_type, &appear_time, &shot_time, &hp, &transform.xr, &transform.yr, &bullet_x_speed, &bullet_y_speed, &x_speed, &y_speed, &end_frame, &start_x, &start_y, &end_x, &end_y, &move_time, &move_end_frame,
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
		bullet_x_speed = 0;
		bullet_y_speed = 0;
		shot_time = 0;
		end_frame = 0;
		start_x = 0;
		end_x = 0;
		end_y = 0;
		appear_time = 0;
		move_time = 0;
		move_end_frame = 0;

		mime_initialize.transform_yr = 0;
		mime_initialize.transform_xr = 0;
		mime_initialize.def_bombs_time = 0;
		mime_initialize.def_explosion_time = 0;
		mime_initialize.explosion_r = 0;
	}

	transform.x = start_x;
	transform.y = start_y;
	exising_flag = false;
	damage_flag[0] = false;
	damage_flag[1] = false;
	damage_flag[2] = false;
	damage_flag[3] = false;
	fast_move_flag = false;

	move_flag = false;
	frame = 0;
	move_num = 0;
	move_frame = 0;

	def_move_time = move_time;
	def_shot_time = shot_time;

	anticipation = 50;
	teleport_flag = false;
}
#pragma endregion

#pragma region ����

//�o�����Ԏ��Ԃ����炵0�ɂȂ�����ŏ��̈ړ�������
//�e��ł����Ă��ׂď�������Ɉړ�����
//�n���ƒe�̓���������

void SubBoss::Move(Player& player, bool reflection_flag)
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

	if (exising_flag == true)
	{
		//if (enemy_type == 1)
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
					if (enemy_type == 1 && move_time == 1)
					{
						//�n���ݒu�t���t�𗧂Ă�
						mine->SetMineFlag(true);
						mine->SetRand(7);
					}

					if (enemy_type == 3 && move_time == 1)
					{
						rand = GetRand(7);
					}

					if (move_time > 0)
					{
						move_time--;
					}

					if (move_time == 0)
					{
						move_flag = true;

						int rand2 = GetRand(7);

						if (enemy_type == 3 && rand == rand2)
						{
							move_flag = false;
							teleport_flag = true;
						}
					}

#pragma region �ړ�
					if (move_flag == true)
					{
						if (move_frame == 0)
						{
							rand = GetRand(7) + 1;

							if ((int)transform.y == 128)//��
							{
								while (rand == 3 || rand == 5 || rand == 7)
								{
									rand = GetRand(7) + 1;
								}
							}
							else if ((int)transform.y == 864)//��
							{
								while (rand == 4 || rand == 6 || rand == 8)
								{
									rand = GetRand(7) + 1;
								}
							}
							else if ((int)transform.x >= 776)//�E
							{
								while (rand == 1 || rand == 5 || rand == 6)
								{
									rand = GetRand(7) + 1;
								}
							}
							else if ((int)transform.x <= 178)//��
							{
								while (rand == 2 || rand == 7 || rand == 8)
								{
									rand = GetRand(7) + 1;
								}
							}
						}

						switch (rand)
						{

						case 1://�E
							XMove(x_speed, true);
							break;

						case 2://��
							XMove(x_speed, false);
							break;

						case 3://��
							YMove(y_speed, true);
							break;

						case 4://��
							YMove(y_speed, false);
							break;

						case 5://�E��
							XMove(x_speed, true);
							YMove(y_speed, true);
							break;

						case 6://�E��
							XMove(x_speed, true);
							YMove(y_speed, false);
							break;

						case 7://����
							XMove(x_speed, false);
							YMove(y_speed, true);
							break;

						case 8://����
							XMove(x_speed, false);
							YMove(y_speed, false);
							break;
						}

						move_frame++;

						if (move_frame == move_end_frame)
						{
							move_frame = 0;
							move_time = def_move_time;
							move_flag = false;
						}
					}
#pragma endregion

					if (teleport_flag == true)
					{
						if (anticipation > 0)
						{
							anticipation--;
						}

						if (anticipation == 0)
						{
							transform.x = (double)GetRand(560) + 207;
							transform.y = (double)GetRand(576) + 192;
							teleport_flag = false;
							anticipation = 50;
						}
					}
				}

				//���ˎ��ԊǗ�
				if (fast_move_flag == false && shot_time > 0)
				{
					shot_time--;
				}

				if (shot_time == -1)
				{
					if (enemy_type == 1)
					{
						shot_time = def_shot_time;
					}
					else
					{
						Refresh_ReflectionNum(4);
					}

				}

				//�����蔻��
				for (int i = 0; i < bullet_max; i++)
				{
					if (*bullet[i]->GetBulletFlag() == true)
					{

						HitBox(*bullet[i]->GetTransform(), bullet[i], i);
					}
				}

				//�e�̐���
				if (shot_time == 0)
				{

					if (enemy_type == 1)
					{
						int k[4] = { 0,0,0,0 };
						bool end = false;
						int i;
						int length = 0;

						for (i = 0; i < 4; i++)
						{
							int j = FlagSerch(bullet, bullet_max);

							if (j != -1)
							{
								bullet[j]->Form(transform, player, bullet_x_speed, bullet_y_speed, enemy_type);
								damage_flag[j] = true;
								k[i] = j;
							}
							else
							{
								length = i;
								break;
							}
						}

						if (i == 4)
						{
							end = true;
						}

						if (end == true)
						{
							//�p�x��90�x�����炷
							bullet[k[1]]->SetAngle(bullet[k[0]]->GetAngle() + (DX_PI_F / 2));
							bullet[k[2]]->SetAngle(bullet[k[1]]->GetAngle() + (DX_PI_F / 2));
							bullet[k[3]]->SetAngle(bullet[k[2]]->GetAngle() + (DX_PI_F / 2));
						}
						else
						{
							for (int i = 0; i < length; i++)
							{
								int j = k[i];
								bullet[j]->SetBulletFlag(false);

								damage_flag[j] = false;
							}
						}
					}
					else
					{
						for (int i = 0; i < 4; i++)
						{
							if (*bullet[i]->GetBulletFlag() == false)
							{
								bullet[i]->Form(transform, player, bullet_x_speed, bullet_y_speed, enemy_type);
								damage_flag[i] = true;
								//�p�x��90�x�����炷
								bullet[1]->SetAngle(bullet[0]->GetAngle() + (DX_PI_F / 2));
								bullet[2]->SetAngle(bullet[1]->GetAngle() + (DX_PI_F / 2));
								bullet[3]->SetAngle(bullet[2]->GetAngle() + (DX_PI_F / 2));
							}
						}
					}



					shot_time = -1;
				}

				if (hp <= 0)
				{
					exising_flag = false;
				}
			}

			if (enemy_type == 1)
			{
				//�n���̓���
				mine->form(transform, rand);
				mine->HitBox(transform, hp);
			}
		}
	}

	if (enemy_type == 1)
	{
		mine->Move();
	}

	for (int i = 0; i < bullet_max; i++)
	{
		//�e�̓���
		bullet[i]->Move(enemy_type, reflection_flag, player, transform.x, transform.y, exising_flag, transform);
	}

	if (enemy_type == 1)
	{
		boss1_anime_timer++;

		if (boss1_anime_timer == 14 * 6)
		{
			boss1_anime_timer = 0;
		}

		boss1_anime = boss1_anime_timer / 6;
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
		if (enemy_type == 1 || enemy_type == 3)
		{

			DrawGraphF((float)transform.x - img_r, (float)transform.y - img_r, boss1_img[boss1_anime], true);
			
			if (teleport_flag == true)
			{
				DrawBox((float)transform.x - img_r, (float)transform.y - img_r, (float)transform.x + img_r, (float)transform.y + img_r, GetColor(255, 255, 255), true);
			}
		}
	}

	for (int i = 0; i < bullet_max; i++)
	{
		bullet[i]->Draw(enemy_type);

		if (bullet[i]->GetReflectionNum() >= 3)
		{
			bullet[i]->SetBulletFlag(false);
			bullet[i]->SetReflectionNum(0);
		}
	}

	mine->Draw();

	DrawFormatString(0, 100, GetColor(255, 255, 255), "sub_boss hp:%d", hp);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "sub_boss move_num:%d", move_num);
	DrawFormatString(0, 140, GetColor(255, 255, 255), "move_time :%d", move_time);
	DrawFormatString(500, 160, GetColor(255, 255, 255), "x:%lf", transform.x);
	DrawFormatString(0, 180, GetColor(255, 255, 255), "y:%lf", transform.y);
}
#pragma endregion

#pragma region �����蔻��

//bullet_flag�������Ă����画�������
//�_���[�W�t���O��false�Ȃ�̗͂����炵
//�e��t���O����

void SubBoss::HitBox(Transform& transform, EnemyBullet* enemyBullet, int i)
{
	if (*enemyBullet->GetBulletFlag() == true)
	{
		if (this->transform.x - this->transform.xr < transform.x + transform.xr &&
			this->transform.x + this->transform.xr > transform.x - transform.xr)
		{
			if (this->transform.y - this->transform.yr < transform.y + transform.yr &&
				this->transform.y + this->transform.yr > transform.y - transform.yr)
			{
				if (damage_flag[i] == false)
				{
					hp--;
					damage_flag[i] = true;
					enemyBullet->SetBulletFlag(false);
				}

			}
			else
			{
				damage_flag[i] = false;
			}
		}
		else
		{
			damage_flag[i] = false;
		}
	}
}

void SubBoss::HP(Transform& transform, EnemyBullet& enemyBullet)
{
	//�����蔻��(����)
	if (*enemyBullet.GetBulletFlag() == true && exising_flag == true)
	{
		if (this->transform.x - this->transform.xr < transform.x + transform.xr &&
			this->transform.x + this->transform.xr > transform.x - transform.xr)
		{
			if (this->transform.y - this->transform.yr < transform.y + transform.yr &&
				this->transform.y + this->transform.yr > transform.y - transform.yr)
			{
				hp -= 1;
				enemyBullet.SetBulletFlag(false);

				if (hp <= 0)
				{
					exising_flag = false;
				}

			}
		}
	}
}


#pragma endregion

#pragma region �����蔻��t���ړ�

void SubBoss::XMove(int x_speed, bool right_flag)
{
	if (right_flag == false)
	{
		//���W�v�Z
		vertex.top_left_y = ((int)transform.y - transform.yr) / 32;
		vertex.down_left_y = ((int)transform.y + transform.yr - 1) / 32;

		vertex.top_left_x = (int)(((double)transform.x - transform.xr) - x_speed) / 32;
		vertex.down_left_x = (int)(((double)transform.x - transform.xr) - x_speed) / 32;

		//����
		if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
			GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
			transform.x > 178)
		{
			transform.x -= x_speed;
		}
		else
		{
			vertex.top_left_x = ((int)transform.x - transform.xr) / 32;
			vertex.down_left_x = ((int)transform.x - transform.xr) / 32;

			if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
				GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
				transform.x > 178)
			{
				while (1)//���Ԗ���
				{
					vertex.top_left_x = (((int)transform.x - transform.xr) - 1) / 32;
					vertex.down_left_x = (((int)transform.x - transform.xr) - 1) / 32;

					if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
						GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
						transform.x > 178)
					{
						transform.x -= 1;
					}
					else
					{
						break;
					}

				}
			}

		}
	}
	else
	{
		//���W�v�Z
		vertex.top_right_y = ((int)transform.y - transform.yr) / 32;
		vertex.down_right_y = ((int)transform.y + transform.yr - 1) / 32;

		vertex.top_right_x = ((int)(transform.x + transform.xr - 1) + x_speed) / 32;
		vertex.down_right_x = ((int)(transform.x + transform.xr - 1) + x_speed) / 32;

		//����
		if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
			GetMap(vertex.down_right_x, vertex.down_right_y) == 0 &&
			transform.x < 776)
		{
			transform.x += x_speed;
		}
		else
		{
			vertex.top_right_x = ((int)transform.x + transform.xr - 1) / 32;
			vertex.down_right_x = ((int)transform.x + transform.xr - 1) / 32;

			if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
				GetMap(vertex.down_right_x, vertex.down_right_y) == 0 &&
				transform.x < 776)
			{
				while (1)//���Ԗ���
				{
					vertex.top_right_x = (((int)transform.x + transform.xr - 1) + 1) / 32;
					vertex.down_right_x = (((int)transform.x + transform.xr - 1) + 1) / 32;

					if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
						GetMap(vertex.down_right_x, vertex.down_right_y) == 0 &&
						transform.x < 776)
					{
						transform.x += 1;
					}
					else
					{
						break;

					}
				}
			}
		}
	}
}

void SubBoss::YMove(int y_speed, bool up_flag)
{
	if (up_flag == true)
	{
		//���W�v�Z
		vertex.top_left_x = ((int)transform.x - transform.xr) / 32;
		vertex.top_right_x = ((int)transform.x + transform.xr - 1) / 32;

		vertex.top_left_y = (int)((transform.y - transform.yr) - y_speed) / 32;
		vertex.top_right_y = (int)((transform.y - transform.yr) - y_speed) / 32;

		//����
		if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
			GetMap(vertex.top_right_x, vertex.top_right_y) == 0)
		{
			transform.y -= y_speed;
		}
		else
		{
			vertex.top_left_y = ((int)transform.y - transform.yr) / 32;
			vertex.top_right_y = ((int)transform.y - transform.yr) / 32;

			if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
				GetMap(vertex.top_right_x, vertex.top_right_y) == 0)
			{
				while (1)//���Ԗ���
				{
					vertex.top_left_y = ((int)(transform.y - transform.yr) - 1) / 32;
					vertex.top_right_y = ((int)(transform.y - transform.yr) - 1) / 32;

					if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
						GetMap(vertex.top_right_x, vertex.top_right_y) == 0)
					{
						transform.y -= 1;
					}
					else
					{
						break;
					}
				}
			}

		}
	}
	else
	{
		//���W�v�Z
		vertex.down_left_x = ((int)transform.x - transform.xr) / 32;
		vertex.down_right_x = ((int)transform.x + transform.xr - 1) / 32;

		vertex.down_left_y = (int)((transform.y + transform.yr - 1) + y_speed) / 32;
		vertex.down_right_y = (int)((transform.y + transform.yr - 1) + y_speed) / 32;

		//����
		if (GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
			GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
		{
			transform.y += y_speed;
		}
		else
		{
			vertex.down_left_y = ((int)transform.y + transform.yr - 1) / 32;
			vertex.down_right_y = ((int)transform.y + transform.yr - 1) / 32;

			if (GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
				GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
			{
				while (1)//���Ԗ���
				{
					vertex.down_left_y = (((int)transform.y + transform.yr - 1) + 1) / 32;

					vertex.down_right_y = (((int)transform.y + transform.yr - 1) + 1) / 32;

					if (GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
						GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
					{
						transform.y += 1;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
}

void SubBoss::MineHit(Transform transform, int& hp, bool damage_flag)
{
	mine->HitBox(transform, hp, damage_flag);
}

void SubBoss::PlayerMineHit(Player& player)
{
	mine->PlayerHitBox(player);
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
		if (*bullet[i]->GetBulletFlag() == true)
		{
			i -= 1;
			break;

		}
	}
	if (i == max && shot_time == -1)
	{
		for (int j = 0; j < max; j++)
		{
			bullet[j]->SetReflectionNum(0);
			shot_time = def_shot_time;
		}
	}
}

#pragma endregion

#pragma region �Q�b�^�[
Transform* SubBoss::GetBulletTransform(int num)
{
	return bullet[num]->GetTransform();
}

EnemyBullet* SubBoss::GetEnmyBullet(int i)
{
	return bullet[i];
}

bool SubBoss::GetEnmyBulletFlag(int i)
{
	return *bullet[i]->GetBulletFlag();
}

bool SubBoss::GetSubBossFlag()
{
	return exising_flag;
}

int SubBoss::GetAppearTime()
{
	return appear_time;
}

int SubBoss::GetBulletMax()
{
	return bullet_max;
}

void SubBoss::SetMineExplosion()
{
	mine->SetExplosionTime(1);
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

	//���_
	vertex.top_left_x = 0;
	vertex.top_left_y = 0;
	vertex.down_left_x = 0;
	vertex.down_left_y = 0;
	vertex.top_right_x = 0;
	vertex.top_right_y = 0;
	vertex.down_right_x = 0;
	vertex.down_right_y = 0;

	hp = 0;//�̗�
	bullet_x_speed = 0;//�e��X���W�̃X�s�[�h
	bullet_y_speed = 0;//�e��Y���W�̃X�s�[�h
	x_speed = 0;//X���W�̃X�s�[�h
	y_speed = 0;//Y���W�̃X�s�[�h
	exising_flag = false;//���݃t���O
	damage_flag[0] = false;
	damage_flag[1] = false;
	damage_flag[2] = false;
	damage_flag[3] = false;
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

	//�����l
	def_move_time = move_time;
	def_shot_time = shot_time;

	for (int i = 0; i < 12; i++)
	{
		bullet[i] = new EnemyBullet;
	}

	mine = new Mine;

	mime_initialize.transform_yr = 0;
	mime_initialize.transform_xr = 0;
	mime_initialize.def_bombs_time = 0;
	mime_initialize.def_explosion_time = 0;
	rand = 0;

	anticipation = 50;
	teleport_flag = false;
	LoadDivGraph("resouce/boss1.png", 14, 14, 1, 128, 128, boss1_img);
	boss1_anime_timer = 0;
	boss1_anime = 0;
	img_r = 64;

	bullet_max = 12;

}

SubBoss::~SubBoss()
{
	delete mine;

	for (int i = 0; i < bullet_max; i++)
	{
		delete bullet[i];
	}

}
#pragma endregion

