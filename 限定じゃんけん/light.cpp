//=============================================================================
// ライト処理 [light.cpp]
// Author : 草刈 翔
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "light.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
int CLight::m_nNum = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CLight::CLight()
{
	//ライトをクリアする
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));

	// カメラに現在の番号を設定し、カメラの総数を増やす
	m_nCnt = m_nNum;
	m_nNum++;
}

//=============================================================================
//デストラクタ
//=============================================================================
CLight::~CLight()
{
	// カメラの総数を減らす
	m_nNum--;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLight::Init(D3DXVECTOR3 vecDir, D3DXVECTOR3 pos)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ライトの種類を設定
	m_light.Type = D3DLIGHT_DIRECTIONAL;		//平行光源

												// ライトの拡散光を設定
	m_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 位置設定
	m_light.Position = pos;

	// 正規化する(ベクトルの大きさを1にする)
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light.Direction = vecDir;

	// ライトを設定する
	pDevice->SetLight(m_nCnt, &m_light);

	// ライトを有効にする
	pDevice->LightEnable(m_nCnt, TRUE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLight::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CLight::Update(void)
{

}

//=============================================================================
// 生成処理
//=============================================================================
CLight *CLight::Create(D3DXVECTOR3 vecDir, D3DXVECTOR3 pos)
{
	// インスタンスの生成
	CLight *pLight = NULL;

	// ヌルチェック
	if (pLight == NULL)
	{
		// クラスの生成
		pLight = new CLight;
		if (pLight != NULL)
		{
			// 初期化処理
			pLight->Init(vecDir, pos);
		}
	}

	return pLight;
}