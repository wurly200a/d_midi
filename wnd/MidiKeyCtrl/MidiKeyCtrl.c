/* ���ʃC���N���[�h�t�@�C�� */
#include "common.h"
/* �ʃC���N���[�h�t�@�C�� */

/* �O���֐���` */
#include "WinMain.h"
#include "DebugWnd.h"

/* �O���ϐ���` */

/* �����֐���` */
#include "MidiKeyCtrl.h"
/* �����ϐ���` */

typedef struct
{
    INT xPos  ;
    INT yPos  ;
    INT width ;
    INT height;
} S_MIDIKEY_WINDOW_INFO;

typedef struct
{
    BOOL                  exist                        ; /* �E�B���h�E����������Ă��邩�ǂ��� */
    BOOL                  bZorderTop                   ;
    HWND                  hwnd                         ;
    S_MIDIKEY_WINDOW_INFO wtInfo                       ;
    WNDPROC               defaultWndProc               ;
} S_MIDIKEY_CTRL_INFO;
static S_MIDIKEY_CTRL_INFO ctrlInfo[MIDIKEY_CTRL_ID_MAX];

#define PARAM_STATIC_X_BASE_POS  10
#define PARAM_STATIC_Y_BASE_POS  70
#define PARAM_STATIC_WIDTH       16
#define PARAM_STATIC_HEIGHT      80

/********************************************************************************
 * ���e  : 
 * ����  : 
 * �߂�l: LRESULT CALLBACK
 ***************************************/
LRESULT CALLBACK
WndProcForMidiKeyCtrl( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    MIDIKEY_CTRL_ID i,myId=MIDIKEY_CTRL_ID_MAX;
    S_MIDIKEY_CTRL_INFO *infoPtr;

    for(i=0; i<MIDIKEY_CTRL_ID_MAX; i++)
    {
        infoPtr = &(ctrlInfo[i]);

        if( infoPtr->hwnd == hwnd )
        {
            myId = i;
            break;
        }
        else
        {
            nop();
        }
    }

//    DebugWndPrintf("WndProcForMidiKeyCtrl,%d\r\n",myId);

    switch (message)
    {
    case WM_LBUTTONDOWN:
        SendMessage(GetParent(hwnd),WM_APP,myId+MIDIKEY_CTRL_ID_OFFSET,hwnd);
        break;
    }

    return CallWindowProc(infoPtr->defaultWndProc,hwnd,message,wParam,lParam);
}

/********************************************************************************
 * ���e  : �o�^���ꂽ�S�ẴR���g���[���𐶐�����
 * ����  : HINSTANCE hInst
 * ����  : PTSTR szAppName
 * ����  : HWND hwnd �e�E�B���h�E�̃n���h��
 * �߂�l: BOOL
 ***************************************/
BOOL
MidiKeyCtrlCreate( HINSTANCE hInst, PTSTR szAppName, HWND hwnd )
{
    int i,j,iCbNum;
    TCHAR szBuff[128];
    INT nowId,numForDisp;
    INT columnNum = 0;
    INT xPosNext;

    xPosNext = PARAM_STATIC_X_BASE_POS;
    for(i=0,numForDisp=0; i<MIDIKEY_CTRL_ID_MAX; i++,numForDisp++)
    {
        PTSTR class;
        DWORD style;
        DWORD exStyle;
        DWORD height;
        INT   width;
        INT yPos;
        INT xPos;

        S_MIDIKEY_CTRL_INFO *infoPtr = &(ctrlInfo[i]);

        if( numForDisp == 12 )
        {
            numForDisp = 0;
        }
        else
        {
            nop();
        }

        style = WS_CHILD;
        exStyle =0;

        height = PARAM_STATIC_HEIGHT;
        width  = PARAM_STATIC_WIDTH;

        xPos = xPosNext;
        yPos = PARAM_STATIC_Y_BASE_POS;

        if( (numForDisp==1)||
            (numForDisp==3)||
            (numForDisp==6)||
            (numForDisp==8)||
            (numForDisp==10) )
        { /* ���� */
            height = 50;
            infoPtr->bZorderTop = (BOOL)TRUE;

            exStyle =WS_EX_TOPMOST;

        }
        else
        {
            infoPtr->bZorderTop = (BOOL)FALSE;

            style |= WS_CLIPSIBLINGS;
        }

        if( (numForDisp == 4) ||
            (numForDisp == 11) )
        {
            xPosNext += PARAM_STATIC_WIDTH;
        }
        else
        {
            xPosNext += PARAM_STATIC_WIDTH/2;
        }

        infoPtr->wtInfo.xPos   = xPos  ;
        infoPtr->wtInfo.yPos   = yPos  ;
        infoPtr->wtInfo.width  = width ;
        infoPtr->wtInfo.height = height;

        infoPtr->hwnd = CreateWindowEx( exStyle,      /* �g���X�^�C��       */
                                        "button",           /* �N���X��           */
                                        "",                 /* �E�B���h�E�e�L�X�g */
                                        style, /* �X�^�C��           */
                                        xPos,yPos,          /* x���W,y���W        */
                                        width,              /* ��                 */
                                        height,             /* ����               */
                                        hwnd,(HMENU)(MIDIKEY_CTRL_ID_OFFSET+i),   /* �e�E�B���h�E,�q�E�B���h�EID */
                                        hInst,NULL );                        /* �C���X�^���X�n���h��,�⏕���� */
        if( infoPtr->hwnd != NULL )
        {
            SendMessage(infoPtr->hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0));

            /* �ʂɏ���������� */
            switch( i )
            {
            default:
                break;
            }

            ShowWindow(infoPtr->hwnd, SW_SHOW);

            infoPtr->exist = TRUE;

            infoPtr->defaultWndProc = (WNDPROC)GetWindowLong(infoPtr->hwnd, GWL_WNDPROC);
            SetWindowLong(infoPtr->hwnd,GWL_WNDPROC,(LONG)WndProcForMidiKeyCtrl);
        }
        else
        {
            /* do nothing */
        }
    }

    return TRUE;
}

/********************************************************************************
 * ���e  : �o�^���ꂽ�S�ẴR���g���[���̃T�C�Y�𒲐�����
 * ����  : int cxClient
 * ����  : int cyClient
 * �߂�l: LONG �R���g���[����z�u�����`�̏c�����̃T�C�Y
 ***************************************/
LONG
MidiKeyCtrlSize( int cxClient,int cyClient )
{
    int i;

    for(i=0; i<MIDIKEY_CTRL_ID_MAX; i++)
    {
        S_MIDIKEY_CTRL_INFO *infoPtr = &(ctrlInfo[i]);

        if( infoPtr->bZorderTop )
        {
            SetWindowPos(infoPtr->hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
        }
        else
        {
            SetWindowPos(infoPtr->hwnd,HWND_BOTTOM,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
        }
    }

    return (LONG)700;
}

/********************************************************************************
 * ���e  : �R���g���[���̃E�B���h�E�n���h�����擾����
 * ����  : MIDIKEY_CTRL_ID id
 * �߂�l: HWND
 ***************************************/
HWND
MidiKeyCtrlGetHWND( MIDIKEY_CTRL_ID id )
{
    HWND rtn;

    if( ctrlInfo[id].exist == TRUE )
    {
        rtn = ctrlInfo[id].hwnd;
    }
    else
    {
        rtn = (HWND)0;
    }

    return rtn;
}
