//=============================================================================
// ゲーム画面 [game.cpp]
// Author : 草刈 翔
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "game.h"
#include "manager.h"
#include "texture.h"
#include "ui.h"
#include "fade.h"
#include "model_single.h"
#include "player.h"
#include "mesh_field.h"
#include "mesh_cylinder.h"
#include "pause.h"
#include "input_keyboard.h"
#include "input_pad.h"
#include "sound.h"
#include "score.h"
#include "time.h"
#include "billboard.h"
#include "control_player.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CGame::CGame()
{
	// 変数のクリア
	memset(&m_apUi, NULL, sizeof(m_apUi));
	memset(&m_apModelSingle, NULL, sizeof(m_apModelSingle));
	memset(&m_apPlayer, NULL, sizeof(m_apPlayer));
	m_pMeshField = NULL;
	memset(&m_pScore, NULL, sizeof(m_pScore)); 
	memset(&m_apBillboard, NULL, sizeof(m_apBillboard));
	m_pTime = NULL;
	m_pPause = NULL;
	m_phase = GAME_PHASE_NONE;
	m_nInterval = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 変数の初期化
	m_nInterval = 0;

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	// BGMの再生
	pSound->Play(CSound::SOUND_LABEL_GAME);

	/*************************/
	/**	  オブジェクト系	**/
	/*************************/
	//+------------------------------------------------+
	//| メッシュフィールドの生成・テクスチャの割り当て |
	//+------------------------------------------------+
	//m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2000.0f, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 5, 5);
	//m_pMeshField->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_FIELD000));

	//+------------------------------------------------+
	//| メッシュシリンダーの生成・テクスチャの割り当て |
	//+------------------------------------------------+
	//※PNG画像の仕様上、外側から描画させる
	// 空の色
	/*m_pMeshCylinder = CMeshCylinder::Create(D3DXVECTOR3(0.0f, -5000.0f, 0.0f), D3DXVECTOR3(5000.0f, 10000.0f, 5000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 16,
		D3DCOLOR_RGBA(30, 30, 30, 255), false);*/

	//+--------------------+
	//| モデル(単体)の生成 |
	//+--------------------+
	for(int nCntModel = 0; nCntModel < GAME_MAX_MODEL / 2; nCntModel++)
	{
		// 1～3の値からランダムに設定
		int nRand = int(rand() % 3) + 1;
		CModelSingle::MODEL_SINGLE_MOVE num = (CModelSingle::MODEL_SINGLE_MOVE)nRand;

		m_apModelSingle[nCntModel] = CModelSingle::Create(D3DXVECTOR3(0.0f - nCntModel * 156.7f, 0.0f, -1200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			CModelLoad::MODEL_TYPE_TEKKOTU, num);

		// どのプレイヤーの足場か設定
		m_apModelSingle[nCntModel]->SetNum(0);
		// 何番目か設定
		m_apModelSingle[nCntModel]->SetModelNum(nCntModel);

		m_apBillboard[nCntModel] = CBillboard::Create(D3DXVECTOR3(0.0f - nCntModel * 156.7f, 50.0f, -1200.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_MODEL);
		switch (nRand)
		{
		case 1:
			m_apBillboard[nCntModel]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_SIGN_ROCK));
			break;
		case 2:
			m_apBillboard[nCntModel]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_SIGN_SCISSORS));
			break;
		case 3:
			m_apBillboard[nCntModel]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_SIGN_PAPERS));
			break;
		}
	}

	//for (int nCntModel = 50; nCntModel < GAME_MAX_MODEL; nCntModel++)
	//{
	//	// 0～3の値からランダムに設定
	//	int nRand = int(rand() % 3) + 1;
	//	CModelSingle::MODEL_SINGLE_MOVE num = (CModelSingle::MODEL_SINGLE_MOVE)nRand;

	//	m_apModelSingle[nCntModel] = CModelSingle::Create(D3DXVECTOR3(0.0f - (nCntModel - 50) * 156.7f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//		CModelLoad::MODEL_TYPE_TEKKOTU, num);

	//	// どのプレイヤーの足場か設定
	//	m_apModelSingle[nCntModel]->SetNum(1);
	//	// 何番目か設定
	//	m_apModelSingle[nCntModel]->SetModelNum(nCntModel - 50);

	//	m_apBillboard[nCntModel] = CBillboard::Create(D3DXVECTOR3(0.0f - nCntModel * 156.7f, 50.0f, -400.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), PRIORITY_MODEL);
	//	/*switch (nRand)
	//	{
	//	case 1:
	//		m_apBillboard[nCntModel]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_SIGN_ROCK));
	//		break;
	//	case 2:
	//		m_apBillboard[nCntModel]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_SIGN_SCISSORS));
	//		break;
	//	case 3:
	//		m_apBillboard[nCntModel]->BindTexture(CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_SIGN_PAPERS));
	//		break;
	//	}*/

	//}

	//+------------------+
	//| プレイヤーの生成 |
	//+------------------+
	m_apPlayer[0] = CPlayer::Create(D3DXVECTOR3(0.0f, 100.0f, -1200.0f), D3DXVECTOR3(0.0f, 1.569f, 0.0f), 0);
	//m_apPlayer[1] = CPlayer::Create(D3DXVECTOR3(0.0f, 100.0f, -400.0f), D3DXVECTOR3(0.0f, 1.569f, 0.0f), 1);

	/*************************/
	/**			UI系		**/
	/*************************/
	//+--------------+
	//| スコアの生成 |
	//+--------------+
	// プレイヤーのスコア
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, 50.0f, 0.0f), D3DXVECTOR3(35.0f, 50.0f, 0.0f), 0);
	//m_pScore[1] = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 600.0f, 50.0f, 0.0f), D3DXVECTOR3(35.0f, 50.0f, 0.0f), 0);

	//+--------------+
	//| ポーズの生成 |
	//+--------------+
	m_pPause = CPause::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//+--------------+
	//| タイムの生成 |
	//+--------------+
	m_pTime = CTime::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f), D3DXVECTOR3(35.0f, 60.0f, 0.0f), 30);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	FILE *pFile;
	int nScore;

	nScore = m_pScore->GetScore();
	
	// スコアを保存するファイル
	pFile = fopen(SCORE_FILENAME, "w");
	if (pFile != NULL)
	{
		fprintf(pFile, "%d\n", nScore);
	}
	else
	{
		printf("ファイルが開けませんでした\n");
	}
	fclose(pFile);
	// オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	//キーボード取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ゲームパッド取得処理
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//フェード取得処理
	CFade *pFade;
	pFade = CManager::GetFade();

	// フェイズ処理(処理は関数の中)
	Phase();

	if (CControlPlayer::AddScore() == true)
	{
		m_pScore->AddScore(1);
		
	}

	/*if (CControlPlayer::AddScore2() == true)
	{
		m_pScore[1]->AddScore(1);
	}*/
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// フェイズ設定処理
//=============================================================================
void CGame::SetPhase(GAME_PHASE phase)
{
	m_phase = phase;
}

