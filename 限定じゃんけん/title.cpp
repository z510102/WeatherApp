//=============================================================================
// �^�C�g����� [title.cpp]
// Author : ���� ��
// Author : ���}�� �V��
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "title.h"
#include "manager.h"
#include "texture.h"
#include "scene2D.h"
#include "ui.h"
#include "fade.h"
#include "input_keyboard.h"
#include "input_pad.h"
#include "sound.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
bool CTitle::m_bPush = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	// �ϐ��̃N���A
	memset(&m_apUi, NULL, sizeof(m_apUi));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�擾����
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	// BGM�̍Đ�
	pSound->Play(CSound::SOUND_LABEL_TITLE);

	// UI�𐶐�
	m_apUi[0] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
		CScene::PRIORITY_UI, CUi::UI_TYPE_TITLE_BG);

	m_apUi[1] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, LOGO_POS, 0.0f), D3DXVECTOR3(LOGO_SIZE_X, LOGO_SIZE_Y, 0.0f),
		CScene::PRIORITY_UI, CUi::UI_TYPE_TITLE_LOGO);

	m_apUi[2] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, PUSH_POS, 0.0f), D3DXVECTOR3(PUSH_SIZE_X, PUSH_SIZE_Y, 0.0f),
		CScene::PRIORITY_UI, CUi::UI_TYPE_TITLE_ENTER);

	m_apUi[3] = CUi::Create(D3DXVECTOR3(PLAYER_UP_POS_X, PUSH_POS, 0.0f), D3DXVECTOR3(PLAYER_UP_SIZE_X, PLAYER_UP_SIZE_Y, 0.0f),
		CScene::PRIORITY_UI, CUi::UI_TYPE_TITLE_PLAYER_UP);

	m_apUi[4] = CUi::Create(D3DXVECTOR3(1100, PUSH_POS, 0.0f), D3DXVECTOR3(400, 350, 0.0f),
		CScene::PRIORITY_UI, CUi::UI_TYPE_TITLE_PLAYER_JUMP);

	m_apUi[5] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 480, 0.0f), D3DXVECTOR3(500, 100, 0.0f),
		CScene::PRIORITY_UI, CUi::UI_TYPE_TITLE_1PLAYER);
	m_apUi[5]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	m_apUi[6] = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 600, 0.0f), D3DXVECTOR3(500, 100, 0.0f),
		CScene::PRIORITY_UI, CUi::UI_TYPE_TITLE_2PLAYER);
	m_apUi[6]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	// �v���C�^�C�v�̏�����
	m_nPlaySelect = TYPE_F_PLAYER;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�擾����
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//�t�F�[�h�擾����
	CFade *pFade;
	pFade = CManager::GetFade();

	if (m_bPush == true)
	{
		if (pInputKeyboard->GetTrigger(DIK_S) == true ||
			pInputPad->GetTrigger(XINPUT_GAMEPAD_DPAD_DOWN, 0) == true ||
			pInputPad->GetTrigger(XINPUT_GAMEPAD_DPAD_DOWN, 1) == true)
		{
			m_nPlaySelect--;	// ��ނ̔ԍ������Z
			if (m_nPlaySelect < TYPE_F_PLAYER)
			{
				m_nPlaySelect = TYPE_F_PLAYER;
			}

		}
		if (pInputKeyboard->GetTrigger(DIK_W) == true ||
			pInputPad->GetTrigger(XINPUT_GAMEPAD_DPAD_UP, 0) == true ||
			pInputPad->GetTrigger(XINPUT_GAMEPAD_DPAD_UP, 1) == true)
		{
			m_nPlaySelect++;	// ��ނ̔ԍ������Z
			if (m_nPlaySelect > TYPE_MAX)
			{
				m_nPlaySelect = TYPE_S_PLAYER;
			}

		}
		switch (m_nPlaySelect)
		{
		case TYPE_S_PLAYER:
			m_apUi[5]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apUi[6]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			// �t�F�[�h���Ă��Ȃ����̂ݑ���ł���
			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				if (pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
					pInputPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true ||
					pInputPad->GetTrigger(XINPUT_GAMEPAD_A, 1) == true)
				{
					// BGM�̒�~
					pSound->Stop(CSound::SOUND_LABEL_TITLE);
					// SE�̍Đ�
					pSound->Play(CSound::SOUND_LABEL_TITLE_ENTER);
					pSound->ControllVoice(CSound::SOUND_LABEL_TITLE_ENTER, 0.2f);
					// �`���[�g���A����ʂɑJ��
					pFade->SetFade(CManager::MODE_TUTORIAL, D3DCOLOR_RGBA(0, 0, 0, 0));
				}
			}
			break;
		case TYPE_F_PLAYER:
			m_apUi[5]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_apUi[6]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			

			break;
		default:
			break;
		}
	}           

	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
		pInputPad->GetTrigger(XINPUT_GAMEPAD_A, 0) == true ||
		pInputPad->GetTrigger(XINPUT_GAMEPAD_A, 1) == true && m_bPush == false)
	{
		m_bPush = true;	// �{�^������
	}

}

//================================================
// �`�揈��
//================================================
void CTitle::Draw(void)
{

}