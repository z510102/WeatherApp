//=============================================================================
// �v���C���[���쏈�� [control_player.cpp]
// Author : ���� ��
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "control_player.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad.h"
#include "player.h"
#include "motion_player.h"
#include "camera.h"
#include "sound.h"
#include "model_single.h"

bool CControlPlayer::bAddScore = false;
bool CControlPlayer::bAddScore2 = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CControlPlayer::CControlPlayer()
{
	// �ϐ��̃N���A
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_fSpeed = 0.0f;
	m_bRotate = false;
	m_bJump = false;
	m_nNextModel = 0;
	m_nNextType = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CControlPlayer::~CControlPlayer()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CControlPlayer::Init(void)
{
	// �ϐ��̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_fSpeed = PLAYER_MOVE_SPEED;
	m_bRotate = false;
	m_bJump = false;

	m_nNextModel = 1;
	m_nNextType = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CControlPlayer::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CControlPlayer::Update(CScene *pScene)
{
	bAddScore = false;
	bAddScore2 = false;

	// �����̃|�C���^���v���C���[�N���X�̃|�C���^�ɃL���X�g
	CPlayer *pPlayer = NULL;
	pPlayer = (CPlayer*)pScene;

	// ���[�V�����擾����
	CMotionPlayer *pMotionPlayer = NULL;
	pMotionPlayer = pPlayer->GetMotionPlayer();

	// �T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	D3DXVECTOR3 rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �J�����̃|�C���^�̃A�h���X�擾
	CCamera **pCameraAddress = CManager::GetCamera();

	// �J�����̍ő吔�Ԃ�A�|�C���^�z���i�߂�
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++, pCameraAddress++)
	{
		// �J�����̎擾
		CCamera *pCamera = &**pCameraAddress;

		if (pCamera != NULL)
		{
			// �v���C���[�̔ԍ��ƃJ�����̔ԍ���������������
			if (pPlayer->GetNum() == pCamera->GetNum())
			{
				// �J�����̌����擾
				rotCamera = pCamera->GetRotV();
			}
		}
	}

	// �ړ��ʂ�ݒ�
	m_move = pPlayer->GetMove();
	m_moveOld = m_move;

	// �d��
	m_move.y -= PLAYER_GRAVITY;

	// �~�߂��Ă��Ȃ�����
	if (pPlayer->GetStop() == false)
	{
		// �ړ�����(�ڂ��������͊֐��̒�)
		GameMove(pPlayer);
	}

	// �ړ��̊���(�ڂ��������͊֐��̒�)
	MoveInteria(pPlayer);

	// ���ݎ~�܂��Ă��邩�A���[�V�������Ȃ��Ă��Ȃ�������
	if (m_move.x == 0.0f && m_move.z == 0.0f &&
		pPlayer->GetMotionPlayer()->GetConnect() == false)
	{
		// �j���[�g�������[�V�����ɂ���
		pPlayer->GetMotionPlayer()->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_NEUTRAL);
	}

	if (pPlayer->GetMotionPlayer()->GetMotion() != CMotionPlayer::MOTION_PLAYER_TYPE_LANDING &&
		pPlayer->GetMotionPlayer()->GetConnect() == true)
	{
		m_fSpeed = PLAYER_MOVE_SPEED;
	}

	// ��]�̊���(�ڂ��������͊֐��̒�)
	Rotate(pPlayer);

	// �v���C���[�����n���Ă���Ȃ�
	if (pPlayer->GetLand() == true)
	{
		// Y�����̈ړ��ʂ�0��
		m_move.x = 0.0f;
		m_move.y = 0.0f;
		m_move.z = 0.0f;
	}
	// �v���C���[�����n���ĂȂ����A�~�߂��Ă��Ȃ��Ȃ�
	else if (pPlayer->GetLand() == false && pPlayer->GetStop() == false)
	{
		//�ړ��ʉ��Z
		m_move.x += +cosf(D3DX_PI) * PLAYER_JUMP_MOVE;
		m_move.z += -sinf(D3DX_PI) * PLAYER_JUMP_MOVE;
	}

	//�I�u�W�F�N�g��������|�C���^
	CScene *pObject = NULL;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CScene *pSaveObject = NULL;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CScene::PRIORITY_MODEL);

	// �v���C���[�̔ԍ����擾
	int nNumPlayer = pPlayer->GetNum();

	while (pObject != NULL)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJECT_TYPE_MODEL)
		{
			//���f���V���O���ɃL���X�g
			CModelSingle *pModelSingle = NULL;
			pModelSingle = (CModelSingle*)pObject;

			// �v���C���[�̔ԍ��ƃ��f���̎��ʔԍ��������Ȃ�
			if (nNumPlayer == pModelSingle->GetNum())
			{
				// ���̑���̔ԍ������f���̔ԍ��ƈ�v������
				if (m_nNextModel == pModelSingle->GetModelNum())
				{
					// ���f���̎�ނ��擾����
					m_nNextType = pModelSingle->GetModelType(m_nNextModel);
				}
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//=============================================================================
// ��������
//=============================================================================
CControlPlayer *CControlPlayer::Create(void)
{
	// �C���X�^���X�̐���
	CControlPlayer *pControlPlayer = NULL;

	// �k���`�F�b�N
	if (pControlPlayer == NULL)
	{
		// �N���X�̐���
		pControlPlayer = new CControlPlayer;
		if (pControlPlayer != NULL)
		{
			// ����������
			pControlPlayer->Init();
		}
	}

	return pControlPlayer;
}

//=============================================================================
// �ړ�����
//=============================================================================
void CControlPlayer::Move(CPlayer *pPlayer)
{
	// �L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�擾����
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	D3DXVECTOR3 rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
			if (pPlayer->GetNum() == pCamera->GetNum())
			{
				// �J�����̌����擾
				rotCamera = pCamera->GetRotV();
			}
		}
	}

	// �v���C���[�̔ԍ����擾
	int nNumPlayer = pPlayer->GetNum();

	// �L�[�{�[�h�ł�2�l�̓��͏���ʁX�ŕۑ�
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER_NUM; nCntPlayer++)
	{
		int nLeft, nRight, nUp, nDown;

		// ���ꂼ��̃v���C���[�̓��̓L�[��ݒ�
		if (nNumPlayer == 0)
		{
			nLeft = DIK_A;
			nRight = DIK_D;
			nUp = DIK_W;
			nDown = DIK_S;
		}
		else if (nNumPlayer == 1)
		{
			nLeft = DIK_LEFT;
			nRight = DIK_RIGHT;
			nUp = DIK_UP;
			nDown = DIK_DOWN;
		}

		//�ړ��̉����x
		m_fSpeed = PLAYER_MOVE_SPEED;

		//***********************************************************************
		// �ړ� (1P:W/A/S/D, 2P:��/��/��/�� �܂��� �p�b�h���X�e�B�b�N)
		//***********************************************************************
		if (pInputKeyboard->GetPress(nLeft) == true ||
			pInputPad->GetPress(CInputPad::PAD_INPUTTYPE_LSTICK_LEFT, nNumPlayer) == true)
		{
			//�����ړ�
			if (pInputKeyboard->GetPress(nUp) == true ||
				pInputPad->GetPress(CInputPad::PAD_INPUTTYPE_LSTICK_UP, nNumPlayer) == true)
			{
				//�ړ��ʉ��Z
				m_move.x += +cosf(rotCamera.y + D3DX_PI / 4.0f) * m_fSpeed;
				m_move.z += -sinf(rotCamera.y + D3DX_PI / 4.0f) * m_fSpeed;

				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y - D3DX_PI / 4.0f;
				//��]�̊������I���ɂ���
				m_bRotate = true;
			}
			//����O�ړ�
			else if (pInputKeyboard->GetPress(nDown) == true ||
				pInputPad->GetPress(CInputPad::PAD_INPUTTYPE_LSTICK_DOWN, nNumPlayer) == true)
			{
				//�ړ��ʉ��Z
				m_move.x += +cosf(rotCamera.y - D3DX_PI / 4.0f) * m_fSpeed;
				m_move.z += -sinf(rotCamera.y - D3DX_PI / 4.0f) * m_fSpeed;

				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y - (D3DX_PI / 4.0f) * 3.0f;
				//��]�̊������I���ɂ���
				m_bRotate = true;
			}
			//���ړ�
			else
			{
				//�ړ��ʉ��Z
				m_move.x += +cosf(rotCamera.y) * m_fSpeed;
				m_move.z += -sinf(rotCamera.y) * m_fSpeed;

				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y - D3DX_PI / 2.0f;
				//��]�̊������I���ɂ���
				m_bRotate = true;
			}
		}
		else if (pInputKeyboard->GetPress(nRight) == true ||
			pInputPad->GetPress(CInputPad::PAD_INPUTTYPE_LSTICK_RIGHT, nNumPlayer) == true)
		{
			//�E���ړ�
			if (pInputKeyboard->GetPress(nUp) == true ||
				pInputPad->GetPress(CInputPad::PAD_INPUTTYPE_LSTICK_UP, nNumPlayer) == true)
			{
				//�ړ��ʉ��Z
				m_move.x += -cosf(rotCamera.y - D3DX_PI / 4.0f) * m_fSpeed;
				m_move.z += +sinf(rotCamera.y - D3DX_PI / 4.0f) * m_fSpeed;

				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 4.0f;
				//��]�̊������I���ɂ���
				m_bRotate = true;
			}
			//�E��O�ړ�
			else if (pInputKeyboard->GetPress(nDown) == true ||
				pInputPad->GetPress(CInputPad::PAD_INPUTTYPE_LSTICK_DOWN, nNumPlayer) == true)
			{
				//�ړ��ʉ��Z
				m_move.x += -cosf(rotCamera.y + D3DX_PI / 4.0f) * m_fSpeed;
				m_move.z += +sinf(rotCamera.y + D3DX_PI / 4.0f) * m_fSpeed;

				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 1.5f;
				//��]�̊������I���ɂ���
				m_bRotate = true;
			}
			//�E�ړ�
			else
			{
				//�ړ��ʉ��Z
				m_move.x += -cosf(rotCamera.y) * m_fSpeed;
				m_move.z += +sinf(rotCamera.y) * m_fSpeed;

				//�ړI�̌�����ݒ�
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 2.0f;
				//��]�̊������I���ɂ���
				m_bRotate = true;
			}
		}
		//���ړ�
		else if (pInputKeyboard->GetPress(nUp) == true ||
			pInputPad->GetPress(CInputPad::PAD_INPUTTYPE_LSTICK_UP, nNumPlayer) == true)
		{
			//�ړ��ʉ��Z
			m_move.z += -cosf(rotCamera.y) * m_fSpeed;
			m_move.x += -sinf(rotCamera.y) * m_fSpeed;

			//��������������
			//�ړI�̌�����ݒ�
			m_fObjectiveRot = rotCamera.y;
			//��]�̊������I���ɂ���
			m_bRotate = true;
		}
		//��O�ړ�
		else if (pInputKeyboard->GetPress(nDown) == true ||
			pInputPad->GetPress(CInputPad::PAD_INPUTTYPE_LSTICK_DOWN, nNumPlayer) == true)
		{
			//�ړ��ʉ��Z
			m_move.z += +cosf(rotCamera.y) * m_fSpeed;
			m_move.x += +sinf(rotCamera.y) * m_fSpeed;

			//����O����������
			//�ړI�̌�����ݒ�
			m_fObjectiveRot = rotCamera.y + D3DX_PI;
			//��]�̊������I���ɂ���
			m_bRotate = true;
		}
	}
}

