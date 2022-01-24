#include "DxLib.h"
#include"player.h"
#include"enemy.h"
#include"bullet.h"
#include"subboss.h"
#include"Score.h"
#include"item.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "自滅ゲー";

// ウィンドウ横幅
const int WIN_WIDTH = 1376;

// ウィンドウ縦幅
const int WIN_HEIGHT = 960;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {

	SetOutApplicationLogValidFlag(FALSE);

	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int Layout = LoadGraph("resouce/Layout.png");

	int player_img[4];
	LoadDivGraph("resouce/player_kari.png", 4, 4, 1, 388, 406, player_img);
	int maba = 0;
	int maba2 = 0;
	// ゲームループで使う変数の宣言
	int ENEMY_MAX = 0;
	int sceneflag = 0;
	int pushflagA = 0;
	int stageflag = 0;
	int resultflag = 0;
	int Pauseflag = 0;
	int Pause = 0;
	int pushflagoption = 0;
	int pushUP = 0;
	int pushDOWN = 0;


	bool reflection_flag = true;

	Player* player = nullptr;
	Enemy* enemy[64] = { nullptr };
	SubBoss* sub_boss = nullptr;
	Score* score = new Score;
	Item* item = new Item;

	int wave_num = 6;
	bool wave_up_flag = false;
	bool game_set = false;
	bool break_flag = false;
	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		//配列なのでoldkey = keys;のようにできない、要素を一つずつコピー

		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		switch (sceneflag) {//シーン管理
		case 0:
			//タイトル
			if (keys[KEY_INPUT_SPACE] == 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0) {
				pushflagA = 0;
			}
			if (pushflagA == 0) {
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
					pushflagA = 1;
					sceneflag = 1;
				}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflagA = 1;
					sceneflag = 1;
				}
			}

			break;

		case 1:
			//ステージ選択
			if (keys[KEY_INPUT_SPACE] == 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0) {
				pushflagA = 0;
			}
			if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT) != 0 || keys[KEY_INPUT_A] == 1) {
				stageflag = 0;
			}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT) != 0 || keys[KEY_INPUT_D] == 1) {
				stageflag = 1;
			}
			if (stageflag == 0) {
				if (pushflagA == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 10;
						player = new Player();
						enemy[0] = new Enemy;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 10;
						player = new Player();
						enemy[0] = new Enemy;
					}
				}
			}
			else {
				if (pushflagA == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 3;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 3;
					}
				}
			}
			break;

		case 2:
			//プレイ画面
			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) == 0 && keys[KEY_INPUT_H] == 0 && oldkeys[KEY_INPUT_H] == 0) {
				pushflagoption = 0;
			}

			if (Pauseflag == 0) {
#pragma region
				score->TC(sceneflag);
				score->IC();
				player->PlayerPadMove(keys, oldkeys);
				//デバッグ用(本番消す)
				if (keys[KEY_INPUT_R] == 1 && oldkeys[KEY_INPUT_R] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6) != 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) != 0) {
					delete player;
					player = new Player();
					wave_num = 16;
					game_set = false;
				}
				if (pushflagoption == 0) {
					if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) != 0 || keys[KEY_INPUT_H] == 1 && oldkeys[KEY_INPUT_H] == 0) {
						pushflagoption = 1;
						Pauseflag = 1;
					}
				}


