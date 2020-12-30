#ifndef SOME_CTRL_H

typedef enum
{
    SOME_CTRL_GROUP_ALWAYS,
    SOME_CTRL_GROUP_SYSTEM,
    SOME_CTRL_GROUP_PATCH ,
    SOME_CTRL_GROUP_MAX
}SOME_CTRL_GROUP_ID;

typedef enum
{
    SOME_CTRL_MIDI_OUT_STATIC               ,
    SOME_CTRL_MIDI_OUT                      ,
    SOME_CTRL_MIDI_OUT_OPEN_BUTTON          ,
    SOME_CTRL_MIDI_CH_STATIC                ,
    SOME_CTRL_MIDI_CH                       ,
    SOME_CTRL_MIDI_PROGRAM_CHANGE_STATIC    ,
    SOME_CTRL_MIDI_PROGRAM_CHANGE           ,
    SOME_CTRL_MIDI_PROGRAM_CHANGE_BUTTON    ,
    SOME_CTRL_MIDI_CTRL_CHANGE_STATIC       ,
    SOME_CTRL_MIDI_CTRL_CHANGE_KIND         ,
    SOME_CTRL_MIDI_CTRL_CHANGE_VALUE        ,
    SOME_CTRL_MIDI_CTRL_CHANGE_VALUE_STATIC ,
    SOME_CTRL_MIDI_CTRL_CHANGE_BUTTON       ,
    SOME_CTRL_MIDI_MESSAGE_STATIC           ,
    SOME_CTRL_MIDI_MESSAGE                  ,
    SOME_CTRL_MAX
}SOME_CTRL_ID;

#define SOME_CTRL_ID_OFFSET 10
#define MY_EX_STYLE (WS_EX_OVERLAPPEDWINDOW)

/********************************************************************************
 * 内容  : 登録された全てのコントロールを生成する
 * 引数  : HINSTANCE hInst
 * 引数  : PTSTR szAppName
 * 引数  : HWND hwnd 親ウィンドウのハンドラ
 * 戻り値: BOOL
 ***************************************/
BOOL SomeCtrlCreate( HINSTANCE hInst, PTSTR szAppName, HWND hwnd );

/********************************************************************************
 * 内容  : 指定のグループのコントロールを表示する
 * 引数  : SOME_CTRL_GROUP_ID groupId
 * 戻り値: BOOL
 ***************************************/
BOOL SomeCtrlGroupDisplay( SOME_CTRL_GROUP_ID groupId );

/********************************************************************************
 * 内容  : 登録された全てのコントロールのサイズを調整する
 * 引数  : int cxClient
 * 引数  : int cyClient
 * 戻り値: LONG コントロールを配置する矩形の縦方向のサイズ
 ***************************************/
LONG SomeCtrlSize( int cxClient,int cyClient );

/********************************************************************************
 * 内容  : コントロールのウィンドウハンドラを取得する
 * 引数  : SOME_CTRL_ID id
 * 戻り値: HWND
 ***************************************/
HWND SomeCtrlGetHWND( SOME_CTRL_ID id );

/********************************************************************************
 * 内容  : コントロールを有効にする
 * 引数  : SOME_CTRL_ID id
 * 戻り値: なし
 ***************************************/
void SomeCtrlEnable( SOME_CTRL_ID id );

/********************************************************************************
 * 内容  : コントロールを無効にする
 * 引数  : SOME_CTRL_ID id
 * 戻り値: なし
 ***************************************/
void SomeCtrlDisable( SOME_CTRL_ID id );

/********************************************************************************
 * 内容  : コントロールからテキストを取得する
 * 引数  : SOME_CTRL_ID id
 * 引数  : PTSTR ptstrText
 * 戻り値: BOOL
 ***************************************/
BOOL SomeCtrlGetText( SOME_CTRL_ID id, PTSTR ptstrText );

#define SOME_CTRL_H
#endif /* SOME_CTRL_H */
