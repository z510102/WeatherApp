//=============================================================================
// UI���� [ui.h]
// Author : ���� ��
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "ui.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "control.h"
//#include "control_ui_title_enter.h"
//#include "control_ui_game_countdown.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CUi::CUi(int nPriority) :CScene2D(nPriority)
{
	// �ϐ��̃N���A
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_pControl = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CUi::~CUi()
{

}

//=============================================================================
//����������
//=============================================================================
HRESULT CUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �p�����N���X�̏���������
	CScene2D::Init(pos, size);

	// �ϐ��̏�����
	m_size = size;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CUi::Uninit(void)
{
	// �p�����N���X�̏I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CUi::Update(void)
{
	// �w�肵��UI�̎�ނŃe�N�X�`����ς��A���蓖�Ă�
	switch (m_type)
	{
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// �^�C�g���n
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// �^�C�g���F�G���^�[����
	case UI_TYPE_TITLE_ENTER:
		//�_�ł�����
		if (CManager::GetMode() == CManager::MODE_TITLE)
		{
			if (m_bBrinkFlag == false)
			{
				m_col.a += 0.015f;
				if (m_col.a >= 1.0f)
				{
					m_col.a = 1.0f;
					m_bBrinkFlag = true;
				}
			}
			else
			{
				m_col.a -= 0.015f;
				if (m_col.a <= 0.0f)
				{
					m_col.a = 0.0f;
					m_bBrinkFlag = false;
				}
			}
			SetColor(m_col);
		}
		else
		{
			m_col.a = 0.0f;
			SetColor(m_col);
		}
		break;

	default:
		break;
	}

	// �R���g���[���N���X���k������Ȃ�������
	//if (m_pControl != NULL)
	//{
	//	// ���g�̃|�C���^�����A�X�V����
	//	m_pControl->Update(this);

	//	// Scene2D����ʒu�E�T�C�Y���擾
	//	D3DXVECTOR3 pos;
	//	pos = GetPos();

	//	m_size = GetSize();

	//	// �擾�����ʒu�Ɉړ��ʂ����Z
	//	pos += m_pControl->GetMove();

	//	// �ʒu�A�T�C�Y��ݒ�
	//	SetPos(pos, m_size);
	//}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CUi::Draw(void)
{
	// �p�����N���X�̕`�揈��
	CScene2D::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CUi* CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriolity, UI_TYPE type)
{
	// �C���X�^���X�̐���
	CUi *pUi = NULL;

	// �k���`�F�b�N
	if (pUi == NULL)
	{
		// �N���X�̐���
		pUi = new CUi(nPriolity);
		if (pUi != NULL)
		{
			// �w�肵��UI�̎�ނŃe�N�X�`����ς��A���蓖�Ă�
			switch (type)
			{
				//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				// �^�C�g���n
				//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				// �^�C�g���F���S
			case UI_TYPE_TITLE_LOGO:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TITLE_LOGO);
				break;
				// �^�C�g���F�G���^�[����
			case UI_TYPE_TITLE_ENTER:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TITLE_ENTER);
				break;
				// �^�C�g���F�w�i
			case UI_TYPE_TITLE_BG:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TITLE_BG);
				break;
				// �����|�[�Y�̃v���C���[
			case UI_TYPE_TITLE_PLAYER_UP:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_PLAYER_UP);
				break;
				// �W�����v�|�[�Y�̃v���C���[
			case UI_TYPE_TITLE_PLAYER_JUMP:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_PLAYER_JUMP);
				break;
				// 1�v���C���[�̕���
			case UI_TYPE_TITLE_1PLAYER:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_1PLAYER);
				break;
				// 2�v���C���[����
			case UI_TYPE_TITLE_2PLAYER:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_2PLAYER);
				break;
			case UI_TYPE_RESULT_BG:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_RESULT_BG);
				break;
			case UI_TYPE_TUTORIAL_BG:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TUTORIAL_BG);
				break;
			default:
				break;
			}
			pUi->BindTexture(pUi->m_pTexture);

			// �ϐ��̏�����
			pUi->m_type = type;

			// ����������
			pUi->Init(pos, size);
		}
	}

	return pUi;
}

//=============================================================================
// ��ނ̎擾����
//=============================================================================
CUi::UI_TYPE CUi::GetUIType(void)
{
	return m_type;
}