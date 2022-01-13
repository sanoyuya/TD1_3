#pragma once
#include"Transform.h"
#include"player.h"

typedef class EnemyBullet
{
public:
	void Move(int enemy_type, bool reflection_flag);
	void Draw();
	void Form(Transform transform, Player& player, int x_speed, int y_speed);
	void TuTorialForm(Transform transform, int x, int y, int x_speed, int y_speed,int stelsflag);

	Vertex GetVertex();
	Transform GetTransform();
	bool* GetBulletFlag();
	int GetReflectionNum();
	float GetAngle();

	void SetAngle(float angle);
	void SetReflectionNum(int reflection_num);
	void SetBulletFlag(bool bullet_flag);
	
	EnemyBullet();
	~EnemyBullet();

	//デバッグ用
	int color;

private:
	Transform transform;
	Vertex vertex;
	int reflection_num;
	bool bullet_flag;
	int x_speed;
	int y_speed;
	float angle;


}EnemyBullet;

