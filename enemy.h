#pragma once
#include"bullet.h"
#include"Transform.h"
#include"player.h"

class Enemy
{
public:
	Enemy();
	~Enemy();
	void form(FILE* fp);
	void Move(Player& player);
	void Draw();
	void HitBox(Transform transform);

private:
	bool use_flag;
	int enemy_type;//�G�̃^�C�v
	Transform transform;//���W
	int hp;//�̗�
	int x_speed;//X���W�̃X�s�[�h
	int y_speed;//Y���W�̃X�s�[�h
	bool exising_flag;//���݃t���O
	bool action_flag;//�������ǂ����t���O
	bool damage_flag;
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



	EnemyBullet* bullet;
};
void EnemyForm(const char* file_name, int max, Enemy enemy[]);

