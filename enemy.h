#pragma once
#include"bullet.h"
#include"Transform.h"
#include"mine.h"
#include"score.h"
class Mine;

void EnemyForm(const char* file_name, int max, Enemy** enemy, int wave_num);
void TutorialEnemyForm(const char* file_name, int max, Enemy** enemy);
double easeInSine(double x);

int FlagSerch(bool flag[], int max);
int FlagSerch(EnemyBullet** bullet, int max);
int GetEnemyMax(int& wave_num);

void TxtDraw(int x,int y, const char* file);

class Enemy
{
public:
	Enemy();
	~Enemy();
	void form(FILE* fp, int wave_num);
	void Tutorialform(FILE* fp);
	void Move(Player& player, bool reflection_flag, Score& score, Item* item, int wave_num, bool& movie_flag, char* keys, int num, int flag, int screenshakeflag, int& shakeflag, int& damageflag, int& shaketime,int& damagetime, bool& txt_shake_flag, int& damageAlpha);
	void TuTorialMove(int x, int y, int r, int& shot_flag, int stelsflag, int reflectionflag);
	void Draw(int num, int wave_num);
	void HitBox(Transform transform,int num, Item* item, Score* score);
	void HitBox(Transform& transform, EnemyBullet& enemyBullet, int i);//当たり判定
	void TutorialHitBox(Transform transform, int num);
	void EnemyToEnemyHitBox(Enemy& enemy);
	void PlaterToEnemyHitBox(Player& player, int enemy_num, int vibflag, int screenshakeflag, int& shakeflag, int& damageflag, int& shaketime, int& damagetime,int& damageAlpha);
	void ExplosionBommer(Enemy* enemy);
	void HP(Transform transform, EnemyBullet& bullet, Item* item, Score* score);
	void XMove(int x_speed, bool right_flag);
	void YMove(int y_speed, bool up_flag);
	void Refresh_ReflectionNum(int max);
	bool BommerHitBox(Player& player);
	bool BommerHitBox(Transform transform);

	bool GetBulletFlag(int i);
	bool GetEnemyFlag(int wave_num);
	int GetAppearTime();
	EnemyBullet* GetEnmyBullet(int i);
	Transform* GetBulletTransform(int num);
	Transform GetTransform();
	int GetShotTime();
	int GetBulletMax();
	bool GetExplosionFlag();
	int GetTxtFlag();
	int GetEnemyType();

	void SetReflectionNum();
	void SetShotTime(int shot_time);
	void SetEnemyFlag(bool flag);
	void SetExplosionFlag(bool flag);

	void PictureBookDraw(int scroll_x);
	void PictureBookMove();
	

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
	int img_Lv3[12];
	int img_Lv5[12];

	int img_r;
	int anime_timer;
	int anime;

	EnemyBullet* bullet[48]; 
	//Item* item;
	Mine* mine;
	

	MimeInitialize mime_initialize;

	//中ボス
	int move_rand;
	int easing_num;
	int rand;
	bool teleport_flag;
	int anticipation;

	int sub_boss1_img[14];
	int sub_boss1_anime;
	int sub_boss1_anime_timer;
	int sub_boss_buiiet_max;
	//ブーメラン
	int boomerang_img[10];
	int boomerang_anime_timer;
	int boomerang_anime;
	//爆発エフェクト
	int explosion_img[8];
	int explosion_img_anime;
	int explosion_img_anime_timer;
	bool explosion_flag;
	int txt_flag;

	//フォーメーション
	bool formation_fast_move_flag;

	int omnidirectional8_img[12];
	int omnidirectional16_img[12];
	int omnidirectional_anime;
	int omnidirectional_anime_timer;

	int invincible_time;//無敵時間

	int sub_boss2_img[14];
	int sub_boss2_anime;
	int sub_boss2_anime_timer;

	int teleport_flag_img_anime;
	int teleport_flag_img_anime_timer;
	int teleport_img[4];

	int formation_img[12];
	int formationLv3_img[12];
	int formation_img_anime;
	int formation_img_anime_timer;

	int laser_img_L[6];
	int laser_img_R[6];
	int laser_img_anime;
	int laser_img_anime_timer;
	int laser_leftand_right_judgment;
	//0レーザーじゃない
	//1左
	//2右

	bool push_flag;

	bool damage_effect;
	int damage_img;
	int damage_effect_time;
	
	int laser_sound;
	int douwn_sound;
	bool sound_flag;
	bool img_set;
	int ron_se;
	int damage_se;
 };
