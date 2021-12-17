#include"bullet.h"
#include"DxLib.h"
#include"map.h"

EnemyBullet::EnemyBullet(int x_speed, int y_speed)
{
	x = 0;
	y = 0;
	r = 8;
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
	this->x_speed = x_speed;
	this->y_speed = y_speed;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Move()
{
	if (bullet_flag == true)
	{
		if (x_speed < 0)
		{
			vertex.top_left_x = (x - r) / 32;
			vertex.top_left_y = (y - r) / 32;

			vertex.down_left_x = (x - r) / 32;
			vertex.down_left_y = (y + r - 1) / 32;

			vertex.top_left_x = ((x - r) + x_speed) / 32;
			vertex.down_left_x = ((x - r) + x_speed) / 32;

			if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 && 
				GetMap(vertex.down_left_x, vertex.down_left_y) == 0)
			{
				x += x_speed;
			}
			else
			{
				vertex.top_left_x = (x - r) / 32;
				vertex.down_left_x = (x - r) / 32;

				if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
					GetMap(vertex.down_left_x, vertex.down_left_y) == 0)
				{
					while (1)
					{
						vertex.top_left_x = ((x - r) - 1) / 32;

						vertex.down_left_x = ((x - r) - 1) / 32;

						if (GetMap(vertex.top_left_x, vertex.top_left_y) == 0 &&
							GetMap(vertex.down_left_x, vertex.down_left_y) == 0)
						{
							x -= 1;

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
		else if (x_speed > 0)
		{
			vertex.top_right_x = (x + r - 1) / 32;
			vertex.top_right_y = (y - r) / 32;

			vertex.down_right_x = (x + r - 1) / 32;
			vertex.down_right_y = (y + r - 1) / 32;

			vertex.top_right_x = ((x + r - 1) + x_speed) / 32;
			vertex.down_right_x = ((x + r - 1) + x_speed) / 32;

			if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
				GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
			{
				x += x_speed;
			}
			else
			{
				vertex.top_right_x = (x + r - 1) / 32;
				vertex.down_right_x = (x + r - 1) / 32;

				if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
					GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
				{
					while (1)
					{
						vertex.top_right_x = ((x + r - 1) + 1) / 32;

						vertex.down_right_x = ((x + r - 1) + 1) / 32;

						if (GetMap(vertex.top_right_x, vertex.top_right_y) == 0 &&
							GetMap(vertex.down_right_x, vertex.down_right_y) == 0)
						{
							x += 1;

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
	}
}

void EnemyBullet::Draw()
{
	if (bullet_flag == true)
	{
		DrawCircle(x, y, r, GetColor(255, 255, 255), true);

		if (reflection_num == 2)
		{
			bullet_flag = false;
			reflection_num = 0;
		}
	}
}

void EnemyBullet::Form(int x, int y)
{
	bullet_flag = true;
	this->x = x;
	this->y = y;

}

Vertex EnemyBullet::GetVertex()
{
	return vertex;
}
