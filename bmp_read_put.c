
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*定义1 2 4字节类型*/
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
/*定义位图文件头*/
typedef struct bmp_file_header
{
	u16 bType;			//文件标识符
	u32 bSize;			//文件大小
	u16 bReserved1;		//保留值 为0
	u16 bReserved2;		//保留值 为0
	u32 bOffset;		//文件头到实际图像数据的偏移量
} BMP_FILE_HEADER;		//14字节
/*定义位图信息头*/
typedef struct bmp_info
{
	u32 bInfoSize;		//信息头大小
	u32 bWidth;			//图像宽度 单位像素
	u32 bHeight;		//图像高度
	u16 bPlanes;		//固定值 为1
	u16 bBitCounts;		//每个像素的位数 1为黑白 4为16色 8为256色 24为真彩色
	u32 bCompression;	//压缩类型
	u32 bmpImageSize;	//图像大小，以字节为单位
	u32 bXPelsPerMeter;	//水平分辨率，像素每米
	u32 bYPelsPerMeter;	//锤子分辨率，像素每米
	u32 bClrUsed;		//使用的色彩数 为0则为2的bBitCount次方
	u32 bClrImportant;	//重要的色彩数 为0则所有颜色均重要
}BMP_INFO;
/*定义调色板 24为真彩色无此项*/
typedef struct bmp_pallette
{
	u16 rgbRead;		//红色
	u16 rgbGreen;		//绿色
	u16 rgbBlue;		//蓝色
}BMP_PALLETTE;

