//=============================================================================
// ゲーム画面 [game.h]
// Author : 草刈 翔
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAME_MAX_UI	(3)								// UIの最大数
#define GAME_MAX_MODEL	(200)						// モデルの最大数
#define GAME_MAX_BILLBOARD	(400)					// ビルボードの最大数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CUi;
class CModelSingle;
class CPlayer;
class CMeshField;
class CMeshCylinder;
class CScore;
class CTime;
class CPause;
class CBillboard;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CGame : public CScene
{
public:
	// ゲームのフェイズ
	typedef enum
	{
		GAME_PHASE_NONE = 0,	// なし
		GAME_PHASE_COUNTDOWN,	// スタート前のカウントダウン
		GAME_PHASE_ACTION,		// アクション中
		GAME_PHASE_CLEAR,		// クリア
		GAME_PHASE_MAX
	} GAME_PHASE;

	CGame();											// コンストラクタ
	~CGame();											// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理
	void SetPhase(GAME_PHASE phase);					// フェイズ設定処理
	GAME_PHASE GetPhase(void);							// フェイズ取得処理

private:
	void Phase();										// フェイズ処理

	CUi *m_apUi[GAME_MAX_UI];							// UIのポインタ
	CModelSingle *m_apModelSingle[GAME_MAX_MODEL];		// モデル(単体)のポインタ
	CBillboard *m_apBillboard[GAME_MAX_BILLBOARD];		// ビルボードのポインタ
	CPlayer *m_apPlayer[MAX_PLAYER_NUM];				// プレイヤーのポインタ
	CMeshField *m_pMeshField;							// メッシュフィールドのポインタ
	CMeshCylinder *m_pMeshCylinder;						// メッシュシリンダーのポインタ
	CPause *m_pPause;									// ポーズのポインタ
	CScore *m_pScore;								// スコアのポインタ
	CTime *m_pTime;										// タイムのポインタ
	GAME_PHASE m_phase;									// 現在のフェイズ
	int m_nInterval;									// フェイズ切り替え時のインターバル
};

#endif	// _GAME_H_