#include "../dxlib_ext/dxlib_ext.h"
#include "game_manager.h"
#include <fstream>
#include <sstream>

game_manager::game_manager() {
	//インスタンス生成
	PLY = new player;
	BK = new background;
	SO = new sound;

	int poolflag = false;

	FILE *fp;

	std::vector<std::string> strvec;

	std::string str_buf;
	std::string str_conma_buf;
	std::string input_csv_file_path = "readfile/enemydata.csv";

	//ファイルオープン
	std::ifstream ifs_csv_file(input_csv_file_path);
	//CSVのデータをカンマ区切りで格納していく
	//参考:https://qiita.com/shirosuke_93/items/d5d068bb15c8e8817c34
	while (std::getline(ifs_csv_file,str_buf)) {

		std::istringstream i_stream(str_buf);

		while (getline(i_stream,str_conma_buf,',')) {

			strvec.push_back(str_conma_buf);

		}
	}
	totalenemycnt = strvec.size() / LoadCSVData - 1;
		//あまり分をバッファに格納
		for (int i = 0; i < strvec.size() / LoadCSVData - 1;i++) {
			enemybuf[i].enemyNo = atoi(strvec[0 + ((i + 1) * LoadCSVData)].c_str());
			enemybuf[i].bulletNo = atoi(strvec[1 + ((i + 1) * LoadCSVData)].c_str());
			enemybuf[i].movepattern = atoi(strvec[2 + ((i + 1) * LoadCSVData)].c_str());
			enemybuf[i].bulletpattern = atoi(strvec[3 + ((i + 1) * LoadCSVData)].c_str());
			enemybuf[i].appartime = atoi(strvec[4 + ((i + 1) * LoadCSVData)].c_str());
			enemybuf[i].stop = atoi(strvec[5 + ((i + 1) * LoadCSVData)].c_str());
			enemybuf[i].shottime = atoi(strvec[6 + ((i + 1) * LoadCSVData)].c_str());
			enemybuf[i].comeback = atoi(strvec[7 + ((i + 1) * LoadCSVData)].c_str());
			enemybuf[i].x = atoi(strvec[8 + ((i + 1) * LoadCSVData)].c_str());
			enemybuf[i].y = atoi(strvec[9 + ((i + 1) * LoadCSVData)].c_str());
			enemybuf[i].bulletspeed = atoi(strvec[10 + ((i + 1) * LoadCSVData)].c_str());
			enemybuf[i].HP = atoi(strvec[11 + ((i + 1) * LoadCSVData)].c_str());
			enemybuf[i].item = atoi(strvec[12 + ((i + 1) * LoadCSVData)].c_str());
			enemybuf[i].threeway = atoi(strvec[13 + ((i + 1) * LoadCSVData)].c_str());
			enemybuf[i].bossflag = atoi(strvec[14 + ((i + 1) * LoadCSVData)].c_str());
		}
	for (int i = 0; i < ENEMY_NUM; i++) {
		EN[i] = new enemy();
		IT[i] = new item();
	}
}

game_manager::~game_manager() {
	//デストラクタもなんかかく
}

void game_manager::scenemanager() {
	//sceneの値によって行う処理を変える
	switch (nowscene) {
		case LOGO:
			sceneLOGO();
			break;
		case MAIN_TITLE:
			sceneTITLE();
			break;
		case GAME_READY:
			sceneREADY();
			break;
		case GAME_MAIN:
			sceneMAIN();
			break;
		case GAME_OVER:
			sceneGAMEOVER();
			break;
		case GAME_CLEAR:
			sceneGAMECLEAR();
			break;
	}
}

void game_manager::sceneLOGO() {
	//フェードイン試作処理
	SO->Init();
	if (Fadetimer < Fadecnt || 180 - Fadecnt * 2 <= Fadetimer) {
		SetDrawBright(0, 0, 0);
	}
	else if (Fadecnt <= Fadetimer && Fadetimer < Fadecnt * 2 || 180 - Fadecnt * 3 <= Fadetimer && Fadetimer < 180 - Fadecnt * 2) {
		SetDrawBright(64, 64, 64);
	}
	else if (Fadecnt <= Fadetimer * 2 && Fadetimer < Fadecnt * 3 || 180 - Fadecnt * 4 <= Fadetimer && Fadetimer < 180 - Fadecnt * 3) {
		SetDrawBright(128, 128, 128);
	}
	else {
		SetDrawBright(255, 255, 255);
	}

	//ロゴ画面（Maked By Taiki Mizuta)
	DrawStringEx(WINDOW_X_SIZE / 2 - 100, WINDOW_Y_SIZE / 2 - 50, -1, "Maked By Taiki Mizuta");//ウィンドウのど真ん中に表示したいので調整
	if (200 <= Fadetimer) {
		Fadetimer = 0;
		titlegh = LoadGraph("graphics/title.png");
		cleargh = LoadGraph("graphics/text_gameclear_j.png");
		nowscene = MAIN_TITLE;
	}
	Fadetimer++;
}

