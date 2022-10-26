//=============================================================================
// プレイヤー操作処理 [control_player.h]
// Author : 草刈 翔
//=============================================================================
#ifndef _CONTROL_PLAYER_H_
#define _CONTROL_PLAYER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "control.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene;
class CPlayer;
class CParticle;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_JUMP_MOVE			(1.0f)	// ジャンプで進む大きさ
#define PLAYER_JUMP					(8.0f)	// ジャンプ力
#define PLAYER_GRAVITY				(0.6f)	// 重力の大きさ
#define PLAYER_MOVE_SPEED			(0.5f)	// 移動量の基準値
#define PLAYER_INTERIA_SUBTRACTIO	(0.86f)	// 地上での慣性の減算値
#define PLAYER_MOVE_STOP_COUNT		(0.02f)	// プレイヤーの移動量を0にする時の移動量の値

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CControlPlayer : public CControl
{
	// 次に入力する操作の種類
	typedef enum
	{
		PLAYER_NEXT_INPUT_NONE = 0,	// なし
		PLAYER_NEXT_INPUT_LEFT,		// 左
		PLAYER_NEXT_INPUT_RIGHT,	// 右
		PLAYER_NEXT_MAX
	} PLAYER_NEXT_INPUT;

public:
	CControlPlayer();						// コンストラクタ
	~CControlPlayer();						// デストラクタ
	HRESULT Init(void);						// 初期化処理
	void Uninit(void);						// 終了処理
	void Update(CScene *pScene);			// 更新処理
	static CControlPlayer *Create(void);	// 生成処理
	static bool AddScore(void);				// 生成処理
	static bool AddScore2(void);			// 生成処理

private:
	void GameMove(CPlayer *pPlayer);		// 移動処理
	void Move(CPlayer *pPlayer);			// 移動処理
	void Jump(CPlayer *pPlayer);			// ジャンプ処理
	void MoveInteria(CPlayer *pPlayer);		// 移動の慣性についての処理
	void Rotate(CPlayer *pPlayer);			// 回転処理

	D3DXVECTOR3 m_rot;						// 向き
	D3DXVECTOR3 m_moveOld;					// 1フレーム前の移動量
	float m_fObjectiveRot;					// 目的の向き
	float m_fNumRot;						// 向きを変える量
	float m_fSpeed;							// 移動量に加える速さ
	bool m_bJump;							// ジャンプしてるかどうか
	bool m_bRotate;							// 回転しているかどうか
	int m_nNextModel;						// 次はどの足場か判別
	int m_nNextType;						// 次の足場の種類
	static bool bAddScore;	
	static bool bAddScore2;	
};

#endif	//_CONTROL_PLAYER_H_