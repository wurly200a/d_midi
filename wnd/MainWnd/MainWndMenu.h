#ifndef MAINWND_MENU_H

/********************************************************************************
 * 内容  : メニューの生成
 * 引数  : なし
 * 戻り値: HMENU
 ***************************************/
HMENU MenuCreate( void );

/********************************************************************************
 * 内容  : アクセラレータの生成
 * 引数  : なし
 * 戻り値: HACCEL
 ***************************************/
HACCEL AccelCreate( void );

/********************************************************************************
 * 内容  : 指定の項目がチェックされているか問い合わせ
 * 引数  : UINT itemID
 * 戻り値: BOOL
 ***************************************/
BOOL MenuInqItemChecked( UINT itemID );

/********************************************************************************
 * 内容  : 指定の項目のチェックを付ける
 * 引数  : UINT itemID
 * 戻り値: なし
 ***************************************/
void MenuCheckItem( UINT itemID );

/********************************************************************************
 * 内容  : 指定の項目のチェックを外す
 * 引数  : UINT itemID
 * 戻り値: なし
 ***************************************/
void MenuUnCheckItem( UINT itemID );

/********************************************************************************
 * 内容  : 指定の項目を有効にする
 * 引数  : UINT itemID
 * 戻り値: なし
 ***************************************/
void MenuEnableItem( UINT itemID );

/********************************************************************************
 * 内容  : 指定の項目を無効にする
 * 引数  : UINT itemID
 * 戻り値: なし
 ***************************************/
void MenuUnEnableItem( UINT itemID );

#define MAINWND_MENU_H
#endif /* MAINWND_MENU_H */
