#pragma once
#include"bullet.h"
#include"Transform.h"


class Enemy
{
public:
	Enemy();
	~Enemy();
	void form(FILE* fp);
	void Move(Player& player, bool reflection_flag);
	void TuTorialMove(int x, int y, int r, int& shot_flag, int stelsflag, int reflectionflag);
	void Draw(int num);
	void HitBox(Transform transform,int num);
	void TutorialHitBox(Transform transform, int num);
	void EnemyToEnemyHitBox(Transform transform);
	void PlaterToEnemyHitBox(Player& player);
	void ExplosionBommer(Enemy& enemy, Player& player);
	void HP(Transform transform, EnemyBullet& bullet);

	bool GetBulletFlag(int i);
	bool GetEnemyFlag();
	int GetAppearTime();
	EnemyBullet* GetEnmyBullet(int i);
	Transform* GetBulletTransform(int num);
	Transform GetTransform();

	void SetReflectionNum();
	void SetShotTime(int shot_time);
	int GetShotTime();

	int color;

private:
	bool use_flag;//使うか
	int enemy_type;//敵のタイプ
	Transform transform;//座標
	int hp;//体力
	int x_speed;//X座標のスピード
	int y_speed;//Y座標のスピード
	bool exising_flag;//存在フラグ
	bool action_flag;//動くかどうかフラグ
	bool shot_action_flag;//打つかどうか
	int bullet_max;
	bool damage_flag[3];
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
	double move_start_x[4];
	double move_start_y[4];
	double move_end_x[4];
	double move_end_y[4];
	//初期値
	int def_move_time;
	int def_shot_time;

	//ボマー
	float angle;
	Vertex vertex;
	int explosion_time;
	bool explosion_bommer_flag;
	bool enemy_to_bommer;
	//初期値
	int def_explosion_time;

	//画像
	int img[12];
	int img_r;
	int anime_timer;
	int anime;

	EnemyBullet* bullet; 
	Item* item;

	//デバッグ用


};

void EnemyForm(const char* file_name, int max, Enemy* enemy);

double easeInSine(double x);

int FlagSerch(bool flag[], int max);