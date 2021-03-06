#include "item.h"
#include"DxLib.h"
#include"enemy.h"

Item::Item()
{
	for (int i = 0; i < 6; i++)
	{
		appear_flag[i] = false;
		exising_flag[i] = false;
		transform[i] = { 0 };
		transform[i].xr = 32;
		transform[i].yr = 32;
		time[i] = 500;
	}




	img = LoadGraph("resouce/ReflectionItem.png");
	img_r = 32;
}

Item::~Item()
{
}

void Item::Form(Transform transform)
{
	int i = FlagSerch(exising_flag, 6);
	if (i != -1)
	{
		int rand = GetRand(100) + 1;

		if (rand <= 25)
		{
			exising_flag[i] = true;

			this->transform[i].x = transform.x;
			this->transform[i].y = transform.y;

		}
	}
}

void Item::TutorialForm(Transform transform, int item_flag)
{
	if (item_flag == 1)
	{
		exising_flag[0] = true;
	}

	if (exising_flag[0] == true)
	{
		this->transform[0].x = transform.x;
		this->transform[0].y = transform.y;
	}
}

bool Item::TutorialMove(int x, int y, int r, int item_flag)
{
	if (item_flag == 1)
	{
		float a = x - (float)transform[0].x;
		float b = y - (float)transform[0].y;
		float c = a * a + b * b;
		float sum_radius = r + (float)transform[0].xr;
		//if (player.GetR() * 64 >
		//	((player.GetX() - (int)transform[i].x) * (player.GetX() - (int)transform[i].x)) +
		//	((player.GetY() - (int)transform[i].y) * (player.GetY() - (int)transform[i].y)))
		if (c <= sum_radius * sum_radius)
		{
			exising_flag[0] = false;
			return true;
		}
	}
	return false;
}


void Item::Move(Player& player, Score& score)
{
	for (int i = 0; i < 6; i++)
	{
		if (exising_flag[i] == true)
		{
			float a = player.GetX() - (float)transform[i].x;
			float b = player.GetY() - (float)transform[i].y;
			float c = a * a + b * b;
			float sum_radius = (float)player.GetR() + transform[i].xr;
			//if (player.GetR() * 64 >
			//	((player.GetX() - (int)transform[i].x) * (player.GetX() - (int)transform[i].x)) +
			//	((player.GetY() - (int)transform[i].y) * (player.GetY() - (int)transform[i].y)))
			if (c <= sum_radius * sum_radius)
			{
				exising_flag[i] = false;
				player.ItemFlagAdd(1, score);
				time[i] = 500;
			}

			if (time[i] > 0)
			{
				time[i]--;
			}
			if (time[i] <= 0)
			{
				exising_flag[i] = false;
				time[i] = 500;
			}
		}
	}
}

void Item::Draw()
{
	for (int i = 0; i < 6; i++)
	{
		if (exising_flag[i] == true)
		{
			DrawGraph((int)transform[i].x - img_r, (int)transform[i].y - img_r, img, true);
		}
	}
}

bool Item::ItemExists()
{
	bool brek_flag = false;;

	for (int i = 0; i < 6; i++)
	{
		if (exising_flag[i] == true)
		{
			brek_flag = true;
			break;
		}
	}

	if (brek_flag == true)
	{
		return false;
	}
	else
	{
		return true;
	}
	;
}
