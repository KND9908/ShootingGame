#include "../dxlib_ext/dxlib_ext.h"
#include"enemy.h"
#include "stdio.h"

#define _USE_MATH_DEFINES
#include<math.h>

void enemy::Update() {
	Move();
	Shot();
	Draw();
	if (!deathflag && en_appar_time < en_calltime) {
		en_shotwaittime++;
	}
	if (en_shottime <=en_shotwaittime) {
		en_callshot = true;
		en_shotwaittime = 0;
	}
	if (pos_x <= -50 || pos_x >= 1100 || pos_y <= -50 || pos_y >= 800) {
		deathflag = true;
	}
}

void enemy::Init() {
	//キャラグラ
	en_gh[0] = LoadGraph("graphics/enemy_g.png");
	en_gh[1] = LoadGraph("graphics/enemy_t.png");
	en_gh[2] = LoadGraph("graphics/enemy_t2.png");
	en_gh[3] = LoadGraph("graphics/enemy_p.png");
	en_gh[4] = LoadGraph("graphics/enemy_p2.png");
	en_gh[5] = LoadGraph("graphics/enemy_p3.png");

	boss_gh[0] = LoadGraph("graphics/boss/boss_g.png");
	boss_gh[1] = LoadGraph("graphics/boss/boss_c.png");
	boss_gh[2] = LoadGraph("graphics/boss/boss_p.png");
	boss_gh[3] = LoadGraph("graphics/boss/boss_n.png");

	boss_sh_gh[0] = LoadGraph("graphics/boss/baria1.png");
	boss_sh_gh[1] = LoadGraph("graphics/boss/baria2.png");
	boss_sh_gh[2] = LoadGraph("graphics/boss/baria3.png");

	srand((unsigned int)time(NULL));
	//弾初期化
	int b_gh_g = LoadGraph("graphics/shot.png");
	int b_gh_c = LoadGraph("graphics/shot2.png");
	int b_gh_p = LoadGraph("graphics/awa.png");
	int b_gh_ex = LoadGraph("graphics/fire.png");
	int w, h;

	deathflag = true;
	//エフェクト
	LoadDivGraph("graphics/pipo-btleffect036.png", 7, 7, 1, 120, 120, ef_gh);
	GetGraphSize(b_gh_g, &w, &h);
	for (int i = 0; i < sizeof en_bullet / sizeof en_bullet[0]; i++) {
		en_bullet[i].bu_shotflag = false;
		en_bullet[i].bu_gh[0] = b_gh_ex;
		en_bullet[i].bu_gh[1] = b_gh_ex;
		en_bullet[i].bu_gh[2] = b_gh_ex;
		en_bullet[i].bu_gh[3] = b_gh_ex;
		en_bullet[i].bu_width = w;
		en_bullet[i].bu_height = h;
	}
}

void enemy::Move() {
	if (!deathflag && en_appar_time < en_calltime) {
		if (bossflag == 1) {//登場時の処理
			if (en_base_x < pos_x) {
				pos_y = en_base_y;
				pos_x--;
			}
			else {
				switch (threeway) {
				case 0:
					en_movecnt_b++;

					if (en_movecnt_b > 300) {
						en_movecnt_b = 0;
						en_movecnt = 0;
						boss_chgrand = false;

						boss_nextchgtype = 3;
						boss_typechgflag = true;
						break;
					}
				case 1:
					en_movecnt_b++;

					if (en_movecnt_b > 300) {
						en_movecnt_b = 0;
						en_movecnt = 0;
						boss_chgrand = false;

						boss_nextchgtype = 3;
						boss_typechgflag = true;
						break;
					}
				case 2:
					en_movecnt_b++;

					if (en_movecnt_b > 300) {
						en_movecnt_b = 0;
						en_movecnt = 0;
						boss_chgrand = false;

						boss_nextchgtype = 3;
						boss_typechgflag = true;
						break;
					}
				case 3:
					if (en_movecnt > 360) {
						if (!boss_chgrand) {
							boss_nextchgtype = rand() % 3;
							boss_chgrand = true;
							boss_typechgflag = true;
						}
					}
					else {
						en_th += M_PI / 360;
						pos_y = en_base_y + 250 * sin(en_th);
						en_movecnt++;
					}
					break;
				}
			}
		}
		else {//雑魚の動き
			switch (threeway) {
			case 0:
				en_th += M_PI / 30;
				pos_y = en_base_y + 80 * sin(en_th);
				pos_x = pos_x - 2;
				break;
			case 1:
				en_movecnt++;
				pos_y = en_base_y;
				if (en_movecnt > 30) {
					en_movecnt = 0;
					en_movechg = true;
				}
				if (en_movechg) {
					pos_x = pos_x - 4;
				}
				else {
					pos_x = en_base_x;
				}
				break;
			case 2:
				if (pos_y > en_base_y) {
					en_movechg = true;
				}
				else {
					pos_y = pos_y + 2;
				}
				if (en_movechg) {
					pos_x = pos_x - 3;
				}
				else {
					pos_x = en_base_x;
				}
				break;
			}
		}
	}
}

