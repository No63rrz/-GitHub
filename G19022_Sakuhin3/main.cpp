//���킩���Ă�o�O
//
//�܂��e�ƓG�͂��蔲����

//����邱��
//�G�́y�`��zPLAY_DRAW
//�G�ƒe���y�ڐG�����u�ԁz�ɓG������
//
//�����G�����̂͂�߂Ă�����ςȂ��烉�X�{�X�I
//��
//1�̂̃f�J���G�������ŐF��ς��Đg�����
//�G�̓o�E���h����

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include "resource.h"

#define GAME_WIDTH			800	//��ʂ̉��̑傫��
#define GAME_HEIGHT			600	//��ʂ̏c�̑傫��
#define GAME_COLOR			32	//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR		0	//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME	"�|�v�W�J���V���[�e�B���O"	//�E�B���h�E�̃^�C�g��

#define GAME_FPS 60 //FPS�̐��l

#define GAME_SOUND_VOLUME_PER 30	//%
#define GAME_SOUND_VOLUME 255 * GAME_SOUND_VOLUME_PER / 100		//���̃p�[�Z���g�̃{�����[��

#define PLAY_TIME_SECOND 60		//�b
#define PLAY_TIME PLAY_TIME_SECOND*1000

//�}�E�X�̃{�^��
#define MOUSE_BUTTON_CODE 129 //0x0000�`0x0080�܂�

//�L�[�{�[�h�̎��
#define KEY_CODE_KIND 256 //256���

//�p�X�̒���
#define PATH_MAX 255 //255�����܂�
#define NAME_MAX 255 //255�����܂�

//�t�H���g
#define FONT_TANU_PATH TEXT(".\\FONT\\TanukiMagic.ttf")
#define FONT_TANU_NAME TEXT("���ʂ������}�W�b�N")
//�t�H���g�G���[
#define FONT_INSTALL_ERR_TITLE TEXT("�t�H���g�C���X�g�[���G���[")
#define FONT_CREATE_ERR_TITLE TEXT("�t�H���g�쐬�G���[")

#define IMAGE_TITLE_ROGO_PATH TEXT(".\\IMAGE\\ROGO.png")

//�w�i
#define IMAGE_PLAY_BK_PATH1 TEXT(".\\IMAGE\\haikei1.png")
#define IMAGE_PLAY_BK_PATH2 TEXT(".\\IMAGE\\haikei2.png")
#define IMAGE_PLAY_BK_PATH3 TEXT(".\\IMAGE\\haikei3.png")
#define IMAGE_PLAY_BK_PATH4 TEXT(".\\IMAGE\\haikei4.png")

#define IMAGE_BACK_NUM 4

#define IMAGE_PLAYER_PATH TEXT(".\\IMAGE\\player.png")

#define IMAGE_LOAD_ERR_TITLE TEXT("�摜�ǂݍ��݃G���[")

#define MUSIC_TITLE_BGM_PATH TEXT(".\\MUSIC\\loop_33.wav")
#define MUSIC_PLAY_BGM_PATH TEXT(".\\MUSIC\\fruitsparfait.mp3")
#define MUSIC_END_BGM_PATH TEXT(".\\MUSIC\\�ق̂ڂ̃Q�[���I�[�o�[.mp3")
#define MUSIC_CLEAR_BGM_PATH TEXT(".\\MUSIC\\�ق̂ڂ̃Q�[���I�[�o�[.mp3") //BGM�͉�
#define MUSIC_PLAYER_SHOT_PATH TEXT(".\\MUSIC\\anime_flying.mp3")
#define MUSIC_LOAD_ERR_TITLE TEXT("���y�ǂݍ��݃G���[")

//�e�̐ݒ�
#define TAMA_CHANGE_MAX		 5	//5�t���[���ڂŒe�̉摜��ς���
#define TAMA_MAX			16	//�ő�16���܂�

/*�e�̉摜�͉��B�����ł����ƕ`���Ă�*/
#define TAMA_RED_PATH			TEXT(".\\IMAGE\\TAMA\\tama_image_red.png")		//�Ԓe�̉摜
#define TAMA_GREEN_PATH			TEXT(".\\IMAGE\\TAMA\\tama_image_green.png")	//�e�̉摜
#define TAMA_BLUE_PATH			TEXT(".\\IMAGE\\TAMA\\tama_image_blue.png")	//�Βe�̉摜
#define TAMA_YELLOW_PATH		TEXT(".\\IMAGE\\TAMA\\tama_image_yellow.png")	//���e�̉摜

