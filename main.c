/* ======================================================================== */
/*  Copyright 2006 by Wintech Digital System Technology Corp.               */
/*  All rights reserved. Property of Texas Instruments Incorporated.        */
/*  Restricted rights to use, duplicate or disclose this code are           */
/*  granted through contract.	                                            */
/* ======================================================================== */
/*========  头文件引用===========*/
#include "stdio.h"

/*============= 工作变量定义======*/
unsigned char *pr_R;    //指针定义
unsigned char *pr_G;    //指针定义
unsigned char *pr_B;    //指针定义
unsigned char *Gray;    //指针定义

//说明：定义数据存放变量
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
//使用说明：
//   1. 本程序可以在Simulator下运动;
//   2. 程序编译、链接、加载成功后，先
//      执行File/data/load，将要进行颜色转换的图像数据从RGB_peppers96x128.dat
//     （说明：*.dat格式，内部存放了某图像各像素的RGB颜色值）加载入数据存储器存储地址RGB_IMG中
//   3. 数据加载成功后，再Debug/Go Main, 一步一步运行程序
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*================= 主程序 ================*/
main()
{
	int n,flg,imgH,imgW;
    int *ptr;
/*=========== 初始化 ==========*/
	flg=3;      //用于选择灰度化方法
	imgH=96;    //图像的高与宽,因为数据文件所对应的图像高与宽就是96，128
	imgW=128;


	//指针指向数组
	pr_R=R_IMG;
	pr_G=G_IMG;
	pr_B=B_IMG;
	Gray=Gray_IMG;

    //1 把RGB三个通道的数据分别放到相应的数组中
    ptr=RGB_IMG;
    for (n=0;n<imgH*imgW;n++)
       *pr_R++=*ptr++;
    for (n=0;n<imgH*imgW;n++)
       *pr_G++=*ptr++;
    for (n=0;n<imgH*imgW;n++)
       *pr_B++=*ptr++;
    //说明：在此暂停，可看原始RGB彩色图像

	//指针指向数组
	pr_R=R_IMG;
	pr_G=G_IMG;
	pr_B=B_IMG;
	Gray=Gray_IMG;

    //2 调用子程序，进行彩色图像变换成灰度图像
    while (1)
    {

       RGB2Gray(pr_R,pr_G,pr_B,Gray,imgW,imgH,flg);
       while(1);

     }
    //说明：在此暂停，可看变换后的灰度图像

}



/*============== 子程序 =============*/
void RGB2Gray
(    unsigned char   *R,      /* 输入彩色图像的R分量   */
     unsigned char   *G,      /* 输入彩色图像的G分量   */
     unsigned char   *B,      /* 输入彩色图像的B分量   */
     unsigned char   *Gray,   /* 输出的灰度图像         */
     int cols, int rows,       /* 图像的宽度与高度      */
     int flg                  /* 控制标志，当其为1、2、3时，分别表示采用方法1、2和3进行灰度化处理 */
)
{
	int  i;  //定义局部变量

	//采用循环的方式对图像中的每个像素进行灰度化
	for (i = 0; i < cols*rows; i++)
	{
	    if (flg==1)              //方法1: 加权平均法
	       *Gray++=(unsigned char)(0.3*(*R++)+ 0.59*(*G++)+ 0.11*(*B++));
	    else if (flg==2)         //方法2: 简单算术平均法
	       *Gray++=(unsigned char)(( (*R++)+ (*G++)+ (*B++))/3);
	    else                     //方法3: 最大值法
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