void enemy::Draw() {
	if (!deathflag && en_appar_time < en_calltime ) {
		if (!bossflag) {
			switch (threeway) {
			case 0:
				DrawRotaGraph(pos_x, pos_y, 0.5, 0.0, en_gh[0], TRUE);
				break;
			case 1:
				DrawRotaGraph(pos_x, pos_y, 0.5, 0.0, en_gh[en_gh_num % 2 + 1], TRUE);
				break;
			case 2:
				if (en_movechg) {
					DrawRotaGraph(pos_x, pos_y, 0.5, 0.0, en_gh[5], TRUE);
				}
				else {
					DrawRotaGraph(pos_x, pos_y, 0.5, 0.0, en_gh[en_gh_num % 2 + 3], TRUE);
				}
				break;
			}
		}
		else {
			bossdrawcnt++;
			DrawRotaGraph(pos_x, pos_y, 0.5, 0.0, boss_sh_gh[2], TRUE);
			if (bossdrawcnt > 10 && bossdrawcnt < 40) {
				DrawRotaGraph(pos_x, pos_y, 0.5, 0.0, boss_sh_gh[1], TRUE);
			}
			if (bossdrawcnt > 20 && bossdrawcnt < 30) {
				DrawRotaGraph(pos_x, pos_y, 0.5, 0.0, boss_sh_gh[0], TRUE);
			}
			if (bossdrawcnt >= 50) {
				bossdrawcnt = 0;
			}if (boss_typechgflag) {
				typechangeDraw(boss_nextchgtype);
			}
			DrawRotaGraph(pos_x, pos_y, 0.5, 0.0, boss_gh[threeway], TRUE);
		}
		en_speedadj++;
		if (en_speedadj % 10 == 0) {
			en_speedadj = 0;
			if (en_gh_num < 3) {
				en_gh_num++;
			}
			else {
				en_gh_num = 0;
			}
		}
	}
	for (int i = 0; i < sizeof en_bullet / sizeof en_bullet[0]; i++) {
		if (en_bullet[i].bu_shotflag) {
			if (bossflag && en_appar_time < en_calltime) {
				DrawRotaGraph(en_bullet[i].bu_pos_x - en_bullet[i].bu_width / 2, en_bullet[i].bu_pos_y - en_bullet[i].bu_height / 2, 1.0, 0.0, en_bullet[i].bu_gh[en_bullet[i].bu_threeway], TRUE);
			}
			else {
				DrawRotaGraph(en_bullet[i].bu_pos_x - en_bullet[i].bu_width / 2, en_bullet[i].bu_pos_y - en_bullet[i].bu_height / 2, 0.1, 0.0, en_bullet[i].bu_gh[en_bullet[i].bu_threeway], TRUE);
			}
		}
	}

	if (ef_flag) {
		Draweffect();
	}
}

void enemy::getPosition(float* px, float* py) {
	*px = this->pos_x;
	*py = this->pos_y;
}

void enemy::setenemypool(int enemyN, int bulletNo, int movepattern,
	int bulletpattern, int appeartime, int stop, int shottime, int comeback,
	float x, float y, int bulletspeed, int HP, int item, int threeway,int bossflag) {
	this->en_No = enemyN;
	this->en_bulletNo = bulletNo;
	this->en_movepattern = movepattern;
	this->en_bulletpattern = bulletpattern;
	this->en_appar_time = appeartime;
	this->en_stop = stop;
	this->en_shottime = shottime;
	this->en_comeback = comeback;
	this->en_base_x = x;
	this->en_base_y = y;
	this->en_bulletspeed = bulletspeed;
	this->HP = HP;
	this->en_itemcode = item;
	this->threeway = threeway;
	this->bossflag = bossflag;
}

void enemy::setpos_x(float x) {
	pos_x = x;
}

