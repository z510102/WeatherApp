//=============================================================================
// �i���o�[�Ǘ����� [number.h]
// Author : ���� ��
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CNumber
{
public:
	CNumber();									// �R���X�g���N�^
	~CNumber();									// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos,
		D3DXVECTOR3 size, D3DXCOLOR col);		// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��
	static CNumber *Create(D3DXVECTOR3 pos,
		D3DXVECTOR3 size, D3DXCOLOR col);		// ��������
	void SetNumber(int nNumber);				// �i���o�[�ݒ菈��
	void SetPos(D3DXVECTOR3 pos);				// �ʒu�ݒ菈��
	void SetColor(D3DXCOLOR col);				// �J���[�ݒ菈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3	m_size;							// �T�C�Y
};

#endif	//_NUMBER_H_