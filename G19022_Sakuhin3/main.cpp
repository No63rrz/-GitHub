//今わかってるバグ
//
//まだ弾と敵はすり抜ける

//次やること
//敵の【描画】PLAY_DRAW
//敵と弾が【接触した瞬間】に敵を消す
//
//複数敵を作るのはやめてしょっぱなからラスボス！
//↓
//1体のデカい敵が自分で色を変えて身を守る
//敵はバウンドする

//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include "resource.h"

#define GAME_WIDTH			800	//画面の横の大きさ
#define GAME_HEIGHT			600	//画面の縦の大きさ
#define GAME_COLOR			32	//画面のカラービット

#define GAME_WINDOW_BAR		0	//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"ポプジカルシューティング"	//ウィンドウのタイトル

#define GAME_FPS 60 //FPSの数値

#define GAME_SOUND_VOLUME_PER 30	//%
#define GAME_SOUND_VOLUME 255 * GAME_SOUND_VOLUME_PER / 100		//↑のパーセントのボリューム

#define PLAY_TIME_SECOND 60		//秒
#define PLAY_TIME PLAY_TIME_SECOND*1000

//マウスのボタン
#define MOUSE_BUTTON_CODE 129 //0x0000～0x0080まで

//キーボードの種類
#define KEY_CODE_KIND 256 //256種類

//パスの長さ
#define PATH_MAX 255 //255文字まで
#define NAME_MAX 255 //255文字まで

//フォント
#define FONT_TANU_PATH TEXT(".\\FONT\\TanukiMagic.ttf")
#define FONT_TANU_NAME TEXT("たぬき油性マジック")
//フォントエラー
#define FONT_INSTALL_ERR_TITLE TEXT("フォントインストールエラー")
#define FONT_CREATE_ERR_TITLE TEXT("フォント作成エラー")

#define IMAGE_TITLE_ROGO_PATH TEXT(".\\IMAGE\\ROGO.png")

//背景
#define IMAGE_PLAY_BK_PATH1 TEXT(".\\IMAGE\\haikei1.png")
#define IMAGE_PLAY_BK_PATH2 TEXT(".\\IMAGE\\haikei2.png")
#define IMAGE_PLAY_BK_PATH3 TEXT(".\\IMAGE\\haikei3.png")
#define IMAGE_PLAY_BK_PATH4 TEXT(".\\IMAGE\\haikei4.png")

#define IMAGE_BACK_NUM 4

#define IMAGE_PLAYER_PATH TEXT(".\\IMAGE\\player.png")

#define IMAGE_LOAD_ERR_TITLE TEXT("画像読み込みエラー")

#define MUSIC_TITLE_BGM_PATH TEXT(".\\MUSIC\\loop_33.wav")
#define MUSIC_PLAY_BGM_PATH TEXT(".\\MUSIC\\fruitsparfait.mp3")
#define MUSIC_END_BGM_PATH TEXT(".\\MUSIC\\ほのぼのゲームオーバー.mp3")
#define MUSIC_CLEAR_BGM_PATH TEXT(".\\MUSIC\\ほのぼのゲームオーバー.mp3") //BGMは仮
#define MUSIC_PLAYER_SHOT_PATH TEXT(".\\MUSIC\\anime_flying.mp3")
#define MUSIC_LOAD_ERR_TITLE TEXT("音楽読み込みエラー")

//弾の設定
#define TAMA_CHANGE_MAX		 5	//5フレーム目で弾の画像を変える
#define TAMA_MAX			16	//最大16発まで

/*弾の画像は仮。自分でちゃんと描いてね*/
#define TAMA_RED_PATH			TEXT(".\\IMAGE\\TAMA\\tama_image_red.png")		//赤弾の画像
#define TAMA_GREEN_PATH			TEXT(".\\IMAGE\\TAMA\\tama_image_green.png")	//青弾の画像
#define TAMA_BLUE_PATH			TEXT(".\\IMAGE\\TAMA\\tama_image_blue.png")	//緑弾の画像
#define TAMA_YELLOW_PATH		TEXT(".\\IMAGE\\TAMA\\tama_image_yellow.png")	//黄弾の画像

#define TAMA_DIV_WIDTH		32	//画像を分割する幅サイズ
#define TAMA_DIV_HEIGHT		32	//画像を分割する高さサイズ

#define TAMA_DIV_TATE		3	//画像を縦に分割する数
#define TAMA_DIV_YOKO		1	//画像を横に分割する数

#define TAMA_DIV_NUM	TAMA_DIV_TATE * TAMA_DIV_YOKO	//画像を分割する総数

//敵マップ
//#define GAME_MAP_BK_PATH TEXT(".\\IMAGE\\ゲーム背景.png")
#define GAME_MAP_PATH TEXT(".\\IMAGE\\enemyMAP.png") 
#define GAME_MAP_TATE_MAX 9
#define GAME_MAP_YOKO_MAX 13
#define GAME_MAP_KIND_MAX 2

#define MAP_DIV_WIDTH 64
#define MAP_DIV_HEIGHT 64
#define MAP_DIV_TATE 10
#define MAP_DIV_YOKO 4

#define MAP_DIV_NUM MAP_DIV_TATE*MAP_DIV_YOKO

#define ENEMY_SPEED 2

#define START_ERR_TITLE		TEXT("スタート位置エラー")
#define START_ERR_CAPTION	TEXT("スタート位置が決まっていません")


//エンド画面画像
#define IMAGE_END_COMP_ROGO_PATH TEXT(".\\IMAGE\\clearROGO.png")
#define IMAGE_END_COMP_CNT 1
#define IMAGE_END_COMP_CNT_MAX 30

#define IMAGE_END_FAIL_ROGO_PATH TEXT(".\\IMAGE\\overROGO.png")
#define IMAGE_END_FAIL_CNT 1
#define IMAGE_END_FAIL_CNT_MAX 30
//閉じるボタンを押したとき
#define MSG_CLOSE_TITLE TEXT("終了メッセージ")
#define MSG_CLOSE_CAPTION TEXT("ゲームを終了しますか？")

enum GAME_MAP_KIND
{
	n = -1, //none
	s = 0, //スタート
	e = 1 //敵（仮）

};

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};

enum GAME_END {
	GAME_END_COMP,
	GAME_END_FAIL
};

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 3
};	//キャラクターのスピード

enum CHARA_RELOAD {
	CHARA_RELOAD_LOW = 60,
	CHARA_RELOAD_MIDI = 30,
	CHARA_RELOAD_HIGH = 15
};	//キャラクターのリロード

enum TAMA_COLOR {
	TAMA_COLOR_RED,
	TAMA_COLOR_GREEN,
	TAMA_COLOR_BLUE,
	TAMA_COLOR_YELLOW
};//弾の色

//int型のPOINT構造体
typedef struct STRUCT_I_POINT
{
	int x = -1;
	int y = -1;
}iPOINT;

//マウス構造体
typedef struct STRUCT_MOUSE
{
	int InputValue = 0;
	int WheelValue = 0;
	iPOINT Point;
	iPOINT OldPoint;
	int OldButton[MOUSE_BUTTON_CODE] = { 0 };
	int Button[MOUSE_BUTTON_CODE] = { 0 };
}MOUSE;

