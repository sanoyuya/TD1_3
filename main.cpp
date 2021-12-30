#include "DxLib.h"
#include"player.h"
#include"enemy.h"
#include"bullet.h"
#include"subboss.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "自滅ゲー";

// ウィンドウ横幅
const int WIN_WIDTH = 1376;

// ウィンドウ縦幅
const int WIN_HEIGHT = 960;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
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


	// ゲームループで使う変数の宣言
	const int ENEMY_MAX = 5;
	int sceneflag = 0;
	Player* player = new Player();
	Enemy* enemy = new Enemy[ENEMY_MAX];
	SubBoss* sub_boss = new SubBoss;

	SubBossForm("subbosstest.csv", 1, *sub_boss);

	int wave_num = 1;
	bool game_set = false;
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
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				sceneflag = 2;
			}if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
				sceneflag = 2;
			}

			break;

		case 1:
			//ステージ選択
			break;

		case 2:
			//プレイ画面

#pragma region 敵データ読み込み
			if (game_set == false)
			{
				switch (wave_num)
				{
				case 1:
					EnemyForm("WAVE_ENEMY_DATA/wave1.csv", ENEMY_MAX, enemy);
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
				}

			}
#pragma endregion

			for (int i = 0; i < ENEMY_MAX; i++)
			{
				enemy[i].Move(*player);
			}

			/*enemy[0].Move(*player);
			enemy[1].Move(*player);
			enemy[0].ExplosionBommer(enemy[1], *player);*/

			//sub_boss->Move(*player);

#pragma region 体力減少
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					player->HP(enemy[i].GetBulletTransform(j), enemy[i].GetEnmyBullet(), j);

					for (int k = 0; k < ENEMY_MAX; k++)
					{
						if (i != k)
						{
							if (enemy[i].GetEnemyFlag() == true && enemy[k].GetEnemyFlag() == true)
							{
								enemy[i].HP(enemy[k].GetBulletTransform(j), enemy[k].GetEnmyBullet(), j);
							}
						}
					}
				}
			}
			for (int i = 0; i < 4; i++)
			{
				player->HP(sub_boss->GetBulletTransform(i), sub_boss->GetEnmyBullet(), i);
			}
#pragma endregion

			//waveクリア判定
			for (int i = 0; i < ENEMY_MAX; i++)
			{
				if (enemy[i].GetEnemyFlag() == true ||
					
					enemy[i].GetAppearTime() != -1)
				{
					i--;
					break;
				}

				if (i == ENEMY_MAX-1)
				{
					game_set = false;
					wave_num++;
				}
			}

			player->PlayerPadMove(keys, oldkeys);

			sceneflag = player->Result();

			break;

		case 3:
			//リザルト画面(ゲームオーバー)
			break;

		case 4:
			//リザルト画面(ゲームクリア)
			break;
		}
		// 描画処理
		switch (sceneflag) {//シーン管理
		case 0:
			//タイトル
			break;

		case 1:
			//ステージ選択
			break;

		case 2:
			//プレイ画面
			for (int i = 0; i < ENEMY_MAX; i++)
			{
			enemy[i].Draw(40*i);
			}

			player->Draw();
			sub_boss->Draw();

			break;
			delete player;
		case 3:
			//リザルト画面(ゲームオーバー)
			break;

		case 4:
			//リザルト画面(ゲームクリア)
			break;
		}

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
	delete[]enemy;
	delete sub_boss;
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
