//=============================================================================
//
// 汎用ポリゴンクラス [polygon.h]
// Author : 小笠原　彪我
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"
#include "texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_VERTEX (4)	// 頂点数

//*****************************************************************************
//	汎用ポリゴンクラス
//*****************************************************************************
class CPolygon
{
public:
	CPolygon();						// コンストラクタ
	~CPolygon();					// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);				// 終了処理
	void Update(void);				// 更新処理
	void Draw(void);				// 描画処理

	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CTexture::TEX_TYPE type);		// 数字の生成
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	// テクスチャの割り当て
	void SetTex(int nNumber);						// テクスチャ座標を設定
	void SetPolygon(int nNumber);					// テクスチャ数を設定

private:
	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;			// 位置
	D3DXVECTOR3				m_size;			// 大きさ
	CTexture::TEX_TYPE		m_type;			// テクスチャの種類
	float					m_fTexU;
	float					m_fTexV;
};
#endif //!_POLYGON_H_