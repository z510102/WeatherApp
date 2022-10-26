//=============================================================================
// ���b�V��(�~��)���� [mesh_cylinder.h]
// Authore : ���� ��
//=============================================================================
#ifndef _MESH_CYLINDER_H_
#define _MESH_CYLINDER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CMeshCylinder : public CScene
{
public:
	CMeshCylinder(int nPriority = PRIORITY_NONE);					// �R���X�g���N�^
	~CMeshCylinder();												// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
	static CMeshCylinder *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		D3DXVECTOR3 rot, int nVertical, int nSide, D3DXCOLOR col,
		bool bOutSide);		// ��������
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);					// �e�N�X�`����������
	void SetNum(int nNum);											// �ԍ��ݒ菈��

private:
	LPDIRECT3DTEXTURE9 m_pTexture;									// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;								// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;								// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;												// �ʒu
	D3DXVECTOR3	m_size;												// �T�C�Y
	D3DXVECTOR3 m_rot;												// ����
	D3DXMATRIX m_mtxWorld;											// ���[���h�}�g���b�N�X
	D3DXCOLOR m_col;												// �J���[
	int m_nSide;													// ���̕�����
	int m_nVertical;												// �c�̕�����
	float m_fRadius;												// ���a
	float m_fAngle;													// �p�x
	float m_fAddAngle;												// ������p�x
	float m_fSpinSpeed;												// ��]�p�x
	float m_fAddSpinSpeed;											// �������]�p�x
	bool m_bOutSide;												// �V�����_�[�̊O���ɕ`�悷�邩�ǂ���
};

#endif // _MESH_CYLINDER_H_