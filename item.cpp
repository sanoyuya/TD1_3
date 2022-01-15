#include "item.h"
#include"DxLib.h"

Item::Item()
{
	appear_flag = false;
	exising_flag = false;
	transform = { 0 };
	transform.xr = 32;
	transform.yr = 32;

	img = LoadGraph("resouce/ReflectionItem.png");
	img_r = 32;
}

Item::~Item()
{
}

void Item::Form(Transform transform)
{
	int rand = GetRand(100) + 1;

	if (rand <= 25)
	{
		exising_flag = true;

		this->transform.x = transform.x;
		this->transform.y = transform.y;

	}
}

void Item::TutorialForm(Transform transform, int item_flag)
{
	if (item_flag == 1)
	{
		exising_flag = true;
	}

	if (exising_flag == true)
	{
		this->transform.x = transform.x;
		this->transform.y = transform.y;
	}
}

bool Item::TutorialMove(int x, int y, int r, int item_flag)
{
	if (item_flag == 1)
	{
		if (r * (int)transform.xr >
			((x - (int)transform.x) * (x - (int)transform.x)) +
			((y - (int)transform.y) * (y - (int)transform.y)))
		{
			exising_flag = false;
			return true;
		}
	}
	return false;
}


void Item::Move(Player& player)
{
	if (exising_flag == true)
	{
		if (player.GetR() * player.GetR() >
			((player.GetX() - (int)transform.x) * (player.GetX() - (int)transform.x)) +
			((player.GetY() - (int)transform.y) * (player.GetY() - (int)transform.y)))
		{
			exising_flag = false;
			player.ItemFlagAdd(1);
		}
	}
}

void Item::Draw()
{
	if (exising_flag == true)
	{
		DrawGraph((int)transform.x - img_r, (int)transform.y - img_r, img, true);
	}
}
