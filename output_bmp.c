#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
typedef unsigned char u8;

static void SetPos (int x,int y);

int main()
{
	u8 bmp_data[672] = { 0 };			//原始数据一个字节表示8个点 bmp_data[0]表示0到7行的第一列的8个点
	u8 picture_data[672 * 8] = { 0 };
	unsigned int num = 1;
	unsigned int delay = 20;
	//宽84 高64 6576张图片
	FILE* fp;
	if ((fp = fopen("D:\\C\\VS2019\\WORKS\\OUTPUT_BMP\\badapple\\bmp_badapple_data.bin", "rb")) == NULL)
		printf("打开失败");
	//mciSendString("open D:\\C\\VS2019\\WORKS\\OUTPUT_BMP\\badapple\\audio.wav",NULL, 0, NULL);
	//mciSendString("play D:\\C\\VS2019\\WORKS\\OUTPUT_BMP\\badapple\\audio.wav",NULL, 0, NULL);
	for (num; num <= 6576;num++)
	{

		//kk = num * 672;
		//fseek(fp, 0, 0);
		fread(bmp_data, 672, 1, fp);
		for (int i = 0; i < 672; i++)
		{
			u8 k = 0;
			k = i / 84;
			for (int j = 0; j < 8; j++)
			{
				if (((bmp_data[i] >> j) & 0x01) == 0)
					picture_data[i + k * 7 * 84 + 84 * j] = 1;
				else
					picture_data[i + k * 7 * 84 + 84 * j] = 0;
			}
		}
		for (int i = 0; i < 672 * 8; i++)
		{
			printf("%2d", picture_data[i]);
			if ((i + 1) % 84 == 0)
				printf("\n");
		}
		SetPos(0,0);
	}
}

static void SetPos(int x, int y)
{
	COORD point = { x,y };
	HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(HOutput,point);
}