typedef struct STRUCT_FONT
{
	char path[PATH_MAX];
	char name[NAME_MAX];
	int handle;
	int size;
	int bold;
	int type;
}FONT;

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];
	int handle;
	int x;
	int y;
	int width;
	int height;

}IMAGE;

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];
	int handle;
}MUSIC;

typedef struct STRUCT_TAMA
{
	char path[PATH_MAX];
	int handle[TAMA_DIV_NUM];
	int x;
	int y;
	int width;
	int height;
	BOOL IsDraw;
	int nowImageKind; //弾の現在の画像
	int changeImageCnt;	//画像を変えるためのカウント
	int changeImageCntMAX; //画像を変えるためのカウント(MAX)
	int speed; //スピード

	RECT coll;
	iPOINT collBeforePt;
}TAMA;	//弾の構造体


typedef struct STRUCT_CHARA
{
	IMAGE image;
	int speed;
	int CenterX;				//中心X
	int CenterY;				//中心Y

	MUSIC musicShot;			//プレイヤーの発射音

	BOOL CanShot;				//ショットできるか
	int ShotReLoadCnt;			//ショットリロード時間
	int ShotReLoadCntMAX=10;		//ショットリロード時間(MAX)

	BOOL PlayerMISS;//プレイヤーが敵と当たったかどうか
	int PlayerReLoadCnt;//プレイヤーのリロード時間
	int PlayerReLoadCntMAX = 180;//プレイヤーのリロードにかかる時間（約3秒）

	TAMA tama[TAMA_MAX];

	RECT coll;
	iPOINT collBeforePt;

}CHARA;

typedef struct STRUCT_ENEMY
{
	IMAGE image;

	RECT rect;
	int YokoSpeed;
	int TateSpeed;
	BOOL IsDraw;

	int Damage = 0;//現在までに受けた弾の個数
	int DamageMAX = 100;//100発当てたら終わり
}ENEMY;

typedef struct STRUCT_IMAGE_BACK
{
	IMAGE image;
	BOOL IsDraw;
}IMAGE_BACK;

typedef struct STRUCT_IMAGE_BLINK
{
	IMAGE image;
	int Cnt;
	int CntMAX;
	BOOL IsDraw;
}IMAGE_BLINK;
typedef struct STRUCT_MAP_IMAGE
{
	char path[PATH_MAX];
	int handle[MAP_DIV_NUM];
	int kind[MAP_DIV_NUM];
	int width;
	int height;
}MAP_CHIP;

typedef struct STRUCT_MAP
{
	GAME_MAP_KIND kind;
	int x;
	int y;
	int width;
	int height;
}MAP;
//FPS関連
int StartTimeFps;
int CountFps;
float CalcFps;
int SampleNumFps = GAME_FPS;

//キーボード入力取得
char AllKeyState[KEY_CODE_KIND] = { '\0' };
char OldAllKeyState[KEY_CODE_KIND] = { '\0' };

//マウスの座標を取得
MOUSE mouse;

//ゲーム関連
int GameScene; //ゲームシーンを管理
int GameEndKind;

//プレイヤー関連
CHARA player; //ゲームのキャラ
//CHARA enemy;
ENEMY enemy;

int TamaColorKind;//弾の色管理

//画像関係
IMAGE ImageTitleROGO; //タイトルロゴ
IMAGE ImageTitleBack; //タイトル背景

IMAGE_BACK ImageBack[IMAGE_BACK_NUM]; //プレイ背景

IMAGE_BLINK ImageEndFAIL; //エンドロゴ
IMAGE_BLINK ImageEndCOMP; //エンドロゴ


//音楽関係
MUSIC TITLE;
MUSIC PLAY_BGM;
MUSIC END_FAIL_BGM;
MUSIC END_COMP_BGM;

//フォント
FONT FontTanu32;

GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]
{
	//　0,1,2,3,4,5,6,7,8,9,0,1,2,
		n,n,n,n,n,n,n,n,n,n,n,n,//0
		n,n,n,n,n,n,n,n,n,n,n,n,//1
		n,n,n,n,n,n,n,n,n,n,n,n,//2
		n,n,n,n,n,n,e,n,n,n,n,n,//3
		n,n,n,n,n,n,n,n,n,n,n,n,//4
		n,n,n,n,n,n,n,n,n,n,n,n,//5
		n,n,n,n,n,n,n,n,n,n,n,n,//6
		n,n,n,n,n,s,n,n,n,n,n,n,//7
		n,n,n,n,n,n,n,n,n,n,n,n//8
		//テスト用
};
GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
MAP_CHIP mapChip;
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
iPOINT startPt{ -1,-1 };
//IMAGE MapBack;
RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

int player_Life;
int StartTime;//プレイ開始時の現在時刻
int NowPlayTime;

//########## プロトタイプ宣言 ##########
VOID MY_FPS_UPDATE(VOID);
VOID MY_FPS_DRAW(VOID);
VOID MY_FPS_WAIT(VOID);

VOID MY_ALL_KEYDOWN_UPDATE(VOID);
BOOL MY_KEY_DOWN(int);
BOOL MY_KEY_UP(int);
BOOL MY_KEYDOWN_KEEP(int, int);

VOID MY_MOUSE_UPDATE(VOID);
BOOL MY_MOUSE_DOWN(int);
BOOL MY_MOUSE_UP(int);
BOOL MY_MOUSEDOWN_KEEP(int, int);

BOOL MY_FONT_INSTALL_ONCE(VOID);
VOID MY_FONT_UNINSTALL_ONCE(VOID);
BOOL MY_FONT_CREATE(VOID);
VOID MY_FONT_DERETE(VOID);

VOID MY_START(VOID);
VOID MY_START_PROC(VOID);
VOID MY_START_DRAW(VOID);

VOID MY_PLAY_INIT(VOID);
VOID MY_PLAY(VOID);
VOID MY_PLAY_PROC(VOID);
VOID MY_PLAY_DRAW(VOID);

VOID MY_END(VOID);
VOID MY_END_PROC(VOID);
VOID MY_END_DRAW(VOID);

BOOL MY_LOAD_IMAGE(VOID);
VOID MY_DELETE_IMAGE(VOID);

