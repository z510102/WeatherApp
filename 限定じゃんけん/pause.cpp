//=============================================================================
// ポーズ処理 [pause.cpp]
// Author : 草刈 翔
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "pause.h"
#include "manager.h"
#include "texture.h"
#include "ui.h"
#include "fade.h"
#include "input_keyboard.h"
#include "input_pad.h"
#include "sound.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
//int CPause::m_nSelect = 0;
bool CPause::m_bPause = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CPause::CPause(int nPriority) :CScene(nPriority)
{
	// 変数のクリア
	memset(&m_apUi, NULL, sizeof(m_apUi));
	m_pScene2D = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPause::~CPause()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPause::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 変数の初期化
	m_bPause = false;
	//m_nSelect = 0;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPause::Uninit(void)
{
	// 破棄する前にポーズ状態を解除
	m_bPause = false;

	// オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPause::Update(void)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//パッド取得処理
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//フェード取得処理
	CFade *pFade;
	pFade = CManager::GetFade();

	// フェードしていない時のみ操作できる
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		for (int nNum = 0; nNum < MAX_PLAYER_NUM; nNum++)
		{
			int nUp, nDown, nPause;

			// それぞれのプレイヤーでキー入力を分ける
			if (nNum == 0)
			{
				nUp = DIK_W;
				nDown = DIK_S;
				nPause = DIK_P;
			}
			else if (nNum == 1)
			{
				nUp = DIK_UP;
				nDown = DIK_DOWN;
				nPause = NULL;
			}

			//***********************************************************************
			// ポーズ (Pキー または パッドスタートボタン)
			//***********************************************************************
			if (pInputKeyboard->GetTrigger(nPause) == true ||
				pInputPad->GetTrigger(XINPUT_GAMEPAD_BACK, nNum) == true)
			{
				// ゲーム画面なら
				if (CManager::GetMode() == CManager::MODE_GAME)
				{
					// 音量を下げる
					//pSound->ControllVoice(CSound::SOUND_LABEL_GAME, 0.1f);
				}

				// ポーズしていない場合に処理
				if (m_bPause == false)
				{
					// すぐにtrueにして1回だけ処理させる
					m_bPause = true;

					//+------------+
					//|  UIの生成  |
					//+------------+
					// 黒い透明なポリゴンを生成し、画面を暗くする
					m_pScene2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), PRIORITY_UI);
					m_pScene2D->SetColor(D3DCOLOR_RGBA(0, 0, 0, 130));
				}
				// ポーズしている場合に処理
				else if (m_bPause == true)
				{
					CancelPause();
				}
			}

			// ポーズしてるなら操作可能
			if (m_bPause == true)
			{
				//***********************************************************************
				// 選択 (1P:W/S、2P:↑/↓ または パッド左スティック)
				//***********************************************************************
				////上
				//if (pInputKeyboard->GetTrigger(nUp) == true ||
				//	pInputPad->GetTrigger(CInputPad::PAD_INPUTTYPE_LSTICK_UP, nNum) == true)
				//{
				//	// SEの再生
				//	pSound->Play(CSound::SOUND_LABEL_CURSOR);
				//	pSound->ControllVoice(CSound::SOUND_LABEL_CURSOR, 0.2f);

				//	m_nSelect--;
				//}
				////下
				//else if (pInputKeyboard->GetTrigger(nDown) == true ||
				//	pInputPad->GetTrigger(CInputPad::PAD_INPUTTYPE_LSTICK_DOWN, nNum) == true)
				//{
				//	// SEの再生
				//	pSound->Play(CSound::SOUND_LABEL_CURSOR);
				//	pSound->ControllVoice(CSound::SOUND_LABEL_CURSOR, 0.2f);

				//	m_nSelect++;
				//}

				//// 選択肢の制限
				//if (m_nSelect < 1)
				//{
				//	m_nSelect = 3;
				//}
				//else if (m_nSelect > 3)
				//{
				//	m_nSelect = 1;
				//}

				//***********************************************************************
				// 決定 (Enter/Space または Aボタン)
				//***********************************************************************
				//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
				//	pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
				//	pInputPad->GetButtonTrigger(XINPUT_GAMEPAD_A, nNum) == true)
				//{
				//	// m_nSelectの値で処理を変える
				//	switch (m_nSelect)
				//	{
				//		// つづける
				//	case 1:
				//		// SEの再生
				//		pSound->Play(CSound::SOUND_LABEL_DECIDE);
				//		pSound->ControllVoice(CSound::SOUND_LABEL_DECIDE, 0.2f);

				//		CancelPause();
				//		break;

				//		// やりなおす
				//	case 2:
				//		// BGMの停止
				//		pSound->Stop(CSound::SOUND_LABEL_GAME);

				//		// SEの再生
				//		pSound->Play(CSound::SOUND_LABEL_DECIDE);
				//		pSound->ControllVoice(CSound::SOUND_LABEL_DECIDE, 0.2f);

				//		// ゲーム画面なら
				//		if (CManager::GetMode() == CManager::MODE_GAME)
				//		{
				//			// ゲーム画面に遷移
				//			pFade->SetFade(CManager::MODE_GAME, D3DCOLOR_RGBA(0, 0, 0, 0));
				//		}
				//		// ゲーム画面なら
				//		else if (CManager::GetMode() == CManager::MODE_PVP)
				//		{
				//			// ゲーム画面に遷移
				//			pFade->SetFade(CManager::MODE_PVP, D3DCOLOR_RGBA(0, 0, 0, 0));
				//		}
				//		break;

				//		// やめる
				//	case 3:
				//		// BGMの停止
				//		pSound->Stop(CSound::SOUND_LABEL_GAME);

				//		// SEの再生
				//		pSound->Play(CSound::SOUND_LABEL_CANCEL);
				//		pSound->ControllVoice(CSound::SOUND_LABEL_CANCEL, 0.2f);

				//		// メニュー画面に遷移
				//		pFade->SetFade(CManager::MODE_MENU, D3DCOLOR_RGBA(0, 0, 0, 0));
				//		break;

				//	default:
				//		break;
				//	}
				//}
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPause::Draw(void)
{

}

//=============================================================================
// 生成処理
//=============================================================================
CPause *CPause::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// インスタンスの生成
	CPause *pPause = NULL;

	// ヌルチェック
	if (pPause == NULL)
	{
		// クラスの生成
		pPause = new CPause;
		if (pPause != NULL)
		{
			// 初期化処理
			pPause->Init(pos, size);
		}
	}

	return pPause;
}

//=============================================================================
// ポーズ設定処理
//=============================================================================
void CPause::SetPause(bool bPause)
{
	m_bPause = bPause;
}

//=============================================================================
// ポーズ取得処理
//=============================================================================
bool CPause::GetPause(void)
{
	return m_bPause;
}

//=============================================================================
// ポーズ解除時の処理
//=============================================================================
void CPause::CancelPause(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	// すぐにfalseにして1回だけ処理させる
	m_bPause = false;

	// ゲーム画面なら
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// 音量を上げる
		//pSound->ControllVoice(CSound::SOUND_LABEL_GAME, 0.2f);
	}

	// 2Dオブジェクトの破棄
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		delete m_pScene2D;
		m_pScene2D = NULL;
	}

	// UIの破棄
	for (int nCntUi = 0; nCntUi < PAUSE_MAX_UI; nCntUi++)
	{
		if (m_apUi[nCntUi] != NULL)
		{
			m_apUi[nCntUi]->Uninit();
			delete m_apUi[nCntUi];
			m_apUi[nCntUi] = NULL;
		}
	}
}