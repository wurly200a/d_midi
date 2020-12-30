/* ���ʃC���N���[�h�t�@�C�� */
#include "common.h"
/* �ʃC���N���[�h�t�@�C�� */
#include "MainWndDef.h"
#include "MenuId.h"
#include "MainWndMenu.h"

/* �O���֐���` */
#include "SomeCtrl.h"
#include "ParamCtrl.h"
#include "File.h"
#include "StsBar.h"
#include "Config.h"
#include "ModalDlg.h"

#include "DebugWnd.h"
#include "Midi.h"
#include "MidiKeyCtrl.h"

/* �O���ϐ���` */

/* �����֐���` */
#include "MainWnd.h"
LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static MAINWND_INDEX convertMSGtoINDEX( UINT message );
static LRESULT onCreate          ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onPaint           ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onSize            ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onMove            ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onWindowPosChanged( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onClose           ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onDestroy         ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onCommand         ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onKeyUp           ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onKeyDown         ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onChar            ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onHscroll         ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onVscroll         ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onMouseWheel      ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onSetFocus        ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onKillFocus       ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onDropFiles       ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onInitMenuPopup   ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onFindMsgString   ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onTimer           ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onApp             ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
static LRESULT onDefault         ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );

int okMessage( HWND hwnd, TCHAR *szMessageFormat, ... );
void doCaption( HWND hwnd, TCHAR* szTitleName, BOOL bNeedSave );
short AskAboutSave( HWND hwnd, TCHAR * szTitleName );

/* �����ϐ���` */
static HWND hwndMain; /* ���C���E�B���h�E�̃n���h�� */
static S_MAINWND_DATA mainWndData;
static TCHAR szCmdLineLocal[1024];
static HMIDIIN hMidiIn;
static HMIDIOUT hMidiOut;
static BYTE ctrlChangeValue = (BYTE)0;

/* *INDENT-OFF* */
static LRESULT (*wndProcTbl[MAINWND_MAX])( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam ) =
{
    onCreate          , /* WM_CREATE                     */
    onPaint           , /* WM_PAINT                      */
    onSize            , /* WM_SIZE                       */
    onMove            , /* WM_MOVE                       */
    onWindowPosChanged, /* WM_WINDOWPOSCHANGED           */
    onClose           , /* WM_CLOSE                      */
    onDestroy         , /* WM_DESTROY                    */
    onCommand         , /* WM_COMMAND                    */
    onKeyUp           , /* WM_KEYUP                      */
    onKeyDown         , /* WM_KEYDOWN                    */
    onChar            , /* WM_CHAR                       */
    onHscroll         , /* WM_HSCROLL                    */
    onVscroll         , /* WM_VSCROLL                    */
    onMouseWheel      , /* WM_MOUSEWHEEL                 */
    onSetFocus        , /* WM_SETFOCUS                   */
    onKillFocus       , /* WM_KILLFOCUS                  */
    onDropFiles       , /* WM_DROPFILES                  */
    onInitMenuPopup   , /* WM_INITMENUPOPUP              */
    onFindMsgString   , /* FINDMSGSTRING�̓o�^���b�Z�[�W */
    onTimer           , /* WM_TIMER                      */
    onApp             , /* WM_APP                        */
    onDefault           /* default                       */
};
/* *INDENT-ON* */

#define TIMER_ID      1
#define TIMER_CYCLE  100 /* msec */

#if 0
#define USE_EDITCONTROL
#endif

/**
 * ------------------------------------------------------------------------------
 * @brief  ���C���E�B���h�E�N���X�̓o�^�A�E�B���h�E�̐���
 * @param  szCmdLine
 * @param  nCmdShow
 * @param  hAccelPtr
 * @return �E�B���h�E�n���h��
 * @author wurly @date 2016�N10��10�� 18��26��52�b
 */
