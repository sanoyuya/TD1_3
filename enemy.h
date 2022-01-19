#pragma once
#include"bullet.h"
#include"Transform.h"
#include"mine.h"

class Mine;

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
	void HitBox(Transform& transform, EnemyBullet& enemyBullet, int i);//当たり判定
	void TutorialHitBox(Transform transform, int num);
	void EnemyToEnemyHitBox(Enemy& enemy);
	void PlaterToEnemyHitBox(Player& player);
	void ExplosionBommer(Enemy& enemy);
	void HP(Transform transform, EnemyBullet& bullet);
	void XMove(int x_speed, bool right_flag);
	void YMove(int y_speed, bool up_flag);
	void Refresh_ReflectionNum(int max);
	bool BommerHitBox(Player& player);
	bool BommerHitBox(Transform transform);

	bool GetBulletFlag(int i);
	bool GetEnemyFlag();
	int GetAppearTime();
	EnemyBullet* GetEnmyBullet(int i);
	Transform* GetBulletTransform(int num);
	Transform GetTransform();
	int GetShotTime();

	void SetReflectionNum();
	void SetShotTime(int shot_time);
	void SetEnemyFlag(bool flag);


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
	int all_bullet_max;
	bool damage_flag[48];
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
	int bommer_img[10];
	int bommer_anime_timer;
	int bommer_anime;
	//初期値
	int def_explosion_time;

	//画像
	int img[12];
	int img_r;
	int anime_timer;
	int anime;

	EnemyBullet* bullet; 
	Item* item;
	Mine* mine;
	

	MimeInitialize mime_initialize;

	//中ボス
	int move_rand;
	//デバッグ用


};

void EnemyForm(const char* file_name, int max, Enemy* enemy);

double easeInSine(double x);

int FlagSerch(bool flag[], int max);