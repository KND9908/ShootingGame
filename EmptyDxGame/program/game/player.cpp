#include "../dxlib_ext/dxlib_ext.h"
#include"player.h"
#include"Image.h"

player::player() {
	
}

void player::Update() {
	Move();
	Shot();
	Draw();
	chgthreeway();
	pl_allcount++;
	if (pl_allcount >= 100) {
		pl_allcount = 0;
	}
	//DrawStringEx(200, 200, -1, "plytype:[%d]", threeway);
}

void player::Move() {
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) {
		if (pos_x>= 16) {
			pos_x = pos_x - 3;
		}
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) {
		if(pos_x <= 1024 - 16) {
			pos_x = pos_x + 3;
		}
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_UP)) {
		if (pos_y >= 24) {
			pos_y = pos_y - 3;
		}
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_DOWN)) {
		if (pos_y < 768 - 24) {
			pos_y = pos_y + 3;
		}
	}
}

void player::chgthreeway() {
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_C) ){
		threeway++;
		if (threeway > 2 ) {
			threeway = 0;
		}
	}
}

void player::Shot() {
	if (tnl::Input::IsKeyDown(eKeys::KB_Z) && pl_allcount % 12 == 0 && !deathflag) {
		for (int i = 0; i < 15; i++) {
			if (!p_bullet[i].bu_shotflag) {
				p_bullet[i].bu_shotflag = true;
				p_bullet[i].bu_threeway = threeway;
				p_bullet[i].bu_pos_x = pos_x;
				p_bullet[i].bu_pos_y = pos_y;
				break;
			}
		}
	}

	for (int i = 0; i < 20; i++) {
		if (p_bullet[i].bu_shotflag) {
			p_bullet[i].bu_pos_x += 7;

			if (p_bullet[i].bu_pos_x > 1100) {
				p_bullet[i].bu_shotflag = false;
				p_bullet[i].bu_pos_x = 0;
			}
		}
	}
}

void player::Init() {
		//ÉLÉÉÉâÉOÉâ
		pl_gh[0] = LoadGraph("graphics/player_g.png");
		pl_gh[1] = LoadGraph("graphics/player_c.png");
		pl_gh[2] = LoadGraph("graphics/player_p.png");
		pl_l_gh = LoadGraph("graphics/heart_gloss.png");

		LoadDivGraph("graphics/pipo-btleffect036.png", 7, 7, 1, 120, 120, ef_gh);
		//íeèâä˙âª
		pl_b_gh_g = LoadGraph("graphics/janken_gu.png");
		pl_b_gh_c = LoadGraph("graphics/janken_choki.png");
		pl_b_gh_p = LoadGraph("graphics/janken_pa.png");
		int w, h;
		GetGraphSize(pl_b_gh_g,&w,&h);
		for (int i = 0; i < 20; i++) {
			p_bullet[i].bu_shotflag = false;
			p_bullet[i].bu_gh[0] = pl_b_gh_g;
			p_bullet[i].bu_gh[1] = pl_b_gh_c;
			p_bullet[i].bu_gh[2] = pl_b_gh_p;
			p_bullet[i].bu_width = w;
			p_bullet[i].bu_height = h;
		}
		Default();
		pl_lifestock = 2;
}

void player::Draw() {

	if (!deathflag) {
		DrawRotaGraph(pos_x, pos_y, 0.5, 0.0, pl_gh[threeway], TRUE);

		if (pl_allcount % 10 == 0) {
			if (pl_ghn < 3) {
				pl_ghn++;
			}
			else {
				pl_ghn = 0;
			}
		}

		for (int i = 0; i < 20; i++) {
			if (p_bullet[i].bu_shotflag) {
				DrawRotaGraph(p_bullet[i].bu_pos_x - p_bullet[i].bu_width / 10 / 2, p_bullet[i].bu_pos_y 
					- p_bullet[i].bu_height / 10 / 2, 0.1, 0.0, p_bullet[i].bu_gh[p_bullet[i].bu_threeway], TRUE);
			}
		}
	}
	if (ef_flag) {
		Draweffect();
	}
}

void player::getplyposition(float *x, float *y) {
	*x = pos_x;
	*y = pos_y;
}

int player::getshotthreeway(int index) {
	return p_bullet[index].bu_threeway;
}

bool player::getshotposition(int index, float* x, float* y) {
	if (p_bullet[index].bu_shotflag) {
		*x = p_bullet[index].bu_pos_x;
		*y = p_bullet[index].bu_pos_y;
		return true;
	}
	else {
		return false;
	}
}

void player::Default() {
	pos_x = 300;
	pos_y = 300;
	pl_ghn = 0;
	pl_allcount = 0;
	if (pl_gameoverflag) {
		pl_lifestock = 2;
		pl_gameoverflag = false;
	}
	HP = 3;
	attackpoint = 1;
	threeway = 0;
	deathflag = false;

	for (int i = 0; i < sizeof p_bullet / sizeof p_bullet[0];i++) {
		p_bullet[i].Default();
	}
}

//get
int player::get_pos_x() {
	return pos_x;
}
int player::get_pos_y() {
	return pos_y;
}
int player::get_life() {
	return HP;
}
int player::get_threeway() {
	return threeway;
}
int player::getlifestock() {
	return pl_lifestock;
}
bool player::get_deathflag() {
	return deathflag;
}


//set
void player::set_pos_x(float num) {
	pos_x = num;
}
void player::set_pos_y(float num) {
	pos_y = num;
}
void player::set_life(int num) {
	HP = num;
}
void player::set_threeway(int num) {
	threeway = num;
}
void player::set_deathflag(bool flag) {
	deathflag = flag;
}
void player::set_lifestock(int lifestock) {
	this->pl_lifestock = lifestock;
}

void player::Drawlife() {
	switch (HP) {
	case 0:
		break;
	case 5:
		DrawRotaGraph(250, 50, 0.1, 0.0, pl_l_gh, TRUE);
	case 4:
		DrawRotaGraph(200, 50, 0.1, 0.0, pl_l_gh, TRUE);
	case 3:
		DrawRotaGraph(150, 50, 0.1, 0.0, pl_l_gh, TRUE);
	case 2:
		DrawRotaGraph(100, 50, 0.1, 0.0, pl_l_gh, TRUE);
	case 1:
		DrawRotaGraph(50, 50, 0.1, 0.0, pl_l_gh, TRUE);
		break;
	}

}

void player::Drawtype() {
	float g = 0.2;
	float c = 0.2;
	float p = 0.2;
	switch (threeway) {
	case 0:
		g = 0.4;
		break;
	case 1:
		c = 0.4;
		break;
	case 2:
		p = 0.4;
		break;
	}
	DrawRotaGraph(100, 700, g, 0.0, pl_b_gh_g, TRUE);
	DrawRotaGraph(200, 700, c, 0.0, pl_b_gh_c, TRUE);
	DrawRotaGraph(300, 700, p, 0.0, pl_b_gh_p, TRUE);
}

void player::damagewait() {
	pl_invisitime++;
	nodamage = true;
	if (pl_invisitime > 180) {
		pl_invisitime = 0;
		nodamage = false;
	}
}

void player::Draweffect() {
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

void player::seteffect() {
	ef_x = pos_x;
	ef_y = pos_y;
	ef_flag = true;
}