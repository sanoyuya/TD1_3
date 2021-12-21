#include"DxLib.h"
#include"enemy.h"
#include"bullet.h"
#include"map.h"
#include"Transform.h"
#include<math.h>


// ウィンドウ横幅
const int WIN_WIDTH = 1856;

// ウィンドウ縦幅
const int WIN_HEIGHT = 960;

#define PI 3.1415926535f

double easeInSine(double x)
{
	return 1 - cos((x * PI) / 2);
}

Enemy::Enemy()
{
	use_flag = false;//使うかフラグ
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
	action_flag = false;//動くかどうかフラグ
	shot_action_flag = false;
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
	move_end_frame = 00;
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

	//初期値
	def_move_time = move_time;
	def_shot_time = shot_time;

	//ボマー
	angle = 0.0f;
	vertex.top_left_x = 0;
	vertex.top_left_y = 0;
	vertex.down_left_x = 0;
	vertex.down_left_y = 0;
	vertex.top_right_x = 0;
	vertex.top_right_y = 0;
	vertex.down_right_x = 0;
	vertex.down_right_y = 0;
	explosion_time = 0;
	enemy_to_bommer = false;
	def_explosion_time = 0;
	explosion_bommer_flag = false;
	bullet = new EnemyBullet();

}

Enemy::~Enemy()
{

}

