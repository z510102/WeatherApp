//=============================================================================
// �v���C���[�̃��[�V�������� [motion_player.h]
// Authore : ���� ��
//=============================================================================
#ifndef _MOTION_PLAYER_H_
#define _MOTION_PLAYER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MOTION_PLAYER_KEY_INFO	(255)					// �L�[�̏��̍ő�l
#define MAX_MOTION_PLAYER_STRING	(255)					// ������̍ő�l
#define MOTION_PLAYER_FILE "data/TEXT/motion_player.txt"	// �t�@�C���̃p�X
#define MOTION_PLAYER2_FILE "data/TEXT/motion_player2.txt"	// �t�@�C���̃p�X

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
//�L�[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 rot;	//����
} KEY;

//�L�[���̍\����
typedef struct
{
	int nFrame;						//�Đ��t���[��
	KEY aKey[MAX_PLAYER_MODEL];		//�e���f���̃L�[�v�f(�p�[�c�̍ő吔)
} KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	int nLoop;				//���[�v���邩�ǂ���
	int nNumKey;			//�L�[�̑���
	KEY_INFO aKeyInfo[MAX_MOTION_PLAYER_KEY_INFO];	//�L�[�̏��
} MOTION_INFO;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CMotionPlayer
{
public:
	// ���[�V�����̎��
	typedef enum
	{
		MOTION_PLAYER_TYPE_NEUTRAL = 0,	// �j���[�g����
		MOTION_PLAYER_TYPE_JUMP,		// �W�����v
		MOTION_PLAYER_TYPE_LANDING,		// ���n
		MOTION_PLAYER_TYPE_MAX
		//���e�L�X�g�t�@�C���̃��[�V�����������̎�ނ̍ő吔�ɍ��킹�邱��!!
	} MOTION_PLAYER_TYPE;

	CMotionPlayer();											// �R���X�g���N�^
	~CMotionPlayer();											// �f�X�g���N�^
	HRESULT Init(CPlayer *pPlayer);								// ����������
	void Uninit(void);											// �I������
	void Update(CPlayer *pPlayer);								// �X�V����
	static CMotionPlayer *Create(CPlayer *pPlayer, int nNum);	// ��������
	void SetMotion(MOTION_PLAYER_TYPE type);					// ���[�V�����ݒ菈��
	MOTION_PLAYER_TYPE GetMotion(void);							// ���[�V�����擾����
	bool GetConnect(void);										// ���[�V���������擾����

private:
	MOTION_INFO m_aInfo[MOTION_PLAYER_TYPE_MAX];				// ���[�V�������
	MOTION_PLAYER_TYPE m_type;									// ���݂̃��[�V�����^�C�v
	MOTION_PLAYER_TYPE m_typeNext;								// ���̃��[�V�����^�C�v
	int m_nNumKey;												// �L�[��
	int m_nKey;													// ���݂̃L�[
	int m_nKeyNext;												// ���̃L�[
	int m_nKeyOld;												// 1�t���[���O�̃L�[
	float m_fCounter;											// ���[�V�����̃J�E���^�[
	bool m_bConnect;											// ���[�V�������������ǂ���
	int m_nPlayerNum;											// ���[�V�������������ǂ���
};

#endif // _MOTION_PLAYER_H_