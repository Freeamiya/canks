//
// Created by Free on 2026/3/18.
//

#include "uart.h"
#include "config.h"

void UART_Init(void)
{
    SCON = 0x50;      // 串口模式1
    TMOD |= 0x20;     // 定时器1模式2
    TH1 = 0xFD;       // 9600波特率
    TL1 = 0xFD;
    TR1 = 1;
    EA  = 1;
}

void UART_SendByte(uint8 dat)
{
    SBUF = dat;
    while(!TI);
    TI = 0;
}

void uart_printf(const char *format, ...)
{
    char buf[128];   // 缓冲区
    va_list args;

    va_start(args, format);
    vsprintf(buf, format, args);
    va_end(args);

    // 逐字节发送
    {
        char *p = buf;
        while(*p)
        {
            UART_SendByte(*p++);
        }
    }
}