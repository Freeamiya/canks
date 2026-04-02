/**
 * CPU: 89C52
 * Freq: 12MHz
*/

#include "config.h"
#include "can.h"
#include "gateway.h"
#include "uart.h"
#include "display.h"

void MCU_Init(void);
void test_can(void);
void main(void)
{
    //CAN_Init();
    //MCU_Init();
    UART_Init();
    UART_SendStr("CAN51 Gateway Started\r\n");
    while (1)
    {      
        Gateway_Process();
    }
}

void MCU_Init(void)
{
	SJA_RST = 0;//SJA1000复位有效
	MDELAY(10);	//延时
    SJA_RST = 1;//CAN总线复位管脚,复位无效
    SJA_CS = 0;//CAN总线片选有效
    EX1 = 1;//外部中断1使能；CAN总线接收中断
    IT1 = 1;//CAN总线接收中断
    IT0 = 1;//外部中断0负边沿触发
    EX0 = 1;//打开外部中断0
    EA = 1; //打开总中断
}