//=============================================================================
//
// �X�R�A�N���X [score.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "score.h"
#include "polygon.h"
#include "input_keyboard.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScore::CScore(int nPriority) : CScene(nPriority)
{
	// �����o�ϐ��̃N���A
	memset(&m_apPolygon[0], 0, sizeof(m_apPolygon));
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	m_nScore = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScore::~CScore()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ���[�h�擾
	m_mode = CManager::GetMode();

	if (m_mode != CManager::MODE_GAME)
	{
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			m_apPolygon[nCntNum] = CPolygon::Create(D3DXVECTOR3(m_pos.x + RESULT_SIZE * nCntNum, m_pos.y, 0.0f), m_size, CTexture::TEX_TYPE_SCORE_NUMBER);
		}
	}
	else
	{
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			m_apPolygon[nCntNum] = CPolygon::Create(D3DXVECTOR3(m_pos.x + RESULT_SIZE * nCntNum, m_pos.y, 0.0f), m_size, CTexture::TEX_TYPE_SCORE_NUMBER);
		}
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScore::Uninit(void)
{



	// �������j��
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		if (m_apPolygon[nCntNum] != NULL)
		{
			m_apPolygon[nCntNum]->Uninit();
			delete m_apPolygon[nCntNum];
			m_apPolygon[nCntNum] = NULL;
		}
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScore::Update(void)
{
	// ���Z���ꂽ�X�R�A�̏�����]�Z�Ōv�Z����
	// �|���S��1�����Ɍv�Z���ꂽ�������i�[
	m_apPolygon[0]->SetTex(m_nScore / (int)pow(10, 7));
	m_apPolygon[1]->SetTex(m_nScore % (int)pow(10, 7) / (int)pow(10, 6));
	m_apPolygon[2]->SetTex(m_nScore % (int)pow(10, 6) / (int)pow(10, 5));
	m_apPolygon[3]->SetTex(m_nScore % (int)pow(10, 5) / (int)pow(10, 4));
	m_apPolygon[4]->SetTex(m_nScore % (int)pow(10, 4) / (int)pow(10, 3));
	m_apPolygon[5]->SetTex(m_nScore % (int)pow(10, 3) / (int)pow(10, 2));
	m_apPolygon[6]->SetTex(m_nScore % (int)pow(10, 2) / (int)pow(10, 1));
	m_apPolygon[7]->SetTex(m_nScore % (int)pow(10, 1));

}

//=============================================================================
// �`�揈��
//=============================================================================
void CScore::Draw(void)
{
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		m_apPolygon[nCntNum]->Draw();
	}
}
//=============================================================================
// �X�R�A�̐���
//=============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int score)
{
	CScore *pScore = NULL;
	pScore = new CScore(3);

	if (pScore != NULL)
	{
		pScore->m_nScore = score;
		pScore->m_pos = pos;
		pScore->m_size = size;
		pScore->Init(pos, size);
	}

	return pScore;
}
//=============================================================================
// �X�R�A�̐ݒ�
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}
//=============================================================================
// �X�R�A�����Z
//=============================================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}
//=============================================================================
// �X�R�A���擾
//=============================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}
//=============================================================================
// �������擾
//=============================================================================
CPolygon *CScore::GetNumber(int nNumber)
{
	return m_apPolygon[nNumber];
}