//=============================================================================
// �P�̂̃��f������ [model_single.h]
// Authore : ���� ��
//=============================================================================
#ifndef _MODEL_SINGLE_H_
#define _MODEL_SINGLE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"
#include "model_load.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CModel;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CModelSingle : public CScene
{
public:
	// ���f���̓����̎��
	typedef enum
	{
		MODEL_SINGLE_MOVE_NONE = 0,
		MODEL_SINGLE_MOVE_ROCK,		// �O�[
		MODEL_SINGLE_MOVE_SCISSORS,	// �`���L
		MODEL_SINGLE_MOVE_PAPERS,	// �p�[
		MODEL_SINGLE_MOVE_GOAL,		// �S�[���̏�
		MODEL_SINGLE_MOVE_MAX
	} MODEL_SINGLE_MOVE;

	CModelSingle(int nPriority = PRIORITY_MODEL);		// �R���X�g���N�^
	~CModelSingle();									// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��
	static CModelSingle *Create(D3DXVECTOR3 pos,
		D3DXVECTOR3 rot, CModelLoad::MODEL_TYPE type,
		MODEL_SINGLE_MOVE modelType);					// ��������
	static bool SimpleCollision(CScene *pScene);		// �����蔻��
	void SetNum(int nNum);								// �ԍ��ݒ菈��
	int GetNum(void);									// �ԍ��擾����
	void SetModelNum(int nNum);							// ���̖ڂ��ݒ菈��
	int GetModelNum(void);								// ���̖ڂ��擾����
	int GetModelType(int nNumModel);					// ���f���̎�ނ��擾

private:
	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR3 m_posOld;								// 1�t���[���O�̈ʒu
	D3DXVECTOR3	m_size;									// �T�C�Y
	D3DXVECTOR3 m_rot;									// ����
	D3DXVECTOR3 m_move;									// �ړ���
	CModel *m_pModel;									// ���f���̃|�C���^
	D3DXMATRIX m_mtxWorld;								// ���[���h�}�g���b�N�X
	CModelLoad::MODEL_TYPE m_type;						// ���f���̎��
	MODEL_SINGLE_MOVE m_modelType;						// ���f���̓����̎��
	int m_nNum;											// �̎��ʔԍ�
	int m_nModelNum;									// ���ڂ̑��ꂩ
};

#endif // _MODEL_SINGLE_H_