BOOL MY_LOAD_MUSIC(VOID);
VOID MY_DELETE_MUSIC(VOID);

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player);
BOOL MY_CHECK_RECT_COLL(RECT a, RECT b);
//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				//log.txtを出力しない
	ChangeWindowMode(TRUE);								//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//指定の数値でウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR);				//タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE);								//非アクティブでも実行する
	SetWindowIconID(IDI_ICON1);
	SetWindowUserCloseEnableFlag(FALSE);


	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	//画像を読み込む
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }
	//音楽を読み込む
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }


	//フォントを一時的にインストール
	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }
	//フォントハンドルを作成
	if (MY_FONT_CREATE() == FALSE) { return -1; }

	//動画の読み込み
	//handle = LoadGraph(MOVIE_PATH);

	GameScene = GAME_SCENE_START; //ゲームシーンはスタート画面から
	SetDrawScreen(DX_SCREEN_BACK); //Draw系関数は裏画面に描画
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			if (mapData[tate][yoko] == s)
			{
				startPt.x = mapChip.width * yoko + mapChip.width / 2;
				startPt.y = mapChip.height * tate + mapChip.height / 2;
			}

			//if (mapData[tate][yoko] == e)
			//{
			//	enemy.CenterX= mapChip.width * yoko + mapChip.width / 2;
			//	enemy.CenterY = mapChip.height * tate + mapChip.height / 2;
			//	
			//	enemy.coll.left = mapChip.width * yoko;
			//	enemy.coll.top = mapChip.height * tate;
			//	enemy.coll.right = mapChip.width * (yoko + 1);
			//	enemy.coll.bottom = mapChip.height * (tate + 1);

			//	/*ここで敵の情報いれる*/
			//}
			//if (mapData[tate][yoko] == g)
			//{
			//	GoalRect.left = mapChip.width * yoko;
			//	GoalRect.top = mapChip.height * tate;
			//	GoalRect.right = mapChip.width * (yoko + 1);
			//	GoalRect.bottom = mapChip.height * (tate + 1);

			//}
		}
	}

	if (startPt.x == -1 && startPt.y == -1)
	{
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);
	}
	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了
		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		//画面の閉じるボタンを押された時
		if (GetWindowUserCloseFlag(TRUE))
		{
			SetMouseDispFlag(TRUE);
			//終了ダイアログを表示
			int Ret = MessageBox(GetMainWindowHandle(), MSG_CLOSE_CAPTION, MSG_CLOSE_TITLE, MB_YESNO | MB_ICONASTERISK);
			if (Ret == IDYES) { break; } //YESならゲーム終了
		}
		MY_ALL_KEYDOWN_UPDATE(); //押しているキー状態を取得

		MY_MOUSE_UPDATE(); //マウスの状態を取得

		MY_FPS_UPDATE(); //fpsの処理（更新）

		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();
			break;
		case GAME_SCENE_END:
			MY_END();
			break;
		}

		MY_FPS_DRAW();

		ScreenFlip();

		MY_FPS_WAIT();
	}
	MY_FONT_DERETE();
	MY_FONT_UNINSTALL_ONCE();
	MY_DELETE_IMAGE();
	MY_DELETE_MUSIC();

	DxLib_End();	//ＤＸライブラリ使用の終了処理

	//DeleteGraph(handle);	//動画の削除

	return 0;
}
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0)
	{
		StartTimeFps = GetNowCount();
	}
	if (CountFps == SampleNumFps)
	{
		int now = GetNowCount();
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

VOID MY_FPS_DRAW(VOID)
{
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}

VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;

	if (waitTime > 0)
	{
		WaitTimer(waitTime);
	}
	return;
}

VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	char TempKey[KEY_CODE_KIND];

	for (int i = 0; i < KEY_CODE_KIND; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey);
	for (int i = 0; i < KEY_CODE_KIND; i++)
	{
		if (TempKey[i] != 0)
		{
			AllKeyState[i]++;
		}
		else {
			AllKeyState[i] = 0;
		}
	}
	return;
}

BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1
		&& AllKeyState[KEY_INPUT_] == 0)
	{
		return TRUE;
	}
	else {
		return FALSE;
	}

}

BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{
	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;
	}
	else {
		return FALSE;
	}
}

VOID MY_MOUSE_UPDATE(VOID)
{
	mouse.OldPoint = mouse.Point;

	for (int i = 0; i < MOUSE_BUTTON_CODE; i++) { mouse.OldButton[i] = mouse.Button[i]; }

	GetMousePoint(&mouse.Point.x, &mouse.Point.y);

	mouse.InputValue = GetMouseInput();

	if ((mouse.InputValue & MOUSE_INPUT_LEFT) == MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT]++; }
	if ((mouse.InputValue & MOUSE_INPUT_LEFT) != MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT] = 0; }

	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) == MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE]++; }
	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) != MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE] = 0; }

	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) == MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT]++; }
	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) != MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT] = 0; }

	mouse.WheelValue = GetMouseWheelRotVol();

	return;
}

BOOL MY_MOUSE_DOWN(int MOUSE_INPUT_)
{
	if (mouse.Button[MOUSE_INPUT_] != 0)
	{
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BOOL MY_MOUSE_UP(int MOUSE_INPUT_)
{
	if (mouse.OldButton[MOUSE_INPUT_] >= 1 &&
		mouse.Button[MOUSE_INPUT_] == 0)
	{
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BOOL MY_MOUSEDOWN_KEEP(int MOUSE_INPUT_, int DownTime)
{
	int UpdateTime = DownTime * GAME_FPS;

	if (mouse.Button[MOUSE_INPUT_] > UpdateTime)
	{
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BOOL MY_FONT_INSTALL_ONCE(VOID)
{
	if (AddFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL) == 0)
	{
		MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}
	return TRUE;
}

VOID MY_FONT_UNINSTALL_ONCE(VOID)
{
	RemoveFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL);
	return;
}

BOOL MY_FONT_CREATE(VOID)
{
	strcpy_s(FontTanu32.path, sizeof(FontTanu32.path), FONT_TANU_PATH);
	strcpy_s(FontTanu32.name, sizeof(FontTanu32.name), FONT_TANU_NAME);
	FontTanu32.handle = -1;
	FontTanu32.size = 32;
	FontTanu32.bold = 1;
	FontTanu32.type = DX_FONTTYPE_ANTIALIASING_EDGE;

	FontTanu32.handle = CreateFontToHandle(FontTanu32.name, FontTanu32.size, FontTanu32.bold, FontTanu32.type);
	if (FontTanu32.handle == 1)
	{
		MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_CREATE_ERR_TITLE, MB_OK);
		return FALSE;

	}
	return TRUE;

}

VOID MY_FONT_DERETE(VOID)
{
	DeleteFontToHandle(FontTanu32.handle);
	return;
}

VOID MY_START(VOID)
{
	MY_START_PROC();
	MY_START_DRAW();

	return;
}

VOID MY_START_PROC(VOID)
{
	//BGMが流れていないなら
	if (CheckSoundMem(TITLE.handle) == 0)
	{
		ChangeVolumeSoundMem(GAME_SOUND_VOLUME, TITLE.handle); //50%の音量
		PlaySoundMem(TITLE.handle, DX_PLAYTYPE_LOOP); //ループ再生
	}
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		//BGMが流れていたら
		if (CheckSoundMem(TITLE.handle) != 0)
		{
			StopSoundMem(TITLE.handle); //止める
		}
		//キーボード用↓
		//プレイヤーの中心位置を計算する
		//player.CenterX = startPt.x;
		//player.CenterY = startPt.y;

		////プレイヤーの画像の位置を設定する
		//player.image.x = player.CenterX;
		//player.image.y = player.CenterY;

		////プレイヤーの当たる以前の位置を設定する
		//player.collBeforePt.x = player.CenterX;
		//player.collBeforePt.y = player.CenterY;
		/*ここまで*/

		//マウス用↓
		SetMouseDispFlag(FALSE);

		player.CenterX = startPt.x;
		player.CenterY = startPt.y;

		player.image.x = player.CenterX;
		player.image.y = player.CenterY;

		player.collBeforePt.x = player.CenterX;
		player.collBeforePt.y = player.CenterY;

		SetMousePoint(player.image.x, player.image.y);

		/*ここまで*/
		StartTime = GetNowCount(); //現在の経過時間を取得
		player_Life = 3; //プレイヤーのライフを設定
		player.PlayerMISS = FALSE;//プレイヤーと敵はまだ当たってないからFALSE
		for (int cnt = 0; cnt < TAMA_MAX; cnt++)
		{
			player.tama[cnt].IsDraw = FALSE;
		}
		GameEndKind = GAME_END_FAIL;
		TamaColorKind = TAMA_COLOR_RED;//初期は赤

		enemy.rect.left = GAME_WIDTH / 2 - enemy.image.width / 2;		//ボールのX位置は画面の中央
		enemy.rect.top = GAME_HEIGHT / 2 - enemy.image.height / 2;		//ボールのY位置は画面の中央
		enemy.rect.right = enemy.rect.left + enemy.image.width;				//ボールの幅を初期化
		enemy.rect.bottom = enemy.rect.top + enemy.image.height;				//ボールの高さを初期化

		enemy.TateSpeed = ENEMY_SPEED;				//縦の速さを初期化
		enemy.YokoSpeed = ENEMY_SPEED;				//横の速さを初期化
		enemy.IsDraw = FALSE;							//ボールを表示しない

		//MY_PLAY_INIT(); //ゲーム初期化

		GameScene = GAME_SCENE_PLAY; //プレイ画面に遷移

		return;
	}
	return;
}

VOID MY_START_DRAW(VOID)
{
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT/2, GetColor(0, 255, 255), TRUE);
	DrawBox(0, GAME_HEIGHT/2, GAME_WIDTH, GAME_HEIGHT, GetColor(255, 0, 255), TRUE);

	DrawString(0, 0, "スタート画面（エンターキーを押してください）", GetColor(255, 255, 255));
	DrawGraph(ImageTitleROGO.x, ImageTitleROGO.y, ImageTitleROGO.handle, TRUE);
	
	DrawStringToHandle(GAME_WIDTH/4, GAME_HEIGHT/2+50, "エンターキーをおしてね！", GetColor(255, 255, 255), FontTanu32.handle);

	return;
}

VOID MY_PLAY_INIT(VOID)
{
	//player_Life = 3; //プレイヤーのライフを設定

	//for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	//{
	//	player.tama[cnt].IsDraw = FALSE;
	//}
	//player.CanShot = TRUE;
	//GameEndKind = GAME_END_FAIL;
	return;
}

VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();
	MY_PLAY_DRAW();
	DrawString(0, 0, "プレイ画面(escでエンド画面)", GetColor(255, 255, 255));

	return;
}

