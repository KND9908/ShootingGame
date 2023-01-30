#pragma once
#include"creaturebase.h"
#include "bullet.h"
/// <summary>
/// プレイヤーの処理を管理するクラス
/// </summary>
class player :public creaturebase {
public:
	player();
	//プレイヤーのポジションをX軸Y軸共に渡す
	void getplyposition(float* x, float* y);
	//PlayerのHPを画面上に描画
	void Drawlife();
	//プレイヤーの現属性を画面に描画
	void Drawtype();
	//プレイヤーがダメージを受けた時の無敵状態判定処理
	void damagewait();
	//
	void Draweffect();
	//
	void seteffect();

	virtual void Update();

	virtual void Init();

	//プレイヤーの状態を一式初期状態にもどす処理
	void Default();

	//get
	int get_pos_x();
	int get_pos_y();
	int get_life();
	int get_threeway();
	int getshotthreeway(int index);
	int getlifestock();
	bool get_deathflag();
	bool getshotposition(int index, float* x, float* y);

	//set
	void set_pos_x(float num);
	void set_pos_y(float num);
	void set_life(int num);
	void set_threeway(int num);
	void set_deathflag(bool flag);
	void set_lifestock(int lifestock);
protected:
	//グラフィックハンドラ
	int pl_gh[3] = { 0 };//プレイヤー0:グー1:チョキ2:パー
	int pl_l_gh = 0; //ライフポイント
	//弾
	bool pl_gameoverflag = false;

	int pl_lifestock = 0;//残機
	int pl_allcount = 0;//アニメーションの描画の切り替えタイミングで使用するフレームのカウント
	int pl_ghn = 0;//アニメーションの現在の数
	int pl_invisitime = 0;//無敵時間中のカウント

	int pl_b_gh_g = 0;
	int pl_b_gh_c = 0;
	int pl_b_gh_p = 0;

	int ef_gh[7] = { 0 };//エフェクトのグラフィックハンドラ
	//エフェクト発生処理周り
	bool ef_flag = false;
	int ef_cnt = 0;
	int ef_cnt_det = 0;
	int ef_x = 0;
	int ef_y = 0;

	void Move();
	void Shot();
	void Draw();
	void chgthreeway();
	//弾幕所持数
	bullet p_bullet[20];
};