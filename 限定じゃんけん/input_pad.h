//=============================================================================
// �Q�[���p�b�h���͏��� [input_pad.h]
// Author : ���� ��
//=============================================================================
#ifndef _INPUT_PAD_H_
#define _INPUT_PAD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "input.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CInputPad : public CInput
{
public:
	typedef enum {
		PAD_INPUTTYPE_LSTICK_UP = 0,
		PAD_INPUTTYPE_LSTICK_DOWN,
		PAD_INPUTTYPE_LSTICK_LEFT,
		PAD_INPUTTYPE_LSTICK_RIGHT,
		PAD_INPUTTYPE_RSTICK_UP,
		PAD_INPUTTYPE_RSTICK_DOWN,
		PAD_INPUTTYPE_RSTICK_LEFT,
		PAD_INPUTTYPE_RSTICK_RIGHT,
		PAD_INPUTTYPE_LEFT,
		PAD_INPUTTYPE_RIGHT,
		PAD_INPUTTYPE_MAX
	} PAD_INPUTTYPE;

	CInputPad();									// �R���X�g���N�^
	~CInputPad();									// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	bool GetPress(int nInput, int nNum);			// ���͏�Ԃ̎擾����(�v���X)
	bool GetTrigger(int nInput, int nNum);			// ���͏�Ԃ̎擾����(�g���K�[)
	bool GetButtonPress(int nButton, int nNum);		// �{�^�����͏�Ԃ̎擾����(�v���X)
	bool GetButtonTrigger(int nButton, int nNum);	// �{�^�����͏�Ԃ̎擾����(�g���K�[)

private:
	// �ő�l����4(XUSER_MAX_COUNT)�����A�����2�l�Ԃ�p��
	XINPUT_STATE m_aState[MAX_PLAYER_NUM];			// ���͂̏��
	XINPUT_STATE m_aStateTrigger[MAX_PLAYER_NUM];	// ���͂̏��(�g���K�[)
	XINPUT_VIBRATION m_aVibration[MAX_PLAYER_NUM];	// �o�C�u���[�V����
	int m_CntVibration[MAX_PLAYER_NUM];
	bool m_bConnect[MAX_PLAYER_NUM];				// �ڑ����Ă��邩�ǂ���
	bool m_bVibration[MAX_PLAYER_NUM];
};

#endif  // _INPUT_PAD_H_