HWND
MainWndCreate( HINSTANCE hInst, PTSTR szAppName, LPSTR szCmdLine, int nCmdShow, HACCEL *hAccelPtr )
{
    WNDCLASS wc = {0};
    PTSTR pAppName = szAppName;
    HMENU hMenu = NULL;

    hwndMain = NULL;

    /* ���C���E�B���h�E�N���X */
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = (WNDPROC) WndProc;
    wc.cbClsExtra       = 0; /* �N���X�\���ׂ̂̈̒ǉ��̈��\�񂷂� */
    wc.cbWndExtra       = 0; /* �E�B���h�E�\���ׂ̂̈̒ǉ��̈��\�񂷂� */
    wc.hInstance        = hInst;
    wc.hIcon            = LoadIcon( hInst, "MAIN_ICON" );          /* �A�C�R�� */
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH) (COLOR_BTNFACE + 1); /* �w�i */
    wc.lpszMenuName     = pAppName;
    wc.lpszClassName    = pAppName;

    if( !RegisterClass(&wc) )
    { /* �E�B���h�E�N���X�̓o�^���s */
        MessageBox( NULL, TEXT("This program requires Windows 2000!"), pAppName, MB_ICONERROR );
    }
    else
    {
        memset( &mainWndData, 0, sizeof(mainWndData) );
        mainWndData.hInstance = hInst;
        mainWndData.szAppName = szAppName;

        /* �ݒ�̏����� */
        ConfigInit(mainWndData.hInstance,mainWndData.szAppName);

        /* ���j���[�̐��� */
        hMenu = MenuCreate();

        /* �A�N�Z�����[�^�̐��� */
        if( hAccelPtr != NULL )
        {
            *(hAccelPtr) = AccelCreate();
        }
        else
        {
            nop();
        }

        strncpy(szCmdLineLocal,szCmdLine,1024);

        /* ���C���E�B���h�E���쐬 */
        InitCommonControls(); /* commctrl.h�̃C���N���[�h�Acomctl32.lib�̃v���W�F�N�g�ւ̎Q�����K�v */
        hwndMain = CreateWindowEx( /* WS_EX_OVERLAPPEDWINDOW | */ WS_EX_ACCEPTFILES,
                                   pAppName, pAppName,
                                   WS_OVERLAPPEDWINDOW /*& ~WS_THICKFRAME*/ | WS_CLIPCHILDREN | WS_CLIPSIBLINGS /* | WS_VSCROLL | WS_HSCROLL*/,
                                   ConfigLoadDword(CONFIG_ID_WINDOW_POS_X) , ConfigLoadDword(CONFIG_ID_WINDOW_POS_Y) ,
                                   ConfigLoadDword(CONFIG_ID_WINDOW_POS_DX), ConfigLoadDword(CONFIG_ID_WINDOW_POS_DY),
                                   NULL, hMenu, hInst, NULL );

        if( hwndMain == NULL )
        { /* �E�B���h�E�̐������s */
            nop();
        }
        else
        {
            ShowWindow( hwndMain, nCmdShow ); /* ->WM_SIZE   */ /* �E�C���h�E��\�� */
            UpdateWindow( hwndMain );         /* ->WM_PAINT  */
        }
    }

    return hwndMain;
}

/********************************************************************************
 * ���e  : ���C���E�B���h�E���ŏ������郁�b�Z�[�W�𔻒肷��
 * ����  : MSG *msgPtr
 * �߂�l: BOOL
 ***************************************/
BOOL
IsMainWndMessage( MSG *msgPtr )
{
    BOOL bRtn = FALSE;

    if( (mainWndData.hDlgModeless) &&                      /* ���[�h���X�_�C�A���O�{�b�N�X�\�����ŁA */
        IsDialogMessage(mainWndData.hDlgModeless,msgPtr) ) /* �{���b�Z�[�W�����[�h���X�_�C�A���O�{�b�N�X�̃E�B���h�E�v���V�[�W���ŏ������ꂽ */
    {
        bRtn = TRUE;
    }
    else
    {
        nop();
    }

    return bRtn;
}

/********************************************************************************
 * ���e  : �E�B���h�E�v���V�[�W���BWINDOWS����󂯎�������b�Z�[�W�̏���
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
LRESULT CALLBACK
WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
#if 0
    DebugWndPrintf("WndProc,%X,%X,%X\r\n",message,wParam,lParam);
#endif
    return wndProcTbl[convertMSGtoINDEX(message)]( hwnd, message, wParam, lParam );
}

/********************************************************************************
 * �֐��� : ConvertMSGtoINDEX()
 * ����   : UINT message
 * �߂�l : WNDPRC_INDEX
 * ���e   : �E�B���h�E�Y���b�Z�[�W����Ή�����C���f�b�N�X�ɕϊ�����
 ***************************************/