#define TAMA_DIV_WIDTH		32	//�摜�𕪊����镝�T�C�Y
#define TAMA_DIV_HEIGHT		32	//�摜�𕪊����鍂���T�C�Y

#define TAMA_DIV_TATE		3	//�摜���c�ɕ������鐔
#define TAMA_DIV_YOKO		1	//�摜�����ɕ������鐔

#define TAMA_DIV_NUM	TAMA_DIV_TATE * TAMA_DIV_YOKO	//�摜�𕪊����鑍��

//�G�}�b�v
//#define GAME_MAP_BK_PATH TEXT(".\\IMAGE\\�Q�[���w�i.png")
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

#define START_ERR_TITLE		TEXT("�X�^�[�g�ʒu�G���[")
#define START_ERR_CAPTION	TEXT("�X�^�[�g�ʒu�����܂��Ă��܂���")


//�G���h��ʉ摜
#define IMAGE_END_COMP_ROGO_PATH TEXT(".\\IMAGE\\clearROGO.png")
#define IMAGE_END_COMP_CNT 1
#define IMAGE_END_COMP_CNT_MAX 30

#define IMAGE_END_FAIL_ROGO_PATH TEXT(".\\IMAGE\\overROGO.png")
#define IMAGE_END_FAIL_CNT 1
#define IMAGE_END_FAIL_CNT_MAX 30
//����{�^�����������Ƃ�
#define MSG_CLOSE_TITLE TEXT("�I�����b�Z�[�W")
#define MSG_CLOSE_CAPTION TEXT("�Q�[�����I�����܂����H")

enum GAME_MAP_KIND
{
	n = -1, //none
	s = 0, //�X�^�[�g
	e = 1 //�G�i���j

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
};	//�L�����N�^�[�̃X�s�[�h

enum CHARA_RELOAD {
	CHARA_RELOAD_LOW = 60,
	CHARA_RELOAD_MIDI = 30,
	CHARA_RELOAD_HIGH = 15
};	//�L�����N�^�[�̃����[�h

enum TAMA_COLOR {
	TAMA_COLOR_RED,
	TAMA_COLOR_GREEN,
	TAMA_COLOR_BLUE,
	TAMA_COLOR_YELLOW
};//�e�̐F

//int�^��POINT�\����
typedef struct STRUCT_I_POINT
{
	int x = -1;
	int y = -1;
}iPOINT;

//�}�E�X�\����
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
	int nowImageKind; //�e�̌��݂̉摜
	int changeImageCnt;	//�摜��ς��邽�߂̃J�E���g
	int changeImageCntMAX; //�摜��ς��邽�߂̃J�E���g(MAX)
	int speed; //�X�s�[�h

	RECT coll;
	iPOINT collBeforePt;
}TAMA;	//�e�̍\����


typedef struct STRUCT_CHARA
{
	IMAGE image;
	int speed;
	int CenterX;				//���SX
	int CenterY;				//���SY

	MUSIC musicShot;			//�v���C���[�̔��ˉ�

	BOOL CanShot;				//�V���b�g�ł��邩
	int ShotReLoadCnt;			//�V���b�g�����[�h����
	int ShotReLoadCntMAX=10;		//�V���b�g�����[�h����(MAX)

	BOOL PlayerMISS;//�v���C���[���G�Ɠ����������ǂ���
	int PlayerReLoadCnt;//�v���C���[�̃����[�h����
	int PlayerReLoadCntMAX = 180;//�v���C���[�̃����[�h�ɂ����鎞�ԁi��3�b�j

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

	int Damage = 0;//���݂܂łɎ󂯂��e�̌�
	int DamageMAX = 100;//100�����Ă���I���
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
//FPS�֘A
int StartTimeFps;
int CountFps;
float CalcFps;
int SampleNumFps = GAME_FPS;

//�L�[�{�[�h���͎擾
char AllKeyState[KEY_CODE_KIND] = { '\0' };
char OldAllKeyState[KEY_CODE_KIND] = { '\0' };

//�}�E�X�̍��W���擾
MOUSE mouse;

//�Q�[���֘A
int GameScene; //�Q�[���V�[�����Ǘ�
int GameEndKind;

//�v���C���[�֘A
CHARA player; //�Q�[���̃L����
//CHARA enemy;
ENEMY enemy;

int TamaColorKind;//�e�̐F�Ǘ�

//�摜�֌W
IMAGE ImageTitleROGO; //�^�C�g�����S
IMAGE ImageTitleBack; //�^�C�g���w�i

IMAGE_BACK ImageBack[IMAGE_BACK_NUM]; //�v���C�w�i

IMAGE_BLINK ImageEndFAIL; //�G���h���S
IMAGE_BLINK ImageEndCOMP; //�G���h���S


//���y�֌W
MUSIC TITLE;
MUSIC PLAY_BGM;
MUSIC END_FAIL_BGM;
MUSIC END_COMP_BGM;

//�t�H���g
FONT FontTanu32;

GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]
{
	//�@0,1,2,3,4,5,6,7,8,9,0,1,2,
		n,n,n,n,n,n,n,n,n,n,n,n,//0
		n,n,n,n,n,n,n,n,n,n,n,n,//1
		n,n,n,n,n,n,n,n,n,n,n,n,//2
		n,n,n,n,n,n,e,n,n,n,n,n,//3
		n,n,n,n,n,n,n,n,n,n,n,n,//4
		n,n,n,n,n,n,n,n,n,n,n,n,//5
		n,n,n,n,n,n,n,n,n,n,n,n,//6
		n,n,n,n,n,s,n,n,n,n,n,n,//7
		n,n,n,n,n,n,n,n,n,n,n,n//8
		//�e�X�g�p
};
GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
MAP_CHIP mapChip;
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
iPOINT startPt{ -1,-1 };
//IMAGE MapBack;
RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

