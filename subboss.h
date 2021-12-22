#pragma once
#include"Transform.h"
#include"bullet.h"
#include"player.h"
class SubBoss
{
public:
	void form(FILE* fp);
	void Move(Player& player);
	void Draw();
	void HitBox(Transform transform, bool* bullet_flag);
	void Refresh_ReflectionNum(int max);

	SubBoss();
	~SubBoss();

private:
	int enemy_type;//敵のタイプ
	Transform transform;//座標
	int hp;//体力
	int x_speed;//X座標のスピード
	int y_speed;//Y座標のスピード
	bool exising_flag;//存在フラグ
	bool damage_flag;
	int shot_time;
	//最初の移動のための変数
	int frame;
	int end_frame;
	double start_x;
	double start_y;
	double end_x;
	double end_y;
	bool fast_move_flag;
	int appear_time;
	//移動のための変数
	bool move_flag;
	int move_time;
	int move_num;
	int move_frame;
	int move_end_frame;
	double move_start_x[8];
	double move_start_y[8];
	double move_end_x[8];
	double move_end_y[8];
	//初期値
	int def_move_time;
	int def_shot_time;

	EnemyBullet* bullet;
};

void SubBossForm(const char* file_name, int max, SubBoss& sub_boss);