BMP_FILE_HEADER BmpMessage_Header(void);
BMP_INFO BmpMessage_Info(void);
int main()
{
	//BMP_FILE_HEADER BmpFileHeader;
	//BMP_INFO BmpInfo;

	//BmpFileHeader = BmpMessage_Header();
	//BmpInfo = BmpMessage_Info();
	//printf("%d\n",(int)(BmpInfo.bWidth));
	//
	u16 height = 63;						//图片高 像素为单位 height = BmpInfo.bHeight;
	u16 width = 84;							//图片宽 像素为单位width = BmpInfo.bWidth
	u16 size = 0;							//图片总像素
	u8 Pixel_Color[5376 * 4] = { 0 };		//图片像素点的rgb信息
	u8 Pixel_Gray[5376] = { 0 };			//各像素点灰度
	u8 Pixel_Gray_b[5376] = { 0 };			//背景灰度
	u8 Pixel_Gray_f[5376] = { 0 };			//前景灰度
	u8 m = 0;								//记录背景像素数目
	u8 n = 0;								//记录前景像素数目
	float gray_avg_b = 0;					//背景平均灰度
	float gray_avg_f = 0;					//前景平均灰度
	float var[256] = { 2 };					//类间方差
	float max_var = 0;						//最大类间方差
	u8 threshhold = 80;						//阈值



	//printf("图片总像素点为：%d\n", size);
	//共06576张图片
	//"D:/C/VS2019/WORKS/BMP_READ_PUT/badapple_picture/badapple00330.bmp
	for (int i = 1; i <= 6576; i++)
	{

		char path[100] = "D:/C/VS2019/WORKS/BMP_READ_PUT/badapple_picture/badapple00330.bmp";					//文件路径
		u16 path_num = 0;
		size = height * width + 84;

		u8 bmp_data[672] = { 0 };

		path[56] = i / 10000 + '0';
		path[57] = i / 1000 + '0';
		path[58] = (i / 100) % 10 + '0';
		path[59] = (i / 10) % 10 + '0';
		path[60] = i % 10 + '0';
		printf("名称为%c%c%c%c%c\n", path[56], path[57], path[58], path[59], path[60]);
		FILE* fp;
		if ((fp = fopen(path, "rb")) == NULL)
			printf("打开失败");
		fseek(fp, 54L, 0);
		fread(Pixel_Color, size * 4, 1, fp);
		fclose(fp);
		//打印出初始图像的信息
		/*
		for (int i = 0; i < size; i++)
		{
			printf("%x", Pixel_Color[4*i]);
			//if ((i + 1) % 3 == 0)
				//printf("  ");
			if ((i + 1) % (width) == 0)
				printf("\n");
		}
		printf("以上为初始图片信息\n");
		*/

		//像素灰度计算 灰度=0.11*R+0.59*G+0.3*B 
		for (int i = 0; i < size; i++)
		{
			Pixel_Gray[i] = (unsigned short)(0.11 * Pixel_Color[4 * i] + 0.59 * Pixel_Color[4 * i + 1] + 0.3 * Pixel_Color[4 * i + 2]);
		}
		/*
		//打印显示出各像素点灰度
		for (int i = 0; i < size; i++)
		{
			printf("%4d", Pixel_Gray[i]);
			if ((i + 1) % width == 0)
				printf("\n");
		}
		printf("像素灰度\n");
		*/
		printf("\n");

		//OTSU大律法计算类间方差值
		/* 大律法效果不是很好 先注释掉 直接自定义阈值
		for (int i = 0; i < 256; i++)
		{
			for (int k = 0; k < size; k++)
			{
				if (Pixel_Gray[k] < i)
				{
					Pixel_Gray_b[m] = Pixel_Gray[k];
					m++;
				}
				else
				{
					Pixel_Gray_f[n] = Pixel_Gray[k];
					n++;
				}
			}
			for (int i = 0; i < m; i++)
			{
				gray_avg_b += Pixel_Gray_b[i] / (float)m;
			}
			for (int i = 0; i < n; i++)
			{
				gray_avg_f += Pixel_Gray_f[i] / (float)n;
			}
			var[i] = (float)m / size * (float)n / size * (gray_avg_b - gray_avg_f) * (gray_avg_b - gray_avg_f);
			m = 0;
			n = 0;
			gray_avg_b = 0;
			gray_avg_f = 0;
		}
		*/

		//寻找最大类间方差 以其对应的灰度 i 作为分割依据即阈值
		/*for (int i = 0; i < 256; i++)
		{
			if (var[i] > max_var)
			{
				max_var = var[i];
				threshhold = i;
			}
		}*/
		//打印显示出计算得到的类间方差
		/*
		printf("方差如下\n\n\n\n\n");
		for (int i = 0; i < 256; i++)
		{
			printf("%2.0f ",var[i]);
			if ((i + 1) % 16== 0)
				printf("\n");
		}
		*/
		printf("阈值为：%d 最大类间方差为：%f\n", threshhold, var[threshhold]);
		printf("\n");
		for (int i = 0; i < size; i++)
		{
			if (Pixel_Gray[i] < threshhold)   //以最大类间方差作为分割依据
				Pixel_Gray[i] = 0;
			else
				Pixel_Gray[i] = 1;
		}
		//图像读取顺序纠正
		for (int i = 0; i < width; i++)
		{
			u16 k = width * (height - 1) + 2 * i;
			u8  Temp_Gray = 0;
			for (int j = 0; j < (height / 2); j++)
			{
				Temp_Gray = Pixel_Gray[i + width * j];
				Pixel_Gray[i + width * j] = Pixel_Gray[k - (i + width * j)];
				Pixel_Gray[k - (i + width * j)] = Temp_Gray;
			}
		}
		//最终结果如下
		/*
		for (int i = 0; i < size; i++)
		{
			printf("%d ", Pixel_Gray[i]);
			if ((i + 1) % width == 0)
				printf("\n");
		}
		printf("\n");*/
		//printf("经过大律法处理之后的图片各像素灰度如上\n");
		//每个像素占1位 8个像素合成一个字节 用于oled显示
		for (int i = 0; i < (int)(size / 8); i++)
		{
			u8 k = 0;
			k = i / width;

			for (int j = 0; j < 8; j++)
			{
				if (Pixel_Gray[i + k * 7 * width + width * j] == 1)
					bmp_data[i] += pow(2, j);
				else
					bmp_data[i] += 0;
			}
		}
		//打印bmp数据
		//bmp_data[672] = '#';
		/*for (int i = 0; i < 672; i++)
		{
			printf("%2x", bmp_data[i]);
			if ((i + 1) % 84 == 0)
				printf("\n");
		}
		printf("\n");
		*/
		printf("%d",i);
		fp = fopen("D:/C/VS2019/WORKS/BMP_READ_PUT/pictures/bmp_badapple_data.bin", "ab");
		//bmp_data[672] = '#';
		fwrite(bmp_data, size / 8, 1, fp);
		//fwrite(&bmp_data[672], 1, 1, fp);
		fclose(fp);
	}
	return 0;
}

