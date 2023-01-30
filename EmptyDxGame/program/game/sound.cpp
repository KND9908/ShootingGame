#include "../dxlib_ext/dxlib_ext.h"
#include "sound.h"

void sound::Init() {
	if (!so_initflag) {
		so_bh[0] = LoadSoundMem("sound/bgm28.mp3");//メインタイトルBGM
		ChangeVolumeSoundMem(so_bh[0], 128);//音量調整
		so_bh[1] = LoadSoundMem("sound/bgm10.mp3");//ステージBGM
		ChangeVolumeSoundMem(so_bh[1], 128);//音量調整
		so_sh[0] = LoadSoundMem("sound/se12.mp3");//爆発
		ChangeVolumeSoundMem(so_sh[0], 128);//音量調整
		so_sh[1] = LoadSoundMem("sound/se07.mp3");//ダメージきいてない
		ChangeVolumeSoundMem(so_sh[1], 128);//音量調整
		so_sh[2] = LoadSoundMem("sound/se_imahitotu.ogg");//ダメージいまひとつ
		ChangeVolumeSoundMem(so_sh[2], 128);//音量調整
		so_sh[3] = LoadSoundMem("sound/se_normal.ogg");//ダメージ普通
		ChangeVolumeSoundMem(so_sh[3], 128);//音量調整
		so_sh[4] = LoadSoundMem("sound/se_batugun.ogg");//ダメージきいてる
		ChangeVolumeSoundMem(so_sh[4], 128);//音量調整
		so_initflag = true;
	}
}

void sound::PlayBGM(int i) {
	//BGMがなっていなければ再生する
	if (!so_bgmflag) {
		so_playnow = PlaySoundMem(so_bh[i], DX_PLAYTYPE_LOOP, true);
		so_bgmflag = true;
	}
}

void sound::StopBGM(int i) {
	if (CheckSoundMem(so_bh[i])) {
		StopSoundMem(so_bh[i]);
		so_bgmflag = false;
	}
}

void sound::PlaySE(int i) {
//	for (int s = 0; s < sizeof se / sizeof se[0]; s++) {
//		if (!se[s].s_flag) {
		PlaySoundMem(so_sh[i], DX_PLAYTYPE_BACK,true);
	//	}
//	}
}

void sound::ClearSE() {
	for (int i = 0; i < sizeof se / sizeof se[0]; i++)
	{
		if (!CheckSoundMem(se[i].s_player)) {
			se[i].s_flag = false;
		}
	}
}