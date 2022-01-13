#pragma once
#include "Transform.h"

class Item
{
public:
	Item();
	~Item();
	void Form();
	void TutorialForm(Transform transform, int item_flag);
	void Move();
	void Draw();

private:

	Transform transform;
	
	bool appear_flag;
	bool exising_flag;
};

