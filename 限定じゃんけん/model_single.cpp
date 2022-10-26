//=============================================================================
// �P�̂̃��f������ [model_single.cpp]
// Authore : ���� ��
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "model_single.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "model_load.h"
#include "player.h"
#include "game.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModelSingle::CModelSingle(int nPriority) :CScene(nPriority)
{
	// �ϐ��̃N���A
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pModel = NULL;
	m_modelType = MODEL_SINGLE_MOVE_NONE;
	m_nNum = 99;
	m_nModelNum = 0;
}

//================================================
// �f�X�g���N�^
//================================================
CModelSingle::~CModelSingle()
{

}

//================================================
// ����������
//================================================
HRESULT CModelSingle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �ϐ��̏�����
	m_pos = pos;
	m_posOld = m_pos;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���f���̐���
	m_pModel = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_rot, m_type);

	// �e���f���̐ݒ�(�P�̂̂���NULL������)
	m_pModel->SetParent(NULL);

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJECT_TYPE_MODEL);

	// �T�C�Y���擾
	m_size = m_pModel->GetSize();
	SetSize(m_size);
	SetPos(m_pos);

	return S_OK;
}

//================================================
// �I������
//================================================
void CModelSingle::Uninit(void)
{
	// �J������
	Release();
}

//================================================
// �X�V����
//================================================
void CModelSingle::Update(void)
{
	// �ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	// �ʒu�̔��f
	m_pos = pos;
	m_posOld = pos;

	//���f���̈ړ�����
	/*if (m_pControl != NULL)
	{
		m_pControl->Update(this);
		m_move = m_pControl->GetMove();
	}*/

	// �ړ��ʂ̔��f
	m_pos += m_move;

	// �ʒu��ݒ�
	SetPos(m_pos);
	SetPosOld(m_posOld);
}

//================================================
// �`�揈��
//================================================
void CModelSingle::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���f���̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//���f���̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//���f���̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���f���̕`��
	m_pModel->Draw();
}

//================================================
// ��������
//================================================
CModelSingle *CModelSingle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModelLoad::MODEL_TYPE type, MODEL_SINGLE_MOVE modelType)
{
	// �C���X�^���X�̐���
	CModelSingle *pModelSingle = NULL;

	// �k���`�F�b�N
	if (pModelSingle == NULL)
	{
		// �N���X�̐���
		pModelSingle = new CModelSingle;
		if (pModelSingle != NULL)
		{
			// �������������ꍇ
			switch (modelType)
			{
			case MODEL_SINGLE_MOVE_NONE:

				break;

			default:
				break;
			}

			// �ϐ��̏�����
			pModelSingle->m_rot = rot;
			pModelSingle->m_type = type;
			pModelSingle->m_modelType = modelType;

			// ����������
			pModelSingle->Init(pos, pModelSingle->m_size);
		}
	}

	return pModelSingle;
}

