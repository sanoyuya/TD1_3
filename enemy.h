#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();
	void Move();
	void Draw();

private:

	int enemy_type;
	double x;
	double y;
	int xr;
	int yr;
	bool move_flag;
	bool fast_move_flag;
	bool exising_flag;
	double start_x;
	double start_y;
	double end_x;
	double end_y;
	int hp;
	int x_speed;
	int y_speed;
	int appear_time;
	int frame;
	int end_frame;
	int shot_time;
};