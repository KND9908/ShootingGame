#pragma once
/// <summary>
/// �A�C�e���̏������Ǘ�����N���X
/// </summary>
class item {
public:
	void Init();
	void Move();
	void Draw();
	void Delete();
	void SetFlag(float x, float y, int itemcode);
	void GetPosition(float* x, float* y);
	void viewupdate();
	void Default();

	bool GetFlag();
	int GetType();

private:
	int it_code = 0;
	int it_gh[2];
	float it_pos_x, it_pos_y;

	int it_ghcnt = 0;//�A�C�e���̃A�j���[�V��������p�̃J�E���g
	bool it_chggh = false;

	bool it_appearflag = false;
};