VOID MY_PLAY_PROC(VOID)
{
	//BGMが流れていないなら
	if (CheckSoundMem(PLAY_BGM.handle) == 0)
	{
		ChangeVolumeSoundMem(GAME_SOUND_VOLUME, PLAY_BGM.handle); //50%の音量
		PlaySoundMem(PLAY_BGM.handle, DX_PLAYTYPE_LOOP); //ループ再生
	}
	if (MY_KEY_UP(KEY_INPUT_ESCAPE) == TRUE)
	{
		if (CheckSoundMem(PLAY_BGM.handle) != 0)
		{
			StopSoundMem(PLAY_BGM.handle);
		}
		GameScene = GAME_SCENE_END; //プレイ画面に遷移

		return;
	}


	//マウス操作
	if (mouse.Point.x >= 0 && mouse.Point.x <= GAME_WIDTH &&
		mouse.Point.y >= 0 && mouse.Point.y <= GAME_HEIGHT)
	{
		//player.CenterX = mouse.Point.x;
		//player.CenterY = mouse.Point.y;

		int MoveValue = 100;

		if (abs(player.collBeforePt.x - mouse.Point.x) < MoveValue &&
			abs(player.collBeforePt.y - mouse.Point.y) < MoveValue)
		{
			player.CenterX = mouse.Point.x;
			player.CenterY = mouse.Point.y;
		}
		else
		{
			player.CenterX = player.collBeforePt.x;
			player.CenterY = player.collBeforePt.y;
			SetMousePoint(player.collBeforePt.x, player.collBeforePt.y);
		}
	}

	//当たり判定
	player.coll.left = player.CenterX - mapChip.width / 2 + 5;
	player.coll.top = player.CenterY - mapChip.height / 2 + 5;
	player.coll.right = player.CenterX + mapChip.width / 2 - 5;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;

	BOOL IsMove = TRUE;

	if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	{
		player.CenterX = player.collBeforePt.x;
		player.CenterY = player.collBeforePt.y;
		SetMousePoint(player.collBeforePt.x, player.collBeforePt.y);

		IsMove = FALSE;
	}
	if (IsMove == TRUE)
	{
		if (mouse.Point.x >= 0 && mouse.Point.x <= GAME_WIDTH
			&& mouse.Point.y >= 0 && mouse.Point.y <= GAME_HEIGHT)
		{
			player.image.x = player.CenterX - player.image.width / 2;
			player.image.y = player.CenterY - player.image.height / 2;

			player.collBeforePt.x = player.CenterX;
			player.collBeforePt.y = player.CenterY;

		}

	}

	RECT PlayerRect;
	PlayerRect.left = player.image.x + 40;
	PlayerRect.top = player.image.y + 40;
	PlayerRect.right = player.image.x + player.image.width - 40;
	PlayerRect.bottom = player.image.y + player.image.height - 40;
	
	//RECT EnemyRect;
	//EnemyRect.left = enemy.image.x + 40;
	//EnemyRect.top = enemy.image.y + 40;
	//EnemyRect.right = enemy.image.x + player.image.width - 40;
	//EnemyRect.bottom = enemy.image.y + player.image.height - 40;

	RECT TamaRect[TAMA_MAX];//弾出すときに値を入れる

	if (enemy.image.x > GAME_WIDTH || enemy.image.y > GAME_HEIGHT ||
		enemy.image.x + enemy.image.width < 0 || enemy.image.y + enemy.image.height < 0) //敵が画面外に出たらエンド
	{
		if (CheckSoundMem(PLAY_BGM.handle) != 0)
		{
			StopSoundMem(PLAY_BGM.handle);
		}
		SetMouseDispFlag(TRUE);
		GameEndKind = GAME_END_FAIL;
		GameScene = GAME_SCENE_END;
		return;
	}

	//ショット
	if (MY_MOUSE_DOWN(MOUSE_INPUT_LEFT) == TRUE)
	{
		//ショットが撃てるとき
		if (player.CanShot == TRUE)
		{
		
			PlaySoundMem(player.musicShot.handle, DX_PLAYTYPE_BACK);
			player.CanShot = FALSE;

			//空いているスロットで、弾の描画をする
			for (int cnt = 0; cnt < TAMA_MAX; cnt++)
			{
				if (player.tama[cnt].IsDraw == FALSE)
				{
					//縦向き
					player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;
					player.tama[cnt].y = player.image.y;

					//* 横シューティング（プレイヤー右）の場合 *//
					//player.tama[cnt].x = player.image.x;
					//player.tama[cnt].y = player.image.y + 40 - player.tama[cnt].height / 2;


					//弾当たり判定
					
					TamaRect[cnt].left = player.tama[cnt].x + 40;
					TamaRect[cnt].top = player.tama[cnt].y + 40;
					TamaRect[cnt].right = player.tama[cnt].x + player.tama[cnt].width - 40;
					TamaRect[cnt].bottom = player.tama[cnt].y + player.tama[cnt].height - 40;
					//DrawBox(TamaRect[cnt].left, TamaRect[cnt].top, TamaRect[cnt].right, TamaRect[cnt].bottom, GetColor(255, 0, 255), TRUE);

					//色指定
					//nowImageKind = TAMA_COLOR;

					//弾を描画する
					player.tama[cnt].IsDraw = TRUE;

					break;
				}
			}
		}
	}

	//ショットが撃てないとき
	if (player.CanShot == FALSE)
	{
		//リロード時間が終わったとき
		if (player.ShotReLoadCnt == player.ShotReLoadCntMAX)
		{
			player.ShotReLoadCnt = 0;
			player.CanShot = TRUE;		//再びショットできる
		}

		player.ShotReLoadCnt++;	//リロードする
	}

	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{


		/* 縦スクロールSTGの背景の流れ方 */

		ImageBack[num].image.y++;

		if (ImageBack[num].IsDraw == FALSE)
		{
			if (ImageBack[num].image.y + ImageBack[num].image.height > 0)
			{
				ImageBack[num].IsDraw = TRUE;
			}
		}

		if (ImageBack[num].image.y > GAME_HEIGHT)
		{
			ImageBack[num].image.y = 0 - ImageBack[0].image.height * 3;
			ImageBack[num].IsDraw = FALSE;
		}

	}

	//敵の動き
	//if (enemy.IsDraw == FALSE)	//ボールが非表示のとき
	//{
	//	if (KeyDownState[VK_RETURN] == TRUE)	//エンターキーを押したら(所定の位置に着いたら開始でもいいね)
	//	{
	//		enemy.IsDraw = TRUE;	//ボール表示
	//	}
	//}

	if (enemy.IsDraw == TRUE)
	{
		/*◎当たり判定のポイント
		　・移動する場所を先回りして、当たっているかチェックすること！
		 　→当たっているのに、スピードが早すぎると「貫通」してしまうことも
	　	   →プログラム中で、ボールの位置に、ボールのスピードを加減しているのが、先回りの処理
		*/

		//ボールが画面外にめり込んだ場合(左)
		if (enemy.rect.left - enemy.YokoSpeed < 0)
		{
			enemy.rect.left = 0 + 1;
			enemy.rect.right = enemy.rect.left + enemy.image.width + 1;

			enemy.YokoSpeed = -enemy.YokoSpeed;	//向きを反転させる
		}

		//ボールが画面外にめり込んだ場合(右)
		if (enemy.rect.right + enemy.YokoSpeed > GAME_WIDTH)
		{
			enemy.rect.left = GAME_WIDTH - enemy.image.width - 1;
			enemy.rect.right = enemy.rect.left + enemy.image.width - 1;

			enemy.YokoSpeed = -enemy.YokoSpeed;	//向きを反転させる
		}

		//ボールが画面外にめり込んだ場合(上)
		if (enemy.rect.top - enemy.TateSpeed < 0)
		{
			enemy.rect.top = 0 + 1;
			enemy.rect.bottom = enemy.rect.top + enemy.image.height;

			enemy.TateSpeed = -enemy.TateSpeed;	//向きを反転させる
		}

		//ボールが画面外にめり込んだ場合(下)
		if (enemy.rect.bottom + enemy.TateSpeed > GAME_HEIGHT)
		{
			enemy.rect.top = GAME_HEIGHT - enemy.image.height - 1;
			enemy.rect.bottom = enemy.rect.top + enemy.image.height - 1;

			enemy.TateSpeed = -enemy.TateSpeed;	//向きを反転させる
		}


		//画面の右下のY位置が、画面の右下のY位置よりも大きいとき(敵とプレイヤーが当たったら即死)
		if (MY_CHECK_RECT_COLL(enemy.rect,PlayerRect))
		{
				if (CheckSoundMem(PLAY_BGM.handle) != 0)
				{
					StopSoundMem(PLAY_BGM.handle);
				}
				GameEndKind = GAME_END_COMP;
				GameScene = GAME_SCENE_END;
		}
		enemy.rect.left += enemy.YokoSpeed;	//ボールの左上のX位置を移動
		enemy.rect.right += enemy.YokoSpeed;	//ボールの右下のX位置を移動

		enemy.rect.top += enemy.TateSpeed;	//ボールの左上のY位置を移動
		enemy.rect.bottom += enemy.TateSpeed;	//ボールの右下のY位置を移動

	}


	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		if (player.tama[cnt].IsDraw == TRUE)//弾があるときだけ判定する
		{
			if(player.tama[cnt].x<enemy.image.x+ enemy.image.width &&
				player.tama[cnt].y<enemy.image.y+ enemy.image.height &&
				player.tama[cnt].x+ player.tama[cnt].width>enemy.image.x &&
				player.tama[cnt].y+ player.tama[cnt].height>enemy.image.y)/*弾x*/
			{
				DrawBox(enemy.image.x, enemy.image.y, enemy.image.x + 10, enemy.image.y + 10, GetColor(0, 0, 255), FALSE);
				//そもそもこれで当たり判定動くか
			}
		}

	}


	//if (MY_CHECK_RECT_COLL(TamaRect, EnemyRect) == TRUE)
	//{
	//	if (map[tate][yoko].kind == e)
	//		map[tate][yoko].kind = n;//敵消したかった
	//}

	//if (MY_CHECK_RECT_COLL(PlayerRect, EnemyRect) == TRUE)
	//{

	//	if(player.PlayerMISS == FALSE)
	//	{
	//		//ダメージSE
	//		--player_Life;
	//		player.PlayerMISS = TRUE;
	//		//リスポーン処理欲しい
	//	}//直前に当たってない場合にダメージ処理

	//}
	//if (player.PlayerMISS == TRUE)//リロードの無敵時間
	//{
	//	//リロード時間が終わったとき
	//	if (player.PlayerReLoadCnt == player.PlayerReLoadCntMAX)
	//	{
	//		player.PlayerReLoadCnt = 0;
	//		player.PlayerMISS = FALSE;
	//	}

	//	player.PlayerReLoadCnt++;	//リロードする
	//}

	if (player_Life < 0) //ライフが無くなったらゲームオーバー
	{
		if (CheckSoundMem(PLAY_BGM.handle) != 0)
		{
			StopSoundMem(PLAY_BGM.handle);
		}
		//ここでタイマーリセット
		GameEndKind = GAME_END_FAIL;
		GameScene = GAME_SCENE_END;
		return;
	}

	NowPlayTime = GetNowCount();
	//if(NowPlayTime-StartTime>=30000&&player_Life>0) //30秒経ったらクリア
	//{
	//	if (CheckSoundMem(PLAY_BGM.handle) != 0)
	//	{
	//		StopSoundMem(PLAY_BGM.handle);
	//	}
	//	GameEndKind = GAME_END_COMP;
	//	GameScene = GAME_SCENE_END;
	//	return;
	//}


	if(NowPlayTime-StartTime>=PLAY_TIME&&player_Life>0)
	{
		if (CheckSoundMem(PLAY_BGM.handle) != 0)
		{
			StopSoundMem(PLAY_BGM.handle);
		}
		GameEndKind = GAME_END_COMP; //現状FAILしかないから仕方なく
		GameScene = GAME_SCENE_END;
		return;
	} /*デバッグ用*/

	return;
}

