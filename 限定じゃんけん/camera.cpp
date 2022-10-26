//=============================================================================
// �J�������� [camera.cpp]
// Author : ���� ��
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "player.h"
#include "input_keyboard.h"
#include "input_pad.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	// �ϐ��̃N���A
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �J�����̌���
	m_rotAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̃J�����̌���
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���݂̎��_
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̎��_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���݂̒����_
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̒����_
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �@��
	m_fHeight = 0.0f;								// ���_���璍���_�̍���
	m_fRotDiffer = 0.0f;							// �ړI�ƌ����̍�
	m_fDistance = 0.0f;								// ���_�ƒ����_�̋���
	m_viewport.X = (DWORD)0.0f;						// �`�悷���ʂ̍���X���W
	m_viewport.Y = (DWORD)0.0f;						// �`�悷���ʂ̍���Y���W
	m_viewport.MinZ = 0.0f;							// �`�悷��z���W�͈̔͂̍ŏ��l
	m_viewport.MaxZ = 0.0f;							// �`�悷��z���W�͈̔͂̍ő�l
	m_viewport.Width = (DWORD)0.0f;					// �`�悷���ʂ̕�
	m_viewport.Height = (DWORD)0.0f;				// �`�悷���ʂ̍���
	m_bTurn = false;								// �J��������]���Ă��邩�ǂ���
	m_nNum = 0;										// �J�����̔ԍ�
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCamera::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float viewportX, float viewportY, float viewportWidth, float viewporHeight)
{
	// �ϐ��̏�����
	m_rot = rot;									// �J�����̌���
	m_rotAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̃J�����̌���
	m_posV = pos;									// ���݂̎��_
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̎��_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���݂̒����_
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړI�̒����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			// �@��
	m_fHeight = CAMERA_HEIGHT;						// ���_���璍���_�̍���
	m_fRotDiffer = 0.0f;							// �ړI�ƌ����̍�
	m_fDistance = CAMERA_DISTANCE;					// ���_�ƒ����_�̋���
	m_viewport.X = (DWORD)viewportX;				// �`�悷���ʂ̍���X���W
	m_viewport.Y = (DWORD)viewportY;				// �`�悷���ʂ̍���Y���W
	m_viewport.MinZ = 0.0f;							// �`�悷��z���W�͈̔͂̍ŏ��l
	m_viewport.MaxZ = 1.0f;							// �`�悷��z���W�͈̔͂̍ő�l
	m_viewport.Width = (DWORD)viewportWidth;		// �`�悷���ʂ̕�
	m_viewport.Height = (DWORD)viewporHeight;		// �`�悷���ʂ̍���
	m_bTurn = false;								// �J��������]���Ă��邩�ǂ���

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	// �J�����ړ�(�ڂ��������͊֐��̒�)
	Move();

	// �f�o�b�O�p�̃J�����ړ�
	//DebugMove();
}

