/* 共通インクルードファイル */
#include "common.h"
/* 個別インクルードファイル */

/* 外部関数定義 */

/* 外部変数定義 */
extern const char *generalMidiProgramChangeStrTbl[128];
extern const char *midiControlChangeStrTbl[128];

/* 内部関数定義 */
#include "SomeCtrl.h"
/* 内部変数定義 */

typedef struct
{
    SOME_CTRL_GROUP_ID groupId;
    PTSTR              class;       /* ウィンドウクラス名                         */
    PTSTR              value;       /* ウィンドウテキスト                         */
    int                x;           /* クライアント領域の x座標                   */
    int                y;           /* クライアント領域の y座標                   */
    int                width;       /* 初期幅                                     */
    int                height;      /* 初期高さ                                   */
    BOOL               bSizeAdj;    /* サイズ調整を行うか                         */
    int                widthOfst;   /* クライアント領域の幅サイズからのオフセット */
    int                heightOfst;  /* 1文字分の高さからのオフセット              */
    DWORD              exStyle;     /* 拡張スタイル                               */
    DWORD              style;       /* スタイル                                   */
} S_SOME_CTRL;

static S_SOME_CTRL ctrlListTbl[SOME_CTRL_MAX] =
{
    /*                     , class            , value                 , x , y  ,  w  , h ,bSAdj  ,wOfst, hOfst,exStyle,style  */
    {SOME_CTRL_GROUP_ALWAYS, TEXT("static")   , TEXT("MIDI OUT")      , 10,  15,  80 , 15 ,FALSE ,0    , 0    ,0                ,(WS_CHILD|ES_LEFT)                      },
    {SOME_CTRL_GROUP_ALWAYS, TEXT("combobox") , TEXT("")              , 85,  10, 200 , 300,FALSE ,0    , 0    ,0                ,(WS_CHILD|CBS_SORT|CBS_DROPDOWNLIST)    },
    {SOME_CTRL_GROUP_ALWAYS, TEXT("button")   , TEXT("Open")          ,300,  10,  40 , 20 ,FALSE ,0    , 0    ,0                ,(WS_CHILD|ES_LEFT)                      },
    {SOME_CTRL_GROUP_ALWAYS, TEXT("static")   , TEXT("MIDI CH")       , 10,  40,  80 , 15 ,FALSE ,0    , 0    ,0                ,(WS_CHILD|ES_LEFT)                      },
    {SOME_CTRL_GROUP_ALWAYS, TEXT("combobox") , TEXT("")              , 85,  35,  50 , 300,FALSE ,0    , 0    ,0                ,(WS_CHILD|CBS_DROPDOWNLIST)             },
    {SOME_CTRL_GROUP_ALWAYS, TEXT("static")   , TEXT("PROGRAM CHANGE"), 10, 170,  80 , 30 ,FALSE ,0    , 0    ,0                ,(WS_CHILD|ES_LEFT)                      },
    {SOME_CTRL_GROUP_ALWAYS, TEXT("combobox") , TEXT("")              , 85, 170, 150 , 300,FALSE ,0    , 0    ,0                ,(WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL)  },
    {SOME_CTRL_GROUP_ALWAYS, TEXT("button")   , TEXT("Send")          ,245, 170,  40 , 20 ,FALSE ,0    , 0    ,0                ,(WS_CHILD|ES_LEFT)                      },
    {SOME_CTRL_GROUP_ALWAYS, TEXT("static")   , TEXT("CONTROL CHANGE"), 10, 200,  80 , 30 ,FALSE ,0    , 0    ,0                ,(WS_CHILD|ES_LEFT)                      },
    {SOME_CTRL_GROUP_ALWAYS, TEXT("combobox") , TEXT("")              , 85, 200, 150 , 300,FALSE ,0    , 0    ,0                ,(WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL)  },
    {SOME_CTRL_GROUP_ALWAYS, TEXT("scrollbar"), TEXT("")              ,250, 200, 150 , 20 ,FALSE ,0    , 0    ,0                ,(WS_CHILD)                              },
    {SOME_CTRL_GROUP_ALWAYS, TEXT("static")   , TEXT("0")             ,405, 205,  20 , 15 ,FALSE ,0    , 0    ,0                ,(WS_CHILD|ES_LEFT)                      },
    {SOME_CTRL_GROUP_ALWAYS, TEXT("button")   , TEXT("Send")          ,435, 200,  40 , 20 ,FALSE ,0    , 0    ,0                ,(WS_CHILD|ES_LEFT)                      },
    {SOME_CTRL_GROUP_ALWAYS, TEXT("static")   , TEXT("MIDI MSG")      , 10, 245,  70 , 15 ,FALSE ,0    , 0    ,0                ,(WS_CHILD|ES_LEFT)                      },
    {SOME_CTRL_GROUP_ALWAYS, TEXT("edit")     , TEXT("")              , 85, 240, 100 , 20 ,FALSE ,0    , 0    ,MY_EX_STYLE      ,(WS_CHILD|ES_LEFT|ES_READONLY)          },
};

