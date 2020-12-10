//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include "resource.h"

#define GAME_WIDTH			800	//画面の横の大きさ
#define GAME_HEIGHT			600	//画面の縦の大きさ
#define GAME_COLOR			32	//画面のカラービット

#define GAME_WINDOW_BAR		0	//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"GAME TITLE"	//ウィンドウのタイトル

#define GAME_FPS 60 //FPSの数値

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

#define IMAGE_PLAYER_PATH TEXT(".\\IMAGE\\pipo-charachip025a.png")
#define IMAGE_PLAYER_WIDTH		96	//画像を分割する幅サイズ
#define IMAGE_PLAYER_HEIGHT		128	//画像を分割する高さサイズ

#define IMAGE_PLAYER_TATE		3	//画像を縦に分割する数
#define IMAGE_PLAYER_YOKO		4	//画像を横に分割する数

#define IMAGE_PLAYER_NUM	IMAGE_PLAYER_TATE * IMAGE_PLAYER_YOKO	//画像を分割する総数
#define IMAGE_LOAD_ERR_TITLE TEXT("画像読み込みエラー")

#define MUSIC_TITLE_BGM_PATH TEXT(".\\MUSIC\\loop_33.wav")
#define MUSIC_PLAY_BGM_PATH TEXT(".\\MUSIC\\fruitsparfait.mp3")
#define MUSIC_END_BGM_PATH TEXT(".\\MUSIC\\ほのぼのゲームオーバー.mp3")

#define MUSIC_LOAD_ERR_TITLE TEXT("音楽読み込みエラー")

//弾の設定
#define TAMA_CHANGE_MAX		 5	//5フレーム目で弾の画像を変える
#define TAMA_MAX			16	//最大16発まで

/*弾の画像は仮。自分でちゃんと描いてね*/
#define TAMA_RED_PATH			TEXT(".\\IMAGE\\TAMA\\red.png")		//赤弾の画像
#define TAMA_GREEN_PATH			TEXT(".\\IMAGE\\TAMA\\green.png")	//青弾の画像
#define TAMA_BLUE_PATH			TEXT(".\\IMAGE\\TAMA\\blue.png")	//緑弾の画像
#define TAMA_YELLOW_PATH		TEXT(".\\IMAGE\\TAMA\\yellow.png")	//黄弾の画像

#define TAMA_DIV_WIDTH		16	//画像を分割する幅サイズ
#define TAMA_DIV_HEIGHT		16	//画像を分割する高さサイズ

#define TAMA_DIV_TATE		3	//画像を縦に分割する数
#define TAMA_DIV_YOKO		1	//画像を横に分割する数

#define TAMA_DIV_NUM	TAMA_DIV_TATE * TAMA_DIV_YOKO	//画像を分割する総数

//敵マップ
//#define GAME_MAP_BK_PATH TEXT(".\\IMAGE\\ゲーム背景.png")
#define GAME_MAP_PATH TEXT(".\\IMAGE\\enemyMAP.png") 
#define GAME_MAP_TATE_MAX 14
#define GAME_MAP_YOKO_MAX 24
#define GAME_MAP_KIND_MAX 2

#define MAP_DIV_WIDTH 64
#define MAP_DIV_HEIGHT 64
#define MAP_DIV_TATE 10
#define MAP_DIV_YOKO 4

#define MAP_DIV_NUM MAP_DIV_TATE*MAP_DIV_YOKO

#define START_ERR_TITLE		TEXT("スタート位置エラー")
#define START_ERR_CAPTION	TEXT("スタート位置が決まっていません")

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
	int ShotReLoadCntMAX;		//ショットリロード時間(MAX)

	TAMA tama[TAMA_MAX];
	RECT coll;
	iPOINT collBeforePt;

}CHARA;

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

/*キャラチップ*/
//横方向と縦方向のカウント数。
int xcount = 0, ycount = 0;
//添字用変数
int ix = 0, iy = 0, result = 0;
MAP_CHIP charaChip;

//マウスの座標を取得
MOUSE mouse;

//ゲーム関連
int GameScene; //ゲームシーンを管理

//プレイヤー関連
CHARA player; //ゲームのキャラ
CHARA enemy;

//画像関係
IMAGE ImageTitleROGO; //タイトルロゴ
IMAGE ImageTitleBack; //タイトル背景

IMAGE ImagePlayBack; //プレイ背景

IMAGE ImageEndBack; //エンド背景

//音楽関係
MUSIC TITLE;
MUSIC PLAY_BGM;
MUSIC END_BGM;

//フォント
FONT FontTanu32;

GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]
{
	//　0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,
		n,n,n,n,n,n,n,n,n,n,n,n,n,n,//0
		n,n,n,n,n,n,n,n,n,n,n,n,n,n,//1
		n,n,n,n,n,n,n,n,n,n,n,n,n,n,//2
		n,n,n,e,n,n,e,n,e,n,e,n,n,n,//3
		n,n,n,n,n,n,n,n,n,n,n,n,n,n,//4
		n,n,n,n,n,n,n,n,n,n,n,n,n,n,//5
		n,n,n,n,n,n,n,n,n,n,n,n,n,n,//6
		n,n,n,n,n,n,n,s,n,n,n,n,n,n,//7
		//テスト用
};
GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
MAP_CHIP mapChip;
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
iPOINT startPt{ -1,-1 };
//IMAGE MapBack;
RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

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
		ChangeVolumeSoundMem(255 * 50 / 100, TITLE.handle); //50%の音量
		PlaySoundMem(TITLE.handle, DX_PLAYTYPE_LOOP); //ループ再生
	}
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		//BGMが流れていたら
		if (CheckSoundMem(TITLE.handle) != 0)
		{
			StopSoundMem(TITLE.handle); //止める
		}

		MY_PLAY_INIT(); //ゲーム初期化

		GameScene = GAME_SCENE_PLAY; //プレイ画面に遷移

		return;
	}
	return;
}

VOID MY_START_DRAW(VOID)
{
	DrawString(0, 0, "スタート画面（エンターキーを押してください）", GetColor(255, 255, 255));
	DrawGraph(ImageTitleROGO.x, ImageTitleROGO.y, ImageTitleROGO.handle, TRUE);
	
	DrawStringToHandle(GAME_WIDTH/4, GAME_HEIGHT/2+50, "エンターキーをおしてね！", GetColor(255, 255, 255), FontTanu32.handle);

	return;
}

VOID MY_PLAY_INIT(VOID)
{
	return;
}

VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();
	MY_PLAY_DRAW();

	return;
}

