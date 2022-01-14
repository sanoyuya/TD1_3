#include "DxLib.h"
#include"player.h"
#include"enemy.h"

Player::Player() {//�R���X�g���N�^�̒�`
	X = 480;
	Y = 832;
	R = 32;
	speed = 7;
	hp = 20;
	stelsflag = 0;
	stelscooltimer = -50;
	reflectionflag = 0;
	reflectioncooltimer = -50;
	stelsAfterglow = 0;
	reflectionAfterglow = 0;
	COOLTIME = 0;
	COOLTIMEtimer = 0;
	itemflag = 0;
	Cgh = LoadGraph("resouce/enban.png");
	Moveflag1 = 0; Moveflag2 = 0; Moveflag2_2 = 0; Moveflag3 = 0; Moveflag4 = 0; Moveflag5 = 0; Move2time = 0; rightflag = 0; leftflag = 0;  Bflag = 0;  Aflag = 0;  CP = 25.0;
	txtflag = 1;
	pushflag = 1;

	//���܂�Ă�����

	easing_end_frame = 70;
	easing_end_x = (double)X;
	easing_end_y = (double)Y;
	easing_flag = 0;
	easing_frame = 0.0;
	easing_start_x = 0.0;
	easing_start_y = 0.0;
	easing_x = 0.0;
	easing_y = 0.0;

	shot_flag = 0;
}

void Player::PlayerPadMove(char* keys, char* oldkeys)//�v���C���[�̈ړ�
{
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT) != 0 || keys[KEY_INPUT_A] == 1) {
		X -= speed;
	}

	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0 || keys[KEY_INPUT_D] == 1) {
		X += speed;
	}

	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) != 0 || keys[KEY_INPUT_W] == 1) {
		Y -= speed;
	}

	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) != 0 || keys[KEY_INPUT_S] == 1) {
		Y += speed;
	}

	if (X <= 64) {
		X = 64;
	}if (X >= 896) {
		X = 896;
	}if (Y <= 64) {
		Y = 64;
	}if (Y >= 896) {
		Y = 896;
	}

	if (COOLTIMEtimer == 0) {
		if (reflectioncooltimer == -50 || stelscooltimer == -50) {//�X�e���X
			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0 || keys[KEY_INPUT_J] == 1 && oldkeys[KEY_INPUT_J] == 0) {
				stelsAfterglow = 1;
				stelsflag = 1;
				COOLTIME = 1;
			}
		}
	}
	if (itemflag == 10) {//����
		if (reflectioncooltimer == -50 || stelscooltimer == -50) {
			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0 || keys[KEY_INPUT_K] == 1 && oldkeys[KEY_INPUT_K] == 0) {
				itemflag = 0;
				reflectionAfterglow = 1;
				reflectionflag = 1;
			}
		}
	}

	if (stelsAfterglow == 1) {//�㌄
		stelscooltimer++;
		if (stelsflag == 1) {//�X�e���X����
			if (stelscooltimer > 0) {
				stelsflag = 0;
			}
		}
		if (stelscooltimer > 50) {
			stelscooltimer = -50;
			stelsAfterglow = 0;
		}
	}

	if (COOLTIME == 1) {//�X�e���X�̎g�p�p�x
		COOLTIMEtimer++;
		if (COOLTIMEtimer > 999) {
			COOLTIME = 0;
			COOLTIMEtimer = 0;
		}
	}

	if (reflectionAfterglow == 1) {//�㌄
		reflectioncooltimer++;
		if (reflectionflag == 1) {//���ˎ���
			if (reflectioncooltimer > 0) {
				reflectionflag = 0;
			}
		}
		if (reflectioncooltimer > 50) {
			reflectioncooltimer = -50;
			reflectionAfterglow = 0;
		}
	}

}

