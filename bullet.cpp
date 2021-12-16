#include"bullet.h"
#include"map.h"

EnemyBullet::EnemyBullet(int x_speed, int y_speed)
{
	x = 0;
	y = 0;
	r = 8;
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
		top_right_x = (x + r - 1) / 32;
		top_right_y = (y - r) / 32;

		down_right_x = (x + r - 1) / 32;
		down_right_y = (y + r - 1) / 32;

		top_right_x = ((x + r - 1) + x_speed) / 32;
		down_right_x = ((x + r - 1) + y_speed) / 32;
		if (GetMap(top_right_x, top_right_y) == 0 && GetMap(down_right_x, down_right_y) == 0)
		{
			x += x_speed;
		}
		else
		{
			top_right_x = (x + r - 1) / 32;
			down_right_x = (x + r - 1) / 32;

			if (GetMap(top_right_x, top_right_y) == 0 && GetMap(down_right_y, down_right_x) == 0)
			{
				while (1)
				{
					top_right_x = ((x + r - 1) + 1) / 32;

					down_right_x = ((x + r - 1) + 1) / 32;

					if (GetMap(top_right_y, top_right_x) == 0 && GetMap(down_right_y, down_right_x) == 0)
					{
						x += 1;

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

void EnemyBullet::Form(int x, int y)
{
	bullet_flag = true;
	this->x = x;
	this->y = y;

}