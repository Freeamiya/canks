//
// Created by Free on 2026/3/18.
//

#include "uart.h"

uint8 uart_rx_data = 0;
bit uart_rx_flag = 0;
char rx_buf[10];
uint8 rx_index = 0;

void UART_Init(void)
{
    SCON = 0x50;      // 串口模式1
    TMOD |= 0x20;     // 定时器1模式2
    TH1 = 0xFD;       // 9600波特率
    TL1 = 0xFD;
    TR1 = 1;
    ES  = 1;   // 串口中断使能
    EA  = 1;
}

void UART_SendByte(uint8 dat)
{
    SBUF = dat;
    while(!TI);
    TI = 0;
}

void UART_SendStr(char *s)
{
    while(*s)
    {
        UART_SendByte(*s++);
    }
}

void UART_SendHex(uint8 dat)
{
    uint8 high = dat >> 4;     // 高4位
    uint8 low  = dat & 0x0F;   // 低4位

    // 高位
    if(high < 10)
        UART_SendByte('0' + high);
    else
        UART_SendByte('A' + high - 10);

    // 低位
    if(low < 10)
        UART_SendByte('0' + low);
    else
        UART_SendByte('A' + low - 10);
}

int my_atoi(const char *str)
{
    int res = 0;
    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9') {
        res = res * 10 + (*str - '0');
        str++;
    }
    return res * sign;
}

void UART_ISR(void) interrupt 4
{
    if(RI)
    {
        RI = 0;
        char c = SBUF;
        if(c == '\n')   // 一行结束
        {
            rx_buf[rx_index] = '\0';
            rx_index = 0;
            uart_rx_data = (uint8)my_atoi(rx_buf);
            uart_rx_flag = 1;
        }
        else
        {
            rx_buf[rx_index++] = c;
        }
    }
}