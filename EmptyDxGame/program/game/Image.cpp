/// <summary>
/// �Q�[�����ň����摜���Ǘ�����N���X(�V���O���g����z��j
/// </summary>
class Image {
public:
	static Image* GetInstance() {
		return pImage;
	}
	static void Create() {
		if (!pImage) {
			pImage = new Image;
		}
	}
	static void Destroy() {
		delete pImage;
		pImage = nullptr;
	}

protected:
	//�e�摜�f�[�^�̃O���t�B�b�N�n���h��
	int gh_PM[3] = { 0 };//�v���C���[�̑����@0:�O�[1:�`���L2:�p�[

	//�V���O���g���p�̃|�C���^
	static Image* pImage;
	//�Q�[�����Ŏg�p����摜�f�[�^���R���X�g���N�^�ňꊇ���[�h
	Image();
};