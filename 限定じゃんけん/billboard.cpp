//=============================================================================
// ビルボード処理 [billboard.cpp]
// Author : 草刈 翔
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "billboard.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CBillboard::CBillboard(int nPriority) :CScene3D(nPriority)
{
	// 変数のクリア
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CBillboard::~CBillboard()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBillboard::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 変数の初期化
	m_pos = pos;
	m_size = size / 2;

	// 位置・サイズ設定処理
	CScene::SetPos(m_pos);
	CScene::SetSize(m_size);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(-m_size.x / 2.0f, +m_size.y / 2.0f, +m_size.z / 2.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x / 2.0f, +m_size.y / 2.0f, +m_size.z / 2.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x / 2.0f, -m_size.y / 2.0f, -m_size.z / 2.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x / 2.0f, -m_size.y / 2.0f, -m_size.z / 2.0f);

	// 法線
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBillboard::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBillboard::Update(void)
{
	// 位置・サイズ取得
	D3DXVECTOR3 pos = GetPos();
	m_pos = pos;

	// 移動量反映
	m_pos += m_move;

	// 位置を設定
	CScene::SetPos(m_pos);
}

//=============================================================================
// 描画処理
//=============================================================================
void CBillboard::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Zバッファの更新
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	D3DXMATRIX mtxView;						//ビューマトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	//計算用マトリックス
	D3DXMatrixIdentity(&m_mtxWorld);		//ワールドマトリックスの初期化

											//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,											//開始する頂点のインデックス
		2);											//描画するプリミティブ数

													// Zバッファの更新
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=============================================================================
// 生成処理
//=============================================================================
CBillboard* CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nPriolity)
{
	// インスタンスの生成
	CBillboard *pBillboard = NULL;

	// ヌルチェック
	if (pBillboard == NULL)
	{
		// 優先順位を持たせてクラスを生成
		pBillboard = new CBillboard(nPriolity);
		if (pBillboard != NULL)
		{
			// 変数の初期化
			pBillboard->m_rot = rot;

			// 初期化処理
			pBillboard->Init(pos, size);
		}
	}

	return pBillboard;
}

//=============================================================================
// 位置取得処理
//=============================================================================
D3DXVECTOR3 CBillboard::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 位置設定処理
//=============================================================================
void CBillboard::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;

	//位置・サイズ設定処理
	CScene::SetPos(m_pos);
	CScene::SetSize(m_size);

	VERTEX_3D *pVtx;	// 頂点情報
						//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(-m_size.x / 2.0f, +m_size.y / 2.0f, +m_size.z / 2.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x / 2.0f, +m_size.y / 2.0f, +m_size.z / 2.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x / 2.0f, -m_size.y / 2.0f, -m_size.z / 2.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x / 2.0f, -m_size.y / 2.0f, -m_size.z / 2.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// テクスチャ設定処理
//=============================================================================
void CBillboard::SetTexture(float fU, float fV, int nCutU, int nCutV)
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//テクスチャ設定(U座標の位置、V座標の位置、横の分割数、縦の分割数を入れる)
	pVtx[0].tex = D3DXVECTOR2(fU * (1.0f / nCutU), fV * (1.0f / nCutV));
	pVtx[1].tex = D3DXVECTOR2(fU * (1.0f / nCutU) + (1.0f / nCutU), fV * (1.0f / nCutV));
	pVtx[2].tex = D3DXVECTOR2(fU * (1.0f / nCutU), fV * (1.0f / nCutV) + (1.0f / nCutV));
	pVtx[3].tex = D3DXVECTOR2(fU * (1.0f / nCutU) + (1.0f / nCutU), fV * (1.0f / nCutV) + (1.0f / nCutV));

	m_pVtxBuff->Unlock();
}

//=============================================================================
// テクスチャ割り当て処理
//=============================================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// カラー設定処理
//=============================================================================
void CBillboard::SetColor(D3DXCOLOR col)
{
	// 頂点情報のポインタ
	VERTEX_3D *pVtx;

	// 色を更新
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;
	m_pVtxBuff->Unlock();
}