VOID MY_PLAY_PROC(VOID)
{
	//BGMが流れていないなら
	if (CheckSoundMem(PLAY_BGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, PLAY_BGM.handle); //50%の音量
		PlaySoundMem(PLAY_BGM.handle, DX_PLAYTYPE_LOOP); //ループ再生
	}
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		if (CheckSoundMem(PLAY_BGM.handle) != 0)
		{
			StopSoundMem(PLAY_BGM.handle);
		}
		GameScene = GAME_SCENE_END; //プレイ画面に遷移

		return;
	}

	//キャラクターをキー入力で操作
	player.speed = 2;
	if (MY_KEY_DOWN(KEY_INPUT_UP) == TRUE)
	{
		player.CenterY -= player.speed;
		if (ycount > 0)
			ycount = 0;
		--ycount;
	}
	if (MY_KEY_DOWN(KEY_INPUT_DOWN) == TRUE)
	{
		player.CenterY += player.speed;
		if (ycount < 0)
			ycount = 0;
		++ycount;
	}
	if (MY_KEY_DOWN(KEY_INPUT_LEFT) == TRUE)
	{
		player.CenterX -= player.speed;
		if (xcount > 0)
			xcount = 0;
		--xcount;
	}
	if (MY_KEY_DOWN(KEY_INPUT_RIGHT) == TRUE)
	{
		player.CenterX += player.speed;
		if (xcount < 0)
			xcount = 0;
		++xcount;
	}
	//カウント数から添字を求める。
	ix = abs(xcount) % 30 / 10;
	iy = abs(ycount) % 30 / 10;

	//xカウントがプラスなら右向きなので2行目の先頭添字番号を足す。
	if (xcount > 0) {
		ix += 3;
		result = ix;
	}
	else if (xcount < 0) {
		//マイナスなら左向きなので、4行目の先頭添字番号を足す。
		ix += 9;
		result = ix;
	}

	//yカウントがプラスなら下向きなので、3行目の先頭添字番号を足す。
	if (ycount > 0) {
		iy += 6;
		result = iy;
	}
	else if (ycount < 0) {
		//１行目の先頭添字番号は０なので何もする必要なし。(分かりやすくするために書いときました)
		iy += 0;
		result = iy;
	}
	//押されてなければカウントをゼロにする。(ここではキーが押されて【いない】で判定してる。【キーが上がっている】か否かは動作確認して合う方を使う)
	if (MY_KEY_DOWN(KEY_INPUT_LEFT) ==FALSE && MY_KEY_DOWN(KEY_INPUT_RIGHT) == FALSE) {
		xcount = 0;
	}
	if (MY_KEY_DOWN(KEY_INPUT_UP) == FALSE && MY_KEY_DOWN(KEY_INPUT_DOWN) == FALSE) {
		ycount = 0;
	}

	//当たり判定
	player.coll.left = player.CenterX - mapChip.width / 2 + 5;
	player.coll.top = player.CenterY - mapChip.height / 2 + 5;
	player.coll.right = player.CenterX + mapChip.width / 2 - 5;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;

	BOOL IsMove = TRUE;

	//if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	{
		player.CenterX = player.collBeforePt.x;
		player.CenterY = player.collBeforePt.y;
		//SetMousePoint(player.collBeforePt.x, player.collBeforePt.y);

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

	RECT EnemyRect;
	EnemyRect.left = enemy.image.x + 40;
	EnemyRect.top = enemy.image.y + 40;
	EnemyRect.right = enemy.image.x + player.image.width - 40;
	EnemyRect.bottom = enemy.image.y + player.image.height - 40;



	//スペースキーを押したとき
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		//弾の描画（仮）
		//ショットが撃てるとき
		if (player.CanShot == TRUE)
		{
			//ショット発射！！
			PlaySoundMem(player.musicShot.handle, DX_PLAYTYPE_BACK);
			player.CanShot = FALSE;

			//空いているスロットで、弾の描画をする
			for (int cnt = 0; cnt < TAMA_MAX; cnt++)
			{
				if (player.tama[cnt].IsDraw == FALSE)
				{
					//弾のX位置はプレイヤーの中心から発射
					player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;

					//弾のY位置はプレイヤーの上部分から発射
					player.tama[cnt].y = player.image.y;


					//弾当たり判定
					RECT TamaRect;
					TamaRect.left = player.tama[cnt].x + 40;
					TamaRect.top = player.tama[cnt].y + 40;
					TamaRect.right = player.tama[cnt].x + player.tama[cnt].width - 40;
					TamaRect.bottom = player.tama[cnt].y + player.tama[cnt].height - 40;

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
	return;
}

VOID MY_PLAY_DRAW(VOID)
{
	DrawGraph(ImagePlayBack.x, ImagePlayBack.y, ImagePlayBack.handle, TRUE);
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);
	
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			DrawGraph(
				map[tate][yoko].x,
				map[tate][yoko].y,
				mapChip.handle[map[tate][yoko].kind],
				TRUE);
		}
	}
	/*画面下から上に動くような描写。方向を変更するかもしれない*/
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

			//弾を上に移動させる
			if (player.tama[cnt].y < 0)
			{
				player.tama[cnt].IsDraw = FALSE;	//描画終了
			}
			else
			{
				player.tama[cnt].y -= player.tama[cnt].speed;
			}
		}
	}

	DrawString(0, 0, "プレイ画面(スペースキーを押してください。)", GetColor(255, 255, 255));

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
	if (CheckSoundMem(END_BGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, END_BGM.handle); //50%の音量
		PlaySoundMem(END_BGM.handle, DX_PLAYTYPE_LOOP); //ループ再生
	}
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		if (CheckSoundMem(END_BGM.handle) != 0)
		{
			StopSoundMem(END_BGM.handle);
		}
		GameScene = GAME_SCENE_START; //プレイ画面に遷移

		return;
	}
	return;
}

VOID MY_END_DRAW(VOID)
{
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
	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		//パスをコピー
		strcpyDx(player.tama[cnt].path, TEXT(TAMA_RED_PATH));

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


	//プレイヤー
	int playerRes = LoadDivGraph(
		IMAGE_PLAYER_PATH,
		IMAGE_PLAYER_NUM, IMAGE_PLAYER_TATE, IMAGE_PLAYER_YOKO,
		IMAGE_PLAYER_WIDTH, IMAGE_PLAYER_HEIGHT,
		&charaChip.handle[0]
	);
	if (playerRes == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//マップ

	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,
		&mapChip.handle[0]
	);

	if (mapRes == -1)
	{
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			mapDataInit[tate][yoko] = mapData[tate][yoko];
			map[tate][yoko].kind = mapData[tate][yoko];

			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;

			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;

		}
	}

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;

		}
	}
	return TRUE;
}

VOID MY_DELETE_IMAGE(VOID)
{
	DeleteGraph(ImageTitleROGO.handle);

	//弾削除
	for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++) { DeleteGraph(player.tama[0].handle[i_num]); }
	//敵マップ
	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++)
	{
		DeleteGraph(mapChip.handle[i_num]);
	}

	for (int i_num = 0; i_num < IMAGE_PLAYER_NUM; i_num++)
	{
		DeleteGraph(charaChip.handle[i_num]);
	}
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

	strcpy_s(END_BGM.path, MUSIC_END_BGM_PATH);
	END_BGM.handle = LoadSoundMem(END_BGM.path);
	if (END_BGM.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_END_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	return TRUE;
}

VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(TITLE.handle);
	DeleteSoundMem(PLAY_BGM.handle); 
	DeleteSoundMem(END_BGM.handle);
	return;
}