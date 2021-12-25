#pragma once
#include"Dxlib.h"
#include"Transform.h"
#include"bullet.h"


class Player
{
private:
    int X;
    int Y;
    int R;
    int speed;
    int hp;
    int stelsflag;
    int stelscooltimer;
    int reflectionflag;
    int reflectioncooltimer;
    int stelsAfterglow = 0;
    int reflectionAfterglow = 0;
    int COOLTIME;
    int COOLTIMEtimer;
    int itemflag;
public:
    Player();
    void PlayerPadMove(char* keys, char* oldkeys);
    void HP(Transform transform, EnemyBullet bullet);
    void Draw();
    int GetX();
    int GetY();
    int Result();
};