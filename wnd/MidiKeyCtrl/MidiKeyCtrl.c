/* 共通インクルードファイル */
#include "common.h"
/* 個別インクルードファイル */

/* 外部関数定義 */
#include "WinMain.h"
#include "DebugWnd.h"

/* 外部変数定義 */

/* 内部関数定義 */
#include "MidiKeyCtrl.h"
/* 内部変数定義 */

typedef struct
{
    INT xPos  ;
    INT yPos  ;
    INT width ;
    INT height;
} S_MIDIKEY_WINDOW_INFO;

typedef struct
{
    BOOL                  exist                        ; /* ウィンドウが生成されているかどうか */
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
 * 内容  : 
 * 引数  : 
 * 戻り値: LRESULT CALLBACK
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
 * 内容  : 登録された全てのコントロールを生成する
 * 引数  : HINSTANCE hInst
 * 引数  : PTSTR szAppName
 * 引数  : HWND hwnd 親ウィンドウのハンドラ
 * 戻り値: BOOL
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
        { /* 黒鍵 */
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

        infoPtr->hwnd = CreateWindowEx( exStyle,      /* 拡張スタイル       */
                                        "button",           /* クラス名           */
                                        "",                 /* ウィンドウテキスト */
                                        style, /* スタイル           */
                                        xPos,yPos,          /* x座標,y座標        */
                                        width,              /* 幅                 */
                                        height,             /* 高さ               */
                                        hwnd,(HMENU)(MIDIKEY_CTRL_ID_OFFSET+i),   /* 親ウィンドウ,子ウィンドウID */
                                        hInst,NULL );                        /* インスタンスハンドル,補助引数 */
        if( infoPtr->hwnd != NULL )
        {
            SendMessage(infoPtr->hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0));

            /* 個別に処理するもの */
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
 * 内容  : 登録された全てのコントロールのサイズを調整する
 * 引数  : int cxClient
 * 引数  : int cyClient
 * 戻り値: LONG コントロールを配置する矩形の縦方向のサイズ
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
 * 内容  : コントロールのウィンドウハンドラを取得する
 * 引数  : MIDIKEY_CTRL_ID id
 * 戻り値: HWND
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
