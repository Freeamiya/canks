/**
 * CPU: 89C52
 * Freq: 12MHz
*/

#include "config.h"
#include "can.h"
#include "gateway.h"
#include "uart.h"

void mcu_init(void);

void main(void)
{
    //CAN_Init();
    mcu_init();
    UART_Init();
    UART_SendStr("CAN51 Gateway Started\r\n");
    while (1)
    {       
        gateway_process();
    }
}

void mcu_init(void)
{

	MDELAY(10);	//延时

    EX1 = 1;//外部中断1使能；CAN总线接收中断
    IT1 = 1;//CAN总线接收中断，低电平触发
    IT0 = 1;//外部中断0负边沿触发
    EX0 = 1;//打开外部中断0
    EA = 1; //打开总中断
}