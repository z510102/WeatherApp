//=============================================================================
// マネージャー処理 [manager.h]
// Author : 草刈 翔
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "camera.h"
#include "light.h"

//*****************************************************************************
// 前方宣言
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
// クラスの定義
//*****************************************************************************
class CManager
{
public:
	// モードの種類
	typedef enum
	{
		MODE_TITLE = 0,	// タイトル
		MODE_GAME,		// ゲーム
		MODE_TUTORIAL,	// チュートリアル
		MODE_RESULT,	// リザルト
		MODE_MAX,
	} MODE;

	CManager();													// コンストラクタ
	~CManager();												// デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
	static void SetMode(MODE mode);								// モード設定処理
	static MODE GetMode(void);									// モード取得処理
	static CGame *GetGame(void);								// ゲーム取得処理
	static CRenderer *GetRenderer(void);						// レンダラー取得処理
	static CInputKeyboard *GetInputKeyboard(void);				// キーボード取得処理
	static CInputPad *GetInputPad(void);						// ゲームパッド取得処理
	static CTexture *GetTexture(void);							// テクスチャ取得処理
	static CCamera **GetCamera(void);							// カメラ取得処理
	static CLight *GetLight(void);								// ライト取得処理
	static CSound *GetSound(void);								// サウンド取得処理
	static CFade *GetFade(void);								// フェード取得処理
	static CModelLoad *GetModelLoad(void);						// モデルロードの取得処理

private:
	static void GameSetUp(int nCamera);							// ゲーム画面のセットアップ処理

	static MODE m_mode;											// 現在のモード
	static CTitle *m_pTitle;									// タイトルのポインタ
	static CGame *m_pGame;										// ゲームのポインタ
	static CResult *m_pResult;									// リザルトのポインタ
	static CTutorial *m_pTutorial;								// リザルトのポインタ
	static CRenderer *m_pRenderer;								// レンダラークラスのポインタ
	static CInputKeyboard *m_pInputKeyboard;					// キーボードクラスのポインタ
	static CInputPad *m_pInputPad;								// ゲームパッドクラスのポインタ
	static CTexture *m_pTexture;								// テクスチャのポインタ
	static CCamera *m_apCamera[MAX_CAMERA];						// カメラのポインタ
	static CLight *m_apLight[MAX_LIGHT];						// ライトのポインタ
	static CSound *m_pSound;									// サウンドのポインタ
	static CFade *m_pFade;										// フェードのポインタ
	static CModelLoad *m_pModelLoad;							// モデルロードのポインタ
};

#endif // _MANAGER_H_