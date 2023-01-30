#include <time.h>
#include <algorithm>
#include "game_main.h"
#include "define.h"
#include "game_manager.h"
#include "player.h"
#include "bullet.h"
#include "../dxlib_ext/dxlib_ext.h"

bool init = false;
bool callOneflag = false;
bool shotflag = false;//弾の発射判定
int scene = LOGO;//最初のシーンはロゴ画面から
int uplength = 0;
int Fadetimer = 0;
int visibleloop = 0;
int xmove = 0;
int ymove = 0;
bool visibleswitch = true;

//ゲームの進行を管理するクラス
game_manager *GM = new game_manager;
void gameMain(float delta_time) {
	if (!init) {
		init = true;
	}
	if (DEBUG) {//デバッグ時のみ、要素を画面に表示
		GM->DEBUG_VIEW();//	DrawStringEx(300, 300, -1, "Fadetimer:%d", Fadetimer);
	}
	GM->scenemanager();
}

