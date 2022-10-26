//=============================================================================
// モデルのロード処理 [model_load.cpp]
// Authore: 草刈 翔
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "model_load.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CModelLoad::CModelLoad()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CModelLoad::~CModelLoad()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
void CModelLoad::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//**********************//
	//*  モデルの読み込み  *//
	//**********************//
	// 鉄骨
	D3DXLoadMeshFromX("data/MODEL/scaffold.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_TEKKOTU], NULL, &m_aNumMat[MODEL_TYPE_TEKKOTU], &m_apMesh[MODEL_TYPE_TEKKOTU]);

	//+-------------+
	//| プレイヤー1 |
	//+-------------+
	// プレイヤー1：体
	D3DXLoadMeshFromX("data/MODEL/Player1/1P_00_body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_1_BODY], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_1_BODY], &m_apMesh[MODEL_TYPE_PLAYER_1_BODY]);
	// プレイヤー1：頭
	D3DXLoadMeshFromX("data/MODEL/Player1/1P_01_head.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_1_HEAD], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_1_HEAD], &m_apMesh[MODEL_TYPE_PLAYER_1_HEAD]);
	// プレイヤー1：首
	D3DXLoadMeshFromX("data/MODEL/Player1/1P_02_neck.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_1_NECK], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_1_NECK], &m_apMesh[MODEL_TYPE_PLAYER_1_NECK]);
	// プレイヤー1：右腕
	D3DXLoadMeshFromX("data/MODEL/Player1/1P_03_armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_1_ARM_R], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_1_ARM_R], &m_apMesh[MODEL_TYPE_PLAYER_1_ARM_R]);
	// プレイヤー1：左腕
	D3DXLoadMeshFromX("data/MODEL/Player1/1P_04_armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_1_ARM_L], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_1_ARM_L], &m_apMesh[MODEL_TYPE_PLAYER_1_ARM_L]);
	// プレイヤー1：右脚
	D3DXLoadMeshFromX("data/MODEL/Player1/1P_05_legR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_1_LEG_R], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_1_LEG_R], &m_apMesh[MODEL_TYPE_PLAYER_1_LEG_R]);
	// プレイヤー1：左脚
	D3DXLoadMeshFromX("data/MODEL/Player1/1P_06_legL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_1_LEG_L], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_1_LEG_L], &m_apMesh[MODEL_TYPE_PLAYER_1_LEG_L]);
	
	//+-------------+
	//| プレイヤー2 |
	//+-------------+
	// プレイヤー2：体
	D3DXLoadMeshFromX("data/MODEL/Player2/2P_00_body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_2_BODY], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_2_BODY], &m_apMesh[MODEL_TYPE_PLAYER_2_BODY]);
	// プレイヤー2：頭
	D3DXLoadMeshFromX("data/MODEL/Player2/2P_01_head.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_2_HEAD], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_2_HEAD], &m_apMesh[MODEL_TYPE_PLAYER_2_HEAD]);
	// プレイヤー2：首
	D3DXLoadMeshFromX("data/MODEL/Player2/2P_02_neck.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_2_NECK], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_2_NECK], &m_apMesh[MODEL_TYPE_PLAYER_2_NECK]);
	// プレイヤー2：右腕
	D3DXLoadMeshFromX("data/MODEL/Player2/2P_03_armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_2_ARM_R], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_2_ARM_R], &m_apMesh[MODEL_TYPE_PLAYER_2_ARM_R]);
	// プレイヤー2：左腕
	D3DXLoadMeshFromX("data/MODEL/Player2/2P_04_armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_2_ARM_L], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_2_ARM_L], &m_apMesh[MODEL_TYPE_PLAYER_2_ARM_L]);
	// プレイヤー2：右脚
	D3DXLoadMeshFromX("data/MODEL/Player2/2P_05_legR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_2_LEG_R], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_2_LEG_R], &m_apMesh[MODEL_TYPE_PLAYER_2_LEG_R]);
	// プレイヤー2：左脚
	D3DXLoadMeshFromX("data/MODEL/Player2/2P_06_legL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_apBuffMat[MODEL_TYPE_PLAYER_2_LEG_L], NULL, &m_aNumMat[MODEL_TYPE_PLAYER_2_LEG_L], &m_apMesh[MODEL_TYPE_PLAYER_2_LEG_L]);

}

//=============================================================================
// 終了処理
//=============================================================================
void CModelLoad::Uninit(void)
{
	for (int nCntModel = 0; nCntModel < MODEL_TYPE_MAX; nCntModel++)
	{
		// メッシュの破棄
		if (m_apMesh[nCntModel] != NULL)
		{
			m_apMesh[nCntModel]->Release();
			m_apMesh[nCntModel] = NULL;
		}

		// マテリアルの破棄
		if (m_apBuffMat[nCntModel] != NULL)
		{
			m_apBuffMat[nCntModel]->Release();
			m_apBuffMat[nCntModel] = NULL;
		}
	}
}

//=============================================================================
// メッシュ割当処理
//=============================================================================
LPD3DXMESH CModelLoad::GetMesh(MODEL_TYPE type)
{
	return m_apMesh[type];
}

//=============================================================================
// マテリアル割当処理
//=============================================================================
LPD3DXBUFFER CModelLoad::GetBuffMat(MODEL_TYPE type)
{
	return m_apBuffMat[type];
}

//=============================================================================
// マテリアル数割当処理
//=============================================================================
DWORD CModelLoad::GetNumMat(MODEL_TYPE type)
{
	return m_aNumMat[type];
}