void Player::HP(Transform transform, EnemyBullet* bullet, int num) {

	if (*bullet[num].GetBulletFlag() == true)
	{
		if (((double)R * (double)R) > (((double)X - transform.x) * ((double)X - transform.x)) + (((double)Y - transform.y) * ((double)Y - transform.y))) {
			hp -= 1;
			bullet[num].SetBulletFlag(false);
		}
	}
}

void Player::TuTorialHP(Transform transform, EnemyBullet* bullet, int num, int& damage_flag) {

	if (*bullet[num].GetBulletFlag() == true)
	{
		if (((double)R * (double)R) > (((double)X - transform.x) * ((double)X - transform.x)) + (((double)Y - transform.y) * ((double)Y - transform.y))) {
			damage_flag = 1;
			bullet[num].SetBulletFlag(false);
		}
	}
}

int Player::GetX()
{
	return X;
}

int Player::GetY()
{
	return Y;
}

int Player::Getreflectionflag()
{
	return reflectionflag;
}

int Player::Getstelsflag()
{
	return stelsflag;
}

int Player::Result() {
	if (hp <= 0) {
		return 4;//�Q�[���I�[�o�[��ʂ�
	}
	else {
		return 2;
	}
	//if (�S�Ă̓G�����񂾂�) {
	//	return 4;//�Q�[���N���A��ʂ�
	//}
	//else {
	//	return 2;
	//}
}

