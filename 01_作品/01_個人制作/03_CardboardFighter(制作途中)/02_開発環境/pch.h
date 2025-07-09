//****************************************
// 
// �v���R���p�C���w�b�_�[
// Author Tetsuji Yamamoto
// 
//****************************************
#ifndef _PCH_H_
#define _PCH_H_

#include<windows.h>
#include <stdio.h>
#include "d3dx9.h"						//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800)	//�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"						//���͏����ɕK�v
#include "Xinput.h"						//�W���C�p�b�h�����ɕK�v
#include "xaudio2.h"					//�T�E���h�����ɕK�v
#include <stdlib.h>

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//[d3d9,lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	//DirectX�R���|�[�l���g(���i)�ɕK�v
#pragma comment(lib,"winmm.lib")	//D
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")	//�W���C�p�b�h�����ɕK�v

#define SCREEN_WIDTH (1280)			//�E�B���h�E�̕�
#define SCREEN_HEIGHT (720)			//�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1) //���W.�@��.�J���[.�e�N�X�`��

#define RGBA_FULLCOLOR 1.0f,1.0f,1.0f,1.0f
#define BACKCOLOR D3DCOLOR_RGBA(100,100,255,100)
#define TEST_WIDTH_CENTER SCREEN_WIDTH * 0.5f
#define TEST_HEIGHT_CENTER SCREEN_HEIGHT * 0.5f
#define D3DXVECTOR3_NULL (D3DXVECTOR3(NULL , NULL , NULL))
#define D3DXCOLOR_FULL (D3DXCOLOR(1.0f , 1.0f , 1.0f,1.0f))
#define D3DXCOLOR_NULL (D3DXCOLOR(0.0f , 0.0f , 0.0f,0.0f))

//���_���[2D]�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//���W�ϊ��p�W��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_2D;

//���_���[3D]�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_3D;

#endif // !_PCH_H_