//================================================
//�����蔻�菈��
//================================================
bool CModelSingle::SimpleCollision(CScene *pScene)
{
	bool bLand = false;	//���n���Ă��邩�ǂ���

	//�I�u�W�F�N�g��������|�C���^
	CScene *pObject = NULL;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CScene *pSaveObject = NULL;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CScene::PRIORITY_MODEL);

	while (pObject != NULL)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJECT_TYPE_MODEL)
		{
			//���f���V���O���ɃL���X�g
			CModelSingle *pModelSingle = NULL;
			pModelSingle = (CModelSingle*)pObject;

			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�Ώۂ̈ʒu
			D3DXVECTOR3 posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���f���̈ʒu
			D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�Ώۂ̃T�C�Y
			D3DXVECTOR3 sizeModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���f���̃T�C�Y
			D3DXVECTOR3 posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�Ώۂ�1�t���[���O�̈ʒu

																		//���f���̈ʒu�E�T�C�Y�擾
			posModel = pModelSingle->GetPos();
			sizeModel = pModelSingle->GetSize();

			//�Ώۂ̈ʒu�E�T�C�Y�擾
			pos = pScene->GetPos();
			posOld = pScene->GetPosOld();
			size = pScene->GetSize();

			if (pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
				pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
				pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
				pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
				pos.y <= posModel.y + sizeModel.y &&
				posOld.y >= posModel.y + sizeModel.y)
			{
				pos.y = posModel.y + sizeModel.y;
				//�ʒu��ݒ�
				pScene->SetPos(pos);

				if (pModelSingle->m_modelType == MODEL_SINGLE_MOVE_GOAL)
				{
					//�t�F�[�Y���S�[���ɂ���
					if (CManager::GetGame() != NULL)
					{
						//�v���C���[�ɃL���X�g
						CPlayer *pPlayer = NULL;
						pPlayer = (CPlayer*)pScene;

						CManager::GetGame()->SetPhase(CGame::GAME_PHASE_CLEAR);
					}
				}

				bLand = true;
			}
			else if (pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
				pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
				pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
				pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
				pos.y + size.y >= posModel.y &&
				posOld.y + size.y <= posModel.y)
			{
				pos.y = posModel.y - size.y;
				//�ʒu��ݒ�
				pScene->SetPos(pos);
			}
			if (pos.y + size.y > posModel.y &&
				pos.y < posModel.y + sizeModel.y &&
				pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
				pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
				pos.x + size.x / 2.0f >= posModel.x - sizeModel.x / 2.0f &&
				posOld.x + size.x / 2.0f <= posModel.x - sizeModel.x / 2.0f)
			{
				pos.x = posModel.x - sizeModel.x / 2.0f - size.x / 2.0f;
				//�ʒu��ݒ�
				pScene->SetPos(pos);
			}
			else if (pos.y + size.y > posModel.y &&
				pos.y < posModel.y + sizeModel.y &&
				pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
				pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
				pos.x - size.x / 2.0f <= posModel.x + sizeModel.x / 2.0f &&
				posOld.x - size.x / 2.0f >= posModel.x + sizeModel.x / 2.0f)
			{
				pos.x = posModel.x + sizeModel.x / 2.0f + size.x / 2.0f;
				//�ʒu��ݒ�
				pScene->SetPos(pos);
			}
			if (pos.y + size.y > posModel.y &&
				pos.y < posModel.y + sizeModel.y &&
				pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
				pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
				pos.z + size.x / 2.0f >= posModel.z - sizeModel.z / 2.0f &&
				posOld.z + size.x / 2.0f <= posModel.z - sizeModel.z / 2.0f)
			{
				pos.z = posModel.z - sizeModel.z / 2.0f - size.x / 2.0f;
				//�ʒu��ݒ�
				pScene->SetPos(pos);
			}
			else if (pos.y + size.y > posModel.y &&
				pos.y < posModel.y + sizeModel.y &&
				pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
				pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
				pos.z - size.x / 2.0f <= posModel.z + sizeModel.z / 2.0f &&
				posOld.z - size.x / 2.0f >= posModel.z + sizeModel.z / 2.0f)
			{
				pos.z = posModel.z + sizeModel.z / 2.0f + size.x / 2.0f;
				//�ʒu��ݒ�
				pScene->SetPos(pos);
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
	return bLand;
}

// �ԍ��ݒ菈��
void CModelSingle::SetNum(int nNum)
{
	m_nNum = nNum;
}
// �ԍ��擾����
int CModelSingle::GetNum(void)
{
	return m_nNum;
}
// ���̖ڂ��ݒ菈��
void CModelSingle::SetModelNum(int nNum)
{
	m_nModelNum = nNum;
}
// ���̖ڂ��擾����
int CModelSingle::GetModelNum(void)
{
	return m_nModelNum;
}

int CModelSingle::GetModelType(int nNumModel)
{
	if (nNumModel == m_nModelNum)
	{
		int nType = (int)m_modelType;

		return nType;
	}
	else
	{
		return false;
	}
}