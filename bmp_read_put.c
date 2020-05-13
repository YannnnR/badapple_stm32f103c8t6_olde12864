
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*����1 2 4�ֽ�����*/
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
/*����λͼ�ļ�ͷ*/
typedef struct bmp_file_header
{
	u16 bType;			//�ļ���ʶ��
	u32 bSize;			//�ļ���С
	u16 bReserved1;		//����ֵ Ϊ0
	u16 bReserved2;		//����ֵ Ϊ0
	u32 bOffset;		//�ļ�ͷ��ʵ��ͼ�����ݵ�ƫ����
} BMP_FILE_HEADER;		//14�ֽ�
/*����λͼ��Ϣͷ*/
typedef struct bmp_info
{
	u32 bInfoSize;		//��Ϣͷ��С
	u32 bWidth;			//ͼ���� ��λ����
	u32 bHeight;		//ͼ��߶�
	u16 bPlanes;		//�̶�ֵ Ϊ1
	u16 bBitCounts;		//ÿ�����ص�λ�� 1Ϊ�ڰ� 4Ϊ16ɫ 8Ϊ256ɫ 24Ϊ���ɫ
	u32 bCompression;	//ѹ������
	u32 bmpImageSize;	//ͼ���С�����ֽ�Ϊ��λ
	u32 bXPelsPerMeter;	//ˮƽ�ֱ��ʣ�����ÿ��
	u32 bYPelsPerMeter;	//���ӷֱ��ʣ�����ÿ��
	u32 bClrUsed;		//ʹ�õ�ɫ���� Ϊ0��Ϊ2��bBitCount�η�
	u32 bClrImportant;	//��Ҫ��ɫ���� Ϊ0��������ɫ����Ҫ
}BMP_INFO;
/*�����ɫ�� 24Ϊ���ɫ�޴���*/
typedef struct bmp_pallette
{
	u16 rgbRead;		//��ɫ
	u16 rgbGreen;		//��ɫ
	u16 rgbBlue;		//��ɫ
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
	u16 height = 63;						//ͼƬ�� ����Ϊ��λ height = BmpInfo.bHeight;
	u16 width = 84;							//ͼƬ�� ����Ϊ��λwidth = BmpInfo.bWidth
	u16 size = 0;							//ͼƬ������
	u8 Pixel_Color[5376 * 4] = { 0 };		//ͼƬ���ص��rgb��Ϣ
	u8 Pixel_Gray[5376] = { 0 };			//�����ص�Ҷ�
	u8 Pixel_Gray_b[5376] = { 0 };			//�����Ҷ�
	u8 Pixel_Gray_f[5376] = { 0 };			//ǰ���Ҷ�
	u8 m = 0;								//��¼����������Ŀ
	u8 n = 0;								//��¼ǰ��������Ŀ
	float gray_avg_b = 0;					//����ƽ���Ҷ�
	float gray_avg_f = 0;					//ǰ��ƽ���Ҷ�
	float var[256] = { 2 };					//��䷽��
	float max_var = 0;						//�����䷽��
	u8 threshhold = 80;						//��ֵ



	//printf("ͼƬ�����ص�Ϊ��%d\n", size);
	//��06576��ͼƬ
	//"D:/C/VS2019/WORKS/BMP_READ_PUT/badapple_picture/badapple00330.bmp
	for (int i = 1; i <= 6576; i++)
	{

		char path[100] = "D:/C/VS2019/WORKS/BMP_READ_PUT/badapple_picture/badapple00330.bmp";					//�ļ�·��
		u16 path_num = 0;
		size = height * width + 84;

		u8 bmp_data[672] = { 0 };

		path[56] = i / 10000 + '0';
		path[57] = i / 1000 + '0';
		path[58] = (i / 100) % 10 + '0';
		path[59] = (i / 10) % 10 + '0';
		path[60] = i % 10 + '0';
		printf("����Ϊ%c%c%c%c%c\n", path[56], path[57], path[58], path[59], path[60]);
		FILE* fp;
		if ((fp = fopen(path, "rb")) == NULL)
			printf("��ʧ��");
		fseek(fp, 54L, 0);
		fread(Pixel_Color, size * 4, 1, fp);
		fclose(fp);
		//��ӡ����ʼͼ�����Ϣ
		/*
		for (int i = 0; i < size; i++)
		{
			printf("%x", Pixel_Color[4*i]);
			//if ((i + 1) % 3 == 0)
				//printf("  ");
			if ((i + 1) % (width) == 0)
				printf("\n");
		}
		printf("����Ϊ��ʼͼƬ��Ϣ\n");
		*/

		//���ػҶȼ��� �Ҷ�=0.11*R+0.59*G+0.3*B 
		for (int i = 0; i < size; i++)
		{
			Pixel_Gray[i] = (unsigned short)(0.11 * Pixel_Color[4 * i] + 0.59 * Pixel_Color[4 * i + 1] + 0.3 * Pixel_Color[4 * i + 2]);
		}
		/*
		//��ӡ��ʾ�������ص�Ҷ�
		for (int i = 0; i < size; i++)
		{
			printf("%4d", Pixel_Gray[i]);
			if ((i + 1) % width == 0)
				printf("\n");
		}
		printf("���ػҶ�\n");
		*/
		printf("\n");

		//OTSU���ɷ�������䷽��ֵ
		/* ���ɷ�Ч�����Ǻܺ� ��ע�͵� ֱ���Զ�����ֵ
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

		//Ѱ�������䷽�� �����Ӧ�ĻҶ� i ��Ϊ�ָ����ݼ���ֵ
		/*for (int i = 0; i < 256; i++)
		{
			if (var[i] > max_var)
			{
				max_var = var[i];
				threshhold = i;
			}
		}*/
		//��ӡ��ʾ������õ�����䷽��
		/*
		printf("��������\n\n\n\n\n");
		for (int i = 0; i < 256; i++)
		{
			printf("%2.0f ",var[i]);
			if ((i + 1) % 16== 0)
				printf("\n");
		}
		*/
		printf("��ֵΪ��%d �����䷽��Ϊ��%f\n", threshhold, var[threshhold]);
		printf("\n");
		for (int i = 0; i < size; i++)
		{
			if (Pixel_Gray[i] < threshhold)   //�������䷽����Ϊ�ָ�����
				Pixel_Gray[i] = 0;
			else
				Pixel_Gray[i] = 1;
		}
		//ͼ���ȡ˳�����
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
		//���ս������
		/*
		for (int i = 0; i < size; i++)
		{
			printf("%d ", Pixel_Gray[i]);
			if ((i + 1) % width == 0)
				printf("\n");
		}
		printf("\n");*/
		//printf("�������ɷ�����֮���ͼƬ�����ػҶ�����\n");
		//ÿ������ռ1λ 8�����غϳ�һ���ֽ� ����oled��ʾ
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
		//��ӡbmp����
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
		printf("��ʧ��");
	
	fread(&BmpFileHeader.bType, 2, 1, fp);
	fread(&BmpFileHeader.bSize, 4, 1, fp);
	fread(&BmpFileHeader.bReserved1, 2, 1, fp);
	fread(&BmpFileHeader.bReserved2, 2, 1, fp);
	fread(&BmpFileHeader.bOffset, 4, 1, fp);

	printf("λͼ�ļ�ͷ��Ҫ�Ƕ�λͼ�ļ���һЩ����:BmpFileHeader\n\n");
	printf("�ļ���ʶ�� = %c%c\n", BmpFileHeader.bType & 0x00ff, BmpFileHeader.bType >> 8);
	printf("BMP�ļ���С = %d �ֽ�\n", BmpFileHeader.bSize);
	printf("����ֵ1 = %u \n", BmpFileHeader.bReserved1);
	printf("����ֵ2 = %u \n", BmpFileHeader.bReserved2);
	printf("�ļ�ͷ�����ͼ������λ��ʼ��ƫ���� = %u �ֽ�\n", BmpFileHeader.bOffset);

	if (!fclose(fp))
		printf("�ر��ļ��ɹ�\n");
	return BmpFileHeader;
}
BMP_INFO BmpMessage_Info(void)
{
	BMP_INFO BmpInfo;
	FILE* fp;
	if ((fp = fopen("D:/C/VS2019/WORKS/BMP_READ_PUT/badapple_picture/badapple00330.bmp", "rb")) == NULL)
		printf("��ʧ��");
	fseek(fp,14L,0);
	fread(&BmpInfo.bInfoSize, 4, 1, fp);       // ��Ϣͷ�Ĵ�С
	fread(&BmpInfo.bWidth, 4, 1, fp);           // ͼ��Ŀ�� ��λ������
	fread(&BmpInfo.bHeight, 4, 1, fp);              // ͼ��ĸ߶�
	fread(&BmpInfo.bPlanes, 2, 1, fp);               // �̶�ֵΪ 1
	fread(&BmpInfo.bBitCounts, 2, 1, fp);             // ÿ�����ص�λ�� 1Ϊ�ڰ�ͼ 4Ϊ16ɫ 8Ϊ256ɫ 24Ϊ���ɫ
	fread(&BmpInfo.bCompression, 4, 1, fp);         // ѹ������
	fread(&BmpInfo.bmpImageSize, 4, 1, fp);         // ͼ��Ĵ�С,���ֽ�Ϊ��λ
	fread(&BmpInfo.bXPelsPerMeter, 4, 1, fp);       // ˮƽ�ֱ��� ����/��
	fread(&BmpInfo.bYPelsPerMeter, 4, 1, fp);       // ��ֱ�ֱ���
	fread(&BmpInfo.bClrUsed, 4, 1, fp);             // ʹ�õ�ɫ���� Ϊ0 ��ɫ����Ϊ2��biBitCount�η�
	fread(&BmpInfo.bClrImportant, 4, 1, fp);        // ��Ҫ����ɫ�� Ϊ0 ��������ɫ����Ҫ

	// ���BMP�ļ���λͼ��Ϣͷ��������Ϣ
	printf("\n\nλͼ��Ϣͷ��Ҫ�Ƕ�λͼͼ������Ϣ������:BmpInfo\n\n");
	printf("��Ϣͷ�Ĵ�С = %u �ֽ�\n", BmpInfo.bInfoSize);
	printf("λͼ�ĸ߶� = %u \n", BmpInfo.bHeight);
	printf("λͼ�Ŀ�� = %u \n", BmpInfo.bWidth);
	printf("ͼ���λ����(λ�����ǵ�ɫ�������,Ĭ��Ϊ1����ɫ��) = %u \n", BmpInfo.bPlanes);
	printf("ÿ�����ص�λ�� = %u λ\n", BmpInfo.bBitCounts);
	printf("ѹ������ = %u \n", BmpInfo.bCompression);
	printf("ͼ��Ĵ�С = %u �ֽ�\n", BmpInfo.bmpImageSize);
	printf("ˮƽ�ֱ��� = %u \n", BmpInfo.bXPelsPerMeter);
	printf("��ֱ�ֱ��� = %u \n", BmpInfo.bYPelsPerMeter);
	printf("ʹ�õ�ɫ���� = %u \n", BmpInfo.bClrUsed);
	printf("��Ҫ��ɫ���� = %u \n", BmpInfo.bClrImportant);

	if (!fclose(fp))
		printf("�ر��ļ��ɹ�\n");
	return BmpInfo;
}