//=============================================================================
// ���f���̃��[�h���� [model_load.cpp]
// Authore: ���� ��
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "model_load.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModelLoad::CModelLoad()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModelLoad::~CModelLoad()
{

}

//=============================================================================
// ����������
//=============================================================================
void CModelLoad::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//**********************//
	//*  ���f���̓ǂݍ���  *//
	//**********************//
	// �S��
	D3DXLoadMeshFromX("data/MODEL/scaffold.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_TEKKOTU], NULL, &m_aNumMat[MODEL_TYPE_TEKKOTU], &m_apMesh[MODEL_TYPE_TEKKOTU]);

	//+-------------+
	//| �v���C���[1 |
	//+-------------+
	// �v���C���[1�F��
	D3DXLoadMeshFromX("data/MODEL/Player1/1P_00_body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_1_BODY], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_1_BODY], &m_apMesh[MODEL_TYPE_PLAYER_1_BODY]);
	// �v���C���[1�F��
	D3DXLoadMeshFromX("data/MODEL/Player1/1P_01_head.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_1_HEAD], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_1_HEAD], &m_apMesh[MODEL_TYPE_PLAYER_1_HEAD]);
	// �v���C���[1�F��
	D3DXLoadMeshFromX("data/MODEL/Player1/1P_02_neck.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_1_NECK], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_1_NECK], &m_apMesh[MODEL_TYPE_PLAYER_1_NECK]);
	// �v���C���[1�F�E�r
	D3DXLoadMeshFromX("data/MODEL/Player1/1P_03_armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_1_ARM_R], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_1_ARM_R], &m_apMesh[MODEL_TYPE_PLAYER_1_ARM_R]);
	// �v���C���[1�F���r
	D3DXLoadMeshFromX("data/MODEL/Player1/1P_04_armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_1_ARM_L], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_1_ARM_L], &m_apMesh[MODEL_TYPE_PLAYER_1_ARM_L]);
	// �v���C���[1�F�E�r
	D3DXLoadMeshFromX("data/MODEL/Player1/1P_05_legR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_1_LEG_R], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_1_LEG_R], &m_apMesh[MODEL_TYPE_PLAYER_1_LEG_R]);
	// �v���C���[1�F���r
	D3DXLoadMeshFromX("data/MODEL/Player1/1P_06_legL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_1_LEG_L], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_1_LEG_L], &m_apMesh[MODEL_TYPE_PLAYER_1_LEG_L]);
	
	//+-------------+
	//| �v���C���[2 |
	//+-------------+
	// �v���C���[2�F��
	D3DXLoadMeshFromX("data/MODEL/Player2/2P_00_body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_2_BODY], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_2_BODY], &m_apMesh[MODEL_TYPE_PLAYER_2_BODY]);
	// �v���C���[2�F��
	D3DXLoadMeshFromX("data/MODEL/Player2/2P_01_head.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_2_HEAD], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_2_HEAD], &m_apMesh[MODEL_TYPE_PLAYER_2_HEAD]);
	// �v���C���[2�F��
	D3DXLoadMeshFromX("data/MODEL/Player2/2P_02_neck.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_2_NECK], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_2_NECK], &m_apMesh[MODEL_TYPE_PLAYER_2_NECK]);
	// �v���C���[2�F�E�r
	D3DXLoadMeshFromX("data/MODEL/Player2/2P_03_armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_2_ARM_R], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_2_ARM_R], &m_apMesh[MODEL_TYPE_PLAYER_2_ARM_R]);
	// �v���C���[2�F���r
	D3DXLoadMeshFromX("data/MODEL/Player2/2P_04_armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_2_ARM_L], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_2_ARM_L], &m_apMesh[MODEL_TYPE_PLAYER_2_ARM_L]);
	// �v���C���[2�F�E�r
	D3DXLoadMeshFromX("data/MODEL/Player2/2P_05_legR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_2_LEG_R], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_2_LEG_R], &m_apMesh[MODEL_TYPE_PLAYER_2_LEG_R]);
	// �v���C���[2�F���r
	D3DXLoadMeshFromX("data/MODEL/Player2/2P_06_legL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_2_LEG_L], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_2_LEG_L], &m_apMesh[MODEL_TYPE_PLAYER_2_LEG_L]);

}

//=============================================================================
// �I������
//=============================================================================
void CModelLoad::Uninit(void)
{
	for (int nCntModel = 0; nCntModel < MODEL_TYPE_MAX; nCntModel++)
	{
		// ���b�V���̔j��
		if (m_apMesh[nCntModel] != NULL)
		{
			m_apMesh[nCntModel]->Release();
			m_apMesh[nCntModel] = NULL;
		}

		// �}�e���A���̔j��
		if (m_apBuffMat[nCntModel] != NULL)
		{
			m_apBuffMat[nCntModel]->Release();
			m_apBuffMat[nCntModel] = NULL;
		}
	}
}

//=============================================================================
// ���b�V����������
//=============================================================================
LPD3DXMESH CModelLoad::GetMesh(MODEL_TYPE type)
{
	return m_apMesh[type];
}

//=============================================================================
// �}�e���A����������
//=============================================================================
LPD3DXBUFFER CModelLoad::GetBuffMat(MODEL_TYPE type)
{
	return m_apBuffMat[type];
}

//=============================================================================
// �}�e���A������������
//=============================================================================
DWORD CModelLoad::GetNumMat(MODEL_TYPE type)
{
	return m_aNumMat[type];
}
