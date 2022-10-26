//=============================================================================
// �v���C���[���� [player.cpp]
// Authore : ���� ��
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input_keyboard.h"
#include "model.h"
#include "model_load.h"
#include "model_single.h"
//#include "mesh_field.h"
#include "camera.h"
#include "motion_player.h"
#include "control_player.h"
#include "game.h"
//#include "shadow.h"
#include "sound.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) :CScene(nPriority)
{
	// �ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		m_apModel[nCntModel] = NULL;
	}
	m_pParent = NULL;
	m_pControl = NULL;
	m_pShadow = NULL;
	m_pMotionPlayer = NULL;
	m_bLand = false;
	m_bJumpOld = false;
	m_nNum = 0;
	m_bStop = true;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �ϐ��̏�����
	m_pos = pos;
	m_posOld = pos;
	m_move = m_pControl->GetMove();
	m_bLand = false;
	m_bJump = true;
	m_bJumpOld = true;
	m_bStop = true;

	if (m_nNum == 0)
	{
		// ���f���̐���
		m_apModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_PLAYER_1_BODY);
		m_apModel[1] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_PLAYER_1_HEAD);
		m_apModel[2] = CModel::Create(D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_PLAYER_1_NECK);
		m_apModel[3] = CModel::Create(D3DXVECTOR3(3.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_PLAYER_1_ARM_R);
		m_apModel[4] = CModel::Create(D3DXVECTOR3(-3.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_PLAYER_1_ARM_L);
		m_apModel[5] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_PLAYER_1_LEG_R);
		m_apModel[6] = CModel::Create(D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_PLAYER_1_LEG_L);

		// �e�̐ݒ�
		m_apModel[0]->SetParent(NULL);			// ��	(�e�Ȃ�)
		m_apModel[1]->SetParent(m_apModel[2]);	// ��	(�e:��)
		m_apModel[2]->SetParent(m_apModel[0]);	// ��	(�e:��)
		m_apModel[3]->SetParent(m_apModel[0]);	// �E�r (�e:��)
		m_apModel[4]->SetParent(m_apModel[0]);	// ���r (�e:��)
		m_apModel[5]->SetParent(m_apModel[0]);	// �E�� (�e:��)
		m_apModel[6]->SetParent(m_apModel[0]);	// �E�� (�e:��)
	}
	else if (m_nNum == 1)
	{
		// ���f���̐���
		m_apModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_PLAYER_2_BODY);
		m_apModel[1] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_PLAYER_2_HEAD);
		m_apModel[2] = CModel::Create(D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_PLAYER_2_NECK);
		m_apModel[3] = CModel::Create(D3DXVECTOR3(3.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_PLAYER_2_ARM_R);
		m_apModel[4] = CModel::Create(D3DXVECTOR3(-3.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_PLAYER_2_ARM_L);
		m_apModel[5] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_PLAYER_2_LEG_R);
		m_apModel[6] = CModel::Create(D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelLoad::MODEL_TYPE_PLAYER_2_LEG_L);

		// �e�̐ݒ�
		m_apModel[0]->SetParent(NULL);			// ��	(�e�Ȃ�)
		m_apModel[1]->SetParent(m_apModel[2]);	// ��	(�e:��)
		m_apModel[2]->SetParent(m_apModel[0]);	// ��	(�e:��)
		m_apModel[3]->SetParent(m_apModel[0]);	// �E�r (�e:��)
		m_apModel[4]->SetParent(m_apModel[0]);	// ���r (�e:��)
		m_apModel[5]->SetParent(m_apModel[0]);	// �E�� (�e:��)
		m_apModel[6]->SetParent(m_apModel[0]);	// �E�� (�e:��)
	}

	
	// �ʒu�̐ݒ�
	SetPos(m_pos);
	SetPosOld(m_posOld);

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJECT_TYPE_PLAYER);

	// �T�C�Y���擾
	m_size = m_apModel[0]->GetSize();

	// �T�C�Y�̐ݒ�
	SetSize(m_size);

	// ���[�V�����̐���
	m_pMotionPlayer = CMotionPlayer::Create(this, m_nNum);

	// �J�����̃|�C���^�z��1�Ԗڂ̃A�h���X�擾
	CCamera **pCameraAddress = CManager::GetCamera();

	// �J�����̍ő吔�Ԃ�A�|�C���^�z���i�߂�
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++, pCameraAddress++)
	{
		// �J�����̎擾
		CCamera *pCamera = &**pCameraAddress;
		if (pCamera != NULL)
		{
			// �v���C���[�̔ԍ��ƃJ�����̔ԍ���������������
			if (m_nNum == pCamera->GetNum())
			{
				// �J�����̌������v���C���[�̌����Ɠ������Ȃ�悤�ݒ�
				pCamera->SetRotV(D3DXVECTOR3(m_rot.x, -0.628f, m_rot.z));
				// �J�����̒����_���v���C���[�̈ʒu�ɂȂ�悤�ݒ�
				pCamera->SetPosR(m_pos);
				// �J�����̎��_��ݒ�
				pCamera->SetPosV(D3DXVECTOR3(m_pos.x + sinf(m_rot.y) * CAMERA_DISTANCE,
					CAMERA_HEIGHT,
					m_pos.z + cosf(m_rot.y) * CAMERA_DISTANCE));
			}
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	//�e������
	//m_pShadow->Uninit();

	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	if (this != NULL)
	{
		// �ʒu�̎擾
		D3DXVECTOR3 pos = GetPos();
		m_pos = pos;
		m_posOld = pos;

		// 1�t���[���O�̈ʒu�ݒ�
		SetPosOld(m_posOld);

		// �O�̃t���[���ɃW�����v���Ă��邩�ǂ����̏�����
		m_bJumpOld = m_bJump;

		// �ړ�����
		Move();

		// �ړ��ʔ��f
		m_pos += m_move;

		// �ʒu���f
		SetPos(m_pos);

		// ���n���Ă���Ƃ��͈ړ��ʂ�0�ɂ���
		m_bLand = CModelSingle::SimpleCollision(this);

		if (m_bLand == true)
		{
			if (m_bJumpOld == true)
			{
				// �W�����v���[�V�����̎��Ȃ�
				if (m_pMotionPlayer->GetMotion() == CMotionPlayer::MOTION_PLAYER_TYPE_JUMP)
				{
					//���n���[�V�����ɂ���
					m_pMotionPlayer->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_LANDING);

					m_move.y = 0.0f;
					m_bJump = false;
				}
			}
		}

		// ���[�V����
		m_pMotionPlayer->Update(this);

		// �e�̒Ǐ]
		ShadowCollision();

		// �ʒu�擾
		m_pos = GetPos();

		//  �����������
		if (m_pos.y < -500)
		{
			Uninit();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// �v���C���[�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���f���̕`��
	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		m_apModel[nCntModel]->Draw();
	}

}

//=============================================================================
// ��������
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nNumPlayer)
{
	// �C���X�^���X�̐���
	CPlayer *pPlayer = NULL;

	// �k���`�F�b�N
	if (pPlayer == NULL)
	{
		// �N���X�̐���
		pPlayer = new CPlayer;
		if (pPlayer != NULL)
		{
			// �e�̐���
			//pPlayer->m_pShadow = CShadow::Create(D3DXVECTOR3(pos.x, 0.0f, pos.z), D3DXVECTOR3(40.0f, 0.0f, 40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			// �v���C���[����̃N���X�𐶐�
			pPlayer->m_pControl = CControlPlayer::Create();

			// �ϐ��̏�����
			pPlayer->m_nNum = nNumPlayer;
			pPlayer->m_rot = rot;

			// ����������
			pPlayer->Init(pos, pPlayer->m_size);
		}
	}

	return pPlayer;
}

