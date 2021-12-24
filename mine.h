#pragma once
#include"DxLib.h"
#include"Transform.h"

typedef struct//�������p
{
	int def_explosion_time;
	int def_bombs_time;
	int transform_xr;
	int transform_yr;
	int explosion_r;
}MimeInitialize;

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

	//�Z�b�^�[
	void SetMineFlag(bool flag);
	void SetRand(int end_frame);
	//�ݒu�t���O�𗧂Ă�

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
};