void Player::TutorialMove(char* keys, char* oldkeys, Enemy enemy[], int& sceneflag) {
	if (keys[KEY_INPUT_SPACE] == 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0) {
		pushflag = 0;
	}
	switch (txtflag) {
		case 0:

			break;

		case 1:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 2;
				}
			}

			break;

		case 2:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 0;
					Moveflag1 = 1;
				}
			}

			break;

		case 3:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 4;
				}
			}

			break;

		case 4:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 5;
					EnemyForm("WAVE_ENEMY_DATA/Tutorial.csv", 5, enemy);
					shot_flag = 1;
				}
			}

			break;

		case 5:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 0;
					Moveflag2 = 1;
				}
			}

			break;

		case 6:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 7;
				}
			}

			break;

		case 7:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 8;
				}
			}

			break;

		case 8:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 0;
					Moveflag3 = 1;
				}
			}

			break;

		case 9:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 10;
				}
			}

			break;

		case 10:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 0;
					Moveflag4 = 1;
				}
			}

			break;

		case 11:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 12;
				}
			}

			break;

		case 12:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 0;
					Moveflag5 = 1;
				}
			}

			break;

		case 13:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 14;
				}
			}

			break;

		case 14:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 0;
					sceneflag = 2;
				}
			}

			break;
	}
	if (Moveflag1 == 1) {//�ړ��L�[�̑�������Ŏg�����
		if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) != 0 || keys[KEY_INPUT_W] == 1 || (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) != 0 || keys[KEY_INPUT_S] == 1 || (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0 || keys[KEY_INPUT_D] == 1 || (GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT) != 0 || keys[KEY_INPUT_A] == 1) {
			CP += 1;
			if (CP >= 125) {
				Moveflag1 = 0;

				if (txtflag == 0)
				{
					easing_flag = 1;
				}
			}
		}
		if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) != 0 || keys[KEY_INPUT_W] == 1) {
			Y -= speed;
		}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) != 0 || keys[KEY_INPUT_S] == 1) {
			Y += speed;
		}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0 || keys[KEY_INPUT_D] == 1) {
			X += speed;
		}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT) != 0 || keys[KEY_INPUT_A] == 1) {
			X -= speed;
		}
	}

	//�C�[�W���O
	if (easing_flag == 1)
	{
		//�ŏ��ɍ��W���
		if (easing_frame == 0)
		{
			easing_start_x = (double)X;
			easing_start_y = (double)Y;
		}

		easing_frame++;

		//�v�Z���đ��
		easing_x = easing_start_x + (easing_end_x - easing_start_x) * easeInSine(easing_frame / easing_end_frame);
		easing_y = easing_start_y + (easing_end_y - easing_start_y) * easeInSine(easing_frame / easing_end_frame);

		//���W�ɑ��
		X = (int)easing_x;
		Y = (int)easing_y;

		//�I������珉����
		if (easing_frame == easing_end_frame)
		{
			easing_frame = 0;
			easing_flag = 0;
			txtflag = 3;
		}
	}

	if (Moveflag2 == 1) {//�G�̒e�������Ƃ��Ɏg�����
		if (Moveflag2_2 == 0) {
			if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0 || keys[KEY_INPUT_D] == 1) {
				rightflag = 1;
				Moveflag2_2 = 1;
			}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT) != 0 || keys[KEY_INPUT_A] == 1) {
				leftflag = 1;
				Moveflag2_2 = 1;
			}
		}

		if (enemy[0].GetBulletFlag(0) == true)
		{
			if (rightflag == 1 && Moveflag2_2 == 1) {
				Move2time++;
				if (Move2time <= 20) {
					X += 5;
				}
				else {
					Move2time = 0;
					Moveflag2_2 = 2;
				}
			}if (leftflag == 1 && Moveflag2_2 == 1) {
				Move2time++;
				if (Move2time <= 20) {
					X -= 5;
				}
				else {
					Move2time = 0;
					Moveflag2_2 = 2;
				}
			}
		}

		HP(enemy[0].GetBulletTransform(0), enemy[0].GetEnmyBullet(), 0);

		if (enemy[0].GetBulletFlag(0) == false && enemy[0].GetShotTime() == -1)
		{
			//�G�̒e����������
			if (rightflag == 1) {
				Move2time++;
				if (Move2time <= 20) {
					X -= 5;
				}
				else {
					Moveflag2 = 0;
					txtflag = 6;
				}
			}
			else if (leftflag == 1) {
				Move2time++;
				if (Move2time <= 20) {
					X += 5;
				}
				else {
					Moveflag2 = 0;
					txtflag = 6;
				}
			}
		}
	}

	if (Moveflag3 == 1) {//�X�e���X�`���[�g���A��
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0 || keys[KEY_INPUT_J] == 1 && oldkeys[KEY_INPUT_J] == 0) {
			stelsflag = 1;
			enemy[0].SetShotTime(5);
			shot_flag = 1;
		}

		if (stelsflag == 1) {
			//���@�Ɍ����Ȃ��e���o��
			//�e����ʊO�ɏo����
			if (enemy[0].GetBulletFlag(0) == false && enemy[0].GetShotTime() == -1)
			{
				stelsflag = 0;
				txtflag = 9;
				Moveflag3 = 0;
			}
		}
	}

	if (Moveflag4 == 1) {//���˃`���[�g���A��
		if (pushflag == 0) {
			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0 || keys[KEY_INPUT_K] == 1 && oldkeys[KEY_INPUT_K] == 0) {
				reflectionflag = 1;
				enemy[0].SetShotTime(5);
				shot_flag = 1;
			}
		}

		if (reflectionflag == 1) {

			if (enemy[0].GetEnemyFlag() == false)
			{
				//���@�Ɍ����Ēe���o��
				//�G�����񂾂�
				reflectionflag = 0;
				txtflag = 11;
				itemflag = 1;
				Moveflag4 = 0;
			}

		}
	}

	if (Moveflag5 == 1) {
		if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) != 0 || keys[KEY_INPUT_W] == 1) {
			Y -= speed;
		}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) != 0 || keys[KEY_INPUT_S] == 1) {
			Y += speed;
		}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0 || keys[KEY_INPUT_D] == 1) {
			X += speed;
		}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT) != 0 || keys[KEY_INPUT_A] == 1) {
			X -= speed;
		}
		if (itemflag == 1) {
			if ((R * R) > ((X - 480) * (X - 480)) + ((Y - 128) * (Y - 128))) {
				itemflag = 0;
				txtflag = 13;
				Moveflag5 = 0;
			}
		}
	}

	enemy[0].TuTorialMove(X, Y, R, shot_flag, stelsflag, reflectionflag);

	if (X <= 64) {
		X = 64;
	}if (X >= 896) {
		X = 896;
	}if (Y <= 64) {
		Y = 64;
	}if (Y >= 896) {
		Y = 896;
	}
}