//=============================================================================
// �ړ�����
//=============================================================================
void CControlPlayer::GameMove(CPlayer *pPlayer)
{
	// �L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�擾����
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	// �T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	D3DXVECTOR3 rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
			if (pPlayer->GetNum() == pCamera->GetNum())
			{
				// �J�����̌����擾
				rotCamera = pCamera->GetRotV();
			}
		}
	}

	// �v���C���[�̔ԍ����擾
	int nNumPlayer = pPlayer->GetNum();

	// �L�[�{�[�h�ł�2�l�̓��͏���ʁX�ŕۑ�
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER_NUM; nCntPlayer++)
	{
		int nLeft, nRight, nDown;

		// ���ꂼ��̃v���C���[�̓��̓L�[��ݒ�
		if (nNumPlayer == 0)
		{
			nLeft = DIK_A;
			nRight = DIK_D;
			nDown = DIK_S;
		}
		else if (nNumPlayer == 1)
		{
			nLeft = DIK_LEFT;
			nRight = DIK_RIGHT;
			nDown = DIK_DOWN;
		}

		//�ړ��̉����x
		m_fSpeed = PLAYER_MOVE_SPEED;

		// �v���C���[�����n���Ă���Ȃ�
		if (pPlayer->GetLand() == true)
		{
			m_move.x = 0.0f;
			m_move.z = 0.0f;
			//***********************************************************************
			// �ړ� (1P:W/S/D, 2P:��/��/�� �܂��� �p�b�hX/Y/B)
			//***********************************************************************
			if (pInputKeyboard->GetTrigger(nLeft) == true ||
				pInputPad->GetTrigger(XINPUT_GAMEPAD_X, nNumPlayer) == true)
			{
				if (m_nNextType == 2)
				{
					// �W�����v����(�ڂ��������͊֐��̒�)
					Jump(pPlayer);

					//�ړI�̌�����ݒ�
					m_fObjectiveRot = 1.569f;
					//��]�̊������I���ɂ���
					m_bRotate = true;

					m_nNextModel++;

					if (nCntPlayer == 0)
					{
						bAddScore = true;
					}

					if (nCntPlayer == 1)
					{
						bAddScore2 = true;
					}
				}
				else
				{
					// SE�̍Đ�
					pSound->Play(CSound::SOUND_LABEL_MISS);
				}
			}
			else if (pInputKeyboard->GetTrigger(nDown) == true ||
				pInputPad->GetTrigger(XINPUT_GAMEPAD_Y, nNumPlayer) == true)
			{
				if (m_nNextType == 3)
				{
					// �W�����v����(�ڂ��������͊֐��̒�)
					Jump(pPlayer);

					//�ړI�̌�����ݒ�
					m_fObjectiveRot = 1.569f;
					//��]�̊������I���ɂ���
					m_bRotate = true;

					m_nNextModel++;

					if (nCntPlayer == 0)
					{
						bAddScore = true;
					}

					if (nCntPlayer == 1)
					{
						bAddScore2 = true;
					}
				}
				else
				{
					// SE�̍Đ�
					pSound->Play(CSound::SOUND_LABEL_MISS);
				}
			}
			else if (pInputKeyboard->GetTrigger(nRight) == true ||
				pInputPad->GetTrigger(XINPUT_GAMEPAD_B, nNumPlayer) == true)
			{
				if (m_nNextType == 1)
				{
					// �W�����v����(�ڂ��������͊֐��̒�)
					Jump(pPlayer);

					//�ړI�̌�����ݒ�
					m_fObjectiveRot = 1.569f;
					//��]�̊������I���ɂ���
					m_bRotate = true;

					m_nNextModel++;

					if (nCntPlayer == 0)
					{
						bAddScore = true;
					}

					if (nCntPlayer == 1)
					{
						bAddScore2 = true;
					}
				}
				else
				{
					// SE�̍Đ�
					pSound->Play(CSound::SOUND_LABEL_MISS);
				}
			}
		}
		else
		{
			// ���n������܂��W�����v���\�ɂ���
			m_bJump = false;
		}
	}
}