typedef struct
{
    BOOL               exist                        ; /* ウィンドウが生成されているかどうか */
    HWND               hwnd                         ;
} S_SOME_CTRL_INFO;
static S_SOME_CTRL_INFO ctrlInfo[SOME_CTRL_MAX];


/********************************************************************************
 * 内容  : 登録された全てのコントロールを生成する
 * 引数  : HINSTANCE hInst
 * 引数  : PTSTR szAppName
 * 引数  : HWND hwnd 親ウィンドウのハンドラ
 * 戻り値: BOOL
 ***************************************/
BOOL
SomeCtrlCreate( HINSTANCE hInst, PTSTR szAppName, HWND hwnd )
{
    int i,j,iCbNum;
    TCHAR szBuff[128];

    for(i=0; i<SOME_CTRL_MAX; i++)
    {
        S_SOME_CTRL *tblPtr = &(ctrlListTbl[i]);
        S_SOME_CTRL_INFO *infoPtr = &(ctrlInfo[i]);

        infoPtr->hwnd = CreateWindowEx( tblPtr->exStyle,                  /* 拡張スタイル       */
                                       tblPtr->class,                    /* クラス名           */
                                       tblPtr->value,                    /* ウィンドウテキスト */
                                       tblPtr->style,                    /* スタイル           */
                                       tblPtr->x,tblPtr->y,       /* x座標,y座標        */
                                       tblPtr->width,                    /* 幅                 */
                                       tblPtr->height,                   /* 高さ               */
                                       hwnd,(HMENU)(SOME_CTRL_ID_OFFSET+i),     /* 親ウィンドウ,子ウィンドウID */
                                       hInst,NULL );                       /* インスタンスハンドル,補助引数 */
        if( infoPtr->hwnd != NULL )
        {
            SendMessage(infoPtr->hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0));

            /* 個別に処理するもの */
            switch( i )
            {
            case SOME_CTRL_MIDI_CH:
                for(j=0; j<16; j++ )
                {
                    wsprintf(szBuff,TEXT("%d"),j+1);
                    iCbNum = SendMessage(infoPtr->hwnd , CB_ADDSTRING, 0, (LPARAM)&szBuff[0]);
                    SendMessage( infoPtr->hwnd , CB_SETITEMDATA, iCbNum, (LPARAM)j );
                }
                SendMessage( infoPtr->hwnd , CB_SETCURSEL, 0, (LPARAM)0 );
                break;
            case SOME_CTRL_MIDI_PROGRAM_CHANGE:
                for(j=0; j<128; j++ )
                {
                    iCbNum = SendMessage(infoPtr->hwnd , CB_ADDSTRING, 0, (LPARAM)generalMidiProgramChangeStrTbl[j]);
                    SendMessage( infoPtr->hwnd , CB_SETITEMDATA, iCbNum, (LPARAM)j );
                }
                SendMessage( infoPtr->hwnd , CB_SETCURSEL, 0, (LPARAM)0 );
                break;
            case SOME_CTRL_MIDI_CTRL_CHANGE_KIND:
                for(j=0; j<128; j++ )
                {
                    iCbNum = SendMessage(infoPtr->hwnd , CB_ADDSTRING, 0, (LPARAM)midiControlChangeStrTbl[j]);
                    SendMessage( infoPtr->hwnd , CB_SETITEMDATA, iCbNum, (LPARAM)j );
                }
                SendMessage( infoPtr->hwnd , CB_SETCURSEL, 0, (LPARAM)0 );
                break;
            case SOME_CTRL_MIDI_CTRL_CHANGE_VALUE:
                SetScrollRange( infoPtr->hwnd, SB_CTL, 0, 127, FALSE );
                SetScrollPos( infoPtr->hwnd, SB_CTL, 0, FALSE );
                break;
            default:
                break;
            }

            if( tblPtr->groupId == SOME_CTRL_GROUP_ALWAYS )
            {
                ShowWindow(infoPtr->hwnd, SW_SHOW);
            }
            else
            {
                nop();
            }
            infoPtr->exist = TRUE;
        }
        else
        {
            /* do nothing */
        }
    }

