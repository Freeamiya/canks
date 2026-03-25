//
// Created by Free on 2026/3/18.
//

#include "gateway.h"

static uint8 last_node1 = 0x00;
static uint8 last_node2 = 0x00;

void gateway_process(void)
{
    if(uart_rx_flag)
    {
        uart_rx_flag = 0;

        UART_SendStr("Send CAN ID:01 DATA:");
        UART_SendHex(uart_rx_data);
        UART_SendStr("\r\n");
    }

    else if(node1_data != last_node1)
    {
        last_node1 = node1_data;

        UART_SendStr("Recv ID:01 DATA:");
        UART_SendHex(node1_data);
        UART_SendStr("\r\n");
    }

    else if(node2_data != last_node2)
    {
        last_node2 = node2_data;

        UART_SendStr("Recv ID:02 DATA:");
        UART_SendHex(node2_data);
        UART_SendStr("\r\n");
    }
}