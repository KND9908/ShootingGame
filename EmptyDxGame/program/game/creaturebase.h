#pragma once
/// <summary>
/// プレイヤーや敵等のオブジェクトの基礎的なパラメータを保持するルーツのクラス
/// </summary>
class creaturebase {
public:
	float getpos_x() {
		return pos_x;
	}
	float getpos_y() {
		return pos_y;
	}
	int getHP() {
		return HP;
	}
	int getattackpoint() {
		return attackpoint;
	}
	int getthreeway() {
		return threeway;
	}
	bool getdeathflag() {
		return deathflag;
	}
	bool getnodamage() {
		return nodamage;
	}


	void setpos_x(float x) {
		pos_x = x;
	}
	void setpos_y(float y) {
		pos_y = y;
	}
	void setHP(int hp) {
		HP = hp;
	}
	void setattackpoint(int atkpoint) {
		attackpoint = atkpoint;
	}
	void settrheeway(int setway) {
		threeway = setway;
	}
	void setdeathflag(bool flag) {
		deathflag = flag;
	}
	void setnodamage(bool flag) {
		nodamage = flag;
	}
	//初期化処理
	virtual void Init() {

	}
	//各処理の更新用関数
	virtual void Update() {

	}
protected:
	float pos_x;
	float pos_y;

	int HP;
	//自身の属性
	int threeway = 0;
	//死亡フラグ
	bool deathflag = false;
	//無敵状態判定
	bool nodamage = false;
	//攻撃力
	int attackpoint = 1;
	//動き
	virtual void Move() {

	}
	//攻撃処理（弾発射）
	virtual void Shot() {

	}
	//描画処理
	virtual void Draw() {

	}
};