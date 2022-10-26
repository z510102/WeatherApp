//=============================================================================
// �L�[�{�[�h���͏��� [input_keyboard.h]
// Author : ���� ��
//=============================================================================
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "input.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();								// �R���X�g���N�^
	~CInputKeyboard();								// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	bool GetPress(int nKey);						// ���͏�Ԃ̎擾����(�v���X)
	bool GetTrigger(int nKey);						// ���͏�Ԃ̎擾����(�g���K�[)

private:
	BYTE m_aKeyState[256];							// �L�[�̏��
	BYTE m_aKeyStateTrigger[256];					// �L�[�̏��(�g���K�[)
};

#endif	// _INPUT_KEYBOARD_H_