static MAINWND_INDEX
convertMSGtoINDEX( UINT message )
{
    MAINWND_INDEX rtn;

    /* *INDENT-OFF* */
    switch( message )
    {
    case WM_CREATE          :rtn = MAINWND_ON_CREATE          ;break;
    case WM_PAINT           :rtn = MAINWND_ON_PAINT           ;break;
    case WM_SIZE            :rtn = MAINWND_ON_SIZE            ;break;
    case WM_MOVE            :rtn = MAINWND_ON_MOVE            ;break;
    case WM_WINDOWPOSCHANGED:rtn = MAINWND_ON_WINDOWPOSCHANGED;break;
    case WM_CLOSE           :rtn = MAINWND_ON_CLOSE           ;break;
    case WM_DESTROY         :rtn = MAINWND_ON_DESTROY         ;break;
    case WM_COMMAND         :rtn = MAINWND_ON_COMMAND         ;break;
    case WM_TIMER           :rtn = MAINWND_ON_TIMER           ;break;
    case WM_APP             :rtn = MAINWND_ON_APP             ;break;
    case WM_KEYUP           :rtn = MAINWND_ON_KEYUP           ;break;
    case WM_KEYDOWN         :rtn = MAINWND_ON_KEYDOWN         ;break;
    case WM_CHAR            :rtn = MAINWND_ON_CHAR            ;break;
    case WM_HSCROLL         :rtn = MAINWND_ON_HSCROLL         ;break;
    case WM_VSCROLL         :rtn = MAINWND_ON_VSCROLL         ;break;
    case WM_MOUSEWHEEL      :rtn = MAINWND_ON_MOUSEWHEEL      ;break;
    case WM_SETFOCUS        :rtn = MAINWND_ON_SETFOCUS        ;break;
    case WM_KILLFOCUS       :rtn = MAINWND_ON_KILLFOCUS       ;break;
    case WM_DROPFILES       :rtn = MAINWND_ON_DROPFILES       ;break;
    case WM_INITMENUPOPUP   :rtn = MAINWND_ON_INITMENUPOPUP   ;break;
    default                 :
        if( message == mainWndData.messageFindReplace )
        {
            rtn = MAINWND_ON_FINDMSGSTRING;
        }
        else
        {
            rtn = MAINWND_ON_DEFAULT;
        }
        break;
    }
    /* *INDENT-ON* */

    return rtn;
}

/********************************************************************************
 * ���e  : WM_CREATE �̏���
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onCreate( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    LRESULT rtn = 0;
    HDC        hdc;

    if( ConfigLoadDebugValue() == 0xDDDDDDDD )
    {
        mainWndData.hWndDebug = DebugWndCreate(mainWndData.hInstance,mainWndData.szAppName,TRUE);
        DebugWndPrintf("DEBUG=%08lX\r\n",ConfigLoadDebugValue());
    }
    else
    {
        nop();
    }

    ModalDlgInit(mainWndData.hInstance,mainWndData.szAppName);
    FileInitialize( hwnd ); /* �t�@�C��������     */

    SomeCtrlCreate( mainWndData.hInstance, mainWndData.szAppName, hwnd ); /* �R���g���[���𐶐� */
#if 0
    SomeCtrlCreate( mainWndData.hInstance, mainWndData.szAppName, hwnd ); /* �R���g���[���𐶐� */
