#pragma once
#include "define.h";
#include"player.h";
#include"enemy.h";
#include"background.h";
#include"item.h";
#include"sound.h";
#include <string>

#define ENEMY_NUM 8
/// <summary>
/// �Q�[���̐i�s���Ǘ�����N���X
/// </summary>
class game_manager {
private:
	
	//---�Q�[���^�C�g���p---
	int Fadetimer = 0;

	//---�^�C�g���V�[���p---
	int uplength = 0;
	int titlegh = 0;
	int cleargh = 0;
	int visibleloop = 0;
	bool visibleswitch = true;

	int restartwait = 0;//player������ł���̍ăX�^�[�gWait�^�C�}�[

	//---�Q�[�����C���p---
	//�e�N���X�̃C���X�^���X���`
	player* PLY;
	enemy* EN[ENEMY_NUM];//1��ʂɂ�����G�̍ő�`�搔
	item* IT[ENEMY_NUM];//�A�C�e���̍ő��ʕ`�搔�i�G�̐��ȏ�͏o�Ȃ��j
	background* BK;
	sound* SO;

	ENEMYDATA enemybuf[40] = { 0 };//��ʂɕ`�悵����Ȃ��G�f�[�^�̃��[�h���ʂ͂����Ɋi�[
	int totalenemycnt = 0; //1�X�e�[�W�ɏo�Ă��鑍�G��
	int nowscene = LOGO;	//�V�[���Ǘ��p
	bool init = false;//����������p�t���O
	int stg_num = 1; //�X�e�[�W�J�E���g�@�����l1
	int stg_move = 0;//�X�e�[�W�̈ړ�����_x(�J�����T�O�I��)
	int poolcnt = 0; //�f�[�^�Ċi�[�����̃J�E���g
	
public:
	int movetotal = 0; //�Q�[���J�n����̌o�ߎ��ԁi�w�i�ړ���G�̕`��^�C�~���O�Ɏg�p�j
	game_manager();
	~game_manager();

	bool clearflag = false;

	void scenemanager();//�V�[���̃g�[�^�����Ǘ�����N���X

	void sceneLOGO();//���S�̃V�[��

	void sceneTITLE();//�^�C�g���V�[��

	void sceneREADY();//���f�B���

	void sceneMAIN();//���C�����

	void sceneGAMEOVER();//�Q�[���I�[�o�[���

	void sceneGAMECLEAR();//�Q�[���N���A���

	void DEBUG_VIEW();//�f�o�b�O�N�����ɁA�����f�[�^��\�����邽�߂̊֐�

	void plydeathmove();//�v���C���[������Ă���̉�ʑJ�ڃR���g���[��

	void Init();	  //�C�j�V�����C�Y�����i�摜���[�h�Ƃ��j

	void Default();	  //�l�������l�֖߂�����

	void viewupdate();//�Q�[����ʂ̗v�f�̃A�b�v�f�[�g��S��

	void CollisionAll();//	�����蔻��̊Ď����s��

	void enemypool();//�󂫂��ł��Ă���enemy�N���X�Ƀf�[�^���Ċi�[����
					  
	//�����蔻�蔻�ʃt���O
	bool CircleCollision(double c1, double c2, double cx1, double cx2, double cy1, double cy2);
	
	int checkthreeway(int a, int b);//���񂷂��ݔ�r�p
	
	//set
	void set_stg_num(int num);
	void set_stg_move(int num);

	//get
	int get_stg_num();
	int get_stg_move();
	int get_nowscene();
};