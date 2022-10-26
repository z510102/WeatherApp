//=============================================================================
// プレイヤー操作処理 [control_player.cpp]
// Author : 草刈 翔
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "control_player.h"
#include "manager.h"
#include "input_keyboard.h"
#include "input_pad.h"
#include "player.h"
#include "motion_player.h"
#include "camera.h"
#include "sound.h"
#include "model_single.h"

bool CControlPlayer::bAddScore = false;
bool CControlPlayer::bAddScore2 = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CControlPlayer::CControlPlayer()
{
	// 変数のクリア
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_fSpeed = 0.0f;
	m_bRotate = false;
	m_bJump = false;
	m_nNextModel = 0;
	m_nNextType = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CControlPlayer::~CControlPlayer()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CControlPlayer::Init(void)
{
	// 変数の初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_fSpeed = PLAYER_MOVE_SPEED;
	m_bRotate = false;
	m_bJump = false;

	m_nNextModel = 1;
	m_nNextType = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CControlPlayer::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CControlPlayer::Update(CScene *pScene)
{
	bAddScore = false;
	bAddScore2 = false;

	// 引数のポインタをプレイヤークラスのポインタにキャスト
	CPlayer *pPlayer = NULL;
	pPlayer = (CPlayer*)pScene;

	// モーション取得処理
	CMotionPlayer *pMotionPlayer = NULL;
	pMotionPlayer = pPlayer->GetMotionPlayer();

	// サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	D3DXVECTOR3 rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// カメラのポインタのアドレス取得
	CCamera **pCameraAddress = CManager::GetCamera();

	// カメラの最大数ぶん、ポインタ配列を進める
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++, pCameraAddress++)
	{
		// カメラの取得
		CCamera *pCamera = &**pCameraAddress;

		if (pCamera != NULL)
		{
			// プレイヤーの番号とカメラの番号が同じだったら
			if (pPlayer->GetNum() == pCamera->GetNum())
			{
				// カメラの向き取得
				rotCamera = pCamera->GetRotV();
			}
		}
	}

	// 移動量を設定
	m_move = pPlayer->GetMove();
	m_moveOld = m_move;

	// 重力
	m_move.y -= PLAYER_GRAVITY;

	// 止められていないかつ
	if (pPlayer->GetStop() == false)
	{
		// 移動処理(詳しい処理は関数の中)
		GameMove(pPlayer);
	}

	// 移動の慣性(詳しい処理は関数の中)
	MoveInteria(pPlayer);

	// 現在止まっているかつ、モーションをつなげていなかったら
	if (m_move.x == 0.0f && m_move.z == 0.0f &&
		pPlayer->GetMotionPlayer()->GetConnect() == false)
	{
		// ニュートラルモーションにする
		pPlayer->GetMotionPlayer()->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_NEUTRAL);
	}

	if (pPlayer->GetMotionPlayer()->GetMotion() != CMotionPlayer::MOTION_PLAYER_TYPE_LANDING &&
		pPlayer->GetMotionPlayer()->GetConnect() == true)
	{
		m_fSpeed = PLAYER_MOVE_SPEED;
	}

	// 回転の慣性(詳しい処理は関数の中)
	Rotate(pPlayer);

	// プレイヤーが着地しているなら
	if (pPlayer->GetLand() == true)
	{
		// Y方向の移動量を0に
		m_move.x = 0.0f;
		m_move.y = 0.0f;
		m_move.z = 0.0f;
	}
	// プレイヤーが着地してないかつ、止められていないなら
	else if (pPlayer->GetLand() == false && pPlayer->GetStop() == false)
	{
		//移動量加算
		m_move.x += +cosf(D3DX_PI) * PLAYER_JUMP_MOVE;
		m_move.z += -sinf(D3DX_PI) * PLAYER_JUMP_MOVE;
	}

	//オブジェクト情報を入れるポインタ
	CScene *pObject = NULL;
	//オブジェクト情報を保存するポインタ変数
	CScene *pSaveObject = NULL;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CScene::PRIORITY_MODEL);

	// プレイヤーの番号を取得
	int nNumPlayer = pPlayer->GetNum();

	while (pObject != NULL)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		if (pObject->GetObjType() == CScene::OBJECT_TYPE_MODEL)
		{
			//モデルシングルにキャスト
			CModelSingle *pModelSingle = NULL;
			pModelSingle = (CModelSingle*)pObject;

			// プレイヤーの番号とモデルの識別番号が同じなら
			if (nNumPlayer == pModelSingle->GetNum())
			{
				// 次の足場の番号がモデルの番号と一致したら
				if (m_nNextModel == pModelSingle->GetModelNum())
				{
					// モデルの種類を取得する
					m_nNextType = pModelSingle->GetModelType(m_nNextModel);
				}
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CControlPlayer *CControlPlayer::Create(void)
{
	// インスタンスの生成
	CControlPlayer *pControlPlayer = NULL;

	// ヌルチェック
	if (pControlPlayer == NULL)
	{
		// クラスの生成
		pControlPlayer = new CControlPlayer;
		if (pControlPlayer != NULL)
		{
			// 初期化処理
			pControlPlayer->Init();
		}
	}

	return pControlPlayer;
}

//=============================================================================
// 移動処理
//=============================================================================
void CControlPlayer::Move(CPlayer *pPlayer)
{
	// キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ゲームパッド取得処理
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	D3DXVECTOR3 rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// カメラのポインタ配列1番目のアドレス取得
	CCamera **pCameraAddress = CManager::GetCamera();

	// カメラの最大数ぶん、ポインタ配列を進める
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++, pCameraAddress++)
	{
		// カメラの取得
		CCamera *pCamera = &**pCameraAddress;
		if (pCamera != NULL)
		{
			// プレイヤーの番号とカメラの番号が同じだったら
			if (pPlayer->GetNum() == pCamera->GetNum())
			{
				// カメラの向き取得
				rotCamera = pCamera->GetRotV();
			}
		}
	}

	// プレイヤーの番号を取得
	int nNumPlayer = pPlayer->GetNum();

	// キーボードでの2人の入力情報を別々で保存
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER_NUM; nCntPlayer++)
	{
		int nLeft, nRight, nUp, nDown;

		// それぞれのプレイヤーの入力キーを設定
		if (nNumPlayer == 0)
		{
			nLeft = DIK_A;
			nRight = DIK_D;
			nUp = DIK_W;
			nDown = DIK_S;
		}
		else if (nNumPlayer == 1)
		{
			nLeft = DIK_LEFT;
			nRight = DIK_RIGHT;
			nUp = DIK_UP;
			nDown = DIK_DOWN;
		}

		//移動の加速度
		m_fSpeed = PLAYER_MOVE_SPEED;

		//***********************************************************************
		// 移動 (1P:W/A/S/D, 2P:↑/↓/←/→ または パッド左スティック)
		//***********************************************************************
		if (pInputKeyboard->GetPress(nLeft) == true ||
			pInputPad->GetPress(CInputPad::PAD_INPUTTYPE_LSTICK_LEFT, nNumPlayer) == true)
		{
			//左奥移動
			if (pInputKeyboard->GetPress(nUp) == true ||
				pInputPad->GetPress(CInputPad::PAD_INPUTTYPE_LSTICK_UP, nNumPlayer) == true)
			{
				//移動量加算
				m_move.x += +cosf(rotCamera.y + D3DX_PI / 4.0f) * m_fSpeed;
				m_move.z += -sinf(rotCamera.y + D3DX_PI / 4.0f) * m_fSpeed;

				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y - D3DX_PI / 4.0f;
				//回転の慣性をオンにする
				m_bRotate = true;
			}
			//左手前移動
			else if (pInputKeyboard->GetPress(nDown) == true ||
				pInputPad->GetPress(CInputPad::PAD_INPUTTYPE_LSTICK_DOWN, nNumPlayer) == true)
			{
				//移動量加算
				m_move.x += +cosf(rotCamera.y - D3DX_PI / 4.0f) * m_fSpeed;
				m_move.z += -sinf(rotCamera.y - D3DX_PI / 4.0f) * m_fSpeed;

				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y - (D3DX_PI / 4.0f) * 3.0f;
				//回転の慣性をオンにする
				m_bRotate = true;
			}
			//左移動
			else
			{
				//移動量加算
				m_move.x += +cosf(rotCamera.y) * m_fSpeed;
				m_move.z += -sinf(rotCamera.y) * m_fSpeed;

				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y - D3DX_PI / 2.0f;
				//回転の慣性をオンにする
				m_bRotate = true;
			}
		}
		else if (pInputKeyboard->GetPress(nRight) == true ||
			pInputPad->GetPress(CInputPad::PAD_INPUTTYPE_LSTICK_RIGHT, nNumPlayer) == true)
		{
			//右奥移動
			if (pInputKeyboard->GetPress(nUp) == true ||
				pInputPad->GetPress(CInputPad::PAD_INPUTTYPE_LSTICK_UP, nNumPlayer) == true)
			{
				//移動量加算
				m_move.x += -cosf(rotCamera.y - D3DX_PI / 4.0f) * m_fSpeed;
				m_move.z += +sinf(rotCamera.y - D3DX_PI / 4.0f) * m_fSpeed;

				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 4.0f;
				//回転の慣性をオンにする
				m_bRotate = true;
			}
			//右手前移動
			else if (pInputKeyboard->GetPress(nDown) == true ||
				pInputPad->GetPress(CInputPad::PAD_INPUTTYPE_LSTICK_DOWN, nNumPlayer) == true)
			{
				//移動量加算
				m_move.x += -cosf(rotCamera.y + D3DX_PI / 4.0f) * m_fSpeed;
				m_move.z += +sinf(rotCamera.y + D3DX_PI / 4.0f) * m_fSpeed;

				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 1.5f;
				//回転の慣性をオンにする
				m_bRotate = true;
			}
			//右移動
			else
			{
				//移動量加算
				m_move.x += -cosf(rotCamera.y) * m_fSpeed;
				m_move.z += +sinf(rotCamera.y) * m_fSpeed;

				//目的の向きを設定
				m_fObjectiveRot = rotCamera.y + D3DX_PI / 2.0f;
				//回転の慣性をオンにする
				m_bRotate = true;
			}
		}
		//奥移動
		else if (pInputKeyboard->GetPress(nUp) == true ||
			pInputPad->GetPress(CInputPad::PAD_INPUTTYPE_LSTICK_UP, nNumPlayer) == true)
		{
			//移動量加算
			m_move.z += -cosf(rotCamera.y) * m_fSpeed;
			m_move.x += -sinf(rotCamera.y) * m_fSpeed;

			//※奥を向くだけ
			//目的の向きを設定
			m_fObjectiveRot = rotCamera.y;
			//回転の慣性をオンにする
			m_bRotate = true;
		}
		//手前移動
		else if (pInputKeyboard->GetPress(nDown) == true ||
			pInputPad->GetPress(CInputPad::PAD_INPUTTYPE_LSTICK_DOWN, nNumPlayer) == true)
		{
			//移動量加算
			m_move.z += +cosf(rotCamera.y) * m_fSpeed;
			m_move.x += +sinf(rotCamera.y) * m_fSpeed;

			//※手前を向くだけ
			//目的の向きを設定
			m_fObjectiveRot = rotCamera.y + D3DX_PI;
			//回転の慣性をオンにする
			m_bRotate = true;
		}
	}
}

