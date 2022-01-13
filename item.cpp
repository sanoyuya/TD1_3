#include "item.h"
#include"DxLib.h"
Item::Item()
{
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

void Item::Draw()
{
	if (exising_flag == true)
	{
		DrawCircle(transform.x, transform.y, transform.xr, GetColor(255, 255, 255));
	}
}
