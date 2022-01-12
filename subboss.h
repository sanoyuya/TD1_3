#pragma once
#include"Transform.h"
#include"mine.h"
class SubBoss
{
public:
	void form(FILE* fp);
	void Move(Player& player, bool reflection_flag);//動き
	void Draw();//描画
	void HitBox(Transform transform, bool* bullet_flag);//当たり判定
	void Refresh_ReflectionNum(int max);//反射回数変更
	void XMove(int x_speed,bool right_flag);
	void YMove(int y_speed,bool up_flag);



	Transform GetBulletTransform(int num);
	EnemyBullet* GetEnmyBullet();

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
	int rand;
	bool move_flag;
	int move_time;
	int move_num;
	int move_frame;
	int move_end_frame;
	//初期値
	int def_move_time;
	int def_shot_time;

	EnemyBullet* bullet;
	Mine* mine;
	MimeInitialize mime_initialize;
};

void SubBossForm(const char* file_name, int max, SubBoss& sub_boss);