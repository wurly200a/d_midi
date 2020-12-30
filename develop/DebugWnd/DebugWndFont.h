#ifndef DEBUG_FONT_H

/********************************************************************************
 * ���e  : �t�H���g������
 * ����  : �Ȃ�
 * �߂�l: �Ȃ�
 ***************************************/
void DebugFontInit( void );

/********************************************************************************
 * ���e  : �t�H���g�I��
 * ����  : HWND hwnd
 * �߂�l: BOOL (TRUE:OK�������ꂽ�AFALSE:�L�����Z�����ꂽ)
 ***************************************/
BOOL DebugFontChooseFont( HWND hwnd );

/********************************************************************************
 * ���e  : �_���t�H���g�擾
 * ����  : �Ȃ�
 * �߂�l: LOGFONT *
 ***************************************/
LOGFONT *DebugFontGetLogFont( void );

#define DEBUG_FONT_H
#endif /* DEBUG_FONT_H */