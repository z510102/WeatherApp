//=============================================================================
// マネージャー処理 [manager.cpp]
// Author : 草刈 翔
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "input_keyboard.h"
#include "input_pad.h"
#include "texture.h"
#include "sound.h"
#include "fade.h"
#include "model_load.h"
#include "pause.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CManager::MODE CManager::m_mode = MODE_TITLE;
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial  = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputPad *CManager::m_pInputPad = NULL;
CTexture *CManager::m_pTexture = NULL;
CCamera *CManager::m_apCamera[MAX_CAMERA] = {};
CLight *CManager::m_apLight[MAX_LIGHT] = {};
CSound *CManager::m_pSound = NULL;
CFade *CManager::m_pFade = NULL;
CModelLoad *CManager::m_pModelLoad = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{
	// カメラとライトは配列のため、memsetで一度にクリア
	memset(&m_apCamera, NULL, sizeof(m_apCamera));
	memset(&m_apLight, NULL, sizeof(m_apLight));
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// 時間で乱数を初期化
	srand((unsigned int)time(NULL));

	// レンダラーの生成
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
		if (m_pRenderer != NULL)
		{
			m_pRenderer->Init(hInstance, hWnd, true);
		}
	}

	// キーボードの生成
	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = new CInputKeyboard;
		if (m_pInputKeyboard != NULL)
		{
			m_pInputKeyboard->Init(hInstance, hWnd);
		}
	}

	// ゲームパッドの生成
	if (m_pInputPad == NULL)
	{
		m_pInputPad = new CInputPad;
		if (m_pInputPad != NULL)
		{
			m_pInputPad->Init(hInstance, hWnd);
		}
	}

	// サウンドの生成
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
		if (m_pInputKeyboard != NULL)
		{
			m_pSound->Init(hWnd);
		}
	}

	// テクスチャの生成
	if (m_pTexture == NULL)
	{
		m_pTexture = new CTexture;
		if (m_pTexture != NULL)
		{
			m_pTexture->Init();
		}
	}

	// モデルロードを生成
	if (m_pModelLoad == NULL)
	{
		m_pModelLoad = new CModelLoad;
		if (m_pModelLoad != NULL)
		{
			m_pModelLoad->Init();
		}
	}

	// カメラの生成(フェード生成時のエラー回避のため)
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		m_apCamera[nCntCamera] = CCamera::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			0.0f, 0.0f,						// 描画する画面の左上X座標、左上Y座標
			SCREEN_WIDTH, SCREEN_HEIGHT);	// 描画する画面の幅、高さ
		m_apCamera[nCntCamera]->SetNum(nCntCamera);
	}

	// フェードの生成
	if (m_pFade == NULL)
	{
		m_pFade = new CFade;
		if (m_pFade != NULL)
		{
			m_pFade->Init(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
				D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		}
	}

	// モードの設定
	SetMode(m_mode);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	// 全てのオブジェクトの破棄
	CScene::ReleaseAll();

	/***********************************/
	//			破棄の流れ			   //
	//  ポインタから終了処理を呼び出す //
	//→deleteでポインタのデータを消去 //
	//→NULLを入れて初期化			   //
	/***********************************/

	// レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// キーボードの破棄
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// ゲームパッドの破棄
	if (m_pInputPad != NULL)
	{
		m_pInputPad->Uninit();
		delete m_pInputPad;
		m_pInputPad = NULL;
	}

	// サウンドの破棄
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Uninit();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// モデルロードの破棄
	if (m_pModelLoad != NULL)
	{
		m_pModelLoad->Uninit();
		delete m_pModelLoad;
		m_pModelLoad = NULL;
	}

	// カメラの破棄
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (m_apCamera[nCntCamera] != NULL)
		{
			m_apCamera[nCntCamera]->Uninit();
			delete m_apCamera[nCntCamera];
			m_apCamera[nCntCamera] = NULL;
		}
	}

	// ライトの破棄
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		if (m_apLight[nCntLight] != NULL)
		{
			m_apLight[nCntLight]->Uninit();
			delete m_apLight[nCntLight];
			m_apLight[nCntLight] = NULL;
		}
	}

	// オブジェクトの開放
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	// ポーズ中じゃないなら
	if (CPause::GetPause() == false)
	{
		// カメラの更新
		for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
		{
			if (m_apCamera[nCntCamera] != NULL)
			{
				m_apCamera[nCntCamera]->Update();
			}
		}
	}

	// キーボードの更新
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// ゲームパッドの更新
	if (m_pInputPad != NULL)
	{
		m_pInputPad->Update();
	}

	// レンダリングの更新
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	// 全オブジェクトの描画
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
// モードの設定処理
//=============================================================================
void CManager::SetMode(MODE mode)
{
	// モードの破棄
	switch (m_mode)
	{
		// タイトルの破棄
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;;
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}
		break;;
		// ゲームの破棄
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;
		// リザルトの破棄
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;

	default:
		break;
	}

	// オブジェクトの開放
	CScene::ReleaseAll();

	//現在のモードを更新
	m_mode = mode;

	// モードの生成
	switch (mode)
	{
		// タイトルの生成
	case MODE_TITLE:
		// ヌルチェック
		if (m_pTitle == NULL)
		{
			// クラスの生成
			m_pTitle = new CTitle;

			if (m_pTitle != NULL)
			{
				// 初期化処理
				m_pTitle->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
		break;
	case MODE_TUTORIAL:
		// ヌルチェック
		if (m_pTutorial == NULL)
		{
			// クラスの生成
			m_pTutorial = new CTutorial;

			if (m_pTutorial != NULL)
			{
				// 初期化処理
				m_pTutorial->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
		break;
		// ゲームの生成
	case MODE_GAME:
		// ヌルチェック
		if (m_pGame == NULL)
		{
			// クラスの生成
			m_pGame = new CGame;

			if (m_pGame != NULL)
			{
				// カメラ・ライトの破棄～生成
				GameSetUp(1);

				// 初期化処理
				m_pGame->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
		break;
		// リザルトの生成
	case MODE_RESULT:
		// ヌルチェック
		if (m_pResult == NULL)
		{
			// クラスの生成
			m_pResult = new CResult;

			if (m_pResult != NULL)
			{
				// 初期化処理
				m_pResult->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
		break;

	default:
		break;
	}
}

//=============================================================================
// モード取得処理
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// ゲーム取得処理
//=============================================================================
CGame* CManager::GetGame(void)
{
	return m_pGame;
}

//=============================================================================
// デバイス取得処理
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// キーボード取得処理
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// ゲームパッド取得処理
//=============================================================================
CInputPad *CManager::GetInputPad(void)
{
	return m_pInputPad;
}

//=============================================================================
// テクスチャ取得処理
//=============================================================================
CTexture *CManager::GetTexture(void)
{
	return m_pTexture;
}

//=============================================================================
// カメラ取得処理
//=============================================================================
CCamera **CManager::GetCamera(void)
{
	return &m_apCamera[0];
}

//=============================================================================
// ライト取得処理
//=============================================================================
CLight *CManager::GetLight(void)
{
	return m_apLight[0];
}

//=============================================================================
// サウンド取得処理
//=============================================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
// フェード取得処理
//=============================================================================
CFade *CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
// モデルロード取得処理
//=============================================================================
CModelLoad *CManager::GetModelLoad(void)
{
	return m_pModelLoad;
}

//=============================================================================
// ゲーム画面のセットアップ処理
//=============================================================================
void CManager::GameSetUp(int nCamera)
{
	// カメラの破棄
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		if (m_apCamera[nCntCamera] != NULL)
		{
			m_apCamera[nCntCamera]->Uninit();
			delete m_apCamera[nCntCamera];
			m_apCamera[nCntCamera] = NULL;
		}
	}
	// ライトの破棄
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		if (m_apLight[nCntLight] != NULL)
		{
			m_apLight[nCntLight]->Uninit();
			delete m_apLight[nCntLight];
			m_apLight[nCntLight] = NULL;
		}
	}

	// ライトの生成
	m_apLight[0] = CLight::Create(D3DXVECTOR3(-0.2f, -0.8f, 0.4f), D3DXVECTOR3(400.0f, 800.0f, -400.0f));
	m_apLight[1] = CLight::Create(D3DXVECTOR3(0.4f, 0.8f, -0.4f), D3DXVECTOR3(-100.0f, 0.0f, 100.0f));
	m_apLight[2] = CLight::Create(D3DXVECTOR3(0.0f, -0.4f, 0.4f), D3DXVECTOR3(100.0f, 0.0f, -100.0f));

	// カメラの生成
	for (int nCntCamera = 0; nCntCamera < nCamera; nCntCamera++)
	{
		float fWidth;

		if (nCamera == 1)
		{
			fWidth = SCREEN_WIDTH;
		}
		else if (nCamera == 2)
		{
			fWidth = SCREEN_WIDTH / 2;
		}

		m_apCamera[nCntCamera] = CCamera::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			(float)(SCREEN_WIDTH / 2 * nCntCamera), 0.0f,		// 描画する画面の左上X座標、左上Y座標
			fWidth, SCREEN_HEIGHT);								// 描画する画面の幅、高さ

																// カメラの番号を設定
		m_apCamera[nCntCamera]->SetNum(nCntCamera);
	}
}