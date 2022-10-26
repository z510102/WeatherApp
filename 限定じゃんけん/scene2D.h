//=============================================================================
// 2D�I�u�W�F�N�g���� [scene2D.h]
// Author : ���� ��
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// ���_�t�H�[�}�b�g

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;  // ���_���W
	float rhw;        // 1.0f�ŌŒ�
	D3DCOLOR col;     // ���_�J���[
	D3DXVECTOR2 tex;  // �e�N�X�`���摜
} VERTEX_2D;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = PRIORITY_NONE);					// �R���X�g���N�^
	~CScene2D();												// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
	static CScene2D *Create(D3DXVECTOR3 pos,
		D3DXVECTOR3 size, int nPriority);						// ��������
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// �ʒu�ݒ菈��
	D3DXVECTOR3 GetPos(void);									// �ʒu�擾����
	D3DXVECTOR3 GetSize(void);									// �T�C�Y�擾����
	void SetTexture(float fU, float fV, int nCutU, int nCutV);	// �e�N�X�`���ݒ菈��
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);				// �e�N�X�`����������
	void SetColor(D3DXCOLOR col);								// �J���[�ݒ菈��

private:
	LPDIRECT3DTEXTURE9 m_pTexture;								// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;											// �ʒu
	D3DXVECTOR3 m_size;											// �T�C�Y
};

#endif // _SCENE2D_H_