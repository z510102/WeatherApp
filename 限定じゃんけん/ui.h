//=============================================================================
// UI���� [ui.h]
// Author : ���� ��
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CControl;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CUi : public CScene2D
{
public:
	// UI�̎��
	typedef enum
	{
		UI_TYPE_TITLE_LOGO = 0,		// �^�C�g���F���S
		UI_TYPE_TITLE_ENTER,		// �^�C�g���F�G���^�[����
		UI_TYPE_TITLE_BG,			// �^�C�g���F�w�i
		UI_TYPE_TITLE_PLAYER_UP,	// �^�C�g���F�����|�[�Y�̃v���C���[
		UI_TYPE_TITLE_PLAYER_JUMP,	// �^�C�g���F�����|�[�Y�̃v���C���[
		UI_TYPE_TITLE_1PLAYER,		// �^�C�g���F1�v���C���[
		UI_TYPE_TITLE_2PLAYER,		// �^�C�g���F2�v���C���[
		UI_TYPE_SCORE_NUMBER,		// �i���o�[�F�X�R�A
		UI_TYPE_TIME_NUMBER,		// �i���o�[�F�^�C��
		UI_TYPE_RESULT_BG,			// ���U���g�F�w�i
		UI_TYPE_TUTORIAL_BG,	// �`���[�g���A���F�w�i
		UI_TYPE_MAX
	}UI_TYPE;

	CUi(int nPriority = PRIORITY_UI);						// �R���X�g���N�^
	~CUi();													// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��
	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		int nPriolty, UI_TYPE type);						// ��������
	UI_TYPE GetUIType(void);								// ��ގ擾����

private:
	UI_TYPE m_type;											// UI�̎��
	LPDIRECT3DTEXTURE9 m_pTexture;							// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_size;										// �T�C�Y
	D3DXCOLOR	m_col;										// �F
	bool		m_bBrinkFlag;								// �_�Ŕ���
	//CControl *m_pControl;									// �R���g���[���N���X�̃|�C���^
};

#endif // _UI_H_