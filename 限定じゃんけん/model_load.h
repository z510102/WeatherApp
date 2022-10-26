//=============================================================================
// ���f���̃��[�h���� [model_load.h]
// Authore: ���� ��
//=============================================================================
#ifndef _MODEL_LOAD_H_
#define _MODEL_LOAD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CModelLoad
{
public:
	// ���f���̎��
	typedef enum
	{
		MODEL_TYPE_TEKKOTU = 0,			// �S��
		MODEL_TYPE_PLAYER_1_BODY,		// �v���C���[1�F��
		MODEL_TYPE_PLAYER_1_HEAD,		// �v���C���[1�F��
		MODEL_TYPE_PLAYER_1_NECK,		// �v���C���[1�F��
		MODEL_TYPE_PLAYER_1_ARM_R,		// �v���C���[1�F�E�r
		MODEL_TYPE_PLAYER_1_ARM_L,		// �v���C���[1�F���r
		MODEL_TYPE_PLAYER_1_LEG_R,		// �v���C���[1�F�E�r
		MODEL_TYPE_PLAYER_1_LEG_L,		// �v���C���[1�F���r
		MODEL_TYPE_PLAYER_2_BODY,		// �v���C���[2�F��
		MODEL_TYPE_PLAYER_2_HEAD,		// �v���C���[2�F��
		MODEL_TYPE_PLAYER_2_NECK,		// �v���C���[2�F��
		MODEL_TYPE_PLAYER_2_ARM_R,		// �v���C���[2�F�E�r
		MODEL_TYPE_PLAYER_2_ARM_L,		// �v���C���[2�F���r
		MODEL_TYPE_PLAYER_2_LEG_R,		// �v���C���[2�F�E�r
		MODEL_TYPE_PLAYER_2_LEG_L,		// �v���C���[2�F���r
		MODEL_TYPE_MAX
	} MODEL_TYPE;

	CModelLoad();								// �R���X�g���N�^
	~CModelLoad();								// �f�X�g���N�^
	void Init(void);							// ����������
	void Uninit(void);							// �I������
	LPD3DXMESH GetMesh(MODEL_TYPE type);		// ���b�V����������
	LPD3DXBUFFER GetBuffMat(MODEL_TYPE type);	// �}�e���A����������
	DWORD GetNumMat(MODEL_TYPE type);			// �}�e���A�����̊�������

private:
	LPD3DXMESH m_apMesh[MODEL_TYPE_MAX];		// ���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_apBuffMat[MODEL_TYPE_MAX];	// �}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD m_aNumMat[MODEL_TYPE_MAX];			// �}�e���A����
};

#endif // _MODEL_LOAD_H_