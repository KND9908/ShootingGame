#pragma once
/// <summary>
/// プレイヤーおよび敵が発射する弾道の管理をするクラス
/// </summary>
struct bullet {
	bool bu_shotflag = false; //弾の射出中華の判定
	float bu_pos_x = 0;//弾のx座標
	float bu_pos_y = 0;//弾のy座標
	int bu_gh[4];//弾のグラフィックハンドル
	int bu_width, bu_height;//画像の幅と高さ

	int bu_threeway = 0;//弾を打った時の属性
	int bu_powerlevel = 0;//弾の火力

	void Default();
};