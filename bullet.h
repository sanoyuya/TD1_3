#pragma once
#include"Transform.h"
#include"player.h"

typedef class EnemyBullet
{
public:
	void Move(int& enemy_type, bool& reflection_flag, Player& player, double& x, double& y, bool& exising_flag, Transform& transform);
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
	void Draw(int enemy_type, int shot_time, bool fast_move_flag, bool exising_flag);
	void Form(Transform transform, Player& player, int x_speed, int y_speed,int& enemy_type);
	void OmniFormHex(Transform transform, Player& player, int x_speed, int y_speed, int& enemy_type, int num, float angle);
	void OmniFormOct(Transform transform, Player& player, int x_speed, int y_speed, int& enemy_type,int num, float angle);
	void TuTorialForm(Transform transform, int x, int y, int x_speed, int y_speed,int stelsflag);

	Vertex GetVertex();
	Transform* GetTransform();
	bool GetBulletFlag(int enemy_type);
	bool* GetBulletFlag();
	int GetReflectionNum();
	float GetAngle();

	void SetAngle(float angle);
	void SetReflectionNum(int reflection_num);
	void SetBulletFlag(bool bullet_flag);
	bool LaserHitBox(Player player);
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
	int img;

	//ブーメラン
	int go_time;
	bool return_flag;

	float center_x;
	float center_y;
	float boomerang_angle;
	float boomerang_x_r;
	float boomerang_y_r;
	bool flag;

	int boomerang_img[8];
	int boomerang_anime_timer;
	int boomerang_anime;

	int reiza;
	float laser_range;
	float laser_magnification;

	int damage_time;
	//全方位
}EnemyBullet;