#endif
    StsBarCreate( mainWndData.hInstance, mainWndData.szAppName, hwnd, TRUE ); /* �X�e�[�^�X�o�[�����A�f�t�H���g�\�� */

    MenuCheckItem( IDM_VIEW_STS_BAR );
    MenuCheckItem( IDM_EXTEND_NEWLINE_CRLF );

    if( (szCmdLineLocal[0] != '\0') &&
        (FileSetName(FILE_ID_BIN,szCmdLineLocal,FALSE)) )
    {
        DWORD dwSize;
        PBYTE dataPtr;

        dataPtr = FileReadByte(FILE_ID_BIN,&dwSize);
        doCaption( hwnd, FileGetTitleName(FILE_ID_BIN),FALSE );
    }
    else
    {
        doCaption( hwnd, "" , FALSE );
    }

    MidiInit();
    MidiKeyCtrlCreate(mainWndData.hInstance, mainWndData.szAppName,hwnd);

    return rtn;
}

/********************************************************************************
 * ���e  : WM_PAINT �̏���
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onPaint( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    return DefWindowProc( hwnd, message, wParam, lParam );
}

/********************************************************************************
 * ���e  : WM_SIZE �̏���
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onSize( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    LONG topSizeSum=0,bottomSizeSum=0;

    mainWndData.cxClient = LOWORD( lParam );
    mainWndData.cyClient = HIWORD( lParam );

    topSizeSum += SomeCtrlSize( mainWndData.cxClient, mainWndData.cyChar ); /* �R���g���[��   */
    bottomSizeSum += StsBarSize( mainWndData.cxClient, mainWndData.cyChar ); /* �X�e�[�^�X�o�[ */

    MidiKeyCtrlSize( mainWndData.cxClient, mainWndData.cyChar );

    return 0;
}

/********************************************************************************
 * ���e  : WM_MOVE �̏���
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onMove( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    mainWndData.xPos = LOWORD( lParam );
    mainWndData.yPos = HIWORD( lParam );

    return 0;
}

/********************************************************************************
 * ���e  : WM_WINDOWPOSCHANGED �̏���
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onWindowPosChanged( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    mainWndData.xWindowPos = ((WINDOWPOS *)lParam)->x ;
    mainWndData.yWindowPos = ((WINDOWPOS *)lParam)->y ;
    mainWndData.cxWindow   = ((WINDOWPOS *)lParam)->cx;
    mainWndData.cyWindow   = ((WINDOWPOS *)lParam)->cy;

    return DefWindowProc( hwnd, message, wParam, lParam );
}

/********************************************************************************
 * ���e  : WM_CLOSE �̏���
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onClose( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    if( mainWndData.bNeedSave && ((AskAboutSave( hwnd, FileGetTitleName(FILE_ID_BIN))) == IDCANCEL) )
    {
        nop();
    }
    else
    {
        int iCbNum;
        HWND hComboBox;

        ConfigSaveDword( CONFIG_ID_WINDOW_POS_X , mainWndData.xWindowPos );
        ConfigSaveDword( CONFIG_ID_WINDOW_POS_Y , mainWndData.yWindowPos );
        ConfigSaveDword( CONFIG_ID_WINDOW_POS_DX, mainWndData.cxWindow   );
        ConfigSaveDword( CONFIG_ID_WINDOW_POS_DY, mainWndData.cyWindow   );

#if 0
        hComboBox = SomeCtrlGetHWND(SOME_CTRL_MIDI_IN);
        iCbNum = SendMessage(hComboBox,CB_GETCURSEL,0,0);
        if( iCbNum != CB_ERR )
        {
            ConfigSaveDword(CONFIG_ID_MIDI_IN_NUM,iCbNum);
        }
        else
        {
            nop();
        }
#endif

        hComboBox = SomeCtrlGetHWND(SOME_CTRL_MIDI_OUT);
        iCbNum = SendMessage(hComboBox,CB_GETCURSEL,0,0);
        if( iCbNum != CB_ERR )
        {
            ConfigSaveDword(CONFIG_ID_MIDI_OUT_NUM,iCbNum);
        }
        else
        {
            nop();
        }

#if 0
        hComboBox = SomeCtrlGetHWND(SOME_CTRL_MIDI_KEY_IN);
        iCbNum = SendMessage(hComboBox,CB_GETCURSEL,0,0);
        if( iCbNum != CB_ERR )
        {
            ConfigSaveDword(CONFIG_ID_MIDI_KEY_IN_NUM,iCbNum);
        }
        else
        {
            nop();
        }
#endif

        DestroyWindow( hwnd );
    }

    return 0;
}

/********************************************************************************
 * ���e  : WM_DESTROY �̏���
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onDestroy( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    KillTimer( hwnd, TIMER_ID );
    MidiInClose();
    MidiOutClose();

    DestroyAcceleratorTable( mainWndData.hAccel );

    FileEnd();

    if( mainWndData.hWndDebug )
    {
        DestroyWindow( mainWndData.hWndDebug );
    }
    else
    {
        nop();
    }

    PostQuitMessage(0); /* WM_QUIT���b�Z�[�W���|�X�g���� */
    return 0;
}

