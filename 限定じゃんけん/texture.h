//=============================================================================
// テクスチャ処理 [texture.cpp]
// Authore : 草刈 翔
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTexture
{
public:
	// テクスチャの種類
	typedef enum
	{
		TEX_TYPE_FIELD000 = 0,	// フィールド
		TEX_TYPE_TITLE_LOGO,	// タイトル：ロゴ
		TEX_TYPE_TITLE_ENTER,	// タイトル：エンター文字
		TEX_TYPE_TITLE_BG,		// タイトル：背景
		TEX_TYPE_PLAYER_UP,		// プレイヤーの直立画像
		TEX_TYPE_PLAYER_JUMP,	// プレイヤーのジャンプ画像
		TEX_TYPE_1PLAYER,		// 1プレイヤーの文字
		TEX_TYPE_2PLAYER,		// 2プレイヤーの文字
		TEX_TYPE_SCORE_NUMBER,	// ナンバー：スコア
		TEX_TYPE_TIME_NUMBER,	// ナンバー：タイム
		TEX_TYPE_RESULT_BG,		// リザルト：背景
		TEX_TYPE_TUTORIAL_BG,	// チュートリアル：背景
		TEX_TYPE_SIGN_ROCK,		// サイン：グー
		TEX_TYPE_SIGN_SCISSORS,	// サイン：チョキ
		TEX_TYPE_SIGN_PAPERS,	// サイン：パー
		TEX_TYPE_MAX
	} TEX_TYPE;

	CTexture();												// コンストラクタ
	~CTexture();											// デストラクタ
	void Init(void);										// 初期化処理
	void Uninit(void);										// 終了処理
	LPDIRECT3DTEXTURE9 GetTexture(TEX_TYPE Type);			// テクスチャ取得処理

private:
	LPDIRECT3DTEXTURE9	m_apTexture[TEX_TYPE_MAX];			// テクスチャのポインタ
};

#endif