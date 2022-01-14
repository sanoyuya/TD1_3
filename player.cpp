#include "DxLib.h"
#include"player.h"
#include"enemy.h"

Player::Player() {//コンストラクタの定義
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

	//頼まれてたもの

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
		return 4;//ゲームオーバー画面へ
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
	if (Moveflag1 == 1) {//移動キーの操作説明で使うやつ
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

	//イージング
	if (easing_flag == 1)
	{
		//最初に座標代入
		if (easing_frame == 0)
		{
			easing_start_x = (double)X;
			easing_start_y = (double)Y;
		}

		easing_frame++;

		//計算して代入
		easing_x = easing_start_x + (easing_end_x - easing_start_x) * easeInSine(easing_frame / easing_end_frame);
		easing_y = easing_start_y + (easing_end_y - easing_start_y) * easeInSine(easing_frame / easing_end_frame);

		//座標に代入
		X = (int)easing_x;
		Y = (int)easing_y;

		//終わったら初期化
		if (easing_frame == easing_end_frame)
		{
			easing_frame = 0;
			easing_flag = 0;
			txtflag = 3;
		}
	}

	if (Moveflag2 == 1) {//敵の弾を避けるときに使うやつ
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
			//敵の弾が消えたら
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

	if (Moveflag3 == 1) {//ステルスチュートリアル
		if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0 || keys[KEY_INPUT_J] == 1 && oldkeys[KEY_INPUT_J] == 0) {
			stelsflag = 1;
			enemy[0].SetShotTime(5);
			shot_flag = 1;
		}

		if (stelsflag == 1) {
			//自機に向けない弾を出す
			//弾が画面外に出たら
			if (enemy[0].GetBulletFlag(0) == false && enemy[0].GetShotTime() == -1)
			{
				stelsflag = 0;
				txtflag = 9;
				Moveflag3 = 0;
			}
		}
	}

	if (Moveflag4 == 1) {//反射チュートリアル
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
				//自機に向けて弾を出す
				//敵が死んだら
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

void Player::Draw() {//描画関数
	DrawCircle(X, Y, R, GetColor(255, 255, 255), true);
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "ステルスフラグ:%d", stelsflag);
	//DrawFormatString(0, 20, GetColor(255, 255, 255), "反射フラグ:%d", reflectionflag);
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
			//テキストなし
			break;
		case 1:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "まずは操作説明を始めるね");
			break;
		case 2:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "Lスティック(絵)で移動出来る。試しに自由に動いてみて");
			break;
		case 3:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "ここに体力ゲージがあるの(わ)");
			break;
		case 4:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "このゲージが0になったら私たちの負け");
			break;
		case 5:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "危ない！敵の攻撃よ、避けて！");
			break;
		case 6:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "この宇宙船(？)は攻撃が出来ないから敵の攻撃で倒すしかない");
			break;
		case 7:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "攻撃が出来ない代わりに2つの防御スキルがあるの(わ)");
			break;
		case 8:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "まずはBボタン(絵)を押してみて");
			DrawFormatString(40, 916, GetColor(255, 255, 255), "一定時間の間、敵の視界から逸らすことが出来るの(わ)");
			break;
		case 9:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "今度はAボタン(絵)を押してみて");
			DrawFormatString(40, 916, GetColor(255, 255, 255), "バリアが張られている間、敵の弾を反射出来るの(わ)");
			break;
		case 10:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "本来はアイテムを20個集めないと使えないのだけど、今回は特別よ");
			break;
		case 11:
			DrawFormatString(40, 896, GetColor(255, 255, 255), "敵を倒せたみたいね");
			break;
		case 12:
			DrawFormatString(20, 896, GetColor(255, 255, 255), "アイテムがドロップしたみたい");
			DrawFormatString(20, 916, GetColor(255, 255, 255), "取りに行ってみましょう");
			break;
		case 13:
			DrawFormatString(20, 896, GetColor(255, 255, 255), "ここで持っているアイテムの数がわかるようになっているの(わ)");
			break;
		case 14:
			DrawFormatString(20, 896, GetColor(255, 255, 255), "これで操作説明は以上よ、一緒に頑張りましょう");
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

