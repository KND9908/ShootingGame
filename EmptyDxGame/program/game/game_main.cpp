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
bool shotflag = false;//�e�̔��˔���
int scene = LOGO;//�ŏ��̃V�[���̓��S��ʂ���
int uplength = 0;
int Fadetimer = 0;
int visibleloop = 0;
int xmove = 0;
int ymove = 0;
bool visibleswitch = true;

//�Q�[���̐i�s���Ǘ�����N���X
game_manager *GM = new game_manager;
void gameMain(float delta_time) {
	if (!init) {
		init = true;
	}
	if (DEBUG) {//�f�o�b�O���̂݁A�v�f����ʂɕ\��
		GM->DEBUG_VIEW();//	DrawStringEx(300, 300, -1, "Fadetimer:%d", Fadetimer);
	}
	GM->scenemanager();
}

