//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include "resource.h"

#define GAME_WIDTH			800	//��ʂ̉��̑傫��
#define GAME_HEIGHT			600	//��ʂ̏c�̑傫��
#define GAME_COLOR			32	//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR		0	//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME	"GAME TITLE"	//�E�B���h�E�̃^�C�g��

#define GAME_FPS 60 //FPS�̐��l

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
#define IMAGE_LOAD_ERR_TITLE TEXT("�摜�ǂݍ��݃G���[")

#define MUSIC_TITLE_BGM_PATH TEXT(".\\MUSIC\\loop_33.wav")
#define MUSIC_PLAY_BGM_PATH TEXT(".\\MUSIC\\fruitsparfait.mp3")
#define MUSIC_END_BGM_PATH TEXT(".\\MUSIC\\�ق̂ڂ̃Q�[���I�[�o�[.mp3")

#define MUSIC_LOAD_ERR_TITLE TEXT("���y�ǂݍ��݃G���[")

//�e�̐ݒ�
#define TAMA_CHANGE_MAX		 5	//5�t���[���ڂŒe�̉摜��ς���
#define TAMA_MAX			16	//�ő�16���܂�

//#define TAMA_RED_PATH			TEXT(".\\IMAGE\\TAMA\\red.png")		//�Ԓe�̉摜
//#define TAMA_GREEN_PATH			TEXT(".\\IMAGE\\TAMA\\green.png")	//�e�̉摜
//#define TAMA_BLUE_PATH			TEXT(".\\IMAGE\\TAMA\\blue.png")	//�Βe�̉摜
//#define TAMA_YELLOW_PATH		TEXT(".\\IMAGE\\TAMA\\yellow.png")	//���e�̉摜

#define TAMA_DIV_WIDTH		16	//�摜�𕪊����镝�T�C�Y
#define TAMA_DIV_HEIGHT		16	//�摜�𕪊����鍂���T�C�Y

#define TAMA_DIV_TATE		3	//�摜���c�ɕ������鐔
#define TAMA_DIV_YOKO		1	//�摜�����ɕ������鐔

#define TAMA_DIV_NUM	TAMA_DIV_TATE * TAMA_DIV_YOKO	//�摜�𕪊����鑍��


//����{�^�����������Ƃ�
#define MSG_CLOSE_TITLE TEXT("�I�����b�Z�[�W")
#define MSG_CLOSE_CAPTION TEXT("�Q�[�����I�����܂����H")


enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};

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
}TAMA;	//�e�̍\����


typedef struct STRUCT_CHARA
{
	IMAGE image;
	int speed;
	//int CenterX;				//���SX
	//int CenterY;				//���SY

	MUSIC musicShot;			//�v���C���[�̔��ˉ�

	BOOL CanShot;				//�V���b�g�ł��邩
	int ShotReLoadCnt;			//�V���b�g�����[�h����
	int ShotReLoadCntMAX;		//�V���b�g�����[�h����(MAX)

	TAMA tama[TAMA_MAX];
	RECT coll;
	iPOINT collBeforePt;

}CHARA;

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

//�v���C���[�֘A
CHARA player; //�Q�[���̃L����

//�摜�֌W
IMAGE ImageTitleROGO; //�^�C�g�����S
IMAGE ImageTitleBack; //�^�C�g���w�i

IMAGE ImagePlayBack; //�v���C�w�i

IMAGE ImageEndBack; //�G���h�w�i

//���y�֌W
MUSIC TITLE;
MUSIC PLAY_BGM;
MUSIC END_BGM;

//�t�H���g
FONT FontTanu32;

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
		ChangeVolumeSoundMem(255 * 50 / 100, TITLE.handle); //50%�̉���
		PlaySoundMem(TITLE.handle, DX_PLAYTYPE_LOOP); //���[�v�Đ�
	}
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		//BGM������Ă�����
		if (CheckSoundMem(TITLE.handle) != 0)
		{
			StopSoundMem(TITLE.handle); //�~�߂�
		}

		MY_PLAY_INIT(); //�Q�[��������

		GameScene = GAME_SCENE_PLAY; //�v���C��ʂɑJ��

		return;
	}
	return;
}

