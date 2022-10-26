//=============================================================================
//
// タイムクラス [time.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include"scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TIME		3		// 最大桁数
#define Time_FILENAME "data/SAVEDATA/currentTime.txt"	// ファイル名
#define GAME_SIZE		35	// ゲーム画面時のサイズ
#define RESULT_SIZE		50	// リザルト画面時のサイズ

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPolygon;

//*****************************************************************************
//	スコアクラス
//*****************************************************************************
class CTime : public CScene
{
public:
	CTime(int nPriority = 4);	// コンストラクタ
	~CTime();							// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	static CTime *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int time);	// スコアの生成

	void SetTime(int nTime);			// スコアの設定
	void AddTime(int nValue);			// スコアの加算
	int GetTime(void);					// スコアの取得
	CPolygon *GetNumber(int nNumber);	// 数字クラス取得

private:
	CPolygon					*m_apPolygon[MAX_TIME];	// 最大桁数分の数字
	D3DXVECTOR3					m_pos;						// 位置
	D3DXVECTOR3					m_size;						// 大きさ
	int							m_nTime;					// スコアの値
	int							m_nValue;					// 増減値
	CManager::MODE				m_mode;						// モード
	DWORD						m_dwCurrentTime;			// 時間計測用
	DWORD						m_dwExecLastTime;			// 同上
};
#endif //!_Time_H_