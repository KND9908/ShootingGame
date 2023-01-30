#pragma once
#include"creaturebase.h"
#include "bullet.h"
/// <summary>
/// �v���C���[�̏������Ǘ�����N���X
/// </summary>
class player :public creaturebase {
public:
	player();
	//�v���C���[�̃|�W�V������X��Y�����ɓn��
	void getplyposition(float* x, float* y);
	//Player��HP����ʏ�ɕ`��
	void Drawlife();
	//�v���C���[�̌���������ʂɕ`��
	void Drawtype();
	//�v���C���[���_���[�W���󂯂����̖��G��Ԕ��菈��
	void damagewait();
	//
	void Draweffect();
	//
	void seteffect();

	virtual void Update();

	virtual void Init();

	//�v���C���[�̏�Ԃ��ꎮ������Ԃɂ��ǂ�����
	void Default();

	//get
	int get_pos_x();
	int get_pos_y();
	int get_life();
	int get_threeway();
	int getshotthreeway(int index);
	int getlifestock();
	bool get_deathflag();
	bool getshotposition(int index, float* x, float* y);

	//set
	void set_pos_x(float num);
	void set_pos_y(float num);
	void set_life(int num);
	void set_threeway(int num);
	void set_deathflag(bool flag);
	void set_lifestock(int lifestock);
protected:
	//�O���t�B�b�N�n���h��
	int pl_gh[3] = { 0 };//�v���C���[0:�O�[1:�`���L2:�p�[
	int pl_l_gh = 0; //���C�t�|�C���g
	//�e
	bool pl_gameoverflag = false;

	int pl_lifestock = 0;//�c�@
	int pl_allcount = 0;//�A�j���[�V�����̕`��̐؂�ւ��^�C�~���O�Ŏg�p����t���[���̃J�E���g
	int pl_ghn = 0;//�A�j���[�V�����̌��݂̐�
	int pl_invisitime = 0;//���G���Ԓ��̃J�E���g

	int pl_b_gh_g = 0;
	int pl_b_gh_c = 0;
	int pl_b_gh_p = 0;

	int ef_gh[7] = { 0 };//�G�t�F�N�g�̃O���t�B�b�N�n���h��
	//�G�t�F�N�g������������
	bool ef_flag = false;
	int ef_cnt = 0;
	int ef_cnt_det = 0;
	int ef_x = 0;
	int ef_y = 0;

	void Move();
	void Shot();
	void Draw();
	void chgthreeway();
	//�e��������
	bullet p_bullet[20];
};