#include"DxLib.h"
#include"enemy.h"
#include"bullet.h"
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
	enemy_type = 0;
	x = 960 + 64.0;
	y = 0.0 - 64.0;
	xr = 32;
	yr = 32;
	move_flag = false;
	exising_flag = false;
	fast_move_flag = false;
	start_x = 960 + 64.0;
	start_y = 0.0 - 64.0;
	end_x = 960 - 150.0;
	end_y = 960 / 2;
	hp = 0;
	x_speed = 0;
	y_speed = 0;
	appear_time = 100;
	frame = 0;
	end_frame = 100;
	shot_time = 10;
	bullet = new EnemyBullet(-10,0);
	
}

Enemy::~Enemy()
{

}

void Enemy::Move()
{

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
			if (fast_move_flag == true)
			{
				frame++;
				x = start_x + (end_x - start_x) * easeInSine((double)frame / (double)end_frame);
				y = start_y + (end_y - start_y) * easeInSine((double)frame / (double)end_frame);

				if (frame == end_frame)
				{
					fast_move_flag = false;
				}
			}

			if (move_flag == true)
			{

			}

			if (move_flag == false && fast_move_flag == false && shot_time>0)
			{
				shot_time--;
			}

			if (shot_time == 0)
			{
				bullet->Form(x, y);
				shot_time = -1;
			}
		}

	}

	bullet->Move();

}

void Enemy::Draw()
{
	if (exising_flag == true)
	{
		DrawBox((int)x - xr, (int)y - yr, (int)x + xr, (int)y + yr, GetColor(255, 255, 255), true);

	}
	bullet->Draw();

	DrawBox(0+32, 0+32, 960+-32, 960-32, GetColor(255, 255, 255), false);
}
