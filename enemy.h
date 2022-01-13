#pragma once
#include"bullet.h"
#include"Transform.h"
#include"item.h"

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
	void EnemyToEnemyHitBox(Transform transform);
	void ExplosionBommer(Enemy& enemy, Player& player);
	void HP(Transform transform, EnemyBullet* bullet, int num);

	bool GetBulletFlag(int i);
	bool GetEnemyFlag();
	int GetAppearTime();
	EnemyBullet* GetEnmyBullet();
	Transform GetBulletTransform(int num);

	void SetReflectionNum();
	void SetShotTime(int shot_time);
	int GetShotTime();
	int color;
private:
	bool use_flag;//�g����
	int enemy_type;//�G�̃^�C�v
	Transform transform;//���W
	int hp;//�̗�
	int x_speed;//X���W�̃X�s�[�h
	int y_speed;//Y���W�̃X�s�[�h
	bool exising_flag;//���݃t���O
	bool action_flag;//�������ǂ����t���O
	bool shot_action_flag;//�ł��ǂ���
	int bullet_max;
	bool damage_flag[3];
	int shot_time;
	//�ŏ��̈ړ��̂��߂̕ϐ�
	int frame;
	int end_frame;
	double start_x;
	double start_y;
	double end_x;
	double end_y;
	bool fast_move_flag;
	int appear_time;
	//�ړ��̂��߂̕ϐ�
	bool move_flag;
	int move_time;
	int move_num;
	int move_frame;
	int move_end_frame;
	double move_start_x[4];
	double move_start_y[4];
	double move_end_x[4];
	double move_end_y[4];
	//�����l
	int def_move_time;
	int def_shot_time;

	//�{�}�[
	float angle;
	Vertex vertex;
	int explosion_time;
	bool explosion_bommer_flag;
	bool enemy_to_bommer;
	//�����l
	int def_explosion_time;

	EnemyBullet* bullet; 
	Item* item;

	//�f�o�b�O�p


};

void EnemyForm(const char* file_name, int max, Enemy* enemy);

double easeInSine(double x);

int FlagSerch(bool flag[], int max);