//=============================================================================
// �ړ�����
//=============================================================================
void CPlayer::Move(void)
{
	// �k���`�F�b�N
	if (m_pControl != NULL)
	{
		// �v���C���[����̃N���X�Ƀv���C���[�̃|�C���^�����A�ړ��ʂ��擾
		m_pControl->Update(this);
		m_move = m_pControl->GetMove();
	}
}

//=============================================================================
// �����蔻�菈��
//=============================================================================
bool CPlayer::Collision(void)
{
	return false;
}

//=============================================================================
// 1�t���[���O�̈ʒu�擾����
//=============================================================================
D3DXVECTOR3 CPlayer::GetPosOld(void)
{
	return m_posOld;
}

//=============================================================================
// �����ݒ菈��
//=============================================================================
void CPlayer::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �����擾����
//=============================================================================
D3DXVECTOR3 CPlayer::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// �ړ��ʐݒ菈��
//=============================================================================
void CPlayer::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// �ړ��ʎ擾����
//=============================================================================
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}

//=============================================================================
// �W�����v�ݒ菈��
//=============================================================================
void CPlayer::SetJump(bool bJump)
{
	m_bJump = bJump;
}

//=============================================================================
// �W�����v�擾����
//=============================================================================
bool CPlayer::GetJump(void)
{
	return m_bJump;
}

