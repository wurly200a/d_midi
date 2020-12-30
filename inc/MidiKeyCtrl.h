#ifndef MIDIKEY_CTRL_H
#define MIDIKEY_CTRL_H

typedef INT MIDIKEY_CTRL_ID;
#define MIDIKEY_CTRL_ID_MAX 128

#define MIDIKEY_CTRL_ID_OFFSET 50
#define MY_EX_STYLE (WS_EX_OVERLAPPEDWINDOW)

/********************************************************************************
 * ���e  : �o�^���ꂽ�S�ẴR���g���[���𐶐�����
 * ����  : HINSTANCE hInst
 * ����  : PTSTR szAppName
 * ����  : HWND hwnd �e�E�B���h�E�̃n���h��
 * �߂�l: BOOL
 ***************************************/
BOOL MidiKeyCtrlCreate( HINSTANCE hInst, PTSTR szAppName, HWND hwnd );

/********************************************************************************
 * ���e  : �o�^���ꂽ�S�ẴR���g���[���̃T�C�Y�𒲐�����
 * ����  : int cxClient
 * ����  : int cyClient
 * �߂�l: LONG �R���g���[����z�u�����`�̏c�����̃T�C�Y
 ***************************************/
LONG MidiKeyCtrlSize( int cxClient,int cyClient );

/********************************************************************************
 * ���e  : �R���g���[���̃E�B���h�E�n���h�����擾����
 * ����  : MIDIKEY_CTRL_ID id
 * �߂�l: HWND
 ***************************************/
HWND MidiKeyCtrlGetHWND( MIDIKEY_CTRL_ID id );

#endif /* MIDIKEY_CTRL_H */
