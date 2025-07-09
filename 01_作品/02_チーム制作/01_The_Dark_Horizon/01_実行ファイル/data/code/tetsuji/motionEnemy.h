#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"
#include "model.h"

// キーの構造体
typedef struct
{
	float fPosX;// 位置X
	float fPosY;// 位置Y
	float fPosZ;// 位置Z
	float fRotX;// 向きX
	float fRotY;// 向きY
	float fRotZ;// 向きZ
}KEY;

// キー情報の構造体
typedef struct
{
	int nFrame;		// 再生フレーム
	KEY aKey[16];	// 各パーツのキー要素
}KEY_INFO;

// キーモーション情報構造体
typedef struct
{
	bool bLoop;				// ループするかどうか
	int nNumKey;			// キーの総数
	KEY_INFO aKeyinfo[32];	// キー情報
}MOTION_INFO;

typedef struct
{
	MOTION_INFO aMotionInfo[15];	// モーション情報
	int nNumMotion;					// モーションの総数
	bool bLoopMotion;				// ループするかどうか
	int nNumKey;					// キーの総数
	int nKey;						// 現在のキーNo.
	int nCounterMotion;				// モーションカウンター
	int nNowMotiType;				// 現在のモーションタイプ

	int nNextKey;	// 次のキー
}MOTION;

// キャラクターパラメーター
typedef struct
{
	float fWidth;	// 幅
	float fHeigt;	// 高さ
	float fJamp;	// ジャンプ力
	int nNumModel;	// モデル数
	int nLife;		// 体力
	int nState;		// 状態
	int nCntState;	// 状態管理カウンター
	int nCntOcc;	// 発生カウンター
	int nCntDura;	// 持続カウンター
	bool bMove;		// 動くかどうか
	bool bJanp;		// ジャンプしているかどうか
	bool bDisp;		// 表示しますか
	bool bAttack;	// 攻撃しているかどうか
}CHARPARAM;

typedef struct
{
	int nCntMotionInfo;		//	モーション情報をカウントするもの
	int nCntKeyInfo;	//	キーモーションの情報をカウントするもの
	int nCntKey;		//	キーをカウントするもの
}SET_MOTION_MANAGER;

// プロトタイプ宣言
void InitMotion(void);
void ReadMotionText(const char* pFileName,Model *pModel, MOTION* motion, CHARPARAM *charParam);
void ReadScript(FILE *pFile,Model* pModel,MOTION *motion, CHARPARAM* charParam);
void ReadCharacterSet(FILE* pFile, Model* pModel, MOTION* motion, CHARPARAM* charParam);
bool UpdateMotion(MOTION *motion,Model *model, int nType,int nNumModel);

void MostionSet(FILE* pFile, MOTION* motion);
void MostionSet(MOTION* motion, MOTION_INFO setMotInfo);
void KeySet(FILE* pFile, MOTION* motion);
void EndKeySet(MOTION* motion, KEY_INFO keyInfo);
void Key(FILE* pFile, MOTION* motion);
void EndKey(MOTION* motion, KEY key);

void StringClear(char* astr, int nMaxCunt);
void ReadComment(FILE *pFile, char* aResult);
#endif // !_MOTION_H_