int player_Life;
int StartTime;//�v���C�J�n���̌��ݎ���
int NowPlayTime;

//########## �v���g�^�C�v�錾 ##########
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
//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				//log.txt���o�͂��Ȃ�
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�w��̐��l�ŃE�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR);				//�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE);								//��A�N�e�B�u�ł����s����
	SetWindowIconID(IDI_ICON1);
	SetWindowUserCloseEnableFlag(FALSE);


	if (DxLib_Init() == -1) { return -1; }	//�c�w���C�u��������������

	//�摜��ǂݍ���
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }
	//���y��ǂݍ���
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }


	//�t�H���g���ꎞ�I�ɃC���X�g�[��
	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }
	//�t�H���g�n���h�����쐬
	if (MY_FONT_CREATE() == FALSE) { return -1; }

	//����̓ǂݍ���
	//handle = LoadGraph(MOVIE_PATH);

	GameScene = GAME_SCENE_START; //�Q�[���V�[���̓X�^�[�g��ʂ���
	SetDrawScreen(DX_SCREEN_BACK); //Draw�n�֐��͗���ʂɕ`��
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

			//	/*�����œG�̏�񂢂��*/
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
	//�������[�v
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��
		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		//��ʂ̕���{�^���������ꂽ��
		if (GetWindowUserCloseFlag(TRUE))
		{
			SetMouseDispFlag(TRUE);
			//�I���_�C�A���O��\��
			int Ret = MessageBox(GetMainWindowHandle(), MSG_CLOSE_CAPTION, MSG_CLOSE_TITLE, MB_YESNO | MB_ICONASTERISK);
			if (Ret == IDYES) { break; } //YES�Ȃ�Q�[���I��
		}
		MY_ALL_KEYDOWN_UPDATE(); //�����Ă���L�[��Ԃ��擾

		MY_MOUSE_UPDATE(); //�}�E�X�̏�Ԃ��擾

		MY_FPS_UPDATE(); //fps�̏����i�X�V�j

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

	DxLib_End();	//�c�w���C�u�����g�p�̏I������

	//DeleteGraph(handle);	//����̍폜

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
	//BGM������Ă��Ȃ��Ȃ�
	if (CheckSoundMem(TITLE.handle) == 0)
	{
		ChangeVolumeSoundMem(GAME_SOUND_VOLUME, TITLE.handle); //50%�̉���
		PlaySoundMem(TITLE.handle, DX_PLAYTYPE_LOOP); //���[�v�Đ�
	}
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		//BGM������Ă�����
		if (CheckSoundMem(TITLE.handle) != 0)
		{
			StopSoundMem(TITLE.handle); //�~�߂�
		}
		//�L�[�{�[�h�p��
		//�v���C���[�̒��S�ʒu���v�Z����
		//player.CenterX = startPt.x;
		//player.CenterY = startPt.y;

		////�v���C���[�̉摜�̈ʒu��ݒ肷��
		//player.image.x = player.CenterX;
		//player.image.y = player.CenterY;

		////�v���C���[�̓�����ȑO�̈ʒu��ݒ肷��
		//player.collBeforePt.x = player.CenterX;
		//player.collBeforePt.y = player.CenterY;
		/*�����܂�*/

		//�}�E�X�p��
		SetMouseDispFlag(FALSE);

		player.CenterX = startPt.x;
		player.CenterY = startPt.y;

		player.image.x = player.CenterX;
		player.image.y = player.CenterY;

		player.collBeforePt.x = player.CenterX;
		player.collBeforePt.y = player.CenterY;

		SetMousePoint(player.image.x, player.image.y);

		/*�����܂�*/
		StartTime = GetNowCount(); //���݂̌o�ߎ��Ԃ��擾
		player_Life = 3; //�v���C���[�̃��C�t��ݒ�
		player.PlayerMISS = FALSE;//�v���C���[�ƓG�͂܂��������ĂȂ�����FALSE
		for (int cnt = 0; cnt < TAMA_MAX; cnt++)
		{
			player.tama[cnt].IsDraw = FALSE;
		}
		GameEndKind = GAME_END_FAIL;
		TamaColorKind = TAMA_COLOR_RED;//�����͐�

		enemy.rect.left = GAME_WIDTH / 2 - enemy.image.width / 2;		//�{�[����X�ʒu�͉�ʂ̒���
		enemy.rect.top = GAME_HEIGHT / 2 - enemy.image.height / 2;		//�{�[����Y�ʒu�͉�ʂ̒���
		enemy.rect.right = enemy.rect.left + enemy.image.width;				//�{�[���̕���������
		enemy.rect.bottom = enemy.rect.top + enemy.image.height;				//�{�[���̍�����������

		enemy.TateSpeed = ENEMY_SPEED;				//�c�̑�����������
		enemy.YokoSpeed = ENEMY_SPEED;				//���̑�����������
		enemy.IsDraw = FALSE;							//�{�[����\�����Ȃ�

		//MY_PLAY_INIT(); //�Q�[��������

		GameScene = GAME_SCENE_PLAY; //�v���C��ʂɑJ��

		return;
	}
	return;
}

