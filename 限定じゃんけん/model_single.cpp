//=============================================================================
// 単体のモデル処理 [model_single.cpp]
// Authore : 草刈 翔
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "model_single.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "model_load.h"
#include "player.h"
#include "game.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CModelSingle::CModelSingle(int nPriority) :CScene(nPriority)
{
	// 変数のクリア
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pModel = NULL;
	m_modelType = MODEL_SINGLE_MOVE_NONE;
	m_nNum = 99;
	m_nModelNum = 0;
}

//================================================
// デストラクタ
//================================================
CModelSingle::~CModelSingle()
{

}

//================================================
// 初期化処理
//================================================
HRESULT CModelSingle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 変数の初期化
	m_pos = pos;
	m_posOld = m_pos;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// モデルの生成
	m_pModel = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_rot, m_type);

	// 親モデルの設定(単体のためNULLを入れる)
	m_pModel->SetParent(NULL);

	// オブジェクトの種類の設定
	SetObjType(CScene::OBJECT_TYPE_MODEL);

	// サイズを取得
	m_size = m_pModel->GetSize();
	SetSize(m_size);
	SetPos(m_pos);

	return S_OK;
}

//================================================
// 終了処理
//================================================
void CModelSingle::Uninit(void)
{
	// 開放処理
	Release();
}

//================================================
// 更新処理
//================================================
void CModelSingle::Update(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 位置の反映
	m_pos = pos;
	m_posOld = pos;

	//モデルの移動処理
	/*if (m_pControl != NULL)
	{
		m_pControl->Update(this);
		m_move = m_pControl->GetMove();
	}*/

	// 移動量の反映
	m_pos += m_move;

	// 位置を設定
	SetPos(m_pos);
	SetPosOld(m_posOld);
}

//================================================
// 描画処理
//================================================
void CModelSingle::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//モデルのワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//モデルの向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//モデルの位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// モデルの描画
	m_pModel->Draw();
}

//================================================
// 生成処理
//================================================
CModelSingle *CModelSingle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModelLoad::MODEL_TYPE type, MODEL_SINGLE_MOVE modelType)
{
	// インスタンスの生成
	CModelSingle *pModelSingle = NULL;

	// ヌルチェック
	if (pModelSingle == NULL)
	{
		// クラスの生成
		pModelSingle = new CModelSingle;
		if (pModelSingle != NULL)
		{
			// 動きをつけたい場合
			switch (modelType)
			{
			case MODEL_SINGLE_MOVE_NONE:

				break;

			default:
				break;
			}

			// 変数の初期化
			pModelSingle->m_rot = rot;
			pModelSingle->m_type = type;
			pModelSingle->m_modelType = modelType;

			// 初期化処理
			pModelSingle->Init(pos, pModelSingle->m_size);
		}
	}

	return pModelSingle;
}

