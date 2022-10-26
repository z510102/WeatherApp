//=============================================================================
// �r���{�[�h���� [billboard.h]
// Author : ���� ��
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"
#include "scene3D.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CBillboard : public CScene3D
{
public:
	CBillboard(int nPriority = PRIORITY_MODEL);					// �R���X�g���N�^
	~CBillboard();												// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
	static CBillboard *Create(D3DXVECTOR3 pos,
		D3DXVECTOR3 size, D3DXVECTOR3 rot, int nPriolty);		// ��������
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size);				// �ʒu�ݒ菈��
	D3DXVECTOR3 GetPos(void);									// �ʒu�擾����
	void SetTexture(float fU, float fV, int nCutU, int nCutV);	// �e�N�X�`���ݒ菈��
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);				// �e�N�X�`����������
	void SetColor(D3DXCOLOR col);								// �J���[�ݒ菈��

private:
	D3DXVECTOR3 m_pos;											// �ʒu
	D3DXVECTOR3	m_size;											// �T�C�Y

protected:
	D3DXVECTOR3 m_move;											// �ړ���
};

#endif // _BILLBOARD_H_