VOID MY_START_DRAW(VOID)
{
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT/2, GetColor(0, 255, 255), TRUE);
	DrawBox(0, GAME_HEIGHT/2, GAME_WIDTH, GAME_HEIGHT, GetColor(255, 0, 255), TRUE);

	DrawString(0, 0, "�X�^�[�g��ʁi�G���^�[�L�[�������Ă��������j", GetColor(255, 255, 255));
	DrawGraph(ImageTitleROGO.x, ImageTitleROGO.y, ImageTitleROGO.handle, TRUE);
	
	DrawStringToHandle(GAME_WIDTH/4, GAME_HEIGHT/2+50, "�G���^�[�L�[�������ĂˁI", GetColor(255, 255, 255), FontTanu32.handle);

	return;
}

VOID MY_PLAY_INIT(VOID)
{
	//player_Life = 3; //�v���C���[�̃��C�t��ݒ�

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
	DrawString(0, 0, "�v���C���(esc�ŃG���h���)", GetColor(255, 255, 255));

	return;
}

VOID MY_PLAY_PROC(VOID)
{
	//BGM������Ă��Ȃ��Ȃ�
	if (CheckSoundMem(PLAY_BGM.handle) == 0)
	{
		ChangeVolumeSoundMem(GAME_SOUND_VOLUME, PLAY_BGM.handle); //50%�̉���
		PlaySoundMem(PLAY_BGM.handle, DX_PLAYTYPE_LOOP); //���[�v�Đ�
	}
	if (MY_KEY_UP(KEY_INPUT_ESCAPE) == TRUE)
	{
		if (CheckSoundMem(PLAY_BGM.handle) != 0)
		{
			StopSoundMem(PLAY_BGM.handle);
		}
		GameScene = GAME_SCENE_END; //�v���C��ʂɑJ��

		return;
	}


	//�}�E�X����
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

	//�����蔻��
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

	RECT TamaRect[TAMA_MAX];//�e�o���Ƃ��ɒl������

	if (enemy.image.x > GAME_WIDTH || enemy.image.y > GAME_HEIGHT ||
		enemy.image.x + enemy.image.width < 0 || enemy.image.y + enemy.image.height < 0) //�G����ʊO�ɏo����G���h
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

	//�V���b�g
	if (MY_MOUSE_DOWN(MOUSE_INPUT_LEFT) == TRUE)
	{
		//�V���b�g�����Ă�Ƃ�
		if (player.CanShot == TRUE)
		{
		
			PlaySoundMem(player.musicShot.handle, DX_PLAYTYPE_BACK);
			player.CanShot = FALSE;

			//�󂢂Ă���X���b�g�ŁA�e�̕`�������
			for (int cnt = 0; cnt < TAMA_MAX; cnt++)
			{
				if (player.tama[cnt].IsDraw == FALSE)
				{
					//�c����
					player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;
					player.tama[cnt].y = player.image.y;

					//* ���V���[�e�B���O�i�v���C���[�E�j�̏ꍇ *//
					//player.tama[cnt].x = player.image.x;
					//player.tama[cnt].y = player.image.y + 40 - player.tama[cnt].height / 2;


					//�e�����蔻��
					
					TamaRect[cnt].left = player.tama[cnt].x + 40;
					TamaRect[cnt].top = player.tama[cnt].y + 40;
					TamaRect[cnt].right = player.tama[cnt].x + player.tama[cnt].width - 40;
					TamaRect[cnt].bottom = player.tama[cnt].y + player.tama[cnt].height - 40;
					//DrawBox(TamaRect[cnt].left, TamaRect[cnt].top, TamaRect[cnt].right, TamaRect[cnt].bottom, GetColor(255, 0, 255), TRUE);

					//�F�w��
					//nowImageKind = TAMA_COLOR;

					//�e��`�悷��
					player.tama[cnt].IsDraw = TRUE;

					break;
				}
			}
		}
	}

	//�V���b�g�����ĂȂ��Ƃ�
	if (player.CanShot == FALSE)
	{
		//�����[�h���Ԃ��I������Ƃ�
		if (player.ShotReLoadCnt == player.ShotReLoadCntMAX)
		{
			player.ShotReLoadCnt = 0;
			player.CanShot = TRUE;		//�ĂуV���b�g�ł���
		}

		player.ShotReLoadCnt++;	//�����[�h����
	}

	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{


		/* �c�X�N���[��STG�̔w�i�̗���� */

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

	//�G�̓���
	//if (enemy.IsDraw == FALSE)	//�{�[������\���̂Ƃ�
	//{
	//	if (KeyDownState[VK_RETURN] == TRUE)	//�G���^�[�L�[����������(����̈ʒu�ɒ�������J�n�ł�������)
	//	{
	//		enemy.IsDraw = TRUE;	//�{�[���\��
	//	}
	//}

	if (enemy.IsDraw == TRUE)
	{
		/*�������蔻��̃|�C���g
		�@�E�ړ�����ꏊ����肵�āA�������Ă��邩�`�F�b�N���邱�ƁI
		 �@���������Ă���̂ɁA�X�s�[�h����������Ɓu�ђʁv���Ă��܂����Ƃ�
	�@	   ���v���O�������ŁA�{�[���̈ʒu�ɁA�{�[���̃X�s�[�h���������Ă���̂��A����̏���
		*/

		//�{�[������ʊO�ɂ߂荞�񂾏ꍇ(��)
		if (enemy.rect.left - enemy.YokoSpeed < 0)
		{
			enemy.rect.left = 0 + 1;
			enemy.rect.right = enemy.rect.left + enemy.image.width + 1;

			enemy.YokoSpeed = -enemy.YokoSpeed;	//�����𔽓]������
		}

		//�{�[������ʊO�ɂ߂荞�񂾏ꍇ(�E)
		if (enemy.rect.right + enemy.YokoSpeed > GAME_WIDTH)
		{
			enemy.rect.left = GAME_WIDTH - enemy.image.width - 1;
			enemy.rect.right = enemy.rect.left + enemy.image.width - 1;

			enemy.YokoSpeed = -enemy.YokoSpeed;	//�����𔽓]������
		}

		//�{�[������ʊO�ɂ߂荞�񂾏ꍇ(��)
		if (enemy.rect.top - enemy.TateSpeed < 0)
		{
			enemy.rect.top = 0 + 1;
			enemy.rect.bottom = enemy.rect.top + enemy.image.height;

			enemy.TateSpeed = -enemy.TateSpeed;	//�����𔽓]������
		}

		//�{�[������ʊO�ɂ߂荞�񂾏ꍇ(��)
		if (enemy.rect.bottom + enemy.TateSpeed > GAME_HEIGHT)
		{
			enemy.rect.top = GAME_HEIGHT - enemy.image.height - 1;
			enemy.rect.bottom = enemy.rect.top + enemy.image.height - 1;

			enemy.TateSpeed = -enemy.TateSpeed;	//�����𔽓]������
		}


		//��ʂ̉E����Y�ʒu���A��ʂ̉E����Y�ʒu�����傫���Ƃ�(�G�ƃv���C���[�����������瑦��)
		if (MY_CHECK_RECT_COLL(enemy.rect,PlayerRect))
		{
				if (CheckSoundMem(PLAY_BGM.handle) != 0)
				{
					StopSoundMem(PLAY_BGM.handle);
				}
				GameEndKind = GAME_END_COMP;
				GameScene = GAME_SCENE_END;
		}
		enemy.rect.left += enemy.YokoSpeed;	//�{�[���̍����X�ʒu���ړ�
		enemy.rect.right += enemy.YokoSpeed;	//�{�[���̉E����X�ʒu���ړ�

		enemy.rect.top += enemy.TateSpeed;	//�{�[���̍����Y�ʒu���ړ�
		enemy.rect.bottom += enemy.TateSpeed;	//�{�[���̉E����Y�ʒu���ړ�

	}


	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		if (player.tama[cnt].IsDraw == TRUE)//�e������Ƃ��������肷��
		{
			if(player.tama[cnt].x<enemy.image.x+ enemy.image.width &&
				player.tama[cnt].y<enemy.image.y+ enemy.image.height &&
				player.tama[cnt].x+ player.tama[cnt].width>enemy.image.x &&
				player.tama[cnt].y+ player.tama[cnt].height>enemy.image.y)/*�ex*/
			{
				DrawBox(enemy.image.x, enemy.image.y, enemy.image.x + 10, enemy.image.y + 10, GetColor(0, 0, 255), FALSE);
				//������������œ����蔻�蓮����
			}
		}

	}


	//if (MY_CHECK_RECT_COLL(TamaRect, EnemyRect) == TRUE)
	//{
	//	if (map[tate][yoko].kind == e)
	//		map[tate][yoko].kind = n;//�G������������
	//}

	//if (MY_CHECK_RECT_COLL(PlayerRect, EnemyRect) == TRUE)
	//{

	//	if(player.PlayerMISS == FALSE)
	//	{
	//		//�_���[�WSE
	//		--player_Life;
	//		player.PlayerMISS = TRUE;
	//		//���X�|�[�������~����
	//	}//���O�ɓ������ĂȂ��ꍇ�Ƀ_���[�W����

	//}
	//if (player.PlayerMISS == TRUE)//�����[�h�̖��G����
	//{
	//	//�����[�h���Ԃ��I������Ƃ�
	//	if (player.PlayerReLoadCnt == player.PlayerReLoadCntMAX)
	//	{
	//		player.PlayerReLoadCnt = 0;
	//		player.PlayerMISS = FALSE;
	//	}

	//	player.PlayerReLoadCnt++;	//�����[�h����
	//}

	if (player_Life < 0) //���C�t�������Ȃ�����Q�[���I�[�o�[
	{
		if (CheckSoundMem(PLAY_BGM.handle) != 0)
		{
			StopSoundMem(PLAY_BGM.handle);
		}
		//�����Ń^�C�}�[���Z�b�g
		GameEndKind = GAME_END_FAIL;
		GameScene = GAME_SCENE_END;
		return;
	}

	NowPlayTime = GetNowCount();
	//if(NowPlayTime-StartTime>=30000&&player_Life>0) //30�b�o������N���A
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
		GameEndKind = GAME_END_COMP; //����FAIL�����Ȃ�����d���Ȃ�
		GameScene = GAME_SCENE_END;
		return;
	} /*�f�o�b�O�p*/

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
			//	GetColor(255, 255, 255), "�w�i�摜 : %d", num + 1
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

	DrawGraph(enemy.image.x, enemy.image.y, enemy.image.handle, TRUE); //�v���C���[�\��
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE); //�v���C���[�\��
	if (player.PlayerMISS == TRUE)//���X�|�[����
	{
		//������_�ł�����
		DrawBox(player.image.x, player.image.y, player.image.x + 10, player.image.y + 10, GetColor(255, 0, 0), TRUE);
	}

	//�e�̏��𐶐�
	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		//�`��ł���e�̏���
		if (player.tama[cnt].IsDraw == TRUE)
		{
			//�e��`�悷��
			DrawGraph(
				player.tama[cnt].x,
				player.tama[cnt].y,
				player.tama[cnt].handle[player.tama[cnt].nowImageKind],	//���݂̉摜�̎�ނɂ������n���h��
				TRUE);
			/*nowImageKind�ɂǂ̐F�����邩���p�X���w�肷��i�H�j*/


			//�e�̕\���t���[���𑝂₷
			if (player.tama[cnt].changeImageCnt < player.tama[cnt].changeImageCntMAX)
			{
				player.tama[cnt].changeImageCnt++;
			}
			else
			{
				//���ݕ\�����Ă���e�̎�ނ��A�܂�����Ƃ�
				if (player.tama[cnt].nowImageKind < TAMA_DIV_NUM - 1)	//-1���Ȃ��ƁA�Ō�̎�ނ̂Ƃ���++����Ă��܂�
				{
					player.tama[cnt].nowImageKind++;	//�e�����̎�ނɂ���
				}
				else
				{
					player.tama[cnt].nowImageKind = 0;	//�e�̎�ނ����Z�b�g����
				}

				player.tama[cnt].changeImageCnt = 0;
			}

			//�e����Ɉړ�������i�c�V���[�e�B���O�j
			if (player.tama[cnt].y < 0)
			{
				player.tama[cnt].IsDraw = FALSE;	//�`��I��
			}
			else
			{
				player.tama[cnt].y -= player.tama[cnt].speed;
			}

			//* ���V���[�e�B���O�ŉE���獶�ɔ�΂��ꍇ *//

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

	//�f�o�b�O�p�i���N���b�N�E���Ă邩�j
	if (MY_MOUSE_DOWN(MOUSE_INPUT_LEFT) == TRUE)
	{
		DrawBox(player.image.x, player.image.y, player.image.x + 10, player.image.y + 10, GetColor(0, 255, 0),TRUE);
	}

	DrawFormatString(
		GAME_WIDTH - 300,
		GAME_HEIGHT - 15,
		GetColor(255, 0, 0), "�c�莞��: %d �b", (PLAY_TIME - (NowPlayTime-StartTime))/1000);

	DrawFormatString(
		GAME_WIDTH - 550,
		GAME_HEIGHT - 15,
		GetColor(255, 0, 0), "���C�t: %d ", player_Life);


	
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
			ChangeVolumeSoundMem(GAME_SOUND_VOLUME, END_COMP_BGM.handle); //50%�̉���
			PlaySoundMem(END_COMP_BGM.handle, DX_PLAYTYPE_LOOP); //���[�v�Đ�
		}
		//���S
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
			ChangeVolumeSoundMem(GAME_SOUND_VOLUME, END_FAIL_BGM.handle); //50%�̉���
			PlaySoundMem(END_FAIL_BGM.handle, DX_PLAYTYPE_LOOP); //���[�v�Đ�
		}

		//���S
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

		//DrawStringToHandle(GAME_WIDTH / 2, GAME_HEIGHT / 2, "���𐔁F%d ��/�S4�⒆", seikai, GetColor(255, 0, 0), FontHandle);
		//DrawFormatString(
		//GAME_WIDTH,
		//GAME_HEIGHT,
		//GetColor(255, 255, 255), "���𐔁F%d ��/�S4�⒆", seikai);
		DrawStringToHandle(30, 330, "�~�b�V�����R���v���[�g�I�@esc�L�[�Ń^�C�g���ɂ��ǂ��", GetColor(255, 0, 0), FontTanu32.handle);
		if (ImageEndCOMP.IsDraw == TRUE)
		{
			DrawGraph(ImageEndCOMP.image.x, ImageEndCOMP.image.y, ImageEndCOMP.image.handle, TRUE);
		}
		break;

	case GAME_END_FAIL:
		DrawStringToHandle(GAME_WIDTH / 4, 500, "�c�O�I�@esc�L�[�Ń^�C�g���ɖ߂��", GetColor(0, 0, 255), FontTanu32.handle);
		if (ImageEndFAIL.IsDraw == TRUE)
		{
			DrawGraph(ImageEndFAIL.image.x, ImageEndFAIL.image.y, ImageEndFAIL.image.handle, TRUE);
		}

		break;
	}

	DrawString(0, 0, "�G���h���(�G�X�P�[�v�L�[�������Ă��������B)", GetColor(255, 255, 255));

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


	//�e�����i���j
	int tamaRedRes = LoadDivGraph(
		TAMA_RED_PATH,/*�e�̐F�i�����ł̓J���[���Ƃɉ摜��ʂɂ��Ă�j*/
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
		//�p�X���R�s�[
		strcpyDx(player.tama[cnt].path, TEXT(TAMA_RED_PATH));//�Ԃ݂̂̒e�摜���p�X�œn���Ă�B�����̂��������Ă݂邩

		for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++)
		{
			//�n���h�����R�s�[
			player.tama[cnt].handle[i_num] = player.tama[0].handle[i_num];
		}

		//�����R�s�[
		player.tama[cnt].width = player.tama[0].width;

		//�������R�s�[
		player.tama[cnt].height = player.tama[0].height;

		//�e��X�ʒu�̓v���C���[�̒��S���甭��
		player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;

		//�e��Y�ʒu�̓v���C���[�̏㕔�����甭��
		player.tama[cnt].y = player.image.y;

		//�e�͍ŏ��͔�\��
		player.tama[cnt].IsDraw = FALSE;

		//�e�̕\���J�E���g��0�ɂ���
		player.tama[cnt].changeImageCnt = 0;

		//�e�̕\���J�E���gMAX��ݒ肷��
		player.tama[cnt].changeImageCntMAX = TAMA_CHANGE_MAX;

		//���݂̉摜�̎�ނ�����������
		player.tama[cnt].nowImageKind = 0;

		//�e�̃X�s�[�h��ݒ肷��
		player.tama[cnt].speed = CHARA_SPEED_LOW;


		//player.ShotReLoadCntMAX = 5;//�e�̃����[�h���ԁi�t���[�����j
	}

	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);
	player.image.handle = LoadGraph(player.image.path);

	if (player.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);	//�摜�̕��ƍ������擾
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;		//���E��������
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;		//�㉺��������
	player.CenterX = player.image.x + player.image.width / 2;		//�摜�̉��̒��S��T��
	player.CenterY = player.image.y + player.image.height / 2;		//�摜�̏c�̒��S��T��


	//�}�b�v

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

	/*�G�P��*/
	int enemyRedRes = LoadDivGraph(
		TAMA_RED_PATH,/*�e�̐F�i�����ł̓J���[���Ƃɉ摜��ʂɂ��Ă�j*/
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
		//�p�X���R�s�[
		strcpyDx(player.tama[cnt].path, TEXT(TAMA_RED_PATH));//�Ԃ݂̂̒e�摜���p�X�œn���Ă�B�����̂��������Ă݂邩

		for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++)
		{
			//�n���h�����R�s�[
			player.tama[cnt].handle[i_num] = player.tama[0].handle[i_num];
		}

		//�����R�s�[
		player.tama[cnt].width = player.tama[0].width;

		//�������R�s�[
		player.tama[cnt].height = player.tama[0].height;

		//�e��X�ʒu�̓v���C���[�̒��S���甭��
		player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;

		//�e��Y�ʒu�̓v���C���[�̏㕔�����甭��
		player.tama[cnt].y = player.image.y;

		//�e�͍ŏ��͔�\��
		player.tama[cnt].IsDraw = FALSE;

		//�e�̕\���J�E���g��0�ɂ���
		player.tama[cnt].changeImageCnt = 0;

		//�e�̕\���J�E���gMAX��ݒ肷��
		player.tama[cnt].changeImageCntMAX = TAMA_CHANGE_MAX;

		//���݂̉摜�̎�ނ�����������
		player.tama[cnt].nowImageKind = 0;

		//�e�̃X�s�[�h��ݒ肷��
		player.tama[cnt].speed = CHARA_SPEED_LOW;
	}

	/*�w�i*/
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

	///* �c�p *//

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

	//* ���p *//

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

	//�G���h���S
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
	
	//�w�i
	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		DeleteGraph(ImageBack[0].image.handle);
	}

	//�e�폜
	for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++) { DeleteGraph(player.tama[0].handle[i_num]); }
	//�G�}�b�v
	//for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++)
	//{
	//	DeleteGraph(mapChip.handle[i_num]);
	//}

	DeleteGraph(player.image.handle); //�L����
	//for (int i_num = 0; i_num < IMAGE_PLAYER_NUM; i_num++)
	//{
	//	DeleteGraph(charaChip.handle[i_num]);
	//}
	DeleteGraph(ImageEndFAIL.image.handle); //�G���h���S
	DeleteGraph(ImageEndCOMP.image.handle); //�p�t�F���S
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

	//�v���C���[�̃V���b�g��
	strcpy_s(player.musicShot.path, MUSIC_PLAYER_SHOT_PATH);			//�p�X�̐ݒ�
	player.musicShot.handle = LoadSoundMem(player.musicShot.path);		//�ǂݍ���
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
//						//�����ɓG�ɓ��������Ƃ��̏��������Ă݂�
//						map[tate][yoko].kind = n;//�G������
//						//�|�������𑫂�
//					}
//				} /* �e�ƓG�����������Ƃ��i�܂����߂����j */
//			}
//
//
//		}
//	}
//	return FALSE;
//}��U����̂��Ƃ͍l���Ȃ�

//���̓����蔻��������ɂ������p�����蔻���邩�H

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