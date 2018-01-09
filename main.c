/* ======================================================================== */
/*  Copyright 2006 by Wintech Digital System Technology Corp.               */
/*  All rights reserved. Property of Texas Instruments Incorporated.        */
/*  Restricted rights to use, duplicate or disclose this code are           */
/*  granted through contract.	                                            */
/* ======================================================================== */
/*========  ͷ�ļ�����===========*/
#include "stdio.h"

/*============= ������������======*/
unsigned char *pr_R;    //ָ�붨��
unsigned char *pr_G;    //ָ�붨��
unsigned char *pr_B;    //ָ�붨��
unsigned char *Gray;    //ָ�붨��

//˵�����������ݴ�ű���
#pragma        DATA_SECTION(RGB_IMG,"data");
int  RGB_IMG[40000];

#pragma        DATA_SECTION(R_IMG,"data");
unsigned char  R_IMG[20000];
#pragma        DATA_SECTION(G_IMG,"data");
unsigned char  G_IMG[20000];
#pragma        DATA_SECTION(B_IMG,"data");
unsigned char  B_IMG[20000];

#pragma        DATA_SECTION(Gray_IMG,"data");
unsigned char  Gray_IMG[20000];


void RGB2Gray();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ʹ��˵����
//   1. �����������Simulator���˶�;
//   2. ������롢���ӡ����سɹ�����
//      ִ��File/data/load����Ҫ������ɫת����ͼ�����ݴ�RGB_peppers96x128.dat
//     ��˵����*.dat��ʽ���ڲ������ĳͼ������ص�RGB��ɫֵ�����������ݴ洢���洢��ַRGB_IMG��
//   3. ���ݼ��سɹ�����Debug/Go Main, һ��һ�����г���
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*================= ������ ================*/
main()
{
	int n,flg,imgH,imgW;
    int *ptr;
/*=========== ��ʼ�� ==========*/
	flg=3;      //����ѡ��ҶȻ�����
	imgH=96;    //ͼ��ĸ����,��Ϊ�����ļ�����Ӧ��ͼ���������96��128
	imgW=128;


	//ָ��ָ������
	pr_R=R_IMG;
	pr_G=G_IMG;
	pr_B=B_IMG;
	Gray=Gray_IMG;

    //1 ��RGB����ͨ�������ݷֱ�ŵ���Ӧ��������
    ptr=RGB_IMG;
    for (n=0;n<imgH*imgW;n++)
       *pr_R++=*ptr++;
    for (n=0;n<imgH*imgW;n++)
       *pr_G++=*ptr++;
    for (n=0;n<imgH*imgW;n++)
       *pr_B++=*ptr++;
    //˵�����ڴ���ͣ���ɿ�ԭʼRGB��ɫͼ��

	//ָ��ָ������
	pr_R=R_IMG;
	pr_G=G_IMG;
	pr_B=B_IMG;
	Gray=Gray_IMG;

    //2 �����ӳ��򣬽��в�ɫͼ��任�ɻҶ�ͼ��
    while (1)
    {

       RGB2Gray(pr_R,pr_G,pr_B,Gray,imgW,imgH,flg);
       while(1);

     }
    //˵�����ڴ���ͣ���ɿ��任��ĻҶ�ͼ��

}



/*============== �ӳ��� =============*/
void RGB2Gray
(    unsigned char   *R,      /* �����ɫͼ���R����   */
     unsigned char   *G,      /* �����ɫͼ���G����   */
     unsigned char   *B,      /* �����ɫͼ���B����   */
     unsigned char   *Gray,   /* ����ĻҶ�ͼ��         */
     int cols, int rows,       /* ͼ��Ŀ����߶�      */
     int flg                  /* ���Ʊ�־������Ϊ1��2��3ʱ���ֱ��ʾ���÷���1��2��3���лҶȻ����� */
)
{
	int  i;  //����ֲ�����

	//����ѭ���ķ�ʽ��ͼ���е�ÿ�����ؽ��лҶȻ�
	for (i = 0; i < cols*rows; i++)
	{
	    if (flg==1)              //����1: ��Ȩƽ����
	       *Gray++=(unsigned char)(0.3*(*R++)+ 0.59*(*G++)+ 0.11*(*B++));
	    else if (flg==2)         //����2: ������ƽ����
	       *Gray++=(unsigned char)(( (*R++)+ (*G++)+ (*B++))/3);
	    else                     //����3: ���ֵ��
	    {
	         Gray[i]= (unsigned char)R[i];
	         if (G[i]>Gray[i])
	             Gray[i]=(unsigned char)G[i];
	         if (B[i]> Gray[i])
	             Gray[i]=(unsigned char)B[i];
	    }
	}
}
/* ======================================================================== */
/*             Copyright (c) 2012 LDX Digital System Technology Corp.   */
/*                         All Rights Reserved.                             */
/* ======================================================================== */