//=============================================================================
// �W�����v����
//=============================================================================
void CControlPlayer::Jump(CPlayer *pPlayer)
{
	// ���[�V�����擾����
	CMotionPlayer *pMotionPlayer = NULL;
	pMotionPlayer = pPlayer->GetMotionPlayer();

	// �T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	// SE�̍Đ�
	//pSound->Play(CSound::SOUND_LABEL_JUMP);
	//pSound->ControllVoice(CSound::SOUND_LABEL_JUMP, 0.2f);

	// �W�����v���[�V�����ɂ���
	pMotionPlayer->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_JUMP);

	// �ړ��ʂ��W�����v�͂Ԃ���Z
	m_move.y = PLAYER_JUMP;

	// �v���C���[�̔�����W�����v�����A���n���Ă��Ȃ��ɐݒ�
	pPlayer->SetJump(true);
	pPlayer->SetLand(false);

	m_bJump = true;
}

//=============================================================================
// �ړ��̊����ɂ��Ă̏���
//=============================================================================
void CControlPlayer::MoveInteria(CPlayer *pPlayer)
{
	// �����̌��Z
	m_move.z *= PLAYER_INTERIA_SUBTRACTIO;
	m_move.x *= PLAYER_INTERIA_SUBTRACTIO;
	
	// �ړ��ʂ�����̒l�ɂȂ�����0�ɂ���
	if (m_move.x <= PLAYER_MOVE_STOP_COUNT && m_move.x >= -PLAYER_MOVE_STOP_COUNT)
	{
		m_move.x = 0.0f;
	}
	if (m_move.z <= PLAYER_MOVE_STOP_COUNT && m_move.z >= -PLAYER_MOVE_STOP_COUNT)
	{
		m_move.z = 0.0f;
	}
}

