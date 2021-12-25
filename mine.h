#pragma once
#include"Transform.h"

typedef struct//初期化用
{
	int def_explosion_time;
	int def_bombs_time;
	int transform_xr;
	int transform_yr;
	int explosion_r;
}MimeInitialize;

class Mine
{
public:
	Mine();//コントラスタ
	~Mine();//デストラクタ
	void form(Transform transForm, int& frame);//生成
	void HitBox(Transform transform, int& hp);//当たり判定
	void Move();//動き
	void Draw();//描画
	void initialize(MimeInitialize& mimeinitialize);//初期化

	//セッター
	void SetMineFlag(bool flag);
	void SetRand(int end_frame);

private:
	int rand;//ランダム
	bool damage_flag;//1ダメージしか与えないようにするフラグ
	Transform transform[10];//座標
	int explosion_r;//爆発の半径
	int explosion_time[10];//爆発するまでの時間
	bool explosion_flag[10];//爆発フラグ
	int bombs_time[10];//爆発している時間
	bool exising_flag[10];//存在フラグ
	bool mine_flag;//地雷を置くフラグ

	//初期値
	int def_explosion_time;
	int def_bombs_time;
};

