#ifndef DEBUGWND_H

/********************************************************************************
 * 内容  : デバッグウィンドウクラスの登録、ウィンドウの生成
 * 引数  : HINSTANCE hInst
 * 引数  : PTSTR szAppName
 * 引数  : int nCmdShow
 * 戻り値: HWND
 ***************************************/
HWND DebugWndCreate( HINSTANCE hInst, PTSTR szAppName, int nCmdShow );

/********************************************************************************
 * 内容  : デバッグウィンドウ内で処理するメッセージを判定する
 * 引数  : MSG *msgPtr
 * 戻り値: BOOL
 ***************************************/
BOOL IsDebugWndMessage( MSG *msgPtr );

/********************************************************************************
 * 内容   : デバッグウィンドウへの printf
 * 引数   : PTSTR ptstrFormat, ...
 * 戻り値 : BOOL
 ********************************************************************************/
BOOL DebugWndPrintf( PTSTR ptstrFormat, ...);

/********************************************************************************
 * 内容   : デバッグウィンドウへの printf (上書き)
 * 引数   : PTSTR ptstrFormat, ...
 * 戻り値 : BOOL
 ********************************************************************************/
BOOL DebugWndPrintfOW( PTSTR ptstrFormat, ...);

/********************************************************************************
 * 内容   : デバッグウィンドウの最終行クリア
 * 引数   : なし
 * 戻り値 : BOOL
 ********************************************************************************/
BOOL DebugWndClearLine( void );

#define DEBUGWND_H
#endif /* DEBUGWND_H */