//================================================
//当たり判定処理
//================================================
bool CModelSingle::SimpleCollision(CScene *pScene)
{
	bool bLand = false;	//着地しているかどうか

	//オブジェクト情報を入れるポインタ
	CScene *pObject = NULL;
	//オブジェクト情報を保存するポインタ変数
	CScene *pSaveObject = NULL;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CScene::PRIORITY_MODEL);

	while (pObject != NULL)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJECT_TYPE_MODEL)
		{
			//モデルシングルにキャスト
			CModelSingle *pModelSingle = NULL;
			pModelSingle = (CModelSingle*)pObject;

			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//対象の位置
			D3DXVECTOR3 posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//モデルの位置
			D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//対象のサイズ
			D3DXVECTOR3 sizeModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//モデルのサイズ
			D3DXVECTOR3 posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//対象の1フレーム前の位置

																		//モデルの位置・サイズ取得
			posModel = pModelSingle->GetPos();
			sizeModel = pModelSingle->GetSize();

			//対象の位置・サイズ取得
			pos = pScene->GetPos();
			posOld = pScene->GetPosOld();
			size = pScene->GetSize();

			if (pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
				pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
				pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
				pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
				pos.y <= posModel.y + sizeModel.y &&
				posOld.y >= posModel.y + sizeModel.y)
			{
				pos.y = posModel.y + sizeModel.y;
				//位置を設定
				pScene->SetPos(pos);

				if (pModelSingle->m_modelType == MODEL_SINGLE_MOVE_GOAL)
				{
					//フェーズをゴールにする
					if (CManager::GetGame() != NULL)
					{
						//プレイヤーにキャスト
						CPlayer *pPlayer = NULL;
						pPlayer = (CPlayer*)pScene;

						CManager::GetGame()->SetPhase(CGame::GAME_PHASE_CLEAR);
					}
				}

				bLand = true;
			}
			else if (pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
				pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
				pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
				pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
				pos.y + size.y >= posModel.y &&
				posOld.y + size.y <= posModel.y)
			{
				pos.y = posModel.y - size.y;
				//位置を設定
				pScene->SetPos(pos);
			}
			if (pos.y + size.y > posModel.y &&
				pos.y < posModel.y + sizeModel.y &&
				pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
				pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
				pos.x + size.x / 2.0f >= posModel.x - sizeModel.x / 2.0f &&
				posOld.x + size.x / 2.0f <= posModel.x - sizeModel.x / 2.0f)
			{
				pos.x = posModel.x - sizeModel.x / 2.0f - size.x / 2.0f;
				//位置を設定
				pScene->SetPos(pos);
			}
			else if (pos.y + size.y > posModel.y &&
				pos.y < posModel.y + sizeModel.y &&
				pos.z + size.x / 2.0f > posModel.z - sizeModel.z / 2.0f &&
				pos.z - size.x / 2.0f < posModel.z + sizeModel.z / 2.0f &&
				pos.x - size.x / 2.0f <= posModel.x + sizeModel.x / 2.0f &&
				posOld.x - size.x / 2.0f >= posModel.x + sizeModel.x / 2.0f)
			{
				pos.x = posModel.x + sizeModel.x / 2.0f + size.x / 2.0f;
				//位置を設定
				pScene->SetPos(pos);
			}
			if (pos.y + size.y > posModel.y &&
				pos.y < posModel.y + sizeModel.y &&
				pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
				pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
				pos.z + size.x / 2.0f >= posModel.z - sizeModel.z / 2.0f &&
				posOld.z + size.x / 2.0f <= posModel.z - sizeModel.z / 2.0f)
			{
				pos.z = posModel.z - sizeModel.z / 2.0f - size.x / 2.0f;
				//位置を設定
				pScene->SetPos(pos);
			}
			else if (pos.y + size.y > posModel.y &&
				pos.y < posModel.y + sizeModel.y &&
				pos.x + size.x / 2.0f > posModel.x - sizeModel.x / 2.0f &&
				pos.x - size.x / 2.0f < posModel.x + sizeModel.x / 2.0f &&
				pos.z - size.x / 2.0f <= posModel.z + sizeModel.z / 2.0f &&
				posOld.z - size.x / 2.0f >= posModel.z + sizeModel.z / 2.0f)
			{
				pos.z = posModel.z + sizeModel.z / 2.0f + size.x / 2.0f;
				//位置を設定
				pScene->SetPos(pos);
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
	return bLand;
}

// 番号設定処理
void CModelSingle::SetNum(int nNum)
{
	m_nNum = nNum;
}
// 番号取得処理
int CModelSingle::GetNum(void)
{
	return m_nNum;
}
// 何体目か設定処理
void CModelSingle::SetModelNum(int nNum)
{
	m_nModelNum = nNum;
}
// 何体目か取得処理
int CModelSingle::GetModelNum(void)
{
	return m_nModelNum;
}

int CModelSingle::GetModelType(int nNumModel)
{
	if (nNumModel == m_nModelNum)
	{
		int nType = (int)m_modelType;

		return nType;
	}
	else
	{
		return false;
	}
}