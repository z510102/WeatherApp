//=============================================================================
// 単体のモデル処理 [model_single.h]
// Authore : 草刈 翔
//=============================================================================
#ifndef _MODEL_SINGLE_H_
#define _MODEL_SINGLE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"
#include "model_load.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModel;

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CModelSingle : public CScene
{
public:
	// モデルの動きの種類
	typedef enum
	{
		MODEL_SINGLE_MOVE_NONE = 0,
		MODEL_SINGLE_MOVE_ROCK,		// グー
		MODEL_SINGLE_MOVE_SCISSORS,	// チョキ
		MODEL_SINGLE_MOVE_PAPERS,	// パー
		MODEL_SINGLE_MOVE_GOAL,		// ゴールの床
		MODEL_SINGLE_MOVE_MAX
	} MODEL_SINGLE_MOVE;

	CModelSingle(int nPriority = PRIORITY_MODEL);		// コンストラクタ
	~CModelSingle();									// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理
	static CModelSingle *Create(D3DXVECTOR3 pos,
		D3DXVECTOR3 rot, CModelLoad::MODEL_TYPE type,
		MODEL_SINGLE_MOVE modelType);					// 生成処理
	static bool SimpleCollision(CScene *pScene);		// 当たり判定
	void SetNum(int nNum);								// 番号設定処理
	int GetNum(void);									// 番号取得処理
	void SetModelNum(int nNum);							// 何体目か設定処理
	int GetModelNum(void);								// 何体目か取得処理
	int GetModelType(int nNumModel);					// モデルの種類を取得

private:
	D3DXVECTOR3 m_pos;									// 位置
	D3DXVECTOR3 m_posOld;								// 1フレーム前の位置
	D3DXVECTOR3	m_size;									// サイズ
	D3DXVECTOR3 m_rot;									// 向き
	D3DXVECTOR3 m_move;									// 移動量
	CModel *m_pModel;									// モデルのポインタ
	D3DXMATRIX m_mtxWorld;								// ワールドマトリックス
	CModelLoad::MODEL_TYPE m_type;						// モデルの種類
	MODEL_SINGLE_MOVE m_modelType;						// モデルの動きの種類
	int m_nNum;											// 個体識別番号
	int m_nModelNum;									// 何個目の足場か
};

#endif // _MODEL_SINGLE_H_