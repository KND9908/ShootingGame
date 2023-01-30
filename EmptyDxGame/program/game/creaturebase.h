#pragma once
/// <summary>
/// �v���C���[��G���̃I�u�W�F�N�g�̊�b�I�ȃp�����[�^��ێ����郋�[�c�̃N���X
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
	//����������
	virtual void Init() {

	}
	//�e�����̍X�V�p�֐�
	virtual void Update() {

	}
protected:
	float pos_x;
	float pos_y;

	int HP;
	//���g�̑���
	int threeway = 0;
	//���S�t���O
	bool deathflag = false;
	//���G��Ԕ���
	bool nodamage = false;
	//�U����
	int attackpoint = 1;
	//����
	virtual void Move() {

	}
	//�U�������i�e���ˁj
	virtual void Shot() {

	}
	//�`�揈��
	virtual void Draw() {

	}
};