//=============================================================================
// フェイズ取得処理
//=============================================================================
CGame::GAME_PHASE CGame::GetPhase(void)
{
	return m_phase;
}

//=============================================================================
// フェーズ処理
//=============================================================================
void CGame::Phase(void)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	//フェード取得処理
	CFade *pFade;
	pFade = CManager::GetFade();

	//フェーズによる処理分け
	switch (m_phase)
	{
	case GAME_PHASE_NONE:
		// フェーズを切り替え
		m_phase = GAME_PHASE_COUNTDOWN;
		break;

	case GAME_PHASE_COUNTDOWN:
		m_nInterval++;
		if (m_nInterval >= 60)
		{
			// フェーズを切り替え
			m_phase = GAME_PHASE_ACTION;
			m_nInterval = 0;
		}
		break;

	case GAME_PHASE_ACTION:
		// プレイヤーを動かせるようにする
		m_apPlayer[0]->SetStop(false);
		//m_apPlayer[1]->SetStop(false);

		if (m_pTime->GetTime() == 0)
		{
			m_phase = GAME_PHASE_CLEAR;
		}
		break;

	case GAME_PHASE_CLEAR:
		// プレイヤーを動かせないようにする
		m_apPlayer[0]->SetStop(true);
		//m_apPlayer[1]->SetStop(true);

		//カウントを増やす
		m_nInterval++;

		// 少し経ったら
		if (m_nInterval >= 50)
		{
			// フェードしていなかったら
			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				// BGMの停止
				pSound->Stop(CSound::SOUND_LABEL_GAME);

				// リザルト画面に遷移
				pFade->SetFade(CManager::MODE_RESULT, D3DCOLOR_RGBA(0, 0, 0, 0));

				//int nScore = m_pScore[0]->GetScore();

				//// スコアのロード
				//m_pScore[0]->LoadScore();

				//// ランキングの設定
				//m_pScore[0]->SetRankScore(nScore, NULL);

				//// スコアのセーブ
				//m_pScore[0]->SaveScore();

				//// リザルト用のスコアを設定
				//m_pScore[0]->SetResultScore(0);
			}
		}
		break;

	default:
		break;
	}
}