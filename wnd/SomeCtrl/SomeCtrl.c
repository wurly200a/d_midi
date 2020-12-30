/* ���ʃC���N���[�h�t�@�C�� */
#include "common.h"
/* �ʃC���N���[�h�t�@�C�� */

/* �O���֐���` */

/* �O���ϐ���` */
extern const char *generalMidiProgramChangeStrTbl[128];
extern const char *midiControlChangeStrTbl[128];

/* �����֐���` */
#include "SomeCtrl.h"
/* �����ϐ���` */

typedef struct
{
    SOME_CTRL_GROUP_ID groupId;
    PTSTR              class;       /* �E�B���h�E�N���X��                         */
    PTSTR              value;       /* �E�B���h�E�e�L�X�g                         */
    int                x;           /* �N���C�A���g�̈�� x���W                   */
    int                y;           /* �N���C�A���g�̈�� y���W                   */
    int                width;       /* ������                                     */
    int                height;      /* ��������                                   */
    BOOL               bSizeAdj;    /* �T�C�Y�������s����                         */
    int                widthOfst;   /* �N���C�A���g�̈�̕��T�C�Y����̃I�t�Z�b�g */
    int                heightOfst;  /* 1�������̍�������̃I�t�Z�b�g              */
    DWORD              exStyle;     /* �g���X�^�C��                               */
    DWORD              style;       /* �X�^�C��                                   */
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
    BOOL               exist                        ; /* �E�B���h�E����������Ă��邩�ǂ��� */
    HWND               hwnd                         ;
} S_SOME_CTRL_INFO;
static S_SOME_CTRL_INFO ctrlInfo[SOME_CTRL_MAX];


/********************************************************************************
 * ���e  : �o�^���ꂽ�S�ẴR���g���[���𐶐�����
 * ����  : HINSTANCE hInst
 * ����  : PTSTR szAppName
 * ����  : HWND hwnd �e�E�B���h�E�̃n���h��
 * �߂�l: BOOL
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

        infoPtr->hwnd = CreateWindowEx( tblPtr->exStyle,                  /* �g���X�^�C��       */
                                       tblPtr->class,                    /* �N���X��           */
                                       tblPtr->value,                    /* �E�B���h�E�e�L�X�g */
                                       tblPtr->style,                    /* �X�^�C��           */
                                       tblPtr->x,tblPtr->y,       /* x���W,y���W        */
                                       tblPtr->width,                    /* ��                 */
                                       tblPtr->height,                   /* ����               */
                                       hwnd,(HMENU)(SOME_CTRL_ID_OFFSET+i),     /* �e�E�B���h�E,�q�E�B���h�EID */
                                       hInst,NULL );                       /* �C���X�^���X�n���h��,�⏕���� */
        if( infoPtr->hwnd != NULL )
        {
            SendMessage(infoPtr->hwnd, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0));

            /* �ʂɏ���������� */
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
 * ���e  : �w��̃O���[�v�̃R���g���[����\������
 * ����  : SOME_CTRL_GROUP_ID groupId
 * �߂�l: BOOL
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
 * ���e  : �o�^���ꂽ�S�ẴR���g���[���̃T�C�Y�𒲐�����
 * ����  : int cxClient
 * ����  : int cyClient
 * �߂�l: LONG �R���g���[����z�u�����`�̏c�����̃T�C�Y
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
 * ���e  : �R���g���[���̃E�B���h�E�n���h�����擾����
 * ����  : SOME_CTRL_ID id
 * �߂�l: HWND
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
 * ���e  : �R���g���[����L���ɂ���
 * ����  : SOME_CTRL_ID id
 * �߂�l: �Ȃ�
 ***************************************/
void
SomeCtrlEnable( SOME_CTRL_ID id )
{
    EnableWindow( ctrlInfo[id].hwnd, TRUE);
}

/********************************************************************************
 * ���e  : �R���g���[���𖳌��ɂ���
 * ����  : SOME_CTRL_ID id
 * �߂�l: �Ȃ�
 ***************************************/
void
SomeCtrlDisable( SOME_CTRL_ID id )
{
    EnableWindow( ctrlInfo[id].hwnd, FALSE);
}

/********************************************************************************
 * ���e  : �E�B���h�E����e�L�X�g���擾����
 * ����  : SOME_CTRL_ID id
 * ����  : PTSTR ptstrText
 * �߂�l: BOOL
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