#pragma region 敵データ読み込み
				if (game_set == false)
				{
					if (wave_up_flag == true)
					{
						wave_num++;
						wave_up_flag = false;
					}

					//敵の数
					ENEMY_MAX = GetEnemyMax(wave_num);


					for (int i = 0; i < ENEMY_MAX; i++)
					{
						enemy[i] = new Enemy;
					}

					for (int i = 0; i < ENEMY_MAX; i++)
					{
						enemy[i]->SetReflectionNum();
					}


					switch (wave_num)
					{
					case 1:
						
						EnemyForm("WAVE_ENEMY_DATA/wave1.csv", ENEMY_MAX, enemy);
						delete player;
						player = new Player();
						game_set = true;


						break;
					case 2:
						EnemyForm("WAVE_ENEMY_DATA/wave2.csv", ENEMY_MAX, enemy);
						game_set = true;
						break;
					case 3:
						EnemyForm("WAVE_ENEMY_DATA/wave3.csv", ENEMY_MAX, enemy);
						game_set = true;
						break;
					case 4:
						EnemyForm("WAVE_ENEMY_DATA/wave4.csv", ENEMY_MAX, enemy);
						game_set = true;
						break;
					case 5:
						EnemyForm("WAVE_ENEMY_DATA/wave5.csv", ENEMY_MAX, enemy);
						game_set = true;
						break;
					case 6:
						EnemyForm("WAVE_ENEMY_DATA/wave6.csv", ENEMY_MAX, enemy);
						game_set = true;
						break;
					case 7:
						EnemyForm("WAVE_ENEMY_DATA/wave7.csv", ENEMY_MAX, enemy);
						game_set = true;
						break;
					case 8:
						EnemyForm("WAVE_ENEMY_DATA/wave8.csv", ENEMY_MAX, enemy);
						game_set = true;
						break;
					case 9:
						EnemyForm("WAVE_ENEMY_DATA/wave9.csv", ENEMY_MAX, enemy);
						game_set = true;
						break;
					case 10:
						EnemyForm("WAVE_ENEMY_DATA/wave10.csv", ENEMY_MAX, enemy);
						sub_boss = new SubBoss;
						SubBossForm("WAVE_ENEMY_DATA/wave10_subboss.csv", 1, *sub_boss);
						game_set = true;
						break;
					case 11:
						EnemyForm("WAVE_ENEMY_DATA/wave11.csv", ENEMY_MAX, enemy);
						game_set = true;
						break;
					case 12:
						EnemyForm("WAVE_ENEMY_DATA/wave12.csv", ENEMY_MAX, enemy);
						game_set = true;
						break;
					case 13:
						EnemyForm("WAVE_ENEMY_DATA/wave13.csv", ENEMY_MAX, enemy);
						game_set = true;
						break;
					case 14:
						EnemyForm("WAVE_ENEMY_DATA/wave14.csv", ENEMY_MAX, enemy);
						game_set = true;
						break;
					case 15:
						EnemyForm("WAVE_ENEMY_DATA/wave15.csv", ENEMY_MAX, enemy);
						game_set = true;
						break;
					case 16:
						EnemyForm("WAVE_ENEMY_DATA/wave16.csv", ENEMY_MAX, enemy);
						game_set = true;
						break;
					case 17:
						EnemyForm("WAVE_ENEMY_DATA/wave17.csv", ENEMY_MAX, enemy);
						game_set = true;
						break;
					case 18:
						EnemyForm("WAVE_ENEMY_DATA/wave18.csv", ENEMY_MAX, enemy);
						game_set = true;
						break;
					case 19:
						EnemyForm("WAVE_ENEMY_DATA/wave19.csv", ENEMY_MAX, enemy);
						game_set = true;
						break;
					case 20:
						sub_boss = new SubBoss;
						EnemyForm("WAVE_ENEMY_DATA/wave20.csv", ENEMY_MAX, enemy);
						SubBossForm("WAVE_ENEMY_DATA/wave20_subboss.csv", 1, *sub_boss);
						game_set = true;
						break;
					}
					//敵が死ぬ毎に
					//Score+=100;

				}
#pragma endregion


#pragma region 体力減少

				for (int i = 0; i < ENEMY_MAX; i++)
				{
					for (int j = 0; j < enemy[i]->GetBulletMax(); j++)
					{
						//時機と敵の弾の当たり判定
						player->HP(*enemy[i]->GetBulletTransform(j), *enemy[i]->GetEnmyBullet(j));

						if (enemy[i]->GetEnemyFlag() == true)
						{
							//時機とボマーの当たり判定
							enemy[i]->PlaterToEnemyHitBox(*player);
						}

					}
				}

				for (int i = 0; i < ENEMY_MAX; i++)
				{
					if (enemy[i]->GetEnemyFlag() == true)
					{
						for (int k = 0; k < ENEMY_MAX; k++)
						{
							if (i != k)
							{
								//敵とボマーの当たり判定
								enemy[i]->ExplosionBommer(*enemy[k]);

								for (int j = 0; j < enemy[k]->GetBulletMax(); j++)
								{
									//敵と敵の弾の当たり判定
									enemy[i]->HP(*enemy[k]->GetBulletTransform(j), *enemy[k]->GetEnmyBullet(j), item);
								}
							}
						}
					}
				}

				if (wave_num == 10 || wave_num == 20)
				{
					for (int i = 0; i < ENEMY_MAX; i++)
					{
						if (sub_boss->GetSubBossFlag() == true)
						{
							for (int j = 0; j < enemy[i]->GetBulletMax(); j++)
							{
								//中ボスと敵の弾の当たり判定
								sub_boss->HP(*enemy[i]->GetBulletTransform(j), *enemy[i]->GetEnmyBullet(j));
							}
						}
					}

					for (int i = 0; i < sub_boss->GetBulletMax(); i++)
					{
						//時機と中ボスの弾の当たり判定
						player->HP(*sub_boss->GetBulletTransform(i), *sub_boss->GetEnmyBullet(i));

						for (int j = 0; j < ENEMY_MAX; j++)
						{
							if (enemy[j]->GetEnemyFlag() == true)
							{
								//敵と中ボスの弾の当たり判定
								enemy[j]->HP(*sub_boss->GetBulletTransform(i), *sub_boss->GetEnmyBullet(i), item);
							}
						}
					}

					//地雷と時機の当たり判定
					sub_boss->PlayerMineHit(*player);
				}

				for (int i = 0; i < ENEMY_MAX; i++)
				{
					//敵の動き
					enemy[i]->Move(*player, reflection_flag, *score, item);
				}

				if (wave_num == 10 || wave_num == 20)
				{
					//中ボスの動き
					sub_boss->Move(*player, reflection_flag);
				}

