//=============================================================================
// 3D�I�u�W�F�N�g���� [scene3D.h]
// Author : ���� ��
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)		//���_�t�H�[�}�b�g3D

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	D3DXVECTOR3 nor;		//�@���x�N�g��
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
} VERTEX_3D;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CScene3D : public CScene
{
public:
	CScene3D(int nPriority = PRIORITY_MODEL);				// �R���X�g���N�^
	~CScene3D();											// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
	static CScene3D *Create(D3DXVECTOR3 pos,
		D3DXVECTOR3 size, D3DXVECTOR3 rot, int nPriolty);	// ��������
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// �ʒu�ݒ菈��
	D3DXVECTOR3 GetPos(void);								// �ʒu�擾����
	void SetTexture(float fU, float fV,
		int nCutU, int nCutV);								// �e�N�X�`���ݒ菈��
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);			// �e�N�X�`����������
	void SetColor(D3DXCOLOR col);							// �J���[�ݒ菈��

protected:
	D3DXVECTOR3 m_pos;										// �ʒu
	D3DXVECTOR3	m_size;										// �T�C�Y
	D3DXVECTOR3 m_rot;										// ����
	LPDIRECT3DTEXTURE9 m_pTexture;							// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;						// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;									// ���[���h�}�g���b�N�X
};

#endif // _SCENE3D_H_