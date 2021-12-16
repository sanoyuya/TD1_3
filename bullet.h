#pragma once
class EnemyBullet
{
public:
	void Move();
	void Form(int x, int y);
	EnemyBullet(int x_speed, int y_speed);
	~EnemyBullet();

private:
	int x;
	int y;
	int r;
	int top_right_y;
	int down_right_x;
	int top_right_x;
	int down_right_y;
	bool bullet_flag;
	int x_speed;
	int y_speed;

};