#pragma endregion
				//waveクリア判定
				if (wave_num != 10 && wave_num != 20)
				{
					for (int i = 0; i < ENEMY_MAX; i++)
					{
						//敵が全員倒されたら弾の反射をなくす
						if (enemy[i]->GetEnemyFlag() == false && enemy[i]->GetAppearTime() == -1)
						{
							if (i == ENEMY_MAX - 1)
							{
								reflection_flag = false;
							}
						}
						else
						{
							break;
						}
					}
				}
				else
				{
					for (int i = 0; i < ENEMY_MAX; i++)
					{
						//敵が全員倒されたら弾の反射をなくす
						if (enemy[i]->GetEnemyFlag() == false && enemy[i]->GetAppearTime() == -1 &&
							sub_boss->GetSubBossFlag() == false && sub_boss->GetAppearTime() == -1)
						{
							if (i == ENEMY_MAX - 1)
							{
								sub_boss->SetMineExplosion();
								reflection_flag = false;
							}
						}
						else
						{
							break;
						}
					}
				}

				for (int i = 0; i < ENEMY_MAX; i++)
				{
					
					if (enemy[i]->GetEnemyFlag() == true || enemy[i]->GetAppearTime() != -1)
					{
						i--;
						break_flag = true;
						break;
					}

					for (int j = 0; j < enemy[i]->GetBulletMax(); j++)
					{
						if (enemy[i]->GetBulletFlag(j) == true)
						{
							break_flag = true;
							break;
						}
					}
				}

				if (wave_num == 10 || wave_num == 20)
				{
					if (sub_boss->GetSubBossFlag() == true || sub_boss->GetAppearTime() != -1)
					{
						break_flag = true;
					}

					if (break_flag == false)
					{
						for (int i = 0; i < 12; i++)
						{
							if (sub_boss->GetEnmyBulletFlag(i) == true)
							{
								break_flag = true;
								break;
							}
						}
					}
				}

				if (break_flag == false)
				{
					game_set = false;
					reflection_flag = true;
					wave_up_flag = true;

					for (int i = 0; i < ENEMY_MAX; i++)
					{
						delete enemy[i];
					}

					if (wave_num == 10 || wave_num == 20)
					{
						delete sub_boss;
					}

					break;
				}
				else
				{
					break_flag = false;
				}

				if (wave_num > 32) {
					score->CC();
					sceneflag = 5;
				}
				sceneflag = player->Result();
				item->Move(*player, *score);
			}
			else {
#pragma region ポーズ画面処理
				if (pushflagoption == 0) {
					if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) != 0 || keys[KEY_INPUT_H] == 1 && oldkeys[KEY_INPUT_H] == 0) {
						pushflagoption = 1;
						Pauseflag = 0;
					}
				}

				if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) == 0 && keys[KEY_INPUT_W] == 0) {
					pushUP = 0;
				}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) == 0 && keys[KEY_INPUT_S] == 0) {
					pushDOWN = 0;
				}
				if (pushUP == 0) {
					if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) != 0 || keys[KEY_INPUT_W] == 1) {
						Pause = Pause - 1;
						pushUP = 1;
					}
				}if (pushDOWN == 0) {
					if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) != 0 || keys[KEY_INPUT_S] == 1) {
						Pause = Pause + 1;
						pushDOWN = 1;
					}
				}

				if (Pause <= 0) {
					Pause = 0;
				}
				if (Pause >= 2) {
					Pause = 2;
				}
				if (Pause == 0) {//戻る
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						Pauseflag = 0;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						Pauseflag = 0;
					}
				}if (Pause == 1) {//初めからやり直す
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 2;
						delete player;
						player = new Player();
						delete score;
						score = new Score();
						wave_num = 1;
						game_set = false;
						Pauseflag = 0;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 2;
						delete player;
						player = new Player();
						delete score;
						score = new Score();
						wave_num = 1;
						game_set = false;
						Pauseflag = 0;
					}
				}if (Pause == 2) {//タイトルに戻る
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 0;
						delete player;

						delete score;
						Pauseflag = 0;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 0;
						delete player;

						delete score;
						Pauseflag = 0;
					}
				}
