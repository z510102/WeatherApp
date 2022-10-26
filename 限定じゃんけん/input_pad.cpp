//=============================================================================
// �Q�[���p�b�h���͏��� [input_pad.cpp]
// Author : ���� ��
//=============================================================================
#include "input_pad.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInputPad::CInputPad()
{
	// �v���C���[�̐l���Ԃ�J��Ԃ�
	for (int nCntPad = 0; nCntPad < MAX_PLAYER_NUM; nCntPad++)
	{
		// �������̃N���A
		ZeroMemory(&m_aState[nCntPad], sizeof(XINPUT_STATE));			// �L�[���(�v���X)
		ZeroMemory(&m_aStateTrigger, sizeof(XINPUT_STATE));				// �L�[���(�g���K�[)
		ZeroMemory(&m_aVibration[nCntPad], sizeof(XINPUT_VIBRATION));	// �o�C�u���[�V�������
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInputPad::~CInputPad()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CInputPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	// ��{�N���X�̏���������
	CInput::Init(hInstance, hWnd);

	// �ϐ��̏�����
	for (int nCntPad = 0; nCntPad < MAX_PLAYER_NUM; nCntPad++)
	{
		m_bConnect[nCntPad] = false;
	}

	XINPUT_STATE state[MAX_PLAYER_NUM];
	for (int nCntPad = 0; nCntPad < MAX_PLAYER_NUM; nCntPad++)
	{
		ZeroMemory(&state[nCntPad], sizeof(XINPUT_STATE));
	}

	// �R���g���[���[���ڑ�����Ă��邩�m�F����
	for (int nCntPad = 0; nCntPad < MAX_PLAYER_NUM; nCntPad++)
	{
		DWORD dwResult = XInputGetState(nCntPad, &state[nCntPad]);

		if (dwResult == ERROR_SUCCESS)
		{
			// �R���g���[���[�͐ڑ����Ă�����
			m_bConnect[nCntPad] = true;
		}
		else
		{
			// �R���g���[���[�͐ڑ�����Ă��Ȃ����
			m_bConnect[nCntPad] = false;
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CInputPad::Uninit(void)
{
	// ���͏����j���[�g�����ɂ���
	XInputEnable(false);

	// ��{�N���X�̏I������
	CInput::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CInputPad::Update(void)
{
	XINPUT_STATE state[MAX_PLAYER_NUM];

	for (int nCntPad = 0; nCntPad < MAX_PLAYER_NUM; nCntPad++)
	{
		ZeroMemory(&state[nCntPad], sizeof(XINPUT_STATE));
	}

	for (int nCntPad = 0; nCntPad < MAX_PLAYER_NUM; nCntPad++)
	{
		DWORD dwResult = XInputGetState(0, &state[nCntPad]);

		// �R���g���[���[���ڑ�����Ă��邩�m�F����
		if (dwResult == ERROR_SUCCESS)
		{
			m_bConnect[nCntPad] = true;
		}
		else
		{
			m_bConnect[nCntPad] = false;
		}
	}

	for (int nCntPad = 0; nCntPad < MAX_PLAYER_NUM; nCntPad++)
	{
		if (XInputGetState(nCntPad, &state[nCntPad]) == ERROR_SUCCESS)
		{
			// ���X�e�B�b�N�̃f�b�h�]�[���̐ݒ�
			if ((m_aState[nCntPad].Gamepad.sThumbLX <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				m_aState[nCntPad].Gamepad.sThumbLX >= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
				(m_aState[nCntPad].Gamepad.sThumbLY <= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
					m_aState[nCntPad].Gamepad.sThumbLY >= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
			{
				m_aState[nCntPad].Gamepad.sThumbLX = 0;
				m_aState[nCntPad].Gamepad.sThumbLY = 0;
			}

			// �E�X�e�B�b�N�̃f�b�h�]�[���̐ݒ�
			if ((m_aState[nCntPad].Gamepad.sThumbRX <= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
				m_aState[nCntPad].Gamepad.sThumbRX >= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
				(m_aState[nCntPad].Gamepad.sThumbRY <= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
					m_aState[nCntPad].Gamepad.sThumbRY >= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
			{
				m_aState[nCntPad].Gamepad.sThumbRX = 0;
				m_aState[nCntPad].Gamepad.sThumbRY = 0;
			}

			m_aStateTrigger[nCntPad] = m_aState[nCntPad];
			m_aState[nCntPad] = state[nCntPad];
		}
	}
}

//=============================================================================
// ���͏�Ԃ̎擾����(�v���X)
//=============================================================================
bool CInputPad::GetPress(int nInput, int nNum)
{
	// �ڑ����Ă��Ȃ��ꍇ��false��Ԃ��ď������I��������
	//�����ꂪ�Ȃ��Ə���ɓ��͂��ꑱ����
	if (m_bConnect[nNum] == false)
	{
		return false;
	}

	switch (nInput)
	{
	case PAD_INPUTTYPE_LSTICK_UP:	// ���X�e�B�b�N�F��
		return m_aState[nNum].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_DOWN:	// ���X�e�B�b�N�F��
		return m_aState[nNum].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_LEFT:	// ���X�e�B�b�N�F��
		return m_aState[nNum].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_RIGHT:// ���X�e�B�b�N�F�E
		return m_aState[nNum].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_UP:	// �E�X�e�B�b�N�F��
		return m_aState[nNum].Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_DOWN:	// �E�X�e�B�b�N�F��
		return m_aState[nNum].Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_LEFT:	// �E�X�e�B�b�N�F��
		return m_aState[nNum].Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_RIGHT:// �E�X�e�B�b�N�F�E
		return m_aState[nNum].Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case PAD_INPUTTYPE_LEFT:		// �g���K�[�F��
		return m_aState[nNum].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;
	case PAD_INPUTTYPE_RIGHT:		// �g���K�[�F�E
		return m_aState[nNum].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;
	default:
		return false;
		break;
	}
}

//=============================================================================
// ���͏�Ԃ̎擾����(�g���K�[)
//=============================================================================
bool CInputPad::GetTrigger(int nInput, int nNum)
{
	if (m_bConnect[nNum] == false)
	{
		return false;
	}

	switch (nInput)
	{
	case PAD_INPUTTYPE_LSTICK_UP:	// ���X�e�B�b�N�F��
		return (((m_aStateTrigger[nNum].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_DOWN:	// ���X�e�B�b�N�F��
		return (((m_aStateTrigger[nNum].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_LEFT:	// ���X�e�B�b�N�F��
		return (((m_aStateTrigger[nNum].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_LSTICK_RIGHT:// ���X�e�B�b�N�F�E
		return (((m_aStateTrigger[nNum].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_UP:	// �E�X�e�B�b�N�F��
		return (((m_aStateTrigger[nNum].Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_DOWN:	// �E�X�e�B�b�N�F��
		return (((m_aStateTrigger[nNum].Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_LEFT:	// �E�X�e�B�b�N�F��
		return (((m_aStateTrigger[nNum].Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_RSTICK_RIGHT:// �E�X�e�B�b�N�F�E
		return (((m_aStateTrigger[nNum].Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_aState[nNum].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case PAD_INPUTTYPE_LEFT:	// �g���K�[�F��
		return (((m_aStateTrigger[nNum].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_aState[nNum].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	case PAD_INPUTTYPE_RIGHT:	// �g���K�[�F�E
		return (((m_aStateTrigger[nNum].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_aState[nNum].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	default:
		return false;
		break;
	}
}

//=============================================================================
// �{�^�����͏�Ԃ̎擾����(�v���X)
//=============================================================================
bool CInputPad::GetButtonPress(int nButton, int nNum)
{
	if (m_bConnect[nNum] == false)
	{
		return false;
	}

	return m_aState[nNum].Gamepad.wButtons & nButton ? true : false;
}

//=============================================================================
// �{�^�����͏�Ԃ̎擾����(�g���K�[)
//=============================================================================
bool CInputPad::GetButtonTrigger(int nButton, int nNum)
{
	if (m_bConnect[nNum] == false)
	{
		return false;
	}

	return (((m_aStateTrigger[nNum].Gamepad.wButtons & nButton) == false) && (m_aState[nNum].Gamepad.wButtons & nButton)) ? true : false;
}

//=======================================================================
// �o�C�u���[�V�����ݒ�
//= ======================================================================
//void CInputPad::SetVibration(int nLeftSpeed, int nRightSpeed, int nCntEnd, int nCntPad)
//{
//	m_avibration[nCntPad].wLeftMotorSpeed = nLeftSpeed;
//	m_avibration[nCntPad].wRightMotorSpeed = nRightSpeed;
//	XInputSetState(nCntPad, &m_avibration[nCntPad]);
//	m_aCntVibration[nCntPad] = nCntEnd;
//	m_aVibration[nCntPad] = true;
//}