//=============================================================================
// キーボード入力処理 [input_keyboard.h]
// Author : 草刈 翔
//=============================================================================
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "input.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();								// コンストラクタ
	~CInputKeyboard();								// デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化処理
	void Uninit(void);								// 終了処理
	void Update(void);								// 更新処理
	bool GetPress(int nKey);						// 入力状態の取得処理(プレス)
	bool GetTrigger(int nKey);						// 入力状態の取得処理(トリガー)

private:
	BYTE m_aKeyState[256];							// キーの情報
	BYTE m_aKeyStateTrigger[256];					// キーの情報(トリガー)
};

#endif	// _INPUT_KEYBOARD_H_