/********************************************************************************
 * ���e  : WM_COMMAND �̏���
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam �ʏ��LOWORD���ʒm�R�[�h�B(�R���g���[������̒ʒm����HIWORD���ʒm�R�[�h�ALOWORD���R���g���[��ID)
 * ����  : LPARAM lParam �ʏ��NULL�B(�R���g���[������̒ʒm���̓E�B���h�E�n���h��)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onCommand( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    LRESULT rtn = 0;
    DWORD dwSize;
    PBYTE dataPtr;
    PTSTR strPtr;
    S_MODAL_DLG_PARAM modalDlgParam;
    static FINDREPLACE fr;
    static TCHAR strFind[80],strRep[80],strMsg[1024];
    RECT rect;

    { /* �R���g���[���A���j���[����̒ʒm */
        static TCHAR szMidiDev[50];
        int iCbNum,iDevNum;
        HWND hComboBox;
        WORD notifyCode = HIWORD(wParam);
        INT iChannelNum;
        INT data1;
        SCROLLINFO si;

//        DebugWndPrintf("onCommand 0x%08lX,0x%08lX,0x%08lX \r\n",message,wParam,lParam);

        if( (MIDIKEY_CTRL_ID_OFFSET+0 <= LOWORD(wParam)) &&
            LOWORD(wParam) <= MIDIKEY_CTRL_ID_OFFSET+MIDIKEY_CTRL_ID_MAX )
        {
            MIDIKEY_CTRL_ID keyNum = LOWORD(wParam)-MIDIKEY_CTRL_ID_OFFSET;

            iChannelNum = SendMessage(SomeCtrlGetHWND(SOME_CTRL_MIDI_CH),CB_GETCURSEL,0,0);

            MidiNoteOff(iChannelNum,keyNum);

//            DebugWndPrintf("OFF KEY %d\r\n",keyNum);
            GetWindowRect(hwnd,&rect);
            MoveWindow( hwnd, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, TRUE ) ;

        }
        else
        {
            nop();
        }

        /* notifyCode == CBN_SELENDOK */

        switch( LOWORD(wParam) )
        {
        case (SOME_CTRL_MIDI_OUT_OPEN_BUTTON+SOME_CTRL_ID_OFFSET):
            if( !hMidiOut )
            {
                DebugWndPrintf("OPEN MIDI_OUT\r\n");

                hComboBox = SomeCtrlGetHWND(SOME_CTRL_MIDI_OUT);
                iCbNum = SendMessage(hComboBox,CB_GETCURSEL,0,0);

                if( iCbNum != CB_ERR )
                {
                    iDevNum = SendMessage( hComboBox , CB_GETITEMDATA, iCbNum, (LPARAM)0 );
                    SomeCtrlGetText( SOME_CTRL_MIDI_OUT, szMidiDev );
                    DebugWndPrintf("%s:%d\r\n",szMidiDev,iDevNum);

                    hMidiOut = MidiOutOpen(iDevNum);
                }
                else
                {
                    DebugWndPrintf("Not Selected\r\n");
                }

                if( hMidiOut )
                {
                    SetWindowText( SomeCtrlGetHWND(SOME_CTRL_MIDI_OUT_OPEN_BUTTON), TEXT("Close") );
                    SomeCtrlDisable( SOME_CTRL_MIDI_OUT );
                }
                else
                {
                }
            }
            else
            {
                MidiOutClose();
                hMidiOut = FALSE;
                SomeCtrlEnable( SOME_CTRL_MIDI_OUT );
                SetWindowText( SomeCtrlGetHWND(SOME_CTRL_MIDI_OUT_OPEN_BUTTON), TEXT("Open") );
            }
            break;

        case (SOME_CTRL_MIDI_PROGRAM_CHANGE_BUTTON+SOME_CTRL_ID_OFFSET):
            iChannelNum = SendMessage(SomeCtrlGetHWND(SOME_CTRL_MIDI_CH),CB_GETCURSEL,0,0);
            data1 = SendMessage(SomeCtrlGetHWND(SOME_CTRL_MIDI_PROGRAM_CHANGE),CB_GETCURSEL,0,0);
            MidiOutData(iChannelNum,0xC0,data1,0x00);
            break;

        case (SOME_CTRL_MIDI_CTRL_CHANGE_BUTTON+SOME_CTRL_ID_OFFSET):
            iChannelNum = SendMessage(SomeCtrlGetHWND(SOME_CTRL_MIDI_CH),CB_GETCURSEL,0,0);
            data1 = SendMessage(SomeCtrlGetHWND(SOME_CTRL_MIDI_CTRL_CHANGE_KIND),CB_GETCURSEL,0,0);
            si.cbSize = sizeof(SCROLLINFO);
            si.fMask  = SIF_TRACKPOS;
            GetScrollInfo(SomeCtrlGetHWND(SOME_CTRL_MIDI_CTRL_CHANGE_VALUE),SB_CTL,&si);
//            DebugWndPrintf("ScrollPos:%d\r\n",si.nTrackPos);
            MidiOutData(iChannelNum,0xB0,data1,si.nTrackPos);
            break;

        case IDM_FILE_NEW:
            if( mainWndData.bNeedSave && ((AskAboutSave( hwnd, FileGetTitleName(FILE_ID_BIN))) == IDCANCEL) )
            {
                nop();
            }
            else
            {
                mainWndData.bNeedSave = FALSE;
                doCaption( hwnd, "", FALSE);
            }
            break;
        case IDM_FILE_OPEN:
            if( mainWndData.bNeedSave && ((AskAboutSave( hwnd, FileGetTitleName(FILE_ID_BIN))) == IDCANCEL) )
            {
                nop();
            }
            else
            {
                if( FileOpenDlg( hwnd,FILE_ID_BIN ) )
                {
                    mainWndData.bNeedSave = FALSE;
                    dataPtr = FileReadByte(FILE_ID_BIN,&dwSize);
                    doCaption( hwnd, FileGetTitleName(FILE_ID_BIN), FALSE );
                }
                else
                {
                    /* �L�����Z�����ꂽ�B���̓G���[ */
                }
            }
            break;
        case IDM_FILE_SAVE:
            break;
        case IDM_FILE_SAVE_AS:
            break;

        case IDM_VIEW_STS_BAR:
            if( MenuInqItemChecked(IDM_VIEW_STS_BAR) )
            {
                MenuUnCheckItem( IDM_VIEW_STS_BAR );
                StsBarShowWindow( FALSE );
            }
            else
            {
                MenuCheckItem( IDM_VIEW_STS_BAR );
                StsBarShowWindow( TRUE );
            }
            SendMessage(hwnd,WM_SIZE,0,MAKELONG(mainWndData.cxClient,mainWndData.cyClient));
            break;

        case IDM_FILE_EXIT:
            SendMessage( hwnd, WM_CLOSE, 0, 0 );
            break;

        case IDM_HELP_ABOUT:
            ModalDlg( MODAL_DLG_ID_ABOUT, &modalDlgParam, hwnd, mainWndData.xPos, mainWndData.yPos );
            break;

        default:
            break;
        }
    }

    return rtn;
}

