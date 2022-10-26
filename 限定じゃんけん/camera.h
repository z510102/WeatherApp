//=============================================================================
// �J�������� [camera.h]
// Author : ���� ��
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_CAMERA				(2)			// �J�����̍ő吔
#define CAMERA_HEIGHT			(80.0f)		// �J�����̍���
#define CAMERA_MOVE_SPEED		(3.0f)		// �J�����̈ړ����x
#define CAMERA_ROTATE_SPEED		(0.03f)		// �J�����̐��񑬓x
#define CAMERA_DISTANCE			(650.0f)	// ���_�ƒ����_�̋���
#define CAMERA_MIN_RENDERER		(10.0f)		// �`��͈͂̍ŏ��l
#define CAMERA_MAX_RENDERER		(10000.0f)	// �`��͈͂̍ő�l

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCamera
{
public:
	CCamera();													// �R���X�g���N�^
	~CCamera();													// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 m_pos, D3DXVECTOR3 rot,
		float viewportX, float viewportY,
		float viewportWidth, float viewporHeight);				// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	static CCamera *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		float viewportX, float viewportY,
		float viewportWidth, float viewporHeight);				// ��������
	void Set(void);												// �J�����ݒ菈��
	void SetPosV(D3DXVECTOR3 pos);								// ���_�ݒ菈��
	D3DXVECTOR3 GetPosV(void);									// ���_�擾����
	void SetPosR(D3DXVECTOR3 pos);								// �����_�ݒ菈��
	D3DXVECTOR3 GetPosR(void);									// �����_�擾����
	void SetRotV(D3DXVECTOR3 rot);								// ���_�̌����ݒ菈��
	D3DXVECTOR3 GetRotV(void);									// ���_�̌����擾����
	void SetNum(int nNum);										// �J�����̔ԍ��ݒ菈��
	int GetNum(void);											// �J�����̔ԍ��擾����
	D3DVIEWPORT9 *GetViewPort(void) { return &m_viewport; }		// �r���[�|�[�g�擾����

private:
	void Move();												// �J�����̈ړ�

#ifdef _DEBUG
	void DebugMove();											// �f�o�b�O�p�̃J����
#endif

	D3DXVECTOR3 m_posV;											// ���݂̎��_
	D3DXVECTOR3 m_posVDest;										// �ړI�̎��_
	D3DXVECTOR3 m_posR;											// ���݂̒����_
	D3DXVECTOR3 m_posRDest;										// �ړI�̒����_
	D3DXVECTOR3 m_vecU;											// ������x�N�g��
	D3DXVECTOR3 m_rot;											// ���_�̌���
	D3DXVECTOR3 m_rotAsk;										// �ړI�̌���
	float m_fHeight;											// ���_���璍���_�̍���
	float m_fRotDiffer;											// �ړI�̌����Ƃ̍�
	float m_fDistance;											// ���_�ƒ����_�̋���
	D3DXMATRIX m_mtxProjection;									// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;										// �r���[�}�g���b�N�X
	D3DVIEWPORT9 m_viewport;									// �r���[�|�[�g
	D3DXMATRIX m_mtxWorldCamera;								// ���[���h�}�g���b�N�X
	bool m_bTurn;												// �J��������]�����ǂ���
	int m_nNum;													// �J�����̔ԍ�
};

#endif // _CAMERA_H_