//=============================================================================
// ��]����
//=============================================================================
void CControlPlayer::Rotate(CPlayer *pPlayer)
{
	// �v���C���[�̌������擾
	D3DXVECTOR3 rotPlayer = pPlayer->GetRot();

	// ��]�������ԂȂ�
	if (m_bRotate == true)
	{
		// �ړI�̌������v�Z
		if (m_fObjectiveRot > D3DX_PI)
		{
			m_fObjectiveRot = -D3DX_PI - (D3DX_PI - m_fObjectiveRot);
		}
		else if (m_fObjectiveRot < -D3DX_PI)
		{
			m_fObjectiveRot = D3DX_PI - (-D3DX_PI - m_fObjectiveRot);
		}

		// �v���C���[�̌��݂̌������Ƃɂ��ꂼ�������ς���ʂ��v�Z
		if (rotPlayer.y < 0.0f && -rotPlayer.y + m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (-D3DX_PI - rotPlayer.y) + -(D3DX_PI - m_fObjectiveRot);
		}
		else if (rotPlayer.y >= D3DX_PI / 2.0f && rotPlayer.y - m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (D3DX_PI - rotPlayer.y) - (-D3DX_PI - m_fObjectiveRot);
		}
		else
		{
			m_fNumRot = (m_fObjectiveRot - rotPlayer.y);
		}

		// �v���C���[�̌����ɉ��Z
		rotPlayer.y += m_fNumRot * 0.2f;

		// ����̒l�ɒB�������]����߂�
		if (rotPlayer.y - m_fObjectiveRot < 0.001 && rotPlayer.y - m_fObjectiveRot > -0.001)
		{
			m_bRotate = false;
		}
	}

	// ������3.14����-3.14�̒l�͈͓̔��Ɏ��߂�
	if (rotPlayer.y > D3DX_PI)
	{
		rotPlayer.y -= D3DX_PI * 2.0f;
	}
	else if (rotPlayer.y < -D3DX_PI)
	{
		rotPlayer.y += D3DX_PI * 2.0f;
	}

	// �����𔽉f
	pPlayer->SetRot(rotPlayer);
}

bool CControlPlayer::AddScore(void)
{
	return bAddScore;
}

bool CControlPlayer::AddScore2(void)
{
	return bAddScore2;
}