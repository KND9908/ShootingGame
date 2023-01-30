#pragma once
/// <summary>
/// シーンの遷移にまつわる定義
/// </summary>
const int LOGO = 0;	//ロゴ画面（後ほどenumに修正する予定)
const int MAIN_TITLE = 1;	//タイトル画面
const int GAME_READY = 2;	//READY画面
const int GAME_MAIN = 3;	//ゲームスタート画面
const int GAME_OVER = 4;	//GAMEOVER
const int GAME_CLEAR = 5;	//ゲームクリア画面

const int Fadecnt = 5;	   //フェードイン/アウトの画面輝度待ち時間
const int LogoWait = 3000; //タイトルロゴ表示中処理待ち画面

const int WINDOW_X_SIZE = 1024;//ウィンドウのX座標の大きさ（sys_main.cppより)
const int WINDOW_Y_SIZE = 768;//ウィンドウのX座標の大きさ（sys_main.cppより)

const int DEBUG = 0;//デバッグ起動フラグ