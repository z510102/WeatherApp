//=============================================================================
// �I�u�W�F�N�g���� [scene.cpp]
// Author : ���� ��
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"
#include "pause.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CScene *CScene::m_pTop[PRIORITY_MAX] = {};
CScene *CScene::m_pCur[PRIORITY_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	// ��ԍŏ��̃I�u�W�F�N�g
	if (m_pTop[nPriority] == NULL && m_pCur[nPriority] == NULL)
	{
		// �擪�̃I�u�W�F�N�g��ݒ�
		m_pTop[nPriority] = this;

		// ���̃I�u�W�F�N�g��񂪂Ȃ���΍Ō���ɐݒ�
		m_pCur[nPriority] = this;

		// �O�̏��E���̏���NULL
		m_pPrev = NULL;
		m_pNext = NULL;
	}
	// ��ڈȍ~�̃I�u�W�F�N�g
	else
	{
		// �O�̃I�u�W�F�N�g�ɍŌ���̏�������
		m_pPrev = m_pCur[nPriority];

		// �O�̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g�����̃I�u�W�F�N�g�ɐݒ�
		m_pCur[nPriority]->m_pNext = this;

		// �������邽�тɍŌ����ݒ�
		m_pCur[nPriority] = this;
		m_pNext = NULL;
	}

	// �ϐ��̏�����
	m_nPriority = nPriority;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bDeath = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
	int nPriority = m_nPriority;
	CScene *pScene = this;

	CScene *pSceneNext = pScene->m_pNext;
	CScene *pScenePrev = pScene->m_pPrev;

	// �I�u�W�F�N�g�����X�g�������

	// �擪�ł��Ō���ł��Ȃ��ꍇ
	if (pScene != m_pTop[m_nPriority] && pScene != m_pCur[m_nPriority])
	{
		// �O�̃I�u�W�F�N�g�������Ă��鎟�̃I�u�W�F�N�g���������̎��̃I�u�W�F�N�g���ɂ���
		pScenePrev->m_pNext = pSceneNext;
		// ���̃I�u�W�F�N�g�������Ă���O�̃I�u�W�F�N�g���������̑O�̃I�u�W�F�N�g���ɂ���
		pSceneNext->m_pPrev = pScenePrev;
	}

	// �擪�������ꍇ
	if (pScene == m_pTop[m_nPriority])
	{
		m_pTop[m_nPriority] = pSceneNext;

		// ���̃I�u�W�F�N�g����������
		if (pSceneNext != NULL)
		{
			// ���̃I�u�W�F�N�g�������Ă���O�̃I�u�W�F�N�g����NULL�ɂ���
			pSceneNext->m_pPrev = NULL;
		}
	}

	// �Ō���������ꍇ
	if (pScene == m_pCur[m_nPriority])
	{
		// �Ō����O�̃I�u�W�F�N�g�ɂ��炷
		m_pCur[m_nPriority] = pScenePrev;

		// �O�̃I�u�W�F�N�g����������
		if (pScenePrev != NULL)
		{
			// �O�̃I�u�W�F�N�g�������Ă��鎟�̃I�u�W�F�N�g����NULL�ɂ���
			pScenePrev->m_pNext = NULL;
		}
	}
}

//=============================================================================
// �S�ẴI�u�W�F�N�g�̊J������
//=============================================================================
void CScene::ReleaseAll(void)
{
	CScene *pScene = NULL;

	// �`��D�揇�ɏ���
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// �t�F�[�h�͏��������Ȃ�
		if (nCntPriority != PRIORITY_FADE)
		{
			pScene = m_pTop[nCntPriority];

			// pScene��NULL����Ȃ��Ȃ烋�[�v
			while (pScene)
			{
				// ���̃I�u�W�F�N�g�̃|�C���^��ۑ�
				CScene *pSceneSave = pScene->m_pNext;

				// �I������
				pScene->Uninit();

				if (pScene->m_bDeath == true)
				{
					// ���S�t���O��true�̃I�u�W�F�N�g��j��
					delete pScene;
					pScene = NULL;
				}

				// ���̃I�u�W�F�N�g�̃|�C���^�ɂ���
				pScene = pSceneSave;
			}
		}
	}
}

