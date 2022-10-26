//=============================================================================
// �Q�[����� [game.cpp]
// Author : ���� ��
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "game.h"
#include "manager.h"
#include "texture.h"
#include "ui.h"
#include "fade.h"
#include "model_single.h"
#include "player.h"
#include "mesh_field.h"
#include "mesh_cylinder.h"
#include "pause.h"
#include "input_keyboard.h"
#include "input_pad.h"
#include "sound.h"
#include "score.h"
#include "time.h"
#include "billboard.h"
#include "control_player.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	// �ϐ��̃N���A
	memset(&m_apUi, NULL, sizeof(m_apUi));
	memset(&m_apModelSingle, NULL, sizeof(m_apModelSingle));
	memset(&m_apPlayer, NULL, sizeof(m_apPlayer));
	m_pMeshField = NULL;
	memset(&m_pScore, NULL, sizeof(m_pScore)); 
	memset(&m_apBillboard, NULL, sizeof(m_apBillboard));
	m_pTime = NULL;
	m_pPause = NULL;
	m_phase = GAME_PHASE_NONE;
	m_nInterval = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �ϐ��̏�����
	m_nInterval = 0;

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	// BGM�̍Đ�
	pSound->Play(CSound::SOUND_LABEL_GAME);

	/*************************/
	/**	  �I�u�W�F�N�g�n	**/
	/*************************/
	//+------------------------------------------------+
	//| ���b�V���t�B�[���h�̐����E�e�N�X�`���̊��蓖�� |
	//+------------------------------------------------+
	//m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2000.0f, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5, 5);
	//m_pMeshField->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FIELD000));

	//+------------------------------------------------+
	//| ���b�V���V�����_�[�̐����E�e�N�X�`���̊��蓖�� |
	//+------------------------------------------------+
	//��PNG�摜�̎d�l��A�O������`�悳����
	// ��̐F
	/*m_pMeshCylinder = CMeshCylinder::Create(D3DXVECTOR3(0.0f, -5000.0f, 0.0f), D3DXVECTOR3(5000.0f, 10000.0f, 5000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 16,
		D3DCOLOR_RGBA(30, 30, 30, 255), false);*/

	//+--------------------+
	//| ���f��(�P��)�̐��� |
	//+--------------------+
	for(int nCntModel = 0; nCntModel < GAME_MAX_MODEL / 2; nCntModel++)
	{
		// 1�`3�̒l���烉���_���ɐݒ�
		int nRand = int(rand() % 3) + 1;
		CModelSingle::MODEL_SINGLE_MOVE num = (CModelSingle::MODEL_SINGLE_MOVE)nRand;

		m_apModelSingle[nCntModel] = CModelSingle::Create(D3DXVECTOR3(0.0f - nCntModel * 156.7f, 0.0f, -1200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			CModelLoad::MODEL_TYPE_TEKKOTU, num);

		// �ǂ̃v���C���[�̑��ꂩ�ݒ�
		m_apModelSingle[nCntModel]->SetNum(0);
		// ���Ԗڂ��ݒ�
		m_apModelSingle[nCntModel]->SetModelNum(nCntModel);

		m_apBillboard[nCntModel] = CBillboard::Create(D3DXVECTOR3(0.0f - nCntModel * 156.7f, 50.0f, -1200.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_MODEL);
		switch (nRand)
		{
		case 1:
			m_apBillboard[nCntModel]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_SIGN_ROCK));
			break;
		case 2:
			m_apBillboard[nCntModel]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_SIGN_SCISSORS));
			break;
		case 3:
			m_apBillboard[nCntModel]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_SIGN_PAPERS));
			break;
		}
	}

	//for (int nCntModel = 50; nCntModel < GAME_MAX_MODEL; nCntModel++)
	//{
	//	// 0�`3�̒l���烉���_���ɐݒ�
	//	int nRand = int(rand() % 3) + 1;
	//	CModelSingle::MODEL_SINGLE_MOVE num = (CModelSingle::MODEL_SINGLE_MOVE)nRand;

	//	m_apModelSingle[nCntModel] = CModelSingle::Create(D3DXVECTOR3(0.0f - (nCntModel - 50) * 156.7f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//		CModelLoad::MODEL_TYPE_TEKKOTU, num);

	//	// �ǂ̃v���C���[�̑��ꂩ�ݒ�
	//	m_apModelSingle[nCntModel]->SetNum(1);
	//	// ���Ԗڂ��ݒ�
	//	m_apModelSingle[nCntModel]->SetModelNum(nCntModel - 50);

	//	m_apBillboard[nCntModel] = CBillboard::Create(D3DXVECTOR3(0.0f - nCntModel * 156.7f, 50.0f, -400.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_MODEL);
	//	/*switch (nRand)
	//	{
	//	case 1:
	//		m_apBillboard[nCntModel]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_SIGN_ROCK));
	//		break;
	//	case 2:
	//		m_apBillboard[nCntModel]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_SIGN_SCISSORS));
	//		break;
	//	case 3:
	//		m_apBillboard[nCntModel]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_SIGN_PAPERS));
	//		break;
	//	}*/

	//}

	//+------------------+
	//| �v���C���[�̐��� |
	//+------------------+
	m_apPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 100.0f, -1200.0f), D3DXVECTOR3(0.0f, 1.569f, 0.0f), 0);
	//m_apPlayer[1] = CPlayer::Create(D3DXVECTOR3(0.0f, 100.0f, -400.0f), D3DXVECTOR3(0.0f, 1.569f, 0.0f), 1);

	/*************************/
	/**			UI�n		**/
	/*************************/
	//+--------------+
	//| �X�R�A�̐��� |
	//+--------------+
	// �v���C���[�̃X�R�A
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, 50.0f, 0.0f), D3DXVECTOR3(35.0f, 50.0f, 0.0f), 0);
	//m_pScore[1] = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 600.0f, 50.0f, 0.0f), D3DXVECTOR3(35.0f, 50.0f, 0.0f), 0);

	//+--------------+
	//| �|�[�Y�̐��� |
	//+--------------+
	m_pPause = CPause::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//+--------------+
	//| �^�C���̐��� |
	//+--------------+
	m_pTime = CTime::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f), D3DXVECTOR3(35.0f, 60.0f, 0.0f), 30);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	FILE *pFile;
	int nScore;

	nScore = m_pScore->GetScore();
	
	// �X�R�A��ۑ�����t�@�C��
	pFile = fopen(SCORE_FILENAME, "w");
	if (pFile != NULL)
	{
		fprintf(pFile, "%d\n", nScore);
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
	}
	fclose(pFile);
	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
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

	// �t�F�C�Y����(�����͊֐��̒�)
	Phase();

	if (CControlPlayer::AddScore() == true)
	{
		m_pScore->AddScore(1);
		
	}

	/*if (CControlPlayer::AddScore2() == true)
	{
		m_pScore[1]->AddScore(1);
	}*/
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// �t�F�C�Y�ݒ菈��
//=============================================================================
void CGame::SetPhase(GAME_PHASE phase)
{
	m_phase = phase;
}

