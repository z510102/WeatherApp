//=============================================================================
//
// スコアクラス [score.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include"scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_DIGIT		8		// 最大桁数
#define SCORE_FILENAME "data/TEXT/newscore.txt"	// ファイル名
#define GAME_SIZE		35	// ゲーム画面時のサイズ
#define RESULT_SIZE		50	// リザルト画面時のサイズ

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;

//*****************************************************************************
//	スコアクラス
//*****************************************************************************
class CScore : public CScene
{
public:
	CScore(int nPriority = 4);	// コンストラクタ
	~CScore();							// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int score);	// スコアの生成

	void SetScore(int nScore);			// スコアの設定
	void AddScore(int nValue);			// スコアの加算
	int GetScore(void);					// スコアの取得
	CPolygon *GetNumber(int nNumber);	// 数字クラス取得

private:
	CPolygon					*m_apPolygon[MAX_DIGIT];	// 最大桁数分の数字
	D3DXVECTOR3					m_pos;						// 位置
	D3DXVECTOR3					m_size;						// 大きさ
	int							m_nScore;					// スコアの値
	int							m_nValue;					// 増減値
	CManager::MODE				m_mode;						// モード
};
#endif //!_SCORE_H_