#pragma once
/// <summary>
/// �v���C���[����ѓG�����˂���e���̊Ǘ�������N���X
/// </summary>
struct bullet {
	bool bu_shotflag = false; //�e�̎ˏo���؂̔���
	float bu_pos_x = 0;//�e��x���W
	float bu_pos_y = 0;//�e��y���W
	int bu_gh[4];//�e�̃O���t�B�b�N�n���h��
	int bu_width, bu_height;//�摜�̕��ƍ���

	int bu_threeway = 0;//�e��ł������̑���
	int bu_powerlevel = 0;//�e�̉Η�

	void Default();
};