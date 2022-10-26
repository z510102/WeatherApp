//=============================================================================
// UI処理 [ui.h]
// Author : 草刈 翔
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CControl;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CUi : public CScene2D
{
public:
	// UIの種類
	typedef enum
	{
		UI_TYPE_TITLE_LOGO = 0,		// タイトル：ロゴ
		UI_TYPE_TITLE_ENTER,		// タイトル：エンター文字
		UI_TYPE_TITLE_BG,			// タイトル：背景
		UI_TYPE_TITLE_PLAYER_UP,	// タイトル：直立ポーズのプレイヤー
		UI_TYPE_TITLE_PLAYER_JUMP,	// タイトル：直立ポーズのプレイヤー
		UI_TYPE_TITLE_1PLAYER,		// タイトル：1プレイヤー
		UI_TYPE_TITLE_2PLAYER,		// タイトル：2プレイヤー
		UI_TYPE_SCORE_NUMBER,		// ナンバー：スコア
		UI_TYPE_TIME_NUMBER,		// ナンバー：タイム
		UI_TYPE_RESULT_BG,			// リザルト：背景
		UI_TYPE_TUTORIAL_BG,	// チュートリアル：背景
		UI_TYPE_MAX
	}UI_TYPE;

	CUi(int nPriority = PRIORITY_UI);						// コンストラクタ
	~CUi();													// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// 初期化処理
	void Uninit(void);										// 終了処理
	void Update(void);										// 更新処理
	void Draw(void);										// 描画処理
	static CUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
		int nPriolty, UI_TYPE type);						// 生成処理
	UI_TYPE GetUIType(void);								// 種類取得処理

private:
	UI_TYPE m_type;											// UIの種類
	LPDIRECT3DTEXTURE9 m_pTexture;							// テクスチャへのポインタ
	D3DXVECTOR3 m_size;										// サイズ
	D3DXCOLOR	m_col;										// 色
	bool		m_bBrinkFlag;								// 点滅判定
	//CControl *m_pControl;									// コントロールクラスのポインタ
};

#endif // _UI_H_