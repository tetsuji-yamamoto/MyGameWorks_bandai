#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"

//マクロ
#define MAX_ENEMY (125)		//敵の最大数
#define MAX_SNAKE_BODY (20)	//敵の最大数
#define PB_WIDTH (50)		//幅
#define PB_HEIGHT (100)		//高さ
#define SNAKE_WIDTH (20)	//幅
#define SNAKE_HEIGHT (50)	//高さ
#define SNAKE_MOVESPEED (10)	//蛇の速さ
#define FILE_TEX_PB "data\\ENEMY\\Panchingbag_001.jpg"
#define FILE_TEX_SNAKE "data\\ENEMY\\Snake_001.png"

//敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//通常状態
	ENEMYSTATE_DAMAGE,		//ダメージ状態
	ENEMYSTATE_DEATH,		//死亡状態
	ENEMYSTATE_MAX
}ENEMYSTATE;

//敵の種類
typedef enum 
{
	ENEMYTYPE_PUNCHINGBAG = 0,//サンドバッグpunching bag
	ENEMYTYPE_SNAKE,//蛇
	ENEMYTYPE_MAX
}ENEMYTYPE;

//蛇行動列挙
typedef enum
{
	SNAKESTATE_APPEAR = 0,	//出現
	SNAKESTATE_STANDE,		//待機
	SNAKESTATE_HEADBUTT,	//攻撃Headbutt
	SNAKESTATE_TOUR,		//攻撃tourbutt
	SNAKESTATE_MAX,
}SNAKESTATE;

//蛇構造体
typedef struct
{
	D3DXVECTOR2 posFrontUnion;	//前合体位置
	D3DXVECTOR2 posAnderUnion;	//後ろ合体位置
	SNAKESTATE snakeState;		//蛇の状態
	int nCntBody;				//何番目の体か
	int nChillTime;				//待機している時間
	bool bAttack;				//攻撃するかどうか
}SNAKE;

//体力構造体
typedef struct
{
	float fMaxLife;
	float fLife;
}SNAKEHP;

//蛇の動き構造体
typedef struct
{
	D3DXVECTOR3 pos;	//目的の位置
	D3DXVECTOR3 move;	//移動量
	int nCntMoveTime;	//カウンター
	int nCntMotion;		//動きカウンター
	int nLoopCnt;		//ループカウンター
	float fLength;		//点と点の距離
	float fAngle;		//向き
	float fLot;			//角度
}SNAKEMOVE;

//敵構造体
typedef struct
{
	const char* pFileName;	//ファイル名
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	D3DXCOLOR col;			//色
	RECT rect;				//四頂点情報
	VERTEX vertex;			//四頂点
	ENEMYSTATE state;		//状態
	SNAKE snake;			//蛇情報
	SNAKEMOVE snakeMove;	//蛇の動き
	int nType;				//種類
	float fLife;			//体力
	int nCntState;			//状態管理カウンター
	float fWidth;			//幅
	float fHeight;			//高さ
	bool bUse;				//使っているかどうか
}ENEMY;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(const char * pFileName ,D3DXVECTOR3 pos, int nType, float fLife, float fWidth, float fHeight);
void HitEnemy(int nCntEnemy,float fDamage);
void UpDateSnake(int nCntEnemy);
void SnakeHeadbutt(int nSnakeHead);
void SnakeTour(int nSnakeHead);
void SnakeStand(int nSnakeHead);
ENEMY* GetEnemy(void);
SNAKEHP* GetSnakeHP(void);
int GetNumEnemy(void);
#endif
