#pragma once
#include "creaturebase.h"
#include "bullet.h"
#define LoadCSVData 15
/// <summary>
/// 敵のデータを管理するクラス
/// </summary>
class enemy:public creaturebase {
public:
	//倒されたエネミーの領域を再利用可能にするための処理
	void setenemypool(int enemyNo, int bulletNo, int movepattern,
		int bulletpattern, int appeartime, int stop, int shottime, int comeback,
		float x, float y, int bulletspeed, int HP, int item,int threeway,int bossflag);
	void Update();
	void Init();
	void Default();

	bool getshotposition(int index, float* x, float* y);
	void setpos_x(float x);

	void getPosition(float* px, float* py);

	void Draweffect();//エフェクトを実行する関数
	
	void damagewait();
	//get
	int get_appartime();
	int get_itemcode();
	bool get_bossflag();

	//set
	void set_callshot(bool flag);

	void set_shotwaittime(int num);

	void set_th(float num);
	
	void set_calltime(int num);

	void set_ef_x(float num);

	void set_ef_y(float num);

	void set_ef_flag(bool flag);

	void set_movechg(bool flag);
protected:
	int en_No = 0;
	int en_bulletNo = 0;
	int en_movepattern = 0;
	int en_bulletpattern = 0;
	int en_stop = 0;
	int en_shottime = 0;
	int en_comeback = 0;
	float en_base_x = 1024;
	float en_base_y = 0;
	int en_bulletspeed = 0;

	int en_shotwaittime = 0;
	int en_calltime = 0;
	bool en_callshot = false; //弾の発射トリガー
	bool en_finishshot = false;//弾の発射完了したか

	bool en_movechg = false;
	int en_itemcode = 0;
	int en_appar_time = 0;

	//ボスとして管理する敵の場合ONにする
	bool bossflag = false;

	//ダメージを受けたときに再度ダメージを受けるまでの無敵時間を管理するクラス
	int en_damagewaittime = 0;
	//円運動用の引数
	float en_th = 0;

	//敵の動きの制御に用いる関数
	int en_movecnt = 0;
	int en_movecnt_b = 0;

	int en_gh[6] = { 0 };//0:岩敵 1~2:ハサミ敵 3~5:紙敵

	int bossdrawcnt = 0;
	int boss_gh[4] = { 0 };//0:デフォルト1:グー属性2:チョキ3:パー
	int boss_sh_gh[3] = { 0 };//ボスのバリアグラフィック

	int en_gh_num = 0; //グラフィックハンドルの順番選択
	int en_speedadj = 0;//アニメーションのスピード調整用

	bullet en_bullet[20];//一度に出せる弾は2つまで（雑魚の場合)

	//爆発エフェクトを発生させる位置
	int ef_x = 0;
	int ef_y = 0;
	bool ef_flag = false; //爆発エフェクト用フラグ

	int ef_gh[7] = { 0 };//爆発エフェクト
	int ef_cnt = 0;//エフェクトアニメーション調整タイマー
	int ef_cnt_det = 0;//より細かい調整

	void Move();
	void Draw();
	void Shot();

	//ボスの動き関連
	bool boss_typechgflag = false;
	bool boss_drawchgflag = false;
	int boss_typechgcount = 0;
	int boss_typechgcountpar = 5;
	int boss_nextchgtype = 0;
	int boss_chgrand = false;
	void typechangeDraw(int nextchg);
};
//CSVから読み取った敵の情報の格納用構造体
struct ENEMYDATA {
	int enemyNo;
	int bulletNo;
	int movepattern; 
	int bulletpattern;
	int appartime;
	int stop;
	int shottime;
	int comeback;
	float x;
	float y;
	int bulletspeed;
	int HP;
	int item;
	int threeway;
	int bossflag;
};