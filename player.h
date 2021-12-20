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
    int stelsAfterglow = 0;
    int reflectionAfterglow = 0;
    int COOLTIME;
    int COOLTIMEtimer;
    int itemflag;
    int GetX();
    int GetY();
public:
    void PlayerPadMove(char *keys,char *oldkeys);
    void Draw();
    Player();
};