void game_manager::sceneTITLE() {
	SetDrawBright(255, 255, 255);
	SetDrawBright(128, 128, 128);
	SetDrawBright(0, 0, 0);

	SetDrawBright(0, 0, 0);
	SetDrawBright(128, 128, 128);
	SetDrawBright(255, 255, 255);
	//メインタイトルが上に上がってくるやつ
	if (uplength <= 200) {
		uplength++;
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			uplength = 200;
		}
	}//上に上がりきったらPRESSENTERKEY表示
	else {
		SO->PlayBGM(0);
		visibleloop++;
		if (visibleloop >= 30 && visibleswitch == true) {
			visibleloop = 0;
			visibleswitch = false;
		}
		else if (visibleloop >= 30 && visibleswitch == false) {
			visibleloop = 0;
			visibleswitch = true;
		}

		if (visibleswitch) {
			DrawStringEx(WINDOW_X_SIZE / 2 - 75, WINDOW_Y_SIZE / 2 + 100, -1, "PRESS ENTER KEY");
		}
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			SO->StopBGM(0);
			nowscene = GAME_READY;	//READY画面へ移動
		}
	}
	DrawRotaGraph(WINDOW_X_SIZE / 2, WINDOW_Y_SIZE / 2 - uplength + 100, 1.0, 0.0, titlegh, TRUE);
}
void game_manager::sceneREADY() {
	//ステージ番号、残機数表示　この間に必要画像データをロードする　3~4秒したらゲームスタート
	DrawStringEx(WINDOW_X_SIZE / 2 - 70, WINDOW_Y_SIZE / 2 - 100, -1, "STAGE:%d", get_stg_num());
	DrawStringEx(WINDOW_X_SIZE / 2 - 70, WINDOW_Y_SIZE / 2 - 50, -1, "PLAYER残機:%d", PLY->getlifestock());
	uplength = 0;
	this->Init();
	Fadetimer++;
	if (Fadetimer >=120) {
		Fadetimer = 0;
		nowscene = GAME_MAIN;
	}

}

void game_manager::sceneMAIN() {
	viewupdate();
}

void game_manager::sceneGAMEOVER() {
	DrawStringEx(WINDOW_X_SIZE / 2 - 80, WINDOW_Y_SIZE / 2, -1, "GAMEOVER");
	movetotal++;
	if (180 < movetotal) {
		movetotal = 0;
		nowscene = MAIN_TITLE;
	}
}

void game_manager::sceneGAMECLEAR() {
	DrawRotaGraph(WINDOW_X_SIZE / 2, WINDOW_Y_SIZE / 2 - uplength - 100, 0.8, 0.0, cleargh, TRUE);
	movetotal++;
	if (240 < movetotal) {
		movetotal = 0;
		nowscene = MAIN_TITLE;
	}
}


void game_manager::DEBUG_VIEW() {
	DrawStringEx(100, 100, -1, "NOW_SCENE:%d", nowscene);
	DrawStringEx(210, 100, -1, "NOW_STAGE:%d", get_stg_num());
	DrawStringEx(320, 100, -1, "STAGE_MOVE:%d", get_stg_move());
}
void game_manager::Init() {
	if (!init) {
		PLY->Init();
		for (int i = 0; i < ENEMY_NUM; i++) {
			EN[i]->Init();
			IT[i]->Init();
		}
		BK->Init();
		enemypool();
		init = true;
	}
}

