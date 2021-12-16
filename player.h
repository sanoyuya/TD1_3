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
    int stelscooltimer;
    int reflectionflag;
    int reflectioncooltimer;
    int Afterglow;
    int itemflag;
public:
    void PlayerPadMove(char *keys,char *oldkeys);
    void Draw();
    Player();
};