#pragma once
#include "creaturebase.h"
#include "bullet.h"
#define LoadCSVData 15
/// <summary>
/// �G�̃f�[�^���Ǘ�����N���X
/// </summary>
class enemy:public creaturebase {
public:
	//�|���ꂽ�G�l�~�[�̗̈���ė��p�\�ɂ��邽�߂̏���
	void setenemypool(int enemyNo, int bulletNo, int movepattern,
		int bulletpattern, int appeartime, int stop, int shottime, int comeback,
		float x, float y, int bulletspeed, int HP, int item,int threeway,int bossflag);
	void Update();
	void Init();
	void Default();

	bool getshotposition(int index, float* x, float* y);
	void setpos_x(float x);

	void getPosition(float* px, float* py);

	void Draweffect();//�G�t�F�N�g�����s����֐�
	
	void damagewait();
	//get
	int get_appartime();
	int get_itemcode();
	bool get_bossflag();

	//set
	void set_callshot(bool flag);

	void set_shotwaittime(int num);

	void set_th(float num);
	
	void set_calltime(int num);

	void set_ef_x(float num);

	void set_ef_y(float num);

	void set_ef_flag(bool flag);

	void set_movechg(bool flag);
protected:
	int en_No = 0;
	int en_bulletNo = 0;
	int en_movepattern = 0;
	int en_bulletpattern = 0;
	int en_stop = 0;
	int en_shottime = 0;
	int en_comeback = 0;
	float en_base_x = 1024;
	float en_base_y = 0;
	int en_bulletspeed = 0;

	int en_shotwaittime = 0;
	int en_calltime = 0;
	bool en_callshot = false; //�e�̔��˃g���K�[
	bool en_finishshot = false;//�e�̔��ˊ���������

	bool en_movechg = false;
	int en_itemcode = 0;
	int en_appar_time = 0;

	//�{�X�Ƃ��ĊǗ�����G�̏ꍇON�ɂ���
	bool bossflag = false;

	//�_���[�W���󂯂��Ƃ��ɍēx�_���[�W���󂯂�܂ł̖��G���Ԃ��Ǘ�����N���X
	int en_damagewaittime = 0;
	//�~�^���p�̈���
	float en_th = 0;

	//�G�̓����̐���ɗp����֐�
	int en_movecnt = 0;
	int en_movecnt_b = 0;

	int en_gh[6] = { 0 };//0:��G 1~2:�n�T�~�G 3~5:���G

	int bossdrawcnt = 0;
	int boss_gh[4] = { 0 };//0:�f�t�H���g1:�O�[����2:�`���L3:�p�[
	int boss_sh_gh[3] = { 0 };//�{�X�̃o���A�O���t�B�b�N

	int en_gh_num = 0; //�O���t�B�b�N�n���h���̏��ԑI��
	int en_speedadj = 0;//�A�j���[�V�����̃X�s�[�h�����p

	bullet en_bullet[20];//��x�ɏo����e��2�܂Łi�G���̏ꍇ)

	//�����G�t�F�N�g�𔭐�������ʒu
	int ef_x = 0;
	int ef_y = 0;
	bool ef_flag = false; //�����G�t�F�N�g�p�t���O

	int ef_gh[7] = { 0 };//�����G�t�F�N�g
	int ef_cnt = 0;//�G�t�F�N�g�A�j���[�V���������^�C�}�[
	int ef_cnt_det = 0;//���ׂ�������

	void Move();
	void Draw();
	void Shot();

	//�{�X�̓����֘A
	bool boss_typechgflag = false;
	bool boss_drawchgflag = false;
	int boss_typechgcount = 0;
	int boss_typechgcountpar = 5;
	int boss_nextchgtype = 0;
	int boss_chgrand = false;
	void typechangeDraw(int nextchg);
};
//CSV����ǂݎ�����G�̏��̊i�[�p�\����
struct ENEMYDATA {
	int enemyNo;
	int bulletNo;
	int movepattern; 
	int bulletpattern;
	int appartime;
	int stop;
	int shottime;
	int comeback;
	float x;
	float y;
	int bulletspeed;
	int HP;
	int item;
	int threeway;
	int bossflag;
};