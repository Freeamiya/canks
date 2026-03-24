/**
 * CPU: 89C52
 * Freq: 12MHz
*/

#include "config.h"
#include "can.h"
#include "gateway.h"
#include "uart.h"

void delay_100ms(void) //@12MHz
{
    unsigned char i, j;

    i = 195;
    j = 138;

    do
    {
        while (--j)
            ;
    } while (--i);
}

void main(void)
{
    //CAN_Init();
    UART_Init();
    while (1)
    {
        gateway_process();
        //uart_printf("Node1: %d, Node2: %d\r\n", node1_data, node2_data);
    }
}
