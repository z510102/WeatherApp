//=============================================================================
// �v���C���[���쏈�� [control_player.h]
// Author : ���� ��
//=============================================================================
#ifndef _CONTROL_PLAYER_H_
#define _CONTROL_PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "control.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene;
class CPlayer;
class CParticle;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_JUMP_MOVE			(1.0f)	// �W�����v�Ői�ޑ傫��
#define PLAYER_JUMP					(8.0f)	// �W�����v��
#define PLAYER_GRAVITY				(0.6f)	// �d�͂̑傫��
#define PLAYER_MOVE_SPEED			(0.5f)	// �ړ��ʂ̊�l
#define PLAYER_INTERIA_SUBTRACTIO	(0.86f)	// �n��ł̊����̌��Z�l
#define PLAYER_MOVE_STOP_COUNT		(0.02f)	// �v���C���[�̈ړ��ʂ�0�ɂ��鎞�̈ړ��ʂ̒l

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CControlPlayer : public CControl
{
	// ���ɓ��͂��鑀��̎��
	typedef enum
	{
		PLAYER_NEXT_INPUT_NONE = 0,	// �Ȃ�
		PLAYER_NEXT_INPUT_LEFT,		// ��
		PLAYER_NEXT_INPUT_RIGHT,	// �E
		PLAYER_NEXT_MAX
	} PLAYER_NEXT_INPUT;

public:
	CControlPlayer();						// �R���X�g���N�^
	~CControlPlayer();						// �f�X�g���N�^
	HRESULT Init(void);						// ����������
	void Uninit(void);						// �I������
	void Update(CScene *pScene);			// �X�V����
	static CControlPlayer *Create(void);	// ��������
	static bool AddScore(void);				// ��������
	static bool AddScore2(void);			// ��������

private:
	void GameMove(CPlayer *pPlayer);		// �ړ�����
	void Move(CPlayer *pPlayer);			// �ړ�����
	void Jump(CPlayer *pPlayer);			// �W�����v����
	void MoveInteria(CPlayer *pPlayer);		// �ړ��̊����ɂ��Ă̏���
	void Rotate(CPlayer *pPlayer);			// ��]����

	D3DXVECTOR3 m_rot;						// ����
	D3DXVECTOR3 m_moveOld;					// 1�t���[���O�̈ړ���
	float m_fObjectiveRot;					// �ړI�̌���
	float m_fNumRot;						// ������ς����
	float m_fSpeed;							// �ړ��ʂɉ����鑬��
	bool m_bJump;							// �W�����v���Ă邩�ǂ���
	bool m_bRotate;							// ��]���Ă��邩�ǂ���
	int m_nNextModel;						// ���͂ǂ̑��ꂩ����
	int m_nNextType;						// ���̑���̎��
	static bool bAddScore;	
	static bool bAddScore2;	
};

#endif	//_CONTROL_PLAYER_H_