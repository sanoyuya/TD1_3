#include "DxLib.h"
#include"player.h"

Player::Player() {
    X = 300;
    Y = 200;
    R = 32;
    speed = 10;
    stelsflag = 0;
    reflectionflag = 0;
}

void Player::PlayerPadMove(char *keys,char *oldkeys)
{
    if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT) != 0)
    {
        X -= speed;
    }

    if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0)
    {
        X += speed;
    }

    if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) != 0)
    {
        Y -= speed;
    }

    if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) != 0)
    {
        Y += speed;
    }

    if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0)
    {
        reflectionflag = 1;
    }

    if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0)
    {
        stelsflag = 1;
    }

    if (keys[KEY_INPUT_J] == 1 && oldkeys[KEY_INPUT_J] == 0) {
        stelsflag = 1;
    }

    if (keys[KEY_INPUT_K] == 1 && oldkeys[KEY_INPUT_K] == 0) {
        reflectionflag = 1;
    }
}

void Player::Draw() {
    DrawBox(X - R, Y - R, X + R, Y + R, GetColor(255, 255, 255), true);
    DrawFormatString(0, 0, GetColor(255, 255, 255), "ステルスフラグ:%d", stelsflag);
    DrawFormatString(0, 20, GetColor(255, 255, 255), "反射フラグ:%d", reflectionflag);
}

