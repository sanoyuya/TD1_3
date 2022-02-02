#include "DxLib.h"
#include"player.h"
#include"enemy.h"
#include"bullet.h"
#include"subboss.h"
#include"Score.h"
#include"item.h"
#include"math.h"
#include"boss.h"
#include"Title.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "Hide og Sigra";

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
	int PSgh = LoadGraph("resouce/pauseselect.png");
	int PSgh128 = LoadGraph("resouce/pauseselect128.png");
	int PSghConfigu = LoadGraph("resouce/pauseselectreturn.png");
	int PSghrestart = LoadGraph("resouce/pauseselectrestart.png");
	int PSghtitle = LoadGraph("resouce/pauseselecttitle.png");
	int CVongh = LoadGraph("resouce/vibon.png");
	int CVoffgh = LoadGraph("resouce/viboff.png");
	int CSon = LoadGraph("resouce/screenon.png");
	int CSoff = LoadGraph("resouce/screenoff.png");
	int Coffoff = LoadGraph("resouce/offoff.png");
	int Coffon = LoadGraph("resouce/offon.png");
	int Conoff = LoadGraph("resouce/onoff.png");
	int Conon = LoadGraph("resouce/onon.png");
	int damageefect = LoadGraph("resouce/DamageEfect.png");
	int A = LoadGraph("resouce/A.png");
	int B = LoadGraph("resouce/B.png");
	int Option = LoadGraph("resouce/option.png");
	int playback = LoadGraph("resouce/GameBackGraund.png");


	//BGM
	int TITLE_BGM = LoadSoundMem("music/title.mp3");
	int STAGE_BGM = LoadSoundMem("music/1~10.mp3");
	int BOSS_BGM = LoadSoundMem("music/BOSS.mp3");
	int TUTORIAL_BGM = LoadSoundMem("music/チュートリアル.mp3");
	int RESULT_BGM = LoadSoundMem("music/result.mp3");

	float volume = 250.0f;

	//SE
	int SELECT_SE = LoadSoundMem("music/選択不可.mp3");

	int player_img[12];
	LoadDivGraph("resouce/EL_stand.png", 12, 12, 1, 380, 402, player_img);
	int playerdamagegh = LoadGraph("resouce/EL_damage.png");
	int wavegh[10] = { 0 };
	LoadDivGraph("resouce/wavenum.png", 10, 10, 1, 34, 37, wavegh);
	int waveback = LoadGraph("resouce/wave.png");
	int wavesand[10] = { 0 };
	LoadDivGraph("resouce/sandstorm.png", 10, 10, 1, 162, 43, wavesand);
	int sandcooltime = 0;
	int sand = 0;
	int maba = 0;
	int maba2 = 0;
	// ゲームループで使う変数の宣言
	int ENEMY_MAX = 0;
	int sceneflag = 0;
	int pushflagA = 0;
	int pushflagB = 0;
	int stageflag = 0;
	int resultflag = 0;
	int Pauseflag = 0;
	int Pause = 0;
	int pushflagoption = 0;
	int pushUP = 0;
	int pushDOWN = 0;
	int vibflag = 1;
	int screenshakeflag = 1;
	int Configuflag = 0;
	int Configu = 0;
	int randX = 0;
	int randY = 0;
	int shaketime = 0;
	int shakeflag = 0;
	int damageflag = 0;
	int damagetime = 0;
	int damageAlpha = 0;
	int recoveryflag = 0;
	int recoverytime = 0;
	int recoveryAlpha = 0;
	int backX = 0;
	int backY = 0;
	int backcooltime = 0;
	double x = 0;
	double y = 0;
	double ang = 0;
	int flame = 0;
	int ABtime = 0;
	int ABflag = 0;

	bool reflection_flag = true;

	Player* player = nullptr;
	Enemy* enemy[40] = { nullptr };
	SubBoss* sub_boss = nullptr;
	Score* score = nullptr;
	Item* item = nullptr;
	Boss* boss = nullptr;
	Title* title = new Title;

	int wave_num = 0;
	int windex = 0;
	int wdeiv = 1;
	int wdiv = 0;
	bool wave_up_flag = false;
	bool game_set = false;
	bool break_flag = false;
	int guide = LoadGraph("resouce/formation_circle.png");
	bool movie_flag = false;
	bool boss_battle_flag = false;
	bool stage_sound_flag = false;
	bool boss_sound_flag = false;

	int game_end = 0;

	int txt_rand_y = 0;
	bool txt_shake_flag = false;
	int txt_shake_time = 25;
	int txt_rand_x = 0;
	bool title_sound_flag = false;
	int titletimer = 0;
	bool tutorial_sound_flag = false;

	bool result_bgm_flag = false;

	int A_img = LoadGraph("resouce/A.png");
	int A_time = 0;

	int RL1_txt = LoadGraph("resouce/text_RL1.png");
	int RL2_txt = LoadGraph("resouce/text_RL2.png");
	int boss2_txt = LoadGraph("resouce/text_boss2.png");
	int boss1_txt = LoadGraph("resouce/text_boss1.png");
	int boss_txt = LoadGraph("resouce/bosstext.png");
	int siturei_txt = LoadGraph("resouce/siturei.png");
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
				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
					pushflagA = 1;
					delete title;
					sceneflag = 1;
					PlaySoundMem(SELECT_SE, DX_PLAYTYPE_BACK);
					//仮--------------------------
					/*sceneflag = 10;
					player = new Player();
					enemy[0] = new Enemy;
					item = new Item;
					score = new Score;*/
					//----------------------------
				}
			}

			break;

		case 1:
			//ステージ選択
			if (keys[KEY_INPUT_SPACE] == 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0) {
				pushflagA = 0;
			}
			if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) != 0 || keys[KEY_INPUT_W] == 1) {
				stageflag = 0;
			}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) != 0 || keys[KEY_INPUT_S] == 1) {
				stageflag = 1;
			}
			if (stageflag == 0) {
				if (pushflagA == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						PlaySoundMem(SELECT_SE, DX_PLAYTYPE_BACK);
						sceneflag = 10;
						player = new Player();
						enemy[0] = new Enemy;
						item = new Item;
						score = new Score;

					}
				}
			}
			else {
				if (pushflagA == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
						PlaySoundMem(SELECT_SE, DX_PLAYTYPE_BACK);
						sceneflag = 3;
					}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						PlaySoundMem(SELECT_SE, DX_PLAYTYPE_BACK);
						sceneflag = 3;
					}
				}
			}
			break;

		case 2:
			//プレイ画面
			if (maba2 >= 11)
			{
				maba = 0;
				maba2 = 0;
			}

			if (flame == 0) {
				x = 15;
				y = 10;
			}

			backX = x + 20 * (cos(ang) * 2);
			backY = y + 10 * (sin(2 * ang) * 2);

			backcooltime++;

			flame++;
			ang += 0.01;

			if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) == 0 && keys[KEY_INPUT_H] == 0 && oldkeys[KEY_INPUT_H] == 0) {
				pushflagoption = 0;
			}

			if (Pauseflag == 0) {
				if (Configuflag == 0) {
					score->TC(sceneflag);
					player->PlayerPadMove(keys, oldkeys, wave_num);
					//デバッグ用(本番消す)
					if (keys[KEY_INPUT_R] == 1 && oldkeys[KEY_INPUT_R] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6) != 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) != 0) {
						delete player;
						player = new Player();
						wave_num = 29;
						game_set = false;
					}
					if (pushflagoption == 0) {
						if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) != 0 || keys[KEY_INPUT_H] == 1 && oldkeys[KEY_INPUT_H] == 0) {
							pushflagoption = 1;
							Pauseflag = 1;
						}
					}


					if (boss_battle_flag == false)
					{
#pragma region 敵データ読み込み
						if (game_set == false)
						{
							//wave_num = 28;
							if (wave_up_flag == true)
							{
								wave_num++;
								player->HPplus(wave_num, recoveryflag = 0, recoverytime = 0);
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

								EnemyForm("WAVE_ENEMY_DATA/wave1.csv", ENEMY_MAX, enemy, wave_num);
								delete player;
								player = new Player();
								player->DeleteItem();
								game_set = true;
								break;
							case 2:
								EnemyForm("WAVE_ENEMY_DATA/wave2.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								break;
							case 3:
								EnemyForm("WAVE_ENEMY_DATA/wave3.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								break;
							case 4:
								EnemyForm("WAVE_ENEMY_DATA/wave4.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								break;
							case 5:
								EnemyForm("WAVE_ENEMY_DATA/wave5.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								break;
							case 6:
								EnemyForm("WAVE_ENEMY_DATA/wave6.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								break;
							case 7:
								EnemyForm("WAVE_ENEMY_DATA/wave7.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								break;
							case 8:
								EnemyForm("WAVE_ENEMY_DATA/wave8.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								break;
							case 9:
								EnemyForm("WAVE_ENEMY_DATA/wave9.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								break;
							case 10:
								EnemyForm("WAVE_ENEMY_DATA/wave10.csv", ENEMY_MAX, enemy, wave_num);
								sub_boss = new SubBoss;
								SubBossForm("WAVE_ENEMY_DATA/wave10_subboss.csv", 1, *sub_boss);
								game_set = true;
								break;
							case 11:
								EnemyForm("WAVE_ENEMY_DATA/wave11.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								break;
							case 12:
								EnemyForm("WAVE_ENEMY_DATA/wave12.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								break;
							case 13:
								EnemyForm("WAVE_ENEMY_DATA/wave13.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								break;
							case 14:
								EnemyForm("WAVE_ENEMY_DATA/wave14.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								break;
							case 15:
								EnemyForm("WAVE_ENEMY_DATA/wave15.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								break;
							case 16:
								EnemyForm("WAVE_ENEMY_DATA/wave16.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								break;
							case 17:
								EnemyForm("WAVE_ENEMY_DATA/wave17.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								break;
							case 18:
								EnemyForm("WAVE_ENEMY_DATA/wave18.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								break;
							case 19:
								EnemyForm("WAVE_ENEMY_DATA/wave19.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								break;
							case 20:
								sub_boss = new SubBoss;
								EnemyForm("WAVE_ENEMY_DATA/wave20.csv", ENEMY_MAX, enemy, wave_num);
								SubBossForm("WAVE_ENEMY_DATA/wave20_subboss.csv", 1, *sub_boss);
								game_set = true;
								break;
							case 21:
								EnemyForm("WAVE_ENEMY_DATA/wave21.csv", ENEMY_MAX, enemy, wave_num);
								player->SetEasingFlag(1);
								game_set = true;
								break;
							case 22:
								EnemyForm("WAVE_ENEMY_DATA/wave22.csv", ENEMY_MAX, enemy, wave_num);
								player->SetEasingFlag(1);
								game_set = true;
								break;
							case 23:
								EnemyForm("WAVE_ENEMY_DATA/wave23.csv", ENEMY_MAX, enemy, wave_num);
								player->SetEasingFlag(1);
								game_set = true;
								break;
							case 24:
								EnemyForm("WAVE_ENEMY_DATA/wave24.csv", ENEMY_MAX, enemy, wave_num);
								player->SetEasingFlag(1);
								game_set = true;
								break;
							case 25:
								EnemyForm("WAVE_ENEMY_DATA/wave25.csv", ENEMY_MAX, enemy, wave_num);
								player->SetEasingFlag(1);
								game_set = true;
								break;
							case 26:
								EnemyForm("WAVE_ENEMY_DATA/wave26.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								movie_flag = true;
								player->SetEasingFlag(1);
								player->SetMoveFlag(0);
								break;
							case 27:
								movie_flag = false;
								EnemyForm("WAVE_ENEMY_DATA/wave27.csv", ENEMY_MAX, enemy, wave_num);
								player->SetEasingFlag(1);
								player->SetMoveFlag(0);
								game_set = true;
								break;
							case 28:
								EnemyForm("WAVE_ENEMY_DATA/wave28.csv", ENEMY_MAX, enemy, wave_num);
								player->SetEasingFlag(1);
								player->SetMoveFlag(0);
								game_set = true;
								break;
							case 29:
								EnemyForm("WAVE_ENEMY_DATA/wave29.csv", ENEMY_MAX, enemy, wave_num);
								game_set = true;
								movie_flag = true;
								player->SetEasingFlag(1);
								player->SetMoveFlag(0);
								break;
							case 30:
								movie_flag = false;
								boss_battle_flag = true;
								boss = new Boss;
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
								player->HP(*enemy[i]->GetBulletTransform(j), *enemy[i]->GetEnmyBullet(j), vibflag, screenshakeflag, shakeflag, damageflag, shaketime, damagetime, damageAlpha);

								if (enemy[i]->GetEnemyFlag(wave_num) == true)
								{
									//時機とボマーの当たり判定
									enemy[i]->PlaterToEnemyHitBox(*player, i, vibflag, screenshakeflag, shakeflag, damageflag, shaketime, damagetime);
								}

							}
						}

						for (int i = 0; i < ENEMY_MAX; i++)
						{
							if (enemy[i]->GetEnemyFlag(wave_num) == true)
							{
								for (int k = 0; k < ENEMY_MAX; k++)
								{
									if (i != k)
									{
										if (enemy[k]->GetEnemyType() != 6)
										{
											//敵とボマーの当たり判定
											enemy[i]->ExplosionBommer(enemy[k]);

											for (int j = 0; j < enemy[k]->GetBulletMax(); j++)
											{
												//敵と敵の弾の当たり判定
												enemy[i]->HP(*enemy[k]->GetBulletTransform(j), *enemy[k]->GetEnmyBullet(j), item, score);
											}
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
								player->HP(*sub_boss->GetBulletTransform(i), *sub_boss->GetEnmyBullet(i), vibflag, screenshakeflag, shakeflag, damageflag, shaketime, damagetime, damageAlpha);

								for (int j = 0; j < ENEMY_MAX; j++)
								{
									if (enemy[j]->GetEnemyFlag(wave_num) == true)
									{
										//敵と中ボスの弾の当たり判定
										enemy[j]->HP(*sub_boss->GetBulletTransform(i), *sub_boss->GetEnmyBullet(i), item, score);
									}
								}
							}

							//地雷と時機の当たり判定
							sub_boss->PlayerMineHit(*player, vibflag, screenshakeflag, shakeflag, damageflag, shaketime, damagetime);
						}

						for (int i = 0; i < ENEMY_MAX; i++)
						{
							//敵の動き
							enemy[i]->Move(*player, reflection_flag, *score, item, wave_num, movie_flag, keys, i, vibflag, screenshakeflag, shakeflag, damageflag, shaketime, damagetime, txt_shake_flag);

						}

						if (wave_num == 10 || wave_num == 20)
						{
							//中ボスの動き
							sub_boss->Move(*player, reflection_flag, vibflag, screenshakeflag, shakeflag, damageflag, shaketime, damagetime);
						}

						item->Move(*player, *score);

						score->SetHp(player->GetHp());
#pragma endregion

#pragma region wave クリア判定
						//waveクリア判定
						if (wave_num != 10 && wave_num != 20)
						{
							for (int i = 0; i < ENEMY_MAX; i++)
							{
								//敵が全員倒されたら弾の反射をなくす
								if (enemy[i]->GetEnemyFlag(wave_num) == false && enemy[i]->GetAppearTime() == -1)
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
								if (enemy[i]->GetEnemyFlag(wave_num) == false && enemy[i]->GetAppearTime() == -1 &&
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

							if (enemy[i]->GetEnemyFlag(wave_num) == true ||
								enemy[i]->GetAppearTime() != -1 ||
								enemy[i]->GetExplosionFlag() == true)
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

						if (item->ItemExists() == false)
						{
							break_flag = true;
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

						if (break_flag == false && reflection_flag == false)
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
#pragma endregion
					}
					else
					{
						boss->Move(enemy, player, item, score,
							recoveryflag, recoverytime, vibflag, screenshakeflag,
							shakeflag, damageflag, shaketime, damagetime,
							reflection_flag, movie_flag, keys, game_end, txt_shake_flag, damageAlpha);
					}

					item->Move(*player, *score);

					if (game_end == 1) {
						score->Clear(sceneflag);
					}
					score->Death(sceneflag);

					if (shakeflag == 1) {//シェイク
						shaketime++;
						if (shaketime < 4) {
							randX = rand() % 21 - 10;
							randY = rand() % 21 - 10;
						}
						if (4 <= shaketime && shaketime < 9) {
							randX = rand() % 11 - 5;
							randY = rand() % 11 - 5;
						}
						if (9 <= shaketime) {
							randX = rand() % 7 - 3;
							randY = rand() % 7 - 3;
						}
						if (shaketime >= 15) {
							shakeflag = 0;
							shaketime = 0;
						}
					}
					else {
						randX = 0;
						randY = 0;
					}
				}

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

				if (Pause == 1) {//初めからやり直す
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						PlaySoundMem(SELECT_SE, DX_PLAYTYPE_BACK);

						sceneflag = 2;
						delete player;
						player = new Player();
						delete score;
						score = new Score();
						wave_num = 1;
						game_set = false;
						Pauseflag = 0;
						for (int i = 0; i < ENEMY_MAX; i++)
						{
							delete enemy[i];
						}
						delete item;
						item = new Item;
						if (boss != nullptr)
						{
							delete boss;
						}
						movie_flag = false;
						boss_battle_flag = false;
						stage_sound_flag = false;
						boss_sound_flag = false;
						StopSoundMem(STAGE_BGM);
						StopSoundMem(BOSS_BGM);
						title_sound_flag = false;
						tutorial_sound_flag = false;
						result_bgm_flag = false;


					}
				}
				if (Pause == 2) {//タイトルに戻る
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						PlaySoundMem(SELECT_SE, DX_PLAYTYPE_BACK);
						delete player;
						for (int i = 0; i < ENEMY_MAX; i++)
						{
							delete enemy[i];
						}
						delete score;
						Pauseflag = 0;
						game_set = false;
						wave_num = 1;
						delete item;
						sceneflag = 0;
						if (boss != nullptr)
						{
							delete boss;
						}
						movie_flag = false;
						boss_battle_flag = false;
						stage_sound_flag = false;
						boss_sound_flag = false;
						StopSoundMem(STAGE_BGM);
						StopSoundMem(BOSS_BGM);
						title_sound_flag = false;
						tutorial_sound_flag = false;
						result_bgm_flag = false;

						title = new Title;
					}
				}
#pragma endregion

			}
			if (Configuflag == 1) {
				if (pushflagoption == 0) {
					if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) != 0 || keys[KEY_INPUT_H] == 1 && oldkeys[KEY_INPUT_H] == 0) {
						Configuflag = 0;
						pushflagoption = 1;
					}
				}
				if (pushflagB == 0) {
					if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0) {
						Pauseflag = 1;
						Configuflag = 0;
						pushflagB = 1;
						player->pushB();
					}
				}

				if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) == 0 && keys[KEY_INPUT_W] == 0) {
					pushUP = 0;
				}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) == 0 && keys[KEY_INPUT_S] == 0) {
					pushDOWN = 0;
				}
				if (pushUP == 0) {
					if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) != 0 || keys[KEY_INPUT_W] == 1) {
						Configu = Configu - 1;
						pushUP = 1;
					}
				}if (pushDOWN == 0) {
					if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) != 0 || keys[KEY_INPUT_S] == 1) {
						Configu = Configu + 1;
						pushDOWN = 1;
					}
				}if (Configu <= 0) {
					Configu = 0;
				}
				if (Configu >= 1) {
					Configu = 1;
				}
				if (Configu == 0) {
					if (pushflagA == 0) {
						if (vibflag == 0) {
							if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
								vibflag = 1;
								PlaySoundMem(SELECT_SE, DX_PLAYTYPE_BACK);

							}
						}
						else {
							if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
								vibflag = 0;
								PlaySoundMem(SELECT_SE, DX_PLAYTYPE_BACK);

							}
						}
					}
				}if (Configu == 1) {
					if (pushflagA == 0) {
						if (screenshakeflag == 0) {
							if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
								screenshakeflag = 1;
								PlaySoundMem(SELECT_SE, DX_PLAYTYPE_BACK);

							}
						}
						else {
							if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
								screenshakeflag = 0;
								PlaySoundMem(SELECT_SE, DX_PLAYTYPE_BACK);

							}
						}
					}
				}
			}

			if (Pauseflag == 1) {
				if (pushflagB == 0) {
					if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0) {
						Pauseflag = 0;
						player->pushB();
					}
				}
				if (Pause == 0) {//設定
					if (pushflagA == 0) {
						if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
							PlaySoundMem(SELECT_SE, DX_PLAYTYPE_BACK);
							Configuflag = 1;
							Pauseflag = 0;
						}
					}
				}
			}

			if (game_set == true && enemy[0]->GetTxtFlag() == 3 && wave_num == 30)
			{
				if (wave_num == 30)
				{
					if (txt_shake_flag == true)
					{
						int shake = 25 - txt_shake_time;

						txt_rand_x = GetRand(25 - shake) - 5;

						txt_rand_y = GetRand(25 - shake) - 5;

						txt_shake_time--;

						if (txt_shake_time == 0)
						{
							txt_shake_flag = false;
							txt_shake_time = 30;

							txt_rand_x = 0;
							txt_rand_y = 0;
						}
					}
				}
			}
			//DrawFormatString(480, 480, GetColor(255, 255, 255), "Pause:%d", Pauseflag);

			if (keys[KEY_INPUT_SPACE] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {//Aボタン
				pushflagA = 1;
			}if (keys[KEY_INPUT_RETURN] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0) {//Bボタン
				pushflagB = 1;
			}

			if (keys[KEY_INPUT_SPACE] == 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0) {//Aボタン
				pushflagA = 0;
			}if (keys[KEY_INPUT_RETURN] == 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) == 0) {//Bボタン
				pushflagB = 0;
			}

			break;

		case 3:
			//プレイ画面
			score->TC(sceneflag);
			//score->IC();
			break;

		case 5:
			//リザルト画面(ゲームクリア)
			StopSoundMem(STAGE_BGM);
			StopSoundMem(BOSS_BGM);

			if (keys[KEY_INPUT_SPACE] == 0 && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) == 0) {
				pushflagA = 0;
			}
			if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP) != 0 || keys[KEY_INPUT_W] == 1) {
				resultflag = 0;
			}if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN) != 0 || keys[KEY_INPUT_S] == 1) {
				resultflag = 1;
			}
			if (resultflag == 0) {//初めからやり直す
				if (pushflagA == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						sceneflag = 2;
						delete player;
						player = new Player();
						delete score;
						score = new Score();
						wave_num = 1;
						game_set = false;
						Pauseflag = 0;
						for (int i = 0; i < ENEMY_MAX; i++)
						{
							delete enemy[i];
						}
						delete item;
						item = new Item;
						shaketime = 0;
						damagetime = 0;
						shakeflag = 0;
						damageflag = 0;
						if (boss != nullptr)
						{
							delete boss;
						}
						movie_flag = false;
						boss_battle_flag = false;
						stage_sound_flag = false;
						boss_sound_flag = false;
						title_sound_flag = false;
						tutorial_sound_flag = false;
						result_bgm_flag = false;
						StopSoundMem(STAGE_BGM);
						StopSoundMem(BOSS_BGM);
						StopSoundMem(RESULT_BGM);

					}
				}
			}
			else {//タイトルへ戻る
				if (pushflagA == 0) {
					if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
						delete player;
						for (int i = 0; i < ENEMY_MAX; i++)
						{
							delete enemy[i];
						}
						delete score;
						Pauseflag = 0;
						game_set = false;
						wave_num = 1;
						delete item;
						shaketime = 0;
						damagetime = 0;
						shakeflag = 0;
						damageflag = 0;
						sceneflag = 0;

						if (boss != nullptr)
						{
							delete boss;
						}
						movie_flag = false;
						boss_battle_flag = false;
						stage_sound_flag = false;
						boss_sound_flag = false;
						title_sound_flag = false;
						tutorial_sound_flag = false;
						result_bgm_flag = false;
						title = new Title;
						StopSoundMem(STAGE_BGM);
						StopSoundMem(BOSS_BGM);
						StopSoundMem(RESULT_BGM);

					}
				}
			}
			break;

		case 10:
			//チュートリアル
			if (maba2 >= 11)
			{
				maba = 0;
				maba2 = 0;
			}

			if (flame == 0) {
				x = 15;
				y = 10;
			}

			backX = x + 20 * (cos(ang) * 2);
			backY = y + 10 * (sin(2 * ang) * 2);

			backcooltime++;

			flame++;
			ang += 0.01;
			player->TutorialMove(keys, oldkeys, enemy, sceneflag, wave_num, pushflagoption, vibflag, screenshakeflag, shakeflag, damageflag, damageAlpha);
			break;
		}
		// 描画処理
		switch (sceneflag) {//シーン管理
		case 0:
			//タイトル
			if (title_sound_flag == false)
			{
				PlaySoundMem(TITLE_BGM, DX_PLAYTYPE_LOOP, true);
				title_sound_flag = true;
			}
			titletimer++;

			if (titletimer < 3000)
			{
				title->title();
			}
			else
			{
				StopSoundMem(TITLE_BGM);
				PlaySoundMem(TITLE_BGM, DX_PLAYTYPE_LOOP, true);
				volume = 250.0f;
				ChangeVolumeSoundMem(volume, TITLE_BGM);
				delete title;
				title = new Title;
				titletimer = 0;
			}

			if (titletimer > 2500)
			{
				volume -= 0.20f;
				ChangeVolumeSoundMem(volume, TITLE_BGM);
			}


			break;

		case 1:
			//ステージ選択
			if (stageflag == 0) {
				DrawBox(64, 64, 1312, 696, GetColor(255, 255, 255), false);
			}if (stageflag == 1) {
				DrawBox(64, 760, 1312, 896, GetColor(255, 255, 255), false);
			}

			break;

		case 2:
			if (stage_sound_flag == false) {
				StopSoundMem(TUTORIAL_BGM);
				PlaySoundMem(STAGE_BGM, DX_PLAYTYPE_LOOP, true);
				ChangeVolumeSoundMem(130, STAGE_BGM);
				stage_sound_flag = true;
			}
			if (wave_num >= 30) {
				if (boss_sound_flag == false)
				{
					StopSoundMem(STAGE_BGM);
					PlaySoundMem(BOSS_BGM, DX_PLAYTYPE_LOOP, true);
					boss_sound_flag = true;
				}

			}
			SetDrawBright(150, 150, 150);
			DrawGraph(backX - 30, backY, playback, true);
			SetDrawBright(255, 255, 255);
			maba++;

			maba2 = maba / 10;

			if (game_set == true)
			{
				//プレイ画面
				for (int i = 0; i < ENEMY_MAX; i++)
				{
					if (enemy[i] != nullptr)
					{
						enemy[i]->Draw(i, wave_num);
					}
				}
			}

			if (wave_num == 10 && wave_up_flag == false || wave_num == 20 && wave_up_flag == false)
			{
				sub_boss->Draw();
			}

			if (boss_battle_flag == true)
			{
				boss->Draw(enemy);
			}	if (wave_num == 10 && wave_up_flag == false || wave_num == 20 && wave_up_flag == false)
			{
				sub_boss->Draw();
			}

			if (boss_battle_flag == true)
			{
				boss->Draw(enemy);
			}

			DrawBox(1014, 606, 1376, 960, GetColor(0, 0, 0), true);

			player->D(randX, randY);
			DrawGraph(-32 + randX, -32 + randY, Layout, true);
			if (damageflag == 0) {
				DrawGraph(962 + randX, 130 + randY, player_img[maba2], true);
			}
			else {
				DrawGraph(962 + randX, 130 + randY, playerdamagegh, true);
			}

			DrawGraph(1041 + randX, 141 + randY, waveback, true);
			wdiv = 1;
			for (int i = 0; i < 2; i++)
			{
				windex = wave_num / wdiv % 10;
				DrawGraph((2 - 1 - i) * 35 + 1194 + randX, 141 + randY, wavegh[windex], true);
				wdiv = wdiv * 10;
			}
			sandcooltime++;
			if (sandcooltime >= 6) {
				sandcooltime = 0;
				sand++;
			}
			if (sand > 10) {
				sand = 0;
			}
			//DrawGraph(1071 + randX, 487 + randY, wavesand[sand], true);
			item->Draw();
			player->Draw(randX, randY);
			score->Draw(randX, randY);

			if (game_set == true && enemy[0]->GetTxtFlag() == 1)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 185);
				DrawBox(0, 0, 1376, 960, GetColor(0, 0, 0), true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				if (wave_num == 29)
				{
					DrawGraph(47, 719, RL2_txt, true);
				}
				if (wave_num == 26)
				{
					DrawGraph(47, 719, RL1_txt, true);
				}
				if (wave_num == 30)
				{
					DrawGraph(47, 719, boss1_txt, true);
				}
				if (wave_num == 30)
				{
					boss->Draw(enemy);
				}
				else
				{
					for (int i = 0; i < ENEMY_MAX; i++)
					{
						if (enemy[i] != nullptr)
						{
							enemy[i]->Draw(i, wave_num);
						}

					}
				}
				A_time++;
				int A_falg = A_time % 50;
				if (A_falg > 25) {
					DrawRotaGraph3(880, 874, 32, 32, 0.5, 0.5, 0.0, A_img, true, false);
				}
				else {

					SetDrawBright(100, 100, 100);
					DrawRotaGraph3(880, 874, 32, 32, 0.5, 0.5, 0.0, A_img, true, false);
					SetDrawBright(255, 255, 255);
				}
			}
			if (game_set == true && enemy[0]->GetTxtFlag() == 2 && wave_num == 30)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 185);
				DrawBox(0, 0, 1376, 960, GetColor(0, 0, 0), true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				if (wave_num == 30)
				{
					DrawGraph(47, 719, boss2_txt, true);
				}

				A_time++;
				int A_falg = A_time % 50;
				if (A_falg > 25) {
					DrawRotaGraph3(880, 874, 32, 32, 0.5, 0.5, 0.0, A_img, true, false);
				}
				else {

					SetDrawBright(100, 100, 100);
					DrawRotaGraph3(880, 874, 32, 32, 0.5, 0.5, 0.0, A_img, true, false);
					SetDrawBright(255, 255, 255);
				}
				boss->Draw(enemy);
			}

			if (game_set == true && enemy[0]->GetTxtFlag() == 3 && wave_num == 30)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 185);
				DrawBox(0, 0, 1376, 960, GetColor(0, 0, 0), true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				if (wave_num == 30)
				{
					DrawGraph(47 + txt_rand_x, 719 + txt_rand_y, boss_txt, true);
					DrawGraph(200, 800, siturei_txt, true);
				}

				A_time++;
				int A_falg = A_time % 50;
				if (A_falg > 25) {
					DrawRotaGraph3(880, 874, 32, 32, 0.5, 0.5, 0.0, A_img, true, false);
				}
				else {

					SetDrawBright(100, 100, 100);
					DrawRotaGraph3(880, 874, 32, 32, 0.5, 0.5, 0.0, A_img, true, false);
					SetDrawBright(255, 255, 255);
				}
				boss->Draw(enemy);
			}

			if (recoveryflag == 1) {//回復エフェクト
				recoverytime++;
				if (recoverytime >= 15) {
					recoverytime = 0;
					recoveryflag = 0;
				}
				else {
					recoveryAlpha -= 15;
				}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, recoveryAlpha);//アルファ
				SetDrawBright(0, 150, 0);
				DrawGraph(962 + randX, 130 + randY, damageefect, true);
				SetDrawBright(255, 255, 255);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);//ノーブレンド
			}
			else {
				recoveryAlpha = 255;
			}

			if (Pauseflag == 1 || Configuflag == 1) {
				DrawGraph(220, 120, PSgh, true);
				ABtime++;
				if (ABflag == 0) {
					if (ABtime >= 25) {
						ABtime = 0;
						ABflag = 1;
					}
				}
				else {
					if (ABtime >= 25) {
						ABtime = 0;
						ABflag = 0;
					}
				}

				if (ABflag == 0) {
					DrawGraph(660, 780, A, true);
					DrawGraph(236, 780, B, true);
					DrawGraph(660, 136, Option, true);
				}
				else {
					SetDrawBright(100, 100, 100);
					DrawGraph(660, 780, A, true);
					DrawGraph(236, 780, B, true);
					DrawGraph(660, 136, Option, true);
					SetDrawBright(255, 255, 255);
				}
			}

			if (Pauseflag == 1) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//アルファ
				DrawGraph(220, 120, PSgh128, true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);//ノーブレンド
				if (Pause == 0) {
					DrawGraph(220, 120, PSghConfigu, true);
					DrawBox(280, 180, 680, 341, GetColor(255, 255, 255), false);
					DrawBox(281, 181, 679, 340, GetColor(255, 255, 255), false);
				}if (Pause == 1) {
					DrawGraph(220, 120, PSghrestart, true);
					DrawBox(280, 410, 680, 571, GetColor(255, 255, 255), false);
					DrawBox(281, 411, 679, 570, GetColor(255, 255, 255), false);
				}if (Pause == 2) {
					DrawGraph(220, 120, PSghtitle, true);
					DrawBox(280, 640, 680, 801, GetColor(255, 255, 255), false);
					DrawBox(281, 641, 679, 800, GetColor(255, 255, 255), false);
				}
			}
			if (Configuflag == 1) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);//アルファ
				if (vibflag == 0) {
					if (screenshakeflag == 0) {
						DrawGraph(220, 120, Coffoff, true);
					}
					else {
						DrawGraph(220, 120, Coffon, true);
					}
				}
				else {
					if (screenshakeflag == 0) {
						DrawGraph(220, 120, Conoff, true);
					}
					else {
						DrawGraph(220, 120, Conon, true);
					}
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);//ノーブレンド
				if (Configu == 0) {
					if (vibflag == 0) {
						DrawGraph(220, 120, CVoffgh, true);
					}
					else {
						DrawGraph(220, 120, CVongh, true);
					}
					DrawBox(280, 180, 680, 341, GetColor(255, 255, 255), false);
					DrawBox(281, 181, 679, 340, GetColor(255, 255, 255), false);
				}if (Configu == 1) {
					if (screenshakeflag == 0) {
						DrawGraph(220, 120, CSoff, true);
					}
					else {
						DrawGraph(220, 120, CSon, true);
					}
					DrawBox(280, 410, 680, 651, GetColor(255, 255, 255), false);
					DrawBox(281, 411, 679, 650, GetColor(255, 255, 255), false);
				}
			}

			if (damageflag == 1) {//ダメージエフェクト
				damagetime++;
				if (damagetime >= 15) {
					damagetime = 0;
					damageflag = 0;
				}
				else {
					damageAlpha -= 15;
				}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, damageAlpha);//アルファ
				SetDrawBright(150, 0, 0);
				DrawGraph(962 + randX, 130 + randY, damageefect, true);
				SetDrawBright(255, 255, 255);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);//ノーブレンド
			}
			else {
				damageAlpha = 255;
			}

			break;
			delete player;
		case 3:
			//プレイ画面
			score->Draw(randX, randY);
			break;


		case 5:
			if (result_bgm_flag == false)
			{
				PlaySoundMem(RESULT_BGM, DX_PLAYTYPE_LOOP, true);
				ChangeVolumeSoundMem(130, RESULT_BGM);
				result_bgm_flag = true;
			}
			//リザルト画面(ゲームクリア)
			score->ResultDraw();
			if (resultflag == 0) {
				DrawBox(50, 760, 910, 810, GetColor(255, 255, 255), false);
				DrawFormatString(100, 785, GetColor(255, 255, 255), "初めからやり直す");
			}
			else {
				DrawBox(50, 860, 910, 910, GetColor(255, 255, 255), false);
				DrawFormatString(100, 885, GetColor(255, 255, 255), "タイトルに戻る");
			}
			break;

		case 10:
			//チュートリアル
			StopSoundMem(TITLE_BGM);
			if (tutorial_sound_flag == false)
			{
				PlaySoundMem(TUTORIAL_BGM, DX_PLAYTYPE_LOOP);
				ChangeVolumeSoundMem(130, TUTORIAL_BGM);
				tutorial_sound_flag = true;
			}
			SetDrawBright(150, 150, 150);
			DrawGraph(backX - 30, backY, playback, true);
			SetDrawBright(255, 255, 255);
			maba++;

			maba2 = maba / 10;

			if (maba2 == 11)
			{
				maba = 0;
				maba2 = 0;
			}

			player->D(randX, randY);//itemback
			enemy[0]->Draw(0, wave_num);
			DrawGraph(-32 + randX, -32 + randY, Layout, true);

			score->Draw(randX, randY);
			player->TutorialDraw(randX, randY, keys);

			if (shakeflag == 1) {//シェイク
				shaketime++;
				if (shaketime < 4) {
					randX = rand() % 21 - 10;
					randY = rand() % 21 - 10;
				}
				if (4 <= shaketime && shaketime < 9) {
					randX = rand() % 11 - 5;
					randY = rand() % 11 - 5;
				}
				if (9 <= shaketime) {
					randX = rand() % 7 - 3;
					randY = rand() % 7 - 3;
				}
				if (shaketime >= 15) {
					shakeflag = 0;
					shaketime = 0;
				}
			}
			else {
				randX = 0;
				randY = 0;
			}

			if (damageflag == 1) {
				damagetime++;
				if (damagetime >= 15) {
					damagetime = 0;
					damageflag = 0;
				}
				else {
					damageAlpha -= 15;
				}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, damageAlpha);//アルファ
				SetDrawBright(150, 0, 0);
				DrawGraph(962 + randX, 130 + randY, damageefect, true);
				SetDrawBright(255, 255, 255);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);//ノーブレンド
			}
			else {
				damageAlpha = 255;
			}

			DrawGraph(1041 + randX, 141 + randY, waveback, true);
			wdiv = 1;
			for (int i = 0; i < 2; i++)
			{
				windex = wave_num / wdiv % 10;
				DrawGraph((2 - 1 - i) * 35 + 1194 + randX, 141 + randY, wavegh[windex], true);
				wdiv = wdiv * 10;
			}
			break;
			delete player;
		}

		//DrawFormatString(480, 480, GetColor(255, 255, 255), "pushflagoption:%d", sceneflag);
		//DrawGraph(34, 34, guide, true);
		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似50FPS)
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