#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef unsigned char u8;
//if ((fp = fopen("D:\\C\\VS2019\\WORKS\\badapple_serial_output\\badapple\\bmp_badapple_data.bin", "rb")) == NULL)

void read_data(u8* data, int num);

int main()
{
    u8 data[673] = { 0 };
    HANDLE hCom1;
    int num = 0;

    hCom1 = CreateFile("COM4", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hCom1 == INVALID_HANDLE_VALUE)
    {
        printf("打开COM失败!\n");
        return FALSE;
    }
    else
    {
        printf("COM打开成功！\n");
    }
    /*********************************配置串口*********************************/
    SetupComm(hCom1, 1024, 1024);//输入缓冲区和输出缓冲区的大小都是20480
    COMMTIMEOUTS TimeOuts;
    //设定读超时
    TimeOuts.ReadIntervalTimeout = 3;                    //1000
    TimeOuts.ReadTotalTimeoutMultiplier = 3;              //500
    TimeOuts.ReadTotalTimeoutConstant = 2;               //5000
    //设定写超时
    TimeOuts.WriteTotalTimeoutMultiplier = 3;             //500
    TimeOuts.WriteTotalTimeoutConstant = 2;              //2000
    SetCommTimeouts(hCom1, &TimeOuts);//设置超时
    DCB dcb;
    GetCommState(hCom1, &dcb);
    dcb.BaudRate = 921600;//波特率为115200
    dcb.ByteSize = 8;//每个字节有8位
    dcb.Parity = NOPARITY;//无奇偶校验位
    dcb.StopBits = ONE5STOPBITS;//两个停止位
    dcb.fParity = FALSE;
    dcb.fNull = FALSE;
    SetCommState(hCom1, &dcb);
    PurgeComm(hCom1, PURGE_TXCLEAR | PURGE_RXCLEAR);//在读写串口之前清空缓冲区

    
    DWORD dwSize = 0;
    for (int i = 0; i < 6576; i++)
    {
        read_data(data, num++);
        WriteFile(hCom1, data, 673, &dwSize, NULL);
        Sleep(22);
        printf("%d\n", dwSize);
    }


}

void read_data(u8* data, int num)
{
    FILE* in = NULL;
    if ((in = fopen("D:\\C\\VS2019\\WORKS\\badapple_serial_output\\badapple\\bmp_badapple_data.bin", "rb")) == NULL)
        printf("Cannot open the file dapple_data_test.bin");
    fseek(in, 672 * num, 0);
    fread(data, 672, 1, in);
    fclose(in);
    data[672] = '#';
    /*
    for (int i = 0; i < 672; i++)
    {
        printf("%2x", data[i]);
        if ((i + 1) % 84 == 0)
            printf("\n");
    }*/
    printf("num=%d  ", num);

}