//=============================================================================
// �S�ẴI�u�W�F�N�g�̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	CScene *pScene = NULL;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// �擪�̃I�u�W�F�N�g�̃|�C���^
		pScene = m_pTop[nCntPriority];

		// pScene��NULL����Ȃ��Ȃ烋�[�v
		while (pScene)
		{
			// �|�[�Y������Ȃ��Ȃ畁�ʂɍX�V
			if (CPause::GetPause() == false)
			{
				pScene->Update();
			}
			// �|�[�Y���Ȃ�
			else if (CPause::GetPause() == true)
			{
				// �t�F�[�h�ƃ|�[�Y�̂ݍX�V������
				if (nCntPriority == PRIORITY_FADE || nCntPriority == PRIORITY_PAUSE)
				{
					pScene->Update();
				}
			}

			//���̃I�u�W�F�N�g�̃|�C���^�ɂ���
			pScene = pScene->m_pNext;
		}
	}

	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CScene *pSaveObject = NULL;
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�擪�̃|�C���^����
		pScene = m_pTop[nCntPriority];
		while (pScene != NULL)
		{
			// ���̃I�u�W�F�N�g�̃|�C���^��ۑ�
			pSaveObject = pScene->m_pNext;

			//���S�t���O�`�F�b�N
			if (pScene->m_bDeath == true)
			{
				//�j��
				delete pScene;
				pScene = NULL;
			}
			//���̃I�u�W�F�N�g�̃|�C���^�ɂ���
			pScene = pSaveObject;
		}
	}
}

//=============================================================================
// �S�ẴI�u�W�F�N�g�̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	// �`��D�揇�ʂ̒Ⴂ���̂���`�悳���Ă���
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		// �ŏ��ɐ擪��ݒ�
		CScene *pScene = m_pTop[nCntPriority];

		while (pScene != NULL)
		{
			// ���̃I�u�W�F�N�^�̃|�C���^��ۑ�
			CScene *pSceneNext = pScene->m_pNext;

			// �`�揈��
			pScene->Draw();

			//���̃I�u�W�F�N�g�̃|�C���^�ɂ���
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// �P�̂̊J������
//=============================================================================
void CScene::Release()
{
	// ���S�t���O��true�ɂ���
	m_bDeath = true;
}

//=============================================================================
// �����̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g�̏��擾����
//=============================================================================
CScene *CScene::GetObjNext(CScene *pObject)
{
	return pObject->m_pNext;
}

//=============================================================================
// �����̃v���C�I���e�B�̐擪�I�u�W�F�N�g�̎擾����
//=============================================================================
CScene *CScene::GetTopObj(int nPriority)
{
	return m_pTop[nPriority];
}

//=============================================================================
// �ʒu�ݒ菈��
//=============================================================================
void CScene::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �ʒu�擾����
//=============================================================================
D3DXVECTOR3 CScene::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 1�t���[���O�̈ʒu�ݒ菈��
//=============================================================================
void CScene::SetPosOld(D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}

//=============================================================================
// 1�t���[���O�̈ʒu�擾����
//=============================================================================
D3DXVECTOR3 CScene::GetPosOld(void)
{
	return m_posOld;
}

//=============================================================================
// �T�C�Y�ݒ菈��
//=============================================================================
void CScene::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// �T�C�Y�擾����
//=============================================================================
D3DXVECTOR3 CScene::GetSize(void)
{
	return m_size;
}

//=============================================================================
// �I�u�W�F�N�g�̎�ނ̐ݒ菈��
//=============================================================================
void CScene::SetObjType(OBJECT_TYPE objType)
{
	m_objType = objType;
}

//=============================================================================
// �I�u�W�F�N�g�̎�ނ̎擾����
//=============================================================================
CScene::OBJECT_TYPE CScene::GetObjType(void)
{
	return m_objType;
}