#pragma endregion
			}

			break;

		case 3:
			//プレイ画面
			score->TC(sceneflag);
			score->IC();
			break;

		case 4:
			if (keys[KEY_INPUT_SPACE] == 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0) {
				pushflagA = 0;
			}
			if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) != 0 || keys[KEY_INPUT_W] == 1) {
				resultflag = 0;
			}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) != 0 || keys[KEY_INPUT_S] == 1) {
				resultflag = 1;
			}
			if (resultflag == 0) {//ステージ選択画面に戻る
				if (pushflagA == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 1;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 1;
					}
				}
			}
			else {//タイトルへ戻る
				if (pushflagA == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 0;
						resultflag = 0;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 0;
						resultflag = 0;
					}
				}
			}
			break;

		case 5:
			//リザルト画面(ゲームクリア)
			score->TC(sceneflag);
			score->RC();
			if (keys[KEY_INPUT_SPACE] == 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0) {
				pushflagA = 0;
			}
			if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) != 0 || keys[KEY_INPUT_W] == 1) {
				resultflag = 0;
			}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) != 0 || keys[KEY_INPUT_S] == 1) {
				resultflag = 1;
			}
			if (resultflag == 0) {//ステージ選択画面に戻る
				if (pushflagA == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 1;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 1;
					}
				}
			}
			else {//タイトルへ戻る
				if (pushflagA == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						sceneflag = 0;
						resultflag = 0;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 0;
						resultflag = 0;
					}
				}
			}
			break;

		case 10:
			//チュートリアル
			player->TutorialMove(keys, oldkeys, enemy, sceneflag, wave_num, pushflagoption);
			score->IC();
			break;
		}
		// 描画処理
		switch (sceneflag) {//シーン管理
		case 0:
			//タイトル
			break;

		case 1:
			//ステージ選択
			if (stageflag == 0) {
				DrawBox(64, 64, 460, 896, GetColor(255, 255, 255), false);
			}if (stageflag == 1) {
				DrawBox(500, 64, 896, 896, GetColor(255, 255, 255), false);
			}

			break;

		case 2:
			maba++;

			maba2 = maba / 10;

			if (maba2 == 4)
			{
				maba = 0;
				maba2 = 0;
			}

			if (game_set == true)
			{
				//プレイ画面
				for (int i = 0; i < ENEMY_MAX; i++)
				{
					enemy[i]->Draw(60 * i);
				}
			}

			if (wave_num == 10 && wave_up_flag == false || wave_num == 20 && wave_up_flag == false)
			{
				sub_boss->Draw();
			}

			player->D();
			DrawGraph(0, 0, Layout, true);
			DrawGraph(958, 128, player_img[maba2], true);
			item->Draw();
			player->Draw();
			score->Draw();

			if (Pauseflag == 1) {
				DrawBox(220, 120, 740, 860, GetColor(255, 255, 255), false);
				if (Pause == 0) {
					DrawBox(280, 180, 680, 340, GetColor(255, 255, 255), false);
					DrawFormatString(400, 300, GetColor(255, 255, 255), "戻る");
				}if (Pause == 1) {
					DrawBox(280, 360, 680, 520, GetColor(255, 255, 255), false);
					DrawFormatString(400, 480, GetColor(255, 255, 255), "再挑戦");
				}if (Pause == 2) {
					DrawBox(280, 640, 680, 800, GetColor(255, 255, 255), false);
					DrawFormatString(400, 660, GetColor(255, 255, 255), "タイトル");
				}
			}

			break;
			delete player;
		case 3:
			//プレイ画面
			score->Draw();
			break;

		case 4:
			//リザルト画面(ゲームオーバー)
			if (resultflag == 0) {
				DrawBox(50, 760, 910, 810, GetColor(255, 255, 255), false);
			}
			else {
				DrawBox(50, 860, 910, 910, GetColor(255, 255, 255), false);
			}

			break;

		case 5:
			//リザルト画面(ゲームクリア)
			if (resultflag == 0) {
				DrawBox(50, 760, 910, 810, GetColor(255, 255, 255), false);
			}
			else {
				DrawBox(50, 860, 910, 910, GetColor(255, 255, 255), false);
			}
			break;

		case 10:
			//チュートリアル

			maba++;

			maba2 = maba / 10;

			if (maba2 == 4)
			{
				maba = 0;
				maba2 = 0;
			}

			player->D();//itemback
			enemy[0]->Draw(0);
			DrawGraph(0, 0, Layout, true);
			DrawGraph(958, 128, player_img[maba2], true);
			score->Draw();
			player->TutorialDraw();


			break;
			delete player;
		}

		//DrawFormatString(480, 480, GetColor(255, 255, 255), "pushflagoption:%d", pushflagoption);

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
