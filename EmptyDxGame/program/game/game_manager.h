#pragma once
#include "define.h";
#include"player.h";
#include"enemy.h";
#include"background.h";
#include"item.h";
#include"sound.h";
#include <string>

#define ENEMY_NUM 8
/// <summary>
/// ゲームの進行を管理するクラス
/// </summary>
class game_manager {
private:
	
	//---ゲームタイトル用---
	int Fadetimer = 0;

	//---タイトルシーン用---
	int uplength = 0;
	int titlegh = 0;
	int cleargh = 0;
	int visibleloop = 0;
	bool visibleswitch = true;

	int restartwait = 0;//playerが死んでからの再スタートWaitタイマー

	//---ゲームメイン用---
	//各クラスのインスタンスを定義
	player* PLY;
	enemy* EN[ENEMY_NUM];//1画面における敵の最大描画数
	item* IT[ENEMY_NUM];//アイテムの最大画面描画数（敵の数以上は出ない）
	background* BK;
	sound* SO;

	ENEMYDATA enemybuf[40] = { 0 };//画面に描画しきれない敵データのロード結果はここに格納
	int totalenemycnt = 0; //1ステージに出てくる総敵数
	int nowscene = LOGO;	//シーン管理用
	bool init = false;//初期化判定用フラグ
	int stg_num = 1; //ステージカウント　初期値1
	int stg_move = 0;//ステージの移動距離_x(カメラ概念的な)
	int poolcnt = 0; //データ再格納処理のカウント
	
public:
	int movetotal = 0; //ゲーム開始からの経過時間（背景移動や敵の描画タイミングに使用）
	game_manager();
	~game_manager();

	bool clearflag = false;

	void scenemanager();//シーンのトータルを管理するクラス

	void sceneLOGO();//ロゴのシーン

	void sceneTITLE();//タイトルシーン

	void sceneREADY();//レディ画面

	void sceneMAIN();//メイン画面

	void sceneGAMEOVER();//ゲームオーバー画面

	void sceneGAMECLEAR();//ゲームクリア画面

	void DEBUG_VIEW();//デバッグ起動時に、内部データを表示するための関数

	void plydeathmove();//プレイヤーがやられてからの画面遷移コントロール

	void Init();	  //イニシャライズ処理（画像ロードとか）

	void Default();	  //値を初期値へ戻す処理

	void viewupdate();//ゲーム画面の要素のアップデートを担う

	void CollisionAll();//	当たり判定の監視を行う

	void enemypool();//空きができているenemyクラスにデータを再格納する
					  
	//当たり判定判別フラグ
	bool CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2);
	
	int checkthreeway(int a, int b);//さんすくみ比較用
	
	//set
	void set_stg_num(int num);
	void set_stg_move(int num);

	//get
	int get_stg_num();
	int get_stg_move();
	int get_nowscene();
};