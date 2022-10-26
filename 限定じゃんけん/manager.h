//=============================================================================
// �}�l�[�W���[���� [manager.h]
// Author : ���� ��
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "camera.h"
#include "light.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CRenderer;
class CTitle;
class CGame;
class CResult;
class CTutorial;
class CModelLoad;
class CInputKeyboard;
class CInputPad;
class CTexture;
class CCamera;
class CLight;
class CSound;
class CFade;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CManager
{
public:
	// ���[�h�̎��
	typedef enum
	{
		MODE_TITLE = 0,	// �^�C�g��
		MODE_GAME,		// �Q�[��
		MODE_TUTORIAL,	// �`���[�g���A��
		MODE_RESULT,	// ���U���g
		MODE_MAX,
	} MODE;

	CManager();													// �R���X�g���N�^
	~CManager();												// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��
	static void SetMode(MODE mode);								// ���[�h�ݒ菈��
	static MODE GetMode(void);									// ���[�h�擾����
	static CGame *GetGame(void);								// �Q�[���擾����
	static CRenderer *GetRenderer(void);						// �����_���[�擾����
	static CInputKeyboard *GetInputKeyboard(void);				// �L�[�{�[�h�擾����
	static CInputPad *GetInputPad(void);						// �Q�[���p�b�h�擾����
	static CTexture *GetTexture(void);							// �e�N�X�`���擾����
	static CCamera **GetCamera(void);							// �J�����擾����
	static CLight *GetLight(void);								// ���C�g�擾����
	static CSound *GetSound(void);								// �T�E���h�擾����
	static CFade *GetFade(void);								// �t�F�[�h�擾����
	static CModelLoad *GetModelLoad(void);						// ���f�����[�h�̎擾����

private:
	static void GameSetUp(int nCamera);							// �Q�[����ʂ̃Z�b�g�A�b�v����

	static MODE m_mode;											// ���݂̃��[�h
	static CTitle *m_pTitle;									// �^�C�g���̃|�C���^
	static CGame *m_pGame;										// �Q�[���̃|�C���^
	static CResult *m_pResult;									// ���U���g�̃|�C���^
	static CTutorial *m_pTutorial;								// ���U���g�̃|�C���^
	static CRenderer *m_pRenderer;								// �����_���[�N���X�̃|�C���^
	static CInputKeyboard *m_pInputKeyboard;					// �L�[�{�[�h�N���X�̃|�C���^
	static CInputPad *m_pInputPad;								// �Q�[���p�b�h�N���X�̃|�C���^
	static CTexture *m_pTexture;								// �e�N�X�`���̃|�C���^
	static CCamera *m_apCamera[MAX_CAMERA];						// �J�����̃|�C���^
	static CLight *m_apLight[MAX_LIGHT];						// ���C�g�̃|�C���^
	static CSound *m_pSound;									// �T�E���h�̃|�C���^
	static CFade *m_pFade;										// �t�F�[�h�̃|�C���^
	static CModelLoad *m_pModelLoad;							// ���f�����[�h�̃|�C���^
};

#endif // _MANAGER_H_