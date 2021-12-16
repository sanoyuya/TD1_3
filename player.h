#pragma once
#include"Dxlib.h"

class Player
{
private:
    int X;
    int Y;
    int R;
    int speed;
    int stelsflag;
    int reflectionflag;
public:
    void PlayerPadMove(char *keys,char *oldkeys);
    void Draw();
    Player();
};