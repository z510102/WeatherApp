//=============================================================================
// テクスチャ処理 [texture.cpp]
// Authore : 草刈 翔
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
void CTexture::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//**************************
	//*  テクスチャの読み込み  *
	//**************************
	// フィールド
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/field000.jpg",
		&m_apTexture[TEX_TYPE_FIELD000]);

	// タイトル：ロゴ
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ハッカソンタイトル.png",
		&m_apTexture[TEX_TYPE_TITLE_LOGO]);
	// タイトル：エンター文字
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/push.png",
		&m_apTexture[TEX_TYPE_TITLE_ENTER]);
	// タイトル：背景
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/titlebg.jpg",
		&m_apTexture[TEX_TYPE_TITLE_BG]);

	// プレイヤーの直立画像
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/player.png",
		&m_apTexture[TEX_TYPE_PLAYER_UP]);
	// プレイヤーのジャンプ画像
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/player_Jump.png",
		&m_apTexture[TEX_TYPE_PLAYER_JUMP]);
	// 1プレイヤーの文字
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/1player.png",
		&m_apTexture[TEX_TYPE_1PLAYER]);
	// 2プレイヤーの文字
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/2player.png",
		&m_apTexture[TEX_TYPE_2PLAYER]);

	// ナンバー：スコア
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/numberscore.png",
		&m_apTexture[TEX_TYPE_SCORE_NUMBER]);
	// ナンバー：タイム
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/numbertime.png",
		&m_apTexture[TEX_TYPE_TIME_NUMBER]);

	// リザルト：背景
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/resultbg.jpg",
		&m_apTexture[TEX_TYPE_RESULT_BG]);

	// チュートリアル：背景
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

	// テクスチャのパスや名前が間違っていると、終了処理でエラーが発生するので注意!!
}

//=============================================================================
// 終了処理
//=============================================================================
void CTexture::Uninit(void)
{
	// テクスチャの総数ぶん繰り返す
	for (int nCntTexture = 0; nCntTexture < TEX_TYPE_MAX; nCntTexture++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCntTexture] != NULL)
		{
			m_apTexture[nCntTexture]->Release();
			m_apTexture[nCntTexture] = NULL;
		}
	}
}

//=============================================================================
// テクスチャの取得処理
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEX_TYPE type)
{
	return m_apTexture[type];
}