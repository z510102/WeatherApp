//=============================================================================
// ���U���g��� [result.cpp]
// Author : ���� ��
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include"tutorial.h"
#include "manager.h"
#include "texture.h"
#include "ui.h"
#include "score.h"
#include "fade.h"
#include "input_keyboard.h"
#include"rankingdata.h"
#include "input_pad.h"
#include "sound.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
	// �ϐ��̃N���A
	memset(&m_apUi, NULL, sizeof(m_apUi));
	//memset(&m_pScore, NULL, sizeof(m_pScore));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	// BGM�̍Đ�
	pSound->Play(CSound::SOUND_LABEL_RESULT);
	pSound->ControllVoice(CSound::SOUND_LABEL_RESULT, 0.2f);

	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), 3, CUi::UI_TYPE_TUTORIAL_BG);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTutorial::Uninit(void)
{
	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTutorial::Update(void)
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

	// �t�F�[�h���Ă��Ȃ����̂ݑ���ł���
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		for (int nNum = 0; nNum < MAX_PLAYER_NUM; nNum++)
		{
			//***********************************************************************
			// ���ւ����� (Space �܂��� �p�b�hA�{�^��)
			//***********************************************************************
			if (pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
				pInputPad->GetTrigger(XINPUT_GAMEPAD_A, nNum) == true)
			{
				// BGM�̒�~
				pSound->Stop(CSound::SOUND_LABEL_RESULT);

				// SE�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_TITLE_ENTER);
				pSound->ControllVoice(CSound::SOUND_LABEL_TITLE_ENTER, 0.2f);

				// �^�C�g����ʂɑJ��
				pFade->SetFade(CManager::MODE_GAME, D3DCOLOR_RGBA(0, 0, 0, 0));
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTutorial::Draw(void)
{

}