VOID MY_PLAY_DRAW(VOID)
{
	//DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT, GetColor(0, 255, 255), TRUE);


	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		if (ImageBack[num].IsDraw == TRUE)
		{
			DrawGraph(ImageBack[num].image.x, ImageBack[num].image.y, ImageBack[num].image.handle, TRUE);

			//DrawFormatString(
			//	ImageBack[num].image.x,
			//	ImageBack[num].image.y,
			//	GetColor(255, 255, 255), "背景画像 : %d", num + 1
			//);
		}
	}

	//for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	//{
	//	for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
	//	{
	//		DrawGraph(
	//			map[tate][yoko].x,
	//			map[tate][yoko].y,
	//			mapChip.handle[map[tate][yoko].kind],
	//			TRUE);
	//	}
	//}

	DrawGraph(enemy.image.x, enemy.image.y, enemy.image.handle, TRUE); //プレイヤー表示
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE); //プレイヤー表示
	if (player.PlayerMISS == TRUE)//リスポーン中
	{
		//自分を点滅させる
		DrawBox(player.image.x, player.image.y, player.image.x + 10, player.image.y + 10, GetColor(255, 0, 0), TRUE);
	}

	//弾の情報を生成
	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		//描画できる弾の処理
		if (player.tama[cnt].IsDraw == TRUE)
		{
			//弾を描画する
			DrawGraph(
				player.tama[cnt].x,
				player.tama[cnt].y,
				player.tama[cnt].handle[player.tama[cnt].nowImageKind],	//現在の画像の種類にあったハンドル
				TRUE);
			/*nowImageKindにどの色が入るかをパスを指定する（？）*/


			//弾の表示フレームを増やす
			if (player.tama[cnt].changeImageCnt < player.tama[cnt].changeImageCntMAX)
			{
				player.tama[cnt].changeImageCnt++;
			}
			else
			{
				//現在表示している弾の種類が、まだあるとき
				if (player.tama[cnt].nowImageKind < TAMA_DIV_NUM - 1)	//-1しないと、最後の種類のときに++されてしまう
				{
					player.tama[cnt].nowImageKind++;	//弾を次の種類にする
				}
				else
				{
					player.tama[cnt].nowImageKind = 0;	//弾の種類をリセットする
				}

				player.tama[cnt].changeImageCnt = 0;
			}

			//弾を上に移動させる（縦シューティング）
			if (player.tama[cnt].y < 0)
			{
				player.tama[cnt].IsDraw = FALSE;	//描画終了
			}
			else
			{
				player.tama[cnt].y -= player.tama[cnt].speed;
			}

			//* 横シューティングで右から左に飛ばす場合 *//

			//if (player.tama[cnt].x < 0)
			//{
			//	player.tama[cnt].IsDraw = FALSE;
			//}
			//else
			//{
			//	player.tama[cnt].x -= player.tama[cnt].speed;
			//}
		}
	}

	//デバッグ用（左クリック拾ってるか）
	if (MY_MOUSE_DOWN(MOUSE_INPUT_LEFT) == TRUE)
	{
		DrawBox(player.image.x, player.image.y, player.image.x + 10, player.image.y + 10, GetColor(0, 255, 0),TRUE);
	}

	DrawFormatString(
		GAME_WIDTH - 300,
		GAME_HEIGHT - 15,
		GetColor(255, 0, 0), "残り時間: %d 秒", (PLAY_TIME - (NowPlayTime-StartTime))/1000);

	DrawFormatString(
		GAME_WIDTH - 550,
		GAME_HEIGHT - 15,
		GetColor(255, 0, 0), "ライフ: %d ", player_Life);


	
	return;
}
VOID MY_END(VOID)
{
	MY_END_PROC();
	MY_END_DRAW();

	return;
}

