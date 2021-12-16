#include "DxLib.h"
#include"player.h"

Player::Player() {//�R���X�g���N�^�̒�`
    X = 300;
    Y = 200;
    R = 32;
    speed = 10;
    stelsflag = 0;
    stelscooltimer = -50;
    reflectionflag = 0;
    reflectioncooltimer = -50;
    Afterglow = 0;
    itemflag = 0;
}

void Player::PlayerPadMove(char *keys,char *oldkeys)//�v���C���[�̈ړ�
{
    if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT) != 0) {
        X -= speed;
    }

    if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0) {
        X += speed;
    }

    if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) != 0) {
        Y -= speed;
    }

    if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) != 0) {
        Y += speed;
    }

    if (reflectioncooltimer == -50 || stelscooltimer == -50) {
        if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0|| keys[KEY_INPUT_J] == 1 && oldkeys[KEY_INPUT_J] == 0) {
            Afterglow = 1;
            stelsflag = 1;
        }
    }
    if (itemflag == 10) {
        if (reflectioncooltimer == -50 || stelscooltimer == -50) {
            if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0 || keys[KEY_INPUT_K] == 1 && oldkeys[KEY_INPUT_K] == 0) {
                itemflag = 0;
                Afterglow = 1;
                reflectionflag = 1;
            }
        }
    } 

    if (Afterglow == 1) {//�㌄
        stelscooltimer++;
        if (stelsflag == 1) {//�X�e���X����
            if (stelscooltimer > 0) {
                stelsflag = 0;
            }
        }
        if (stelscooltimer > 50) {
            stelscooltimer = -50;
            Afterglow = 0;
        }
    }
   
    if (Afterglow == 1) {//�㌄
        reflectioncooltimer++;
        if (reflectionflag == 1) {//���ˎ���
            if (reflectioncooltimer > 0) {
                reflectionflag = 0;
            }
        }
        if (reflectioncooltimer > 50) {
            reflectioncooltimer = -50;
            Afterglow = 0;
        }
    }
    
}

void Player::Draw() {//�`��֐�
    DrawBox(X - R, Y - R, X + R, Y + R, GetColor(255, 255, 255), true);
    DrawFormatString(0, 0, GetColor(255, 255, 255), "�X�e���X�t���O:%d", stelsflag);
    DrawFormatString(0, 20, GetColor(255, 255, 255), "���˃t���O:%d", reflectionflag);
}