void Player::Draw() {//�`��֐�
	DrawCircle(X, Y, R, GetColor(255, 255, 255), true);
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "�X�e���X�t���O:%d", stelsflag);
	//DrawFormatString(0, 20, GetColor(255, 255, 255), "���˃t���O:%d", reflectionflag);
	//DrawFormatString(0, 40, GetColor(255, 255, 255), "stelscooltimer:%d", stelscooltimer);
	//DrawFormatString(0, 60, GetColor(255, 255, 255), "COOLTIMEtimer:%d", COOLTIMEtimer);
	//DrawFormatString(0, 80, GetColor(255, 255, 255), "hp:%d", hp);
	//DrawFormatString(0, 80, GetColor(255, 255, 255), "Afterglow:%d", Afterglow);
}

void Player::TutorialDraw() {
	DrawCircle(X, Y, R, GetColor(255, 255, 255), true);
	if (Moveflag1 == 1) {
		DrawCircleGauge(480, 240, CP, Cgh, 25.0);
	}
	switch (txtflag) {
		case 0:
			//�e�L�X�g�Ȃ�
			break;
		case 1:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "�܂��͑���������n�߂��");
			break;
		case 2:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "L�X�e�B�b�N(�G)�ňړ��o����B�����Ɏ��R�ɓ����Ă݂�");
			break;
		case 3:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "�����ɑ̗̓Q�[�W�������(��)");
			break;
		case 4:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "���̃Q�[�W��0�ɂȂ����玄�����̕���");
			break;
		case 5:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "��Ȃ��I�G�̍U����A�����āI");
			break;
		case 6:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "���̉F���D(�H)�͍U�����o���Ȃ�����G�̍U���œ|�������Ȃ�");
			break;
		case 7:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "�U�����o���Ȃ������2�̖h��X�L���������(��)");
			break;
		case 8:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "�܂���B�{�^��(�G)�������Ă݂�");
			DrawFormatString(40, 916, GetColor(255, 255, 255), "��莞�Ԃ̊ԁA�G�̎��E�����炷���Ƃ��o�����(��)");
			break;
		case 9:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "���x��A�{�^��(�G)�������Ă݂�");
			DrawFormatString(40, 916, GetColor(255, 255, 255), "�o���A�������Ă���ԁA�G�̒e�𔽎ˏo�����(��)");
			break;
		case 10:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "�{���̓A�C�e����20�W�߂Ȃ��Ǝg���Ȃ��̂����ǁA����͓��ʂ�");
			break;
		case 11:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "�G��|�����݂�����");
			break;
		case 12:
			DrawFormatString(20, 896, GetColor(255, 255, 255), "�A�C�e�����h���b�v�����݂���");
			DrawFormatString(20, 916, GetColor(255, 255, 255), "���ɍs���Ă݂܂��傤");
			break;
		case 13:
			DrawFormatString(20, 896, GetColor(255, 255, 255), "�����Ŏ����Ă���A�C�e���̐����킩��悤�ɂȂ��Ă����(��)");
			break;
		case 14:
			DrawFormatString(20, 896, GetColor(255, 255, 255), "����ő�������͈ȏ��A�ꏏ�Ɋ撣��܂��傤");
			break;
	}
	if (itemflag == 1) {
		DrawCircle(480, 128, 32, GetColor(255, 255, 255), false);
	}

}
int Player::GetR()
{
	return R;
}
//DrawFormatString(0, 0, GetColor(255, 255, 255), "txtflag:%d", txtflag);

