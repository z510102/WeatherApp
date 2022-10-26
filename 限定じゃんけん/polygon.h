//=============================================================================
//
// �ėp�|���S���N���X [polygon.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_VERTEX (4)	// ���_��

//*****************************************************************************
//	�ėp�|���S���N���X
//*****************************************************************************
class CPolygon
{
public:
	CPolygon();						// �R���X�g���N�^
	~CPolygon();					// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);				// �I������
	void Update(void);				// �X�V����
	void Draw(void);				// �`�揈��

	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CTexture::TEX_TYPE type);		// �����̐���
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	// �e�N�X�`���̊��蓖��
	void SetTex(int nNumber);						// �e�N�X�`�����W��ݒ�
	void SetPolygon(int nNumber);					// �e�N�X�`������ݒ�

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;			// �ʒu
	D3DXVECTOR3				m_size;			// �傫��
	CTexture::TEX_TYPE		m_type;			// �e�N�X�`���̎��
	float					m_fTexU;
	float					m_fTexV;
};
#endif //!_POLYGON_H_