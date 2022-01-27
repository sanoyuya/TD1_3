#pragma once
#include"Transform.h"

typedef struct//�������p
{
	int def_explosion_time;
	int def_bombs_time;
	int transform_xr;
	int transform_yr;
	int explosion_r;
}MimeInitialize;

class Player;

class Mine
{
public:
	Mine();//�R���g���X�^
	~Mine();//�f�X�g���N�^
	void form(Transform transForm, int& frame);//����
	void HitBox(Transform transform, int& hp);//�����蔻��
	void Move();//����
	void Draw();//�`��
	void initialize(MimeInitialize& mimeinitialize);//������
	void HitBox(Transform transform, int& hp, bool damage_flag);
	void PlayerHitBox(Player& player);
	//�Z�b�^�[
	void SetMineFlag(bool flag);
	void SetRand(int end_frame);
	void SetExplosionTime(int num);

private:
	int rand;//�����_��
	bool damage_flag;//1�_���[�W�����^���Ȃ��悤�ɂ���t���O
	Transform transform[10];//���W
	int explosion_r;//�����̔��a
	int explosion_time[10];//��������܂ł̎���
	bool explosion_flag[10];//�����t���O
	int bombs_time[10];//�������Ă��鎞��
	bool exising_flag[10];//���݃t���O
	bool mine_flag;//�n����u���t���O

	//�����l
	int def_explosion_time;
	int def_bombs_time;

	int mine_img[10];
	int mine_anime_timer[10];
	int mine_anime[10];
	int mine_r;

	//�����G�t�F�N�g
	int explosion_img[8];
	int explosion_img_anime[10];
	int explosion_img_anime_timer[10];
};

