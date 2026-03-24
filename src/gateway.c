//
// Created by Free on 2026/3/18.
//

#include "gateway.h"
#include "uart.h"
#include "can.h"

static uint8 last_node1 = 0xFF;
static uint8 last_node2 = 0xFF;

void gateway_process(void)
{

    if(node1_data != last_node1)
    {
        last_node1 = node1_data;

        uart_printf("ID:01 DATA:%d\r\n", node1_data);
    }

    if(node2_data != last_node2)
    {
        last_node2 = node2_data;

        uart_printf("ID:02 DATA:%d\r\n", node2_data);
    }
}