//動き
void Enemy::Move(Player& player)
{
	if (use_flag == true)
	{
		//出現時間管理
		if (appear_time == 0)
		{
			fast_move_flag = true;
			exising_flag = true;
			appear_time = -1;

			if (enemy_type == 2)
			{
				angle = (float)atan2(player.GetY() - this->transform.y, player.GetX() - this->transform.x);
			}
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
				if (action_flag == true && fast_move_flag == false)
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

								if (move_num == 4)
								{
									move_num = 0;
								}
							}
						}
					}
				}
				else if (action_flag == false)
				{
					if (move_flag == true)
					{
						shot_time = def_shot_time;
						move_flag = false;
					}
				}

				if (shot_action_flag == true)
				{
					//発射時間管理
					if (fast_move_flag == false && shot_time > 0 && move_flag == false)
					{
						shot_time--;
					}

					//反射回数初期化
					if (bullet->GetReflectionNum() == 4)
					{
						bullet->SetReflectionNum(0);
						move_flag = true;
					}

					//当たり判定
					if (bullet->GetBulletFlag() == true)
					{
						HitBox(bullet->GetTransform());
					}

					//弾の生成
					if (shot_time == 0)
					{
						bullet->Form(transform, player, x_speed, y_speed);
						shot_time = -1;
					}

					if (hp <= 0)
					{
						exising_flag = false;
					}
				}

			}

		}

		//ボマー
		if (enemy_type == 2)
		{
			if (exising_flag == true)
			{
				//最初の移動
				if (fast_move_flag == true && explosion_bommer_flag == false)
				{
					if (transform.x < 960.0 && transform.x> 0 + 64 &&
						transform.y < 960.0 && transform.y> 0 + 64)
					{
						if ((cos(angle) * x_speed) < 0)
						{
							//座標計算
							vertex.top_left_y = ((int)transform.y - transform.yr) / 32;
							vertex.down_left_y = ((int)transform.y + transform.yr - 1) / 32;

							vertex.top_left_x = (int)(((double)transform.x - transform.xr) + (cos(angle) * x_speed)) / 32;
							vertex.down_left_x = (int)(((double)transform.x - transform.xr) + (cos(angle) * x_speed)) / 32;

							//判定
							if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
								GetMap(vertex.down_left_x, vertex.down_left_y) == 0)
							{
								transform.x += (cos(angle) * x_speed);
							}
							else
							{
								vertex.top_left_x = ((int)transform.x - transform.xr) / 32;
								vertex.down_left_x = ((int)transform.x - transform.xr) / 32;

								if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
									GetMap(vertex.down_left_x, vertex.down_left_y) == 0)
								{
									while (1)//隙間埋め
									{
										vertex.top_left_x = (((int)transform.x - transform.xr) - 1) / 32;
										vertex.down_left_x = (((int)transform.x - transform.xr) - 1) / 32;

										if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
											GetMap(vertex.down_left_x, vertex.down_left_y) == 0)
										{
											if (x_speed < 0)
											{
												transform.x += (cos(angle) * -1);
											}
											else
											{
												transform.x += (cos(angle) * 1);
											}


										}
										else
										{
											explosion_bommer_flag = true;
											break;

										}

									}
								}

							}
						}
						else if ((cos(angle) * x_speed) > 0)
						{
							//座標計算
							vertex.top_right_y = ((int)transform.y - transform.yr) / 32;
							vertex.down_right_y = ((int)transform.y + transform.yr - 1) / 32;

							vertex.top_right_x = (int)((transform.x + transform.xr - 1) + (cos(angle) * x_speed)) / 32;
							vertex.down_right_x = (int)((transform.x + transform.xr - 1) + (cos(angle) * x_speed)) / 32;

							//判定
							if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
								GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
							{
								transform.x += (cos(angle) * x_speed);
							}
							else
							{
								vertex.top_right_x = ((int)transform.x + transform.xr - 1) / 32;
								vertex.down_right_x = ((int)transform.x + transform.xr - 1) / 32;

								if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
									GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
								{
									while (1)//隙間埋め
									{
										vertex.top_right_x = (((int)transform.x + transform.xr - 1) + 1) / 32;
										vertex.down_right_x = (((int)transform.x + transform.xr - 1) + 1) / 32;

										if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
											GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
										{
											if (x_speed < 0)
											{
												transform.x += (cos(angle) * -1);
											}
											else
											{
												transform.x += (cos(angle) * 1);
											}

										}
										else
										{
											explosion_bommer_flag = true;
											break;

										}

									}
								}

							}
						}

						if ((sin(angle) * y_speed) < 0)
						{
							//座標計算
							vertex.top_left_x = ((int)transform.x - transform.xr) / 32;
							vertex.top_right_x = ((int)transform.x + transform.xr - 1) / 32;

							vertex.top_left_y = (int)((transform.y - transform.yr) + (sin(angle) * y_speed)) / 32;
							vertex.top_right_y = (int)((transform.y - transform.yr - 1) + (sin(angle) * y_speed)) / 32;

							//判定
							if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
								GetMap(vertex.top_right_x, vertex.top_right_y) == 0)
							{
								transform.y += (sin(angle) * y_speed);
							}
							else
							{
								vertex.top_left_y = ((int)transform.y - transform.yr) / 32;
								vertex.top_right_y = ((int)transform.y - transform.yr - 1) / 32;

								if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
									GetMap(vertex.top_right_x, vertex.top_right_y) == 0)
								{
									while (1)//隙間埋め
									{
										vertex.top_left_y = (int)((transform.y - transform.yr) + (sin(angle) * -1)) / 32;
										vertex.top_right_y = (int)((transform.y - transform.yr - 1) + (sin(angle) * -1)) / 32;

										if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
											GetMap(vertex.top_right_x, vertex.top_right_y) == 0)
										{
											if (y_speed < 0)
											{
												transform.y += (sin(angle) * -1);
											}
											else
											{
												transform.y += (sin(angle) * 1);
											}
										}
										else
										{
											explosion_bommer_flag = true;
											break;
										}

									}
								}
							}
						}
						else if ((sin(angle) * y_speed) > 0)
						{
							//座標計算
							vertex.down_left_x = ((int)transform.x - transform.xr) / 32;
							vertex.down_right_x = ((int)transform.x + transform.xr - 1) / 32;

							vertex.down_left_y = (int)((transform.y + transform.yr - 1) + (sin(angle) * y_speed)) / 32;
							vertex.down_right_y = (int)((transform.y + transform.yr - 1) + (sin(angle) * y_speed)) / 32;

							//判定
							if (GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
								GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
							{
								transform.y += (sin(angle) * y_speed);
							}
							else
							{
								vertex.down_left_y = ((int)transform.y + transform.yr - 1) / 32;
								vertex.down_right_y = ((int)transform.y + transform.yr - 1) / 32;

								if (GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
									GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
								{
									while (1)//隙間埋め
									{
										vertex.down_left_y = (((int)transform.y + transform.yr - 1) + 1) / 32;

										vertex.down_right_y = (((int)transform.y + transform.yr - 1) + 1) / 32;

										if (GetMap(vertex.down_left_x, vertex.down_left_y) == 0 &&
											GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
										{
											if (y_speed > 0)
											{
												transform.y += (sin(angle) * 1);
											}
											else
											{
												transform.y += (sin(angle) * -1);
											}

										}
										else
										{
											explosion_bommer_flag = true;
											break;

										}

									}
								}
							}
						}
					}
					else
					{
						transform.y += (sin(angle) * y_speed);
						transform.x += (cos(angle) * x_speed);
					}
				}
			}
		}

		//弾の動き
		bullet->Move(enemy_type);
	}
}