//=============================================================================
// 移動処理
//=============================================================================
void CControlPlayer::GameMove(CPlayer *pPlayer)
{
	// キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ゲームパッド取得処理
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	// サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	D3DXVECTOR3 rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// カメラのポインタ配列1番目のアドレス取得
	CCamera **pCameraAddress = CManager::GetCamera();

	// カメラの最大数ぶん、ポインタ配列を進める
	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++, pCameraAddress++)
	{
		// カメラの取得
		CCamera *pCamera = &**pCameraAddress;
		if (pCamera != NULL)
		{
			// プレイヤーの番号とカメラの番号が同じだったら
			if (pPlayer->GetNum() == pCamera->GetNum())
			{
				// カメラの向き取得
				rotCamera = pCamera->GetRotV();
			}
		}
	}

	// プレイヤーの番号を取得
	int nNumPlayer = pPlayer->GetNum();

	// キーボードでの2人の入力情報を別々で保存
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER_NUM; nCntPlayer++)
	{
		int nLeft, nRight, nDown;

		// それぞれのプレイヤーの入力キーを設定
		if (nNumPlayer == 0)
		{
			nLeft = DIK_A;
			nRight = DIK_D;
			nDown = DIK_S;
		}
		else if (nNumPlayer == 1)
		{
			nLeft = DIK_LEFT;
			nRight = DIK_RIGHT;
			nDown = DIK_DOWN;
		}

		//移動の加速度
		m_fSpeed = PLAYER_MOVE_SPEED;

		// プレイヤーが着地しているなら
		if (pPlayer->GetLand() == true)
		{
			m_move.x = 0.0f;
			m_move.z = 0.0f;
			//***********************************************************************
			// 移動 (1P:W/S/D, 2P:←/↓/→ または パッドX/Y/B)
			//***********************************************************************
			if (pInputKeyboard->GetTrigger(nLeft) == true ||
				pInputPad->GetTrigger(XINPUT_GAMEPAD_X, nNumPlayer) == true)
			{
				if (m_nNextType == 2)
				{
					// ジャンプ処理(詳しい処理は関数の中)
					Jump(pPlayer);

					//目的の向きを設定
					m_fObjectiveRot = 1.569f;
					//回転の慣性をオンにする
					m_bRotate = true;

					m_nNextModel++;

					if (nCntPlayer == 0)
					{
						bAddScore = true;
					}

					if (nCntPlayer == 1)
					{
						bAddScore2 = true;
					}
				}
				else
				{
					// SEの再生
					pSound->Play(CSound::SOUND_LABEL_MISS);
				}
			}
			else if (pInputKeyboard->GetTrigger(nDown) == true ||
				pInputPad->GetTrigger(XINPUT_GAMEPAD_Y, nNumPlayer) == true)
			{
				if (m_nNextType == 3)
				{
					// ジャンプ処理(詳しい処理は関数の中)
					Jump(pPlayer);

					//目的の向きを設定
					m_fObjectiveRot = 1.569f;
					//回転の慣性をオンにする
					m_bRotate = true;

					m_nNextModel++;

					if (nCntPlayer == 0)
					{
						bAddScore = true;
					}

					if (nCntPlayer == 1)
					{
						bAddScore2 = true;
					}
				}
				else
				{
					// SEの再生
					pSound->Play(CSound::SOUND_LABEL_MISS);
				}
			}
			else if (pInputKeyboard->GetTrigger(nRight) == true ||
				pInputPad->GetTrigger(XINPUT_GAMEPAD_B, nNumPlayer) == true)
			{
				if (m_nNextType == 1)
				{
					// ジャンプ処理(詳しい処理は関数の中)
					Jump(pPlayer);

					//目的の向きを設定
					m_fObjectiveRot = 1.569f;
					//回転の慣性をオンにする
					m_bRotate = true;

					m_nNextModel++;

					if (nCntPlayer == 0)
					{
						bAddScore = true;
					}

					if (nCntPlayer == 1)
					{
						bAddScore2 = true;
					}
				}
				else
				{
					// SEの再生
					pSound->Play(CSound::SOUND_LABEL_MISS);
				}
			}
		}
		else
		{
			// 着地したらまたジャンプを可能にする
			m_bJump = false;
		}
	}
}

