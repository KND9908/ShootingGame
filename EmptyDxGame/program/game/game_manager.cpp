#include "../dxlib_ext/dxlib_ext.h"
#include "game_manager.h"
#include <fstream>
#include <sstream>

game_manager::game_manager() {
	//�C���X�^���X����
	PLY = new player;
	BK = new background;
	SO = new sound;

	int poolflag = false;

	FILE *fp;

	std::vector<std::string> strvec;

	std::string str_buf;
	std::string str_conma_buf;
	std::string input_csv_file_path = "readfile/enemydata.csv";

	//�t�@�C���I�[�v��
	std::ifstream ifs_csv_file(input_csv_file_path);
	//CSV�̃f�[�^���J���}��؂�Ŋi�[���Ă���
	//�Q�l:https://qiita.com/shirosuke_93/items/d5d068bb15c8e8817c34
	while (std::getline(ifs_csv_file,str_buf)) {

		std::istringstream i_stream(str_buf);

		while (getline(i_stream,str_conma_buf,',')) {

			strvec.push_back(str_conma_buf);

		}
	}
	totalenemycnt = strvec.size() / LoadCSVData - 1;
		//���܂蕪���o�b�t�@�Ɋi�[
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
	//�f�X�g���N�^���Ȃ񂩂���
}

void game_manager::scenemanager() {
	//scene�̒l�ɂ���čs��������ς���
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
	//�t�F�[�h�C�����쏈��
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

	//���S��ʁiMaked By Taiki Mizuta)
	DrawStringEx(WINDOW_X_SIZE / 2 - 100, WINDOW_Y_SIZE / 2 - 50, -1, "Maked By Taiki Mizuta");//�E�B���h�E�̂ǐ^�񒆂ɕ\���������̂Œ���
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
	//���C���^�C�g������ɏオ���Ă�����
	if (uplength <= 200) {
		uplength++;
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			uplength = 200;
		}
	}//��ɏオ�肫������PRESSENTERKEY�\��
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
			nowscene = GAME_READY;	//READY��ʂֈړ�
		}
	}
	DrawRotaGraph(WINDOW_X_SIZE / 2, WINDOW_Y_SIZE / 2 - uplength + 100, 1.0, 0.0, titlegh, TRUE);
}
void game_manager::sceneREADY() {
	//�X�e�[�W�ԍ��A�c�@���\���@���̊ԂɕK�v�摜�f�[�^�����[�h����@3~4�b������Q�[���X�^�[�g
	DrawStringEx(WINDOW_X_SIZE / 2 - 70, WINDOW_Y_SIZE / 2 - 100, -1, "STAGE:%d", get_stg_num());
	DrawStringEx(WINDOW_X_SIZE / 2 - 70, WINDOW_Y_SIZE / 2 - 50, -1, "PLAYER�c�@:%d", PLY->getlifestock());
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

	//��ʎ�O�Ɉڂ��w�i�摜
	BK->ForeDraw();
	//���C�t�\��
	PLY->Drawlife();
	PLY->Drawtype();
	CollisionAll();
	if ( poolcnt < totalenemycnt) {
		//�f�X�t���O�����Ă��ɒl���ق��肱�ޏ���
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
	//�v���C���[�̒e�ƓG�̓����蔻��
	for (int i = 0; i < 20;i++) {
		if (PLY->getshotposition(i,&px,&py)) {
			for (int s = 0; s < ENEMY_NUM; s++) {
				if (EN[s]!=NULL && !EN[s]->getdeathflag() && EN[s]->get_appartime() < movetotal) {
					EN[s]->getPosition(&ex, &ey);
					//�����̒e�ƓG�̓����蔻��
					if (CircleCollision(20, 30, px, ex, py, ey)) {
						if (!EN[s]->getnodamage()) {
							switch (checkthreeway(PLY->getshotthreeway(i), EN[s]->getthreeway())) {
							case 0://�����������Ă�Ƃ�
								EN[s]->setHP(EN[s]->getHP() - PLY->getattackpoint() * 2);
								EN[s]->setnodamage(true);
								//SO->PlaySE(4);���邳���̂ŃR�����g�A�E�g
								DrawStringEx(400, 700, -1, "EXTRA HIT!");
								break;
							case 1://�������̂Ƃ�
								EN[s]->setHP(EN[s]->getHP() - PLY->getattackpoint());
								EN[s]->setnodamage(true);
								//SO->PlaySE(3);
								DrawStringEx(400, 700, -1, "HIT");
								break;
							case 2://�����Ă�Ƃ�
								if (PLY->getattackpoint() <= 1) {
									//�Ȃɂ����Ȃ�(�_���[�W��0)
									DrawStringEx(400, 700, -1, "NO DAMAGE");
								}
								else {
									EN[s]->setHP(EN[s]->getHP() - PLY->getattackpoint() / 2);
									EN[s]->setnodamage(true);
									DrawStringEx(400, 700, -1, "NOT GOOD DAMAGE");
								}
								//SO->PlaySE(2);
								break;
							case 3://�{�X�̃_���[�W�󂯂Ȃ����
								DrawStringEx(400, 700, -1, "NO�@DAMAGE");
								break;
							}
							if (EN[s]->getthreeway() == 3) {
								SO->PlaySE(1);
							}
							if (EN[s]->getHP() <= 0 && EN[s]->getdeathflag() == false) {
								//�_���[�W�v�Z
								EN[s]->set_movechg(false);
								EN[s]->setdeathflag(true);
								EN[s]->set_ef_x(EN[s]->getpos_x());
								EN[s]->set_ef_y(EN[s]->getpos_y());
								EN[s]->set_ef_flag(true);
								SO->PlaySE(0);
								//�|�����G���{�X�������ꍇ
								if (EN[s]->get_bossflag()) {
									clearflag = true;
								}
								//�|�����G���A�C�e���������Ă����ꍇ
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
	//�v���C���[�ƓG�̓����蔻��
	if (!PLY->getdeathflag() && !PLY->getnodamage()) {
		PLY->getplyposition(&plx,&ply);
		for (int s = 0; s < ENEMY_NUM; s++) {
			//�e�Ƃ̓����蔻�菈��������������œG�������Ă��邩�̔���
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

	//�G�̒e�Ƃ̓����蔻��
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

	//�A�C�e���ƃv���C���[�̓����蔻��
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
	//�_���[�W�󂯂Ă��Ԃ̎���wait
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
	if (b == 3) {//���G��Ԃ͂Ȃɂ����Ȃ�
		return 3;
	}
	else if (a < b && !(a == 0 &&b == 2) || a == 2 && b == 0) {
		//����񂯂�Ŏ��@���L���̃P�[�X
		return 0;
	}
	else if (a == b) {
		//�������̃P�[�X
		return 1;
	}
	else if(a > b && (a == 2 && b == 0) || a == 0 && b == 2) {
		//����񂯂�Ŏ��@���s���̃P�[�X
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
			//�����l�փ��Z�b�g
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
		nowscene = GAME_READY;	//READY��ʂֈړ�
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