//=============================================================================
// ��������
//=============================================================================
CCamera *CCamera::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float viewportX, float viewportY,
	float viewportWidth, float viewporHeight)
{
	// �C���X�^���X�̐���
	CCamera *pCamera = NULL;

	// �k���`�F�b�N
	if (pCamera == NULL)
	{
		// �N���X�̐���
		pCamera = new CCamera;
		if (pCamera != NULL)
		{
			// ����������
			pCamera->Init(pos, rot, viewportX, viewportY, viewportWidth, viewporHeight);
		}
	}

	return pCamera;
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CCamera::Set(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(50.0f),									// ��p
		(float)m_viewport.Width / (float)m_viewport.Height,		// �䗦
		CAMERA_MIN_RENDERER,									// Z�����̕`��͈�
		CAMERA_MAX_RENDERER);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//=============================================================================
// ���_�擾����
//=============================================================================
D3DXVECTOR3 CCamera::GetPosV(void)
{
	return m_posV;
}

//=============================================================================
// �����_�擾����
//=============================================================================
D3DXVECTOR3 CCamera::GetPosR(void)
{
	return m_posR;
}

//=============================================================================
// ���_�ݒ菈��
//=============================================================================
void CCamera::SetPosV(D3DXVECTOR3 pos)
{
	m_posV = pos;
}

//=============================================================================
// �����_�ݒ菈��
//=============================================================================
void CCamera::SetPosR(D3DXVECTOR3 pos)
{
	m_posR = pos;
}


//=============================================================================
// ���_�̌����擾����
//=============================================================================
D3DXVECTOR3 CCamera::GetRotV(void)
{
	return m_rot;
}

//=============================================================================
// ���_�̌����ݒ菈��
//=============================================================================
void CCamera::SetRotV(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �J�����̔ԍ��ݒ菈��
//=============================================================================
void CCamera::SetNum(int nNum)
{
	m_nNum = nNum;
}

//=============================================================================
// �J�����̔ԍ��擾����
//=============================================================================
int CCamera::GetNum(void)
{
	return m_nNum;
}

//=============================================================================
// �J�����̈ړ�
//=============================================================================
void CCamera::Move(void)
{
	// �L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�p�b�h�擾����
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	// �I�u�W�F�N�g��������|�C���^�E���̏���ۑ�����|�C���^
	CScene *pObject = NULL;
	CScene *pSaveObject = NULL;

	// �擪�̃|�C���^����
	pObject = pObject->GetTopObj(CScene::PRIORITY_MODEL);

	while (pObject != NULL)
	{
		// ���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;
		if (pObject->GetObjType() == CScene::OBJECT_TYPE_PLAYER)
		{
			// �v���C���[�N���X�ɃL���X�g
			CPlayer *pPlayer = NULL;
			pPlayer = (CPlayer*)pObject;

			// �J�����̔ԍ����v���C���[�̔ԍ��ƈ�v���Ă�����
			if (m_nNum == pPlayer->GetNum())
			{
				// �v���C���[�̈ʒu���擾
				D3DXVECTOR3 pos = pPlayer->GetPos();

				// �J�����̒����_���v���C���[�̈ʒu�ɒǏ]������
				m_posR = pos;

				// �v���C���[�̈ʒu�{�J�����̍��������_��Y���W�ɐݒ�
				m_posV.y = pos.y + m_fHeight;
			}
		}

		// ���̃I�u�W�F�N�g���擾
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//�����_�����Ɏ��_�̏ꏊ���ړ�
	m_posV.x = m_posR.x + sinf(m_rot.y) * m_fDistance;
	m_posV.z = m_posR.z + cosf(m_rot.y) * m_fDistance;

	// ������3.14����-3.14�̒l�͈͓̔��Ɏ��߂�
	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
}

#ifdef _DEBUG
//=============================================================================
// �f�o�b�O�p�̃J�����̈ړ�
//=============================================================================
void CCamera::DebugMove(void)
{
	// �L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�p�b�h�擾����
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// �J�����ړ�(�����_�̈ʒu�̈ړ�)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (pInputKeyboard->GetPress(DIK_LEFT) == true)
	{
		//�����ړ�
		if (pInputKeyboard->GetPress(DIK_UP) == true)
		{
			m_posR.x += +cosf(m_rot.y) * CAMERA_MOVE_SPEED;
			m_posR.z += -sinf(m_rot.y) * CAMERA_MOVE_SPEED;
		}
		//����O�ړ�
		else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
		{
			m_posR.x += +cosf(m_rot.y) * CAMERA_MOVE_SPEED;
			m_posR.z += -sinf(m_rot.y) * CAMERA_MOVE_SPEED;
		}
		//���ړ�
		else
		{
			m_posR.x += +cosf(m_rot.y) * CAMERA_MOVE_SPEED;
			m_posR.z += -sinf(m_rot.y) * CAMERA_MOVE_SPEED;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{
		//�E���ړ�
		if (pInputKeyboard->GetPress(DIK_UP) == true)
		{
			m_posR.x += -cosf(m_rot.y) * CAMERA_MOVE_SPEED;
			m_posR.z += +sinf(m_rot.y) * CAMERA_MOVE_SPEED;
		}
		//�E��O�ړ�
		else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
		{
			m_posR.x += -cosf(m_rot.y) * CAMERA_MOVE_SPEED;
			m_posR.z += +sinf(m_rot.y) * CAMERA_MOVE_SPEED;
		}
		else	//�E�ړ�
		{
			m_posR.x += -cosf(m_rot.y) * CAMERA_MOVE_SPEED;
			m_posR.z += +sinf(m_rot.y) * CAMERA_MOVE_SPEED;
		}
	}
	//���ړ�
	else if (pInputKeyboard->GetPress(DIK_UP) == true)
	{
		m_posR.x += -sinf(m_rot.y) * CAMERA_MOVE_SPEED;
		m_posR.z += -cosf(m_rot.y) * CAMERA_MOVE_SPEED;
	}
	//��O�ړ�
	else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
	{
		m_posR.x += sinf(m_rot.y) * CAMERA_MOVE_SPEED;
		m_posR.z += cosf(m_rot.y) * CAMERA_MOVE_SPEED;
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// �J�����㉺�ړ�(���_�̈ʒu�̈ړ�)
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//��ړ�
	if (pInputKeyboard->GetPress(DIK_Y) == true)
	{
		m_posV.y += 3.0f;
		//m_fHeight += 3.0f;
	}
	//���ړ�
	if (pInputKeyboard->GetPress(DIK_N) == true)
	{
		m_posV.y -= 3.0f;
		//m_fHeight += -3.0f;
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// �J������]
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (pInputKeyboard->GetPress(DIK_Z) == true && m_bTurn == false)
	{
		m_rot.y += CAMERA_ROTATE_SPEED;
		m_posV.x = m_posR.x + sinf(m_rot.y) * CAMERA_DISTANCE;
		m_posV.z = m_posR.z + cosf(m_rot.y) * CAMERA_DISTANCE;
	}
	else if (pInputKeyboard->GetPress(DIK_C) == true && m_bTurn == false)
	{
		m_rot.y -= CAMERA_ROTATE_SPEED;
		m_posV.x = m_posR.x + sinf(m_rot.y) * CAMERA_DISTANCE;
		m_posV.z = m_posR.z + cosf(m_rot.y) * CAMERA_DISTANCE;
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// ���_�ƒ����_�̋���
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (pInputKeyboard->GetPress(DIK_T) == true)
	{
		m_fDistance -= 4.0f;
	}
	else if (pInputKeyboard->GetPress(DIK_B) == true)
	{
		m_fDistance += 4.0f;
	}

	//�����_�����Ɏ��_�̏ꏊ���ړ�
	m_posV.x = m_posR.x + sinf(m_rot.y) * m_fDistance;
	m_posV.z = m_posR.z + cosf(m_rot.y) * m_fDistance;

	// ��]���Ȃ�
	if (m_bTurn == true)
	{
		// �ړI�̌��������߂�
		if (m_rotAsk.y > D3DX_PI)
		{
			m_rotAsk.y = -D3DX_PI - (D3DX_PI - m_rotAsk.y);
		}
		else if (m_rotAsk.y < -D3DX_PI)
		{
			m_rotAsk.y = D3DX_PI - (-D3DX_PI - m_rotAsk.y);
		}

		// �ړI�̌����Ƃ̍������߂�
		if (m_rot.y < 0.0f && -m_rot.y + m_rotAsk.y > D3DX_PI)
		{
			m_fRotDiffer = (-D3DX_PI - m_rot.y) + -(D3DX_PI - m_rotAsk.y);
		}
		else if (m_rot.y >= D3DX_PI / 2.0f && m_rot.y - m_rotAsk.y > D3DX_PI)
		{
			m_fRotDiffer = (D3DX_PI - m_rot.y) - (-D3DX_PI - m_rotAsk.y);
		}
		else
		{
			m_fRotDiffer = (m_rotAsk.y - m_rot.y);
		}

		// �ړI�̌����Ƃ̍�������]������
		m_rot.y += m_fRotDiffer * 0.1f;
	}

	// ������3.14����-3.14�̒l�͈͓̔��Ɏ��߂�
	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
}
#endif