//=============================================================================
// ジャンプ処理
//=============================================================================
void CControlPlayer::Jump(CPlayer *pPlayer)
{
	// モーション取得処理
	CMotionPlayer *pMotionPlayer = NULL;
	pMotionPlayer = pPlayer->GetMotionPlayer();

	// サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	// SEの再生
	//pSound->Play(CSound::SOUND_LABEL_JUMP);
	//pSound->ControllVoice(CSound::SOUND_LABEL_JUMP, 0.2f);

	// ジャンプモーションにする
	pMotionPlayer->SetMotion(CMotionPlayer::MOTION_PLAYER_TYPE_JUMP);

	// 移動量をジャンプ力ぶん加算
	m_move.y = PLAYER_JUMP;

	// プレイヤーの判定をジャンプした、着地していないに設定
	pPlayer->SetJump(true);
	pPlayer->SetLand(false);

	m_bJump = true;
}

//=============================================================================
// 移動の慣性についての処理
//=============================================================================
void CControlPlayer::MoveInteria(CPlayer *pPlayer)
{
	// 慣性の減算
	m_move.z *= PLAYER_INTERIA_SUBTRACTIO;
	m_move.x *= PLAYER_INTERIA_SUBTRACTIO;
	
	// 移動量が既定の値になったら0にする
	if (m_move.x <= PLAYER_MOVE_STOP_COUNT && m_move.x >= -PLAYER_MOVE_STOP_COUNT)
	{
		m_move.x = 0.0f;
	}
	if (m_move.z <= PLAYER_MOVE_STOP_COUNT && m_move.z >= -PLAYER_MOVE_STOP_COUNT)
	{
		m_move.z = 0.0f;
	}
}