/********************************************************************************
 * ���e  : WM_KEYUP �̏���
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onKeyUp( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    LRESULT rtn = 0;

    return rtn;
}

/********************************************************************************
 * ���e  : WM_KEYDOWN �̏���
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onKeyDown( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    LRESULT rtn = 0;

    return rtn;
}

/********************************************************************************
 * ���e  : WM_CHAR �̏���
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onChar( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    LRESULT rtn = 0;

    return rtn;
}

/********************************************************************************
 * ���e  : WM_HSCROLL �̏���
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onHscroll( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    LRESULT rtn = 0;

    if( SomeCtrlGetHWND(SOME_CTRL_MIDI_CTRL_CHANGE_VALUE) == (HWND)lParam )
    {
        HWND hwndScroll,hwndStatic;
        TCHAR szBuffer[128];

        hwndScroll = SomeCtrlGetHWND(SOME_CTRL_MIDI_CTRL_CHANGE_VALUE);
        hwndStatic = SomeCtrlGetHWND(SOME_CTRL_MIDI_CTRL_CHANGE_VALUE_STATIC);

//    DebugWndPrintf("HSCROLL,0x%08lX,0x%08lX\r\n",wParam,lParam);
//    DebugWndPrintf("hwnd,0x%08lX\r\n",hwndScroll);

        switch( LOWORD(wParam) )
        {
        case SB_LINERIGHT:
            ctrlChangeValue++;
            break;
        case SB_LINELEFT:
            ctrlChangeValue--;
            break;
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
            ctrlChangeValue = HIWORD(wParam);
            break;
        default:
            break;
        }

        ctrlChangeValue = min(max(0,ctrlChangeValue),127);

        SetScrollPos(hwndScroll,SB_CTL,ctrlChangeValue,TRUE);

        wsprintf(szBuffer,"%d",ctrlChangeValue);
        SetWindowText( hwndStatic, szBuffer );
    }
    else
    {
        nop();
    }

    return rtn;
}

/********************************************************************************
 * ���e  : WM_VSCROLL �̏���
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onVscroll( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    LRESULT rtn = 0;

    return rtn;
}

/********************************************************************************
 * ���e  : WM_MOUSEWHEEL ����������
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onMouseWheel( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    LRESULT rtn = 0;

    return rtn;
}

/********************************************************************************
 * ���e  : WM_SETFOCUS ����������
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onSetFocus( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    LRESULT rtn = 0;

    return rtn;
}

/********************************************************************************
 * ���e  : WM_KILLFOCUS ����������
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onKillFocus( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    LRESULT rtn = 0;

    return rtn;
}

/********************************************************************************
 * ���e  : WM_DROPFILES ����������
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onDropFiles( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    LRESULT rtn = 0;
    static TCHAR szFileName[1024];
    DWORD dwSize;
    PBYTE dataPtr;

    if( mainWndData.bNeedSave && ((AskAboutSave( hwnd, FileGetTitleName(FILE_ID_BIN))) == IDCANCEL) )
    {
        nop();
    }
    else
    {
        mainWndData.bNeedSave = FALSE;
        doCaption( hwnd, FileGetTitleName(FILE_ID_BIN),FALSE );
    }

    return rtn;
}

/********************************************************************************
 * ���e  : WM_INITMENUPOPUP ����������
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onInitMenuPopup( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    LRESULT rtn = 0;

    return rtn;
}

/********************************************************************************
 * ���e  : FINDMSGSTRING�̓o�^���b�Z�[�W �̏���
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onFindMsgString( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    LRESULT rtn = 0;

    return rtn;
}

/********************************************************************************
 * ���e  : WM_TIMER ����������
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onTimer( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    LRESULT rtn = 0;
    TCHAR szCtrlTemp[50];

#if 0
    SomeCtrlGetText( SOME_CTRL_MIDI_IN_OPEN_BUTTON, szCtrlTemp );

    if( !strcmp( szCtrlTemp, TEXT("Close")) )
    {
        MidiCycleProc();
        JvCtrlCycleProc();
    }
    else
    {
        nop();
    }
#endif

    SetTimer( hwnd, TIMER_ID, TIMER_CYCLE, NULL );

    return rtn;
}

/********************************************************************************
 * ���e  : WM_APP �̏���
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onApp( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    LRESULT rtn = 0;
    RECT rect;
    MIDIKEY_CTRL_ID keyNum = LOWORD(wParam)-MIDIKEY_CTRL_ID_OFFSET;
    INT iChannelNum;

    iChannelNum = SendMessage(SomeCtrlGetHWND(SOME_CTRL_MIDI_CH),CB_GETCURSEL,0,0);

    MidiNoteOn(iChannelNum,keyNum,127);

//    DebugWndPrintf("ON KEY %d\r\n",keyNum);
    GetWindowRect(hwnd,&rect);
    MoveWindow( hwnd, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, TRUE );

    switch( LOWORD(wParam) )
    {
    default:
        break;
    }

    return rtn;
}

/********************************************************************************
 * ���e  : ���b�Z�[�W�̃f�t�H���g����
 * ����  : HWND hwnd
 * ����  : UINT message
 * ����  : WPARAM wParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * ����  : LPARAM lParam (���e�̓��b�Z�[�W�̎�ނɂ��قȂ�)
 * �߂�l: LRESULT
 ***************************************/