void game_manager::viewupdate() {
	BK->Update();
	SO->PlayBGM(1);
	movetotal++;
	
	for (int i = 0; i < ENEMY_NUM; i++) {
		EN[i]->set_calltime(movetotal);
		EN[i]->Update();
		IT[i]->viewupdate();
	}
	
	//DrawStringEx(100, 400, -1, "movetotal[%d]",movetotal);

	PLY->Update();

	//画面手前に移す背景画像
	BK->ForeDraw();
	//ライフ表示
	PLY->Drawlife();
	PLY->Drawtype();
	CollisionAll();
	if ( poolcnt < totalenemycnt) {
		//デスフラグ立ってるやつに値をほうりこむ処理
		enemypool();
	}
	if (PLY->getdeathflag()) {
		restartwait++;
		if (50 < restartwait) {
			restartwait = 0;
			SO->StopBGM(1);
			plydeathmove();
		}
	}
	if (clearflag) {
		restartwait++;
		if (70 < restartwait) {
			Default();
			BK->Default();
			PLY->Default();
			for (int i = 0; i < ENEMY_NUM; i++) {
				EN[i]->Default();
				IT[i]->Default();
			}
			enemypool();
			restartwait = 0;
			clearflag = 0;
			SO->StopBGM(1);
			nowscene = GAME_CLEAR;
		}
	}
}

