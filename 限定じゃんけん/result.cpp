//=============================================================================
// ���U���g��� [result.cpp]
// Author : ���� ��
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "result.h"
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
CResult::CResult()
{
	// �ϐ��̃N���A
	memset(&m_apUi, NULL, sizeof(m_apUi));
	//memset(&m_pScore, NULL, sizeof(m_pScore));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	// BGM�̍Đ�
	pSound->Play(CSound::SOUND_LABEL_RESULT);
	pSound->ControllVoice(CSound::SOUND_LABEL_RESULT, 0.2f);

	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), 3, CUi::UI_TYPE_RESULT_BG);

	// �����L���O�̐���
	CRankingData::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, 180.0f, 0.0f), D3DXVECTOR3(45.0f, 47.0f, 0.0f), true);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
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

				// �^�C�g����ʂɑJ��
				pFade->SetFade(CManager::MODE_TITLE, D3DCOLOR_RGBA(0, 0, 0, 0));
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{

}