static LRESULT
onDefault( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    return DefWindowProc( hwnd, message, wParam, lParam );
}

/********************************************************************************
 * ���e  :
 * ����  : HWND hwnd
 * ����  : TCHAR *szMessageFormat, ...
 * �߂�l: int
 ***************************************/
int
okMessage( HWND hwnd, TCHAR *szMessageFormat, ... )
{
    va_list vaArgs;
    TCHAR szBuffer[64 + MAX_PATH] ;
    BOOL bResult = (BOOL)FALSE;

    va_start(vaArgs, szMessageFormat);
    if( wvsprintf(szBuffer, szMessageFormat, vaArgs) != EOF )
    {
        bResult = (BOOL)TRUE;
    }
    else
    {
        /* do nothing */
    }
    va_end(vaArgs);

    if( bResult )
    {
        /* do nothing */
    }
    else
    {
        szBuffer[0] = '\0';
    }

    return MessageBox( hwnd, szBuffer, mainWndData.szAppName, MB_OK | MB_ICONINFORMATION );
}

/********************************************************************************
 * ���e  :
 * ����  : HWND hwnd
 * ����  : TCHAR* szTitleName
 * ����  : BOOL bNeedSave
 * �߂�l: �Ȃ�
 ***************************************/
void
doCaption( HWND hwnd, TCHAR* szTitleName, BOOL bNeedSave )
{
     TCHAR szCaption[64 + MAX_PATH];

#if 1
     wsprintf( szCaption, TEXT ("%s"), mainWndData.szAppName );
#else
     if( bNeedSave )
     {
         wsprintf( szCaption, TEXT ("*%s - %s"), (szTitleName[0] ? szTitleName : TEXT("����")),mainWndData.szAppName );
     }
     else
     {
         wsprintf( szCaption, TEXT ("%s - %s"), (szTitleName[0] ? szTitleName : TEXT("����")),mainWndData.szAppName );
     }
#endif

     SetWindowText( hwnd, szCaption );
}

