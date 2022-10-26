//=============================================================================
//
// �����N���X [polygon.cpp]
// Author : ���}���@�V��
//
//=============================================================================
//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "polygon.h"
#include"renderer.h"
#include"scene2D.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPolygon::CPolygon()
{
	// �����o�ϐ��̃N���A
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPolygon::~CPolygon()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CPolygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,										// ���_�o�b�t�@�̎g�p�@
		FVF_VERTEX_2D,											// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,										// ���\�[�X�̃o�b�t�@��ێ����郁����
		&m_pVtxBuff,											// ���_�o�b�t�@�ւ̃|�C���^
		NULL);													// NULL�ɐݒ�

	VERTEX_2D *pVtx; //���_�o�b�t�@�ւ̃|�C���^

					 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W��ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPolygon::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CPolygon::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPolygon::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
//=============================================================================
// �����̐���
//=============================================================================
CPolygon *CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CTexture::TEX_TYPE type)
{
	CPolygon *pPolygon;
	pPolygon = new CPolygon;

	if (pPolygon != NULL)
	{
		pPolygon->Init(pos, size);
		pPolygon->BindTexture(CManager::GetTexture()->GetTexture(type));
	}

	return pPolygon;
}
//=============================================================================
// �e�N�X�`���̊��蓖��
//=============================================================================
void CPolygon::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// �e�N�X�`�����W��ݒ�
//=============================================================================
void CPolygon::SetTex(int nNumber)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);

	m_pVtxBuff->Unlock();
}
