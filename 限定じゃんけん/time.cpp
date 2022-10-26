//=============================================================================
//
// スコアクラス [Time.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "time.h"
#include "polygon.h"
#include "input_keyboard.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CTime::CTime(int nPriority) : CScene(nPriority)
{
	// メンバ変数のクリア
	memset(&m_apPolygon[0], 0, sizeof(m_apPolygon));
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	m_nTime = 0;
	m_dwCurrentTime = 0;
	m_dwExecLastTime = timeGetTime();
}
//=============================================================================
// デストラクタ
//=============================================================================
CTime::~CTime()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTime::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// モード取得
	m_mode = CManager::GetMode();

	if (m_mode != CManager::MODE_GAME)
	{
		for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
		{
			m_apPolygon[nCntNum] = CPolygon::Create(D3DXVECTOR3(m_pos.x + 40 * nCntNum, m_pos.y, 0.0f), m_size, CTexture::TEX_TYPE_TIME_NUMBER);
		}
	}
	else
	{
		for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
		{
			m_apPolygon[nCntNum] = CPolygon::Create(D3DXVECTOR3(m_pos.x + RESULT_SIZE * nCntNum, m_pos.y, 0.0f), m_size, CTexture::TEX_TYPE_TIME_NUMBER);
		}
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTime::Uninit(void)
{
	// 桁数分破棄
	for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
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
void CTime::Update(void)
{
	m_dwCurrentTime = timeGetTime();	// 現在の時間を取得

	if ((m_dwCurrentTime - m_dwExecLastTime) >= 1000)
	{
		AddTime(-1);
		m_dwCurrentTime = 0;
		m_dwExecLastTime = timeGetTime();
	}

	// 加算されたスコアの情報を剰余算で計算する
	// ポリゴン1枚毎に計算された数字を格納
	m_apPolygon[0]->SetTex(m_nTime % (int)pow(10, 3) / (int)pow(10, 2));
	m_apPolygon[1]->SetTex(m_nTime % (int)pow(10, 2) / (int)pow(10, 1));
	m_apPolygon[2]->SetTex(m_nTime % (int)pow(10, 1));

}

//=============================================================================
// 描画処理
//=============================================================================
void CTime::Draw(void)
{
	for (int nCntNum = 0; nCntNum < MAX_TIME; nCntNum++)
	{
		m_apPolygon[nCntNum]->Draw();
	}
}
//=============================================================================
// スコアの生成
//=============================================================================
CTime *CTime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int time)
{
	CTime *pTime = NULL;
	pTime = new CTime(3);

	if (pTime != NULL)
	{
		pTime->m_nTime = time;
		pTime->m_pos = pos;
		pTime->m_size = size;
		pTime->Init(pos, size);
	}

	return pTime;
}
//=============================================================================
// スコアの設定
//=============================================================================
void CTime::SetTime(int nTime)
{
	m_nTime = nTime;
}
//=============================================================================
// スコア情報加算
//=============================================================================
void CTime::AddTime(int nValue)
{
	m_nTime += nValue;
}
//=============================================================================
// スコア情報取得
//=============================================================================
int CTime::GetTime(void)
{
	return m_nTime;
}
//=============================================================================
// 数字情報取得
//=============================================================================
CPolygon *CTime::GetNumber(int nNumber)
{
	return m_apPolygon[nNumber];
}