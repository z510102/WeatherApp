//=============================================================================
// ���f������ [model.h]
// Aouthor : ���� ��
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "model_load.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MODEL_TEXTURE (128)	// �e�N�X�`���̐�
#define MODEL_VTX		  (8)	// ���_�̐�

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CModel
{
public:
	CModel();											// �R���X�g���N�^
	~CModel();											// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
		CModelLoad::MODEL_TYPE type);					// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��
	static CModel *Create(D3DXVECTOR3 pos,
		D3DXVECTOR3 rot, CModelLoad::MODEL_TYPE type);	// ��������
	void SetParent(CModel *pModel);						// �e���f���ݒ菈��
	D3DXMATRIX GetMtx(void);							// ���[���h�}�g���b�N�X�擾����
	void SetPos(D3DXVECTOR3 pos);						// �ʒu�ݒ菈��
	D3DXVECTOR3 GetPos(void);							// �ʒu�擾����
	void SetRot(D3DXVECTOR3 rot);						// �����ݒ菈��
	D3DXVECTOR3 GetRot(void);							// �����擾����
	D3DXVECTOR3 GetSize(void);							// �T�C�Y�擾����

private:
	void Collision(void);								// �����蔻��
	LPD3DXMESH m_pMesh;									// ���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;							// �}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD m_nNumMat;									// �}�e���A����
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_MODEL_TEXTURE];	// �e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR3	m_size;									// �T�C�Y
	D3DXVECTOR3 m_rot;									// ����
	D3DXMATRIX m_mtxWorld;								// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_vtxMin;								// ���f���̒��_�̍ŏ��l
	D3DXVECTOR3 m_vtxMax;								// ���f���̒��_�̍ő�l
	CModel *m_pParent;									// �e�̃��f��
	D3DXVECTOR3 m_vtxPos[MODEL_VTX];					// 8���_�̈ʒu�ۑ��p�ϐ�
	D3DXVECTOR3 m_vtxRot[MODEL_VTX];					// 8���_�̉�]�ۑ��p�ϐ�
	D3DXMATRIX m_vtxMtxWorld[MODEL_VTX];				// 8���_�̃��[���h�}�g���b�N�X�ۑ��p�ϐ�
};

#endif // _MODEL_H_