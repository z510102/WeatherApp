//=============================================================================
//
// スコアクラス [score.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "score.h"
#include "polygon.h"
#include "input_keyboard.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CScore::CScore(int nPriority) : CScene(nPriority)
{
	// メンバ変数のクリア
	memset(&m_apPolygon[0], 0, sizeof(m_apPolygon));
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	m_nScore = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CScore::~CScore()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// モード取得
	m_mode = CManager::GetMode();

	if (m_mode != CManager::MODE_GAME)
	{
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			m_apPolygon[nCntNum] = CPolygon::Create(D3DXVECTOR3(m_pos.x + RESULT_SIZE * nCntNum, m_pos.y, 0.0f), m_size, CTexture::TEX_TYPE_SCORE_NUMBER);
		}
	}
	else
	{
		for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
		{
			m_apPolygon[nCntNum] = CPolygon::Create(D3DXVECTOR3(m_pos.x + RESULT_SIZE * nCntNum, m_pos.y, 0.0f), m_size, CTexture::TEX_TYPE_SCORE_NUMBER);
		}
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScore::Uninit(void)
{



	// 桁数分破棄
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		if (m_apPolygon[nCntNum] != NULL)
		{
			m_apPolygon[nCntNum]->Uninit();
			delete m_apPolygon[nCntNum];
			m_apPolygon[nCntNum] = NULL;
		}
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScore::Update(void)
{
	// 加算されたスコアの情報を剰余算で計算する
	// ポリゴン1枚毎に計算された数字を格納
	m_apPolygon[0]->SetTex(m_nScore / (int)pow(10, 7));
	m_apPolygon[1]->SetTex(m_nScore % (int)pow(10, 7) / (int)pow(10, 6));
	m_apPolygon[2]->SetTex(m_nScore % (int)pow(10, 6) / (int)pow(10, 5));
	m_apPolygon[3]->SetTex(m_nScore % (int)pow(10, 5) / (int)pow(10, 4));
	m_apPolygon[4]->SetTex(m_nScore % (int)pow(10, 4) / (int)pow(10, 3));
	m_apPolygon[5]->SetTex(m_nScore % (int)pow(10, 3) / (int)pow(10, 2));
	m_apPolygon[6]->SetTex(m_nScore % (int)pow(10, 2) / (int)pow(10, 1));
	m_apPolygon[7]->SetTex(m_nScore % (int)pow(10, 1));

}

//=============================================================================
// 描画処理
//=============================================================================
void CScore::Draw(void)
{
	for (int nCntNum = 0; nCntNum < MAX_DIGIT; nCntNum++)
	{
		m_apPolygon[nCntNum]->Draw();
	}
}
//=============================================================================
// スコアの生成
//=============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int score)
{
	CScore *pScore = NULL;
	pScore = new CScore(3);

	if (pScore != NULL)
	{
		pScore->m_nScore = score;
		pScore->m_pos = pos;
		pScore->m_size = size;
		pScore->Init(pos, size);
	}

	return pScore;
}
//=============================================================================
// スコアの設定
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}
//=============================================================================
// スコア情報加算
//=============================================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}
//=============================================================================
// スコア情報取得
//=============================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}
//=============================================================================
// 数字情報取得
//=============================================================================
CPolygon *CScore::GetNumber(int nNumber)
{
	return m_apPolygon[nNumber];
}