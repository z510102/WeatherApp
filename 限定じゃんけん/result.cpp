//=============================================================================
// リザルト画面 [result.cpp]
// Author : 草刈 翔
//=============================================================================
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "result.h"
#include "manager.h"
#include "texture.h"
#include "ui.h"
#include "score.h"
#include "fade.h"
#include "input_keyboard.h"
#include"rankingdata.h"
#include "input_pad.h"
#include "sound.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CResult::CResult()
{
	// 変数のクリア
	memset(&m_apUi, NULL, sizeof(m_apUi));
	//memset(&m_pScore, NULL, sizeof(m_pScore));
}

//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//サウンド取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	// BGMの再生
	pSound->Play(CSound::SOUND_LABEL_RESULT);
	pSound->ControllVoice(CSound::SOUND_LABEL_RESULT, 0.2f);

	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), 3, CUi::UI_TYPE_RESULT_BG);

	// ランキングの生成
	CRankingData::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 200.0f, 180.0f, 0.0f), D3DXVECTOR3(45.0f, 47.0f, 0.0f), true);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	// オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CResult::Update(void)
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

	// フェードしていない時のみ操作できる
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		for (int nNum = 0; nNum < MAX_PLAYER_NUM; nNum++)
		{
			//***********************************************************************
			// 次へすすむ (Space または パッドAボタン)
			//***********************************************************************
			if (pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
				pInputPad->GetTrigger(XINPUT_GAMEPAD_A, nNum) == true)
			{
				// BGMの停止
				pSound->Stop(CSound::SOUND_LABEL_RESULT);

				// タイトル画面に遷移
				pFade->SetFade(CManager::MODE_TITLE, D3DCOLOR_RGBA(0, 0, 0, 0));
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{

}