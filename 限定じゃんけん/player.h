//=============================================================================
// プレイヤー処理 [player.h]
// Authore : 草刈 翔
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModel;
class CMotionPlayer;
class CControl;
class CShadow;
class CParticle;

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define MAX_PLAYER_MODEL	(7)	// モデルの数

//*****************************************************************************
//クラスの定義
//*****************************************************************************
class CPlayer : public CScene
{
public:
	CPlayer(int nPriority = PRIORITY_MODEL);					// コンストラクタ
	~CPlayer();													// デストラクタ
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3	rot,
		int nNumPlayer);										// 生成処理
	D3DXVECTOR3 GetPosOld(void);								// 1フレーム前の位置取得処理
	D3DXVECTOR3 GetRot(void);									// 向き取得処理
	void SetRot(D3DXVECTOR3 rot);								// 向き設定処理
	void SetMove(D3DXVECTOR3 move);								// 移動量設定処理
	D3DXVECTOR3 GetMove(void);									// 移動量取得処理
	void SetJump(bool bJump);									// ジャンプ設定処理
	bool GetJump(void);											// ジャンプ取得処理
	void SetLand(bool bLand);									// 着地設定処理
	bool GetLand(void);											// 着地取得処理
	void SetModelPos(int nCntModel, D3DXVECTOR3 pos);			// モデル毎の位置設定処理
	D3DXVECTOR3 GetModelPos(int nCntModel);						// モデル毎の位置取得処理
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot);			// モデル毎の向き設定処理
	D3DXVECTOR3 GetModelRot(int nCntModel);						// モデル毎の向き取得処理
	CMotionPlayer *GetMotionPlayer(void);						// プレイヤーのモーション取得処理
	void Collision(CScene *pSCene);								// オブジェクトとの当たり判定
	void ShadowCollision(void);									// 影の表示のためのオブジェクトとの当たり判定
	void SetNum(int nNum);										// プレイヤーの番号設定処理
	int GetNum(void);											// プレイヤーの番号取得処理
	void SetStop(bool bStop);									// 止まっているかどうか設定処理
	bool GetStop(void);											// 止まっているかどうか取得処理

private:
	bool Collision(void);										// 当たり判定
	void Move(void);											// 移動

	D3DXVECTOR3 m_pos;											// 位置
	D3DXVECTOR3 m_posOld;										// 1フレーム前の位置
	D3DXVECTOR3 m_move;											// ポリゴンの移動量
	D3DXVECTOR3	m_size;											// サイズ
	D3DXVECTOR3 m_rot;											// 向き
	CModel *m_apModel[MAX_PLAYER_MODEL];						// モデルのポインタ
	D3DXMATRIX m_mtxWorld;										// ワールドマトリックス
	CModel *m_pParent;											// 親モデルへのポインタ
	CControl *m_pControl;										// コントロールのポインタ
	CShadow *m_pShadow;											// シャドウのポインタ
	CMotionPlayer *m_pMotionPlayer;								// プレイヤーモーションのポインタ
	bool m_bLand;												// 着地しているかどうか
	bool m_bJump;												// ジャンプしているかどうか
	bool m_bJumpOld;											// 前フレームジャンプしているかどうか
	bool m_bStop;												// 止まっているかどうか
	int m_nNum;													// プレイヤー識別番号
};

#endif // _PLAYER_H_