//=============================================================================
//
// �X�R�A�N���X [Time.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "time.h"
#include "polygon.h"
#include "input_keyboard.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTime::CTime(int nPriority) : CScene(nPriority)
{
	// �����o�ϐ��̃N���A
	memset(&m_apPolygon[0], 0, sizeof(m_apPolygon));
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	m_nTime = 0;
	m_dwCurrentTime = 0;
	m_dwExecLastTime = timeGetTime();
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTime::~CTime()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CTime::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ���[�h�擾
	m_mode = CManager::GetMode();

	if (m_mode != CManager::MODE_GAME)
	{
		for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
		{
			m_apPolygon[nCntNum] = CPolygon::Create(D3DXVECTOR3(m_pos.x + 40 * nCntNum, m_pos.y, 0.0f), m_size, CTexture::TEX_TYPE_TIME_NUMBER);
		}
	}
	else
	{
		for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
		{
			m_apPolygon[nCntNum] = CPolygon::Create(D3DXVECTOR3(m_pos.x + RESULT_SIZE * nCntNum, m_pos.y, 0.0f), m_size, CTexture::TEX_TYPE_TIME_NUMBER);
		}
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTime::Uninit(void)
{
	// �������j��
	for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
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
void CTime::Update(void)
{
	m_dwCurrentTime = timeGetTime();	// ���݂̎��Ԃ��擾

	if ((m_dwCurrentTime - m_dwExecLastTime) >= 1000)
	{
		AddTime(-1);
		m_dwCurrentTime = 0;
		m_dwExecLastTime = timeGetTime();
	}

	// ���Z���ꂽ�X�R�A�̏�����]�Z�Ōv�Z����
	// �|���S��1�����Ɍv�Z���ꂽ�������i�[
	m_apPolygon[0]->SetTex(m_nTime % (int)pow(10, 3) / (int)pow(10, 2));
	m_apPolygon[1]->SetTex(m_nTime % (int)pow(10, 2) / (int)pow(10, 1));
	m_apPolygon[2]->SetTex(m_nTime % (int)pow(10, 1));

}

//=============================================================================
// �`�揈��
//=============================================================================
void CTime::Draw(void)
{
	for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
	{
		m_apPolygon[nCntNum]->Draw();
	}
}
//=============================================================================
// �X�R�A�̐���
//=============================================================================
CTime *CTime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int time)
{
	CTime *pTime = NULL;
	pTime = new CTime(3);

	if (pTime != NULL)
	{
		pTime->m_nTime = time;
		pTime->m_pos = pos;
		pTime->m_size = size;
		pTime->Init(pos, size);
	}

	return pTime;
}
//=============================================================================
// �X�R�A�̐ݒ�
//=============================================================================
void CTime::SetTime(int nTime)
{
	m_nTime = nTime;
}
//=============================================================================
// �X�R�A�����Z
//=============================================================================
void CTime::AddTime(int nValue)
{
	m_nTime += nValue;
}
//=============================================================================
// �X�R�A���擾
//=============================================================================
int CTime::GetTime(void)
{
	return m_nTime;
}
//=============================================================================
// �������擾
//=============================================================================
CPolygon *CTime::GetNumber(int nNumber)
{
	return m_apPolygon[nNumber];
}