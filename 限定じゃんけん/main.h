//=============================================================================
// メイン処理 [main.h]
// Author : 草刈 翔
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define DIRECTINPUT_VERSION (0x0800)//ビルド時の警告対処用マクロ
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"					// 描画に必要
#include "dinput.h"					// 入力処理に必要
#include "xaudio2.h"				// サウンド処理に必要
#include <XInput.h>					// ゲームパッド入力に必要
#include <stdio.h>
#include <time.h>					// 時間に関する関数の使用に必要

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment(lib, "d3d9.lib")	// 描画に使用
#pragma comment(lib, "d3dx9.lib")	// [d3d9.lib]の拡張ライブラリ
#pragma comment(lib, "dxguid.lib")	// DirectXコンポーネント使用に必要
#pragma comment(lib, "dinput8.lib") // 入力処理に必要
#pragma comment(lib, "winmm.lib")	// FPS表示に必要
#pragma comment(lib, "xinput.lib")	// ゲームパッド入力に必要

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH (1280)			// ウィンドウの幅
#define SCREEN_HEIGHT (720)			// ウィンドウの高さ
#define MAX_PLAYER_NUM (2)			// プレイヤーの数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
#ifdef _DEBUG
int GetCntFPS(void);				// FPSの取得
#endif

#endif // _MAIN_H_