//=============================================================================
// ���n�ݒ菈��
//=============================================================================
void CPlayer::SetLand(bool bLand)
{
	m_bLand = bLand;
}

//=============================================================================
// ���n�擾����
//=============================================================================
bool CPlayer::GetLand(void)
{
	return m_bLand;
}

//=============================================================================
// ���f�����̈ʒu�ݒ菈��
//=============================================================================
void CPlayer::SetModelPos(int nCntModel, D3DXVECTOR3 pos)
{
	m_apModel[nCntModel]->SetPos(pos);
}

//=============================================================================
// ���f�����̈ʒu�擾����
//=============================================================================
D3DXVECTOR3 CPlayer::GetModelPos(int nCntModel)
{
	return m_apModel[nCntModel]->GetPos();
}

//=============================================================================
// ���f�����̌����ݒ菈��
//=============================================================================
void CPlayer::SetModelRot(int nCntModel, D3DXVECTOR3 rot)
{
	m_apModel[nCntModel]->SetRot(rot);
}

//=============================================================================
// ���f�����̌����擾����
//=============================================================================
D3DXVECTOR3 CPlayer::GetModelRot(int nCntModel)
{
	return m_apModel[nCntModel]->GetRot();
}

//=============================================================================
// ���[�V�����v���C���[�擾����
//=============================================================================
CMotionPlayer *CPlayer::GetMotionPlayer(void)
{
	return m_pMotionPlayer;
}

//=============================================================================
// �v���C���[�̔ԍ��ݒ菈��
//=============================================================================
void CPlayer::SetNum(int nNum)
{
	m_nNum = nNum;
}

//=============================================================================
// �v���C���[�̔ԍ��擾����
//=============================================================================
int CPlayer::GetNum(void)
{
	return m_nNum;
}