//=============================================================================
// �t�F�C�Y�擾����
//=============================================================================
CGame::GAME_PHASE CGame::GetPhase(void)
{
	return m_phase;
}

//=============================================================================
// �t�F�[�Y����
//=============================================================================
void CGame::Phase(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//�t�F�[�h�擾����
	CFade *pFade;
	pFade = CManager::GetFade();

	//�t�F�[�Y�ɂ�鏈������
	switch (m_phase)
	{
	case GAME_PHASE_NONE:
		// �t�F�[�Y��؂�ւ�
		m_phase = GAME_PHASE_COUNTDOWN;
		break;

	case GAME_PHASE_COUNTDOWN:
		m_nInterval++;
		if (m_nInterval >= 60)
		{
			// �t�F�[�Y��؂�ւ�
			m_phase = GAME_PHASE_ACTION;
			m_nInterval = 0;
		}
		break;

	case GAME_PHASE_ACTION:
		// �v���C���[�𓮂�����悤�ɂ���
		m_apPlayer[0]->SetStop(false);
		//m_apPlayer[1]->SetStop(false);

		if (m_pTime->GetTime() == 0)
		{
			m_phase = GAME_PHASE_CLEAR;
		}
		break;

	case GAME_PHASE_CLEAR:
		// �v���C���[�𓮂����Ȃ��悤�ɂ���
		m_apPlayer[0]->SetStop(true);
		//m_apPlayer[1]->SetStop(true);

		//�J�E���g�𑝂₷
		m_nInterval++;

		// �����o������
		if (m_nInterval >= 50)
		{
			// �t�F�[�h���Ă��Ȃ�������
			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				// BGM�̒�~
				pSound->Stop(CSound::SOUND_LABEL_GAME);

				// ���U���g��ʂɑJ��
				pFade->SetFade(CManager::MODE_RESULT, D3DCOLOR_RGBA(0, 0, 0, 0));

				//int nScore = m_pScore[0]->GetScore();

				//// �X�R�A�̃��[�h
				//m_pScore[0]->LoadScore();

				//// �����L���O�̐ݒ�
				//m_pScore[0]->SetRankScore(nScore, NULL);

				//// �X�R�A�̃Z�[�u
				//m_pScore[0]->SaveScore();

				//// ���U���g�p�̃X�R�A��ݒ�
				//m_pScore[0]->SetResultScore(0);
			}
		}
		break;

	default:
		break;
	}
}