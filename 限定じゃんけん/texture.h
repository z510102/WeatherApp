//=============================================================================
// �e�N�X�`������ [texture.cpp]
// Authore : ���� ��
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTexture
{
public:
	// �e�N�X�`���̎��
	typedef enum
	{
		TEX_TYPE_FIELD000 = 0,	// �t�B�[���h
		TEX_TYPE_TITLE_LOGO,	// �^�C�g���F���S
		TEX_TYPE_TITLE_ENTER,	// �^�C�g���F�G���^�[����
		TEX_TYPE_TITLE_BG,		// �^�C�g���F�w�i
		TEX_TYPE_PLAYER_UP,		// �v���C���[�̒����摜
		TEX_TYPE_PLAYER_JUMP,	// �v���C���[�̃W�����v�摜
		TEX_TYPE_1PLAYER,		// 1�v���C���[�̕���
		TEX_TYPE_2PLAYER,		// 2�v���C���[�̕���
		TEX_TYPE_SCORE_NUMBER,	// �i���o�[�F�X�R�A
		TEX_TYPE_TIME_NUMBER,	// �i���o�[�F�^�C��
		TEX_TYPE_RESULT_BG,		// ���U���g�F�w�i
		TEX_TYPE_TUTORIAL_BG,	// �`���[�g���A���F�w�i
		TEX_TYPE_SIGN_ROCK,		// �T�C���F�O�[
		TEX_TYPE_SIGN_SCISSORS,	// �T�C���F�`���L
		TEX_TYPE_SIGN_PAPERS,	// �T�C���F�p�[
		TEX_TYPE_MAX
	} TEX_TYPE;

	CTexture();												// �R���X�g���N�^
	~CTexture();											// �f�X�g���N�^
	void Init(void);										// ����������
	void Uninit(void);										// �I������
	LPDIRECT3DTEXTURE9 GetTexture(TEX_TYPE Type);			// �e�N�X�`���擾����

private:
	LPDIRECT3DTEXTURE9	m_apTexture[TEX_TYPE_MAX];			// �e�N�X�`���̃|�C���^
};

#endif