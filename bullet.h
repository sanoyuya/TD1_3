#pragma once
#include"Transform.h"
#include"player.h"

class EnemyBullet
{
public:
	void Move();
	void Draw();
	void Form(Transform transform, Player& player, int x_speed, int y_speed);
	Vertex GetVertex();
	Transform GetTransform();
	bool GetBulletFlag();
	int GetReflectionNum();
	void SetReflectionNum(int reflection_num);
	EnemyBullet();
	~EnemyBullet();

private:
	Transform transform;
	Vertex vertex;
	int reflection_num;
	bool bullet_flag;
	int x_speed;
	int y_speed;
	float angle;

};

