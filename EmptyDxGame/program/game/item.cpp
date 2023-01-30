#include "item.h"
#include "../dxlib_ext/dxlib_ext.h"]

void item::Init() {
	it_gh[0] = LoadGraph("graphics/item.png");
	it_gh[1] = LoadGraph("graphics/item2.png");
}
void item::Move() {
		it_pos_x--;
}

void item::Draw() {
	if (it_appearflag) {
		it_ghcnt++;
		if (it_ghcnt % 8 == 0) {
			it_chggh = !it_chggh;
			it_ghcnt = 0;
		}
		if (it_chggh) {
			DrawRotaGraph(it_pos_x, it_pos_y, 0.5, 0.0, it_gh[0], TRUE);
		}
		else {
			DrawRotaGraph(it_pos_x, it_pos_y, 0.5, 0.0, it_gh[1], TRUE);
		}
	}
}

void item::Delete() {
	it_pos_x = 0;
	it_pos_y = 0;
	it_appearflag = false;
}

void item::SetFlag(float x, float y,int itemcode) {
	this->it_pos_x = x;
	this->it_pos_y = y;
	this->it_code = itemcode;
	it_appearflag = true;
}

void item::GetPosition(float* x, float* y) {
	*x = this->it_pos_x;
	*y = this->it_pos_y;
}

void item::Default() {
	it_code = 0;
	it_pos_x = 0;
	it_pos_y = 0;
	it_appearflag = false;
}

void item::viewupdate() {
	Move();
	Draw();
}

bool item::GetFlag() {
	return it_appearflag;
}

int item::GetType() {
	return it_code;
}