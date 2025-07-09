#ifndef _SCOR_H_
#define _SCOR_H_

#include "main.h"

// É}ÉNÉçíËã`
#define MAX_NUM (8)			// ñáêî
#define MAX_NUM_HEIGHT (50) // ÇΩÇ©Ç≥
#define MAX_NUM_WIDTH (50)	// ïù

void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValu);
int GetScore(void);
#endif