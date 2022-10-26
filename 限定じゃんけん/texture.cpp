//=============================================================================
// �e�N�X�`������ [texture.cpp]
// Authore : ���� ��
//=============================================================================
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// ����������
//=============================================================================
void CTexture::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//**************************
	//*  �e�N�X�`���̓ǂݍ���  *
	//**************************
	// �t�B�[���h
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/field000.jpg",
		&m_apTexture[TEX_TYPE_FIELD000]);

	// �^�C�g���F���S
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/�n�b�J�\���^�C�g��.png",
		&m_apTexture[TEX_TYPE_TITLE_LOGO]);
	// �^�C�g���F�G���^�[����
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/push.png",
		&m_apTexture[TEX_TYPE_TITLE_ENTER]);
	// �^�C�g���F�w�i
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/titlebg.jpg",
		&m_apTexture[TEX_TYPE_TITLE_BG]);

	// �v���C���[�̒����摜
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/player.png",
		&m_apTexture[TEX_TYPE_PLAYER_UP]);
	// �v���C���[�̃W�����v�摜
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/player_Jump.png",
		&m_apTexture[TEX_TYPE_PLAYER_JUMP]);
	// 1�v���C���[�̕���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/1player.png",
		&m_apTexture[TEX_TYPE_1PLAYER]);
	// 2�v���C���[�̕���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/2player.png",
		&m_apTexture[TEX_TYPE_2PLAYER]);

	// �i���o�[�F�X�R�A
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/numberscore.png",
		&m_apTexture[TEX_TYPE_SCORE_NUMBER]);
	// �i���o�[�F�^�C��
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/numbertime.png",
		&m_apTexture[TEX_TYPE_TIME_NUMBER]);

	// ���U���g�F�w�i
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/resultbg.jpg",
		&m_apTexture[TEX_TYPE_RESULT_BG]);

	// �`���[�g���A���F�w�i
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorialbg.png",
		&m_apTexture[TEX_TYPE_TUTORIAL_BG]);

	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/goo.png",
		&m_apTexture[TEX_TYPE_SIGN_ROCK]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/choki.png",
		&m_apTexture[TEX_TYPE_SIGN_SCISSORS]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/par.png",
		&m_apTexture[TEX_TYPE_SIGN_PAPERS]);

	// �e�N�X�`���̃p�X�▼�O���Ԉ���Ă���ƁA�I�������ŃG���[����������̂Œ���!!
}

//=============================================================================
// �I������
//=============================================================================
void CTexture::Uninit(void)
{
	// �e�N�X�`���̑����Ԃ�J��Ԃ�
	for (int nCntTexture = 0; nCntTexture < TEX_TYPE_MAX; nCntTexture++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCntTexture] != NULL)
		{
			m_apTexture[nCntTexture]->Release();
			m_apTexture[nCntTexture] = NULL;
		}
	}
}

//=============================================================================
// �e�N�X�`���̎擾����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEX_TYPE type)
{
	return m_apTexture[type];
}