//=============================================================================
// 回転処理
//=============================================================================
void CControlPlayer::Rotate(CPlayer *pPlayer)
{
	// プレイヤーの向きを取得
	D3DXVECTOR3 rotPlayer = pPlayer->GetRot();

	// 回転させる状態なら
	if (m_bRotate == true)
	{
		// 目的の向きを計算
		if (m_fObjectiveRot > D3DX_PI)
		{
			m_fObjectiveRot = -D3DX_PI - (D3DX_PI - m_fObjectiveRot);
		}
		else if (m_fObjectiveRot < -D3DX_PI)
		{
			m_fObjectiveRot = D3DX_PI - (-D3DX_PI - m_fObjectiveRot);
		}

		// プレイヤーの現在の向きごとにそれぞれ向きを変える量を計算
		if (rotPlayer.y < 0.0f && -rotPlayer.y + m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (-D3DX_PI - rotPlayer.y) + -(D3DX_PI - m_fObjectiveRot);
		}
		else if (rotPlayer.y >= D3DX_PI / 2.0f && rotPlayer.y - m_fObjectiveRot > D3DX_PI)
		{
			m_fNumRot = (D3DX_PI - rotPlayer.y) - (-D3DX_PI - m_fObjectiveRot);
		}
		else
		{
			m_fNumRot = (m_fObjectiveRot - rotPlayer.y);
		}

		// プレイヤーの向きに加算
		rotPlayer.y += m_fNumRot * 0.2f;

		// 既定の値に達したら回転をやめる
		if (rotPlayer.y - m_fObjectiveRot < 0.001 && rotPlayer.y - m_fObjectiveRot > -0.001)
		{
			m_bRotate = false;
		}
	}

	// 向きを3.14から-3.14の値の範囲内に収める
	if (rotPlayer.y > D3DX_PI)
	{
		rotPlayer.y -= D3DX_PI * 2.0f;
	}
	else if (rotPlayer.y < -D3DX_PI)
	{
		rotPlayer.y += D3DX_PI * 2.0f;
	}

	// 向きを反映
	pPlayer->SetRot(rotPlayer);
}

bool CControlPlayer::AddScore(void)
{
	return bAddScore;
}

bool CControlPlayer::AddScore2(void)
{
	return bAddScore2;
}