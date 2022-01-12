#pragma once
#include"Transform.h"
#include"mine.h"
class SubBoss
{
public:
	void form(FILE* fp);
	void Move(Player& player, bool reflection_flag);//����
	void Draw();//�`��
	void HitBox(Transform transform, bool* bullet_flag);//�����蔻��
	void Refresh_ReflectionNum(int max);//���ˉ񐔕ύX
	void XMove(int x_speed,bool right_flag);
	void YMove(int y_speed,bool up_flag);



	Transform GetBulletTransform(int num);
	EnemyBullet* GetEnmyBullet();

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
	int rand;
	bool move_flag;
	int move_time;
	int move_num;
	int move_frame;
	int move_end_frame;
	//�����l
	int def_move_time;
	int def_shot_time;

	EnemyBullet* bullet;
	Mine* mine;
	MimeInitialize mime_initialize;
};

void SubBossForm(const char* file_name, int max, SubBoss& sub_boss);