#pragma once
/// <summary>
/// �X�e�[�W�w�i�̃A�j���[�V�������Ǘ�����N���X
/// </summary>
class background {
private:
	int bk_pos_x = 0 ,bk_pos_y = 0;
	int bk_gh[4];//0:�w�i�摜 1:���@2:���@3�F����
	int bk_speedadj = 0;//�A�j���[�V�����̃X�s�[�h�����p

	//���ꂼ��̉摜�̍��v�̈ړ��ʒu
	int bk_move_deserttotal = 0;
	int bk_move_windtotal = 0;
	int bk_move_dusttotal = 0;

	//���ꂼ��̉摜�̈��̏������Ƃ̈ړ����x
	int bk_move_desert = 0;
	int bk_move_wind = 0;
	int bk_move_dust = 0;

public:
	void Update();
	void Init();
	void Draw();
	void Default();
	void ForeDraw();//��O�Ɉڂ��w�i�摜
};