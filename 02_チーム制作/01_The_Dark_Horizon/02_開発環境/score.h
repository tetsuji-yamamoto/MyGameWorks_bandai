#ifndef _SCOR_H_
#define _SCOR_H_

#include "main.h"

// �}�N����`
#define MAX_NUM (8)			// ����
#define MAX_NUM_HEIGHT (50) // ������
#define MAX_NUM_WIDTH (50)	// ��

void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void AddScore(int nValu);
int GetScore(void);
#endif