#include<DxLib.h>
#include"enemy.h"
#include"subboss.h"
#include"Transform.h"
#include<math.h>

void SubBoss::form(FILE* fp)
{
	if (fscanf_s(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%lf,%lf,%lf,%lf,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf"
		, &enemy_type, &appear_time, &shot_time, &hp, &transform.xr, &transform.yr, &x_speed, &y_speed, &end_frame, &start_x, &start_y, &end_x, &end_y, &move_time, &move_end_frame,
		&move_end_x[0], &move_end_y[0],
		&move_end_x[1], &move_end_y[1],
		&move_end_x[2], &move_end_y[2],
		&move_end_x[3], &move_end_y[3],
		&move_end_x[4], &move_end_y[4],
		&move_end_x[5], &move_end_y[5],
		&move_end_x[6], &move_end_y[6])
   		!= EOF)
	{

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
		move_end_x[0] = 0;
		move_end_y[0] = 0;
		move_end_x[1] = 0;
		move_end_y[1] = 0;
		move_end_x[2] = 0;
		move_end_y[2] = 0;
		move_end_x[3] = 0;
		move_end_y[3] = 0;
		move_end_x[4] = 0;
		move_end_y[4] = 0;
		move_end_x[5] = 0;
		move_end_y[5] = 0;
		move_end_x[6] = 0;
		move_end_y[6] = 0;
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
	move_start_x[1] = move_end_x[0];
	move_start_y[1] = move_end_y[0];
	move_start_x[2] = move_end_x[1];
	move_start_y[2] = move_end_y[1];
	move_start_x[3] = move_end_x[2];
	move_start_y[3] = move_end_y[2];
	move_start_x[4] = move_end_x[3];
	move_start_y[4] = move_end_y[3];
	move_start_x[5] = move_end_x[4];
	move_start_y[5] = move_end_y[4];
	move_start_x[6] = move_end_x[5];
	move_start_y[6] = move_end_y[5];
	move_start_x[7] = move_end_x[6];
	move_start_y[7] = move_end_y[6];
	move_end_x[7] = move_start_y[0];
	move_end_y[7] = move_start_y[0];
	def_move_time = move_time;
	def_shot_time = shot_time;
}

void SubBoss::Move(Player& player)
{

	//出現時間管理
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
			//最初の移動
			if (fast_move_flag == true)
			{
				frame++;
				transform.x = start_x + (end_x - start_x) * easeInSine((double)frame / (double)end_frame);
				transform.y = start_y + (end_y - start_y) * easeInSine((double)frame / (double)end_frame);

				if (frame == end_frame)
				{
					fast_move_flag = false;
				}
			}

			//移動
			if (fast_move_flag == false)
			{
				if (move_flag == true)
				{
					if (move_time > 0)
					{
						move_time--;
					}

					if (move_time == 0)
					{
						move_frame++;
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

			//発射時間管理
			if (fast_move_flag == false && shot_time > 0 && move_flag == false)
			{
				shot_time--;
			}

			Refresh_ReflectionNum(4);

			//当たり判定
			if (*bullet->GetBulletFlag() == true)
			{
				for (int i = 0; i < 4; i++)
				{
					HitBox(bullet[i].GetTransform(),bullet[i].GetBulletFlag());
				}
			}

			//弾の生成
			if (shot_time == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					bullet[i].Form(transform, player, x_speed, y_speed);
					damage_flag = true;
				}

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


	}

	for (int i = 0; i < 4; i++)
	{
		//弾の動き
		bullet[i].Move(enemy_type);
	}
}

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

	DrawFormatString(0, 100, GetColor(255, 255, 255), "%d", hp);
}

void SubBoss::HitBox(Transform transform, bool *bullet_flag)
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

void SubBoss::Refresh_ReflectionNum(int max)
{
	int i = 0;

	for (i = 0; i < max; i++)
	{
		//反射回数初期化
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

SubBoss::SubBoss()
{
	enemy_type = 0;//敵のタイプ
	//座標
	transform.x = 0;
	transform.y = 0;
	transform.xr = 0;
	transform.yr = 0;
	hp = 0;//体力
	x_speed = 0;//弾のX座標のスピード
	y_speed = 0;//弾のY座標のスピード
	exising_flag = false;//存在フラグ
	damage_flag = false;
	shot_time = 0;
	//最初の移動のための変数
	frame = 0;
	end_frame = 0;
	start_x = 0;
	start_y = 0;
	end_x = 0;
	end_y = 0;
	fast_move_flag = false;
	appear_time = 0;
	//移動のための変数
	move_flag = false;
	move_time = 0;
	move_num = 0;
	move_frame = 0;
	move_end_frame = 0;
	move_start_x[0] = .0;
	move_start_y[0] = 0;
	move_end_x[0] = 0;
	move_end_y[0] = 0;
	move_start_x[1] = 0;
	move_start_y[1] = 0;
	move_end_x[1] = 0;
	move_end_y[1] = 0;
	move_start_x[2] = 0;
	move_start_y[2] = 0;
	move_end_x[2] = 0;
	move_end_y[2] = 0;
	move_start_x[3] = 0;
	move_start_y[3] = 0;
	move_end_x[3] = 0;
	move_end_y[3] = 0;

	move_start_x[4] = .0;
	move_start_y[4] = 0;
	move_end_x[4] = 0;
	move_end_y[4] = 0;
	move_start_x[5] = 0;
	move_start_y[5] = 0;
	move_end_x[5] = 0;
	move_end_y[5] = 0;
	move_start_x[6] = 0;
	move_start_y[6] = 0;
	move_end_x[6] = 0;
	move_end_y[6] = 0;
	move_start_x[7] = 0;
	move_start_y[7] = 0;
	move_end_x[7] = 0;
	move_end_y[7] = 0;

	//初期値
	def_move_time = move_time;
	def_shot_time = shot_time;

	bullet = new EnemyBullet[4];
}

SubBoss::~SubBoss()
{
}

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