bool enemy::getshotposition(int index, float* x, float* y) {
	if (en_bullet[index].bu_shotflag) {
		*x = en_bullet[index].bu_pos_x;
		*y = en_bullet[index].bu_pos_y;
		return true;
	}
	else {
		return false;
	}
}

void enemy::Shot() {
	if (en_callshot && en_speedadj % 12 == 0 && !deathflag) {
		for (int i = 0; i < sizeof en_bullet / sizeof en_bullet[0]; i++) {
			if (!en_bullet[i].bu_shotflag) {
				en_bullet[i].bu_shotflag = true;
				en_bullet[i].bu_threeway = threeway;
				en_bullet[i].bu_pos_x = pos_x;
				en_bullet[i].bu_pos_y = pos_y;
				en_callshot = false;
				break;
			}
		}
	}

	for (int i = 0; i < sizeof en_bullet / sizeof en_bullet[0]; i++) {
		if (en_bullet[i].bu_shotflag) {
			en_bullet[i].bu_pos_x -= en_bulletspeed;

			if (en_bullet[i].bu_pos_x < 0) {
				en_bullet[i].bu_shotflag = false;
				en_bullet[i].bu_pos_x = 0;
			}
		}
	}
}

void enemy::Default() {
	en_No = 0;
	en_bulletNo = 0;
	en_movepattern = 0;
	en_bulletpattern = 0;
	en_stop = 0;
	en_shottime = 0;
	en_comeback = 0;
	en_base_x = 1024;
	en_base_y = 0;
	en_bulletspeed = 0;
	pos_x = 1024;
	pos_y = 0;

	en_th = 0;

	en_speedadj = 0;

	en_shotwaittime = 0;
	threeway = 0;
	en_itemcode = 0;
	en_appar_time = 0;
	HP = 1;
	en_calltime = 0;
	en_callshot = false;
	en_finishshot = false;
	deathflag = true;
	en_gh_num = 0;
	for (int i = 0; i < sizeof en_bullet / sizeof en_bullet[0];i++) {
		en_bullet[i].Default();
	}
}

void enemy::typechangeDraw(int nextchg) {
	int nowthreeway = threeway;
	boss_typechgcount++;
	if (boss_typechgcount % boss_typechgcountpar == 0) {
		switch (boss_drawchgflag) {
		case true:
			DrawRotaGraph(pos_x, pos_y, 0.5, 0.0, boss_gh[nowthreeway], TRUE);
			break;
		case false:
			DrawRotaGraph(pos_x, pos_y, 0.5, 0.0, boss_gh[nextchg], TRUE);
			break;
		}
		boss_drawchgflag = !boss_drawchgflag;
	}
	if (boss_typechgcount >= 30) {
		boss_typechgcountpar = 2;
	}
	if (boss_typechgcount > 50) {
		boss_typechgflag = false;
		threeway = nextchg;
		boss_typechgcountpar = 5;
		boss_typechgcount = 0;
	}
}

void enemy::Draweffect() {
	if (ef_flag) {
		DrawRotaGraph(ef_x, ef_y, 0.7, 0.0, ef_gh[ef_cnt_det], TRUE);
		ef_cnt++;
		if (ef_cnt % 3 == 0) {
			ef_cnt_det++;
		}
	}
	if (ef_cnt_det >= 7) {
		ef_cnt = 0;
		ef_cnt_det = 0;
		ef_x = 0;
		ef_y = 0;
		ef_flag = false;
	}
}

void enemy::damagewait() {
	en_damagewaittime++;
	if (en_damagewaittime > 5) {
		en_damagewaittime = 0;
		nodamage = false;
	}
}

int enemy::get_appartime() {
	return en_appar_time;
}

int enemy::get_itemcode() {
	return en_itemcode;
}

bool enemy::get_bossflag() {
	return bossflag;
}

void enemy::set_calltime(int num) {
	en_calltime = num;
}

void enemy::set_callshot(bool flag) {
	en_callshot = flag;
}

void enemy::set_shotwaittime(int num) {
	en_shotwaittime = num;
}

void enemy::set_th(float num) {
	en_th = num;
}

void enemy::set_ef_x(float num) {
	ef_x = num;
}

void enemy::set_ef_y(float num) {
	ef_y = num;
}

void enemy::set_ef_flag(bool flag) {
	ef_flag = flag;
}

void enemy::set_movechg(bool flag) {
	en_movechg = flag;
}