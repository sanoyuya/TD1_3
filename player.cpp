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
	txt1 = LoadGraph("resouce/text_1.png"); txt2 = LoadGraph("resouce/text_2.png"); txt3 = LoadGraph("resouce/text_3.png");
	txt4 = LoadGraph("resouce/text_4.png"); txt5 = LoadGraph("resouce/text_5.png"); txt6 = LoadGraph("resouce/text_6.png");
	txt7 = LoadGraph("resouce/text_7.png"); txt8 = LoadGraph("resouce/text_8.png"); txt9 = LoadGraph("resouce/text_9.png");
	txt10 = LoadGraph("resouce/text_10.png"); txt11 = LoadGraph("resouce/text_11.png"); txt12 = LoadGraph("resouce/text_12.png");
	txt13 = LoadGraph("resouce/text_13.png"); txt14 = LoadGraph("resouce/text_14.png"); txt15 = LoadGraph("resouce/text_15.png");
	txt16 = LoadGraph("resouce/text_16.png"); txt17 = LoadGraph("resouce/text_17.png"); A = LoadGraph("resouce/A.png");
	Apflag = 0; Apushflag = 0; SetAtime = 0;

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
					txtflag = 9;
				}
			}

			break;

		case 9:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 0;
					Moveflag3 = 1;
				}
			}

			break;

		case 10:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 11;

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
					txtflag = 13;
				}
			}

			break;

		case 13:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 0;
					Moveflag4 = 1;
				}
			}

			break;

		case 14:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 15;
				}
			}

			break;

		case 15:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 0;
					Moveflag5 = 1;
				}
			}

			break;

		case 16:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 17;
				}
			}

		case 17:
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
			if (rightflag == 0 && leftflag == 0) {
				Moveflag2 = 0;
				txtflag = 6;
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
				txtflag = 10;
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
				txtflag = 14;
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
				txtflag = 16;
				Moveflag5 = 0;
			}
		}
	}

	SetAtime++;
	if (Apushflag == 0) {
		if (SetAtime >= 25) {
			Apushflag = 1;
			SetAtime = 0;
		}
	}
	else {
		if (SetAtime >= 25) {
			Apushflag = 0;
			SetAtime = 0;
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
	DrawCircle(X, Y, R, GetColor(25, 25, 25), true);

	if (Moveflag1 == 1) {
		DrawCircleGauge(480, 240, CP, Cgh, 25.0);
	}
	switch (txtflag) {
		case 0:
			//�e�L�X�g�Ȃ�
			break;
		case 1:
			DrawGraph(47, 719, txt1, true);//�܂��͊ȒP�ȑ���������n�߂��(��)
			break;
		case 2:
			DrawGraph(47, 719, txt2, true);//L�X�e�B�b�N(�G)�ňړ��o����B�����Ɏ��R�ɓ����Ă݂�
			break;
		case 3:
			DrawGraph(47, 719, txt3, true);//�����ɑ̗̓Q�[�W�������(��)
			break;
		case 4:
			DrawGraph(47, 719, txt4, true);//
			break;
		case 5:
			DrawGraph(47, 719, txt5, true);
			break;
		case 6:
			DrawGraph(47, 719, txt6, true);
			break;
		case 7:
			DrawGraph(47, 719, txt7, true);
			break;
		case 8:
			DrawGraph(47, 719, txt8, true);
			break;
		case 9:
			DrawGraph(47, 719, txt9, true);
			break;
		case 10:
			DrawGraph(47, 719, txt10, true);
			break;
		case 11:
			DrawGraph(47, 719, txt11, true);
			break;
		case 12:
			DrawGraph(47, 719, txt12, true);
			break;
		case 13:
			DrawGraph(47, 719, txt13, true);
			break;
		case 14:
			DrawGraph(47, 719, txt14, true);
			break;
		case 15:
			DrawGraph(47, 719, txt15, true);
			break;
		case 16:
			DrawGraph(47, 719, txt16, true);
			break;
		case 17:
			DrawGraph(47, 719, txt17, true);
			break;
	}
	if (itemflag == 1) {
		DrawCircle(480, 128, 32, GetColor(255, 255, 255), false);
	}
	DrawFormatString(40, 80, GetColor(255, 255, 255), "txtflag:%d", txtflag);
	if (txtflag != 0) {
		if (Apushflag == 0) {
			DrawRotaGraph3(880, 874, 32, 32, 0.5, 0.5, 0.0, A, true, false);
		}
		else {
			SetDrawBright(100, 100, 100);
			DrawRotaGraph3(880, 874, 32, 32, 0.5, 0.5, 0.0, A, true, false);
			SetDrawBright(255, 255, 255);
		}
		
	}
}
int Player::GetR()
{
	return R;
}

