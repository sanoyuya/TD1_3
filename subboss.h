#pragma once
#include"Transform.h"
#include"mine.h"
class SubBoss
{
public:
	void form(FILE* fp);
	void Move(Player& player, bool reflection_flag);//����
	void Draw();//�`��
	void HitBox(Transform& transform, EnemyBullet* enemyBullet, int i);//�����蔻��
	void HP(Transform& transform, EnemyBullet& enemyBullet);//�����蔻��
	void Refresh_ReflectionNum(int max);//���ˉ񐔕ύX
	void XMove(int x_speed,bool right_flag);
	void YMove(int y_speed,bool up_flag);
	void MineHit(Transform transform, int& hp, bool damage_flag);
	void PlayerMineHit(Player& player);

	Transform* GetBulletTransform(int num);
	EnemyBullet* GetEnmyBullet(int i);

	bool GetEnmyBulletFlag(int i);

	bool GetSubBossFlag();
	int GetAppearTime();
	int GetBulletMax();

	void SetMineExplosion();

	SubBoss();
	~SubBoss();

private:

	int enemy_type;//�G�̃^�C�v
	Transform transform;//���W
	Vertex vertex;
	int hp;//�̗�
	int bullet_x_speed;//�e��X���W�̃X�s�[�h
	int bullet_y_speed;//�e��Y���W�̃X�s�[�h
	int x_speed = 10;//X���W�̃X�s�[�h
	int y_speed = 10;//Y���W�̃X�s�[�h
	bool exising_flag;//���݃t���O
	bool damage_flag[14];
	int shot_time;
	int bullet_max;
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
	int rand;
	bool move_flag;
	int move_time;
	int move_num;
	int move_frame;
	int move_end_frame;
	//�����l
	int def_move_time;
	int def_shot_time;
	//�u�Ԉړ��\������
	int anticipation;
	bool teleport_flag;

	int boss1_img[14];
	int boss1_anime_timer;
	int boss1_anime;
	int img_r;



	EnemyBullet* bullet[12];
	Mine* mine;
	MimeInitialize mime_initialize;
};

void SubBossForm(const char* file_name, int max, SubBoss& sub_boss);