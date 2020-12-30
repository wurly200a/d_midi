#ifndef MIDIKEY_CTRL_H
#define MIDIKEY_CTRL_H

typedef INT MIDIKEY_CTRL_ID;
#define MIDIKEY_CTRL_ID_MAX 128

#define MIDIKEY_CTRL_ID_OFFSET 50
#define MY_EX_STYLE (WS_EX_OVERLAPPEDWINDOW)

/********************************************************************************
 * 内容  : 登録された全てのコントロールを生成する
 * 引数  : HINSTANCE hInst
 * 引数  : PTSTR szAppName
 * 引数  : HWND hwnd 親ウィンドウのハンドラ
 * 戻り値: BOOL
 ***************************************/
BOOL MidiKeyCtrlCreate( HINSTANCE hInst, PTSTR szAppName, HWND hwnd );

/********************************************************************************
 * 内容  : 登録された全てのコントロールのサイズを調整する
 * 引数  : int cxClient
 * 引数  : int cyClient
 * 戻り値: LONG コントロールを配置する矩形の縦方向のサイズ
 ***************************************/
LONG MidiKeyCtrlSize( int cxClient,int cyClient );

/********************************************************************************
 * 内容  : コントロールのウィンドウハンドラを取得する
 * 引数  : MIDIKEY_CTRL_ID id
 * 戻り値: HWND
 ***************************************/
HWND MidiKeyCtrlGetHWND( MIDIKEY_CTRL_ID id );

#endif /* MIDIKEY_CTRL_H */
