#include "DxLib.h"
#include"player.h"
#include"enemy.h"

Player::Player() {//コンストラクタの定義
	X = 300;
	Y = 200;
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
}

void Player::PlayerPadMove(char* keys, char* oldkeys)//プレイヤーの移動
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
		if (reflectioncooltimer == -50 || stelscooltimer == -50) {//ステルス
			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0 || keys[KEY_INPUT_J] == 1 && oldkeys[KEY_INPUT_J] == 0) {
				stelsAfterglow = 1;
				stelsflag = 1;
				COOLTIME = 1;
			}
		}
	}
	if (itemflag == 10) {//反射
		if (reflectioncooltimer == -50 || stelscooltimer == -50) {
			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0 || keys[KEY_INPUT_K] == 1 && oldkeys[KEY_INPUT_K] == 0) {
				itemflag = 0;
				reflectionAfterglow = 1;
				reflectionflag = 1;
			}
		}
	}

	if (stelsAfterglow == 1) {//後隙
		stelscooltimer++;
		if (stelsflag == 1) {//ステルス時間
			if (stelscooltimer > 0) {
				stelsflag = 0;
			}
		}
		if (stelscooltimer > 50) {
			stelscooltimer = -50;
			stelsAfterglow = 0;
		}
	}

	if (COOLTIME == 1) {//ステルスの使用頻度
		COOLTIMEtimer++;
		if (COOLTIMEtimer > 999) {
			COOLTIME = 0;
			COOLTIMEtimer = 0;
		}
	}

	if (reflectionAfterglow == 1) {//後隙
		reflectioncooltimer++;
		if (reflectionflag == 1) {//反射時間
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

void Player::HP(Transform transform, EnemyBullet* bullet) {

	if (*bullet->GetBulletFlag() == true)
	{
		if (((double)R * (double)R) > (((double)X - transform.x) * ((double)X - transform.x)) + (((double)Y - transform.y) * ((double)Y - transform.y))) {
			hp -= 1;
			bullet->SetBulletFlag(false);
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

int Player::Result() {
	if (hp <= 0) {
		return 3;//ゲームオーバー画面へ
	}
	else {
		return 2;
	}
	//if (全ての敵が死んだら) {
	//	return 4;//ゲームクリア画面へ
	//}
	//else {
	//	return 2;
	//}
}

void Player::Draw() {//描画関数
	DrawBox(X - R, Y - R, X + R, Y + R, GetColor(255, 255, 255), true);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "ステルスフラグ:%d", stelsflag);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "反射フラグ:%d", reflectionflag);
	DrawFormatString(0, 40, GetColor(255, 255, 255), "stelscooltimer:%d", stelscooltimer);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "COOLTIMEtimer:%d", COOLTIMEtimer);
	DrawFormatString(0, 80, GetColor(255, 255, 255), "hp:%d", hp);
	//DrawFormatString(0, 80, GetColor(255, 255, 255), "Afterglow:%d", Afterglow);
}