//=============================================================================
// �I�u�W�F�N�g�Ƃ̓����蔻��
//=============================================================================
void CPlayer::Collision(CScene *pScene)
{
	//�I�u�W�F�N�g�̈ʒu���擾
	D3DXVECTOR3 posObj = pScene->GetPos();
	//�I�u�W�F�N�g��1�t���[���O�̈ʒu���擾
	D3DXVECTOR3 posObjOld = pScene->GetPosOld();
	//�I�u�W�F�N�g�̃T�C�Y���擾
	D3DXVECTOR3 sizeObj = pScene->GetSize();

	if (posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
		posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
		posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
		posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
		posObj.y + sizeObj.y >= m_pos.y&&
		posObjOld.y + sizeObj.y <= m_pos.y)
	{
		m_pos.y = posObj.y + sizeObj.y;
		//�ʒu��ݒ�
		SetPos(m_pos);
		//1�t���[���O�̈ʒu��ݒ�
		SetPosOld(m_pos);
	}
	else if (posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
		posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
		posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
		posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
		posObj.y <= m_pos.y + m_size.y &&
		posObjOld.y >= m_pos.y + m_size.y)
	{
		m_pos.y = posObj.y - m_size.y;
		//�ʒu��ݒ�
		SetPos(m_pos);
		//1�t���[���O�̈ʒu��ݒ�
		SetPosOld(m_pos);
	}
	if (posObj.y + sizeObj.y < m_pos.y &&
		posObj.y > m_pos.y + m_size.y &&
		posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
		posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
		posObj.x + sizeObj.x / 2.0f <= m_pos.x - m_size.x / 2.0f &&
		posObjOld.x + sizeObj.x / 2.0f >= m_pos.x - m_size.x / 2.0f)
	{
		m_pos.x = posObj.x + sizeObj.x / 2.0f - m_size.x / 2.0f;
		//�ʒu��ݒ�
		SetPos(m_pos);
		//1�t���[���O�̈ʒu��ݒ�
		SetPosOld(m_pos);
	}
	else if (posObj.y + sizeObj.y < m_pos.y &&
		posObj.y > m_pos.y + m_size.y &&
		posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
		posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
		posObj.x - sizeObj.x / 2.0f >= m_pos.x + m_size.x / 2.0f &&
		posObjOld.x - sizeObj.x / 2.0f <= m_pos.x + m_size.x / 2.0f)
	{
		m_pos.x = posObj.x - sizeObj.x / 2.0f + m_size.x / 2.0f;
		//�ʒu��ݒ�
		SetPos(m_pos);
		//1�t���[���O�̈ʒu��ݒ�
		SetPosOld(m_pos);
	}
	if (posObj.y + sizeObj.y < m_pos.y &&
		posObj.y > m_pos.y + m_size.y &&
		posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
		posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
		posObj.z + sizeObj.z / 2.0f <= m_pos.z - m_size.x / 2.0f &&
		posObjOld.z + sizeObj.z / 2.0f >= m_pos.z - m_size.x / 2.0f)
	{
		m_pos.z = posObj.z - sizeObj.z / 2.0f + m_size.x / 2.0f;
		//�ʒu��ݒ�
		SetPos(m_pos);
		//1�t���[���O�̈ʒu��ݒ�
		SetPosOld(m_pos);
	}
	else if (posObj.y + sizeObj.y < m_pos.y &&
		posObj.y > m_pos.y + m_size.y &&
		posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
		posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
		posObj.z - sizeObj.z / 2.0f >= m_pos.z + m_size.x / 2.0f &&
		posObjOld.z - sizeObj.z / 2.0f <= m_pos.z + m_size.x / 2.0f)
	{
		m_pos.z = posObj.z + sizeObj.z / 2.0f - m_size.x / 2.0f;
		//�ʒu��ݒ�
		SetPos(m_pos);
		//1�t���[���O�̈ʒu��ݒ�
		SetPosOld(m_pos);
	}
}

