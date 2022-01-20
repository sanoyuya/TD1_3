#include "DxLib.h"
#include"player.h"
#include"enemy.h"
#include"item.h"

Player::Player() {//コンストラクタの定義
	X = 480;
	Y = 832;
	R = 32;
	speed = 7;
	hp = 20;
	stelsflag = 0;
	stelscooltimer = 250;
	reflectionflag = 0;
	reflectioncooltimer = -250;
	stelsAfterglow = 0;
	reflectionAfterglow = 0;
	COOLTIME = 0;
	COOLTIMEtimer = 0;
	itemflag = 0; scoreitem = 0;
	Cgh = LoadGraph("resouce/enban.png");
	Moveflag1 = 0; Moveflag2 = 0; Moveflag2_2 = 0; Moveflag3 = 0; Moveflag4 = 0; Moveflag5 = 0; Move2time = 0;rightflag = 0; leftflag = 0;  Bflag = 0;  Aflag = 0;  CP = 25.0;
	txtflag = 1;
	pushflag = 1;
	txt1 = LoadGraph("resouce/text_1.png"); txt2 = LoadGraph("resouce/text_2.png"); txt3 = LoadGraph("resouce/text_3.png");
	txt4 = LoadGraph("resouce/text_4.png"); txt5 = LoadGraph("resouce/text_5.png"); txt6 = LoadGraph("resouce/text_6.png");
	txt7 = LoadGraph("resouce/text_7.png"); txt8 = LoadGraph("resouce/text_8.png"); txt9 = LoadGraph("resouce/text_9.png");
	txt10 = LoadGraph("resouce/text_10.png"); txt11 = LoadGraph("resouce/text_11.png"); txt12 = LoadGraph("resouce/text_12.png");
	txt13 = LoadGraph("resouce/text_13.png"); txt14 = LoadGraph("resouce/text_14.png"); txt15 = LoadGraph("resouce/text_15.png");
	txt16 = LoadGraph("resouce/text_16.png"); txt17 = LoadGraph("resouce/text_17.png"); A = LoadGraph("resouce/A.png");
	option = LoadGraph("≡skip.png"); HPgh = LoadGraph("resouce/HP.png"); MPgh = LoadGraph("resouce/MP.png");
	Apflag = 0; Apushflag = 0; SetAtime = 0;
	itemline = LoadGraph("resouce/ItemGauge.png"); itemback = LoadGraph("resouce/ItemColor.png"); bigitem = LoadGraph("resouce/ReflectionItem_ver2.png");
	Alpha = 36;
	nohitflag = 0;

	//頼まれてたもの
	itemflag2 = 0;

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
	anime = 0;
	anime_timer = 0;
	hp_img = LoadGraph("resouce/HP1.png");

	img_r = 48;
	LoadDivGraph("resouce/player.png", 16, 16, 1, 96, 96, img);
	tutorial_item = new Item;

	item_x[0] = 1008;
	item_x[1] = 1120;
	item_x[2] = 1233;
	item_y[0] = 752;
	item_y[1] = 848;
	item_r = 32;
	item_img = LoadGraph("resouce/ReflectionItem.png");

	reflection_img = LoadGraph("resouce/Reflection.png");
	reflection_r = 56;

	LoadDivGraph("resouce/playerStealth.png", 16, 16, 1, 112, 112, stealth_img);
	stealth_img_r = 56;
	stealth_anime_timer = 0;
	stealth_anime = 0;
	damage_flag[0] = 0;

	item_1_img = LoadGraph("resouce/item1big.png");
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
		if (reflectionflag == 0 && stelscooltimer == 250) {//ステルス
			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0 || keys[KEY_INPUT_J] == 1 && oldkeys[KEY_INPUT_J] == 0) {
				stelscooltimer = -150;//ステルス効果時間
				stelsAfterglow = 1;
				stelsflag = 1;
			}
		}
	}
	if (itemflag == 6) {//反射
		if (reflectioncooltimer == -250 && stelsflag == 0) {
			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0 || keys[KEY_INPUT_K] == 1 && oldkeys[KEY_INPUT_K] == 0) {
				itemflag = 0;
				reflectionAfterglow = 1;
				reflectionflag = 1;
			}
		}
	}

	if (stelsflag == 1) {
		speed = 4;
	}
	else {
		speed = 7;
	}

	if (stelsAfterglow == 1) {
		stelscooltimer++;
		if (stelsflag == 1) {
			if (stelscooltimer > 0) {
				stelsflag = 0;
			}
		}
		if (stelscooltimer > 250) {//ステルス後隙
			stelscooltimer = 250;
			stelsAfterglow = 0;
		}
	}

	if (reflectionAfterglow == 1) {
		reflectioncooltimer++;
		if (reflectionflag == 1) {
			if (reflectioncooltimer > 0) {
				reflectionflag = 0;
			}
		}
		if (reflectioncooltimer > 0) {//後隙
			reflectioncooltimer = -250;//反射時間
			reflectionAfterglow = 0;
		}
	}

	if (hp < 20) {
		nohitflag = 1;
	}

	anime_timer++;

	if (anime_timer == 16 * 6)
	{
		anime_timer = 0;
	}

	anime = anime_timer / 6;

	if (stelsflag == 1)
	{
		stealth_anime_timer++;

		if (stealth_anime_timer == 16 * 6)
		{
			stealth_anime_timer = 0;
		}

		stealth_anime = stealth_anime_timer / 6;
	}
}

