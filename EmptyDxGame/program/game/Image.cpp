/// <summary>
/// ゲーム内で扱う画像を管理するクラス(シングルトンを想定）
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
	//各画像データのグラフィックハンドラ
	int gh_PM[3] = { 0 };//プレイヤーの属性　0:グー1:チョキ2:パー

	//シングルトン用のポインタ
	static Image* pImage;
	//ゲーム内で使用する画像データをコンストラクタで一括ロード
	Image();
};