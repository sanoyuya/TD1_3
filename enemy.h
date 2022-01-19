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
	void HitBox(Transform& transform, EnemyBullet& enemyBullet, int i);//�����蔻��
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
	int all_bullet_max;
	bool damage_flag[48];
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
	int bommer_img[10];
	int bommer_anime_timer;
	int bommer_anime;
	//�����l
	int def_explosion_time;

	//�摜
	int img[12];
	int img_r;
	int anime_timer;
	int anime;

	EnemyBullet* bullet; 
	Item* item;
	Mine* mine;
	

	MimeInitialize mime_initialize;

	//���{�X
	int move_rand;
	//�f�o�b�O�p


};

void EnemyForm(const char* file_name, int max, Enemy* enemy);

double easeInSine(double x);

int FlagSerch(bool flag[], int max);