void Player::HP(Transform transform, EnemyBullet& bullet) {

	if (*bullet.GetBulletFlag() == true)
	{
		if (((double)R * (double)R) > (((double)X - transform.x) * ((double)X - transform.x)) + (((double)Y - transform.y) * ((double)Y - transform.y))) {
			
			if (reflectionflag == 0)
			{
				hp -= 1;
			}
			bullet.SetBulletFlag(false);
		}
	}
}

void Player::TuTorialHP(Transform transform, EnemyBullet& bullet, int& damage_flag) {

	if (*bullet.GetBulletFlag() == true)
	{
		if (((double)R * (double)R) > (((double)X - transform.x) * ((double)X - transform.x)) + (((double)Y - transform.y) * ((double)Y - transform.y))) {
			damage_flag = 1;
			bullet.SetBulletFlag(false);
		}
	}
}

void Player::ItemFlagAdd(int num, Score& score )
{
	if (itemflag < 6)
	{
		itemflag += num;
	}

	scoreitem += num;

	score.Setscoreitem(scoreitem);

}

int Player::GetHp()
{
	return hp;
}

int Player::GetReflectionR()
{
	return reflection_r;
}

int Player::GetDamageFlag(int num)
{
	return damage_flag[num];
}

void Player::HpSub(int num)
{
	hp -= num;
}