/********************************************************************************
 * ���e  :
 * ����  : HWND hwnd
 * ����  : TCHAR* szTitleName
 * �߂�l: �Ȃ�
 ***************************************/
short
AskAboutSave( HWND hwnd, TCHAR * szTitleName )
{
    TCHAR szBuffer[64 + MAX_PATH];
    int   iReturn;

    wsprintf(szBuffer, TEXT("�t�@�C�� %s �̓��e�͕ύX����Ă��܂��B\n\n�ύX��ۑ����܂���?"), szTitleName[0] ? szTitleName : TEXT("����") );

    iReturn = MessageBox( hwnd,szBuffer,mainWndData.szAppName,MB_YESNOCANCEL|MB_ICONEXCLAMATION );

    if( iReturn == IDYES )
    {
        if( !SendMessage( hwnd,WM_COMMAND,IDM_FILE_SAVE,0) )
        {
            iReturn = IDCANCEL;
        }
        else
        {
            nop();
        }
    }
    else
    {
        nop();
    }

    return iReturn;
}

#if 0
/********************************************************************************
 * ���e  : WM_APP �̏���
 * ����  : SOME_CTRL_ID id
 * �߂�l: INT
 ***************************************/
static INT
someCtrlGetCbNum( SOME_CTRL_ID id )
{
    return 0;
}
#endif
