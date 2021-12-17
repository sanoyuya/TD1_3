#pragma once

typedef struct Vertex
{
	int top_right_x;
	int top_right_y;
	int down_right_x;
	int down_right_y;
	int top_left_x;
	int top_left_y;
	int down_left_x;
	int down_left_y;
};

class EnemyBullet
{
public:
	void Move();
	void Draw();
	void Form(int x, int y);
	Vertex GetVertex();
	EnemyBullet(int x_speed, int y_speed);
	~EnemyBullet();

private:
	int x;
	int y;
	int r;
	Vertex vertex;
	int reflection_num;
	bool bullet_flag;
	int x_speed;
	int y_speed;

};