void Player::SetDamageFlag(int i,int num)
{
	damage_flag[i] = num;
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

int Player::Getnohitflag() {
	return nohitflag;
}

int Player::Getscoreitem() {
	return scoreitem;
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

#pragma region チュートリアル
void Player::TutorialMove(char* keys, char* oldkeys, Enemy enemy[], int& sceneflag, int& wave_num) {
	if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) != 0 || keys[KEY_INPUT_H] == 1 && oldkeys[KEY_INPUT_H] == 0)
	{
		X = 480;
		Y = 832;
		sceneflag = 2;
		wave_num = 1;
	}
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

				}
			}

			break;

		case 5:
			if (pushflag == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflag = 1;
					txtflag = 0;
					Moveflag2 = 1;
					EnemyForm("WAVE_ENEMY_DATA/Tutorial.csv", 5, enemy);
					shot_flag = 1;
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
					itemflag = 6;
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
					X = 480;
					Y = 832;
					sceneflag = 2;
					wave_num = 1;
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
		if (enemy[0].GetBulletFlag(0) == true)
		{
			if (Moveflag2_2 == 0) {
				if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0 || keys[KEY_INPUT_D] == 1) {
					rightflag = 1;
					Moveflag2_2 = 1;
				}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT) != 0 || keys[KEY_INPUT_A] == 1) {
					leftflag = 1;
					Moveflag2_2 = 1;
				}
			}
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

		HP(*enemy[0].GetBulletTransform(0), *enemy[0].GetEnmyBullet(0));

		if (enemy[0].GetBulletFlag(0) == false && enemy[0].GetShotTime() == -1)
		{
			if (rightflag == 1 || leftflag == 1) {
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
					Moveflag2 = 0;
					txtflag = 6;
				}
			}
			else {
				Moveflag2 = 0;
				txtflag = 6;
			}
		}
	}

	if (Moveflag3 == 1) {//ステルスチュートリアル
		if (COOLTIMEtimer == 0) {
			if (reflectionflag == 0 && stelscooltimer == 250) {//ステルス
				if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0 || keys[KEY_INPUT_J] == 1 && oldkeys[KEY_INPUT_J] == 0) {
					stelscooltimer = -150;//ステルス効果時間
					stelsAfterglow = 1;
					stelsflag = 1;
					enemy[0].SetShotTime(5);
					shot_flag = 1;
				}
			}
		}

		if (stelsflag == 1) {

			stealth_anime_timer++;

			if (stealth_anime_timer == 16 * 6)
			{
				stealth_anime_timer = 0;
			}

			stealth_anime = stealth_anime_timer / 6;

			//自機に向けない弾を出す
			//弾が画面外に出たら
			if (enemy[0].GetBulletFlag(0) == false && enemy[0].GetShotTime() == -1)
			{
				stelsflag = 0;
				txtflag = 10;
				Moveflag3 = 0;
			}
		}
	}

	if (stelsAfterglow == 1) {
		stelscooltimer++;
		if (stelsflag == 1) {
			if (stelscooltimer > 0) {
				stelsflag = 0;
			}
		}
		if (stelscooltimer > 250) {//ステルス後隙
			stelscooltimer = 250;
			stelsAfterglow = 0;
		}
	}

	if (Moveflag4 == 1) {//反射チュートリアル
		if (pushflag == 0 && reflectionflag == 0) {
			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0 || keys[KEY_INPUT_K] == 1 && oldkeys[KEY_INPUT_K] == 0) {
				reflectionflag = 1;
				enemy[0].SetShotTime(5);
				shot_flag = 1;
				itemflag = 0;
			}
		}

		if (reflectionflag == 1) {

			if (enemy[0].GetEnemyFlag() == false)
			{
				//自機に向けて弾を出す
				//敵が死んだら
				reflectionflag = 0;
				txtflag = 14;
				itemflag2 = 1;
				Moveflag4 = 0;

				tutorial_item->TutorialForm(enemy[0].GetTransform(), itemflag2);
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

		if (tutorial_item->TutorialMove(X, Y, R, itemflag2) == true) {

			itemflag = 1;
			txtflag = 16;
			Moveflag5 = 0;

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

	anime_timer++;

	if (anime_timer == 16 * 6)
	{
		anime_timer = 0;
	}

	anime = anime_timer / 6;

}
#pragma endregion

void Player::Draw() {//描画関数
	float CHP = hp * 5.0f + 25.0f;
	float CMP = stelscooltimer * 0.4f + 25.0f;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);//アルファ
	DrawGraph(1088, 680, bigitem, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, Alpha);//ノーブレンド
	DrawGraph(966, 558, itemline, true);

	//体力
	if (hp > 10)
	{
		SetDrawBright(153, 229, 80);
	}
	else if (hp > 4)
	{
		SetDrawBright(255, 239, 15);
	}
	else
	{
		SetDrawBright(255, 25, 0);
	}

	DrawCircleGauge(966 + 186, 558 + 186, CHP, HPgh, 25.0);

	SetDrawBright(255, 255, 255);

	//ステルスゲージ
	SetDrawBright(0x00, 0xFF, 0xFF);
	DrawCircleGauge(966 + 186, 558 + 186, CMP, MPgh, 25.0);
	SetDrawBright(255, 255, 255);

	//時機
	if (stelsflag == 1)
	{
		DrawGraph(X - stealth_img_r, Y - stealth_img_r, stealth_img[stealth_anime], true);
	}
	else
	{
		DrawGraph(X - img_r, Y - img_r, img[anime], true);
	}

	//バリア
	if (reflectionflag == 1)
	{
		DrawGraph(X - reflection_r, Y - reflection_r, reflection_img, true);
	}

	//アイテム取得数
	if (itemflag == 0)
	{
		Alpha = 36;
	}
	if (itemflag == 1)
	{
		
		Alpha = 72;
	}
	if (itemflag == 2)
	{
		Alpha = 108;
	}
	if (itemflag == 3)
	{
		Alpha = 144;
	}
	if (itemflag == 4)
	{
		Alpha = 180;
	}
	if (itemflag == 5)
	{
		Alpha = 216;
	}
	if (itemflag == 6)
	{
		Alpha = 255;
	}

	DrawFormatString(0, 60, GetColor(255, 255, 255), "ステルスフラグ:%d", stelsflag);
	DrawFormatString(0, 80, GetColor(255, 255, 255), "反射フラグ:%d", reflectionflag);
	DrawFormatString(0, 100, GetColor(255, 255, 255), "stelscooltimer:%d", stelscooltimer);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "COOLTIMEtimer:%d", COOLTIMEtimer);
	//DrawFormatString(0, 80, GetColor(255, 255, 255), "hp:%d", hp);
	//DrawFormatString(0, 80, GetColor(255, 255, 255), "Afterglow:%d", Afterglow);
}

