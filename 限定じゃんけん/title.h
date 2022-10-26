//=============================================================================
// タイトル画面 [title.h]
// Author : 草刈 翔
// Author : 小笠原 彪我
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE_MAX_UI		(8)		// UIの最大数
#define LOGO_POS			200.0f	// タイトルロゴのY座標
#define LOGO_SIZE_X			1150.0f	// タイトルロゴのX幅
#define LOGO_SIZE_Y			300.0f	// タイトルロゴのY高さ
#define PUSH_POS			550.0f	// ゲーム開始UIのY座標
#define PUSH_SIZE_X			800.0f	// ゲーム開始UIのX幅
#define PUSH_SIZE_Y			125.0f	// ゲーム開始UIのY高さ
#define PLAYER_UP_POS_X		150.0f	// 直立ポーズのプレイヤーのX座標
#define PLAYER_UP_SIZE_X	200.0f	// 直立ポーズのプレイヤーのX幅
#define PLAYER_UP_SIZE_Y	300.0f	// 直立ポーズのプレイヤーのY高さ

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene2D;
class CInputKeyboard;
class CInputPad;
class CUi;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CTitle : public CScene
{
	// プレイタイプ
	typedef enum
	{
		TYPE_F_PLAYER = 0,
		TYPE_S_PLAYER,
		TYPE_MAX
	} PLAY_TYPE;

public:
	CTitle();											// コンストラクタ
	~CTitle();											// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理

	static bool GetPush(void) { return m_bPush; }
private:
	CUi *m_apUi[TITLE_MAX_UI];			// UIのポインタ
	int m_nPlaySelect;
	static bool m_bPush;
};

#endif	// _RESULT_H_