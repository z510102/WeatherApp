//=============================================================================
//
// 数字クラス [polygon.cpp]
// Author : 小笠原　彪我
//
//=============================================================================
//=============================================================================
//インクルードファイル
//=============================================================================
#include "polygon.h"
#include"renderer.h"
#include"scene2D.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPolygon::CPolygon()
{
	// メンバ変数のクリア
	memset(&m_pos, 0, sizeof(D3DXVECTOR3));
	memset(&m_size, 0, sizeof(D3DXVECTOR2));
}
//=============================================================================
// デストラクタ
//=============================================================================
CPolygon::~CPolygon()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPolygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,										// 頂点バッファの使用法
		FVF_VERTEX_2D,											// 使用する頂点フォーマット
		D3DPOOL_MANAGED,										// リソースのバッファを保持するメモリ
		&m_pVtxBuff,											// 頂点バッファへのポインタ
		NULL);													// NULLに設定

	VERTEX_2D *pVtx; //頂点バッファへのポインタ

					 //頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標を設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPolygon::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CPolygon::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CPolygon::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}
//=============================================================================
// 数字の生成
//=============================================================================
CPolygon *CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CTexture::TEX_TYPE type)
{
	CPolygon *pPolygon;
	pPolygon = new CPolygon;

	if (pPolygon != NULL)
	{
		pPolygon->Init(pos, size);
		pPolygon->BindTexture(CManager::GetTexture()->GetTexture(type));
	}

	return pPolygon;
}
//=============================================================================
// テクスチャの割り当て
//=============================================================================
void CPolygon::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// テクスチャ座標を設定
//=============================================================================
void CPolygon::SetTex(int nNumber)
{
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);

	m_pVtxBuff->Unlock();
}
