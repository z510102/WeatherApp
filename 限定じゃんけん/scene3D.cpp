//=============================================================================
// 3D�I�u�W�F�N�g���� [scene3D.cpp]
// Author : ���� ��
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene3D::CScene3D(int nPriority) :CScene(nPriority)
{
	// �ϐ��̃N���A
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene3D::~CScene3D()
{

}

//================================================
// ����������
//================================================
HRESULT CScene3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �ϐ��̏�����
	m_pos = pos;
	m_size = size;

	// �ʒu�E�T�C�Y�ݒ菈��
	CScene::SetPos(m_pos);
	CScene::SetSize(m_size);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x / 2.0f, +m_size.y / 2.0f, +m_size.z / 2.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x / 2.0f, +m_size.y / 2.0f, +m_size.z / 2.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x / 2.0f, -m_size.y / 2.0f, -m_size.z / 2.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x / 2.0f, -m_size.y / 2.0f, -m_size.z / 2.0f);

	// �@��
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// �J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`��
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
// �I������
//================================================
void CScene3D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//================================================
// �X�V����
//================================================
void CScene3D::Update(void)
{

}

//================================================
// �`�揈��
//================================================
void CScene3D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �J�����O���s��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//================================================
// ��������
//================================================
CScene3D* CScene3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nPriolity)
{
	// �C���X�^���X�̐���
	CScene3D *pScene3D = NULL;

	// �k���`�F�b�N
	if (pScene3D == NULL)
	{
		// �D�揇�ʂ��������ăN���X�𐶐�
		pScene3D = new CScene3D(nPriolity);
		if (pScene3D != NULL)
		{
			// �ϐ��̏�����
			pScene3D->m_rot = rot;

			// ����������
			pScene3D->Init(pos, size);
		}
	}

	return pScene3D;
}

//================================================
// �ʒu�ݒ菈��
//================================================
void CScene3D::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �ʒu�E�T�C�Y�ɑ��
	m_pos = pos;
	m_size = size;

	// �ʒu�E�T�C�Y�ݒ菈��
	CScene::SetPos(m_pos);
	CScene::SetSize(m_size);

	// ���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(-m_size.x / 2.0f, m_size.y / 2.0f, m_size.z / 2.0f);
	pVtx[1].pos = D3DXVECTOR3(m_size.x / 2.0f, m_size.y / 2.0f, m_size.z / 2.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x / 2.0f, -m_size.y / 2.0f, -m_size.z / 2.0f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x / 2.0f, -m_size.y / 2.0f, -m_size.z / 2.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
// �ʒu�擾����
//================================================
D3DXVECTOR3 CScene3D::GetPos(void)
{
	return m_pos;
}

//================================================
// �e�N�X�`���ݒ菈��
//================================================
void CScene3D::SetTexture(float fU, float fV, int nCutU, int nCutV)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//�e�N�X�`���ݒ�(U���W�̈ʒu�AV���W�̈ʒu�A���̕������A�c�̕�����������)
	pVtx[0].tex = D3DXVECTOR2(fU * (1.0f / nCutU), fV * (1.0f / nCutV));
	pVtx[1].tex = D3DXVECTOR2(fU * (1.0f / nCutU) + (1.0f / nCutU), fV * (1.0f / nCutV));
	pVtx[2].tex = D3DXVECTOR2(fU * (1.0f / nCutU), fV * (1.0f / nCutV) + (1.0f / nCutV));
	pVtx[3].tex = D3DXVECTOR2(fU * (1.0f / nCutU) + (1.0f / nCutU), fV * (1.0f / nCutV) + (1.0f / nCutV));

	m_pVtxBuff->Unlock();
}

//================================================
// �e�N�X�`����������
//================================================
void CScene3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//================================================
// �J���[�ݒ菈��
//================================================
void CScene3D::SetColor(D3DXCOLOR col)
{
	// ���_���̃|�C���^
	VERTEX_3D *pVtx;

	// �F���X�V
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;
	m_pVtxBuff->Unlock();
}