VOID MY_END_PROC(VOID)
{
	SetMouseDispFlag(TRUE);

	switch (GameEndKind)
	{
	case GAME_END_COMP:
		if (CheckSoundMem(END_COMP_BGM.handle) == 0)
		{
			ChangeVolumeSoundMem(GAME_SOUND_VOLUME, END_COMP_BGM.handle); //50%の音量
			PlaySoundMem(END_COMP_BGM.handle, DX_PLAYTYPE_LOOP); //ループ再生
		}
		//ロゴ
		if (ImageEndCOMP.Cnt < ImageEndCOMP.CntMAX)
		{
			ImageEndCOMP.Cnt += IMAGE_END_COMP_CNT;
		}
		else
		{
			if (ImageEndCOMP.IsDraw == FALSE)
			{
				ImageEndCOMP.IsDraw = TRUE;
			}
			else if (ImageEndCOMP.IsDraw == TRUE)
			{
				ImageEndCOMP.IsDraw = FALSE;
			}
			ImageEndCOMP.Cnt = 0;
		}
		break;

	case GAME_END_FAIL:
		if (CheckSoundMem(END_FAIL_BGM.handle) == 0)
		{
			ChangeVolumeSoundMem(GAME_SOUND_VOLUME, END_FAIL_BGM.handle); //50%の音量
			PlaySoundMem(END_FAIL_BGM.handle, DX_PLAYTYPE_LOOP); //ループ再生
		}

		//ロゴ
		if (ImageEndFAIL.Cnt < ImageEndFAIL.CntMAX)
		{
			ImageEndFAIL.Cnt += IMAGE_END_FAIL_CNT;
		}
		else
		{
			if (ImageEndFAIL.IsDraw == FALSE)
			{
				ImageEndFAIL.IsDraw = TRUE;
			}
			else if (ImageEndFAIL.IsDraw == TRUE)
			{
				ImageEndFAIL.IsDraw = FALSE;
			}
			ImageEndFAIL.Cnt = 0;
		}
		
		break;
	}
	if (MY_KEY_UP(KEY_INPUT_ESCAPE) == TRUE)
	{
		if (CheckSoundMem(END_FAIL_BGM.handle) != 0)
		{
			StopSoundMem(END_FAIL_BGM.handle);
		}
		//else if (CheckSoundMem(END_COMP_BGM.handle) != 0)
		//{
		//	StopSoundMem(END_COMP_BGM.handle);
		//}
		
		GameScene = GAME_SCENE_START;

		return;
	}
	return;
}

