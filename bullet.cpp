#include"bullet.h"
#include"enemy.h"
#include"DxLib.h"
#include"map.h"
#include"player.h"
#include<math.h>

EnemyBullet::EnemyBullet()
{
	transform.x = 0;
	transform.y = 0;
	transform.xr = 8;
	transform.yr = 8;
	vertex.top_left_x = 0;
	vertex.top_left_y = 0;
	vertex.down_left_x = 0;
	vertex.down_left_y = 0;
	vertex.top_right_x = 0;
	vertex.top_right_y = 0;
	vertex.down_right_x = 0;
	vertex.down_right_y = 0;
	reflection_num = 0;
	bullet_flag = false;
	x_speed = 0;
	y_speed = 0;
	angle = 0.0f;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Move()
{
	if (bullet_flag == true)
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
							x_speed = -(x_speed);
							reflection_num++;
							break;

						}

					}
				}
				else
				{
					x_speed = -(x_speed);
					reflection_num++;

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
							x_speed = -(x_speed);
							reflection_num++;
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
							y_speed = -(y_speed);
							reflection_num++;
							break;
						}

					}
				}
				else
				{
					y_speed = -(y_speed);
					reflection_num++;
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
							y_speed = -(y_speed);
							reflection_num++;
							break;

						}

					}
				}
				else
				{
					y_speed = -(y_speed);
					reflection_num++;
				}

			}
		}
	}
}

//描画
void EnemyBullet::Draw()
{
	if (bullet_flag == true)
	{
		DrawCircle((int)transform.x, (int)transform.y, transform.xr, GetColor(255, 255, 255), true);

		if (reflection_num == 4)
		{
			bullet_flag = false;
		}
	}
}

//生成
void EnemyBullet::Form(Transform transform, Player& player, int x_speed, int y_speed)
{
	bullet_flag = true;
	this->transform.x = transform.x;
	this->transform.y = transform.y;
	angle = (float)atan2(player.GetY() - this->transform.y, player.GetX() - this->transform.x);
	this->transform.x += (cos(angle) * ((double)transform.xr + 15));
	this->transform.y += (sin(angle) * ((double)transform.yr + 15));
	this->x_speed = x_speed;
	this->y_speed = y_speed;
}

//ゲッター
Vertex EnemyBullet::GetVertex()
{
	return vertex;
}

Transform EnemyBullet::GetTransform()
{
	return transform;
}

bool EnemyBullet::GetBulletFlag()
{
	return bullet_flag;
}

int EnemyBullet::GetReflectionNum()
{
	return reflection_num;
}

//セッター
void EnemyBullet::SetReflectionNum(int reflection_num)
{
	this->reflection_num = reflection_num;
}



