#pragma once
#include "Transform.h"
#include"player.h"
#include"score.h"
class Item
{
public:
	Item();
	~Item();
	void Form(Transform transform);
	void TutorialForm(Transform transform, int item_flag);
	bool TutorialMove(int x, int y, int r, int item_flag);
	void Move(Player& player, Score& score);
	void Draw();
	bool ItemExists();

private:

	Transform transform[6];
	
	bool appear_flag[6];
	bool exising_flag[6];
	int img;
	int img_r;

	int time[6];
};