void Player::D() {
	SetDrawBright(0xff,0xff,0x00);
	if (itemflag == 1) {
		DrawExtendGraph(1000, 790, 1300, 900, itemback, true);
	}if (itemflag == 2) {
		DrawExtendGraph(800, 750, 1400, 900, itemback, true);
	}if (itemflag == 3) {
		DrawExtendGraph(800, 702, 1400, 900, itemback, true);
	}if (itemflag == 4) {
		DrawExtendGraph(800, 628, 1400, 1000, itemback, true);
	}if (itemflag == 5) {
		DrawExtendGraph(800, 589, 1400, 1000, itemback, true);
	}if (itemflag == 6) {
		DrawExtendGraph(800, 500, 1400, 1100, itemback, true);
	}
	SetDrawBright(255,255,255);
}

#pragma region チュートリアル
void Player::TutorialDraw() {

	float CHP = hp * 5.0f + 25.0f;
	float CMP = stelscooltimer * 0.4f + 25.0f;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Alpha);//アルファ
	DrawGraph(1088, 680, bigitem, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, Alpha);//ノーブレンド
	DrawGraph(966, 558, itemline, true);

	//DrawCircle(X, Y, R, GetColor(25, 25, 25), true);

	tutorial_item->Draw();

	//時機
	if (stelsflag == 1)
	{
		DrawGraph(X - stealth_img_r, Y - stealth_img_r, stealth_img[stealth_anime], true);
	}
	else
	{
		DrawGraph(X - img_r, Y - img_r, img[anime], true);
	}

	if (reflectionflag == 1)
	{
		DrawGraph(X - reflection_r, Y - reflection_r, reflection_img, true);
	}
	if (hp > 10)
	{
		SetDrawBright(153, 229, 80);
	}
	else if (hp > 4)
	{
		SetDrawBright(255, 239, 15);
	}
	else
	{
		SetDrawBright(255, 25, 0);
	}

	DrawCircleGauge(966 + 186, 558 + 186, CHP, HPgh, 25.0);

	SetDrawBright(255, 255, 255);

	if (Moveflag1 == 1) {
		DrawCircleGauge(480, 240, CP, Cgh, 25.0);
	}

	//ステルスゲージ
	SetDrawBright(0x00, 0xFF, 0xFF);
	DrawCircleGauge(966 + 186, 558 + 186, CMP, MPgh, 25.0);
	SetDrawBright(255, 255, 255);

	switch (txtflag) {
		case 0:
			//テキストなし
			break;
		case 1:
			DrawGraph(47, 719, txt1, true);//まずは簡単な操作説明を始めるね(わ)
			break;
		case 2:
			DrawGraph(47, 719, txt2, true);//Lスティック(絵)で移動出来る。試しに自由に動いてみて
			break;
		case 3:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 185);
			DrawBox(0, 0, 1376, 960, GetColor(0, 0, 0), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			SetDrawBright(153, 229, 80);
			DrawCircleGauge(966 + 186, 558 + 186, CHP, HPgh, 25.0);
			SetDrawBright(255, 255, 255);

			DrawGraph(47, 719, txt3, true);//ここに体力ゲージがあるの(わ)

			break;
		case 4:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 185);
			DrawBox(0, 0, 1376, 960, GetColor(0, 0, 0), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			SetDrawBright(153, 229, 80);
			DrawCircleGauge(966 + 186, 558 + 186, CHP, HPgh, 25.0);
			SetDrawBright(255, 255, 255);

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
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 185);
			DrawBox(0, 0, 1376, 960, GetColor(0, 0, 0), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			SetDrawBright(0x00, 0xFF, 0xFF);
			DrawCircleGauge(966 + 186, 558 + 186, CMP, MPgh, 25.0);
			SetDrawBright(255, 255, 255);

			DrawGraph(47, 719, txt8, true);
			break;
		case 9:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 185);
			DrawBox(0, 0, 1376, 960, GetColor(0, 0, 0), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			SetDrawBright(0x00, 0xFF, 0xFF);
			DrawCircleGauge(966 + 186, 558 + 186, CMP, MPgh, 25.0);
			SetDrawBright(255, 255, 255);

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
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 185);
			DrawBox(0, 0, 1376, 960, GetColor(0, 0, 0), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			DrawGraph(966, 558,item_1_img,true);

			DrawGraph(47, 719, txt16, true);
			break;
		case 17:
			DrawGraph(47, 719, txt17, true);
			break;
	}

	if (Moveflag3 == 1 && stelsflag == 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 185);
		DrawBox(0, 0, 1376, 960, GetColor(0, 0, 0), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBright(0x00, 0xFF, 0xFF);
		DrawCircleGauge(966 + 186, 558 + 186, CMP, MPgh, 25.0);
		SetDrawBright(255, 255, 255);
	}


	DrawFormatString(40, 80, GetColor(255, 255, 255), "txtflag:%d", txtflag);

	if (txtflag != 0) {
		if (Apushflag == 0) {
			DrawRotaGraph3(880, 874, 32, 32, 0.5, 0.5, 0.0, A, true, false);
			DrawGraph(650, 64, option, true);
		}
		else {
			SetDrawBright(100, 100, 100);
			DrawRotaGraph3(880, 874, 32, 32, 0.5, 0.5, 0.0, A, true, false);
			DrawGraph(650, 64, option, true);
			SetDrawBright(255, 255, 255);
		}
	}

	//アイテム取得数
	if (itemflag == 0)
	{
		Alpha = 36;
	}
	if (itemflag == 1)
	{
		Alpha = 72;
	}
	if (itemflag >= 6)
	{
		Alpha = 255;
	}
	if (Apushflag == 0) {
		DrawGraph(650, 64, option, true);
	}
	else {
		SetDrawBright(100, 100, 100);
		DrawGraph(650, 64, option, true);
		SetDrawBright(255, 255, 255);
	}
}
#pragma endregion

int Player::GetR()
{
	return R;
}

