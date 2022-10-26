//=============================================================================
// モデルのロード処理 [model_load.h]
// Authore: 草刈 翔
//=============================================================================
#ifndef _MODEL_LOAD_H_
#define _MODEL_LOAD_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CModelLoad
{
public:
	// モデルの種類
	typedef enum
	{
		MODEL_TYPE_TEKKOTU = 0,			// 鉄骨
		MODEL_TYPE_PLAYER_1_BODY,		// プレイヤー1：体
		MODEL_TYPE_PLAYER_1_HEAD,		// プレイヤー1：頭
		MODEL_TYPE_PLAYER_1_NECK,		// プレイヤー1：首
		MODEL_TYPE_PLAYER_1_ARM_R,		// プレイヤー1：右腕
		MODEL_TYPE_PLAYER_1_ARM_L,		// プレイヤー1：左腕
		MODEL_TYPE_PLAYER_1_LEG_R,		// プレイヤー1：右脚
		MODEL_TYPE_PLAYER_1_LEG_L,		// プレイヤー1：左脚
		MODEL_TYPE_PLAYER_2_BODY,		// プレイヤー2：体
		MODEL_TYPE_PLAYER_2_HEAD,		// プレイヤー2：頭
		MODEL_TYPE_PLAYER_2_NECK,		// プレイヤー2：首
		MODEL_TYPE_PLAYER_2_ARM_R,		// プレイヤー2：右腕
		MODEL_TYPE_PLAYER_2_ARM_L,		// プレイヤー2：左腕
		MODEL_TYPE_PLAYER_2_LEG_R,		// プレイヤー2：右脚
		MODEL_TYPE_PLAYER_2_LEG_L,		// プレイヤー2：左脚
		MODEL_TYPE_MAX
	} MODEL_TYPE;

	CModelLoad();								// コンストラクタ
	~CModelLoad();								// デストラクタ
	void Init(void);							// 初期化処理
	void Uninit(void);							// 終了処理
	LPD3DXMESH GetMesh(MODEL_TYPE type);		// メッシュ割当処理
	LPD3DXBUFFER GetBuffMat(MODEL_TYPE type);	// マテリアル割当処理
	DWORD GetNumMat(MODEL_TYPE type);			// マテリアル数の割当処理

private:
	LPD3DXMESH m_apMesh[MODEL_TYPE_MAX];		// メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER m_apBuffMat[MODEL_TYPE_MAX];	// マテリアル(材質情報)へのポインタ
	DWORD m_aNumMat[MODEL_TYPE_MAX];			// マテリアル数
};

#endif // _MODEL_LOAD_H_