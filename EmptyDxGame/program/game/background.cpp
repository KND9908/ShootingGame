#include "../dxlib_ext/dxlib_ext.h"
#include"background.h"

void background::Init() {
	bk_gh[0] = LoadGraph("graphics/backgrownd.png");
	bk_gh[1] = LoadGraph("graphics/kaze.png");
	bk_gh[2] = LoadGraph("graphics/desert.png");
	bk_gh[3] = LoadGraph("graphics/sunabokori.png");
}

void background:: Update() {
	Draw();
}

void background::Draw() {

	bk_speedadj++;
	if (bk_speedadj % 10 == 0) {
		bk_speedadj = 0;
		bk_pos_x++;
	}
	DrawRotaGraph(0 + 512, 768 / 2, 1.0, 0.0, bk_gh[0], TRUE);//TODO:”wŒi‰æ‘œ‚ð‚Æ‚¬‚ç‚¹‚È‚¢‚æ‚¤‚É‚ ‚é’ö“x‚µ‚½‚ç“¯‚¶‰æ‘œ‚ðÄ“x“Ç‚Ýž‚Þˆ—
	if (bk_pos_x >= 1024) {
		bk_pos_x = 0;
	}
}

void background::Default() {
	bk_pos_x = 0;
	bk_pos_y = 0;
	bk_speedadj = 0;
}

void background::ForeDraw() {
	//•—
	bk_move_wind = 16;
	bk_move_windtotal += bk_move_wind;
	if (bk_move_windtotal > 1024) {
		bk_move_windtotal = 0;
	}

	//»‚Ìˆ—
	bk_move_desert = 8;
	bk_move_deserttotal += bk_move_desert;
	if (bk_move_deserttotal > 1024) {
		bk_move_deserttotal = 0;
	}

	//»šº
	bk_move_dust = 16;
	bk_move_dusttotal += bk_move_dust;
	if (bk_move_dusttotal > 1024) {
		bk_move_dusttotal = 0;
	}
	DrawRotaGraph(166 - bk_move_windtotal, 100, 1.0, 0.0, bk_gh[1], TRUE);
	DrawRotaGraph(512 - bk_move_deserttotal, 702, 1.0, 0.0, bk_gh[2], TRUE);
	DrawRotaGraph(369 - bk_move_dusttotal, 702, 1.0, 0.0, bk_gh[3], TRUE);
	DrawRotaGraph(166 + 1024 - bk_move_windtotal, 100, 1.0, 0.0, bk_gh[1], TRUE);
	DrawRotaGraph(512 + 1024 - bk_move_deserttotal, 702, 1.0, 0.0, bk_gh[2], TRUE);
	DrawRotaGraph(369 + 1024 - bk_move_dusttotal, 702, 1.0, 0.0, bk_gh[3], TRUE);
}