void Enemy::ExplosionBommer(Enemy& enemy, Player& player)
{
	if (transform.x != enemy.transform.x && transform.y != enemy.transform.y && 
		enemy.exising_flag ==true && exising_flag == true)
	{
		EnemyToEnemyHitBox(enemy.transform);
	}

	if (explosion_bommer_flag == true)
	{
		if (explosion_time == def_explosion_time)
		{
			if (enemy_to_bommer == true)
			{
				enemy.exising_flag = false;
			}
		}

		explosion_time--;

		if (explosion_time == 0)
		{
			exising_flag = false;
		}
	}
}

void Enemy::EnemyToEnemyHitBox(Transform transform)
{
	if (this->transform.x - this->transform.xr < transform.x + transform.xr &&
		this->transform.x + this->transform.xr > transform.x - transform.xr)
	{
		if (this->transform.y - this->transform.yr < transform.y + transform.yr &&
			this->transform.y + this->transform.yr > transform.y - transform.yr)
		{
			if (damage_flag == false)
			{
				explosion_bommer_flag = true;
				enemy_to_bommer = true;
			}
		}
	}
}
//描画
void Enemy::Draw()
{
	if (exising_flag == true)
	{
		if (explosion_bommer_flag == true)
		{
			DrawBox((int)transform.x - transform.xr, (int)transform.y - transform.yr,
				(int)transform.x + transform.xr, (int)transform.y + transform.yr, GetColor(255, 0, 0), true);
		}
		else
		{
			DrawBox((int)transform.x - transform.xr, (int)transform.y - transform.yr,
				(int)transform.x + transform.xr, (int)transform.y + transform.yr, GetColor(255, 255, 255), true);
		}
	}
	bullet->Draw();

	DrawBox(0 + 32, 0 + 32, 960 + -32, 960 - 32, GetColor(255, 255, 255), false);
}

//当たり判定
void Enemy::HitBox(Transform transform)
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





//ファイルからデータ読みこみ
void Enemy::form(FILE* fp)
{
	int a = 0;
	int b = 0;
	int c = 0;
	if (fscanf_s(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%lf,%lf,%lf,%lf,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf"
, &a,&b,&c,&enemy_type,&appear_time,&shot_time,&explosion_time,&hp,&transform.xr,&transform.yr,&x_speed,&y_speed,&end_frame,&start_x,&start_y,&end_x,&end_y,&move_time,&move_end_frame,
		&move_end_x[0], &move_end_y[0], &move_end_x[1], &move_end_y[1], &move_end_x[2], &move_end_y[2])
		!= EOF)
	{
		use_flag = a;
		action_flag = b;
		shot_action_flag = c;
	}
	else
	{
		use_flag = false;
		enemy_type = 0;
		transform.xr = 0;
		transform.yr = 0;
		hp = 0;
		x_speed = 0;
		y_speed = 0;
		action_flag = false;
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
		shot_action_flag = false;

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
	move_end_x[3] = move_start_x[0];
	move_end_y[3] = move_start_y[0];
	def_move_time = move_time;
	def_shot_time = shot_time;

	angle = 0.0f;
	vertex.top_left_x = 0;
	vertex.top_left_y = 0;
	vertex.down_left_x = 0;
	vertex.down_left_y = 0;
	vertex.top_right_x = 0;
	vertex.top_right_y = 0;
	vertex.down_right_x = 0;
	vertex.down_right_y = 0;
	explosion_bommer_flag = false;
	def_explosion_time = explosion_time;
}

void EnemyForm(const char* file_name, int max, Enemy* enemy)
{

	FILE* fp;
	fopen_s(&fp, file_name, "r");

	if (fp != NULL)
	{
		for (int i = 0; i < max; i++)
		{
			enemy[i].form(fp);
		}
		enemy[0];
		enemy[1];
		fclose(fp);
	}
}