VOID MY_END_DRAW(VOID)
{
	MY_PLAY_DRAW();

	switch (GameEndKind)
	{
	case GAME_END_COMP:
		//DrawGraph(ImagePerEndBK.x, ImagePerEndBK.y, ImagePerEndBK.handle, TRUE);

		//DrawStringToHandle(GAME_WIDTH / 2, GAME_HEIGHT / 2, "正解数：%d 問/全4問中", seikai, GetColor(255, 0, 0), FontHandle);
		//DrawFormatString(
		//GAME_WIDTH,
		//GAME_HEIGHT,
		//GetColor(255, 255, 255), "正解数：%d 問/全4問中", seikai);
		DrawStringToHandle(30, 330, "ミッションコンプリート！　escキーでタイトルにもどるよ", GetColor(255, 0, 0), FontTanu32.handle);
		if (ImageEndCOMP.IsDraw == TRUE)
		{
			DrawGraph(ImageEndCOMP.image.x, ImageEndCOMP.image.y, ImageEndCOMP.image.handle, TRUE);
		}
		break;

	case GAME_END_FAIL:
		DrawStringToHandle(GAME_WIDTH / 4, 500, "残念！　escキーでタイトルに戻るよ", GetColor(0, 0, 255), FontTanu32.handle);
		if (ImageEndFAIL.IsDraw == TRUE)
		{
			DrawGraph(ImageEndFAIL.image.x, ImageEndFAIL.image.y, ImageEndFAIL.image.handle, TRUE);
		}

		break;
	}

	DrawString(0, 0, "エンド画面(エスケープキーを押してください。)", GetColor(255, 255, 255));

	return;
}

BOOL MY_LOAD_IMAGE(VOID)
{
	strcpy_s(ImageTitleROGO.path, IMAGE_TITLE_ROGO_PATH);
	ImageTitleROGO.handle = LoadGraph(ImageTitleROGO.path);
	if (ImageTitleROGO.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleROGO.handle, &ImageTitleROGO.width, &ImageTitleROGO.height);

	ImageTitleROGO.x = GAME_WIDTH / 2 - ImageTitleROGO.width / 2;
	ImageTitleROGO.y = (GAME_HEIGHT / 2 - ImageTitleROGO.height / 2) - 50;


	//弾生成（仮）
	int tamaRedRes = LoadDivGraph(
		TAMA_RED_PATH,/*弾の色（ここではカラーごとに画像を別にしてる）*/
		TAMA_DIV_NUM, TAMA_DIV_TATE, TAMA_DIV_YOKO,
		TAMA_DIV_WIDTH, TAMA_DIV_HEIGHT,
		&player.tama[0].handle[0]
	);

	if (tamaRedRes == -1)
	{
		MessageBox(GetMainWindowHandle(), TAMA_RED_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	GetGraphSize(player.tama[0].handle[0], &player.tama[0].width, &player.tama[0].height);

	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		//パスをコピー
		strcpyDx(player.tama[cnt].path, TEXT(TAMA_RED_PATH));//赤のみの弾画像をパスで渡してる。自分のもそうしてみるか

		for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++)
		{
			//ハンドルをコピー
			player.tama[cnt].handle[i_num] = player.tama[0].handle[i_num];
		}

		//幅をコピー
		player.tama[cnt].width = player.tama[0].width;

		//高さをコピー
		player.tama[cnt].height = player.tama[0].height;

		//弾のX位置はプレイヤーの中心から発射
		player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;

		//弾のY位置はプレイヤーの上部分から発射
		player.tama[cnt].y = player.image.y;

		//弾は最初は非表示
		player.tama[cnt].IsDraw = FALSE;

		//弾の表示カウントを0にする
		player.tama[cnt].changeImageCnt = 0;

		//弾の表示カウントMAXを設定する
		player.tama[cnt].changeImageCntMAX = TAMA_CHANGE_MAX;

		//現在の画像の種類を初期化する
		player.tama[cnt].nowImageKind = 0;

		//弾のスピードを設定する
		player.tama[cnt].speed = CHARA_SPEED_LOW;


		//player.ShotReLoadCntMAX = 5;//弾のリロード時間（フレーム数）
	}

	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);
	player.image.handle = LoadGraph(player.image.path);

	if (player.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);	//画像の幅と高さを取得
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;		//左右中央揃え
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;		//上下中央揃え
	player.CenterX = player.image.x + player.image.width / 2;		//画像の横の中心を探す
	player.CenterY = player.image.y + player.image.height / 2;		//画像の縦の中心を探す


	//マップ

	//int mapRes = LoadDivGraph(
	//	GAME_MAP_PATH,
	//	MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,
	//	MAP_DIV_WIDTH, MAP_DIV_HEIGHT,
	//	&mapChip.handle[0]
	//);

	//if (mapRes == -1)
	//{
	//	MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
	//	return FALSE;
	//}

	//GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);
	//for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	//{
	//	for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
	//	{
	//		mapDataInit[tate][yoko] = mapData[tate][yoko];
	//		map[tate][yoko].kind = mapData[tate][yoko];

	//		map[tate][yoko].width = mapChip.width;
	//		map[tate][yoko].height = mapChip.height;

	//		map[tate][yoko].x = yoko * map[tate][yoko].width;
	//		map[tate][yoko].y = tate * map[tate][yoko].height;

	//	}
	//}

	//for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	//{
	//	for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
	//	{
	//		mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
	//		mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
	//		mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
	//		mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;

	//	}
	//}

	/*敵単体*/
	int enemyRedRes = LoadDivGraph(
		TAMA_RED_PATH,/*弾の色（ここではカラーごとに画像を別にしてる）*/
		TAMA_DIV_NUM, TAMA_DIV_TATE, TAMA_DIV_YOKO,
		TAMA_DIV_WIDTH, TAMA_DIV_HEIGHT,
		&player.tama[0].handle[0]
	);

	if (enemyRedRes == -1)
	{
		MessageBox(GetMainWindowHandle(), TAMA_RED_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	GetGraphSize(player.tama[0].handle[0], &player.tama[0].width, &player.tama[0].height);

	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		//パスをコピー
		strcpyDx(player.tama[cnt].path, TEXT(TAMA_RED_PATH));//赤のみの弾画像をパスで渡してる。自分のもそうしてみるか

		for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++)
		{
			//ハンドルをコピー
			player.tama[cnt].handle[i_num] = player.tama[0].handle[i_num];
		}

		//幅をコピー
		player.tama[cnt].width = player.tama[0].width;

		//高さをコピー
		player.tama[cnt].height = player.tama[0].height;

		//弾のX位置はプレイヤーの中心から発射
		player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;

		//弾のY位置はプレイヤーの上部分から発射
		player.tama[cnt].y = player.image.y;

		//弾は最初は非表示
		player.tama[cnt].IsDraw = FALSE;

		//弾の表示カウントを0にする
		player.tama[cnt].changeImageCnt = 0;

		//弾の表示カウントMAXを設定する
		player.tama[cnt].changeImageCntMAX = TAMA_CHANGE_MAX;

		//現在の画像の種類を初期化する
		player.tama[cnt].nowImageKind = 0;

		//弾のスピードを設定する
		player.tama[cnt].speed = CHARA_SPEED_LOW;
	}

	/*背景*/
	strcpy_s(ImageBack[0].image.path, IMAGE_PLAY_BK_PATH1);
	strcpy_s(ImageBack[1].image.path, IMAGE_PLAY_BK_PATH2);
	strcpy_s(ImageBack[2].image.path, IMAGE_PLAY_BK_PATH3);
	strcpy_s(ImageBack[3].image.path, IMAGE_PLAY_BK_PATH4);



	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		ImageBack[num].image.handle = LoadGraph(ImageBack[num].image.path);
		if (ImageBack[num].image.handle == -1)
		{
			MessageBox(GetMainWindowHandle(), IMAGE_PLAY_BK_PATH1, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}
		GetGraphSize(ImageBack[num].image.handle, &ImageBack[num].image.width, &ImageBack[num].image.height);

	}

	///* 縦用 *//

	ImageBack[0].image.x = GAME_WIDTH / 2 - ImageBack[0].image.width / 2;
	ImageBack[0].image.y = 0 - ImageBack[0].image.height * 0;
	ImageBack[0].IsDraw = FALSE;

	ImageBack[1].image.x = GAME_WIDTH / 2 - ImageBack[1].image.width / 2;
	ImageBack[1].image.y = 0 - ImageBack[0].image.height * 1;
	ImageBack[1].IsDraw = FALSE;

	ImageBack[2].image.x = GAME_WIDTH / 2 - ImageBack[2].image.width / 2;
	ImageBack[2].image.y = 0 - ImageBack[0].image.height * 2;
	ImageBack[2].IsDraw = FALSE;

	ImageBack[3].image.x = GAME_WIDTH / 2 - ImageBack[3].image.width / 2;
	ImageBack[3].image.y = 0 - ImageBack[0].image.height * 3;
	ImageBack[3].IsDraw = FALSE;

	//* 横用 *//

	//ImageBack[0].image.x = 0 - ImageBack[0].image.width * 0;
	//ImageBack[0].image.y = GAME_HEIGHT / 2 - ImageBack[0].image.height / 2;
	//ImageBack[0].IsDraw = FALSE;

	//ImageBack[1].image.x = 0 - ImageBack[0].image.width * 1;
	//ImageBack[1].image.y = GAME_HEIGHT / 2 - ImageBack[1].image.height / 2;
	//ImageBack[1].IsDraw = FALSE;

	//ImageBack[2].image.x = 0 - ImageBack[0].image.width * 2;
	//ImageBack[2].image.y = GAME_HEIGHT / 2 - ImageBack[2].image.height / 2;
	//ImageBack[2].IsDraw = FALSE;

	//ImageBack[3].image.x = 0 - ImageBack[0].image.width * 3;
	//ImageBack[3].image.y = GAME_HEIGHT / 2 - ImageBack[3].image.height / 2;
	//ImageBack[3].IsDraw = FALSE;

	//エンドロゴ
	strcpy_s(ImageEndCOMP.image.path, IMAGE_END_COMP_ROGO_PATH);
	ImageEndCOMP.image.handle = LoadGraph(ImageEndCOMP.image.path);
	if (ImageEndCOMP.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_END_COMP_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndCOMP.image.handle, &ImageEndCOMP.image.width, &ImageEndCOMP.image.height);

	ImageEndCOMP.image.x = GAME_WIDTH / 2 - ImageEndCOMP.image.width / 2;
	ImageEndCOMP.image.y = GAME_HEIGHT / 2 - ImageEndCOMP.image.height / 2;
	ImageEndCOMP.Cnt = 0.0;
	ImageEndCOMP.CntMAX = IMAGE_END_COMP_CNT_MAX;
	ImageEndCOMP.IsDraw = FALSE;

	strcpy_s(ImageEndFAIL.image.path, IMAGE_END_FAIL_ROGO_PATH);
	ImageEndFAIL.image.handle = LoadGraph(ImageEndFAIL.image.path);
	if (ImageEndFAIL.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_END_FAIL_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndFAIL.image.handle, &ImageEndFAIL.image.width, &ImageEndFAIL.image.height);

	ImageEndFAIL.image.x = GAME_WIDTH / 2 - ImageEndFAIL.image.width / 2;
	ImageEndFAIL.image.y = GAME_HEIGHT / 2 - ImageEndFAIL.image.height / 2;
	ImageEndFAIL.Cnt = 0.0;
	ImageEndFAIL.CntMAX = IMAGE_END_FAIL_CNT_MAX;
	ImageEndFAIL.IsDraw = FALSE;

	return TRUE;
}

