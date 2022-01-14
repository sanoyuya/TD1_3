#include "item.h"
#include"DxLib.h"

Item::Item()
{
	appear_flag = false;
	exising_flag = false;
	transform = { 0 };
}

Item::~Item()
{
}

void Item::TutorialForm(Transform transform, int item_flag)
{
	if (item_flag == 1)
	{
		exising_flag = true;
	}

	{ 
	if (exising_flag == true)
		this->transform.x = transform.x;
		this->transform.y = transform.y;
	}
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
		}
	}
}

void Item::Draw()
{
	if (exising_flag == true)
	{
		DrawCircle((int)transform.x, (int)transform.y, transform.xr, GetColor(255, 255, 255));
	}
}
