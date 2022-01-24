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
	int i = FlagSerch(exising_flag,6);
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
		if (r * (int)transform[0].xr >
			((x - (int)transform[0].x) * (x - (int)transform[0].x)) +
			((y - (int)transform[0].y) * (y - (int)transform[0].y)))
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
			if (player.GetR() * 64 >
				((player.GetX() - (int)transform[i].x) * (player.GetX() - (int)transform[i].x)) +
				((player.GetY() - (int)transform[i].y) * (player.GetY() - (int)transform[i].y)))
			{
				exising_flag[i] = false;
				player.ItemFlagAdd(1, score);
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
