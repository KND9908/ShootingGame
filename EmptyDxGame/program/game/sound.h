#pragma once
struct SE {
	int s_player;//SE再生中のハンドル
	bool s_flag = false;//SE再生中かのハンドルを投げるフラグ
};
/// <summary>
/// SE、BGMの管理を行うクラス
/// </summary>

class sound {
private:
	bool so_initflag = false;
	int so_bh[2];//BGMのハンドル
	int so_sh[5];//SEのハンドル

	int so_playnow;//BGM再生中のハンドル
	SE se[20];

	bool so_bgmflag = false;
public:
	void Init();
	void PlayBGM(int i);
	void StopBGM(int i);
	void PlaySE(int i);
	void ClearSE();//SEの再生状況をクリアする

};