VOID MY_DELETE_IMAGE(VOID)
{
	DeleteGraph(ImageTitleROGO.handle);
	
	//背景
	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		DeleteGraph(ImageBack[0].image.handle);
	}

	//弾削除
	for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++) { DeleteGraph(player.tama[0].handle[i_num]); }
	//敵マップ
	//for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++)
	//{
	//	DeleteGraph(mapChip.handle[i_num]);
	//}

	DeleteGraph(player.image.handle); //キャラ
	//for (int i_num = 0; i_num < IMAGE_PLAYER_NUM; i_num++)
	//{
	//	DeleteGraph(charaChip.handle[i_num]);
	//}
	DeleteGraph(ImageEndFAIL.image.handle); //エンドロゴ
	DeleteGraph(ImageEndCOMP.image.handle); //パフェロゴ
	return;
}

BOOL(MY_LOAD_MUSIC)(VOID)
{
	strcpy_s(TITLE.path, MUSIC_TITLE_BGM_PATH);
	TITLE.handle = LoadSoundMem(TITLE.path);
	if (TITLE.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_TITLE_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(PLAY_BGM.path, MUSIC_PLAY_BGM_PATH);
	PLAY_BGM.handle = LoadSoundMem(PLAY_BGM.path);
	if (PLAY_BGM.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_PLAY_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//プレイヤーのショット音
	strcpy_s(player.musicShot.path, MUSIC_PLAYER_SHOT_PATH);			//パスの設定
	player.musicShot.handle = LoadSoundMem(player.musicShot.path);		//読み込み
	if (player.musicShot.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_PLAYER_SHOT_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(END_FAIL_BGM.path, MUSIC_END_BGM_PATH);
	END_FAIL_BGM.handle = LoadSoundMem(END_FAIL_BGM.path);
	if (END_FAIL_BGM.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_END_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	strcpy_s(END_COMP_BGM.path, MUSIC_END_BGM_PATH);
	END_COMP_BGM.handle = LoadSoundMem(END_COMP_BGM.path);
	if (END_COMP_BGM.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_CLEAR_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	return TRUE;
}

VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(TITLE.handle);
	DeleteSoundMem(PLAY_BGM.handle); 
	DeleteSoundMem(player.musicShot.handle);

	DeleteSoundMem(END_FAIL_BGM.handle);
	DeleteSoundMem(END_COMP_BGM.handle);
	return;
}

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player)
{
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				if (map[tate][yoko].kind == e)
				{ 

				}
			}

		}
	}
	return FALSE;
}
//
//BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT tama[TAMA_MAX])
//{
//	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
//	{
//		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
//		{
//			for (int cnt = 0; cnt < TAMA_MAX; cnt++)
//			{
//				if (MY_CHECK_RECT_COLL(tama[cnt], mapColl[tate][yoko]) == TRUE)
//				{
//					if (map[tate][yoko].kind == e)
//					{
//						//ここに敵に当たったときの処理書いてみて
//						map[tate][yoko].kind = n;//敵を消す
//						//倒した数を足す
//					}
//				} /* 弾と敵が当たったとき（まだだめじゃん） */
//			}
//
//
//		}
//	}
//	return FALSE;
//}一旦これのことは考えない

//球の当たり判定を引数にした球用当たり判定作るか？

BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left<b.right &&
		a.top<b.bottom &&
		a.right>b.left &&
		a.bottom>b.top)
	{
		return TRUE;
	}
	return FALSE;
}