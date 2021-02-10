//���킩���Ă�o�O
//
//�܂��e�ƓG�͂��蔲����

//����邱��


//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include "resource.h"
#include "math.h"

#define GAME_WIDTH			800	//��ʂ̉��̑傫��
#define GAME_HEIGHT			600	//��ʂ̏c�̑傫��
#define GAME_COLOR			32	//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR		0	//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME	"�|�v�W�J���V���[�e�B���O"	//�E�B���h�E�̃^�C�g��

#define GAME_FPS 60 //FPS�̐��l

#define GAME_SOUND_VOLUME_PER 30	//%
#define GAME_SOUND_VOLUME 255 * GAME_SOUND_VOLUME_PER / 100		//���̃p�[�Z���g�̃{�����[��

#define PLAY_TIME_SECOND 30		//�b
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
#define MUSIC_PLAYER_MISS_PATH TEXT(".\\MUSIC\\se_maoudamashii_battle07.mp3")
#define MUSIC_LOAD_ERR_TITLE TEXT("���y�ǂݍ��݃G���[")

//�e�̐ݒ�
#define TAMA_CHANGE_MAX		 5	//5�t���[���ڂŒe�̉摜��ς���
#define TAMA_MAX			16	//�ő�16���܂�
#define TAMA_KIND			4	//�e�̎��


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

//�G�摜
#define IMAGE_ENEMY_RED_PATH TEXT(".\\IMAGE\\enemyRed.png")
#define IMAGE_ENEMY_GREEN_PATH TEXT(".\\IMAGE\\enemyGreen.png")
#define IMAGE_ENEMY_BLUE_PATH TEXT(".\\IMAGE\\enemyBlue.png")
#define IMAGE_ENEMY_YELLOW_PATH TEXT(".\\IMAGE\\enemyYellow.png")



#define ENEMY_SPEED 2
#define ENEMY_MAX 20

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
	int Kind;	//�e�̎��

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
	int ShotReLoadCntMAX = 10;		//�V���b�g�����[�h����(MAX)

	MUSIC musicMiss;//�G�ɓ��������Ƃ���SE

	BOOL PlayerMISS;//�v���C���[���G�Ɠ����������ǂ���
	int PlayerReLoadCnt;//�v���C���[�̃����[�h����
	int PlayerReLoadCntMAX = 180;//�v���C���[�̃����[�h�ɂ����鎞�ԁi��3�b�j

	TAMA moto[TAMA_KIND];
	TAMA tama[TAMA_MAX];

	RECT coll;
	iPOINT collBeforePt;

}CHARA;

typedef struct STRUCT_ENEMY
{
	IMAGE image;

	RECT rect;
	//int YokoSpeed;
	//int TateSpeed;
	BOOL IsDraw;

	int Damage = 0;//���݂܂łɎ󂯂��e�̌�
	int DamageMAX = 3;//�񓖂Ă���I���
	
	int Kind;//�����̐F
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
//typedef struct STRUCT_MAP_IMAGE
//{
//	char path[PATH_MAX];
//	int handle[MAP_DIV_NUM];
//	int kind[MAP_DIV_NUM];
//	int width;
//	int height;
//}MAP_CHIP;

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

ENEMY enemy[ENEMY_MAX];

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

//GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]
//{
//	//�@0,1,2,3,4,5,6,7,8,9,0,1,2,
//		n,n,n,n,n,n,n,n,n,n,n,n,//0
//		n,n,n,n,n,n,n,n,n,n,n,n,//1
//		n,n,n,n,n,n,n,n,n,n,n,n,//2
//		n,n,n,n,n,n,e,n,n,n,n,n,//3
//		n,n,n,n,n,n,n,n,n,n,n,n,//4
//		n,n,n,n,n,n,n,n,n,n,n,n,//5
//		n,n,n,n,n,n,n,n,n,n,n,n,//6
//		n,n,n,n,n,s,n,n,n,n,n,n,//7
//		n,n,n,n,n,n,n,n,n,n,n,n//8
//		//�e�X�g�p
//};
//GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
//MAP_CHIP mapChip;
//MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
iPOINT startPt{ -1,-1 };
//IMAGE MapBack;
//RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

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

VOID EnemyAtariKeisan(ENEMY* e);
VOID TamaAtariKeisan(TAMA* tama);

VOID EnemyAtariDelete(ENEMY* e);


//BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player);
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
	if (MY_MOUSE_UP(MOUSE_INPUT_LEFT) == TRUE
		|| MY_MOUSE_UP(MOUSE_INPUT_MIDDLE) == TRUE
		|| MY_MOUSE_UP(MOUSE_INPUT_RIGHT) == TRUE)
	{
		//BGM������Ă�����
		if (CheckSoundMem(TITLE.handle) != 0)
		{
			StopSoundMem(TITLE.handle); //�~�߂�
		}

		//�}�E�X�p��
		SetMouseDispFlag(FALSE);

		startPt.x = GAME_WIDTH / 2;
		startPt.y = GAME_HEIGHT;
		//�X�^�[�g�n�_�������Ō��߂�i�^�񒆂�艺�����肪�����ȁj

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
		player.PlayerMISS = TRUE;
		for (int cnt = 0; cnt < TAMA_MAX; cnt++)
		{
			player.tama[cnt].IsDraw = FALSE;
		}
		GameEndKind = GAME_END_FAIL;
		TamaColorKind = TAMA_COLOR_RED;//�����͐�

		//MY_PLAY_INIT(); //�Q�[��������

		GameScene = GAME_SCENE_PLAY; //�v���C��ʂɑJ��

		return;
	}
	return;
}

