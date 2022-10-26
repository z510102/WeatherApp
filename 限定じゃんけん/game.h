//=============================================================================
// �Q�[����� [game.h]
// Author : ���� ��
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAME_MAX_UI	(3)								// UI�̍ő吔
#define GAME_MAX_MODEL	(200)						// ���f���̍ő吔
#define GAME_MAX_BILLBOARD	(400)					// �r���{�[�h�̍ő吔

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CUi;
class CModelSingle;
class CPlayer;
class CMeshField;
class CMeshCylinder;
class CScore;
class CTime;
class CPause;
class CBillboard;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CGame : public CScene
{
public:
	// �Q�[���̃t�F�C�Y
	typedef enum
	{
		GAME_PHASE_NONE = 0,	// �Ȃ�
		GAME_PHASE_COUNTDOWN,	// �X�^�[�g�O�̃J�E���g�_�E��
		GAME_PHASE_ACTION,		// �A�N�V������
		GAME_PHASE_CLEAR,		// �N���A
		GAME_PHASE_MAX
	} GAME_PHASE;

	CGame();											// �R���X�g���N�^
	~CGame();											// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��
	void SetPhase(GAME_PHASE phase);					// �t�F�C�Y�ݒ菈��
	GAME_PHASE GetPhase(void);							// �t�F�C�Y�擾����

private:
	void Phase();										// �t�F�C�Y����

	CUi *m_apUi[GAME_MAX_UI];							// UI�̃|�C���^
	CModelSingle *m_apModelSingle[GAME_MAX_MODEL];		// ���f��(�P��)�̃|�C���^
	CBillboard *m_apBillboard[GAME_MAX_BILLBOARD];		// �r���{�[�h�̃|�C���^
	CPlayer *m_apPlayer[MAX_PLAYER_NUM];				// �v���C���[�̃|�C���^
	CMeshField *m_pMeshField;							// ���b�V���t�B�[���h�̃|�C���^
	CMeshCylinder *m_pMeshCylinder;						// ���b�V���V�����_�[�̃|�C���^
	CPause *m_pPause;									// �|�[�Y�̃|�C���^
	CScore *m_pScore;								// �X�R�A�̃|�C���^
	CTime *m_pTime;										// �^�C���̃|�C���^
	GAME_PHASE m_phase;									// ���݂̃t�F�C�Y
	int m_nInterval;									// �t�F�C�Y�؂�ւ����̃C���^�[�o��
};

#endif	// _GAME_H_