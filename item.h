#pragma once
#include "Transform.h"
#include"player.h"
class Item
{
public:
	Item();
	~Item();
	void Form();
	void TutorialForm(Transform transform, int item_flag);
	void Move(Player& player);
	void Draw();

private:

	Transform transform;
	
	bool appear_flag;
	bool exising_flag;
};