VOID MY_START_DRAW(VOID)
{
	DrawBox(0, 0, GAME_WIDTH, GAME_HEIGHT / 2, GetColor(0, 255, 255), TRUE);
	DrawBox(0, GAME_HEIGHT / 2, GAME_WIDTH, GAME_HEIGHT, GetColor(255, 0, 255), TRUE);

	DrawString(0, 0, "�X�^�[�g��ʁi�G���^�[�L�[�������Ă��������j", GetColor(255, 255, 255));
	DrawGraph(ImageTitleROGO.x, ImageTitleROGO.y, ImageTitleROGO.handle, TRUE);

	DrawStringToHandle(GAME_WIDTH / 4, GAME_HEIGHT / 2 + 50, "�N���b�N�ŃX�^�[�g�I", GetColor(255, 255, 255), FontTanu32.handle);

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

	BOOL IsMove = TRUE;

	//if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	//{
	//	player.CenterX = player.collBeforePt.x;
	//	player.CenterY = player.collBeforePt.y;
	//	SetMousePoint(player.collBeforePt.x, player.collBeforePt.y);

	//	IsMove = FALSE;
	//}
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


	//RECT TamaRect[TAMA_MAX] = {0,0,0,0};//�e�o���Ƃ��ɒl������

	//if (enemy.image.x > GAME_WIDTH || enemy.image.y > GAME_HEIGHT ||
	//	enemy.image.x + enemy.image.width < 0 || enemy.image.y + enemy.image.height < 0) //�G����ʊO�ɏo����G���h
	//{
	//	if (CheckSoundMem(PLAY_BGM.handle) != 0)
	//	{
	//		StopSoundMem(PLAY_BGM.handle);
	//	}
	//	SetMouseDispFlag(TRUE);
	//	GameEndKind = GAME_END_FAIL;
	//	GameScene = GAME_SCENE_END;
	//	return;
	//}

	//�V���b�g
	if (MY_MOUSE_UP(MOUSE_INPUT_RIGHT) == TRUE)//�E�N���b�N�ŐF�ς�
	{
			TamaColorKind++;

			if (TamaColorKind > TAMA_COLOR_YELLOW)
			{
				TamaColorKind = TAMA_COLOR_RED;
			}
	}

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

					//�e�����蔻���t��
					TamaAtariKeisan(&player.tama[cnt]);

					//�F�w��
					for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++)
					{
						//�n���h�����R�s�[
						player.tama[cnt].handle[i_num] = player.moto[TamaColorKind].handle[i_num];	//�����R�s�[����
					}
					player.tama[cnt].Kind = TamaColorKind;	//�e�̎�ނ�ݒ莩�Ȑ\��������

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

	/* �c�X�N���[��STG�̔w�i�̗���� */
	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
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

	for (int i = 0; i < ENEMY_MAX; i++) 
	{
		//�G�̋����X�N���[��
		enemy[i].image.y += 1;
		enemy[i].image.x = (GAME_WIDTH / 2 - enemy[i].image.width / 2) + cos(enemy[i].image.y * DX_PI / 180 ) * 100;
		EnemyAtariKeisan(&enemy[i]);	//�����蔻����v�Z����֐�

		//���������Ƃ��i�G�ƃv���C���[�j
		if (player.PlayerMISS == FALSE)
		{
			//�����[�h���Ԃ��I������Ƃ�
			if (player.PlayerReLoadCnt == player.PlayerReLoadCntMAX)
			{
				player.PlayerReLoadCnt = 0;
				player.PlayerMISS = TRUE;		//�����Ԃ芮��
			}

			player.PlayerReLoadCnt++;	//�����[�h����
		}
		
		if (enemy[i].IsDraw == TRUE)
		{
			//�G�ƃv���C���[������������
			if (MY_CHECK_RECT_COLL(enemy[i].rect, PlayerRect))
			{
				if (player.PlayerMISS == TRUE)
				{
					player.PlayerMISS = FALSE;//���΂炭���G�ɂȂ�
					player_Life--;
					PlaySoundMem(player.musicMiss.handle, DX_PLAYTYPE_BACK);
				}

				if (player_Life < 1)
				{
					if (CheckSoundMem(PLAY_BGM.handle) != 0)
					{
						StopSoundMem(PLAY_BGM.handle);
					}
					GameEndKind = GAME_END_FAIL;
					GameScene = GAME_SCENE_END;
				}

			}
		}

	}

		////���������Ƃ��i�G�ƃv���C���[�j
		//if (player.PlayerMISS == FALSE)
		//{
		//	//�����[�h���Ԃ��I������Ƃ�
		//	if (player.PlayerReLoadCnt == player.PlayerReLoadCntMAX)
		//	{
		//		player.PlayerReLoadCnt = 0;
		//		player.PlayerMISS = TRUE;		//�����Ԃ芮��
		//	}

		//	player.PlayerReLoadCnt++;	//�����[�h����
		//}
		////�G�ƃv���C���[������������

		//if (MY_CHECK_RECT_COLL(enemy[i].rect, PlayerRect))
		//{
		//	if (player.PlayerMISS == TRUE)
		//	{
		//		player.PlayerMISS = FALSE;//���΂炭���G�ɂȂ�
		//		player_Life--;
		//		PlaySoundMem(player.musicMiss.handle, DX_PLAYTYPE_BACK);
		//	}

		//	if (player_Life < 1)
		//	{
		//		if (CheckSoundMem(PLAY_BGM.handle) != 0)
		//		{
		//			StopSoundMem(PLAY_BGM.handle);
		//		}
		//		GameEndKind = GAME_END_FAIL;
		//		GameScene = GAME_SCENE_END;
		//	}

		//}

	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		if (player.tama[cnt].IsDraw == TRUE)
		{
			//�e����Ɉړ�������i�c�V���[�e�B���O�j
			if (player.tama[cnt].y < 0)
			{
				player.tama[cnt].IsDraw = FALSE;	//�`��I��
			}
			else
			{
				player.tama[cnt].y -= player.tama[cnt].speed;
				TamaAtariKeisan(&player.tama[cnt]);	////�e�̓����蔻��
			}

			for (int i = 0; i < ENEMY_MAX; i++)
			{
				if (enemy[i].IsDraw == TRUE)
				{
					if (enemy[i].DamageMAX < 1)
					{
						EnemyAtariDelete(&enemy[i]);
					}

					if (MY_CHECK_RECT_COLL(player.tama[cnt].coll, enemy[i].rect))//�����Ŕ��肵�Ă邯�ǁc
					{
						if (enemy[i].Kind == player.tama[cnt].Kind)//���F�Ȃ�_���[�W����������
						{
							//enemy[i].Damage++;
							--enemy[i].DamageMAX;

							player.tama[cnt].IsDraw = FALSE;//�������������
							PlaySoundMem(player.musicMiss.handle, DX_PLAYTYPE_BACK);//�_���[�W��
						}
					}



				}
			}

		}

	}

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



	if (NowPlayTime - StartTime >= PLAY_TIME && player_Life > 0)
	{
		if (CheckSoundMem(PLAY_BGM.handle) != 0)
		{
			StopSoundMem(PLAY_BGM.handle);
		}
		GameEndKind = GAME_END_COMP;
		GameScene = GAME_SCENE_END;
		return;
	}

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

	//��ʂ̒��ɗ�����
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (enemy[i].image.y+ enemy[i].image.height >= 0)
		{
			enemy[i].IsDraw = TRUE;
		}
		else if (enemy[i].image.y >= GAME_HEIGHT)
		{
			enemy[i].IsDraw = FALSE;
		}

		if (enemy[i].DamageMAX < 1)
		{
			enemy[i].IsDraw = FALSE;//�������������
		}
	//�G���\���ł���Ƃ���
		if (enemy[i].IsDraw == TRUE)
		{

			DrawGraph(enemy[i].image.x, enemy[i].image.y, enemy[i].image.handle, TRUE); //�G�\��
			//DrawFormatString(enemy[i].image.x, enemy[i].image.y, GetColor(0, 0, 255), "�̂���:%d", enemy[i].DamageMAX - enemy[i].Damage);
			DrawFormatString(enemy[i].image.x, enemy[i].image.y, GetColor(0, 0, 255), "�̂���:%d", enemy[i].DamageMAX);
		


			if (TRUE)
			{
				DrawBox(
					enemy[i].image.x,
					enemy[i].image.y,
					enemy[i].image.x + enemy[i].image.width,
					enemy[i].image.y + enemy[i].image.height,
					GetColor(255, 0, 0),
					FALSE);//�G�̓����蔻��f�o�b�O�p
			}

		}
	}
	switch (TamaColorKind)
	{
	case TAMA_COLOR_RED:
		DrawCircle(player.CenterX,
			player.CenterY,
			player.image.height/2,
			GetColor(255, 0, 0),
			TRUE);//���o����e�̐F
		break;

	case TAMA_COLOR_GREEN:
		DrawCircle(player.CenterX,
			player.CenterY,
			player.image.height / 2,
			GetColor(0, 255, 0),
			TRUE);//���o����e�̐F
		break;

	case TAMA_COLOR_BLUE:
		DrawCircle(player.CenterX,
			player.CenterY,
			player.image.height / 2,
			GetColor(0, 0, 255),
			TRUE);//���o����e�̐F
		break;

	case TAMA_COLOR_YELLOW:
		DrawCircle(player.CenterX,
			player.CenterY,
			player.image.height / 2,
			GetColor(255, 255, 0),
			TRUE);//���o����e�̐F
		break;
	}

	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE); //�v���C���[�\��



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

			if (TRUE)
			{
				DrawBox(
					player.tama[cnt].coll.left,
					player.tama[cnt].coll.top,
					player.tama[cnt].coll.right,
					player.tama[cnt].coll.bottom,
					GetColor(0, 255, 0),
					FALSE);//�e�̓����蔻��f�o�b�O�p
			}

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
		}
	}

	DrawFormatString(
		GAME_WIDTH - 300,
		GAME_HEIGHT - 15,
		GetColor(255, 0, 0), "�c�莞��: %d �b", (PLAY_TIME - (NowPlayTime - StartTime)) / 1000);

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


		if (MY_MOUSE_UP(MOUSE_INPUT_LEFT) == TRUE)//�������u�Ԃ�
		{
			if (CheckSoundMem(END_FAIL_BGM.handle) != 0)
			{
				StopSoundMem(END_FAIL_BGM.handle);
			}
			else if (CheckSoundMem(END_COMP_BGM.handle) != 0)
			{
				StopSoundMem(END_COMP_BGM.handle);
			}

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
		DrawStringToHandle(30, 400, "�~�b�V�����R���v���[�g�I\n�N���b�N�Ń^�C�g���ɂ��ǂ��", GetColor(255, 0, 0), FontTanu32.handle);
		if (ImageEndCOMP.IsDraw == TRUE)
		{
			DrawGraph(ImageEndCOMP.image.x, ImageEndCOMP.image.y, ImageEndCOMP.image.handle, TRUE);
		}
		break;

	case GAME_END_FAIL:
		DrawStringToHandle(GAME_WIDTH / 4, 500, "�c�O�I�@�N���b�N�Ń^�C�g���ɖ߂��", GetColor(0, 0, 255), FontTanu32.handle);
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
		&player.moto[TAMA_COLOR_RED].handle[0]
	);

	if (tamaRedRes == -1)
	{
		MessageBox(GetMainWindowHandle(), TAMA_RED_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.moto[TAMA_COLOR_RED].handle[0], &player.moto[TAMA_COLOR_RED].width, &player.moto[TAMA_COLOR_RED].height);

	int tamaGreenRes = LoadDivGraph(
		TAMA_GREEN_PATH,/*�e�̐F�i�����ł̓J���[���Ƃɉ摜��ʂɂ��Ă�j*/
		TAMA_DIV_NUM, TAMA_DIV_TATE, TAMA_DIV_YOKO,
		TAMA_DIV_WIDTH, TAMA_DIV_HEIGHT,
		&player.moto[TAMA_COLOR_GREEN].handle[0]
	);

	if (tamaGreenRes == -1)
	{
		MessageBox(GetMainWindowHandle(), TAMA_GREEN_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.moto[TAMA_COLOR_GREEN].handle[0], &player.moto[TAMA_COLOR_GREEN].width, &player.moto[TAMA_COLOR_GREEN].height);

	int tamaBlueRes = LoadDivGraph(
		TAMA_BLUE_PATH,/*�e�̐F�i�����ł̓J���[���Ƃɉ摜��ʂɂ��Ă�j*/
		TAMA_DIV_NUM, TAMA_DIV_TATE, TAMA_DIV_YOKO,
		TAMA_DIV_WIDTH, TAMA_DIV_HEIGHT,
		&player.moto[TAMA_COLOR_BLUE].handle[0]
	);

	if (tamaBlueRes == -1)
	{
		MessageBox(GetMainWindowHandle(), TAMA_BLUE_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.moto[TAMA_COLOR_BLUE].handle[0], &player.moto[TAMA_COLOR_BLUE].width, &player.moto[TAMA_COLOR_BLUE].height);


	int tamaYellowRes = LoadDivGraph(
		TAMA_YELLOW_PATH,/*�e�̐F�i�����ł̓J���[���Ƃɉ摜��ʂɂ��Ă�j*/
		TAMA_DIV_NUM, TAMA_DIV_TATE, TAMA_DIV_YOKO,
		TAMA_DIV_WIDTH, TAMA_DIV_HEIGHT,
		&player.moto[TAMA_COLOR_YELLOW].handle[0]
	);

	if (tamaYellowRes == -1)
	{
		MessageBox(GetMainWindowHandle(), TAMA_YELLOW_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.moto[TAMA_COLOR_YELLOW].handle[0], &player.moto[TAMA_COLOR_YELLOW].width, &player.moto[TAMA_COLOR_YELLOW].height);

	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++)
		{
			//�n���h�����R�s�[
			player.tama[cnt].handle[i_num] = player.moto[TAMA_COLOR_RED].handle[i_num];	//�����R�s�[����
		}

		//�����R�s�[
		player.tama[cnt].width = player.moto[TAMA_COLOR_RED].width;

		//�������R�s�[
		player.tama[cnt].height = player.moto[TAMA_COLOR_RED].height;

		//�e��X�ʒu�̓v���C���[�̒��S���甭��
		player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;

		//�e��Y�ʒu�̓v���C���[�̏㕔�����甭��
		player.tama[cnt].y = player.image.y;

		//�e�̓����蔻���t��
		TamaAtariKeisan(&player.tama[cnt]);

		//�e�͍ŏ��͔�\��
		player.tama[cnt].IsDraw = FALSE;

		//�e�̕\���J�E���g��0�ɂ���
		player.tama[cnt].changeImageCnt = 0;

		//�e�̕\���J�E���gMAX��ݒ肷��
		player.tama[cnt].changeImageCntMAX = TAMA_CHANGE_MAX;

		//���݂̉摜�̎�ނ�����������
		player.tama[cnt].nowImageKind = 0;

		//�e�̃X�s�[�h��ݒ肷��
		player.tama[cnt].speed = CHARA_SPEED_HIGH;


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


	/*�G�P��*/
	strcpy_s(enemy[TAMA_COLOR_RED].image.path, IMAGE_ENEMY_RED_PATH);
	strcpy_s(enemy[TAMA_COLOR_GREEN].image.path, IMAGE_ENEMY_GREEN_PATH);
	strcpy_s(enemy[TAMA_COLOR_BLUE].image.path, IMAGE_ENEMY_BLUE_PATH);
	strcpy_s(enemy[TAMA_COLOR_YELLOW].image.path, IMAGE_ENEMY_YELLOW_PATH);

	enemy[TAMA_COLOR_RED].image.handle = LoadGraph(enemy[TAMA_COLOR_RED].image.path);
	enemy[TAMA_COLOR_GREEN].image.handle = LoadGraph(enemy[TAMA_COLOR_GREEN].image.path);
	enemy[TAMA_COLOR_BLUE].image.handle = LoadGraph(enemy[TAMA_COLOR_BLUE].image.path);
	enemy[TAMA_COLOR_YELLOW].image.handle = LoadGraph(enemy[TAMA_COLOR_YELLOW].image.path);


	if (enemy[0].image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	//�Ԃ̓G
	GetGraphSize(enemy[TAMA_COLOR_RED].image.handle, &enemy[TAMA_COLOR_RED].image.width, &enemy[TAMA_COLOR_RED].image.height);	//�摜�̕��ƍ������擾
	//enemy[TAMA_COLOR_RED].image.x = GAME_WIDTH / 2 - enemy[TAMA_COLOR_RED].image.width / 2;		//���E��������
	//enemy[TAMA_COLOR_RED].image.y = -10;
	
	/*�e�X�g�p�ɂ�����*/
	enemy[TAMA_COLOR_RED].image.x = 100;		//���E��������
	enemy[TAMA_COLOR_RED].image.y = TAMA_COLOR_RED * (-100);
	
	EnemyAtariKeisan(&enemy[TAMA_COLOR_RED]);	//�����蔻����v�Z����֐�
	enemy[TAMA_COLOR_RED].IsDraw = FALSE;
	enemy[TAMA_COLOR_RED].Kind = TAMA_COLOR_RED;	//�e�̎�ނ�ݒ莩�Ȑ\��������

	//�΂̓G
	GetGraphSize(enemy[TAMA_COLOR_GREEN].image.handle, &enemy[TAMA_COLOR_GREEN].image.width, &enemy[TAMA_COLOR_GREEN].image.height);	//�摜�̕��ƍ������擾
	//enemy[TAMA_COLOR_GREEN].image.x = GAME_WIDTH / 2 - enemy[TAMA_COLOR_GREEN].image.width / 2;		//���E��������
	//enemy[TAMA_COLOR_GREEN].image.y = enemy[0].image.height-10;

	enemy[TAMA_COLOR_GREEN].image.x = 200;		
	enemy[TAMA_COLOR_GREEN].image.y = TAMA_COLOR_GREEN * (-100);

	EnemyAtariKeisan(&enemy[TAMA_COLOR_GREEN]);	//�����蔻����v�Z����֐�
	enemy[TAMA_COLOR_GREEN].IsDraw = FALSE;
	enemy[TAMA_COLOR_GREEN].Kind = TAMA_COLOR_GREEN;	//�e�̎�ނ�ݒ莩�Ȑ\��������


	//�̓G
	GetGraphSize(enemy[TAMA_COLOR_BLUE].image.handle, &enemy[TAMA_COLOR_BLUE].image.width, &enemy[TAMA_COLOR_BLUE].image.height);	//�摜�̕��ƍ������擾
	//enemy[TAMA_COLOR_BLUE].image.x = GAME_WIDTH / 2 - enemy[TAMA_COLOR_BLUE].image.width / 2;		//���E��������
	//enemy[TAMA_COLOR_BLUE].image.y = enemy[0].image.height -20;

	enemy[TAMA_COLOR_BLUE].image.x = 300;		
	enemy[TAMA_COLOR_BLUE].image.y = TAMA_COLOR_BLUE * (-100);

	EnemyAtariKeisan(&enemy[TAMA_COLOR_BLUE]);	//�����蔻����v�Z����֐�
	enemy[TAMA_COLOR_BLUE].IsDraw = FALSE;
	enemy[TAMA_COLOR_BLUE].Kind = TAMA_COLOR_BLUE;	//�e�̎�ނ�ݒ莩�Ȑ\��������

	//���F�̓G
	GetGraphSize(enemy[TAMA_COLOR_YELLOW].image.handle, &enemy[TAMA_COLOR_YELLOW].image.width, &enemy[TAMA_COLOR_YELLOW].image.height);	//�摜�̕��ƍ������擾
	//enemy[TAMA_COLOR_YELLOW].image.x = GAME_WIDTH / 2 - enemy[TAMA_COLOR_YELLOW].image.width / 2;		//���E��������
	//enemy[TAMA_COLOR_YELLOW].image.y = enemy[0].image.height -30;

	enemy[TAMA_COLOR_YELLOW].image.x = 400;
	enemy[TAMA_COLOR_YELLOW].image.y = TAMA_COLOR_YELLOW*(-100);

	EnemyAtariKeisan(&enemy[TAMA_COLOR_YELLOW]);	//�����蔻����v�Z����֐�
	enemy[TAMA_COLOR_YELLOW].IsDraw = FALSE;
	enemy[TAMA_COLOR_YELLOW].Kind = TAMA_COLOR_YELLOW;	//�e�̎�ނ�ݒ莩�Ȑ\��������

	//int TekiIndex = 0;
	//GetGraphSize(enemy[TekiIndex].image.handle, &enemy[TekiIndex].image.width, &enemy[TekiIndex].image.height);	//�摜�̕��ƍ������擾
	//enemy[TekiIndex].image.x = GAME_WIDTH / 2 - enemy[TekiIndex].image.width / 2;		//���E��������
	//enemy[TekiIndex].image.y = -10;
	//EnemyAtariKeisan(&enemy[TekiIndex]);	//�����蔻����v�Z����֐�
	//enemy[TekiIndex].IsDraw = FALSE;
	//enemy[TekiIndex].Kind = TAMA_COLOR_RED;	//�e�̎�ނ�ݒ莩�Ȑ\��������

	////�G�̃R�s�[(�G�𑝂₷�Ƃ��́A���̏������R�s�[���ăl)
	int TekiIndex = TAMA_COLOR_YELLOW;
	TekiIndex++;
	enemy[TekiIndex] = enemy[TAMA_COLOR_RED];	//�R�s�[��(��)
	enemy[TekiIndex].image.x = GAME_WIDTH / 2 - enemy[TekiIndex].image.width / 2;
	enemy[TekiIndex].image.y = TekiIndex*(-100);
	EnemyAtariKeisan(&enemy[TekiIndex]);	//�����蔻����v�Z����֐�

	TekiIndex++;
	enemy[TekiIndex] = enemy[TAMA_COLOR_GREEN];	//�R�s�[��
	enemy[TekiIndex].image.x = GAME_WIDTH / 2 - enemy[TekiIndex].image.width / 2;
	enemy[TekiIndex].image.y = TekiIndex * (-100);
	EnemyAtariKeisan(&enemy[TekiIndex]);	//�����蔻����v�Z����֐�

	TekiIndex++;
	enemy[TekiIndex] = enemy[TAMA_COLOR_BLUE];	//�R�s�[��
	enemy[TekiIndex].image.x = GAME_WIDTH / 2 - enemy[TekiIndex].image.width / 2;
	enemy[TekiIndex].image.y = TekiIndex * (-100);
	EnemyAtariKeisan(&enemy[TekiIndex]);	//�����蔻����v�Z����֐�

	TekiIndex++;
	enemy[TekiIndex] = enemy[TAMA_COLOR_YELLOW];	//�R�s�[��
	enemy[TekiIndex].image.x = GAME_WIDTH / 2 - enemy[TekiIndex].image.width / 2;
	enemy[TekiIndex].image.y = TekiIndex * (-100);
	EnemyAtariKeisan(&enemy[TekiIndex]);	//�����蔻����v�Z����֐�

	TekiIndex++;
	enemy[TekiIndex] = enemy[TAMA_COLOR_RED];	//�R�s�[��(��)
	enemy[TekiIndex].image.x = GAME_WIDTH / 2 - enemy[TekiIndex].image.width / 2;
	enemy[TekiIndex].image.y = TekiIndex * (-100);
	EnemyAtariKeisan(&enemy[TekiIndex]);	//�����蔻����v�Z����֐�

	TekiIndex++;
	enemy[TekiIndex] = enemy[TAMA_COLOR_GREEN];	//�R�s�[��
	enemy[TekiIndex].image.x = GAME_WIDTH / 2 - enemy[TekiIndex].image.width / 2;
	enemy[TekiIndex].image.y = TekiIndex * (-100);
	EnemyAtariKeisan(&enemy[TekiIndex]);	//�����蔻����v�Z����֐�

	TekiIndex++;
	enemy[TekiIndex] = enemy[TAMA_COLOR_BLUE];	//�R�s�[��
	enemy[TekiIndex].image.x = GAME_WIDTH / 2 - enemy[TekiIndex].image.width / 2;
	enemy[TekiIndex].image.y = TekiIndex * (-100);
	EnemyAtariKeisan(&enemy[TekiIndex]);	//�����蔻����v�Z����֐�

	TekiIndex++;
	enemy[TekiIndex] = enemy[TAMA_COLOR_YELLOW];	//�R�s�[��
	enemy[TekiIndex].image.x = GAME_WIDTH / 2 - enemy[TekiIndex].image.width / 2;
	enemy[TekiIndex].image.y = TekiIndex * (-100);
	EnemyAtariKeisan(&enemy[TekiIndex]);	//�����蔻����v�Z����֐�

	TekiIndex++;
	enemy[TekiIndex] = enemy[TAMA_COLOR_RED];	//�R�s�[��(��)
	enemy[TekiIndex].image.x = GAME_WIDTH / 2 - enemy[TekiIndex].image.width / 2;
	enemy[TekiIndex].image.y = TekiIndex * (-100);
	EnemyAtariKeisan(&enemy[TekiIndex]);	//�����蔻����v�Z����֐�

	TekiIndex++;
	enemy[TekiIndex] = enemy[TAMA_COLOR_GREEN];	//�R�s�[��
	enemy[TekiIndex].image.x = GAME_WIDTH / 2 - enemy[TekiIndex].image.width / 2;
	enemy[TekiIndex].image.y = TekiIndex * (-100);
	EnemyAtariKeisan(&enemy[TekiIndex]);	//�����蔻����v�Z����֐�

	TekiIndex++;
	enemy[TekiIndex] = enemy[TAMA_COLOR_BLUE];	//�R�s�[��
	enemy[TekiIndex].image.x = GAME_WIDTH / 2 - enemy[TekiIndex].image.width / 2;
	enemy[TekiIndex].image.y = TekiIndex * (-100);
	EnemyAtariKeisan(&enemy[TekiIndex]);	//�����蔻����v�Z����֐�

	TekiIndex++;
	enemy[TekiIndex] = enemy[TAMA_COLOR_YELLOW];	//�R�s�[��
	enemy[TekiIndex].image.x = GAME_WIDTH / 2 - enemy[TekiIndex].image.width / 2;
	enemy[TekiIndex].image.y = TekiIndex * (-100);
	EnemyAtariKeisan(&enemy[TekiIndex]);	//�����蔻����v�Z����֐�

	TekiIndex++;
	enemy[TekiIndex] = enemy[TAMA_COLOR_RED];	//�R�s�[��(��)
	enemy[TekiIndex].image.x = GAME_WIDTH / 2 - enemy[TekiIndex].image.width / 2;
	enemy[TekiIndex].image.y = TekiIndex * (-100);
	EnemyAtariKeisan(&enemy[TekiIndex]);	//�����蔻����v�Z����֐�

	TekiIndex++;
	enemy[TekiIndex] = enemy[TAMA_COLOR_GREEN];	//�R�s�[��
	enemy[TekiIndex].image.x = GAME_WIDTH / 2 - enemy[TekiIndex].image.width / 2;
	enemy[TekiIndex].image.y = TekiIndex * (-100);
	EnemyAtariKeisan(&enemy[TekiIndex]);	//�����蔻����v�Z����֐�

	TekiIndex++;
	enemy[TekiIndex] = enemy[TAMA_COLOR_BLUE];	//�R�s�[��
	enemy[TekiIndex].image.x = GAME_WIDTH / 2 - enemy[TekiIndex].image.width / 2;
	enemy[TekiIndex].image.y = TekiIndex * (-100);
	EnemyAtariKeisan(&enemy[TekiIndex]);	//�����蔻����v�Z����֐�

	TekiIndex++;
	enemy[TekiIndex] = enemy[TAMA_COLOR_YELLOW];	//�R�s�[��
	enemy[TekiIndex].image.x = GAME_WIDTH / 2 - enemy[TekiIndex].image.width / 2;
	enemy[TekiIndex].image.y = TekiIndex * (-100);
	EnemyAtariKeisan(&enemy[TekiIndex]);	//�����蔻����v�Z����֐�


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

VOID EnemyAtariKeisan(ENEMY* e)
{
	e->rect.left = e->image.x;
	e->rect.top = e->image.y;
	e->rect.right = e->image.x + e->image.width;
	e->rect.bottom = e->image.y + e->image.height;

	return;
}

VOID TamaAtariKeisan(TAMA* tama)
{
	tama->coll.left = tama->x;
	tama->coll.top = tama->y;
	tama->coll.right = tama->x + tama->width;
	tama->coll.bottom = tama->y + tama->height;

	return;
}

VOID EnemyAtariDelete(ENEMY* e)
{
	e->rect.left = -10;
	e->rect.top = -10;
	e->rect.right = -10;
	e->rect.bottom = -10;

	return;
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

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		DeleteGraph(enemy[i].image.handle); //�G
	}

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

	//�v���C���[�_���[�W
	strcpy_s(player.musicMiss.path, MUSIC_PLAYER_MISS_PATH);			//�p�X�̐ݒ�
	player.musicMiss.handle = LoadSoundMem(player.musicMiss.path);		//�ǂݍ���
	if (player.musicMiss.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_PLAYER_MISS_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
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
	DeleteSoundMem(player.musicMiss.handle);

	DeleteSoundMem(END_FAIL_BGM.handle);
	DeleteSoundMem(END_COMP_BGM.handle);
	return;
}

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