#if 0
    SomeCtrlDisable(SOME_CTRL_MODE_PERFORMANCE);
    SomeCtrlDisable(SOME_CTRL_MODE_GM);

    SomeCtrlGroupDisplay(SOME_CTRL_GROUP_SYSTEM);
#endif

    return TRUE;
}

/********************************************************************************
 * 内容  : 指定のグループのコントロールを表示する
 * 引数  : SOME_CTRL_GROUP_ID groupId
 * 戻り値: BOOL
 ***************************************/
BOOL
SomeCtrlGroupDisplay( SOME_CTRL_GROUP_ID groupId )
{
    SOME_CTRL_ID id;

    for(id=0; id<SOME_CTRL_MAX; id++)
    {
        S_SOME_CTRL *tblPtr = &(ctrlListTbl[id]);
        S_SOME_CTRL_INFO *infoPtr = &(ctrlInfo[id]);

        if( (tblPtr->groupId == SOME_CTRL_GROUP_ALWAYS) ||
            (tblPtr->groupId == groupId) )
        {
            ShowWindow(infoPtr->hwnd, SW_SHOW);
        }
        else
        {
            ShowWindow(infoPtr->hwnd, SW_HIDE);
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
SomeCtrlSize( int cxClient,int cyClient )
{
    int i;

    for(i=0; i<SOME_CTRL_MAX; i++)
    {
        S_SOME_CTRL *tblPtr = &(ctrlListTbl[i]);
        S_SOME_CTRL_INFO *infoPtr = &(ctrlInfo[i]);

        if( tblPtr->bSizeAdj )
        {
            MoveWindow( infoPtr->hwnd, tblPtr->x,tblPtr->y, (cxClient + tblPtr->widthOfst),cyClient + tblPtr->heightOfst, TRUE);
        }
        else
        {
            /* do nothing */
        }
    }

    return (LONG)700;
}

/********************************************************************************
 * 内容  : コントロールのウィンドウハンドラを取得する
 * 引数  : SOME_CTRL_ID id
 * 戻り値: HWND
 ***************************************/
HWND
SomeCtrlGetHWND( SOME_CTRL_ID id )
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

/********************************************************************************
 * 内容  : コントロールを有効にする
 * 引数  : SOME_CTRL_ID id
 * 戻り値: なし
 ***************************************/
void
SomeCtrlEnable( SOME_CTRL_ID id )
{
    EnableWindow( ctrlInfo[id].hwnd, TRUE);
}

/********************************************************************************
 * 内容  : コントロールを無効にする
 * 引数  : SOME_CTRL_ID id
 * 戻り値: なし
 ***************************************/
void
SomeCtrlDisable( SOME_CTRL_ID id )
{
    EnableWindow( ctrlInfo[id].hwnd, FALSE);
}

/********************************************************************************
 * 内容  : ウィンドウからテキストを取得する
 * 引数  : SOME_CTRL_ID id
 * 引数  : PTSTR ptstrText
 * 戻り値: BOOL
 ***************************************/
BOOL
SomeCtrlGetText( SOME_CTRL_ID id, PTSTR ptstrText )
{
    BOOL rtn = FALSE;
    INT iLength;

    if( ctrlInfo[id].exist == TRUE )
    {
        iLength = GetWindowTextLength( ctrlInfo[id].hwnd );
        GetWindowText( ctrlInfo[id].hwnd, ptstrText, iLength + 1 );
        rtn = TRUE;
    }
    else
    {
        /* error */
    }

    return rtn;
}
