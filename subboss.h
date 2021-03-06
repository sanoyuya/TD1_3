#pragma once
#include"Transform.h"
#include"mine.h"
class SubBoss
{
public:
	void form(FILE* fp);
	void Move(Player& player, bool reflection_flag,int flag, int screenshakeflag, int& shakeflag, int& damageflag, int& shaketime, int& damagetime, int& damageAlpha);//動き
	void Draw();//描画
	void HitBox(Transform& transform, EnemyBullet* enemyBullet, int i);//当たり判定
	void HP(Transform& transform, EnemyBullet& enemyBullet);//当たり判定
	void Refresh_ReflectionNum(int max);//反射回数変更
	void XMove(int x_speed,bool right_flag);
	void YMove(int y_speed,bool up_flag);
	void MineHit(Transform transform, int& hp, bool damage_flag);
	void PlayerMineHit(Player& player, int vibflag, int screenshakeflag, int& shakeflag, int& damageflag, int& shaketime, int& damagetime);

	Transform* GetBulletTransform(int num);
	EnemyBullet* GetEnmyBullet(int i);

	bool GetEnmyBulletFlag(int i);

	bool GetSubBossFlag();
	int GetAppearTime();
	int GetBulletMax();

	void SetMineExplosion();

	void PictureBookDraw(int x,int y,int num);
	SubBoss();
	~SubBoss();

private:

	int enemy_type;//敵のタイプ
	Transform transform;//座標
	Vertex vertex;
	int hp;//体力
	int bullet_x_speed;//弾のX座標のスピード
	int bullet_y_speed;//弾のY座標のスピード
	int x_speed = 10;//X座標のスピード
	int y_speed = 10;//Y座標のスピード
	bool exising_flag;//存在フラグ
	bool damage_flag[14];
	int shot_time;
	int bullet_max;
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
	int rand;
	bool move_flag;
	int move_time;
	int move_num;
	int move_frame;
	int move_end_frame;
	//初期値
	int def_move_time;
	int def_shot_time;
	//瞬間移動予備動作
	int anticipation;
	bool teleport_flag;

	int boss1_img[14];
	int boss2_img[19];
	int boss1_anime_timer;
	int boss1_anime;
	int boss2_anime_timer;
	int boss2_anime;
	int img_r;

	//爆発エフェクト
	int explosion_img[8];
	int explosion_img_anime;
	int explosion_img_anime_timer;
	bool explosion_flag;

	int teleport_flag_img_anime;
	int teleport_flag_img_anime_timer;
	int teleport_img[4];

	EnemyBullet* bullet[12];
	Mine* mine;
	MimeInitialize mime_initialize;


	bool damage_effect;
	int damage_img;
	int damage_effect_time;
	int damage_se;
	int knockdouwn_se;
};

void SubBossForm(const char* file_name, int max, SubBoss& sub_boss);