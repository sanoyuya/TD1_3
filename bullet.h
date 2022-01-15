#pragma once
#include"Transform.h"
#include"player.h"

typedef class EnemyBullet
{
public:
	void Move(int enemy_type, bool reflection_flag, Player& player);
	void Move(int enemy_type, bool reflection_flag);
	
	int Box_Line(
		float start_x, float start_y, float start2_x, float start2_y,
		float start3_x, float start3_y, float start4_x, float start4_y,
		float point1_x, float point1_y, float point2_x, float point2_y,
		float point3_x, float point3_y, float point4_x, float point4_y
	);

	bool LineAndLine(float start_x, float start_y, float end_x, float end_y,
		float start2_x, float start2_y, float end2_x, float end2_y,
		float point1_x, float point1_y, float point2_x, float point2_y);

	void TutorialMove(int y);
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

	//�f�o�b�O�p
	int color;

private:
	Transform transform;
	Vertex vertex;
	int reflection_num;
	bool bullet_flag;
	int x_speed;
	int y_speed;
	float angle;
	int img;

}EnemyBullet;

