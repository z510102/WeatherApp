//=============================================================================
//
// �^�C���N���X [time.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include"scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TIME		3		// �ő包��
#define Time_FILENAME "data/SAVEDATA/currentTime.txt"	// �t�@�C����
#define GAME_SIZE		35	// �Q�[����ʎ��̃T�C�Y
#define RESULT_SIZE		50	// ���U���g��ʎ��̃T�C�Y

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;

//*****************************************************************************
//	�X�R�A�N���X
//*****************************************************************************
class CTime : public CScene
{
public:
	CTime(int nPriority = 4);	// �R���X�g���N�^
	~CTime();							// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	static CTime *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int time);	// �X�R�A�̐���

	void SetTime(int nTime);			// �X�R�A�̐ݒ�
	void AddTime(int nValue);			// �X�R�A�̉��Z
	int GetTime(void);					// �X�R�A�̎擾
	CPolygon *GetNumber(int nNumber);	// �����N���X�擾

private:
	CPolygon					*m_apPolygon[MAX_TIME];	// �ő包�����̐���
	D3DXVECTOR3					m_pos;						// �ʒu
	D3DXVECTOR3					m_size;						// �傫��
	int							m_nTime;					// �X�R�A�̒l
	int							m_nValue;					// �����l
	CManager::MODE				m_mode;						// ���[�h
	DWORD						m_dwCurrentTime;			// ���Ԍv���p
	DWORD						m_dwExecLastTime;			// ����
};
#endif //!_Time_H_