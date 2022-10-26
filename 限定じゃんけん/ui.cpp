//=============================================================================
// UI処理 [ui.h]
// Author : 草刈 翔
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "ui.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "control.h"
//#include "control_ui_title_enter.h"
//#include "control_ui_game_countdown.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CUi::CUi(int nPriority) :CScene2D(nPriority)
{
	// 変数のクリア
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_pControl = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CUi::~CUi()
{

}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CUi::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 継承元クラスの初期化処理
	CScene2D::Init(pos, size);

	// 変数の初期化
	m_size = size;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CUi::Uninit(void)
{
	// 継承元クラスの終了処理
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CUi::Update(void)
{
	// 指定したUIの種類でテクスチャを変え、割り当てる
	switch (m_type)
	{
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// タイトル系
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// タイトル：エンター文字
	case UI_TYPE_TITLE_ENTER:
		//点滅させる
		if (CManager::GetMode() == CManager::MODE_TITLE)
		{
			if (m_bBrinkFlag == false)
			{
				m_col.a += 0.015f;
				if (m_col.a >= 1.0f)
				{
					m_col.a = 1.0f;
					m_bBrinkFlag = true;
				}
			}
			else
			{
				m_col.a -= 0.015f;
				if (m_col.a <= 0.0f)
				{
					m_col.a = 0.0f;
					m_bBrinkFlag = false;
				}
			}
			SetColor(m_col);
		}
		else
		{
			m_col.a = 0.0f;
			SetColor(m_col);
		}
		break;

	default:
		break;
	}

	// コントロールクラスがヌルじゃなかったら
	//if (m_pControl != NULL)
	//{
	//	// 自身のポインタを入れ、更新処理
	//	m_pControl->Update(this);

	//	// Scene2Dから位置・サイズを取得
	//	D3DXVECTOR3 pos;
	//	pos = GetPos();

	//	m_size = GetSize();

	//	// 取得した位置に移動量を加算
	//	pos += m_pControl->GetMove();

	//	// 位置、サイズを設定
	//	SetPos(pos, m_size);
	//}
}

//=============================================================================
// 描画処理
//=============================================================================
void CUi::Draw(void)
{
	// 継承元クラスの描画処理
	CScene2D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CUi* CUi::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriolity, UI_TYPE type)
{
	// インスタンスの生成
	CUi *pUi = NULL;

	// ヌルチェック
	if (pUi == NULL)
	{
		// クラスの生成
		pUi = new CUi(nPriolity);
		if (pUi != NULL)
		{
			// 指定したUIの種類でテクスチャを変え、割り当てる
			switch (type)
			{
				//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				// タイトル系
				//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
				// タイトル：ロゴ
			case UI_TYPE_TITLE_LOGO:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TITLE_LOGO);
				break;
				// タイトル：エンター文字
			case UI_TYPE_TITLE_ENTER:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TITLE_ENTER);
				break;
				// タイトル：背景
			case UI_TYPE_TITLE_BG:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TITLE_BG);
				break;
				// 直立ポーズのプレイヤー
			case UI_TYPE_TITLE_PLAYER_UP:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_PLAYER_UP);
				break;
				// ジャンプポーズのプレイヤー
			case UI_TYPE_TITLE_PLAYER_JUMP:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_PLAYER_JUMP);
				break;
				// 1プレイヤーの文字
			case UI_TYPE_TITLE_1PLAYER:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_1PLAYER);
				break;
				// 2プレイヤー文字
			case UI_TYPE_TITLE_2PLAYER:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_2PLAYER);
				break;
			case UI_TYPE_RESULT_BG:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_RESULT_BG);
				break;
			case UI_TYPE_TUTORIAL_BG:
				pUi->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_TUTORIAL_BG);
				break;
			default:
				break;
			}
			pUi->BindTexture(pUi->m_pTexture);

			// 変数の初期化
			pUi->m_type = type;

			// 初期化処理
			pUi->Init(pos, size);
		}
	}

	return pUi;
}

//=============================================================================
// 種類の取得処理
//=============================================================================
CUi::UI_TYPE CUi::GetUIType(void)
{
	return m_type;
}