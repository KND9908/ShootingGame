#pragma once
struct SE {
	int s_player;//SE�Đ����̃n���h��
	bool s_flag = false;//SE�Đ������̃n���h���𓊂���t���O
};
/// <summary>
/// SE�ABGM�̊Ǘ����s���N���X
/// </summary>

class sound {
private:
	bool so_initflag = false;
	int so_bh[2];//BGM�̃n���h��
	int so_sh[5];//SE�̃n���h��

	int so_playnow;//BGM�Đ����̃n���h��
	SE se[20];

	bool so_bgmflag = false;
public:
	void Init();
	void PlayBGM(int i);
	void StopBGM(int i);
	void PlaySE(int i);
	void ClearSE();//SE�̍Đ��󋵂��N���A����

};

