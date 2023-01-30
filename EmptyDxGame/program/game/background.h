#pragma once
/// <summary>
/// ステージ背景のアニメーションを管理するクラス
/// </summary>
class background {
private:
	int bk_pos_x = 0 ,bk_pos_y = 0;
	int bk_gh[4];//0:背景画像 1:風　2:砂　3：砂埃
	int bk_speedadj = 0;//アニメーションのスピード調整用

	//それぞれの画像の合計の移動位置
	int bk_move_deserttotal = 0;
	int bk_move_windtotal = 0;
	int bk_move_dusttotal = 0;

	//それぞれの画像の一回の処理ごとの移動速度
	int bk_move_desert = 0;
	int bk_move_wind = 0;
	int bk_move_dust = 0;

public:
	void Update();
	void Init();
	void Draw();
	void Default();
	void ForeDraw();//手前に移す背景画像
};