void game_manager::CollisionAll() {
	float px, py,plx,ply,ix,iy,ebx,eby;
	float ex = 0, ey = 0;
	//プレイヤーの弾と敵の当たり判定
	for (int i = 0; i < 20;i++) {
		if (PLY->getshotposition(i,&px,&py)) {
			for (int s = 0; s < ENEMY_NUM; s++) {
				if (EN[s]!=NULL && !EN[s]->getdeathflag() && EN[s]->get_appartime() < movetotal) {
					EN[s]->getPosition(&ex, &ey);
					//自分の弾と敵の当たり判定
					if (CircleCollision(20, 30, px, ex, py, ey)) {
						if (!EN[s]->getnodamage()) {
							switch (checkthreeway(PLY->getshotthreeway(i), EN[s]->getthreeway())) {
							case 0://自分が勝ってるとき
								EN[s]->setHP(EN[s]->getHP() - PLY->getattackpoint() * 2);
								EN[s]->setnodamage(true);
								//SO->PlaySE(4);うるさいのでコメントアウト
								DrawStringEx(400, 700, -1, "EXTRA HIT!");
								break;
							case 1://あいこのとき
								EN[s]->setHP(EN[s]->getHP() - PLY->getattackpoint());
								EN[s]->setnodamage(true);
								//SO->PlaySE(3);
								DrawStringEx(400, 700, -1, "HIT");
								break;
							case 2://負けてるとき
								if (PLY->getattackpoint() <= 1) {
									//なにもしない(ダメージは0)
									DrawStringEx(400, 700, -1, "NO DAMAGE");
								}
								else {
									EN[s]->setHP(EN[s]->getHP() - PLY->getattackpoint() / 2);
									EN[s]->setnodamage(true);
									DrawStringEx(400, 700, -1, "NOT GOOD DAMAGE");
								}
								//SO->PlaySE(2);
								break;
							case 3://ボスのダメージ受けない状態
								DrawStringEx(400, 700, -1, "NO　DAMAGE");
								break;
							}
							if (EN[s]->getthreeway() == 3) {
								SO->PlaySE(1);
							}
							if (EN[s]->getHP() <= 0 && EN[s]->getdeathflag() == false) {
								//ダメージ計算
								EN[s]->set_movechg(false);
								EN[s]->setdeathflag(true);
								EN[s]->set_ef_x(EN[s]->getpos_x());
								EN[s]->set_ef_y(EN[s]->getpos_y());
								EN[s]->set_ef_flag(true);
								SO->PlaySE(0);
								//倒した敵がボスだった場合
								if (EN[s]->get_bossflag()) {
									clearflag = true;
								}
								//倒した敵がアイテムを持っていた場合
								if (EN[s]->get_itemcode()) {
									for (int z = 0; z < ENEMY_NUM; z++) {
										if (!IT[z]->GetFlag()) {
											IT[z]->SetFlag(ex, ey, EN[s]->get_itemcode());
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	//プレイヤーと敵の当たり判定
	if (!PLY->getdeathflag() && !PLY->getnodamage()) {
		PLY->getplyposition(&plx,&ply);
		for (int s = 0; s < ENEMY_NUM; s++) {
			//弾との当たり判定処理をやったうえで敵が生きているかの判定
			if (EN[s] != NULL && !EN[s]->getdeathflag() && EN[s]->get_appartime() < movetotal && !PLY->getnodamage()) {
				EN[s]->getPosition(&ex, &ey);

				if (CircleCollision(20,30,plx,ex,ply,ey)) {
					PLY->setHP(PLY->getHP() - 1);
					PLY->setnodamage(true);
					if (PLY->getHP() <= 0) {
						PLY->seteffect();
						PLY->setdeathflag(true);
						SO->PlaySE(0);
						PLY->set_lifestock(PLY->getlifestock() - 1);
					}
				}
			}
		}
	}

	//敵の弾との当たり判定
	if (!PLY->getdeathflag() && !PLY->getnodamage()) {
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (EN[i]->getshotposition(i, &ebx, &eby) && !PLY->getnodamage()) {
				if (CircleCollision(30, 35, plx, ebx, ply, eby)) {
					PLY->setHP(PLY->getHP() - 1);
					PLY->setnodamage(true);
					if (PLY->getHP() <= 0) {
						PLY->seteffect();
						PLY->setdeathflag(true);
						SO->PlaySE(0);
						PLY->set_lifestock(PLY->getlifestock() - 1);
					}
				}
			}
		}
	}

	//アイテムとプレイヤーの当たり判定
	if (!PLY->getdeathflag()) {
		PLY->getplyposition(&plx, &ply);
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (IT[i]->GetFlag()) {
				IT[i]->GetPosition(&ix, &iy);
				if (CircleCollision(20, 30, plx, ix, ply, iy)) {
					if (PLY->getHP() < 3 && IT[i]->GetFlag()) {
						PLY->setHP(PLY->getHP() + 1);
					}
					IT[i]->Delete();
				}
			}
		}
	}
	//ダメージ受けてる状態の時のwait
	if (!PLY->getdeathflag() && PLY->getnodamage()) {
		PLY->damagewait();
	}

	for (int i = 0; i < ENEMY_NUM; i++) {
		if (EN[i]->getnodamage()) {
			EN[i]->damagewait();
		}
	}
}

int game_manager::checkthreeway(int a, int b) {
	if (b == 3) {//無敵状態はなにもしない
		return 3;
	}
	else if (a < b && !(a == 0 &&b == 2) || a == 2 && b == 0) {
		//じゃんけんで自機が有利のケース
		return 0;
	}
	else if (a == b) {
		//あいこのケース
		return 1;
	}
	else if(a > b && (a == 2 && b == 0) || a == 0 && b == 2) {
		//じゃんけんで自機が不利のケース
		return 2;
	}
}

void game_manager::enemypool() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (EN[i]->getdeathflag()) {
			EN[i]->setenemypool(enemybuf[poolcnt].enemyNo,
				enemybuf[poolcnt].bulletNo,
				enemybuf[poolcnt].movepattern,
				enemybuf[poolcnt].bulletpattern,
				enemybuf[poolcnt].appartime,
				enemybuf[poolcnt].stop,
				enemybuf[poolcnt].shottime,
				enemybuf[poolcnt].comeback,
				enemybuf[poolcnt].x,
				enemybuf[poolcnt].y,
				enemybuf[poolcnt].bulletspeed,
				enemybuf[poolcnt].HP,
				enemybuf[poolcnt].item,
				enemybuf[poolcnt].threeway,
				enemybuf[poolcnt].bossflag);
			EN[i]->setdeathflag(false);
			//初期値へリセット
			EN[i]->setpos_x(1024);
			EN[i]->setpos_y(0);
			EN[i]->set_th(0);
			poolcnt++;
			EN[i]->set_shotwaittime(0);
			EN[i]->set_callshot(false);
		}
	}
}
bool  game_manager::CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2) {

	double hl = c1 + c2;
	double xl = cx1 - cx2;
	double yl = cy1 - cy2;

	if (hl * hl >= xl * xl + yl * yl) {
		return true;
	}
	else {
		return false;
	}
}

void game_manager::plydeathmove() {
	Default();
	BK->Default();
	PLY->Default();
	for (int i = 0; i < ENEMY_NUM;i++) {
		EN[i]->Default();
		IT[i]->Default();
	}
	enemypool();
	if (PLY->getlifestock() < 0) {
		PLY->set_lifestock(2);
		nowscene = GAME_OVER;
	}
	else {
		nowscene = GAME_READY;	//READY画面へ移動
	}
}

void game_manager::Default() {
	stg_move = 0;
	poolcnt = 0;
	movetotal = 0;
}

//set
void game_manager::set_stg_num(int num) {
	stg_num = num;
}
void game_manager::set_stg_move(int num) {
	stg_move = num;
}

//get
int game_manager::get_stg_num() {
	return stg_num;
}

int game_manager::get_stg_move() {
	return stg_move;
}

int game_manager::get_nowscene() {
	return nowscene;
}