VOID MY_START_DRAW(VOID)
{
	DrawString(0, 0, "�X�^�[�g��ʁi�G���^�[�L�[�������Ă��������j", GetColor(255, 255, 255));
	DrawGraph(ImageTitleROGO.x, ImageTitleROGO.y, ImageTitleROGO.handle, TRUE);
	
	DrawStringToHandle(GAME_WIDTH/4, GAME_HEIGHT/2+50, "�G���^�[�L�[�������ĂˁI", GetColor(255, 255, 255), FontTanu32.handle);

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
	//BGM������Ă��Ȃ��Ȃ�
	if (CheckSoundMem(PLAY_BGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 50 / 100, PLAY_BGM.handle); //50%�̉���
		PlaySoundMem(PLAY_BGM.handle, DX_PLAYTYPE_LOOP); //���[�v�Đ�
	}
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{
		if (CheckSoundMem(PLAY_BGM.handle) != 0)
		{
			StopSoundMem(PLAY_BGM.handle);
		}
		GameScene = GAME_SCENE_END; //�v���C��ʂɑJ��

		return;
	}

	//�}�E�X�̍��{�^�����N���b�N�����Ƃ�
	if (MY_MOUSE_DOWN(MOUSE_INPUT_LEFT) == TRUE)
	{
		//�e�̕`��i���j
		//�V���b�g�����Ă�Ƃ�
		//if (player.CanShot == TRUE)
		//{
		//	//�V���b�g���ˁI�I
		//	PlaySoundMem(player.musicShot.handle, DX_PLAYTYPE_BACK);
		//	player.CanShot = FALSE;

		//	//�󂢂Ă���X���b�g�ŁA�e�̕`�������
		//	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
		//	{
		//		if (player.tama[cnt].IsDraw == FALSE)
		//		{
		//			//�e��X�ʒu�̓v���C���[�̒��S���甭��
		//			player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;

		//			//�e��Y�ʒu�̓v���C���[�̏㕔�����甭��
		//			player.tama[cnt].y = player.image.y;

		//			//�e��`�悷��
		//			player.tama[cnt].IsDraw = TRUE;

		//			break;
		//		}
		//	}
		//}
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
	return;
}

VOID MY_PLAY_DRAW(VOID)
{
	DrawGraph(ImagePlayBack.x, ImagePlayBack.y, ImagePlayBack.handle, TRUE);
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

	/*��ʉ������ɓ����悤�ȕ`�ʁB������ύX���邩������Ȃ�*/
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

			//�e����Ɉړ�������
			if (player.tama[cnt].y < 0)
			{
				player.tama[cnt].IsDraw = FALSE;	//�`��I��
			}
			else
			{
				player.tama[cnt].y -= player.tama[cnt].speed;
			}
		}
	}

	DrawString(0, 0, "�v���C���(�X�y�[�X�L�[�������Ă��������B)", GetColor(255, 255, 255));

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
		ChangeVolumeSoundMem(255 * 50 / 100, END_BGM.handle); //50%�̉���
		PlaySoundMem(END_BGM.handle, DX_PLAYTYPE_LOOP); //���[�v�Đ�
	}
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		if (CheckSoundMem(END_BGM.handle) != 0)
		{
			StopSoundMem(END_BGM.handle);
		}
		GameScene = GAME_SCENE_START; //�v���C��ʂɑJ��

		return;
	}
	return;
}

VOID MY_END_DRAW(VOID)
{
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
	//for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	//{
	//	//�p�X���R�s�[
	//	strcpyDx(player.tama[cnt].path, TEXT(TAMA_RED_PATH));

	//	for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++)
	//	{
	//		//�n���h�����R�s�[
	//		player.tama[cnt].handle[i_num] = player.tama[0].handle[i_num];
	//	}

	//	//�����R�s�[
	//	player.tama[cnt].width = player.tama[0].width;

	//	//�������R�s�[
	//	player.tama[cnt].height = player.tama[0].height;

	//	//�e��X�ʒu�̓v���C���[�̒��S���甭��
	//	player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;

	//	//�e��Y�ʒu�̓v���C���[�̏㕔�����甭��
	//	player.tama[cnt].y = player.image.y;

	//	//�e�͍ŏ��͔�\��
	//	player.tama[cnt].IsDraw = FALSE;

	//	//�e�̕\���J�E���g��0�ɂ���
	//	player.tama[cnt].changeImageCnt = 0;

	//	//�e�̕\���J�E���gMAX��ݒ肷��
	//	player.tama[cnt].changeImageCntMAX = TAMA_CHANGE_MAX;

	//	//���݂̉摜�̎�ނ�����������
	//	player.tama[cnt].nowImageKind = 0;

	//	//�e�̃X�s�[�h��ݒ肷��
	//	player.tama[cnt].speed = CHARA_SPEED_LOW;
	//}

	return TRUE;
}

VOID MY_DELETE_IMAGE(VOID)
{
	DeleteGraph(ImageTitleROGO.handle);

	//�e�폜
	//for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++) { DeleteGraph(player.tama[0].handle[i_num]); }

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