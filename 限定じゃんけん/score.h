//=============================================================================
//
// �X�R�A�N���X [score.h]
// Author : ���}���@�V��
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"
#include"scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DIGIT		8		// �ő包��
#define SCORE_FILENAME "data/TEXT/newscore.txt"	// �t�@�C����
#define GAME_SIZE		35	// �Q�[����ʎ��̃T�C�Y
#define RESULT_SIZE		50	// ���U���g��ʎ��̃T�C�Y

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPolygon;

//*****************************************************************************
//	�X�R�A�N���X
//*****************************************************************************
class CScore : public CScene
{
public:
	CScore(int nPriority = 4);	// �R���X�g���N�^
	~CScore();							// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int score);	// �X�R�A�̐���

	void SetScore(int nScore);			// �X�R�A�̐ݒ�
	void AddScore(int nValue);			// �X�R�A�̉��Z
	int GetScore(void);					// �X�R�A�̎擾
	CPolygon *GetNumber(int nNumber);	// �����N���X�擾

private:
	CPolygon					*m_apPolygon[MAX_DIGIT];	// �ő包�����̐���
	D3DXVECTOR3					m_pos;						// �ʒu
	D3DXVECTOR3					m_size;						// �傫��
	int							m_nScore;					// �X�R�A�̒l
	int							m_nValue;					// �����l
	CManager::MODE				m_mode;						// ���[�h
};
#endif //!_SCORE_H_