BMP_FILE_HEADER BmpMessage_Header(void)
{
	BMP_FILE_HEADER BmpFileHeader;
	FILE *fp;
	//D:\C\VS2019\WORKS\BMP_READ_PUT\badapple_picure
	if ((fp = fopen("D:/C/VS2019/WORKS/BMP_READ_PUT/badapple_picture/badapple00330.bmp","rb")) == NULL)
		printf("打开失败");
	
	fread(&BmpFileHeader.bType, 2, 1, fp);
	fread(&BmpFileHeader.bSize, 4, 1, fp);
	fread(&BmpFileHeader.bReserved1, 2, 1, fp);
	fread(&BmpFileHeader.bReserved2, 2, 1, fp);
	fread(&BmpFileHeader.bOffset, 4, 1, fp);

	printf("位图文件头主要是对位图文件的一些描述:BmpFileHeader\n\n");
	printf("文件标识符 = %c%c\n", BmpFileHeader.bType & 0x00ff, BmpFileHeader.bType >> 8);
	printf("BMP文件大小 = %d 字节\n", BmpFileHeader.bSize);
	printf("保留值1 = %u \n", BmpFileHeader.bReserved1);
	printf("保留值2 = %u \n", BmpFileHeader.bReserved2);
	printf("文件头的最后到图像数据位开始的偏移量 = %u 字节\n", BmpFileHeader.bOffset);

	if (!fclose(fp))
		printf("关闭文件成功\n");
	return BmpFileHeader;
}
BMP_INFO BmpMessage_Info(void)
{
	BMP_INFO BmpInfo;
	FILE* fp;
	if ((fp = fopen("D:/C/VS2019/WORKS/BMP_READ_PUT/badapple_picture/badapple00330.bmp", "rb")) == NULL)
		printf("打开失败");
	fseek(fp,14L,0);
	fread(&BmpInfo.bInfoSize, 4, 1, fp);       // 信息头的大小
	fread(&BmpInfo.bWidth, 4, 1, fp);           // 图像的宽度 单位是像素
	fread(&BmpInfo.bHeight, 4, 1, fp);              // 图像的高度
	fread(&BmpInfo.bPlanes, 2, 1, fp);               // 固定值为 1
	fread(&BmpInfo.bBitCounts, 2, 1, fp);             // 每个像素的位数 1为黑白图 4为16色 8为256色 24为真彩色
	fread(&BmpInfo.bCompression, 4, 1, fp);         // 压缩类型
	fread(&BmpInfo.bmpImageSize, 4, 1, fp);         // 图像的大小,以字节为单位
	fread(&BmpInfo.bXPelsPerMeter, 4, 1, fp);       // 水平分辨率 像素/米
	fread(&BmpInfo.bYPelsPerMeter, 4, 1, fp);       // 垂直分辨率
	fread(&BmpInfo.bClrUsed, 4, 1, fp);             // 使用的色彩数 为0 则色彩数为2的biBitCount次方
	fread(&BmpInfo.bClrImportant, 4, 1, fp);        // 重要的颜色数 为0 则所有颜色均重要

	// 输出BMP文件的位图信息头的所有信息
	printf("\n\n位图信息头主要是对位图图像方面信息的描述:BmpInfo\n\n");
	printf("信息头的大小 = %u 字节\n", BmpInfo.bInfoSize);
	printf("位图的高度 = %u \n", BmpInfo.bHeight);
	printf("位图的宽度 = %u \n", BmpInfo.bWidth);
	printf("图像的位面数(位面数是调色板的数量,默认为1个调色板) = %u \n", BmpInfo.bPlanes);
	printf("每个像素的位数 = %u 位\n", BmpInfo.bBitCounts);
	printf("压缩类型 = %u \n", BmpInfo.bCompression);
	printf("图像的大小 = %u 字节\n", BmpInfo.bmpImageSize);
	printf("水平分辨率 = %u \n", BmpInfo.bXPelsPerMeter);
	printf("垂直分辨率 = %u \n", BmpInfo.bYPelsPerMeter);
	printf("使用的色彩数 = %u \n", BmpInfo.bClrUsed);
	printf("重要的色彩数 = %u \n", BmpInfo.bClrImportant);

	if (!fclose(fp))
		printf("关闭文件成功\n");
	return BmpInfo;
}