//=============================================================================
////�e�̕\���̂��߂̃I�u�W�F�N�g�Ƃ̓����蔻��
//=============================================================================
void CPlayer::ShadowCollision(void)
{
	//�I�u�W�F�N�g��������|�C���^
	CScene *pObject = NULL;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CScene *pSaveObject = NULL;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CScene::PRIORITY_MODEL);

	/*while (pObject != NULL)
	{
	//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
	pSaveObject = pObject;

	if (pObject->GetObjType() == CScene::OBJECT_TYPE_MODEL)
	{
	// ���f���V���O���N���X�ɃL���X�g
	CModelSingle *pModelSingle = NULL;
	pModelSingle = (CModelSingle*)pObject;

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ۑ��p�̈ʒu
	D3DXVECTOR3 posObj = pModelSingle->GetPos();		// �I�u�W�F�N�g�̈ʒu���擾
	D3DXVECTOR3 posObjOld = pModelSingle->GetPosOld();	// �I�u�W�F�N�g��1�t���[���O�̈ʒu���擾
	D3DXVECTOR3 sizeObj = pModelSingle->GetSize();		// �I�u�W�F�N�g�̃T�C�Y���擾

	if (posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
	posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
	posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
	posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
	posObj.y + sizeObj.y >= m_pos.y - 50.0f &&
	posObj.y + sizeObj.y <= m_pos.y)
	{
	//�ʒu�����f���̏��
	pos.y = posObj.y + sizeObj.y;

	//�e�̒Ǐ]
	m_pShadow->SetShadow(D3DXVECTOR3(m_pos.x, pos.y, m_pos.z), (m_pos.y - pos.y));

	//�e���g���Ă����Ԃɂ���
	m_pShadow->SetUseShadow(true);

	return;
	}
	else
	{
	//�e���g���Ă��Ȃ���Ԃɂ���
	m_pShadow->SetUseShadow(false);
	}
	}

	pObject = pSaveObject->GetObjNext(pSaveObject);
	}*/

	//�擪�̃|�C���^����
	//pObject = pObject->GetTopObj(CScene::PRIORITY_NONE);

	//while (pObject != NULL)
	//{
	//	//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
	//	pSaveObject = pObject;

	//	if (pObject->GetObjType() == CScene::OBJECT_TYPE_MODEL)
	//	{
	//		// ���b�V���t�B�[���h�N���X�ɃL���X�g
	//		CMeshField *pMeshField = NULL;
	//		pMeshField = (CMeshField*)pObject;

	//		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ۑ��p�̈ʒu
	//		D3DXVECTOR3 posObj = pMeshField->GetPos();			// �I�u�W�F�N�g�̈ʒu���擾
	//		D3DXVECTOR3 posObjOld = pMeshField->GetPosOld();	// �I�u�W�F�N�g��1�t���[���O�̈ʒu���擾
	//		D3DXVECTOR3 sizeObj = pMeshField->GetSize();		// �I�u�W�F�N�g�̃T�C�Y���擾

	//		if (posObj.x + sizeObj.x / 2.0f > m_pos.x - m_size.x / 2.0f &&
	//			posObj.x - sizeObj.x / 2.0f < m_pos.x + m_size.x / 2.0f &&
	//			posObj.z + sizeObj.z / 2.0f > m_pos.z - m_size.x / 2.0f &&
	//			posObj.z - sizeObj.z / 2.0f < m_pos.z + m_size.x / 2.0f &&
	//			posObj.y + sizeObj.y >= m_pos.y - 500.0f &&
	//			posObj.y + sizeObj.y <= m_pos.y + 10.0f)
	//		{
	//			//�ʒu���t�B�[���h�̏��
	//			pos.y = posObj.y * 2;

	//			//�e�̒Ǐ]
	//			m_pShadow->SetShadow(D3DXVECTOR3(m_pos.x, pos.y, m_pos.z), (m_pos.y - pos.y));

	//			//�e���g���Ă����Ԃɂ���
	//			m_pShadow->SetUseShadow(true);

	//			return;
	//		}
	//		else
	//		{
	//			//�e���g���Ă��Ȃ���Ԃɂ���
	//			m_pShadow->SetUseShadow(false);
	//		}
	//	}

	//	pObject = pSaveObject->GetObjNext(pSaveObject);
	//}
}

//=============================================================================
// �~�܂��Ă��邩�ǂ����ݒ菈��
//=============================================================================
void CPlayer::SetStop(bool bStop)
{
	m_bStop = bStop;
}

//=============================================================================
// �~�܂��Ă��邩�ǂ����ݒ菈��
//=============================================================================
bool CPlayer::GetStop(void)
{
	return m_bStop;
}
