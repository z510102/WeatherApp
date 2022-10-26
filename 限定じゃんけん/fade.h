//=============================================================================
// �t�F�[�h���� [fade.h]
// Author : ���� ��
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include "scene2D.h"

//*****************************************************************************
// �t�F�[�h�N���X
//*****************************************************************************
class CFade : public CScene2D
{
public:
	// �t�F�[�h�̏��
	typedef enum
	{
		FADE_NONE = 0,		// �������Ă��Ȃ�
		FADE_IN,			// �t�F�[�h�C��
		FADE_OUT,			// �t�F�[�h�A�E�g
		FADE_MAX
	} FADE;

	CFade(int nPriority = PRIORITY_FADE);					// �R���X�g���N�^
	~CFade();												// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
	void SetFade(CManager::MODE modeNext, D3DXCOLOR col);	// �ݒ菈��
	static FADE GetFade(void);								// �擾����

private:
	static FADE m_fade;										// �t�F�[�h�̏��
	CManager::MODE m_modeNext;								// ���̉��
	D3DXCOLOR m_color;										// �t�F�[�h�̐F
};
#endif // _FADE_H_