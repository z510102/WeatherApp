//=============================================================================
// �^�C�g����� [title.h]
// Author : ���� ��
// Author : ���}�� �V��
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE_MAX_UI		(8)		// UI�̍ő吔
#define LOGO_POS			200.0f	// �^�C�g�����S��Y���W
#define LOGO_SIZE_X			1150.0f	// �^�C�g�����S��X��
#define LOGO_SIZE_Y			300.0f	// �^�C�g�����S��Y����
#define PUSH_POS			550.0f	// �Q�[���J�nUI��Y���W
#define PUSH_SIZE_X			800.0f	// �Q�[���J�nUI��X��
#define PUSH_SIZE_Y			125.0f	// �Q�[���J�nUI��Y����
#define PLAYER_UP_POS_X		150.0f	// �����|�[�Y�̃v���C���[��X���W
#define PLAYER_UP_SIZE_X	200.0f	// �����|�[�Y�̃v���C���[��X��
#define PLAYER_UP_SIZE_Y	300.0f	// �����|�[�Y�̃v���C���[��Y����

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScene2D;
class CInputKeyboard;
class CInputPad;
class CUi;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CTitle : public CScene
{
	// �v���C�^�C�v
	typedef enum
	{
		TYPE_F_PLAYER = 0,
		TYPE_S_PLAYER,
		TYPE_MAX
	} PLAY_TYPE;

public:
	CTitle();											// �R���X�g���N�^
	~CTitle();											// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

	static bool GetPush(void) { return m_bPush; }
private:
	CUi *m_apUi[TITLE_MAX_UI];			// UI�̃|�C���^
	int m_nPlaySelect;
	static bool m_bPush;
};

#endif	// _RESULT_H_